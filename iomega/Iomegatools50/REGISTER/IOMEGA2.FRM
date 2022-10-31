[Misc]
Width=366
Height=296
Bitmap=screen2.gif
nextscreen=iomega3
DatSection=Market
StretchBitmap=1

[OnExit]
Item1=Defaults,EXITCODE,2,SCREEN,io_cancl

[Field Profile]
Field1="Serial Number",EDIT,300,76,68,55,12
Field2="Purchase Month",dropdownlistbox,325,246,67,29,60
Field3="Purchase Year",EDIT,309,278,67,22,13
Field4="Which Zip drive did you purchase",dropdownlistbox,302,145,83,96,60
Field5="Where purchased",combobox,303,145,100,172,120
Field6="How hear",combobox,304,160,117,157,100
Field7="Influenced purchase",combobox,305,175,134,142,120
Field8="How many disks purchased with",EDIT,306,194,150,20,12
Field9="How many purchased since",EDIT,307,194,166,20,12
Field10="Plan to purchase",EDIT,308,235,182,20,12
Field11="Business",checkbox,320,30,209,66,8
Field12="Business in your home",checkbox,321,30,218,88,8
Field13="Home for personal use",checkbox,322,128,209,87,8
Field14="Home for work brought from office",checkbox,323,128,218,120,8
Field15="School",checkbox,324,256,209,66,8
Field16="Personal Funds",radio,330,134,231,61,8
Field17="Organizational Funds",radio,331,203,231,80,8
Field18="Company Size",dropdownlistbox,335,23,253,110,60
Field19="Serial Number:",ltext,-1,23,70,59,8
Field20="Which Zip drive did you purchase?",ltext,-1,23,87,116,8
Field21="Purchase Date:",ltext,-1,191,70,52,8
Field22="Where did you buy your Zip drive?",ltext,-1,23,104,114,8
Field23="How did you learn about your Zip drive?",ltext,-1,23,121,132,8
Field24="What factor most influenced your purchase?",ltext,-1,23,138,145,8
Field25="How many disks did you purchase with your drive?",ltext,-1,23,152,167,8
Field26="How many disks have you purchased since then? (not including the disks purchased with your drive)",ltext,-1,23,164,169,16
Field27="How many additional disks do you plan to buy in the next year?",ltext,-1,23,184,207,8
Field28="Which category best describes where you plan to use your Zip drive? (check all that apply)",ltext,-1,23,198,299,8
Field29="Was your drive purchased with?",ltext,-1,23,231,106,8
Field30="Please indicate the size of your company:",ltext,-1,23,243,139,8
Field31="month",ltext,-1,251,80,21,8
Field32="year",ltext,-1,282,80,16,8
Field33="cancelb.gif","ownerdrawbutton",2,230,250,28,30
Field34="prrev.gif","ownerdrawbutton",10,273,250,34,30
Field35="continue.gif","defownerdrawbutton",1,320,250,35,30

[Values]
302=Zip 100 Parallel Port,Zip 100 SCSI External,Zip 100 SCSI Internal,Zip 100 IDE Internal
303=" ",Best Buy,Circuit City,CompUSA,Computer City,Egghead Software,Fry's Electronic,Incredible Universe,Micro/Mac Warehouse,Office Depot,Office Max,PC/Mac connection,Staples,-Computer Dealer,-System Integrator,-Don't Know,Other(type here)
304=" ",Advertisement,Dealer Recommendation,Friend,Magazine Article,MIS Department,"On-line (e.g., Internet, AOL, CompuServe)",Trade Show,Other(type here)
305=" ",Capacity,Compatibility,Disk Price,Drive Price,Performance,Portability,Product Versatility,Protection,Reliability,Reputation,Other(type here)
325=" ",1,2,3,4,5,6,7,8,9,10,11,12
335="" ",1,2-9 employees,10-99 employees,100-499 employees,500-999 employees,"1,000 or more""

[Radio Groups]
Group1=330,331

[ButtonDown]
1="continud.gif"
10="prev-dp.gif"
2="cancelbp.gif"


; Edit fields must be elaborated on here
[Edit Info]
300=EDIT,20,0
309=NUMERIC,2,0
306=NUMERIC,3,0
307=NUMERIC,3,0
308=NUMERIC,3,0
303=COMBOBOX,50,0
304=COMBOBOX,50,0
305=COMBOBOX,50,0
302=DROPDOWNLISBOX,100,1

[Masks]
301=MY


