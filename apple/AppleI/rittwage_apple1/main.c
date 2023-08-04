/* SimCon 2000
 * Copyright 1996,1998, Peter Rittwage
 *
 */

#include "simcon.h"

void init_vars(void);
void read_raw(byte *dest, byte *filename, int length);
void cleanup(char *problem);
extern int init_system(void);

int main(int argc, char *argv[])
{
   int x,loop;

   cursor_x=cursor_y=0;
   video=1;
   trace=0;
   logevents=0;
   speed_throttle=0;

   close_graphics();
   printf("Apple I Emulator\n");
   printf("Copyright 1999, Peter Rittwage\n");
   printf("\nOriginal Apple Hardware and Monitor\n");
   printf("Copyright 1975, Steve Wozniak\n");
   printf("\nPress a key to travel back in time...\n");
   getch();

   // Parse Arguments
   if(argc>1)
   {
      printf("\nParsing switches:\n");
      for(loop=1;loop<argc;loop++)
      {
         if(argv[loop][1]=='d')
         {
             video=0;
             trace=1;
         }
         if(argv[loop][1]=='?')
         {
             printf("Usage:\n-vXXX : XXX is vesa mode in hex\n");
             printf("-noaudio : disable audio support\n");
             printf("-mXXXX : amount of memory to use for buffering (debug tool)\n");
             exit(0);
         }
      }
      printf("\n");
   }

   __djgpp_nearptr_enable();

   printf("Allocating memory map\n");
   if(NULL==(mem_map=(byte *)malloc(MAPSIZE))) cleanup("out of memory");
   if(NULL==(swap_screen=(byte *)malloc(DISPLAY_SIZE_PIX))) cleanup("out of memory");
   if(NULL==(stampset=(byte *)malloc(0x1000))) cleanup("out of memory");

   if (kb_install(key) != 0)
      cleanup("Couldn't install keyboard handler !");

   for(x=0;x<MAPSIZE;x++) mem_map[x]=0xff;

   if(!init_system()) cleanup("couldn't initialize system");
   init_graphics();
   reset_processor();
   if(!video) close_graphics();
   go_6502();
   cleanup("normal exit");
}

void cleanup(char *problem)
{
   byte x;

   if(logevents) fclose(logfile);
   if(mem_map) free(mem_map);
   if(swap_screen) free(swap_screen);
   if(stampset) free(stampset);

   if(video) close_graphics();
   __djgpp_nearptr_disable();

//   printf("%s\n\n",problem);
   printf("halt: 0x%04x\n",proc_PC);
   printf("irq: 0x%02x%02x\nres: 0x%02x%02x\nnmi: 0x%02x%02x\n",
      mem_map[0xfffb],mem_map[0xfffa],mem_map[0xfffd],
      mem_map[0xfffc],mem_map[0xffff],mem_map[0xfffe]);
//   printf("irqr: %d cycles/frame\n",irq_rate);
   exit(0);
}

void read_raw(byte *dest, byte *filename, int length)
{
   FILE *myfile; 
   int filesize;
   
   if(NULL==(myfile=fopen(filename,"rb")))
      cleanup("missing rom(s)");

   filesize=fread(dest,1,length,myfile);
   if(filesize!=length)
      cleanup("problem with rom(s)");

   fclose(myfile);
}


