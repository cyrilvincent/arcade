https://groups.google.com/g/comp.os.cpm/c/mfTdhZttbTo/m/xj838HKuCAAJ

dxforth
I believe I've sorted out all the details necessary to configure TERM.CTL
and expect this to be the final revision.

----------------------------------------------------------------------

Details of configurable items in TERM.CTL - the terminal data file
used by ORBQUEST for CP/M.

Last revised: 2020-01-06

File: TERM.CTL

OFFS VALUE SIZE FUNC COMMENT

00 1A 00 CD 67 0B CD 6 CLS CLEAR SCREEN/HOME CURSOR STRING
06 1B 54 00 C1 77 D8 6 CLEOL CLEAR TO END OF LINE STRING
0C 1B 3D 00 C5 E5 5 CPOS CURSOR POS LEAD-IN STRING
11 00 5C 1D 3A 4 CPOS CURSOR POS BETWEEN ROW/COL STRING
15 00 02 D6 0D 4 CPOS CURSOR POS AFTER STRING
19 00 BYTE HORIZONTAL OFFSET
1A 00 BYTE 0 = ROW FIRST 1 = COL FIRST
1B 01 BYTE (1)
1C 01 BYTE 1 = USE CLS/CLEOL 0 = SIMULATE

4D 20 00 WORD OFFSET ADDED TO ROW/COL

(1) Appears to be unused in Orbquest.

- Strings are terminated with 00H byte
- Data from 1D to EB is used by ORBQUEST
- Data from EC to FF is overwritten by the overlay

The usual disclaimers apply.

----------------------------------------------------------------------

http://planemo.org/retro/downloads/cpm/games/

