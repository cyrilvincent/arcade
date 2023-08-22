DISASM .ORG $B000 ; DISASSEMBLER FOR THE MCS-6502
VERSION 0 March 1982 Hans Otten
Disassembly subroutine by Wozniak/Baum  V3 Hans Otten, January 17, 2023 KIM-1 TTY version

changed to TASM32 syntax 
  tasm -65 -x3 -g1 -s "PRDISV3.ASM" "PRDISV3.pap"  "PRDISV3.lst"  -s "PRDISV3.sym"

 Changed to paginated or simple output format, traces of H14 serial printer and parallel keyboard present in comments
 8 bit character display 
 print/video behaviour changed

How to use

- Load and start program at $B000, Uses buffer at $0200
- Choose paginated or not, enter P or P for paginated 
- enter start and address in hex, allowed is  
   0100 0300
   0100-0300
   0100,0300 
- backspace works
- Enter header text if paginated
- Disassembly starts now
- if not paginated output stops after page, ENter to continue., other key stops
- at end monitor is entered at B000

Improvements V3, Hans Otten, 1982

- based upon work by Glen Deas who made V2 with all the syntax and standard KIM-1 TTY routines changes 
- No problems with echo or 7 bit anymore, all standard KIM-1 TTY monitor
- Code for H14 printer or parallel keyboard commented out, reducing size
- Rommable, variables moved to RAM $0200, program at $B000
- Stops non-paginated output after every 16 lines, any key but Enter stops program
- Source formatted and syntax changed for TASM32
- license (MIT) added