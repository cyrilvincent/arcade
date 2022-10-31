[Misc]
Width=366
Height=296
Bitmap=screen1.gif
WriteDisabled=0
nextscreen=iomega2
DatSection=Register
StretchBitmap=1

[OnExit]
Item1=Defaults,EXITCODE,2,SCREEN,io_cancl

[Field Profile]
Field1="First Name",EDIT,201,63,72,106,11
Field2="Last Name",EDIT,203,230,72,106,11
Field3="Title",EDIT,205,63,87,106,11
Field4="Company",EDIT,204,230,86,106,11
Field5="Address and phone",dropdownlistbox,230,63,101,68,64
Field6="Street Address",EDIT,213,63,117,106,12
Field7="Apartment Number",EDIT,231,228,118,25,11
Field8="City",EDIT,215,63,133,106,12
Field9="State/Province",EDIT,216,228,134,17,11
Field10="Zip Code",EDIT,217,270,133,48,12
Field11="Phone Number",EDIT,207,63,148,100,12
Field12="Fax Number",EDIT,210,228,148,100,12
Field13="E-Mail Address",EDIT,219,63,164,155,12
Field14="Mail",checkbox,285,250,178,29,8
Field15="Fax",checkbox,286,286,178,24,8
Field16="E-Mail",checkbox,287,317,178,31,8
Field17="Occupation",combobox,220,63,187,126,60
Field18="Household Income",dropdownlistbox,221,286,188,63,70
Field19="Birth Month",dropdownlistbox,222,63,203,25,60
Field20="Birth Year",EDIT,223,102,203,21,12
Field21="M",radio,226,162,210,16,8
Field22="F",radio,227,182,210,16,8
Field23="Married",radio,224,272,210,37,8
Field24="Single",radio,225,314,210,30,8
Field25="No children in household",checkbox,240,20,235,92,8
Field26="M",radio,241,35,247,18,10
Field27="F",radio,242,55,247,16,10
Field28="Month",edit,243,74,245,25,12
Field29="M",radio,251,35,261,18,10
Field30="F",radio,252,55,261,16,10
Field31="Month",EDIT,253,74,259,25,12
Field32="M",radio,261,35,275,18,10
Field33="F",radio,262,55,275,16,10
Field34="Month",EDIT,263,74,273,25,12
Field35="First Name:",rtext,-1,12,75,47,8
Field36="Last Name:",rtext,-1,185,73,39,8
Field37="Title:",rtext,-1,12,89,47,8
Field38="Company:",rtext,-1,185,86,39,8
Field39="Street Address:",rtext,-1,7,118,52,8
Field40="Apt#",rtext,-1,207,121,17,8
Field41="City:",rtext,-1,12,134,47,8
Field42="State/Province:",rtext,-1,172,135,52,8
Field43="Zip:",ltext,-1,253,135,15,8
Field44="Phone Number:",rtext,-1,7,149,52,8
Field45="Fax:",ltext,-1,210,150,16,8
Field46="E-Mail:",rtext,-1,10,165,50,8
Field47="Occupation",rtext,-1,12,187,47,8
Field48="Household Income: $",ltext,-1,212,191,70,8
Field49="Date of Birth",rtext,-1,12,206,47,8
Field50="What is the Gender and Age of children living in your household?",ltext,-1,13,225,337,8
Field51="1.",ltext,-1,21,247,9,10
Field52="2.",ltext,-1,21,261,9,10
Field53="3.",ltext,-1,21,275,9,10
Field54="Month",ctext,-1,62,216,24,8
Field55="Year",ltext,-1,104,216,23,8
Field56="This is my",ltext,-1,24,104,37,8
Field57="phone and address.",ltext,-1,136,104,72,8
Field58=" ",ctext,-1,92,210,8,9
Field59="",groupbox,-1,155,202,46,20
Field60="",groupbox,-1,268,202,81,20
Field61="Years",ltext,-1,103,248,20,7
Field62="Years",ltext,-1,103,262,20,7
Field63="Years",ltext,-1,103,276,20,7
Field64="cancelb.gif","ownerdrawbutton",2,230,250,28,30
Field65="continue.gif","defownerdrawbutton",1,320,250,35,30
Field66="Sex:",ltext,-1,136,210,14,7
Field67="Marital Status:",ltext,-1,218,210,66,7
Field68="How should we notify you of updates and special offers?",ltext,-1,62,177,185,8

[ButtonDown]
1="continud.gif"
10="prev-dp.gif"
2="cancelbp.gif"

[Radio Groups]
Group1=224,225
Group2=226,227
Group3=241,242
Group4=251,252
Group5=261,262

[Exclusion]
240=241,242,243,244,251,252,253,254,261,262,263,264

[Values]
230=Company,Home,Home Business 
222=" ",1,2,3,4,5,6,7,8,9,10,11,12
243=" ",1,2,3,4,5,6,7,8,9,10,11,12
253=" ",1,2,3,4,5,6,7,8,9,10,11,12
263=" ",1,2,3,4,5,6,7,8,9,10,11,12
220=" ",Clerical/Service,Finance,Management,Manufacturing/Production,Marketing,Professional,Sales,Technical,Homemaker,Student,Retired,Other(type here)
221="" ","0-24,999","25,000-49,999","50,000-74,999","75,000-99,999","100,000 +"

; Edit fields must be elaborated on here
[Edit Info]
201=CHAR,15,1
203=CHAR,20,1
205=CHAR,30,0
204=ALPHANUM,30,0
213=EDIT,50,1
231=EDIT,5,0
215=CHAR,30,1
216=CHARCAPS,2,1
217=NUMCAPS,10,1
206=EDIT,10,1
207=SSNO,28,0
209=EDIT,10,0
210=SSNO,28,0
219=EDIT,50,0
;221=NUMERIC,10,1
223=NUMERIC,2,0
244=NUMERIC,2,0
254=NUMERIC,2,0
264=NUMERIC,2,0
220=COMBOBOX,50,0
243=NUMERIC,2,0
253=NUMERIC,2,0
263=NUMERIC,2,0
