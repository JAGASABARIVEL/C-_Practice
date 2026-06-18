@echo off
setlocal EnableExtensions
title Jackdesk Matrix - Caddy (Windows) setup

REM ============================================================================
REM  Windows-side half of the WSL2/Docker deployment (deploy.sh does the rest).
REM  Writes the Caddyfile, adds the hosts entry, registers Caddy as an auto-start
REM  Scheduled Task (no NSSM needed), trusts the internal root CA on THIS server,
REM  and prints the root.crt path to distribute to client machines.
REM
REM  Run as Administrator. Re-runnable (idempotent).
REM ============================================================================

REM ---------------------------- CONFIG (edit me) ------------------------------
set "SERVER_NAME=chat.jackdesk.in"
set "CADDY_DIR=C:\Caddy"
REM ----------------------------------------------------------------------------

set "CADDY=%CADDY_DIR%\caddy.exe"
set "CFG=%CADDY_DIR%\Caddyfile"
set "HOSTS=%SystemRoot%\System32\drivers\etc\hosts"
set "ROOTCA=%CADDY_DIR%\data\pki\authorities\local\root.crt"

echo.
echo === Jackdesk Caddy setup ===
echo   server_name : %SERVER_NAME%
echo   caddy       : %CADDY%
echo.

REM ---- must be elevated ----
net session >nul 2>&1
if errorlevel 1 ( echo [ERROR] Run this script as Administrator. & goto :fail )

REM ---- caddy.exe present ----
if not exist "%CADDY%" ( echo [ERROR] %CADDY% not found. & goto :fail )

REM ---- 1. write Caddyfile (storage pinned so root CA path is deterministic) ----
echo [*] Writing %CFG% ...
>  "%CFG%" echo {
>> "%CFG%" echo 	storage file_system {
>> "%CFG%" echo 		root C:\Caddy\data
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

REM ---- 3. register Caddy as an auto-start Scheduled Task (SYSTEM, no time limit) ----
echo [*] Registering 'Caddy' startup task ...
powershell -NoProfile -ExecutionPolicy Bypass -Command ^
  "$a=New-ScheduledTaskAction -Execute '%CADDY%' -Argument 'run --config \"%CFG%\"';" ^
  "$t=New-ScheduledTaskTrigger -AtStartup;" ^
  "$s=New-ScheduledTaskSettingsSet -ExecutionTimeLimit ([TimeSpan]::Zero) -AllowStartIfOnBatteries -DontStopIfGoingOnBatteries -RestartCount 3 -RestartInterval (New-TimeSpan -Minutes 1);" ^
  "$p=New-ScheduledTaskPrincipal -UserId 'SYSTEM' -LogonType ServiceAccount -RunLevel Highest;" ^
  "Register-ScheduledTask -TaskName 'Caddy' -Action $a -Trigger $t -Settings $s -Principal $p -Force | Out-Null"
if errorlevel 1 ( echo [ERROR] Could not register the Caddy task. & goto :fail )

REM ---- 4. (re)start Caddy now ----
echo [*] Starting Caddy ...
schtasks /end /tn "Caddy" >nul 2>&1
schtasks /run /tn "Caddy" >nul 2>&1
if errorlevel 1 echo [WARN] Could not start the task - check Task Scheduler / port 443.

REM ---- 5. trust the internal root CA on THIS server ----
echo [*] Trusting Caddy internal root CA on this server ...
"%CADDY%" trust --config "%CFG%"

echo.
echo === Done ===
echo   Caddyfile     : %CFG%
echo   Root CA       : %ROOTCA%
echo                   ^(distribute to EVERY client: import into
echo                    "Trusted Root Certification Authorities"^)
echo   Verify        : open https://%SERVER_NAME%/_matrix/client/versions  (no cert warning)
echo   Next          : run the Jackdesk wizard (Connect), download registration.yaml,
echo                   then in WSL:  ./deploy.sh attach ^<path-to-registration.yaml^>
echo.
endlocal
exit /b 0

:fail
echo.
echo *** Caddy setup FAILED. See messages above. ***
endlocal
exit /b 1
