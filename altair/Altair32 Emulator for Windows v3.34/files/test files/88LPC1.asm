;
; MITS 88-LPC PRINTER TEST
;
; SCOTT LaBOMBARD
; 6/26/04
;
;
; THIS TEST PRINTS ONE COMPLETE LINE OF EACH OF THE
; 64 POSSIBLE CHARACTERS THAT CAN BE PRINTED (THIS
; PRINTER HANDLES 6 BIT ASCII WORDS FOR DATA)
;
; OPERATIONAL NOTES:
;
; * 88-LPR PRINTER HANDLES 80 CHARACTERS PER LINE
;
; * PRINTER AUTOMATICALLY DOES CR/LF AFTER CHAR 80
;
; * THE PRINTER BUFFER IS 80 CHARACTERS
; 
; * A PRINT COMMAND IS ISSUED AUTOMATICALLY WHEN
;   THE 80 CHARACTER BUFFER IS FULL BY THE 88-LPC
;   BOARD ...SPECIFICALLY, UNLESS THE USER SENDS
;   A PRINT COMMAND NO CHARACTERS WILL BE PRINTED
;   UNTIL THE BUFFER IS FULL
;
; * IF THE USER SENDS A PRINT COMMNAD, AND IF THE
;   BUFFER IS NOT FULL, THE CURRENT BUFFER CONTENTS
;   ARE PRINTED AND A LINEFEED WILL AUTOMATICALLY
;   BE PERFORMED.
;
; * ASSUMES PORT 2=CONTROL, 3=DATA (MITS STANDARD)
;

; IO PORT EQUATES
PCTRL		EQU	002H	;CONTROL/STATUS PORT
PDATA		EQU	003H	;DATA PORT

; CONTROL PORT OUTPUT COMMANDS ...
PRT		EQU	001H	;PRINT COMMAND (FORCE PRINT OF BUFF)
LF		EQU	002H	;LINEFEED COMMAND
CLRBUF		EQU	004H	;CLEAR CHAR BUFFER COMMAND

; CONTROL PORT INPUT STATUS BIT MASKS ...
BUFFUL		EQU	001H	;BIT 0=0=FULL, BIT 0=1=EMPTY
PRTBSY		EQU	002H	;BIT 1=0=PRINTING, BIT 1=1=IDLE
JAMMED		EQU	004H	;BIT 2=0=JAMMED, BIT 2=1=NORMAL
LFRDY		EQU	008H	;BIT 3=0=LF IN PROCESS, BIT 3=1=RDY FOR LF

;
; TEST PROGRAM FOLLOWS ...

		ORG	00000H

		MVI	B,000H	;START WITH CHAR 0 FIRST
DOPRT:		MOV	A,B	;LOAD ACC WITH CHAR TO PRINT
		OUT	PDATA	;SEND CHAR TO PRINTER BUFFER
		IN	PCTRL	;CHECK IF BUFFER IS FULL (80 CHARS)
		ANI	BUFFUL	;BUFFER FULL MASK
		JNZ	DOPRT	;JUMP IF BUFFER NOT YET FULL

;
; SINCE BUFFER IF FULL, PRINTER IS PRINTING AT THIS POINT
;
WAIT:		IN	PCTRL	;WAIT UNTIL PRINTER IS NOT PRINTING
		ANI	PRTBSY	;PRINTING MASK
		JZ	WAIT	;JUMP IF STILL PRINTING

;
; PRINTER STOPPED PRINTING AT THIS POINT
;
		MOV	A,B	;GET CHAR THAT WAS JUST PRINTED
		CPI	03FH	;DID WE PRINT A LINE FOR ALL 64 CHARS?
		JZ	DONE	;QUIT IF SO
		INR	B	;NEXT CHAR TO PRINT ON NEXT LINE
		JMP	DOPRT	;DO IT AGAIN

DONE:		HLT		;ALL STOP

		END
