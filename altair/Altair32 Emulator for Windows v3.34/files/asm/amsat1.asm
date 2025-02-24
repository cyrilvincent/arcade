.TITLE "AMS80 - AMSAT STANDARD 8080 MONITOR V2.0"

;   THIS MONITOR IS A MINIMUM 8080 SYSTEM MONITOR
; FOR USE BY AMSAT MEMBERS. IT PROVIDES THE BASIC
; STRUCTURE NECESSARY FOR 8080 DEBUG AND ALSO A
; STANDARD BASE FOR AMSAT MEMBERS USING THE 8080.
;
;   THIS STANDARD BASE WILL ALLOW PROGRAMS
; TO BE USED BY ALL AMSAT MEMBERS AND AID IN THE
; TRANSMISSION OF PROGRAM MATERIALS VIA THE OSCAR
; SATELLITES.
;
;   THE ROUTINE ALLOWS FOR MEMORY EXAMINE AND MODIFY,
; USER INTERRUPT/RST VECTORS, AND VARIOUS
; TELETYPE SUPPORT ROUTINES TO LOAD AND DUMP MEMORY
; IN A STANDARD FORMAT ( SAME AS THE INTEL FORMAT ).

;
; DEFINE THE SYSTEM MEMORY PARAMETERS
;

ROM	= 0	;START OF READ-ONLY MEMORY
RAM	= 0C00h	;START OF READ-WRITE MEMORY
STACK =RAM+256	;TOP OF MONITOR STACK

;
; DEFINE TTY CONTROL CHARS
;
CR	= 	0Dh	;CARRIAGE RETURN
LF	= 	0Ah	;LINE FEED
RBO	= 	7Fh	;RUB-OUT
TOFF = 	14h	;TAPE OFF COMMAND
TON	= 	12h	;TAPE ON COMMAND
XOFF = 	13h	;PUNCH OFF COMMAND
XON	= 	11h	;PUNCH ON COMMAND 

;
; START OF SYSTEM
;

	.ORG 	ROM

EXEC:			; MAIN ENTRY INTO EXEC-80
	SHLD	SVHL	; SAVE HL
	JMP	BEGIN	; AND BEGIN
	.DW	ENDROM	;PAD BYTES ONLY

;
; DEFINE USER INTERRUPT/SUBROUTINE VECTORS
;

RS1:	PUSH 	H	;SAVE HL
	LHLD	RST1	; FETCH USER VECTOR
	XTHL		;PUT ONTO STACK RESTORING HL
	RET		; GO TO USER PROC
	.DW	0	;PAD

RS2:	PUSH 	H	;SAVE HL
	LHLD	RST2	; FETCH USER VECTOR
	XTHL		;PUT ONTO STACK RESTORING HL
	RET		; GO TO USER PROC
	.DW	0	;PAD

RS3:	PUSH 	H	;SAVE HL
	LHLD	RST3	; FETCH USER VECTOR
	XTHL		;PUT ONTO STACK RESTORING HL
	RET		; GO TO USER PROC
	.DW	0	;PAD

RS4:	PUSH 	H	;SAVE HL
	LHLD	RST4	; FETCH USER VECTOR
	XTHL		;PUT ONTO STACK RESTORING HL
	RET		; GO TO USER PROC
	.DW	0	;PAD

RS5:	PUSH 	H	;SAVE HL
	LHLD	RST5	; FETCH USER VECTOR
	XTHL		;PUT ONTO STACK RESTORING HL
	RET		; GO TO USER PROC
	.DW	0	;PAD

RS6:	PUSH 	H	;SAVE HL
	LHLD	RST6	; FETCH USER VECTOR
	XTHL		;PUT ONTO STACK RESTORING HL
	RET		; GO TO USER PROC
	.DW	0	;PAD

RS7:	PUSH 	H	;SAVE HL
	LHLD	RST7	; FETCH USER VECTOR
	XTHL		;PUT ONTO STACK RESTORING HL
	RET		; GO TO USER PROC
	.DW	0	;PAD


;
; MONITOR SUPPORT SUBROUTINE VECTORS
;
; USER UTILITY SUBROUTINES
;
;   THE FOLLOUING SET OF JUMPS ARE PROVIDED SO
; USER PROGRAMS CAN REFERENCE COMMON ENTRY POINTS
; TO THE VARIOUS ROUTINES.  THESE LOCATIONS WILL
; REMAIN CONSTANT WHILE THE ACTUAL LOCATION OF EACH
; ROUTINE MAY CHANGE FROM ONE REVISION LEVEL TO THE
; NEXT.
;
;  THE CALLING SEQUENCE FOR EACH SUBROUTINE
; REMAINS THE SAME AS DEFINED IN THE LISTING, WITH
; ONLY A SLIGHT EXECUTION TIME OVERHEAD FOR THE
; EXTRA JMP.

ITYPE:	JMP	TYPE	;TYPE A CHARACTER FROM 'A'
IGETCH:	JMP	GETCH	;GET CHAR TO A (NO ECHO)
ICHIN:	JMP	CHIN	;GET CHAR TO 'A' WITH ECHO
			; ( PARITY SET OFF )
IMSG:	JMP	MSG	;TYPE MSG, POINTER IN HL
			; ( MSG TERMINATED BY 0FFH )
ICRET:	JMP	CRET	;TYPE CR, LF, RUB-OUT
ISPACE:	JMP	SPACE	;TYPE A SPACE
ITHXN:	JMP	THXN	;TYPE B3-B0 OF 'A' IN HEX
			; ( ONE ASCII CHARACTER )
ITHXB: 	JMP	THXB	;TYPE 'A' IN ASCII-HEX 2 CH
ITHXW: 	JMP	THXW	;TYPE 'HL' IN ASCII-HEX 4 CH
IGHXN: 	JMP 	GHXN	;GET HEX NIBBLE TO B3-B0 'A'
IGHXB: 	JMP 	GHXB	;GET HEX BYTE FROM TTY1 - 'A'
IGHXW: 	JMP 	GHXW	;GET HEX WORD TO HL
ISTORE:	JMP 	STORE	;STORE A BYTE M,A WITH CHECK
INEGDE:	JMP 	NEGDE	;NEGATE THE DE REGISTER
IPWAIT:	JMP 	PWAIT	;TYPE 'PAUSE' AND WAIT FOR
			; ANY CHARACTER ON TTY1
IOK:	JMP	OKK	;TYPE	'OK?' AND WAIT FOR
			; SPACE IF OK. OTHERS WILL
			; PRINT ABORT MSG AND RETURN
			; TO MONITOR.
;
; BEGIN MONITOR
;
BEGIN:
	LXI	H,TMPA	;SET PSEUDO
	MVI 	M,0	; CARRY TO 0
	JNC 	$+5	; NO CARRY ON INPUT
	MVI 	M,1	;PSEUDO CY TO 1
	POP 	H	;POP CALL ADDRESS IF ANY
	SHLD 	SVPC	; AND SAVE PC
	LXI 	H,-2	;FETCH SP
	DAD 	SP	; ADJUSTING FOR POP
	SHLD 	SVSP	;SAVE USER STACK POINTER
	LXI 	SP,SVA+1	;SET SP FOR REGISTER SAVE
	PUSH 	PSW	;SAVE A,PSW
	PUSH 	B	;SAVE BC
	PUSH 	D	;SAVE DE
	LXI 	H,SVF	;POINT TO SAVED PSW
	MOV 	A,M	; AND FETCHIT
	ANI	0FEh	;ZERO CY
	MOV 	B,A	; AND SAVE
	LDA 	TMPA	;GET INPUT SAVED CY
	ORA 	B	; AND INSERT
	MOV	M,A	;RESTORE PSB WITH OK CY
	LXI 	SP,STACK	;SET SP TO EXEC STACK ARRAY
	LXI 	H,M0	;TYPE ENTRY
	CALL 	MSG	; MESSAGE

;
; NEXT MONITOR COMMAND
;

NEXT:	LXI 	SP,STACK	;RESTORE SP
	LXI	H,M1	;TYPE
	CALL	MSG	; PROMPTER
	CALL 	CHIN	;GET COMMAND CHAR
	MOV 	B,A	; AND SAVE COMMAND

;
; SEARCH OPERATION TABLE FOR COMMAND
;
	LXI	H,OPTAB	;FETCH TABLE VECTOR

SRCH:	MOV 	A,M	; GET TABLE COMMAND BYTE
	CPI 	-1	;CHECK FOR END OF TABLE
	JZ 	ILLEG	;MUST BE ILLEGAL INPUT
	CMP	B	;COMPARE TO INPUT
	JZ 	FNDCM	;FOUND COMMAND
	INX	H	;BUMP TO
	INX	H	; NEXT
	INX	H	;  COMMAND
	JMP	SRCH	;AND CONTINUE

;
; UNDEFINED COMMAND. TYPE ERROR MESSAGE
;

ILLEG:	LXI	H,M2	;UNDEFINED
	CALL	MSG	;  MESSAGE
	JMP	NEXT	;TRY AGAIN

;
; FOUND COMMAND, NOW FETCH ADDRESS AND EXECUTE COMMAND
;

FNDCM:	INX 	H	;BUMP TO LOW ADDRESS BITS
	MOV 	E,M	; AND FETCH IT
	INX 	H	;GET HIGH
	MOV 	D,M	; ADDRESS BYTE
	XCHG		;ADDRESS TO HL
	PCHL		;GOTO COMMAND PROCESSOR

;
; OPERATION DECODE/DISPATCH TABLE
;

OPTAB:	.DB	'A'	;COMMAND
	.DW 	GETAD	; TO GET ADDRESS

	.DB	CR	;COMMAND
	.DW	NEXT	; EFFECTIVE NOP

	.DB 	'.'	;COMMAND
	.DW	LOCAT	; TO EXAMINE CURRENT LOCATION

	.DB	LF	;COMMAND
	.DW	NXLOC	; TO EXAMINE NEXT LOCATION

	.DB 	'-'	;COMMAND
	.DW	LSTLC	; TO EXAMINE PREVIOUS LOCATION

	.DB	'D'	;COMMAND
	.DW	DUMP	; TO DUMP MEMORY AREA

	.DB	'F'	;COMMAND
	.DW	FILL	; TO FILL MEMORY

	.DB	'G'	;COMMAND
	.DW	GOTO	; TO GOTO MEMORY LOCATION

	.DB	'M'	;COMMAND
	.DW MOVE	; TO GOTO AREA OF MEMORY

	.DB	'X'	;COMMAND
	.DW	GETXA	; TO GET XEQ ADDRESS

	.DB	'J'	;COMMAND
	.DW	JUMP	; TO JUMP TO MEMORY LOCATION

	.DB	'R'	;COMMAND
	.DW	REGEX	; REGISTER EXAMINE

	.DB	'P'	;COMMAND
	.DW	PUNCH	; PUNCH MEMORY

	.DB	'E'	;COMMAND
	.DW 	PEND	; PUNCH END-OF-FILE

	.DB 	'L'	;COMMAND
	.DW 	LOAD	; LOAD MEMORY

	.DB 	'N'	;COMMAND
	.DW 	NULL	; PUNCH NULLS

	.DB	-1	;END OF TABLE CODE


;
; CHIN - ROUTINE TO INPUT ONE CHARACTER,
;        STRIP OFF PARITY, AND ECHO IF ABOVE
;        A SPACE (I.E., NOT CR, LF, ETC.)
;
; CALLING SEQUENCE ...
;
;        CALL CHIN		;CHARACTER IN
;        ... 		;RETURN AFTER ECHO STARTED
; 			;WITH CHAR .AND. 7FH IN 'A'
;


CHIN:	MVI 	A,-1	;SET ECHO
	STA 	ECHO	; FLAG ON
CHINN:	CALL 	GETCH	;GET CHARACTER
	ANI 	7FH	;STRIP PARITY
	PUSH 	PSW	;SAVE DATA
	LDA 	ECHO	; AND CHECK
	ANA 	A	;  ECHO FLAG
	JNZ 	$+5	;ECHO SET
	POP 	PSW	;ECHO NOT SET
	RET		; SO RETURN
	POP 	PSW	;RESTORE DATA AND ECHO
	CPI 	' '	;CHECK FOR CONTROL
	CNC 	TYPE	;TYPE IF >= SPACE
	RET		;RETURN

;
; MESSAGE PRINT ROUTINE
;
; CALLING SEQUENCE ...
;
;	LXA H,ADDRESS	;ADDRESS OF MESSAGE
;	CALL MSG		;CALL ROUTINE
;	...		;RETURN HERE AFTER LAST CHAR
;			; INITIATED. ALL REGISTERS
;			; PRESERVED
;

MSG:	PUSH 	PSW	;SAVE PSW
	PUSH 	H	;SAVE HL
MNXT:	MOV 	A,M	;GET A CHARACTER
	CPI 	-1	;CHECK FOR 377Q/0FFH/-1 TERMINATOR
	JZ 	MDONE	;FOUND THE TERMINATOR
	CALL 	TYPE	;TYPE THE CHARACTER
	INX	H	;DUMP MEM VECTOR
	JMP 	MNXT	; AND CONTINUE

MDONE:	POP	H	;RESTORE HL
	POP 	PSW	; AND PSW
	RET		;EXIT TO CALLER

;
; ROUTINE TO TYPE CR, LF, RBO
;
; CALLING SEQUENCE ...
;
;        CALL CRET	 
;        ... 		;RETURN HERE WITH ALL REGS PRESERVED
;

CRET:	PUSH 	H	;SAVE HL
	LXI 	H,CRMSG	;ADDRESS Of CRLFRBO MSG
	CALL 	MSG	;TYPE IT
	POP 	H	;RESTORE HL
	RET		; AND RETURN

CRMSG:	.DB CR,LF,RBO,-1


;
; ROUTINE TO TYPE ONE SPACE
;
; CALLING SEQUENCE ...
;
;        CALL SPACE 
;        ... 		;RETURN HERE WITH ALL REGS PRESERVED

SPACE:	PUSH 	PSW	;SAVE A,PSB
	MVI 	A,' '	;GET A SPACE
	CALL 	TYPE	; AND DO IT
	POP 	PSW	;RESTORE PSW
	RET		;AND RETURN

;
; ROUTINE TO TYPE VALUE ON 'A' IN HEX ON TTY
;
; CALLING SEQUENCE ...
;
;        LDA  DATA		;DATA BYTE IN 'A'
;        CALL THXB		;TYPE IN HEX
;        ... 		;RETURN HERE WITH ALL REGS PRESERVED
;

THXB:	PUSH 	PSW	;SAVE A,PSB
	RRC		;SHIFT
	RRC		; TO
	RRC		;  LEFT
	RRC		;   NIBBLE
	CALL 	THXN	;TYPE HEX NIBBLE
	POP 	PSW	;RESTORE DATA
	CALL 	THXN	;TYPE RIGHT NIBBLE
	RET		; AND EXIT

; ROUTINE TO TYPE ONE ASCII CHARACTER REPRESENTING
; BITS 3-0 OF 'A' IN HEX
;
; CALLING SEQUENCE ...
;
;        LDA  DATA		;DATA NIBBLE IN BITS 3-0
;        CALL THXN		;TYPE NIBBLE IN HEX 
;        ... 		;RETURN HERE WITH ALL REGS PRESERVED
;			; AND CONTENTS OF 'A' BITS ARE NOT
;			; SIGNIFNCANT AND IGNORED
;

THXN:	PUSH 	PSW	;SAVE PSW
	ANI 	0FH	;ISOLATE NIBBLE B3=>B0
	CPI 	10	;SEE IF > 9
	JC 	$+5	;NIBBLE <= 9
	ADI 	7	;ADJUST ALPHA CHARACTER
	ADI 	'0'	; ADD IN ASCII 0
	CALL 	TYPE	; AND TYPE THE NIBBLE
	POP 	PSW	;RESTORE PSW
	RET		; AND RETURN

;
; ROUTINE TO TYPE A WORD IN HEX
;
; CALLING SEQUENCE ...
;
;        LHLD WORD		;WORD IN HL
;        CALL THXW		;TYPE IT IN HEX 
;        ... 		;RETURN HERE WITH ALL REGS PRESERVED
;

THXW:	PUSH	PSW	;SAVE PSW
	MOV 	A,H	;GET HIGH BYTE
	CALL 	THXB	; AND TYPE IT
	MOV 	A,L	;GET LOW BYTE
	CALL 	THXB	; AND TYPE IT
	POP 	PSW	;RESTORE PSW
	RET		; AND RETURN

;
; ROUTINE TO GET ONE HEX CHARACTER FROM TTY
;
; CALLING SEQUENCE ...
;
;        CALL GHXN		;GET HEX NIBBLE 
;        JC   NONHX		;CY SET IF NON-HEX 
;        ... 		;HEX NIBBLE IN 'A'
;
; IF THE CHARACTER ENTERED IS 0 TO 9 OR A TO F
;  'A' WILL BE SET TO THE BINARY VALUE 0 TO 15
;  THE CARRY WILL BE RESET.
;
; IF THE CHARACTER ENTERED IS NOT A VALID HEX 
;   THEN THE 'A' REGISTER WILL CONTAIN THE ??
;   AND THE CARRY WILL BE SET TO A 1.
;
; ALL REGISTERS EXCEPT PSW PRESERVED
;

GHXN:	CALL	CHINN	;GET CHARACTER IN 
			;(CHINN IN CASE NOT ??
	CPI 	'0'	;RETURN IF
	RC		; < '0' 
	CPI 	':'	;SEE IF NUMERIC
	JC 	GHX1	;CHAR IS 0 TO 9
	CPI	'A'	;SEE IF A TO F
	RC		;CHAR ':' TO ' '
	CPI 	'G'	;SEE IF > 'F' 
	CMC		;INVERT CY SENSE
	RC		;CHAR > 'F'
	SUI 	7	;CHAR IS A TO F SO 
GHX1:	SUI	'0'	;ADJUST TO BINARY
	RET		; AND EXIT

;
; ROUTINE TO GET ONE HEX BYTE FROM TTY1
;
; CALLING SEQUENCE ...
;
;        CALL GHXB		;GET HEX BYTE
;        JC   NONHX		;SAME AS GHXN NON-HEX 
;        ... 		;HEX BYTE IN 'A'
;
; ALL REGS EXCEPT PSW PRESERVED, CY SET AS NEEDED
;

GHXB:	CALL	GHXN	;GET LEFT NIBBLE
	RC		;LEAVE IF NON-HEX
	PUSH 	B	;SAVE BC 
	RLC		; SHIFT
	RLC		;  TO
	RLC		;   LEFT
	RLC		;    NIBBLE
	MOV 	B,A	;AND SAVE IN B
	CALL 	GHXN	;GET RIGHT NIBBLE
	JC 	$+4	;JMP IF NON-HEX 
	ADD 	B	;ADD IN LEFT NIBBLE 
	POP 	B	;RESTORE BC 
	RET		;AND EXIT

;
; ROUTINE TO GET A HEX WORD FROM TTY1
;
; CALLING SEQUENCE ...
;
;        CALL GHXW		;GET HEX WORD TO HL 
;        JC   NONHX		;NON-HEX IF CY SET 
;        ... 		;OK, WORD IN HL
;
; IF INPUT VALUE IS VALID HEX THEN VALUE WILL BE IN HL
;   WITH ALL OTHER REGISTERS PRESERVED AND CY RST
;
; IF INPUT IS INVALID, HL WILL BE PARTIALLY MODIFIED
;   AND CY WILL BE SET AND 'A' WILL HAVE THE
;   ILLEGAL NON-HEX CHARACTER
;

GHXW:	STC		;SET AND
	CMC		; CLEAR CY
	PUSH 	PSW	;SAVE STATUS
	CALL 	GHXB	;GET HIGH HEX BYTE
	MOV 	H,A	; AND SET TO H
	JNC 	GHX2	;JMP IF VALID
	POP 	PSW	;RESTORE STATUS
	MOV 	A,H	;SET A TO BAD CHARACTER
	STC		;SET CY
	RET		; AND EXIT

GHX2:	CALL 	GHXB	;GET LOW HEX BYTE
	MOV 	L,A	; AND SET TO L
	JNC 	GHX3	;JMP IF VALID
	POP 	PSW	;INVALID. RESTORE STATUS
	MOV 	A,L	;SET A TO BAD CHAR
	STC		; SET CARRY
	RET		;  AND RETURN

GHX3:	POP	PSW	;ALL OK
	RET		; SO RET WITH HL SET TO WORD

;
; ROUTINE TO STORE A BYTE IN MEMORY WITH READ-BACK CHK
;
; CALLING SEQUENCE ...
;
;        ...		;ADDRESS IN HL
;        ...		;DATA IN 'A'
;        CALL STORE		;STORE THE BYTE 
;        ... 		;RETURN HERE IF OK. ALL REGS PRESERVED
;
; IF READ-BACK CHECK FAILS, AN APPROPRIATE ERROR
; MESSAGE WILL BE TYPED AND CONTROL RETURNED TO
; THE MONITOR.
;

STORE:	MOV 	M,A	;STORE THE BYTE
	CMP 	M	;READ-BACK CHECK
	RZ		;LEAVE IF OK
	PUSH	H	;ERROR, SAVE VECTOR
	LXI 	H,M4	;TYPE ERROR
	CALL 	MSG	; MESSAGE
	POP 	H	;RESTORE VECTOR
	CALL 	THXW	; AND TYPE ADDRESS
	JMP 	NEXT	;AND RETURN TO EXEC

;
; MEMORY EXAMINE/MODIFY ROUTINES
;
; THE FOLLOWING ROUTINES HANDLE MEMORY EXAMINES
; AND MODIFIES. THE ADDRESS OF THE MEMORY LOCATION
; CURRENTLY BEING ACCESSED IS IN 'ADR'. TO INITIALIZE
; 'ADR', THE MONITOR COMMAND 'A' IS USED.
;
;	** A	1234
;
; WILL SET THE 'ADR' TO THE VALUE 1234 (HEX)
;
; THE ROUTINE WILL THEM RETURN THE CARRIAGE.
; TYPE VALUE OF 'ADR' AND IT'S CONTENTS IN HEX.
; AND WAIT FOR ONE OF THE FOLLOWING INPUTS:
;
;	A VALID HEX BYTE TO REPLACE THE VALUE TYPED
;	 IN WHICH CASE THE ROUTINE WILL
;	'STORE' THE BYTE. INCREMENT 'ADR', AND
;	 Do THE NEXT ADDRESS.
;
;	A LINE-FEED WILL CAUSE THE NEXT ADDRWSS TO BE
;	 ACCESSED WITH-OUT MODIFYING THE CURRENT ONE
;
;	A CARRIAGE-RETURN WILL RETURN CONTROL TO THE
;	 KONITOR.
;
;	A MINUS SIGN WILL CAUSE THE 'ADR' TO BE
;	 DECREMENTED BY ONE.
;
;  THE LF AND '-' MAY BE ENTERED AS A
; MONITOR COMMAND ALSO AND WILL PERFORM THE SAME
; FUNCTION.
;
;  IN ADDITION, THE COMMAND '.' FROM THE
; MONITOR WILL CAUSE THE CONTENTS OF THE CURRENT
; 'ADR' TO BE TYPED AS IF THE COMMAND 'A' WITH
; 'ADR' HAD BEEN ENTERED.

GETAD:			;FROM COMMAND 'A'
	CALL	SPACE	;TYPE A SPACE
	CALL	GHXW	; AND GET 'ADR'
	JNC 	GTA1	;JMP IF VALID

ILLCH:	LXI 	H,M3	;ILLEGAL INPUT
	JMP 	ILLEG+3	; MESSAGE AND BACK TO
			;   MONITOR.
GTA1:	SHLD 	ADR	;SAVE 'ADR'

LOCAT:			; FROM COMMAND '.' ALSO
	CALL 	CRET	;RETURN CARRIAGE
	LHLD 	ADR	;FETCH 'ADDR'
	CALL 	THXW	; AND PRINT IT
	CALL 	SPACE	;SPACE
	MOV 	A,M	;FETCH CONTENTS
	CALL 	THXB	; AND TYPE
	CALL 	SPACE	;SPACE
	CALL 	GHXB	; AND GET DATA OR COMMAND
	JC 	NONHX	;NON-HEX INPUT
	CALL 	STORE	;STORE THE NEW VALUE
	MOV	A,M	; AND
	CALL	SPACE	;  ECHO
	CALL	THXB	;   VALUE

NXLOC:			;FROM COMMAND 'LF' ALSO
	LHLD 	ADR	;ACCESS
	INX 	H	; NEXT
	JMP 	GTA1	;AND CONTINUE

NONHX:	CPI 	CR	;IF CR
	JZ 	NEXT	; RETURN TO MONITOR
	CPI 	LF	;IF LF
	JZ 	NXLOC	; ACCESS NEXT 'ADR'
	CPI 	'-'	;IF - ACCESS LAST
	JNZ 	ILLCH	;NOT CR, LF, OR - SO ILLEGAL

LSTLC:			;FROM COMMAND '-' ALSO
	LHLD 	ADR	;DECREMENT 
	DCX 	H	; 'ADR'
	JMP 	GTA1	;AND CONTINUE


;
; ROUTINE TO NEGATE THE DE REGISTER
;
; CALLING SEQUENCE...
;
;	...		;VALUE IN DE
;	CALL	NEGDE	;NEGATE DE
;	...		;RETURN HERE WITH DE = -DE
;

NEGDE:	PUSH 	PSW	;SAVE PSW
	MOV 	A,D	;FETCH D
	CMA		;COMPLEMENT
	MOV 	D,A	;AND RESTORE
	MOV 	A,E	;FETCH E
	CMA		; COMPLEMENT
	MOV 	E,A	;  AND RESTORE
	INX 	D	;ADD ONE TO D
	POP 	PSW	;RESTORE PSW
	RET		;AND EXIT

;
; ROUTINE TO DUMP A BLOCK OF MEMORY TO TTY
;
;    THIS ROUTINE WILL DUMP A BLOCK OF MEMORY
; ON THE TTY, 16 BYTES PER LINE WITH THE ADDRESS
; AT THE START OF EACH LINE.
;
; THE FOLLOWING MONITOR COMMAND IS USED:
;
;	** D XXXX YYYY
;
; WILL CAUSE THE CONTENTS OF MEMORY LOCATIONS
; XXXX TO YYYY TO BE PRINTED. XXXX AND YYYY MUST
; BOTH BE VALID FOUR DIGIT HEX ADDRESSES AND IF
; XXXX >= YYYY ONLY LOCATION XXXX WILL BE PRINTED.
;
; AFTER THE FIRST LINE, ALL LINES WILL START WITH AN
; ADDRESS THAT IS AN EVEN MULTIPLE OF 16.
;
;


DUMP:			;FROM COMMAND 'D'
	CALL  	PU3	;GET HEX ADDRESS
	CALL  	PU3	;GET ANOTHER

;
; FROM ADDRESS IN HL, TO ADDRESS IN DE
;
	CALL  	NEGDE	;NEGATE DE FOR END CHECK

DMRET:	CALL  	CRET	;RETURN CARRIAGE
	CALL	THXW	;TYPE VECTOR ADDRESS
	CALL	SPACE
DMNXT:	CALL 	SPACE	;SPACE
	MOV 	A,M	;GET DATA
	CALL 	THXB	; AND DISPLAY
	CALL 	LAST	;CHECK FOR ALL DONE
	MOV 	A,L	;CHECK FOR MOD 16
	ANI 	15	; ADDRESS
	JZ 	DMRET	;NEW LINE IF MOD 16
	JMP 	DMNXT	; CONTINUE IF NOT

;
;   JUMP - ROUTINE TO TRANSFER CONTROL
;
;    THIS ROUTINE WILL ACCEPT AN ADDRESS FROM TTY
; AND THEN RESTORE ALL REGISTERS TO THE STATE AS
; SAVED IN RAM ON ENTRY TO THE MONITOR AND TRANSFER
; CONTROL TO THE ADDRESS ENTERED.
;
;	** J 1234
;
; JUMP TO LOCATION 1234H
;
;   IN ADDITION TWO OTHER MODES ARE POSSIBLE.
;
; THE COMMAND
;	** J (CR)
;
;  WILL CAUSE THE ADDRESS SAVED AS A RESULT OF
; A RST 0 TO BE USED FOR THE EXECUTION ADDRESS.
; INSERTING A RST 0 IN A PROGRAM AS A BREAKPOINT
; WILL CAUSE THE ENTIRE MACHINE STATE TO BE SAVED
; AND THE J (CH) WILL RETURN YOU TO THE POINT AFTER
; THE RST 0
;    OF COURSE, IF THE RST 0 REPLACED PART OF AN
; INSTRUCTION YOU MUST REPLACE THE RST 0 AND
; MODIFY THE ADDRESS WITH 'RP=' SO THAT YOU WILL GET
; BACK INTO THE PROGRAM AT THE PROPER PLACE.
;
;  ALSO
;
;  THE COMMAND
;	** J (LF)
;
;    WILL CAUSE THE ADDRESS ENTERED WITH THE 'X'
; COMMAND TO BE USED AS IF IT WERE TYPED IN.
;
;    THE CARRIAGE RETURN AND LINE FEED RESPONSES WILL
; CAUSE THE ADDRESS TO BE TYPED FOR VERIFICATION AND
; AFTER THE ADDRESS THE 'OK?' PROMPT WILL REQUIRE A
; SPACE REPLY FOR EXECUTION TO PROCEED. OTHERWISE
; THE OPERATION WILL BE ABORTED.
;
;

JUMP:			;COMMAND 'J'
	CALL	SPACE	;SPACE
	CALL 	GHXW	;GET ADDRESS
	JNC 	JMP3	;HEX ADDRESS ENTERED
	CPI 	CR	;SEE IF CR RESPONSE
	JNZ 	JMP1	; NO. GO CHECK FOR LF
	LHLD 	SVPC	;GET SAVED PC VALUE
	JMP 	JMP2	; AND SO PROCESS
JMP1:	CPI 	LF	;CHECK FOR LF RESPONSE
	JNZ 	ILLCH	; ALL OTHERS ILLEGAL
	LHLD 	XEQAD	;GET XEQ ADDRESS FROM 'X'
JMP2:	CALL 	THXW	;TYPE ADDRESS
JMP3:	CALL 	OKK	;OK?
	SHLD	GOGO+1	;SET UP FINAL JUMP
	MVI 	A,0C3H	;JMP COMMAND
	STA 	GOGO	; TO RAM
	LXI 	SP,SVE	;RESTORE REGS
	POP	D	; TO
	POP	B 	;  VALUES
	POP 	PSW	;   IN RAM
	LHLD 	SVSP	;SAVED SP
	SPHL		;SET NEW SP
	LHLD 	SVHL	;AND HL
	JMP 	GOGO	; AND EXECUTE

;
; CONSIAND 'G' - DIRECT GOTO ADDRESS
;
GOTO:	CALL	PU3	;GET HEX ADDRESS
	XCHG		; TO HL
	CALL 	OKK	;VFY
	PCHL		; THEN JMP ADR

;
; COKKAND 'X' - SET EXECUTION ADDRESS FOR 'J'
;
GETXA:	CALL 	PU3	;GET HEX ADDRESS
	XCHG		;TO HL
	SHLD 	XEQAD	;SAVE IT
	JMP 	NEXT	; AND BACK TO NEXT

;
; OKK - ROUTINE TO VERIFY OPERATION
;
; CALLING SEQUENCE...
;
;	CALL OKK		;VERIFY
;	...		;RETURN HERE IF SPACE
;			;ABORT IF NOT
;
; ALL REGISTERS PRESERVED
;

OKK:	PUSH 	PSW	;SAVE PSW
	PUSH 	H	; AND HL
	LXI 	H,M7	;ADR OF 'OK?' MSG
	CALL 	MSG	;PRINT IT
	LXI 	H,M8	;POSSIBLE ABORT
	CALL 	CHIN	;GET ANSWER
	CPI 	' '	; SPACE?
	JNZ 	ILLEG+3	;NO, GO ABORT
	POP 	H	;RESTORL HL
	POP 	PSW	; AND PSW
	RET		;  AND LEAVE

;
; ROUTINE TO CHECK FOR LAST OPERATION IN
; DUMP, FILL, MOVE, ETC.
;
LAST:	PUSH	H 	;SAVE MEM VECTOR
	DAD 	D	;  ADD NEGATIVE END ADDRESS
	JC 	NEXT	;DONE IF CARRY
	POP 	H	;RESTORE VECTOR
	INX 	H	;BUMP AND
	RET		; EXIT

;
; COMMAND 'M' - MOVE MEMORY BLOCK
;
; FORMAT
;	** M XXXX YYYY ZZZZ  OK?
;
;     WILL MOVE THE BLOCK OF MEMORY STARTING AT
; XXXX AND ENDING AT AND INCLUDING YYYY	TO TKE
; BLOCK STARTING AT ZZZZ.
;
;
; ***** THE FOLLOWING RESTRICTIONS APPLY! *****
;
;  EITHER	ZZZZ <= XXXX
;
;   OR	ZZZZ > YYYY
;
;   THE ROUTINE MOVES BYTES IN ASCENDING MEMORY ORDER
; SO IF THE HEX ADDRESS VALUES DO NOT SATISFY
; THE ABOVE RULES, MOVED DATA WILL OVERWRITE DATA TO
; BE MOVED.
;

MOVE:	CALL 	PU3	;GET XXXX
	PUSH 	D	;SAVE ON STACK
	CALL 	PU3	;GET YYYY TO DE
	CALL 	PU3	;GET ZZZZ TO DE, YYYY TO HL
	XCHG		;DE=Y, HL=Z, TOP=X
	XTHL		;DE=Y, TOP=Z, HL=X
	CALL 	NEGDE	;DE=-Y, TOP=Z, HL=X
	CALL 	OKK
MOV1:	MOV 	A,M	;GET THRU X
	XTHL		;HL=Z, TOP=X
	CALL 	STORE	;CHECKED STORE
	INX 	H	;BUMP Z
	XTHL		;RESTORE
	CALL 	LAST	;CHECK FOR END
	JMP 	MOV1	; AND CONTINUE

;
; COMMAND 'F' - FILL A BLOCK OF MEMORY WITH VALUE
;
;  FORMAT
;
;	** F XXXX YYYY VV OK?
;
;    WILL CAUSE MEMORY LOCATIONS XXXX THRU YYYY
; INCLUSIVE TO BE SET TO THE VALUE VV (HEX).
;

FILL:	CALL 	PU3	;DE=X
	CALL 	PU3	;DE=Y, HL=X
	CALL 	NEGDE	;DE=-Y
	CALL 	SPACE
	CALL 	GHXB	;GET VV -> 'A'
	JC	ILLCH	;MUST BE VALID HEX
	CALL 	OKK
FILL1:	CALL 	STORE	;STUFF IT
	CALL 	LAST	; CHECK IT
	JMP 	FILL1	;  AND CONTINUE IT

;
; REGISTER EXAMINE/MODIFY ROUTINE
;
;  THE MONITOR COMMAND 'R' FOLLOWED BY A SINGLE
; CHARACTER WILL CAUSE THE ENTRY SAVED
; CONTENTS OF THAT REGISTER TO BE PRINTED AND A
; MODIFICATION ACCEPTED. IF THE 'R' IS FOLLOWED BY
; A CR THEN ALL OF THE REGISTERS WILL BE PRINTED.
;
; RA - ACC
; RF - FLAGS, PSB
; RB - B
; RC - C
; RD - D
; RE - I
; RH - H
; RL - L
; RS - SP
; RP - PROGRAM COUNTER IF MONITOR 'CALLED'
;
; R(CR) - PRINT ALL REGISTERS
;
; REGISTERS S AND P WILL BE PRINTED AS 4 HEX DIGITS
; AND MODIFICATIONS TO THEM MUST BE 4 DIGITS ALSO.
;

RXLST:	.DB "AFBCDEHL",0	;REGISTER LIST

REGEX:			; FROM COMMAND 'R'
	CALL 	CHIN	;GET REGISTER TO
	CPI 	CR	;CHECK FOR CR
	JZ 	REXAL	;DO ALL IF CR
	PUSH 	PSW	;SAVE ID
	MVI 	A,'='	;TYPE
	CALL 	TYPE	; =
	POP 	PSW	;RESTORE ID
	LXI 	D,SVPC	;ADDRESS OF PC
	CPI 	'P'	;SEE IF
	JZ 	RX2	;PRINT PC
	INX 	D	;POINT TO
	INX 	D	; SP
	CPI 	'S'	;CHECK S
	JZ 	RX2	; DO SP
	MOV 	B,A	;SAVE ID
	LXI 	H,RXLST	;LIST VECTOR
	LXI 	D,SVA	;ADDRESS OF 'A' STORAGE
RX0:	MOV 	A,M	;GET TABLE ID
	ANA 	A	;CHECK FOR END
	JZ 	ILLCH	;NOT IN TABLE

	CMP 	B	;CHECK INPUT ID
	JZ 	RX1	;FOUND IT
	INX 	H	;NEXT TBL
	DCX 	D	;NEXT REG
	JMP 	RX0	;CONTINUE

RX1:	LDAX 	D	;GET THE RGE
	CALL 	THXB	; AND PRINT IT
	CALL 	SPACE	;SPACE
	CALL 	GHXB	;AND WAIT FOR REQUEST
	JC 	RX1A	;NON-HEX SO SEE IF CH
	STAX 	D	;STORE INPUT IN RG
	JMP 	NEXT	;AND BACK TO MONITOR
RX1A:	CPI 	CR	;CR OK
	JZ 	NEXT	;BACX TO MON
	JMP 	ILLCH	;OTHERS ILLEGAL

RX2:	XCHG		;RD ADR TO XL
	MOV	E,M	;GET LOW S OR P
	INX 	H	;BUMP VECTOR
	MOV 	D,M	;GET HIGH S OR P
	XCHG		;RG VAL TO HL
	CALL 	THXW	;TYPE WORD
	CALL 	SPACE	;SPACE
	CALL 	GHXW	;AND GET REQUEST
	JC 	RX1A	;IF NON-HEX
	XCHG		;RESTORE RAM VECTOR FOR RG
	MOV 	M,D	;STORE HIGH S OR P
	DCX 	H	;BUMP VECTOR DOWN
	MOV 	M,E	;STORE LOW S OR P
	JMP 	NEXT	;BACK TO MON

RXTSE:	CALL 	SPACE	;SPACE
	CALL 	TYPE	; TYPE ID
	MVI 	A,'='	;  THEN
	CALL 	TYPE	;   =
	RET		; AND RETURN


REXAL:	CALL	CRET	;RETURN CARRIAGE FOR ALL REGS
	LXI 	D,SVA	;ADDRESS OF 'A'
	LXI 	H,RXLST	;ID LIST
RXA1:	MOV 	A,M	;GET ID
	ANA 	A	;CHECK FOR LAST
	JZ 	RXA2	;DONE SINGLES
	CALL 	RXTSE	;TYPE SPACE, ID, AND =
	LDAX 	D	;GET REG
	DCX 	D	;DUMP RG PNTR
	INX 	H	; AND LIST PNTR
	CALL	THXB	;TYPE REGISTER
	JMP 	RXA1	; AND CONTINUE

RXA2:	MVI 	A,'P'	;DO PC
	CALL	RXTSE	;SP, ID, =
	LHLD	SVPC	;GET PC
	CALL	THXW	; AND PRINT
	MVI	A,'S'	; DO SP
	CALL	RXTSE	;SP,ID,=
	LHLD 	SVSP	;GET SP
	CALL	THXW	;AND PRINT
	JMP	NEXT	;BACK TO MON

PU3:	CALL	SPACE	;SPACE
	CALL	GHXW	;GET HEX WORD
	JC	ILLCH	;IF BAD
	XCHG		;SAVE TO DE
	RET		;AND RETURN

;
;
; ROUTINES TO PUNCH OR LOAD MEMORY ON TTY
;
; THESE ROUTINES WORK WITH DATA IN THE INTEL
; BINARY FORMAT. THE FORMAT CONSISTS OF A RECORD
; HEADER, UP TO 16 BYTES OF DATA, AND
; A RECORD CHECKSUM.
;
; RECORD FORMAT
;
; HEADER CHARACTER ':'
; HEX-ASCII BYTE COUNT, TWO CHARACTERS
; HEX-ASCII LOAD ADDRESS, FOUR CHARACTERS HHLL
; HEX-ASCII RECORD TYPE, TWO CHARACTERS 00 FOR DATA
;				01 FOR EOF
; DATA BYTES IN HEX-ASCII, TWO CHARACTERS EACH
;
; HEX-ASCII CHECKSUM, TWO CHARACTERS
;
; THE CHECKSUM IS CALCULATED SUCH THAT THE
; SUM OF ALL OF THE TWO CHARACTER BYTE FIELDS
; WILL BE ZERO.
;
;  THE EOF RECORD MAY CONTAIN AN EXECUTION ADDRESS
; IN THE LOAD ADDRESS FIELD. THE LOAD ROUTINE WILL
; TRANSFER CONTROL TO THIS ADDRESS AFTER READING THE
; TAPE IF THE ADDRESS IS NON-ZERO.
;

PUNCH:			;COMMAND 'P'
	CALL	PU3	;GET FROM ADDRESS
	CALL	PU3	;GET TO ADDRESS
	CALL	PWAIT	;TYPE PROMPT AND WRITE
	MVI	A,XON	;START
	CALL	TYPE	; THE PUNCH
;
; HL HAS LOW ADDRESS, DE HAS HIGH ADDRESS
;
PN0:	MOV	A,L
	ADI	16
	MOV	C,A
	MOV	A,H
	ACI	0
	MOV	B,A
	MOV	A,E
	SUB	C
	MOV	C,A
	MOV	A,D
	SBB	B
	JC	PN1	;RCD LENGTH	16
	MVI	A,16
	JMP	PN2
PN1	MOV	A,C	;LAST RECORD
	ADI	17
PN2:	ORA	A
	JZ	PDONE
	PUSH	D	;SAVE HIGH
	MOV	E,A	;E=LENGTH
	MVI	D,0	;CLREAR CHECKSUM
	CALL	CRET	;PUNCH CR,LF,RBO
	MVI 	A,':'	;PUNCH HDR
	CALL 	TYPE
	MOV 	A,E
	CALL 	PBYTE	;PUNCH LENGTH
	MOV 	A,H
	CALL 	PBYTE
	MOV 	A,L
	CALL 	PBYTE
	XRA 	A
	CALL 	PBYTE	;PUNCH RECORD TYPE
PN3:	MOV 	A,M	;GET DATA
	INX 	H
	CALL 	PBYTE
	DCR 	E	;DECR CNT
	JNZ 	PN3	;CONTINUE
	XRA 	A	;CALCULATE
	SUB 	D	; CHECKSUM
	CALL 	PBYTE	;AND PUNCH IT
	POP 	D	;RESTORE HIGH ADDRESS
	JMP 	PN0	;AND CONTINUE

PBYTE:	CALL 	THXB
	ADD 	D	;ADD TO SUM
	MOV 	D,A
	RET

PDONE:	CALL 	CRET
	MVI 	A,XOFF	;PUNCH
	CALL 	TYPE	; OFF
	CALL	GETCH	;WAIT FOR GO-AHEAD
	JMP 	NEXT	;BACK TO MON

;
; ROUTINE TO TYPE 'PAUSE' MESSAGE
; AND WAIT FOR TTY1 GO-AHEAD
;

PWAIT:	PUSH	H	;SAVE H
	LXI 	H,M5	;PROMPT
	CALL 	MSG	; MESSAGE
	POP	H
	CALL	GETCH	;WAIT FOR GO-AHEAD
	RET		; AND THEN LEAVE

;
; ROUTINE TO PUNCH EOF RECORD
;

PEND:	CALL	SPACE
	CALL	GHXW	;GET ADDRESS OR CR
	JNC	PEND1	; ADDRESS
	LXI	H,0	;SET 0 ADDRESS
	CPI	CR	;CHECK FOR CR REPLY
	JNZ	ILLCH	; OTHERS ILLEGAL
PEND1:	CALL	PWAIT	;PROMPT PAUSE
	MVI	A,XON	;PUNCH
	CALL	TYPE	; ON
	CALL	CRET	;CR,LF,RBO
	MVI	A,':'
	CALL	TYPE	;TYPE HDR :
	XRA	A
	MOV	D,A	;ZERO CHECKSUM
	CALL	PBYTE	;AND OUTPUT ZERO LINE
	MOV	A,H
	CALL	PBYTE	;EXECUTION
	MOV	A,L
	CALL	PBYTE	; ADDRESS
	MVI	A,1	;RCD TYPE
	CALL	PBYTE
	XRA	A
	SUB	D	;CALCULATE CHECKSUM
	CALL	PBYTE	; AND PUNCH IT
;
; PUNCH NULLS
;

NULLS:	MVI	C,100	; 100 NULLS
	XRA	A
	CALL	TYPE
	DCR	C
	JNZ	$-4	;CONTINUE
	JMP	PDONE	;DONE

NULL:			; COMMAND 'N'
	CALL	PWAIT	;PROMPT PAUSE
	MVI	A,XON	;PUNCH
	CALL	TYPE	;  ON
	JMP	NULLS	;GO DO IT

;
; ROUTINE TO LOAD HEX-ASCII TAPE
;
LOAD:			;COMMAND 'L'
	CALL	SPACE
	CALL	GHXW	;GET bDIAS OR CR
	JNC	LDQ	;BIAS ADRESS ENTERED
	LXI	H,0	;BIAS 0
	CPI	CR	;CHECK FOR CR
	JNZ	ILLCH	;OTHERS N.G.
LDQ:	PUSH	H	;SAVE BIAS
	XRA	A	;KILL
	STA	ECHO	; TTY0 ECHO
	MVI	A,TON	;TAPE
	CALL	TYPE	; ON
LD0:	POP	H	;GET BIAS
	PUSH	H	;AND RESTORE
	CALL	RIX	;GET INPUT
	MVI 	B,':'
	SUB	B	;CHECK FOR RCD MARK
	JNZ	LD0
	MOV 	D,A	;CLEAR CHECKSUM
	CALL	BYTE	;GET LENGTH
	JZ	LD2	;ZERO ALL DONE
	MOV	E,A	;SAVE LENGTH
	CALL	BYTE	;GET HIGH ADDRESS
	PUSH	PSW	; AND SAVE
	CALL	BYTE	;GET LOW ADDRESS
	POP 	B	;FETCH MSBYTE
	MOV 	C,A	;BC HAS ADDRESS
	PUSH 	B	;SAVE VECT
	XTHL		; TO HL
	SHLD 	BLKAD	;SAVE BLOCK ADDRESS
	XTHL		; IN CASE OF ERROR
	POP 	B	;RESTORE
	DAD 	B	;ADD TO BIAS
	CALL 	BYTE	;GET TYPE
LD1:	CALL 	BYTE	;GET DATA
	CALL 	STORE	;AND STORE IT
	INX	H
	DCR	E
	JNZ 	LD1	;CONTINUE
	CALL 	BYTE	;GET CHECKSUM
	JZ 	LD0	;CONTINUE
	LXI 	H,M6	;CHEKSUM ERROR
	CALL	MSG	; MSG
	LHLD 	BLKAD	;ADDRESS OF THIS BLOCK
	CALL	THXW	; FOR REFERENCE
	JMP	NEXT	;AND EXIT

LD2:	CALL	BYTE	;GET MSB OF XEQAD
	MOV 	H,A
	CALL	BYTE
	MOV 	L,A
	ORA 	H
	MVI 	A,TOFF	;TAPE RDR
	CALL	TYPE	; OFF
	JZ 	NEXT	;MON IF NO XEQAD
	PCHL		;GO TO ROUTINE

RIX:	CALL 	GETCH
	ANI 	7FH
	RET

BYTE:	CALL 	GHXB	;GET TWO CHARS
	MOV	C,A
	ADD 	D
	MOV 	D,A
	MOV	A,C
	RET

;$$$$$$
;
; SYSTEM MESSAGES
;

M0:	.DB	CR,LF,LF,"AMS80 V2.0",LF,-1
M1:	.DB	CR,LF,RBO,"** ".-1
M2:	.DB	" IS UNDEFINED",-1
M3:	.DB	" ??", -1
M4:	.DB	TOFF,CR,LF,RBO,"MEM WRITE ERROR AT ",-1
M5:	.DB	" PAUSE ",-1
M6:	.DB	TOFF," CHKSM ERR, BLOCK ",-1
M7:	.DB	"  OK? ",-1
M8:	.DB 	" ABORTED!",-1

;
; SYSTEM I/O ROUTINES
;
;USER IS TO PATCH HIS OWN TELETYPE
;ROUTINES HERE
;

;
; ROUTINE TO TYPE A CHARACTER
;
; CALLING SEQUENCE
;	LDA	CHAR	;CHARACTER IN 'A' REGISTER
;	CALL	TYPE	;TYPE IT
;	.....		;RETURN HERE

TYPE:	PUSH	PSW	;SAVE CONTENTS OF 'A'
	IN	1	;INPUT TTY STATUS
	ANI	4	;TEST FOR BUSY
	JNZ	TYPE+1	;IF BUSY, KEEP TRYING
	POP	PSW	;RETRIEVE THE DATA
	PUSH	PSW	;AND SAVE IT AGAIN
	CMA		;PREPARE THE DATA
	OUT	0	;OUTPUT IT
	POP	PSW	;RESTORE 'A'
	RET
;THIS ROUTINE WORKS IN MY SYSTEM
;BUT MAY NOT WORK IN YOURS

;
; ROUTINE TO GET A CHARACTER FROM THE TTY
;
; CALLING SEQUENCE
;
;	CALL	GETCH	; GET CHARACTER
;	.....		; RETURN HERE WITH CHARACTER
;			; IN 'A'
;
; ALL REGISTERS PRESERVED EXCEPT 'A' WHICH
; CONTAINS THE INPUT CHARACTER

GETCH:	IN	1	;INPUT TTY STATUS
	ANI	1	;TEST FOR READY
	JNZ	GETCH	;KEEP TRYING IF NOT READY
	IN	0	;GET THE CHARACTER
	CMA		;PROCESS IT
	RET

;THIS ROUTINE WORKS IN MY SYSTEM BUT MAY NOT
;WORK IN YOURS

ENDROM 	=$	;BOUNDARY MARKER

;
; SYSTEM RAM AREA DEFINITIONS
;

.ORG RAM

;
; USER RESTART VECTORS 1 - 7
;
RST1:	.DW 0
RST2:	.DW 0
RST3:	.DW 0
RST4:	.DW 0
RST5:	.DW 0
RST6:	.DW 0
RST7:	.DW 0

;
; MONITOR REGISTER SAVE AREA
;
SVPC:
SVPCL:	.DB	0 ;SAVED PC LOW
SVPCH:	.DB	0 ;SAVED PC HIGH

SVSP:
SVSPL:	.DB	0 ;SAVED SP LOW
SVSPH:	.DB	0 ;SAVED SP HIGH

SVHL:
SVL:	.DB	0 ;SAVED L
SVH:	.DB	0 ;SAVED H

SVE:	.DB	0 ;SAVED E
SVD:	.DB	0 ;SAVED D
SVC:	.DB	0 ;SAVED C
SVB:	.DB	0 ;SAVED B
SVF:	.DB	0 ;SAVED PSB, FLAGS
SVA:	.DB	0 ;SAVED ACC

ECHO:	.DW 	1	;CHIN ECHO FLAG, <>0=ECHO
			;=0 = NO ECHO

ADR:	.DW	2	;EXAMINE/MODIFY ADDRESS

TMPA:			;TEMP STORAGE LOCATIONS
GOGO:	.DW	3	;'JUMP' STORAGE
XEQAD:	.DW 	2	;'X' EXECUTION ADDRESS
BLKAD:	.DW 	2	;'L' BLOCK ADDRESS
	NOP		;PROGRAM BOUNDARY MARKER

.END
