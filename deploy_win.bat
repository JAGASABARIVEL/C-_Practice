@echo off
setlocal EnableExtensions
title Jackdesk Matrix - Windows deploy (Caddy + IP reporter + boot autostart)

REM ============================================================================
REM  Windows half of the on-prem deployment, in ONE script. It GENERATES every
REM  Windows-side file and runs it - nothing else to copy onto this box.
REM
REM    1. Caddyfile (C:\Caddy\Caddyfile)         -> TLS for https://SERVER_NAME
REM    2. hosts entry  127.0.0.1  SERVER_NAME    -> server resolves itself
REM    3. Caddy auto-start Scheduled Task + start + trust internal root CA
REM    4. report-ip.ps1 (C:\Caddy\report-ip.ps1) -> self-reports this box's LAN IP
REM    5. Scheduled Tasks: Jackdesk-ReportIP (boot) + -Refresh (every N min)
REM    6. WSL2 boot autostart (systemd + WSL-Autostart task) so Synapse returns
REM
REM  Run as Administrator. Re-runnable (idempotent). Pairs with deploy.sh (WSL).
REM ============================================================================

REM ---------------------------- CONFIG (edit me) ------------------------------
set "SERVER_NAME=chat.jackdesk.in"
set "API_BASE=https://api.jackdesk.com"
REM  ORG_ID + AS_TOKEN are in the jackdesk-registration.yaml you download from the
REM  wizard (id: jackdesk-<ORG_ID>, as_token: <...>). Required for step 4-5.
set "ORG_ID=REPLACE_ORG_ID"
set "AS_TOKEN=REPLACE_AS_TOKEN"
set "CADDY_DIR=C:\Caddy"
set "DISTRO=Ubuntu"
set "REFRESH_MIN=15"
REM ----------------------------------------------------------------------------

set "CADDY=%CADDY_DIR%\caddy.exe"
set "CFG=%CADDY_DIR%\Caddyfile"
set "HOSTS=%SystemRoot%\System32\drivers\etc\hosts"
set "ROOTCA=%CADDY_DIR%\data\pki\authorities\local\root.crt"
set "PS=%CADDY_DIR%\report-ip.ps1"
set "ARGS=-NoProfile -ExecutionPolicy Bypass -File %PS% -ApiBase %API_BASE% -OrgId %ORG_ID% -AsToken %AS_TOKEN%"

REM  base64 of report-ip.ps1 (decoded byte-exact in step 4; no escaping issues).
set "REPORT_B64=PCMKICBKYWNrZGVzayBNYXRyaXggLSBvbi1wcmVtIHNlcnZlciBJUCByZXBvcnRlciAocnVucyBPTiB0aGUgU3luYXBzZSBib3gpLgoKICBEZXRlY3RzIHRoaXMgbWFjaGluZSdzIHByaW1hcnkgTEFOIElQdjQgYW5kIHJlcG9ydHMgaXQgdG8gdGhlIEphY2tkZXNrIGNsb3VkIHNvCiAgY2xpZW50IHdvcmtzdGF0aW9ucyBjYW4ga2VlcCByZXNvbHZpbmcgdGhlIHNlcnZlcidzIGhvc3RuYW1lIGFmdGVyIERIQ1AgY2hhbmdlcwogIHRoaXMgYm94J3MgYWRkcmVzcy4gIEF1dGhlZCB3aXRoIHRoZSBBUyB0b2tlbiAoc2FtZSB0b2tlbiB0aGF0J3MgaW4KICBqYWNrZGVzay1yZWdpc3RyYXRpb24ueWFtbCkuCgogIEludm9rZWQgYnkgdGhlICdKYWNrZGVzay1SZXBvcnRJUCcgc2NoZWR1bGVkIHRhc2sgKGdlbmVyYXRlZCBieSBkZXBsb3lfd2luLmJhdCksCiAgd2hpY2ggcGFzc2VzIHRoZSBjb25maWcgYmVsb3cgYXMgYXJndW1lbnRzLiAgWW91IGNhbiBhbHNvIHJ1biBpdCBieSBoYW5kOgoKICAgICAgcG93ZXJzaGVsbCAtRXhlY3V0aW9uUG9saWN5IEJ5cGFzcyAtRmlsZSByZXBvcnQtaXAucHMxIGAKICAgICAgICAtQXBpQmFzZSBodHRwczovL2FwaS5qYWNrZGVzay5jb20gLU9yZ0lkIDQyIC1Bc1Rva2VuIDxhc190b2tlbj4KIz4KcGFyYW0oCiAgW1BhcmFtZXRlcihNYW5kYXRvcnkgPSAkdHJ1ZSldIFtzdHJpbmddICRBcGlCYXNlLAogIFtQYXJhbWV0ZXIoTWFuZGF0b3J5ID0gJHRydWUpXSBbc3RyaW5nXSAkT3JnSWQsCiAgW1BhcmFtZXRlcihNYW5kYXRvcnkgPSAkdHJ1ZSldIFtzdHJpbmddICRBc1Rva2VuCikKJEVycm9yQWN0aW9uUHJlZmVyZW5jZSA9ICdTdG9wJwoKJFJlcG9ydFVybCA9ICIkKCRBcGlCYXNlLlRyaW1FbmQoJy8nKSkvbWF0cml4L2Rpc2NvdmVyeS8kT3JnSWQvcmVwb3J0IgoKIyBQcmltYXJ5IExBTiBJUHY0ID0gdGhlIGFkZHJlc3Mgb24gdGhlIGludGVyZmFjZSB0aGF0IG93bnMgdGhlIGRlZmF1bHQgcm91dGU7CiMgc2tpcCBsb29wYmFjayAoMTI3LiopIGFuZCBBUElQQSAoMTY5LjI1NC4qKS4KJGlwID0gR2V0LU5ldElQQ29uZmlndXJhdGlvbiB8CiAgICBXaGVyZS1PYmplY3QgeyAkXy5JUHY0RGVmYXVsdEdhdGV3YXkgLW5lICRudWxsIC1hbmQgJF8uTmV0QWRhcHRlci5TdGF0dXMgLWVxICdVcCcgfSB8CiAgICBTZWxlY3QtT2JqZWN0IC1GaXJzdCAxIC1FeHBhbmRQcm9wZXJ0eSBJUHY0QWRkcmVzcyB8CiAgICBTZWxlY3QtT2JqZWN0IC1GaXJzdCAxIC1FeHBhbmRQcm9wZXJ0eSBJUEFkZHJlc3MKaWYgKC1ub3QgJGlwKSB7CiAgICAkaXAgPSBHZXQtTmV0SVBBZGRyZXNzIC1BZGRyZXNzRmFtaWx5IElQdjQgfAogICAgICAgIFdoZXJlLU9iamVjdCB7ICRfLklQQWRkcmVzcyAtbm90bGlrZSAnMTI3LionIC1hbmQgJF8uSVBBZGRyZXNzIC1ub3RsaWtlICcxNjkuMjU0LionIH0gfAogICAgICAgIFNlbGVjdC1PYmplY3QgLUZpcnN0IDEgLUV4cGFuZFByb3BlcnR5IElQQWRkcmVzcwp9CmlmICgtbm90ICRpcCkgeyBXcml0ZS1FcnJvciAnQ291bGQgbm90IGRldGVybWluZSBhIExBTiBJUHY0IGFkZHJlc3MuJzsgZXhpdCAxIH0KCiRib2R5ID0gQHsgaXAgPSAkaXAgfSB8IENvbnZlcnRUby1Kc29uCkludm9rZS1SZXN0TWV0aG9kIC1NZXRob2QgUG9zdCAtVXJpICRSZXBvcnRVcmwgLUJvZHkgJGJvZHkgLUNvbnRlbnRUeXBlICdhcHBsaWNhdGlvbi9qc29uJyBgCiAgICAtSGVhZGVycyBAeyBBdXRob3JpemF0aW9uID0gIkJlYXJlciAkQXNUb2tlbiIgfSB8IE91dC1OdWxsCldyaXRlLUhvc3QgIlJlcG9ydGVkICRpcCB0byAkUmVwb3J0VXJsIgo="

echo.
echo === Jackdesk Windows deploy ===
echo   server_name : %SERVER_NAME%
echo   api_base    : %API_BASE%
echo   org_id      : %ORG_ID%
echo   caddy       : %CADDY%
echo.

net session >nul 2>&1
if errorlevel 1 ( echo [ERROR] Run this script as Administrator. & goto :fail )
if not exist "%CADDY%" ( echo [ERROR] %CADDY% not found. Put caddy.exe in %CADDY_DIR%. & goto :fail )

REM ---- 1. write Caddyfile (storage pinned so root CA path is deterministic) ----
echo [*] Writing %CFG% ...
if not exist "%CADDY_DIR%" mkdir "%CADDY_DIR%"
>  "%CFG%" echo {
>> "%CFG%" echo 	storage file_system {
>> "%CFG%" echo 		root %CADDY_DIR%\data
>> "%CFG%" echo 	}
>> "%CFG%" echo }
>> "%CFG%" echo.
>> "%CFG%" echo %SERVER_NAME% {
>> "%CFG%" echo 	tls internal
>> "%CFG%" echo 	reverse_proxy 127.0.0.1:8008
>> "%CFG%" echo }

REM ---- 2. hosts entry so SERVER_NAME resolves on this box ----
findstr /i /c:"%SERVER_NAME%" "%HOSTS%" >nul 2>&1
if errorlevel 1 (
  echo [*] Adding hosts entry: 127.0.0.1  %SERVER_NAME%
  >>"%HOSTS%" echo 127.0.0.1    %SERVER_NAME%
  if errorlevel 1 echo [WARN] Could not edit hosts ^(Defender tamper protection?^) - add it manually.
) else (
  echo [*] hosts entry already present.
)

REM ---- 3. Caddy auto-start Scheduled Task + start + trust root CA ----
echo [*] Registering 'Caddy' startup task ...
powershell -NoProfile -ExecutionPolicy Bypass -Command ^
  "$a=New-ScheduledTaskAction -Execute '%CADDY%' -Argument 'run --config \"%CFG%\"';" ^
  "$t=New-ScheduledTaskTrigger -AtStartup;" ^
  "$s=New-ScheduledTaskSettingsSet -ExecutionTimeLimit ([TimeSpan]::Zero) -AllowStartIfOnBatteries -DontStopIfGoingOnBatteries -RestartCount 3 -RestartInterval (New-TimeSpan -Minutes 1);" ^
  "$p=New-ScheduledTaskPrincipal -UserId 'SYSTEM' -LogonType ServiceAccount -RunLevel Highest;" ^
  "Register-ScheduledTask -TaskName 'Caddy' -Action $a -Trigger $t -Settings $s -Principal $p -Force | Out-Null"
if errorlevel 1 ( echo [ERROR] Could not register the Caddy task. & goto :fail )
echo [*] Starting Caddy ...
schtasks /end /tn "Caddy" >nul 2>&1
schtasks /run /tn "Caddy" >nul 2>&1
echo [*] Trusting Caddy internal root CA on this server ...
"%CADDY%" trust --config "%CFG%"

REM ---- 4. generate report-ip.ps1 from the embedded base64 ----
echo [*] Writing %PS% ...
powershell -NoProfile -Command "[IO.File]::WriteAllBytes('%PS%',[Convert]::FromBase64String($env:REPORT_B64))"
if errorlevel 1 ( echo [ERROR] Could not write report-ip.ps1. & goto :fail )

if "%ORG_ID%"=="REPLACE_ORG_ID" ( echo [WARN] ORG_ID/AS_TOKEN not set - skipping IP reporter ^(steps 4-5^). Edit them and re-run. & goto :boot )
if "%AS_TOKEN%"=="REPLACE_AS_TOKEN" ( echo [WARN] ORG_ID/AS_TOKEN not set - skipping IP reporter ^(steps 4-5^). Edit them and re-run. & goto :boot )

REM ---- 5. report once now + schedule boot/refresh tasks ----
echo [*] Reporting current IP now ...
powershell -NoProfile -ExecutionPolicy Bypass -File "%PS%" -ApiBase %API_BASE% -OrgId %ORG_ID% -AsToken %AS_TOKEN%
if errorlevel 1 echo [WARN] Initial report failed - check connectivity to %API_BASE%.
echo [*] Registering 'Jackdesk-ReportIP' (at startup) ...
powershell -NoProfile -ExecutionPolicy Bypass -Command ^
  "$a=New-ScheduledTaskAction -Execute 'powershell.exe' -Argument '%ARGS%';" ^
  "$t=New-ScheduledTaskTrigger -AtStartup;" ^
  "$s=New-ScheduledTaskSettingsSet -AllowStartIfOnBatteries -DontStopIfGoingOnBatteries -StartWhenAvailable;" ^
  "$p=New-ScheduledTaskPrincipal -UserId 'SYSTEM' -LogonType ServiceAccount -RunLevel Highest;" ^
  "Register-ScheduledTask -TaskName 'Jackdesk-ReportIP' -Action $a -Trigger $t -Settings $s -Principal $p -Force | Out-Null"
if errorlevel 1 ( echo [ERROR] Could not register Jackdesk-ReportIP. & goto :fail )
echo [*] Registering 'Jackdesk-ReportIP-Refresh' (every %REFRESH_MIN% min) ...
powershell -NoProfile -ExecutionPolicy Bypass -Command ^
  "$a=New-ScheduledTaskAction -Execute 'powershell.exe' -Argument '%ARGS%';" ^
  "$t=New-ScheduledTaskTrigger -Once -At (Get-Date) -RepetitionInterval (New-TimeSpan -Minutes %REFRESH_MIN%);" ^
  "$s=New-ScheduledTaskSettingsSet -AllowStartIfOnBatteries -DontStopIfGoingOnBatteries -StartWhenAvailable;" ^
  "$p=New-ScheduledTaskPrincipal -UserId 'SYSTEM' -LogonType ServiceAccount -RunLevel Highest;" ^
  "Register-ScheduledTask -TaskName 'Jackdesk-ReportIP-Refresh' -Action $a -Trigger $t -Settings $s -Principal $p -Force | Out-Null"
if errorlevel 1 ( echo [ERROR] Could not register Jackdesk-ReportIP-Refresh. & goto :fail )

:boot
REM ---- 6. WSL2 boot autostart (systemd + logon task) so Synapse comes back ----
wsl.exe -l -q 2>nul | findstr /i /c:"%DISTRO%" >nul
if errorlevel 1 (
  echo [WARN] WSL distro "%DISTRO%" not found - skipping boot autostart. Run deploy.sh in WSL first.
  goto :done
)
echo [*] Enabling systemd in /etc/wsl.conf ...
wsl.exe -d %DISTRO% -u root -- bash -c "grep -q '^systemd=true' /etc/wsl.conf 2>/dev/null || printf '[boot]\nsystemd=true\n' >> /etc/wsl.conf"
echo [*] Restarting WSL to apply systemd ...
wsl.exe --shutdown
wsl.exe -d %DISTRO% -u root -- bash -c "true"
echo [*] Enabling docker service in the distro (if present) ...
wsl.exe -d %DISTRO% -u root -- bash -c "if systemctl list-unit-files 2>/dev/null | grep -q '^docker.service'; then systemctl enable docker docker.socket >/dev/null 2>&1 && systemctl start docker >/dev/null 2>&1 && echo '    docker.service enabled'; else echo '    no docker.service - assuming Docker Desktop'; fi"
echo [*] Registering 'WSL-Autostart' logon task ...
powershell -NoProfile -ExecutionPolicy Bypass -Command "$u=\"$env:USERDOMAIN\$env:USERNAME\"; $a=New-ScheduledTaskAction -Execute 'wsl.exe' -Argument '-d %DISTRO% -e true'; $t=New-ScheduledTaskTrigger -AtLogOn -User $u; $p=New-ScheduledTaskPrincipal -UserId $u -LogonType Interactive -RunLevel Limited; $s=New-ScheduledTaskSettingsSet -ExecutionTimeLimit ([TimeSpan]::Zero) -AllowStartIfOnBatteries -DontStopIfGoingOnBatteries; Register-ScheduledTask -TaskName 'WSL-Autostart' -Action $a -Trigger $t -Settings $s -Principal $p -Force | Out-Null"
echo [*] Bringing the stack up now ...
wsl.exe -d %DISTRO% -- bash -lc "cd ~/jackdesk-synapse 2>/dev/null && docker compose up -d || echo '    (run ./deploy.sh in WSL first if the stack is not set up yet)'"

:done
echo.
echo === Done ===
echo   Caddyfile     : %CFG%
echo   Root CA       : %ROOTCA%
echo                   ^(distribute to EVERY client, or let install-client.bat import it^)
echo   IP reporter   : %PS%  ^(tasks: Jackdesk-ReportIP, -Refresh^)
echo   WSL autostart : WSL-Autostart ^(at logon^) + systemd in the distro
echo   Verify        : https://%SERVER_NAME%/_matrix/client/versions ^(no cert warning^)
echo                   and the wizard's On-prem panel shows this box's LAN IP.
echo.
endlocal
exit /b 0

:fail
echo.
echo *** Windows deploy FAILED. See messages above. ***
endlocal
exit /b 1
