@echo off
REM
REM ADTPro - Windows startup batch file
REM
REM Note:
REM   Invoke with the name of the communications button to push
REM   in order to start with that mode active (i.e. 'adtpro ethernet')

SET ADTPRO_HOME=%CD%\

REM You can set two variables here:
REM   1. %JAVA_HOME% - to pick a particular java to run under
REM   2. %ADTPRO_HOME% - to say where you installed ADTPro
REM
REM e.g. uncomment (remove the "REM" from in front of) and
REM      customize the following SET statements.  
REM Note: They must have a trailing backslash as in the examples!
REM 
SET ADTPRO_HOME=C:\Users\conta\git-CVC\Retro\gitarcade\AppleII\ADTPro-2.1.0\
SET MY_JAVA_HOME=C:\Progra~1\Java\jdk-18.0.2.1\bin\


:start
CD "%ADTPRO_HOME%"
start %MY_JAVA_HOME%java -Xms128m -Xmx256m %ADTPRO_EXTRA_JAVA_PARMS% -cp "%ADTPRO_HOME%lib\ADTPro-2.1.0.jar";"%ADTPRO_HOME%lib\AppleCommander\AppleCommander-1.3.5.13-ac.jar";"%ADTPRO_HOME%lib\jssc\jssc-2.9.2.jar";"%ADTPRO_HOME%lib\jssc\slf4j-nop-1.7.9.jar" org.adtpro.ADTPro %*
