[misc]
token=connect
; Name of next screen here
nextscreen=intro

[OnInit]
Item1=*,*,*,READINI,REGISTER,IDENTITY,PIPELINE.INI,DEFAULTS,IDENTITY
Item2=Defaults,IDENTITY,1,SCREEN,REGISTRD
Item3=*,*,*,WRITEDAT,Defaults,COMM PORT,
Item4=*,*,*,WRITEINI,MODEM,COMM PORT,PIPELINE.INI,Defaults,COMM PORT
Item5=*,*,*,WRITEDAT,Defaults,previous,2
Item6=*,*,*,WRITEINI,MISC,Previous,x25cntry.frm,Defaults,previous
