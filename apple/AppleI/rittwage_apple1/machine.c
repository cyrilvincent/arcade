/* Apple 1
 * Machine internals
 * (c) 1996,1998 Peter Rittwage
 */

#include "simcon.h"

void refresh(void);
void set_palette(byte entry, byte red, byte green, byte blue);
void clear_video(void);
byte read_memory(unsigned int address);
void set_memory(unsigned int address, byte value);
void check_controls(void);
void scroll(void);
int init_system(void);

int ignore_keypress;


void refresh(void)
{
   check_controls();
   throttle();
}

void set_palette(byte entry, byte red, byte green, byte blue)
{
   outportb(0x3c6,0xff);
   outportb(0x3c8,entry);
   outportb(0x3c9,red);
   outportb(0x3c9,green);
   outportb(0x3c9,blue);
}
      
byte read_memory(unsigned int address)
{
   char string[40];

   switch(address)
   {
      case 0xD010:
//         sprintf(string,"Read from keyboard");
//         if(video) Blit_String(0,24,string);
//         else printf(&string);
         mem_map[0xD011]=0x00;
         key=kb_getkey();
//         sprintf(string,"%d",key); Blit_String(0,24,string);
         return(key+0x80);
         break;

      case 0xD011:
//         sprintf(string,"Read from keyboard CR");
//         if(video) Blit_String(0,24,string);
//         else printf(&string);
         if(kb_kbhit()) mem_map[0xD011]=0x80;
         Blit_Char(cursor_x*8,cursor_y*8,127);
         return(mem_map[address]);
         break;

      case 0xD012:
//         sprintf(string,"Read from display");
//         if(video) Blit_String(0,24,string);
//         else printf(&string);
         return(mem_map[address]);
         break;

      case 0xD013:
//         sprintf(string,"Read from display CR");
//         if(video) Blit_String(0,24,string);
//         else printf(&string);
         return(mem_map[address]);
         break;

      default:
         return(mem_map[address]);
         break;
      }
}

void set_memory(unsigned int address, byte value)
{
   char string[40];

   switch(address)
   {
      case 0xD010:
//         sprintf(string,"Wrote to keyboard");
//         if(video) Blit_String(0,24,string);
//         else printf(&string);
         break;

      case 0xD011:
//         sprintf(string,"Wrote to keyboard CR");
//         if(video) Blit_String(0,24,string);
//         else printf(&string);
         break;

      case 0xD012:
//         sprintf(string,"Wrote to display");
         if(video)
         {
            if(value==0x8D) // Carriage Return
            {
               cursor_x=0;
               cursor_y++;
               if(cursor_y>23) { scroll(); cursor_y=23; }
            }
            else if(value==0x7F) // CLRSCN Command Sent
            {
              //memset(screen,0,320*200);
              //cursor_x=cursor_y=0;
            }
            else if(value==0xDF) cursor_x--; // Backspace Pressed
            else if(value==27+0x80); // ESC Pressed
            else if(value==60+0x80); // F1 Pressed
            else if(value==61+0x80); // F2 Pressed
            else if(value==62+0x80); // F3 Pressed
            else
            {
//               Blit_String(0,24,string);
               Blit_Char(cursor_x*STAMP_XSIZE,cursor_y*STAMP_YSIZE,value&=0x7F);
               cursor_x++;
               if(cursor_x>39) { cursor_x=0; cursor_y++; }
               if(cursor_y>23) { scroll(); cursor_y=23; }
            }
         }   
//         else printf(&string);
         break;

      case 0xD013:
//         sprintf(string,"Wrote to display CR");
//         if(video) Blit_String(0,24,string);
//         else printf(&string);
         break;

      default:
         mem_map[address]=value;
         break;
   }
   return;
}
void check_controls(void)
{
   kb_update();

   if(kb_key(KB_SCAN_F4)) { reset_processor(); ignore_keypress=1; }
   if(kb_key(KB_SCAN_F2)) { force_irq=1; ignore_keypress=1; }
   if(kb_key(KB_SCAN_F3)) { force_nmi=1; ignore_keypress=1; }
   if(kb_key(KB_SCAN_F1)) { done=1; ignore_keypress=1; }
}

int init_system(void)
{
   int x;

   read_raw(&mem_map[0xFF00],"monitor.bin",0x0100);
   read_raw(&stampset[0],"char.bin",0x0400);

   irq=FALSE;
   nmi=FALSE;

   cpu_rate=1000000;   /* 1.000MHz */
   irq_rate=cpu_rate/FRAMES_PER_SECOND;

   mem_map[0xD010]=0x00;
   mem_map[0xD011]=0x00;
   mem_map[0xD012]=0x00;
   mem_map[0xD013]=0x00;

   set_palette(255,63,63,63);

   return(TRUE);
}

void scroll(void)
{
   int index;

   for(index=0;index<23;index++)
      memcpy(screen+(index*320*8),screen+((index+1)*8*320),320*8);

   memset(screen+(23*320*8-1),0,320*8-1);
//   Blit_Char(26*STAMP_XSIZE,24*STAMP_YSIZE,'S');
}


