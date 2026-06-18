@echo off
setlocal EnableExtensions
title Jackdesk Matrix - WSL2 boot autostart

REM ============================================================================
REM  Make the WSL2 distro (and therefore Docker + the Synapse/Postgres
REM  containers) come back automatically after a reboot.
REM
REM  Does three things:
REM    1. Enables systemd inside the distro (/etc/wsl.conf).
REM    2. Enables the Docker daemon as a systemd service IN the distro, so the
REM       containers (restart: unless-stopped) restart when the distro boots.
REM       (Skipped automatically if you use Docker Desktop instead of engine-in-WSL.)
REM    3. Registers a Windows logon Scheduled Task that starts the distro, which
REM       triggers systemd -> docker -> containers.
REM
REM  Run as Administrator. Re-runnable.
REM
REM  NOTE: WSL distros are per-user, so the autostart task runs at YOUR logon.
REM  For a truly unattended server, enable Windows auto-login for this account.
REM ============================================================================

REM ---------------------------- CONFIG (edit me) ------------------------------
set "DISTRO=Ubuntu"
REM ----------------------------------------------------------------------------

echo.
echo === WSL2 boot autostart ===
echo   distro : %DISTRO%
echo.

net session >nul 2>&1
if errorlevel 1 ( echo [ERROR] Run this script as Administrator. & goto :fail )

wsl.exe -l -q 2>nul | findstr /i /c:"%DISTRO%" >nul
if errorlevel 1 ( echo [ERROR] WSL distro "%DISTRO%" not found. Run: wsl --list & goto :fail )

REM ---- 1. enable systemd in /etc/wsl.conf (idempotent) ----
echo [*] Enabling systemd in /etc/wsl.conf ...
wsl.exe -d %DISTRO% -u root -- bash -c "grep -q '^systemd=true' /etc/wsl.conf 2>/dev/null || printf '[boot]\nsystemd=true\n' >> /etc/wsl.conf"
if errorlevel 1 ( echo [ERROR] Could not write /etc/wsl.conf. & goto :fail )

REM ---- 2. restart the distro so systemd takes effect ----
echo [*] Restarting WSL to apply systemd (this stops the distro briefly) ...
wsl.exe --shutdown
wsl.exe -d %DISTRO% -u root -- bash -c "true"
timeout /t 3 >nul

REM ---- 3. enable the Docker daemon in the distro (engine-in-WSL only) ----
echo [*] Enabling docker service in the distro (if present) ...
wsl.exe -d %DISTRO% -u root -- bash -c "if systemctl list-unit-files 2>/dev/null | grep -q '^docker.service'; then systemctl enable docker docker.socket >/dev/null 2>&1 && systemctl start docker >/dev/null 2>&1 && echo '    docker.service enabled'; else echo '    no docker.service in distro - assuming Docker Desktop (set it to start on login)'; fi"

REM ---- 4. register a logon Scheduled Task that starts the distro at boot ----
echo [*] Registering 'WSL-Autostart' logon task ...
powershell -NoProfile -ExecutionPolicy Bypass -Command "$u=\"$env:USERDOMAIN\$env:USERNAME\"; $a=New-ScheduledTaskAction -Execute 'wsl.exe' -Argument '-d %DISTRO% -e true'; $t=New-ScheduledTaskTrigger -AtLogOn -User $u; $p=New-ScheduledTaskPrincipal -UserId $u -LogonType Interactive -RunLevel Limited; $s=New-ScheduledTaskSettingsSet -ExecutionTimeLimit ([TimeSpan]::Zero) -AllowStartIfOnBatteries -DontStopIfGoingOnBatteries; Register-ScheduledTask -TaskName 'WSL-Autostart' -Action $a -Trigger $t -Settings $s -Principal $p -Force | Out-Null"
if errorlevel 1 ( echo [ERROR] Could not register the WSL-Autostart task. & goto :fail )

REM ---- 5. bring the stack back up now (so it's running before next reboot) ----
echo [*] Bringing the stack up now ...
wsl.exe -d %DISTRO% -- bash -lc "cd ~/jackdesk-synapse 2>/dev/null && docker compose up -d || echo '    (run ./deploy.sh first if the stack is not set up yet)'"

echo.
echo === Done ===
echo   systemd            : enabled in /etc/wsl.conf
echo   autostart task     : WSL-Autostart (at logon of %USERDOMAIN%\%USERNAME%)
echo   containers         : restart: unless-stopped (come back when docker starts)
echo.
echo   Reboot to verify: after login, the distro + containers should be up.
echo   Headless server?  Enable Windows auto-login for this account so the logon
echo   task fires without someone signing in.
echo.
endlocal
exit /b 0

:fail
echo.
echo *** WSL boot autostart setup FAILED. See messages above. ***
endlocal
exit /b 1
