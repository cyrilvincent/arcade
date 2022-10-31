[Misc]
Width=235
Height=102
Title=Modem Diagnostics

[OnExit]
Item1=Defaults,Exitcode,2,SCREEN,faxrmail
;Item1=Defaults,Exitcode,2,SCREEN,ftpcheck

[Field Profile]
Field1="&Retry",defpushbutton,10,48,77,50,14
Field2="Cancel",pushbutton,2,140,77,50,14
Field3="Did not find a phone line attached to your modem. Please check to see if a phone line is plugged into your modem.",ltext,-1,17,15,207,24
Field4="It should plug into the jack marked 'LINE'.",ltext,-1,17,38,213,24
Field5="Please hit Retry to try again.",ltext,-1,17,54,213,18
