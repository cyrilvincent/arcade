#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <dos.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>    
#include <memory.h>
#include <dpmi.h>
#include <sys/nearptr.h>
#include <go32.h>
#include <pc.h>
#include <audio.h>
#include <time.h>
#include <kb.h>


#define MAPSIZE 0x10000
#define DISPLAY_XSIZE_PIX 320
#define DISPLAY_YSIZE_PIX 200
#define DISPLAY_XSIZE_STAMP 40
#define DISPLAY_YSIZE_STAMP 24
#define DISPLAY_SIZE_PIX DISPLAY_XSIZE_PIX*DISPLAY_YSIZE_PIX
#define DISPLAY_SIZE_STAMP DISPLAY_XSIZE_STAMP*DISPLAY_YSIZE_STAMP
#define STAMP_XSIZE 8
#define STAMP_YSIZE 8
#define FALSE 0
#define TRUE 1

#define FRAMES_PER_SECOND 60
#define UCLOCKS_PER_FRAME (UCLOCKS_PER_SEC / FRAMES_PER_SECOND)

typedef unsigned char byte;
typedef unsigned short word;

byte proc_X;
byte proc_Y;
byte proc_A;
word proc_PC;
byte proc_N,proc_Z,proc_C,proc_I,proc_D,proc_V;
byte proc_SP;

byte *mem_map;
byte *screen;
byte *swap_screen;
byte *stampset;
byte *rom_char_set;

int irq, nmi;
int force_irq, force_nmi;
int video;
int trace;
int logevents;
int irq_rate;
int cpu_rate;
int speed_throttle;
int frameskip;
unsigned long instructions;
unsigned long totalcycles;
FILE *logfile;
int cursor_x, cursor_y;

unsigned int key;
 
byte old_stamps[DISPLAY_SIZE_STAMP];
int force_stamps;
int done;


