[Misc]
Width=234
Height=77
Title=Iomega Registration

[OnInit]
Item1=*,*,*,WRITEDAT,Defaults,500,

[OnExit]
Item1=Defaults,EXITCODE,3,WRITEDAT,Defaults,500,Mail
Item2=Defaults,EXITCODE,1,WRITEDAT,Defaults,500,Fax
Item3=*,*,*,WRITEINI,Misc,whichform,REGPRINT.FRM,Defaults,500
Item4=Defaults,500,*,SCREEN,regprint
Item5=Defaults,EXITCODE,2,SCREEN,io_cancl

[Field Profile]
Field1="Print &Fax Form",defpushbutton,1,19,46,57,14
Field2="Print &Mail Form",pushbutton,3,84,46,57,14
Field3="Cancel",pushbutton,2,149,46,57,14
Field4="Please print out your registration form. For your convenience you can either Fax or Mail in your registration. ",ltext,-1,17,14,198,16

