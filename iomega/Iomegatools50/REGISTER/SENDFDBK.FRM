[Misc]
Width=180
Height=215
token=sendfdbk
LocalSlideShow=900
SaveDatSection=Register
NextScreen=affthank

[OnExit]
Item1=Defaults,sendfdbk,FAIL,SCREEN,FDBKFAIL
Item2=Defaults,sendfdbk,CANCEL,SCREEN,FDBKCNCL
Item3=Defaults,Exitcode,2,SCREEN,FDBKCNCL

[Messages]
NOUI_MD=Performing Modem Diagnostics
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
XMSEND=Sending Offer Information
XMRECV=Receiving Special Offers
ZMSEND=Sending Offer Information
ZMRECV=Receiving Special Offers
DROPCARRIER=Lost Connection
NOUI_INIT=Initializing
NOUI_DIALING=Dialing Iomega toll-free
NOUI_SIGNON=Signing On
NOUI_LOGOFF=Signing Off
NOUI_FINISHED=Disconnecting

[Field Profile]
Field1="slidshow.fss~itp",SLIDESHOW,201,6,6,162,151
Field2="Cancel",defpushbutton,2,117,190,50,14
Field3="",frame,-1,7,170,161,12
Field4="",ltext,900,8,171,156,10
