Pipeline Cookie Cutter Program definition

PROGRAM: Regrmdr

Files Needed: REGRMDR.SEQ, REGRMDR1.FRM, REGRMDR2.FRM, REGRMDR3.FRM,
              REMIND.FRM

This replaces REGRMDR.EXE.

Modifications:
1. In REGRMDR1.FRM change the last entry on Item 2 under the [OnExit]
   section to whichever .SEQ file you are using.

    [OnExit]
    Item2=Defaults,Exitcode,1,SEQUENCE,MHI.SEQ

These are the files
