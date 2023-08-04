CC	= gcc -O2 -m486 -funroll-loops -fomit-frame-pointer
OBJECTS	= main.o video.o machine.o 6502.o 
LIBS	= c:/djgpp/lib/libkb.a


apple1:	${OBJECTS}	
	${CC} -s -o apple1.exe ${OBJECTS} ${LIBS}

main.o:		main.c simcon.h
video.o:	video.c simcon.h
machine.o:	machine.c simcon.h
6502.o:		6502.c 6502.h simcon.h

