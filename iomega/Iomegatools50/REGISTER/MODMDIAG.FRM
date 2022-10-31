[Misc]
token=modmdiag
Width=180
Height=215
LocalSlideShow=900
NextScreen=x25cntry
ignoreover=100

[OnExit]
Item1=Defaults,Exitcode,2,SCREEN,io_CANCL
Item2=Defaults,MODMDIAG,CANCEL,SCREEN,io_CANCL
Item3=Defaults,MODMDIAG,NOPHONE,SCREEN,MDNOLINE
Item4=Defaults,MODMDIAG,FAIL,SCREEN,MDFAIL

[Messages]
;NOUI_INIT=Performing Modem Diagnostics
;INIT=Performing Modem Diagnostics
NOUI_MD=Performing Modem Diagnostics
;STATUS=ENABLE
LOOKCOM1=Checking for modem at port COM1.
LOOKCOM2=Checking for modem at port COM2.
LOOKCOM3=Checking for modem at port COM3.
LOOKCOM4=Checking for modem at port COM4.
RESETCOM1=Resetting modem at port COM1.
RESETCOM2=Resetting modem at port COM2.
RESETCOM3=Resetting modem at port COM3.
RESETCOM4=Resetting modem at port COM4.
CHECKSPEEDMAX=Checking modem top speed.
CHECKDATARATE=Checking PC to modem data rate.
CHECKPHONELINE=Checking for a live phone line.
IDENTIFYMFG=Identifying modem manufacturer
IDENCOMPLETE=Identification Completed.
ENHANCEDMD=Performing Enhanced Diagnostics

[Field Profile]
Field1="slidshow.fss~registration",SLIDESHOW,201,6,6,162,151
;Field1="slidshow.fss~md",SLIDESHOW,201,6,6,162,151
Field2="Cancel",defpushbutton,2,117,190,50,14
Field3="",frame,-1,7,170,161,12
Field4="",ltext,900,8,171,156,10
