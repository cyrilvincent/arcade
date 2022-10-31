[Misc]
Width=225
Height=110
Title=Iomega Registration
NextScreen=REMIND14

[OnExit]
Item1=Defaults,Exitcode,2,WRITEDAT,Defaults,1218,You will be reminded to register in two weeks.
Item2=Defaults,Exitcode,1,WRITEDAT,Defaults,1218,You will be reminded to register in two weeks.

[Field Profile]
Field1="&Previous",defpushbutton,10,150,87,50,16
Field2="Cancel",pushbutton,2,30,87,50,16
Field3="Completing this registration allows you to receive future special offers and upgrade notifications.",ltext,-1,17,10,190,24
Field4="The installation program provides a way for you to register by using your modem, fax or the mail.",ltext,-1,17,35,190,18
Field5="Are you sure you want to cancel?",ltext,-1,17,61,111,8


[ButtonDown]
1="continud.gif"
10="prev-dp.gif"
2="cancelbp.gif"
