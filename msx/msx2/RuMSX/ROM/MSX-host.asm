;------------------------------------------------------------------
;MSX Host Interface V1.2
;(intended for compilation with tniASM assembler)
;
;CAPS is synchronized with host-system
;KANA/HANGUL (if used) is synchronized with host-system
;Hanja and Junja mode are not explicitly supported by MSX computers
;
;See also:
;  HanjaMode VK_HANJA.
;            The Hanja (Korean characters) Mode key. 
;  JunjaMode VK_JUNJA.
;            The Junja Mode key. 
;  KanaMode  VK_KANA, VK_HANGUL.
;            The Kana Mode (Kana Lock) key.
;            Also used for Hangul (Korean characters). 
;  KanjiMode VK_KANJI.
;            The Kanji (Japanese name for ideographic characters
;            of Chinese origin) Mode key.
;  IME final mode VK_FINAL 
;
;Features:
;CALL HOSTKEYON    enables host-system keyboard        (integration active)
;CALL HOSTKEYOFF   uses guessed layout of MSX keyboard (native emulation)
;CALL HOSTUPTIME   queries, how long the MSX-session is running
;CALL HOSTSHUTDOWN quits the MSX emulation
;
;Known issue:
;CALL KANJI registers a HTIMI hook with own keyboard decoder,
;that supersedes the pre-registered MSX-HOST keyboard driver.
;
;
;Assumptions: this code is intended to be executed in RAM memory (2nd choice)
;             or as new ROM-Type "MSX-Emulator host Interface" which has RAM
;             memory top-down beginning from $7FFF (for now starting at RAMBAS) 
;------------------------------------------------------------------
;
VERMAJ: EQU     1            ;ROM Major version
VERMIN: EQU     2            ;ROM Minor version  
;
KEYFLG: EQU     00FH         ;MSX key fetch flags
DMYCHR: EQU     030H         ;Dummy character code (030H=CTRL, does nothing)
;
OUTDO:  EQU     00018H       ;Output to current device
WRTPSG: EQU     00093H       ;Write data in PSG register
RSLREG: EQU     00138H       ;Read Primary Slot Register
KILBUF: EQU     00156H       ;Clear keyboard buffer 
CALBAS: EQU     00159H       ;Call to BASIC from any slot
CINT:   EQU     02F8AH       ;Convert to Integer
;
ERROR:  EQU     0406FH       ;Basic Error-Routine
DOCNVF: EQU     0517AH       ;Convert variable type
PTRGET: EQU     05EA4H       ;Get pointer to Basic variable
STRINI: EQU     06627H       ;Allocate Basic string
;
USRTAB: EQU     0F39AH       ;USR-Function Adress-Table
PUTPNT: EQU     0F3F8H       ;Put position in KEYBUF 
GETPNT: EQU     0F3FAH       ;Get position in KEYBUF
BUF:    EQU     0F55EH       ;Input buffer (258 bytes)
VALTYP: EQU     0F663H       ;BASIC Value-Type
DSCTMP: EQU     0F698H       ;Basic string result descriptor
DAC:    EQU     0F7F6H       ;DAC (decimal accumulator)
KEYBUF: EQU     0FBF0H       ;Key code buffer
BOTTOM: EQU     0FC48H       ;lowest RAM location used by the Interpreter
HIMEM:  EQU     0FC4AH       ;highest RAM location used by the interpreter
CAPST:  EQU     0FCABH       ;Capital status
KANAST: EQU     0FCACH       ;KANA/HANGUL status  
KANAMD: EQU     0FCADH       ;keyboard mode on Japanese machines 
EXPTBL: EQU     0FCC1H       ;Flag for expanded slot
SLTTBL: EQU     0FCC5H       ;Current expanded slot reg
SLTWRK: EQU     0FD09H       ;Slot attributes 
PROCNM: EQU     0FD89H       ;Name of expanded statement
HTIMI:  EQU     0FD9FH       ;VDP Interrupt handler   
HKEYC:  EQU     0FDCCH       ;Keyboard decoder     
;
HIBASE: EQU     0FFE0H       ;HostInterface Base address
;
HIBACK: EQU     07FFDH       ;HostInterface backup data
OHKEYC: EQU     07FF8H       ;Old Keyboard decoder
OHTIMI: EQU     07FF3H       ;Old VDP Interrupt handler
MSXCHR: EQU     07FF2H       ;Fetched MSX character code
BOOTMD: EQU     07FF1H       ;Boot mode
RAMBAS: EQU     07F00H       ;MSX-HOST RAM base
;
        ORG     04000H
;
;------------------------------------------------------------------
;ROM-Header:
;------------------------------------------------------------------
        DB       'A', 'B'    ;Magic ID
        DW       ROMINI      ;Init address
        DW       CALSTH      ;CALL Statement handler
        DW       0           ;Device handler
        DW       0           ;Basic text
        DW       0
        DW       0
        DW       0
;------------------------------------------------------------------
;AutoDetect signature
;
;This signature can be used to detect the MSX-HOST ROM code
;and (if needed) assign the corresponding ROM-type.
;------------------------------------------------------------------
        DB       'MSX-HOST'
;------------------------------------------------------------------
;ROM Version information
;------------------------------------------------------------------
        DB       VERMAJ      ;ROM Major version
        DB       VERMIN      ;ROM Minor version
        DB       0x01        ;BIOS present
        DB       0x00        ;Reserved
;------------------------------------------------------------------
;BIOS
;------------------------------------------------------------------
        JP       GETBM       ;Get BootMode
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
        DB       0, 0, 0
;------------------------------------------------------------------
;ROM Initialisation
;------------------------------------------------------------------
ROMINI: DI
;
        LD       HL,RAMBAS   ;Test RAM
        LD       A,(HL)
        CPL
        LD       (HL),A
        CP       (HL)
        JR       NZ,NORAM
        CPL
        LD       (HL),A
;
        LD       HL,HTIMI    ;Backup old hooks
        LD       DE,OHTIMI
        LD       BC,5
        LDIR
        LD       HL,HKEYC
        LD       DE,OHKEYC
        LD       BC,5
        LDIR
;
        LD       HL,NHTIMI   ;Set new hooks
        LD       DE,HTIMI
        LD       BC,5
        LDIR
        LD       HL,NHKEYC
        LD       DE,HKEYC
        LD       BC,5
        LDIR
;
        CALL     GETSLT
        LD       (HTIMI+1),A
        LD       (HKEYC+1),A
;
;Activate HostInterface routine
        CALL     IFINIT
;Enable HOST keyboard by default 
        LD       A,003H      ;Set Settings      
        LD       B,000H      ;Reserved: setting-index
        LD       HL,00001H   ;Set bit 0
        PUSH     HL
        POP      DE          ;Consider bit 0
        CALL     HIBASE      ;Call HostInterface
;Additional: get boot mode
        LD       A,00AH      ;Get BootMode
        LD       B,000H      ;Reserved
        CALL     HIBASE      ;Call HostInterface
        LD       A,B
        LD       (BOOTMD),A
;Deactivate HostInterface routine  
        CALL     IFTERM
;Return from ROM-Initialisation       
        EI 
        RET
;
;------------------------------------------------------------------
;No scratch RAM available (wrong ROM-type?)
;------------------------------------------------------------------
NORAM:  LD       HL,NORAMM
NORAM1: LD       A,(HL)
        AND      A
        JR       Z,STOP
        CALL     OUTDO
        INC      HL
        JR       NORAM1
STOP:   DI
        HALT
;
NORAMM: DB       'Missing MSX-HOST RAM!'
        DB       10,13
        DB       'Wrong ROM-type?'
        DB       0
;
;------------------------------------------------------------------
;Get current slot ID of page 1
;------------------------------------------------------------------
GETSLT: CALL     RSLREG      ;Read Primary Slot register
        RRCA                 ;Get primary slot# in bit0+1
        RRCA
        AND      003H
        LD       C,A         ;PSL into C (LO)
        LD       B,0         ;B (Hi) = 0
        LD       HL,EXPTBL
        ADD      HL,BC
        OR       (HL)        ;Merge 080H for expanded slot
        LD       C,A         ;Save into C
        INC      HL          ;SLTTBL
        INC      HL
        INC      HL
        INC      HL
        LD       A,(HL)      ;Get current expanded slot register
        AND      00CH        ; in bit2+3 
        OR       C           ;Merge with bit 7, 0+1
        RET
;
;------------------------------------------------------------------
;Hook routines (templates)
;------------------------------------------------------------------
NHTIMI: DB       0F7H        ;RST 030H 
        DB       000H        ;Slot ID placeholder
        DW       KHTIMI      ;Hook implementation
        DB       0C9H        ;RET
;
NHKEYC: DB       0F7H        ;RST 030H 
        DB       000H        ;Slot ID placeholder
        DW       KHKEYC      ;Hook implementation
        DB       0C9H        ;RET
;
;------------------------------------------------------------------
;Own hook routines for HOST keyboard-driver
;------------------------------------------------------------------
;
;------------------------------------------------------------------
;MSX-HOST HTIMI hook routine
;------------------------------------------------------------------
KHTIMI: 
        CALL     IFINIT
;
        SCF
        LD       A,2         ;GetSettings
        LD       B,000H      ;SettingsIndex=0
        CALL     HIBASE
        JR       C,TIMI1     ;GetSettings unsupported
        JR       NZ,TIMI1    ;GetSettings failed
        LD       A,L
        AND      001H        ;Host Keyboard enabled?
        JR       Z,TIMI1
;
TIMI0:  LD       A,5         ;GetKeys
        LD       HL,MSXCHR
        LD       B,KEYFLG    ;Mask
        LD       C,001H      ;1 Character
        CALL     HIBASE
        JR       C,TIMI1     ;GetKeys unsupported
        JR       NZ,TIMI1    ;GetKeys failed
        LD       A,C         ;Number of chars
        OR       A
        JR       Z,TIMI1     ;No character: end
;Put MSX character code
        LD       A,(MSXCHR)
        CALL     MSXPUT
;Fetch next character (if any)
        JR       TIMI0
;               
TIMI1:  CALL     HDLTOG      ;Handle Toggle keys KANA/HANGUL and CAPS
        CALL     IFTERM
        JP       OHTIMI
;
;------------------------------------------------------------------
;Put character into key buffer
;Entry: A = keycode
;Modifies: HL
;------------------------------------------------------------------
MSXPUT: LD       HL,(PUTPNT)
        LD       (HL),A
        CALL     KBUFNX      ;Keyboard buffer pointer to next char
;       CALL     HDLTOG      ;Handle KANA, HANGUL, CODE  
        LD       A,(GETPNT)
        CP       L
        RET      Z
        LD       (PUTPNT),HL
        RET
;
;Increment keyboard buffer pointer (in HL) circular
KBUFNX: INC      HL
        LD       A,L
        CP       018H
        RET      NZ
        LD       HL,KEYBUF
        RET
;
;------------------------------------------------------------------
;Handle toggle keys KANA/HANGUL and CAPS status:
;Keep KANA/HANGUL on Japanese/Korean MSX, otherwise clear
;------------------------------------------------------------------
HDLTOG: LD       A,006H      ;Get Toggle keys
        LD       B,003H      ;CAPS + KANA/HANGUL
        CALL     HIBASE      ;Get Toggle status in B
        JR       C,TOGERR    ;GetToggleStatus unsupported
        JR       NZ,TOGERR   ;GetToggleStatus failed
        JR       PRCTOG      ;Success: process toggle keys
;GetToggleStatus error
TOGERR: LD       B,000H      ;Error: assume all toggles OFF 
;Process Kana/Hangul toggle status
PRCTOG: LD       A,(0002BH)  ;BIOS version: character-set, ...
        AND      00FH   ;Mask character set only
        JR       Z,KANHAN    ;Japanese keyboard: supports KANA
        CP       002H
        JR       Z,KANHAN    ;Korean keyboard: supports HANGUL
;International keyboard (european, ...): clear KANAST
        XOR      A
        LD       (KANAST),A
        JR       CHKCAP
;KANA/HANGUL supported by the MSX version        
KANHAN: LD       A,B
        AND      002H        ;KANA/HANGUL?
        RRC      A           ;2->1 or 0->0
        LD       HL,KANAST
        CP       (HL)
        JR       Z,CHKCAP    ;No status change: skip
;KANA/HANGUL status toggled
        LD       (HL),A      ;change KANAST
        XOR      A
        LD       (KANAMD),A
;Toggle KANA/HANGUL LED
        LD       A,(HL)      ;KANAST    000H or 001H 
        RRC      A           ;change to 000H or 080H
        XOR      080H
        LD       E,A
        LD       A,15
        CALL     WRTPSG
        POP      AF
;
;Check CAPS lock status        
CHKCAP: LD       A,B
        AND      001H        ;CAPS lock?
        DEC      A           ;000H=Yes, 0FFH=No
        CPL                  ;0FFH=Yes, 000H=No
        LD       HL,CAPST
        CP       (HL)
        RET      Z           ;CAPS status unchanged: return
        LD       (CAPST),A
;Toggle CAPS LED
        CPL
        AND      A
        LD       A,000CH
        JR       Z,SETCAP
        INC      A
SETCAP: OUT      (0ABH),A    ;Write PPI port C (set CAPS Led)
        RET
;
;------------------------------------------------------------------
;MSX-HOST HKEYC hook routine
;Entry/Exit: HL = pointer to decoder table
;            A = key group
;------------------------------------------------------------------
KHKEYC: CP       030H
        JR       C,KEYC0     ;Row 0-5 (0-9, ..., A-Z): likely already decoded
        CP       03CH
        JR       Z,KEYC3     ;Row 7 STOP: decode in MSX BIOS
        CP       03AH
        JR       NC,KEYC0    ;Row 8-10 + part of Row 7: likely already decoded
;Row 6 + part of Row 7 (selected character) is probably already decoded
;F4+F5 or Row 7 are already excluded
;Includes: Shift, Ctrl, Grph, Caps, Code/Kana/Hangul, F1-F5
        CP       033H
        JR       Z,KEYC0     ;CAPS: already handled?
        CP       034H
        JR       Z,KEYC0     ;KANA, HANGUL, CODE: already handled?
;       CP       03AH       
;       JR       C,KEYC3     ;Row6+7: Shift/Ctrl/Grph/F1-F5: decode in MSX BIOS
        JR       KEYC3
;Here we have RETURN, SELECT, BACK, TAB or ESC
;They are already pre-decoded and may not need to be decoded again        
;
;Likely already decoded character: use from MSX-HOST (if enabled)
KEYC0:  PUSH     HL          ;Save decoder table
        PUSH     AF          ;Save key-code
        CALL     OHKEYC      ;Call old HKEYC
;
        DI
        CALL     IFINIT
;
        SCF
        LD       A,2         ;GetSettings
        LD       B,000H      ;SettingsIndex=0
        CALL     HIBASE
        PUSH     AF          ;Save result     
        CALL     IFTERM
        EI
        POP      AF          ;Restore result
;
        JR       C,KEYC1     ;GetSettings unsupported
        JR       NZ,KEYC1    ;GetSettings failed
        LD       A,L
        AND      001H        ;Host Keyboard enabled?
        JR       Z,KEYC1
;
;if keyboard is active: discard MSX key input
        POP      AF          ;Discard AF
        LD       A,DMYCHR    ;MSX keyboard
        JR       KEYC2
;
KEYC1:  POP      AF          ;Restore key-code
KEYC2:  POP      HL          ;Restore decoder table
KEYC3:  RET
;
;
;------------------------------------------------------------------
;MSX-HOST Interface Call Opcodes
;------------------------------------------------------------------
HIOPC:  DB      0EDH, 0FEH
        RET
;        
;------------------------------------------------------------------
;MSX-HOST Interface initialisation
;(Backup data and set interface opcodes)
;Note: Interrupt must be disabled!
;
;Modifies: HL', DE', BC'
;------------------------------------------------------------------
IFINIT: EXX   
        LD      HL,HIBASE
        LD      DE,HIBACK
        LD      BC,3
        LDIR                 ;Save original RAM
        LD      HL,HIOPC
        LD      DE,HIBASE
        LD      BC,3
        LDIR                 ;Build opcodes
        EXX
        RET
;
;------------------------------------------------------------------
;MSX-HOST Interface initialisation
;(Restore data)
;Note: Interrupt must be disabled!
;
;Modifies: HL', DE', BC'
;------------------------------------------------------------------
IFTERM: EXX
        LD      HL,HIBACK
        LD      DE,HIBASE
        LD      BC,3
        LDIR                 ;Restore original RAM
        EXX
        RET
;
;------------------------------------------------------------------
;CALL Statement handler
;
;Entry:    PROCNM = name of the CALL statement
;          HL     = basic pointer to the 1st character after the name
;
;Exit:     AF     = carry, if statement not recognized
;------------------------------------------------------------------
CALSTH: PUSH    HL           ;Save basic-pointer
        PUSH    HL           ;Backup basic-pointer into IX
        POP     IX
        CALL    TESTNM
        POP     HL           ;Restore original basic-pointer
        ;(only if statement is not recognized)
        RET                  ;Return from this handler
;
;Detect CALL statement
TESTNM: LD      HL,NCALKB    ;Command table
;Check command name
TESTN2: LD      DE,PROCNM
;Check character
TESTN3: LD      A,(DE)       ;Get PROCNM character
        CP      (HL)         ;Get command character
        INC     DE
        INC     HL
        JR      NZ,TESTN6    ;Command name does not match
        CP      $20          ;Space? (some commands use it as delimiter)
        JR      Z,TESTN8     ;Yes: command name matches
        AND     A            ;Terminated?
        JR      NZ,TESTN3    ;No: check next character
;Command name matches
TESTN4: LD      A,(HL)       ;Get command address Lo
        INC     HL
        LD      H,(HL)       ;Get command address Hi
        LD      L,A
;
        POP     DE           ;POP return address
        POP     DE           ;POP saved HL and skip POP HL
;
        JP      (HL)         ;Execute call statement
;Seek to next command in table
TESTN5: INC     HL
        LD      A,(HL)
;Is command end? (command name does not match)
TESTN6: AND     A
        JR      NZ,TESTN5
;Command end (command name does not match)
        INC     HL           ;Skip terminating 0
        INC     HL           ;Skip command address Lo
        INC     HL           ;Skip command address Hi
        LD      A,(HL)       ;Get 1st character of next command
        AND     A            ;Is there one more command?
        JR      NZ,TESTN2    ;Check command name
;Stop parsing, command not recognized
        SCF
        RET
;Command name matches, but ends with a space.
;In this case more tokens are expected.
TESTN8: INC     HL           ;Skip space
        JR      TESTN4
;
;------------------------------------------------------------------
;CALL Statement handler table
;------------------------------------------------------------------
NCALKB: DB      'HOSTKEYOFF' ;CALL HOSTKEYOFF
        DB      0
        DW      CALHK0
;
        DB      'HOSTKEYON'  ;CALL HOSTKEYON
        DB      0
        DW      CALHK1
;
        DB      'HOSTKEY '   ;CALL HOSTKEY
        DB      0
        DW      CALKBD
;
        DB      'HOSTUPTIME' ;CALL HOSTUPTIME
        DB      0
        DW      CALUTM
;
        DB      'HOSTSHUTDOWN' ;CALL HOSTSHUTDOWN
        DB      0
        DW      CALSDN
;
        DB      'HOSTGETBOOTMODE' ;CALL HOSTGETBOOTMODE
        DB      0
        DW      CALBTM
;
        DB      0
;
;------------------------------------------------------------------
;CALL HOSTKEYOFF
;
;Toggles the host-keyboard usage off.
;
;Since: MSX-HOST ROM v1.0
;------------------------------------------------------------------
CALHK0: XOR     A
        JR      CALKB3
;------------------------------------------------------------------
;CALL HOSTKEYON
;
;Toggles the host-keyboard usage on.
;
;Since: MSX-HOST ROM v1.0
;------------------------------------------------------------------
CALHK1: LD      A,1
        JR      CALKB3
;
;------------------------------------------------------------------
;CALL HOSTKEY ON/OFF
;
;Toggles the host-keyboard usage on/off.
;Note: in version 1.0 of the MSX-HOST ROM no space between HOSTKEY
;and ON or OFF was allowed. Since version 1.0 a space can be used
;as delimiter.
;
;Exit:     MSX keyboard input from the specified source
;          (ON = Windows keyboard, OFF = virtual MSX keyboard).
;          Generates an "Illegal function call" error,
;          if not supported by the host
;
;Since:    MSX-HOST ROM v1.1
;------------------------------------------------------------------
CALKBD: LD      H,D
        LD      L,E
;Check ON/OFF but skip leading spaces
CALKBN: LD      A,(HL)
        CP      020H;        ;Space?
        JR      NZ,CALKBC
        INC     HL
        JR      CALKBN
;Check ON/OFF?
CALKBC: CP      'O'
        JR      NZ,CALUNR    ;No O(N/FF)
        INC     HL
        LD      A,(HL)
        CP      'N'
        JR      Z,CALKB1     ;CALL HOSTKEY ON
        LD      A,'F'
        CP      (HL)
        JR      NZ,CALUNR
        INC     HL
        CP      (HL)
        JR      NZ,CALUNR
;
;CALL HOSTKEY OFF
CALKB0: XOR     A
        JR      CALKB2
;
;CALL HOSTKEY ON
CALKB1: LD      A,1
;
CALKB2: LD      D,A
        INC     HL
        LD      A,(HL)
        OR      A
        JR      NZ,CALUNR
;
        LD      A,D
;
;CALL HOSTKEY (A)
CALKB3: DI
        CALL    IFINIT
        LD      H,0
        LD      L,A
        LD      DE,00001H    ;Use Host OS keyboard
        LD      A,3          ;Set setting flags
        CALL    HIBASE
;Reset character input to avoid appearance of
;previously entered characters (ignore errors here)        
        LD      A,4          ;Reset character input        
        CALL    HIBASE
;
        CALL    IFTERM
        EI
        LD      A,E          ;Changed flags of [Set setting flags]
        BIT     0,A
        JP      Z,ILLFCT     ;Unsupported bit: fail!
;Note: because the support bit indicates the (un)sucessful setting
;the C/NZ flags of the HIBASE call-result are ignored.
        AND     A    ;Clear carry (since V1.02) for success
        RET
;
;------------------------------------------------------------------
;Unrecognized CALL statement
;------------------------------------------------------------------
CALUNR: SCF
        RET
;
;------------------------------------------------------------------
;CALL SHUTDOWN
;
;Quits MSX-emulation without confirmation-prompt.
;
;Exit:     Quits MSX-emulation.
;          Generates a "Device I/O error" if not supported by the host.
;          Programs are responsible for correct handling of such
;          conditions (e.g. by displaying a message and looping infinite).
;
;Since:    MSX-HOST ROM v1.2
;------------------------------------------------------------------
CALSDN: DI
        CALL    IFINIT
        LD      A,9          ;Shutdown
        CALL    HIBASE
;(succeeded shutdown should not return)
        PUSH    AF           ;Save result     
        CALL    IFTERM
        EI
        POP     AF           ;Restore result
;Error?
        JP      C,DEVIOE     ;Shutdown unsupported
        JP      NZ,DEVIOE    ;Shutdown failed
;
        RET
;
;------------------------------------------------------------------
;CALL HOSTUPTIME([CpuTimeString][[,][Vdp60Hz][,Vdp50Hz]])
;
;Get uptime of the MSX-HOST (usually emulation). The uptime
;is measured by a string containing 1-10 digits. The resolution
;of this timer is 255682 Hz (same as the Turbo-R system timer),
;but it provides more digits.
;In addition the number of completed 60Hz and 50Hz VDP refreshes
;can be queried. These values are 16bit integers only and will
;therefore overflow after approx. 20 minutes (depending on the
;frequency).
;
;The timers are assumed to be reset on every soft- or hard-boot.
;This enables profiling of the MSX-BIOS boot-time, which may only
;be affected by the MSX 2+/TR reset-status of I/O port &HF4
;(boot-method and boot-mode).
;
;Exit:     Queried MSX-Basic variables.
;          Generates a "Device I/O error",
;          if not supported by the host
;
;Since:    MSX-HOST ROM v1.2
;------------------------------------------------------------------
CALUTM: PUSH    IX    ;Copy basic-pointer into HL
        POP     HL
        LD      A,(HL)
        CP      '('
        JP      NZ,SYNTAX
        INC     HL           ;Skip '('
        LD      A,(HL)
        CP      ','
        JR      Z,CALUT6     ;CpuTimeString is omitted
;CpuTimeString is specified
        CALL    GETVAD       ;Get address of Basic variable
        LD      A,(VALTYP)
        CP      003H         ;String?
        JP      NZ,TYPMIS    ;No: Type mismatch
        PUSH    HL           ;Save basic pointer
        PUSH    DE           ;Save variable pointer
        DI
        CALL    IFINIT
        LD      HL,BUF
        LD      A,8          ;Get CPU uptime
        CALL    HIBASE
        PUSH    AF
        CALL    IFTERM
        EI
        POP     AF
        JP      C,DEVIOE     ;GetCpuUptime unsupported
        JP      NZ,DEVIOE    ;GetCpuUptime failed
;Convert 10 BCD digits into String
        LD      B,5          ;2*5 digits
        LD      HL,BUF       ;BCD digit buffer
        LD      DE,BUF+5     ;ACSII digit buffer
CALUT2: LD      A,(HL)       ;Convert BCD buffer to String
        PUSH    AF
        SRL     A
        SRL     A
        SRL     A
        SRL     A
        CALL    PUSHDG
        POP     AF
        CALL    PUSHDG
        INC     HL
        DJNZ    CALUT2
;HL now points to BUF+5
;It contains a 10 digit number, where leading zeroes will be
;stripped. To keep at least one "0" up to 9 digits are stripped.
        LD      B,9
CALUT3: LD      A,(HL)
        CP      '0'
        JR      NZ,CALUT4
        INC     HL
        DJNZ    CALUT3
        INC     B            ;Update string-length
;Move string to BUF
CALUT4: LD      DE,BUF
        PUSH    BC           ;Save string-length
CALUT5: LD      A,(HL)
        LD      (DE),A
        INC     HL
        INC     DE
        DJNZ    CALUT5
        POP     BC           ;Restore string-length
        LD      A,B
        PUSH    AF           ;Save string-length
        CALL    ALCSTR       ;Allocate basic string
        POP     AF           ;Restore string-length
;Copy string into allocated buffer (not empty)
        LD      C,A          ;String length
        LD      B,0
        LD      DE,(DSCTMP+1)
        LD      HL,BUF
        LDIR                 ;Copy string (never empty)
;Copy string descriptor
        POP     DE           ;restore variable pointer
        LD      HL,DSCTMP
        LD      BC,3
        LDIR
;Restore basic-pointer and continue with VDP uptime(s)
        POP     HL
;Process VDP uptime(s)
CALUT6:
        LD      A,(HL)
        CP      ','
        JR      NZ,CALUT8    ;No ','; must be ')'
        INC     HL           ;Skip ','
;VDP uptime(s) requested
;        CALL    GETVAD       ;Get address of Basic variable
;        LD      A,(VALTYP)
;        CP      002H         ;Integer?
;        JR      NZ,TYPMIS    ;No: Type mismatch
        PUSH    HL           ;Save basic pointer
        DI
        CALL    IFINIT
        LD      HL,BUF
        PUSH    HL           ;save BUF
        LD      A,7          ;Get VDP uptime
        CALL    HIBASE
        PUSH    AF
        CALL    IFTERM
        EI
        POP     AF
        JP      C,DEVIOE     ;GetVdpUptime unsupported
        JP      NZ,DEVIOE    ;GetVdpUptime failed
        POP     IX           ;restore BUF
        POP     HL           ;restore Basic-pointer
        LD      A,(HL)
        CP      ','          ;60Hz counter omitted?
        JR      Z,CALUT7
;Assign 60Hz counter
        PUSH    IX           ;Save pointer to int
        CALL    RETINT
        POP     IX           ;Restore pointer
        LD      A,(HL)
        CP      ','
        JR      NZ,CALUT8
;Assign 50Hz counter
CALUT7: INC     HL           ;Skip ','
        INC     IX
        INC     IX
        CALL    RETINT
        LD      A,(HL)
;
CALUT8: CP      ')'
        JR      NZ,SYNTAX
        INC     HL           ;Skip ')'
        AND     A            ;Clear carry to indicate success
        RET
;
;Push digit
;Convert digit in A to ASCII and put it onto location DE
PUSHDG: AND     00FH
        ADD     A,'0'
        LD      (DE),A
        INC     DE
        RET
;
;------------------------------------------------------------------
;Assign integer value to a basic variable
;
;Entry:    HL     = basic pointer (to 1st character of varname)
;          IX     = pointer to buffer with 16bit integer (lo/hi)
;
;Exit:     HL     = basic pointer
;          DE     = pointer to variable
;          VALTYP = variable type (2=INT, 4=SNG, 8=DBL, ...)
;
;Modifies: all registers
;------------------------------------------------------------------
RETINT: PUSH    HL           ;Save basic pointer
        PUSH    IX           ;Copy INT-pointer from IX to HL
        POP     HL
        LD      DE,DAC+2     ;Target = DAC+2
        LD      BC,2         ;2 Bytes
        LDIR                 ;Copy INT
;
        POP  HL              ;Restore basic-pointer to 1st char
        CALL    GETVAD       ;Get address of Basic variable
        PUSH    HL
        LD      H,D          ;Copy pointer of variable to HL
        LD      L,E
        CALL    INT2X        ;Assign INT value to variable
        POP     HL
        RET
;
;------------------------------------------------------------------
;Assign numeric value to MSX-Basic variable. The integer in
;DAC+2 is converted into the corresponding variable type.
;
;Entry:    HL     = pointer to variable (from PTRGET)
;          VALTYP = variable type (2=INT, 4=SNG, 8=DBL, ...)
;          DAC+2  = integer value to be set
;
;Exit:     DE     = pointer to variable
;
;Modifies: all registers
;------------------------------------------------------------------
INT2X:  PUSH    HL           ;save pointer to variable
        LD      HL,VALTYP    ;get variable type
        LD      A,(HL)
        LD      C,A          ;save type in C
        LD      (HL),002H    ;set new type = INT
        LD      HL,DAC+2
        CP      002H         ;INT?
        JR      Z,INT2X2
        CP      004H         ;SNG?
        JR      Z,INT2X1
        CP      008H         ;DBL?
        JP      NZ,TYPMIS    ;Type mismatch
;
INT2X1: PUSH    BC           ;save length (in C)
        CALL    CVTNUM       ;Convert type (CSNG, CDBL)
        POP     BC           ;restore length (in C)
        LD      HL,DAC       ;DAC (decimal accumulator)
;
INT2X2: LD      B,000H
        POP     DE           ;restore pointer to variable
        LDIR
        RET
;
;------------------------------------------------------------------
;Get address of Basic variable
;
;Entry:    HL     = basic pointer to 1st character of varname
;
;Exit:     HL     = basic pointer
;          DE     = pointer to variable
;          VALTYP = variable type (2=INT, 4=SNG, 8=DBL, ...)
;------------------------------------------------------------------
GETVAD: LD      IX,PTRGET
        JR      CALB
;
;------------------------------------------------------------------
;Allocate Basic string
;------------------------------------------------------------------
ALCSTR: LD      IX,STRINI
        JR      CALB
;
;------------------------------------------------------------------
;Convert variable type
;------------------------------------------------------------------
CVTNUM: LD      IX,DOCNVF
        JR      CALB
;
;------------------------------------------------------------------
;Error: Illegal function call
;------------------------------------------------------------------
ILLFCT: LD      E,5          ;Illegal function
BASERR: LD      IX,ERROR
CALB:   JP      CALBAS
;
;------------------------------------------------------------------
;Error: Syntax error
;------------------------------------------------------------------
SYNTAX: LD      E,2          ;Syntax error
        JR      BASERR
;
;------------------------------------------------------------------
;Error: Type mismatch
;------------------------------------------------------------------
TYPMIS: LD      E,13         ;Type mismatch
        JR      BASERR
;
;------------------------------------------------------------------
;Error: Device I/O error
;------------------------------------------------------------------
DEVIOE: LD      E,19         ;Device I/O error
        JR      BASERR
;
;------------------------------------------------------------------
;CALL HOSTGETBOOTMODE(BootMode)
;
;Get the boot-mode of the MSX-HOST (usually emulation). The
;boot-mode (hardware-reset, software-reset) is returned as
;integer, with up to 2 significant bits.
;  Zero value means software-reset
;  Non-zero value means hardware-reset
;Details:
;  Bit 0 = 1 hardware-reset
;  Bit 1 = 1 reserved for future use
;
;The boot-mode is similar to the Reset-Status flag (I/O-port $F4),
;but is also available on MSX 1+2 computers.
;In addition it is intended to detect real hardware-resets rather
;than preventing device conflicts.
;What kind of hardware resets? Those, who e.g. affect the CPU and
;VDP uptime (see corresponding function CALL HOSTUPTIME).
;
;Exit:     Queried MSX-Basic variables.
;          Generates a "Device I/O error",
;          if not supported by the host
;
;Since:    MSX-HOST ROM v1.2
;------------------------------------------------------------------
CALBTM: PUSH    IX           ;Copy basic-pointer into HL
        POP     HL
        LD      A,(HL)
        CP      '('
        JP      NZ,SYNTAX
        INC     HL           ;Skip '('
;Assign BootMode
        LD      IX,BUF
        XOR     A
        LD      (IX+1),A
        LD      A,(BOOTMD)
        LD      (IX),A
        CALL    RETINT
;
        LD      A,(HL)
        CP      ')'
        JR      NZ,SYNTAX
        INC     HL           ;Skip ')'
        AND     A            ;Clear carry to indicate success
        RET
;
;------------------------------------------------------------------
;BIOS: GetBootMode
;
;See CALL HOSTGETBOOTMODE for more details.
;
;Exit:     A      = Queried BootMode
;          AF     = carry, if statement not recognized
;                   non-zero after hardware-reset,
;                   zero after software-reset
;
;Since:    MSX-HOST ROM v1.2
;------------------------------------------------------------------
GETBM:  LD      A,(BOOTMD)
        AND     A            ;Clear carry to indicate success
        RET                  ;and to check A for NZ
;------------------------------------------------------------------
;End
        DS      ROMEND-$
ROMEND: ORG     08000H