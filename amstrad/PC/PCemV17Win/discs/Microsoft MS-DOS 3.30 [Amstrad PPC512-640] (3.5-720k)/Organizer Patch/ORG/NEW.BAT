@echo off
echo You are about to delete ALL the information
echo  stored in the PPC Organizer
echo.
echo Are you sure (Y/N) ?
yn
if errorlevel 1 goto exit
echo Please wait...
del *.doc > nul
del *.dry > nul
copy empty\*.* . > nul

:exit
