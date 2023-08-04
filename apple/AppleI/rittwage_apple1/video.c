#include "simcon.h"

void wait_retrace(void);
void init_graphics(void);
void close_graphics(void);
void do_mode13h(void);
void Blit_Char(int xc, int yc, char c);
void Blit_String(int x, int y, char *string);


void throttle(void)
{
   #define MEMORY 10
   
   uclock_t curr,mtpf;
   static uclock_t prev[MEMORY];
   static int i,fps;
   char string[16];

   do
   {
      curr = uclock();
   } while ((speed_throttle) && (curr - prev[i]) < 
        UCLOCKS_PER_SEC/FRAMES_PER_SECOND);

   i = (i+1) % MEMORY;
   mtpf = ((curr - prev[i])/(MEMORY))/2;

   if (mtpf) fps = (UCLOCKS_PER_SEC+mtpf)/2/mtpf;
      prev[i] = curr;

   sprintf(string,"%4x",proc_PC);
   Blit_String(35,24,string);
//   sprintf(string,"%4d",fps);
//   Blit_String(28,24,string);
}

void Blit_Char(int xc, int yc, char c)
{
   int offset,x,y;
   unsigned char *work_char;
   unsigned char bit_mask = 0x80;

   work_char = stampset + (c * 8);
   offset = (yc << 8) + (yc << 6) + xc;

   for (y=0; y<8; y++)
   {
      bit_mask = 0x80;
      for (x=8; x>0; x--)
      {
         if ((*work_char & bit_mask)) screen[offset+x]=255;
         else screen[offset+x]=0;

         bit_mask = (bit_mask>>1);
      }
      offset += 320;
      work_char++;
   }
}

void Blit_String(int x, int y, char *string)
{
   int index;

   for(index=0; string[index]!=0; index++)
      Blit_Char(((x*STAMP_XSIZE)+(index<<3)),y*STAMP_YSIZE,string[index]);
}



void init_graphics(void)
{
   do_mode13h();
   rom_char_set=(unsigned char *)0xf0000 +
      __djgpp_conventional_base + 0xfa6e;

}
 
void close_graphics(void)
{
   __dpmi_regs reg;

   reg.x.ax = 0x0003;
   __dpmi_int(0x10,&reg);
}

void do_mode13h(void)
{
   __dpmi_regs reg;

   reg.x.ax = 0x0013;
   __dpmi_int(0x10,&reg);

   screen = (char *) 0xa0000 + __djgpp_conventional_base;
}


