cls
del MBR*.bin
ML /Zm /Fl /Fm /W3 /DPTN0=TRUE /DPTN1=FALSE /DPTN2=FALSE /DSPT32=FALSE TESTMBR.asm
if errorlevel 1 goto :END
exe2bin TESTMBR.exe MBR0P.BIN
ML /Zm /Fl /Fm /W3 /DPTN0=FALSE /DPTN1=TRUE /DPTN2=FALSE /DSPT32=FALSE TESTMBR.asm
exe2bin TESTMBR.exe MBR1P63S.BIN
ML /Zm /Fl /Fm /W3 /DPTN0=FALSE /DPTN1=FALSE /DPTN2=TRUE /DSPT32=FALSE TESTMBR.asm
exe2bin TESTMBR.exe MBR2P63S.BIN
ML /Zm /Fl /Fm /W3 /DPTN0=FALSE /DPTN1=TRUE /DPTN2=FALSE /DSPT32=TRUE TESTMBR.asm
exe2bin TESTMBR.exe MBR1P32S.BIN
ML /Zm /Fl /Fm /W3 /DPTN0=FALSE /DPTN1=FALSE /DPTN2=TRUE /DSPT32=TRUE TESTMBR.asm
exe2bin TESTMBR.exe MBR2P32S.BIN
dir mbr*.bin
:END
pause

