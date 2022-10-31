[Misc]
token=REGPRINT
WhichForm=

[OnInit]
Item1=*,*,*,WRITEDAT,Defaults,30050,0

[OnExit]
Item1=Defaults,regprint,SUCCESS,SCREEN,PRINTSUC
Item2=Defaults,regprint,CANCEL,SCREEN,PRINTCAN
Item3=Defaults,regprint,SUCCESS,WRITEDAT,Defaults,30050,1
Item4=Defaults,regprint,SUCCESS,WRITEINI,REGISTER,IDENTITY,PIPELINE.INI,Defaults,30050
