echo off
echo Make sure your USB disk is NOT plugged
pause
drvload.exe /d:"%~dp0dummydisk.sys" /n:USBasFixed /run
pause