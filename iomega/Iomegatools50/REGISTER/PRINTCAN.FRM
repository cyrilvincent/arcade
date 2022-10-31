[Misc]
Width=166
Height=80
Title=Print Canceled
Previous=2

[OnExit]
Item1=Defaults,Exitcode,2,SCREEN,REMIND14
Item2=Defaults,Exitcode,2,WRITEDAT,Defaults,1218,You will be reminded to register in two weeks.

[Field Profile]
Field1="&Retry",defpushbutton,10,38,54,50,14
Field2="Cancel",pushbutton,2,105,54,50,14
Field3="Print has been canceled.",ltext,-1,40,10,162,8
Field4="You may try again by clicking Retry\nor exit by clicking Cancel.",ltext,-1,40,26,162,16
Field5="question",icon,300,10,13,64,64
