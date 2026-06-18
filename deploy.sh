#!/usr/bin/env bash
#
# Jackdesk Matrix — WSL2/Docker deployer (run INSIDE the WSL2 Ubuntu distro).
#
#   ./deploy.sh                 phases 1-8: prereqs, stack, generate+patch config,
#                               start Synapse (phase 1, no AS), write Caddyfile,
#                               print the Windows/browser hand-off steps.
#   ./deploy.sh attach <file>   phase 9-10: attach the downloaded registration.yaml
#                               and restart Synapse, then print provision/verify.
#
# What bash CANNOT do (printed for you to run elevated on Windows / in the browser):
#   - wsl --install, registering Caddy as a Windows service (NSSM), `caddy trust`,
#     editing the Windows hosts file, distributing the root CA to clients,
#     and the wizard Connect / Provision / Verify clicks.
#
set -euo pipefail

# Resolve to the script's own dir so it works from anywhere.
cd "$(dirname "$(readlink -f "$0")")"

# ── helpers ───────────────────────────────────────────────────────────────────
c_g(){ printf '\033[1;32m%s\033[0m\n' "$*"; }   # green banner
c_y(){ printf '\033[1;33m%s\033[0m\n' "$*"; }   # yellow note
c_r(){ printf '\033[1;31m%s\033[0m\n' "$*"; }   # red
die(){ c_r "ERROR: $*"; exit 1; }
pause(){ read -r -p "$(c_y "↳ Press Enter once done...")" _; }
dc(){ docker compose "$@"; }

WIN_CADDY="/mnt/c/Caddy"

load_env(){
  [ -f .env ] || die ".env not found. Copy .env.example to .env and fill it in."
  set -a; . ./.env; set +a
  : "${SERVER_NAME:?set SERVER_NAME in .env}"
  : "${SYNAPSE_DB_PASSWORD:?set SYNAPSE_DB_PASSWORD in .env}"
  [ "$SYNAPSE_DB_PASSWORD" = "CHANGE_ME" ] && die "Set a real SYNAPSE_DB_PASSWORD in .env."
}

# ── PHASE 9-10: attach AS + restart, then provision/verify ────────────────────
if [ "${1:-}" = "attach" ]; then
  load_env
  REG="${2:-}"
  [ -n "$REG" ] && [ -f "$REG" ] || die "Usage: ./deploy.sh attach <path-to-registration.yaml>"
  c_g "== Phase 9: attach Application Service =="
  cp "$REG" data/jackdesk-registration.yaml
  cat > data/_attach.py <<'PYEOF'
import yaml
p = "/data/homeserver.yaml"
c = yaml.safe_load(open(p))
files = c.get("app_service_config_files") or []
reg = "/data/jackdesk-registration.yaml"
if reg not in files:
    files.append(reg)
c["app_service_config_files"] = files
yaml.safe_dump(c, open(p, "w"), default_flow_style=False, sort_keys=False)
print("app_service_config_files ->", files)
PYEOF
  dc run --rm --no-deps --entrypoint python3 synapse /data/_attach.py
  rm -f data/_attach.py
  dc restart synapse
  c_g "Synapse restarted with the AS attached."
  echo
  c_g "== Phase 10: provision + verify (in the Jackdesk wizard) =="
  echo "  Back in the wizard: run Provision (mints per-user tokens via the AS),"
  echo "  then it calls POST /matrix/setup/verify -> tenant becomes 'active'."
  echo "  Team Chat now talks to https://$SERVER_NAME directly."
  exit 0
fi

# ── PHASE 1: prerequisites ────────────────────────────────────────────────────
c_g "== Phase 1: prerequisites =="
grep -qi microsoft /proc/version || c_y "Note: this doesn't look like WSL2 — continuing anyway."
command -v docker >/dev/null || die "docker not found. Install Docker (Desktop w/ WSL2 backend, or engine in WSL)."
docker compose version >/dev/null 2>&1 || die "'docker compose' v2 not available."
docker info >/dev/null 2>&1 || die "Docker daemon not reachable. Start Docker and retry."
[ -d /mnt/c ] || die "/mnt/c not mounted — are you in WSL2?"
[ -x "$WIN_CADDY/caddy.exe" ] || c_y "Note: $WIN_CADDY/caddy.exe not found yet — put caddy.exe (+nssm.exe) there before Phase 6."
case "$PWD" in /mnt/*) c_y "WARNING: project is on /mnt/c. Move it to the WSL Linux fs (~/) for the ./data bind mount.";; esac

# ── PHASE 2: stack on the Linux fs ────────────────────────────────────────────
c_g "== Phase 2: stack files =="
load_env
mkdir -p data
[ -f docker-compose.yml ] || die "docker-compose.yml missing next to this script."
c_g "Using SERVER_NAME=$SERVER_NAME"

# ── PHASE 3-4: generate config, then swap in Postgres + harden ────────────────
c_g "== Phase 3-4: generate + patch homeserver.yaml =="
if [ ! -f data/homeserver.yaml ]; then
  c_g "Generating homeserver.yaml + signing key + secrets (official 'generate')..."
  dc run --rm --no-deps \
    -e SYNAPSE_SERVER_NAME="$SERVER_NAME" \
    -e SYNAPSE_REPORT_STATS=no \
    synapse generate
else
  c_y "data/homeserver.yaml already exists — leaving signing key/secrets as is."
fi

# Patch with the container's own PyYAML (robust; runs as the image's uid).
cat > data/_patch.py <<'PYEOF'
import os, yaml
p = "/data/homeserver.yaml"
c = yaml.safe_load(open(p))
c["database"] = {
    "name": "psycopg2",
    "args": {
        "user": "synapse",
        "password": os.environ["DBPW"],
        "database": "synapse",
        "host": "postgres",
        "port": 5432,
        "cp_min": 5,
        "cp_max": 10,
    },
}
for lst in c.get("listeners", []):
    if lst.get("type") == "http":
        lst["x_forwarded"] = True          # trust Caddy's X-Forwarded-* headers
c["enable_registration"] = False           # users are minted via the AS
c["report_stats"] = False
c["trusted_key_servers"] = []              # intranet-only, no federation
c["suppress_key_server_warning"] = True
c["max_upload_size"] = "50M"
yaml.safe_dump(c, open(p, "w"), default_flow_style=False, sort_keys=False)
print("homeserver.yaml -> Postgres + hardened")
PYEOF
dc run --rm --no-deps -e DBPW="$SYNAPSE_DB_PASSWORD" --entrypoint python3 synapse /data/_patch.py
rm -f data/_patch.py

# ── PHASE 5: start Synapse (phase 1 — no AS yet) ──────────────────────────────
c_g "== Phase 5: start Synapse (no AS yet) =="
dc up -d
c_y "Waiting for Synapse health..."
for i in $(seq 1 30); do
  if curl -fsS http://127.0.0.1:8008/health >/dev/null 2>&1; then ok=1; break; fi
  sleep 2
done
[ "${ok:-}" = 1 ] || die "Synapse did not become healthy. Check: docker compose logs synapse"
curl -fsS http://127.0.0.1:8008/_matrix/client/versions >/dev/null && c_g "Synapse is up on 127.0.0.1:8008."

# ── PHASE 6-7: Caddy service + DNS/hosts + trust root CA (Windows side) ────────
c_g "== Phase 6-7: Caddy (native Windows) =="
c_r "bash can't register services, edit hosts, or trust the CA — run the .bat."
cat <<EOF
  In an ELEVATED Windows cmd (set SERVER_NAME=$SERVER_NAME at the top of the .bat first):
      C:\\…\\wsl2-docker\\caddy-setup.bat
  It writes C:\\Caddy\\Caddyfile, adds the hosts entry, registers Caddy as an
  auto-start task, starts it, and trusts the internal root CA on this server.

  Then distribute the root CA to EVERY client (browser = Matrix client; an
  untrusted cert breaks Team Chat):
      file:  C:\\Caddy\\data\\pki\\authorities\\local\\root.crt
      import into "Trusted Root Certification Authorities" (manually or by GPO).
  Verify from a client:  https://$SERVER_NAME/_matrix/client/versions  (no warning)
EOF
c_y "On client machines, the customer's DNS must resolve $SERVER_NAME to the server's LAN IP."
pause

# ── PHASE 8: wizard Connect + download registration.yaml ──────────────────────
c_g "== Phase 8: Jackdesk wizard (Connect) =="
cat <<EOF
  In Jackdesk: Admin -> Integrations -> Matrix setup.
  Enter homeserver URL:   https://$SERVER_NAME
  The browser probes /versions, POST /matrix/setup/connect creates the tenant
  (pending) and offers registration.yaml. Download it.
EOF
echo
c_g "Then finish with phase 9-10:"
echo "  ./deploy.sh attach /mnt/c/Users/<you>/Downloads/jackdesk-registration.yaml"
