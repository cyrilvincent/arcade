[Misc]
Width=180
Height=215
token=sendreg
LocalSlideShow=900
SaveDatSection=Register
nextscreen=thanks

[OnExit]
Item1=Defaults,SENDREG,FAIL,SCREEN,RETRYMDM
Item2=Defaults,SENDREG,CANCEL,SCREEN,IO_CANCL

[Messages]
NOUI_MD=Performing Modem Diagnostics
XMRECV=Receiving Special Offers
ZMRECV=Receiving Special Offers
;XMSEND=Sending Registration
;ZMSEND=Sending Registration
DROPCARRIER=Lost Connection
;OFFHOOK=Dialing Iomega
NOUI_INIT=Initializing
NOUI_DIALING=Dialing Iomega toll-free
NOUI_SIGNON=Signing On
NOUI_BEGINREG=Sending Registration
NOUI_LOGOFF=Signing Off
NOUI_FINISHED=Disconnecting

[Field Profile]
Field1="slidshow.fss~registration",SLIDESHOW,201,6,6,162,151
Field2="Cancel",defpushbutton,2,117,190,50,14
Field3="",frame,-1,7,170,161,12
Field4="",ltext,900,8,171,156,10
