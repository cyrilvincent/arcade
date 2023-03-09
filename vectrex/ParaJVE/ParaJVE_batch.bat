@REM  ===========================================================================
@REM                ParaJVE Launching batch file (Windows only)
@REM  ===========================================================================
@REM  
@REM    You may use this file to start ParaJVE, if the provided EXE launcher(s)
@REM  do not work on your system,  or if you want to have a fine control of the
@REM  JVM invokation process (either to use a specific java virtual machine, or
@REM  to set additional JVM properties).
@REM  
@REM    This file uses the default java runtime ; hopefully it is a 1.5 JRE. If
@REM  not, ParaJVE will detect the mismatch, display an error message and exit.
@REM
@REM    Also, it disables the use of DirectDraw by Java  (forcing Java2D to use
@REM  GDI), for compatibility issues between DirectDraw and OpenGL.
@REM
@REM  ---------------------------------------------------------------------------
@REM  
@REM  You can append several optional parameters to this command-line. 
@REM  The list of the supported parameters is available in the User Guide.
@REM
@REM  ---------------------------------------------------------------------------
@REM
@start "ParaJVE" javaw -Djava.library.path=libs/natives -Dsun.java2d.noddraw=true -cp libs/ParaJVE.jar;libs/jogl.jar;libs/gluegen-rt.jar;libs/jinput.jar ParaJVE %*%