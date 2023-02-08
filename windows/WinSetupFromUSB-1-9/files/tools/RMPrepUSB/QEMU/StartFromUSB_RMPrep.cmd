@Echo off
cls
TITLE RMPREPUSB QEMU Launcher
REM %1 is USB drive number
REM %2 is memory size
REM %3 is hard disk image

pushd %~dp0
echo EXECUTING %0
echo DRIVE NUMBER=%1
echo MEMORY SIZE=%2
echo HARD DISK IMAGE=%3

REM Flush cache (esp. if NTFS filesystem still writing cache to slow disks)
sync


IF "%3"==""     SET CMD=qemu-system-x86_64.exe -L . -name "RMPrepUSB Emulation Session" -boot c -m %2 -drive file=\\.\PhysicalDrive%1,if=ide,index=0,media=disk,snapshot=on
IF NOT "%3"=="" SET CMD=qemu-system-x86_64.exe -L . -name "RMPrepUSB Emulation Session" -boot c -m %2 -drive file=\\.\PhysicalDrive%1,if=ide,index=0,media=disk,snapshot=on -hdb %3

echo Sending command %CMD% to shell...
%CMD%
if errorlevel 1 echo FAILED!
if errorlevel 1 PAUSE
popd

