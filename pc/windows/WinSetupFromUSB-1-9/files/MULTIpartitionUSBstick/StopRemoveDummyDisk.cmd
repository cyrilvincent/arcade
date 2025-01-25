echo off
echo Make sure your USB disk is NOT plugged
pause
drvload.exe /n:USBasFixed /remove /quiet
echo.
echo You have to restart your computer in order to complete removal.
pause