100 REM *** B L A C K J A C K ***
101 WIDTH 80
110 DIM D(208),H(16),O(16),P(16,11),Q(11),S(16),X(16)
120 PRINT:PRINT"WELCOME TO THE CASINO"
130 PRINT "WE PLAY VEGAS STYLE BLACKJACK"
140 PRINT:INPUT"INSTRUCTIONS? (YES-NO) ";M$: IF M$="NO" THEN GOTO 160
150 IF M$="YES" THEN GOSUB 1640:GOTO 160 ELSE GOTO 140
160 R=16:PRINT"HOW MANY DECKS (1-4)";
170 INPUTN:IFN<1ORN>4THENPRINT"1 TO 4 DECKS ONLY. REENTER";:GOTO170
180 E=N*52:GOSUB870:B=1:GOSUB890:A=1
190 PRINT:G=1
200 INPUT"BET PLEASE";U:IF U>0 THENGOTO220 ELSE IF U=0 THEN GOTO1600
210 B=1:GOSUB 890:GOTO 200
220 IF U<=500 THEN GOTO240 ELSEPRINT"SORRY, THE HOUSE LIMIT IS $500!"
230 GOTO 200
240 GOSUB930:H(1)=U:N=Q(2):PRINT:PRINT"MY UP CARD";:GOSUB1050:N=P(R,1)
250 PRINT : PRINT"YOUR 1ST CARD";:GOSUB1050:PRINT"YOUR 2ND CARD";:N=P(R,2)
260 GOSUB 1050
270 GOSUB1170:IFM<>11THEN GOTO 280 ELSE GOSUB 1550
280 IF W<>21 THEN GOTO 320 ELSE PRINT : PRINT"I HAVE BLACKJACK, ";
290 IF X(1)<>21 THEN GOTO 310 ELSE PRINT"SO DO YOU, WE PUSH"
300 GOSUB 1510:GOTO 190
310 PRINT"YOU LOSE":V=V-U:GOTO300
320 IF X(1)<>21 THEN GOTO340 ELSE PRINT"YOU HAVE BLACKJACK, YOU WIN!"
330 V=V+3*U/2:GOTO300
340 PRINT:PRINT"PLAY ";:IF R=1 THEN GOTO 350 ELSE PRINT"FOR HAND";G;
350 PRINT:PRINT"YOUR TOTAL IS";X(G);:INPUT F:IF F>-1 THEN GOTO 370
360 PRINT"ONLY 0-3 IS VALID, REENTER";:GOTO350
370 IF F>3 THEN GOTO 360 ELSE IF F<>1 THEN GOTO 550
380 REM ******** PLAYER HIT ROUTINE *************
390 IF A<=E THEN GOTO 400 ELSE GOSUB 1220
400 M=S(G):M=M+1:S(G)=M:N=D(A):P(G,M)=N:PRINT"YOUR CARD IS";:GOSUB 1050
410 GOSUB 1010:A=A+1:IF N<>11 THEN GOTO 420 ELSE O(G)=O(G)+1
420 X(G)=X(G)+N
430 IF X(G)<22 THEN GOTO 340 ELSE IF O(G)=0 THEN 450
440 O(G)=O(G)-1:X(G)=X(G)-10:GOTO 430
450 PRINT:PRINT"YOU BUSTED WITH";X(G):X(G)=0:Y=Y-1:PRINT
460 REM ********* CHECK FOR END OF PLAY ************
470 IF G<R GOTO 500
480 GOSUB 1250
490 GOTO190
500 G=G+1
510 N=P(G,1)
520 PRINT "YOUR 1ST CARD FOR HAND ";G;" WAS";
530 GOSUB 1050
540 GOTO 340
550 IF F<>0 GOTO 620
560 REM *********PLAYER STAND ALONE ROUTINE ************
570 IF X(G)<22 GOTO 470
580 IF O(G)=0 GOTO 450
590 X(G)=X(G)-10
600 O(G)=O(G)-1
610 G=G+1
620 IF F<>2 GOTO 730
630 IF S(G)=2 GOTO 670
640 PRINT "DOUBLE ON 1ST 2 CARDS ONLY"
650 GOTO 340
660 REM ***** DOUBLE DOWN ROUTINE **********
670 IF A<=E THEN GOTO 680 ELSE 1220
680 H(G)=2*U:N=D(A):P(G,3)=N:A=A+1:PRINT "YOU DRAW THE";:GOSUB 1050
690 GOSUB 1010:IF N=11 THEN O(G)=O(G)+1
700 X(G)=X(G)+N
710 IF X(G)<22 THEN GOTO 470
720 IF O(G)=0 THEN GOTO 450 ELSE O(G)=O(G)-1:X(G)=X(G)-10:GO1350
730 N=P(G,1):Y=Y+1:GOSUB 1010:M=N:N=P(G,2):GOSUB1010:IFM=NTHENGOTO760
740 PRINT "YOU MAY ONLY SPLIT PAIRS": GOTO 340
750 REM *********PAIR SPLIT ROUTINE **********
760 R=R+1:Y=Y+1:P(R,1)=P(G,2):S(G)=1:S(R)=1:X(G)=X(G)/2:X(R)=X(G)
770 H(R)=U:IF N<>11 THEN GOTO 340
780 REM **********ACES WERE SPLIT - 1 CARD EACH *********
790 IF A>E THEN GOSUB 1220
800 N=D(A):P(G,2)=N:PRINT "1ST ACE GETS A";:GOSUB 1050: GOSUB 1010
810 IF N=11 THEN N=1
820 X(G)=X(G)+N:A=A+1:IF A>E THEN GOSUB 1220
830 N=D(A):P(R,2)=N:PRINT "2ND ACE GETS A";:GOSUB 1050:GOSUB 1010
840 IF N=11 THEN N=1
850 X(R)=X(R)+N:A=A+1:GOTO480
860 REM ************ BUILD 1 TO 4 DECKS ************
870 FOR I=1 TO N: J=(I-1)*52: FOR K =1 TO 52: D(J+K)=K:NEXT K,I:RETURN
880 REM *********SHUFFLE THE CARDS ***********
890 PRINTCHR$(26):PRINT "I'M SHUFFLING.... ":FOR I=B TO E
900 C=RND(1)*E:IF C<B GOTO 900 ELSE L=D(I):D(I)=D(C):D(C)=L:NEXTI
910 A=B:RETURN
920 REM ******** DEAL THE CARDS ***********
930 FOR I=1 TO 11:Q(I)=0:FOR J=1 TO R: P(J,I)=0:NEXT J,I:R=1:Y=1
940 IF A+4>E THEN B=1:GOSUB 890
950 PRINT "DEALING":P(R,1)=D(A):Q(1)=D(A+1):P(R,2)=D(A+2):Q(2)=D(A+3)
960 A=A+4:T=2:S(1)=2:GOSUB980:M=N:RETURN
970 REM ********** COMPUTE THE VALUE OF THE DEALERS HAND *********
980 Z=0:W=0:FOR I=1 TO 2:N=Q(I):GOSUB 1010:IF N=11 THEN Z=Z+1
990 W=W+N:NEXT I :RETURN
1000 REM **********COMPUTE THE VALUE OF A CARD **********:
1010 IF N<14 THEN GOTO 1020 ELSE N=N-13:GOTO 1010
1020 IF N=1 THEN N=11:RETURN ELSE GOTO 1030
1030 IF N<11 THEN RETURN ELSE N=10:RETURN
1040 **********PRINT A CARD **********
1050 I=0
1060 IF N>=14 THEN N=N-13:I=I+1:GOTO1060
1070 IF N=1 THEN PRINT TAB(17);"ACE ";:GOTO1130
1080 IF N<10 THEN PRINT TAB(18);N;:GOTO1130
1090 IF N<11 THEN PRINT TAB(17);N;:GOTO 1130
1100 IF N<12 THEN PRINT TAB(16);"JACK ";:GOTO1130
1110 IF N<13 THEN PRINT TAB(15);"QUEEN ";:GOTO 1130
1120 PRINT TAB(16);"KING ";
1130 PRINT "OF ";:IF I=0 THEN PRINT "SPADES":RETURN
1140 IF I=1 THEN PRINT "HEARTS":RETURN
1150 IF I=2 THEN PRINT "DIAMONDS":RETURN ELSE PRINT "CLUBS":RETURN
1160 REM ********* COMPUTE VALUE OF PLAYERS HAND *********:
1170 O(G)=0:X(G)=0:FOR I =1 TO 2: N=P(G,I):GOSUB 1010:X(G)=X(G)+N
1180 IF N<>11 THEN GOTO 1200
1190 O(G)=O(G)+1
1200 NEXT I:RETURN
1210 REM *********SAVE THE CARDS THAT ARE ALREADY DEALT AND SHUFFLE**
1220 K=T:FOR I=1 TO R:K=K+S(I):NEXT I
1230 FOR I=1TOK:A=A-1:J=D(I):D(I)=D(A):D(A)=J:NEXTI:B=K+1:GOSUB890:RETURN
1240 REM *******DEALERS LOGIC **********:
1250 N=Q(1):PRINT "MY HOLE CARD";:GOSUB 1050:IF Y=0 THEN GOTO 1390
1260 IF W<17 THEN GOTO 1300
1270 IF W>17 THEN GOTO 1340
1280 IF Z=0 THEN GOTO 1380
1290 W=W-10:Z=Z-1
1300 IF A>E THEN GOSUB 1220
1310 N=D(A):T=T+1:A=A+1:PRINT:PRINT "I DRAW THE";:GOSUB1050:GOSUB1010
1320 IF N=11 THEN Z=Z+1
1330 W=W+N:GOTO 1260
1340 IF W<22 THEN GOTO 1380
1350 IF Z=0 THEN GOTO 1370
1360 Z=Z-1:W=W-10:GOTO1260
1370 PRINT "I BUSTED ";
1380 PRINT "MY TOTAL IS ";W
1390 FOR I =1 TO R:PRINT "YOU ";:IF X(I)<>0 THEN GOTO 1410
1400 PRINT "LOST ";:V=V-H(I):GOTO 1460
1410 IF W<22 THEN GOTO 1430
1420 PRINT "WON ";:V=V+H(I):GOTO 1460
1430 IF W<>X(I) THEN GOTO 1450
1440 PRINT "PUSHED ON ";:GOTO1460
1450 IF W<X(I) THEN GOTO 1420 ELSE GOTO 1400
1460 IF R<>1 THEN GOTO 1470 ELSE PRINT "THE HAND":GOTO 1480
1470 PRINT "HAND ";I
1480 NEXT I
1490 REM ********* PRINT THE PLAYERS WON/LOST STANDING *******
1500 PRINT
1510 PRINT "YOU'RE ";:IF V=0 THEN PRINT "EVEN":RETURN
1520 IF V<0 THEN PRINT "BEHIND $"V:RETURN ELSE PRINT "AHEAD $";V:RETURN
1530 PRINT "AHEAD $";V
1540 REM ********INSURANCE ROUTINE ************
1550 INPUT "INSURANCE (YES-NO)";M$:IF M$="NO" THEN RETURN
1560 IF M$<>"YES" THEN GOTO 1550
1570 PRINT "YOUR INSURANCE BET ";:IF W=21 THEN PRINT "WINS":V=V+U:RETURN
1580 PRINT "LOSES":V=V-U/2:RETURN
1590 REM ******END OF GAME WRAP UP **************
1600 PRINT "THANKS FOR PLAYING":PRINT "HOPE YOU ENJOYED YOURSELF"
1610 PRINT "HERE'S YOUR FINAL STANDING!":GOSUB 1510
1620 IFV>0THENPRINT"NOW, JUST YOU TRY TO COLLECT !!":END
1630 IF V=0THENPRINT"BIG DEAL......":END ELSEPRINT"PAY UP, OR ELSE":END
1640 REM ******** INSTRUCTIONS ***********
1650 PRINT:PRINT"THE DEALER STANDS ON 17 OR MORE"
1660 PRINT"BUT WILL HIT A SOFT 17."
1670 PRINT"YOU MAY SPLIT ANY PAIR.":PRINT"YOU MAY DOUBLE THE 1ST 2 CARDS"
1680 PRINT"AND GET ONLY 1 MORE CARD.":PRINT:PRINT"PLAY CODES:"
1690 PRINT "  0 - STAND":PRINT "  1 - HIT":PRINT "  2 - DOUBLE DOWN"
1700 PRINT "  3 - SPLIT A PAIR":PRINT:PRINT "A ZERO BET ENDS THE GAME"
1710 PRINT "A NEGATIVE BET FORCES A SHUFFLE"
1720 PRINT "GOOD LUCK - LET'S START":RETURN
T:PRINT "A ZERO BET ENDS THE GAME"
1710 PRINT "A NEGATIVE BET FORCES A SHUFFLE"
1720 PRINT "GOOD LUC