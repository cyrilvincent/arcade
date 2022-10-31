[Misc]
Width=366
Height=296
Bitmap=screen3.gif
WriteDisabled=0
NextScreen=modmdiag
;NextScreen=x25cntry
DatSection=Market
StretchBitmap=1

[OnExit]
Item1=Defaults,EXITCODE,2,SCREEN,io_cancl
Item2=*,*,*,READINI,MODEM,COMM PORT,PIPELINE.INI,Defaults,COMM PORT
Item3=Defaults,COMM PORT,@,SCREEN,x25cntry
Item4=Defaults,COMM PORT,@,WRITEDAT,Defaults,previous,1
Item5=Defaults,COMM PORT,@,WRITEINI,MISC,Previous,x25cntry.frm,Defaults,previous


[Field Profile]
Field1="Brand of Computer",combobox,400,212,66,137,60
Field2="How long used computer",dropdownlistbox,401,275,81,74,60
Field3="Processor",dropdownlistbox,402,162,98,46,60
Field4="Hard disk size",dropdownlistbox,403,279,98,70,60
Field5="Number of computers at home",EDIT,404,186,114,22,13
Field6="Number of computers at office",EDIT,405,264,114,22,13
Field7="Type of industry",combobox,406,238,135,110,90
Field8="Accounting",checkbox,410,27,171,47,8
Field9="Administration",checkbox,411,27,182,58,8
Field10="Business presentations",checkbox,412,27,193,86,8
Field11="CAD",checkbox,413,27,204,26,8
Field12="Contact manager/calendar",checkbox,414,27,215,98,8
Field13="Data communications",checkbox,415,27,226,80,8
Field14="Data or file management",checkbox,416,27,237,91,8
Field15="Database",checkbox,417,27,248,43,8
Field16="Desktop Publishing",checkbox,418,27,259,77,8
Field17="Education",checkbox,419,129,171,47,8
Field18="Engineering/scientific",checkbox,420,129,182,89,8
Field19="Financial",checkbox,421,129,193,89,8
Field20="Games/recreation",checkbox,422,129,204,89,8
Field21="Information services",checkbox,423,129,215,89,8
Field22="Legal",checkbox,424,129,226,31,8
Field23="Manufacturing/production",checkbox,425,129,237,93,8
Field24="Marketing/sales planning",checkbox,426,129,248,95,8
Field25="Multimedia/audio/video",checkbox,427,129,259,95,8
Field26="On-line/internet services",checkbox,428,239,171,91,8
Field27="Project management",checkbox,429,239,182,78,8
Field28="Record Keeping",checkbox,430,239,193,63,8
Field29="Word Processing",checkbox,431,239,204,67,8
Field30="Other: (please specify)",checkbox,432,239,215,103,8
Field31="Other",EDIT,435,248,225,93,12
Field32="With what brand of computer will your Zip drive be used?",ltext,-1,22,68,194,9
Field33="How long have you used the computer on which you will use your Zip drive?",ltext,-1,22,84,270,16
Field34="What processor does this computer have?",ltext,-1,22,100,139,8
Field35="Hard disk capacity:",ltext,-1,214,100,65,8
Field36="How many computers do you have in your home?",ltext,-1,22,116,163,8
Field37="in your office?",ltext,-1,215,116,48,8
Field38="If you plan to use your drive for business purposes, please select the description that best describes your company's industry:",ltext,-1,22,133,213,16
Field39="Please check all applications for which you use your computer && Zip drive.",ltext,-1,23,156,239,8
Field40="cancelb.gif","ownerdrawbutton",2,230,250,28,30
Field41="prrev.gif","ownerdrawbutton",10,273,250,34,30
Field42="continue.gif","defownerdrawbutton",1,320,250,35,30
[Inclusion]
432=435

[Values]
400=Acer,Apple,AST,Compaq,Dell,Digital,Gateway 2000,Hewlett-Packard,IBM,Micron,NEC,Packard-Bell,Power Computing,Toshiba,Other(type here)
401=Less than 1 month,1-6 months,7-11 months,1-2 years,2+ years
402=286,386,486,Pentium,680x0,PowerPC
403=Less than 200 MB,200-339 MB,340-539 MB,540-999 MB,1-2 GB,2+ GB
406=Aerospace,Accounting,Banking,Business Consulting,Communication,Computer Services,Database Analysis,Engineering,Government,Health Care,Higher Education,Image Bureau,Insurance,K-12 Education,Marketing,Manufacturing,Multimedia Developer,Network Management,Printer,Publisher,Real Estate,Video/Audio Production,Other(type here)

[ButtonDown]
1="continud.gif"
10="prev-dp.gif"
2="cancelbp.gif"

; Edit fields must be elaborated on here
[Edit Info]
404=NUMERIC,3,0
405=NUMERIC,3,0
435=EDIT,30,0
400=COMBOBOX,50,0
406=COMBOBOX,50,0
