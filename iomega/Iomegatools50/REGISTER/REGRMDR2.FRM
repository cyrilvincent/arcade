[Misc]
Width=135
Height=85
Title=Select a Time
NextScreen=REGRMDR3

[OnInit]
Item1=*,*,*,WRITEDAT,defaults,110,Two Weeks

[OnExit]
Item1=Defaults,110,*,WRITEDAT,defaults,1218,You will be reminded
Item2=Defaults,110,Tomorrow,APPENDDAT,defaults,1218, tomorrow.
Item3=Defaults,110,Tomorrow,WRITEDAT,defaults,67,1
Item4=Defaults,67,1,WRITEINI,Misc,Remind,REMIND.FRM
Item5=Defaults,110,One Week,APPENDDAT,defaults,1218, in one week.
Item6=Defaults,110,One Week,WRITEDAT,defaults,67,7
Item7=Defaults,67,7,WRITEINI,Misc,Remind,REMIND.FRM
Item8=Defaults,110,Two Weeks,APPENDDAT,defaults,1218, in two weeks.
Item9=Defaults,110,Two Weeks,WRITEDAT,defaults,67,14
Item10=Defaults,67,14,WRITEINI,Misc,Remind,REMIND.FRM

[Field Profile]
Field1="Schedule",DROPDOWNLISTBOX,110,15,30,100,50
Field2="OK",defpushbutton,1,9,58,50,14
Field3="Cancel",pushbutton,10,78,58,50,14
Field4="Please choose a reminder time:",ltext,-1,15,10,175,8

[Values]
110=Tomorrow,One Week,Two Weeks
