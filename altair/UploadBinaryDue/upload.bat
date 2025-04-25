@echo off

if not "%2"=="" goto go

echo Usage: upload filename.bin COMn
goto end

:go
echo Erasing flash and entering upload mode...
mode %2:1200,N,8,1 >NUL

rem DOS batch scripts don't have a "wait" command so we use "ping" to wait for 1 second.
ping localhost -n 2 >NUL

echo Uploading %1...
bossac -p %2 -U false -e -b -w -v -R %1

:end
