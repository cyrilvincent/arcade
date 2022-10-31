[Misc]
Width=215
Height=124
Title=Telephone Setup
NextScreen=Sendreg

[OnInit]
Item1=*,*,*,READINI,MODEM,Toll-Free Dialing Prefix,PIPELINE.INI,Defaults,100
Item2=*,*,*,READINI,MODEM,Dial Type,PIPELINE.INI,Defaults,201
Item3=Defaults,201,1,WRITEDAT,Defaults,101,Yes
Item4=Defaults,201,0,WRITEDAT,Defaults,102,Yes

[OnExit]
Item1=*,*,*,WRITEINI,MODEM,Toll-Free Dialing Prefix,PIPELINE.INI,Defaults,100
Item2=Defaults,101,Yes,WRITEDAT,Defaults,201,1
Item3=Defaults,101,No,WRITEDAT,Defaults,201,0
Item4=*,*,*,WRITEINI,MODEM,Dial Type,PIPELINE.INI,Defaults,201

[Field Profile]
Field1="Dialing Prefix:",ltext,-1,63,45,46,8
Field2=,EDIT,100,118,42,27,12
Field3="If you need to dial a '9' or other prefix to access an outside number, please enter the number or numbers to dial in the box below.",ltext,-1,6,5,196,33
Field4="Select your phone line's dial type:",ltext,-1,49,62,111,8
Field5="&Tone",radio,101,71,74,28,10
Field6="&Pulse",radio,102,108,74,29,10
Field7="OK",defpushbutton,1,79,100,50,14

[Radio Groups]
Group1=101,102

; Edit fields must be elaborated on here
[Edit Info]
100=EDIT,10,0
