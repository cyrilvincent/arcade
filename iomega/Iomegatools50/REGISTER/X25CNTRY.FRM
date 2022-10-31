[Misc]
Width=242
Height=181
Title=Select Country
nextscreen=prefix
previous=2

[OnExit]
Item1=Defaults,EXITCODE,2,SCREEN,io_cancl

[Field Profile]
Field1=,countryx25,400,64,81,158,60
Field2=,cityx25,401,64,104,158,60

Field3="&Continue",defpushbutton,1,168,156,50,14
Field4="&Previous",pushbutton,10,91,156,50,14
Field5="Cancel",pushbutton,2,14,156,50,14

Field6="If your computer has a modem with a telephone line attached, we can send your information electronically.",ltext,-1,6,11,215,19
Field7="Country:",rtext,-1,9,79,47,8
Field8="First, we need to know what country you are registering from.",ltext,-1,6,34,215,8
Field9="City: ",rtext,cbb_city_text,9,102,47,8
Field10=" Select the location you are calling from ",groupbox,-1,5,58,224,75
