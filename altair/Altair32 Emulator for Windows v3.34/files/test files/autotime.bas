10 REM ****** MICROSOFT DISK BASIC, RUNNING UNDER CP/M ******
20 REM *** REV. BY HARRY KAEMMERER 07/14/1979 ***
30 REM *** PGM TO AUTO DISPLAY & UPDATE TIME OF COMPU/TIME
40 REM    CLOCK MODEL T102A ***
50 REM
60 REM *** SET DISPLAY SCREEN WIDTH ***
70 WIDTH 80
80 REM *** CLEAR SCREEN COMMAND ***
90 PRINT CHR$(27)+"c"
91 REM PRINT CHR$(12)
100 REM
110 REM *** CHANGE Pl= TO DECIMAL ADDRESS OF YOUR STARTING PORT ***
120 REM *** l92=C0Hex ***
130 P1=128
140 X=0
150 H=23:V=0:GOSUB 780
160 IF X=1 THEN PRINT CHR$(8)
170 IF X=0 THEN PRINT" TIME ";
180 REM *** HOUR TENS ***
190 OUT P1,0
200 H1=INP(P1)
210 REM *** HOUR UNITS ***
220 OUT P1,1
230 H2=INP(P1)
240 REM *** MINUTE TENS ***
250 OUT P1,2
260 M1=INP(P1)
270 REM *** MINUTE UNITS ***
280 OUT P1,3
290 M2=INP(P1)
300 REM *** SECOND TENS ***
310 OUT P1,4
320 S1=INP(P1)
330 REM *** SECOND UNITS ***
340 OUT P1,5
350 S2=INP(P1)
360 T1=H1+H2+M1+M2+S1+S2
370 IF T1=T2 THEN 190
380 T2=T1
390 REM *** ELIMINATE SPACES BETWEEN NUMBERS BY CONVERTING TO STRINGS ***
400 H1$=CHR$(H1+48): IF H1=0 THEN H1$="0"
410 H2$=CHR$(H2+48): IF H2=0 THEN H2$="0"
420 M1$=CHR$(M1+48): IF M1=0 THEN M1$="0"
430 M2$=CHR$(M2+48): IF M2=0 THEN M2$="0"
440 S1$=CHR$(S1+48): IF S1=0 THEN S1$="0"
450 S2$=CHR$(S2+48): IF S2=0 THEN S2$="0"
460 IF X=1 THEN H=29:V=0: GOSUB 780
470 PRINT H1$;H2$;":";M1$;M2$;":";S1$;S2$;
480 IF X=1 THEN 160
490 PRINT"  DATE ";
500 REM *** MONTH TENS ***
510 OUT P1,8
520 M1=INP(P1)
530 IF M1=15 THEN M1=0
540 REM *** MONTH UNITS ***
550 OUT P1,9
560 M2=INP(P1)
570 REM *** DAY TENS ***
580 OUT P1,10
590 D1=INP(P1)
600 REM *** DAY UNITS ***
610 OUT P1,11
620 D2=INP(P1)
630 REM *** ELIMINATE SPACES BETWEEN NUMBERS BY CONVERTING TO STRINGS ***
640 M1$=CHR$(M1+48)
650 M2$=CHR$(M2+48)
660 D1$=CHR$(D1+48)
670 D2$=CHR$(D2+48)
680 REM *** CHANGE NEXT LINE TO CURRENT YEAR ***
690 PRINT M1$;M2$;"/";D1$;D2$;"/2006"
700 PRINT:PRINT 
710 X=X+1
720 GOTO 160
730 REM --------------------------
740 REM *** CURSOR CONTROL SUB. ***
750 REM --------------------------
760 REM
770 REM H=HORZ  V=VERTICAL
780 Y$=CHR$(V):X$=CHR$(H)
790 PRINT CHR$(27)+"["+Y$+";"+X$+"f";
840 RETURN