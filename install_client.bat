@echo off
setlocal EnableExtensions
title Jackdesk Matrix - client install (hosts auto-updater)

REM ============================================================================
REM  Client half of the on-prem self-healing DNS, in ONE script. Generates the
REM  updater and schedules it - nothing else to copy. Install on EVERY
REM  workstation (run by hand, or push fleet-wide via GPO "Startup Script"/RMM).
REM
REM    1. client-hosts-update.ps1 (C:\Jackdesk\)  -> pulls the server's current IP
REM    2. (optional) import root.crt if it sits next to this .bat -> trust Caddy CA
REM    3. run once now, then schedule 'Jackdesk-UpdateHosts':
REM         boot + 10 min (server head-start), then every N min.
REM
REM  Run as Administrator. Re-runnable (idempotent).
REM ============================================================================

REM ---------------------------- CONFIG (edit me) ------------------------------
set "API_BASE=https://api.jackdesk.com"
REM  ORG_ID + DISCOVERY_TOKEN come from the Matrix wizard's On-prem panel.
set "ORG_ID=REPLACE_ORG_ID"
set "DISCOVERY_TOKEN=REPLACE_DISCOVERY_TOKEN"
set "SERVER_NAME=chat.jackdesk.in"
set "INSTALL_DIR=C:\Jackdesk"
set "REFRESH_MIN=15"
REM ----------------------------------------------------------------------------

set "PS=%INSTALL_DIR%\client-hosts-update.ps1"
set "ARGS=-NoProfile -ExecutionPolicy Bypass -File %PS% -ApiBase %API_BASE% -OrgId %ORG_ID% -Token %DISCOVERY_TOKEN% -HostName %SERVER_NAME%"

REM  base64 of client-hosts-update.ps1 (decoded byte-exact; no escaping issues).
set "CLIENT_B64=PCMKICBKYWNrZGVzayBNYXRyaXggLSBjbGllbnQgaG9zdHMgdXBkYXRlciAocnVucyBvbiBlYWNoIFdpbmRvd3Mgd29ya3N0YXRpb24pLgoKICBSZXNvbHZlcyB0aGUgb24tcHJlbSBTeW5hcHNlIGJveCdzIGN1cnJlbnQgTEFOIElQIGZyb20gdGhlIEphY2tkZXNrIGNsb3VkIGFuZAogIHJld3JpdGVzIHRoZSA8SG9zdE5hbWU+IGxpbmUgaW4gdGhlIFdpbmRvd3MgaG9zdHMgZmlsZSwgc28gdGhlIGJyb3dzZXIga2VlcHMKICByZWFjaGluZyB0aGUgc2VydmVyIGV2ZW4gYWZ0ZXIgaXRzIERIQ1AgYWRkcmVzcyBjaGFuZ2VzLiAgQXV0aGVkIHdpdGggdGhlCiAgbG93LXByaXZpbGVnZSBkaXNjb3ZlcnkgdG9rZW4gKHJlYWQtb25seTsgbmV2ZXIgbWludHMgdXNlcnMpLgoKICBJbnZva2VkIGJ5IHRoZSAnSmFja2Rlc2stVXBkYXRlSG9zdHMnIHNjaGVkdWxlZCB0YXNrIChnZW5lcmF0ZWQgYnkgaW5zdGFsbC1jbGllbnQuYmF0KSwKICB3aGljaCBwYXNzZXMgdGhlIGNvbmZpZyBiZWxvdyBhcyBhcmd1bWVudHMuICBNYW51YWwgcnVuOgoKICAgICAgcG93ZXJzaGVsbCAtRXhlY3V0aW9uUG9saWN5IEJ5cGFzcyAtRmlsZSBjbGllbnQtaG9zdHMtdXBkYXRlLnBzMSBgCiAgICAgICAgLUFwaUJhc2UgaHR0cHM6Ly9hcGkuamFja2Rlc2suY29tIC1PcmdJZCA0MiAtVG9rZW4gPGRpc2NvdmVyeV90b2tlbj4gLUhvc3ROYW1lIGNoYXQuamFja2Rlc2suaW4KIz4KcGFyYW0oCiAgW1BhcmFtZXRlcihNYW5kYXRvcnkgPSAkdHJ1ZSldIFtzdHJpbmddICRBcGlCYXNlLAogIFtQYXJhbWV0ZXIoTWFuZGF0b3J5ID0gJHRydWUpXSBbc3RyaW5nXSAkT3JnSWQsCiAgW1BhcmFtZXRlcihNYW5kYXRvcnkgPSAkdHJ1ZSldIFtzdHJpbmddICRUb2tlbiwKICBbUGFyYW1ldGVyKE1hbmRhdG9yeSA9ICR0cnVlKV0gW3N0cmluZ10gJEhvc3ROYW1lCikKJEVycm9yQWN0aW9uUHJlZmVyZW5jZSA9ICdTdG9wJwoKJFJlc29sdmVVcmwgPSAiJCgkQXBpQmFzZS5UcmltRW5kKCcvJykpL21hdHJpeC9kaXNjb3ZlcnkvJE9yZ0lkL3Jlc29sdmU/dG9rZW49JFRva2VuIgokSG9zdHNGaWxlICA9ICIkZW52OldJTkRJUlxTeXN0ZW0zMlxkcml2ZXJzXGV0Y1xob3N0cyIKCnRyeSB7ICRyZXNwID0gSW52b2tlLVJlc3RNZXRob2QgLU1ldGhvZCBHZXQgLVVyaSAkUmVzb2x2ZVVybCB9IGNhdGNoIHsKICAgIFdyaXRlLVdhcm5pbmcgIkNvdWxkIG5vdCByZWFjaCBKYWNrZGVzayB0byByZXNvbHZlICRIb3N0TmFtZTsgbGVhdmluZyBob3N0cyB1bmNoYW5nZWQuIjsgZXhpdCAwCn0KJGlwID0gJHJlc3Auc2VydmVyX2lwCmlmICgtbm90ICRpcCkgeyBXcml0ZS1XYXJuaW5nICJObyBzZXJ2ZXIgSVAgcmVwb3J0ZWQgeWV0OyBsZWF2aW5nIGhvc3RzIHVuY2hhbmdlZC4iOyBleGl0IDAgfQoKIyBEcm9wIGFueSBleGlzdGluZyBsaW5lIGZvciB0aGlzIGhvc3QsIHRoZW4gYXBwZW5kIHRoZSBmcmVzaCBtYXBwaW5nLgokbGluZXMgPSBAKEdldC1Db250ZW50ICRIb3N0c0ZpbGUgLUVycm9yQWN0aW9uIFNpbGVudGx5Q29udGludWUgfAogICAgICAgICAgIFdoZXJlLU9iamVjdCB7ICRfIC1ub3RtYXRjaCAiXHMkKFtyZWdleF06OkVzY2FwZSgkSG9zdE5hbWUpKVxzKiQiIH0pCiRsaW5lcyArPSAiJGlwYHQkSG9zdE5hbWUiClNldC1Db250ZW50IC1QYXRoICRIb3N0c0ZpbGUgLVZhbHVlICRsaW5lcyAtRW5jb2RpbmcgQVNDSUkKV3JpdGUtSG9zdCAiaG9zdHM6ICRIb3N0TmFtZSAtPiAkaXAiCg=="

echo.
echo === Jackdesk client install ===
echo   server_name : %SERVER_NAME%
echo   org_id      : %ORG_ID%
echo   script      : %PS%   (boot +10 min, then every %REFRESH_MIN% min)
echo.

net session >nul 2>&1
if errorlevel 1 ( echo [ERROR] Run this script as Administrator. & goto :fail )
if "%ORG_ID%"=="REPLACE_ORG_ID" ( echo [ERROR] Edit ORG_ID/DISCOVERY_TOKEN at the top of this .bat first. & goto :fail )
if "%DISCOVERY_TOKEN%"=="REPLACE_DISCOVERY_TOKEN" ( echo [ERROR] Edit ORG_ID/DISCOVERY_TOKEN at the top of this .bat first. & goto :fail )

REM ---- 1. generate the updater script from the embedded base64 ----
if not exist "%INSTALL_DIR%" mkdir "%INSTALL_DIR%"
echo [*] Writing %PS% ...
powershell -NoProfile -Command "[IO.File]::WriteAllBytes('%PS%',[Convert]::FromBase64String($env:CLIENT_B64))"
if errorlevel 1 ( echo [ERROR] Could not write client-hosts-update.ps1. & goto :fail )

REM ---- 2. trust the Caddy root CA if root.crt is shipped next to this .bat ----
if exist "%~dp0root.crt" (
  echo [*] Importing Caddy root CA into Trusted Root Certification Authorities ...
  certutil -addstore -f Root "%~dp0root.crt" >nul && echo     root.crt imported. || echo [WARN] CA import failed - import root.crt manually.
) else (
  echo [*] No root.crt next to this .bat - skipping CA import ^(ensure the Caddy root CA is trusted some other way^).
)

REM ---- 3. run once now ----
echo [*] Updating hosts now ...
powershell -NoProfile -ExecutionPolicy Bypass -File "%PS%" -ApiBase %API_BASE% -OrgId %ORG_ID% -Token %DISCOVERY_TOKEN% -HostName %SERVER_NAME%
if errorlevel 1 echo [WARN] Initial update failed - it will retry on the schedule.

REM ---- 4. schedule: at boot +10 min, repeating every REFRESH_MIN minutes ----
echo [*] Registering 'Jackdesk-UpdateHosts' ...
powershell -NoProfile -ExecutionPolicy Bypass -Command ^
  "$a=New-ScheduledTaskAction -Execute 'powershell.exe' -Argument '%ARGS%';" ^
  "$t=New-ScheduledTaskTrigger -AtStartup;" ^
  "$t.Delay='PT10M';" ^
  "$r=New-ScheduledTaskTrigger -Once -At (Get-Date) -RepetitionInterval (New-TimeSpan -Minutes %REFRESH_MIN%);" ^
  "$s=New-ScheduledTaskSettingsSet -AllowStartIfOnBatteries -DontStopIfGoingOnBatteries -StartWhenAvailable;" ^
  "$p=New-ScheduledTaskPrincipal -UserId 'SYSTEM' -LogonType ServiceAccount -RunLevel Highest;" ^
  "Register-ScheduledTask -TaskName 'Jackdesk-UpdateHosts' -Action $a -Trigger $t,$r -Settings $s -Principal $p -Force | Out-Null"
if errorlevel 1 ( echo [ERROR] Could not register Jackdesk-UpdateHosts. & goto :fail )

echo.
echo === Done ===
echo   task    : Jackdesk-UpdateHosts (boot +10 min, then every %REFRESH_MIN% min)
echo   verify  : open https://%SERVER_NAME%/_matrix/client/versions  (no cert warning)
echo.
endlocal
exit /b 0

:fail
echo.
echo *** Client install FAILED. See messages above. ***
endlocal
exit /b 1
