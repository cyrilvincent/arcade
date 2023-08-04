/* 6502 processor code
 * Copyright 1996,1998 Peter Rittwage
 * Developed for the Generic PCB emulator
 */

#include "simcon.h"
#include "6502.h"
#include "opcodes.h"


void compare(byte val1, byte val2);
void push(byte val);
byte pop(void);
void reset_processor(void);

extern void refresh(void);
extern byte read_memory(word);
extern void set_memory(word,byte);

byte cycle_table[256] =
{
   6,6,1,1,1,3,5,1,3,2,2,1,1,4,6,1, 
   2,5,1,1,1,4,6,1,2,4,1,1,1,4,7,1,
   6,6,1,1,3,3,5,1,4,2,2,1,4,4,6,1,
   2,5,1,1,1,4,6,1,2,4,1,1,1,4,7,1,
   7,6,1,1,1,3,5,1,3,2,2,1,3,4,6,1,   
   2,5,1,1,1,4,6,1,15,4,1,1,1,4,7,1,
   6,6,1,1,1,3,5,1,4,2,2,1,5,4,6,1,
   2,5,1,1,1,4,6,1,2,4,1,1,1,4,7,1,
   1,6,1,1,3,3,3,1,2,1,2,1,4,4,4,1, 
   2,6,1,1,4,4,4,1,2,5,2,1,1,5,1,1,
   2,6,2,1,3,3,3,1,2,2,2,1,4,4,4,1,
   2,5,1,1,4,4,4,1,2,4,2,1,4,4,4,1,   
   2,6,1,1,3,3,5,1,2,2,2,1,4,4,6,1,   
   2,5,1,1,1,4,6,1,2,4,1,1,1,4,7,1,
   2,6,1,1,3,3,5,1,2,2,2,1,4,4,6,1,
   2,5,1,1,1,4,6,1,2,4,1,1,1,4,7,1
};

inline unsigned int do_abs(void)
{
   unsigned int address;
   byte lowbyte, hibyte;

   lowbyte=mem_map[proc_PC++];
   hibyte=mem_map[proc_PC++];
   address=(hibyte<<8|lowbyte);
   return(address);
}

inline unsigned int do_absx(void)
{
   unsigned int address;
   byte lowbyte, hibyte;

   lowbyte=mem_map[proc_PC++];
   hibyte=mem_map[proc_PC++];
   address=(hibyte<<8|lowbyte)+proc_X;
   return(address);
}

inline unsigned int do_absy(void)
{
   unsigned int address;
   byte lowbyte, hibyte;

   lowbyte=mem_map[proc_PC++];
   hibyte=mem_map[proc_PC++];
   address=(hibyte<<8|lowbyte)+proc_Y;
   return(address);
}

inline unsigned int do_zero(void)
{
   unsigned int address;
   
   address=mem_map[proc_PC++];
   return(address);
}

inline unsigned int do_zerox(void)
{
   unsigned int address;
   
   address=(mem_map[proc_PC++]+proc_X) & 0xff;
   return(address);
}

inline unsigned int do_zeroy(void)
{
   unsigned int address;
   
   address=(mem_map[proc_PC++]+proc_Y) & 0xff;
   return(address);
}

inline unsigned int do_indx(void)
{
   unsigned int address;
   byte lowbyte, hibyte;

   address=(mem_map[proc_PC++]+proc_X) & 0xff;
   lowbyte=mem_map[address++];
   hibyte=mem_map[address];
   address=(hibyte<<8|lowbyte);
   return(address);
}

inline unsigned int do_indy(void)
{
   unsigned int address;
   byte lowbyte, hibyte;

   address=mem_map[proc_PC++];
   lowbyte=mem_map[address++];
   hibyte=mem_map[address];
   address=(hibyte<<8|lowbyte)+proc_Y;
   return(address);
}


unsigned long go_6502(void)
{
   byte lowbyte,hibyte;
   unsigned int address;
   byte unsignedvalue, spareunsigned;
   char signedvalue;
   byte opcode;
   int irq_cycles;

   done=instructions=0;
  
   while(!done)
   {
      if(trace)
      {
         printf("PC:%0.4x SP:%0.2x A:%0.2x X:%0.2x Y:%0.2x N:%0.2x Z:%0.2x C:%0.2x I:%0.2x D:%0.2x V:%0.2x\n",proc_PC,proc_SP,proc_A,proc_X,proc_Y,proc_N,proc_Z,proc_C,proc_I,proc_D,proc_V);
      }
      refresh();

      /* Regular IRQ */
      if(((!TST_I)&&(irq))||(force_irq))
      {
         force_irq=0;

         push(proc_PC >> 8);
         push(proc_PC & 0xff);
         unsignedvalue=FLAGS_TO_BYTE;
         push(unsignedvalue);
         
         SET_I;
         lowbyte=mem_map[0xfffe];
         hibyte=mem_map[0xffff];
         proc_PC=hibyte<<8|lowbyte;
      }

      /* NMI */
      if(force_nmi)
      {
         force_nmi=0;

         push(proc_PC >> 8);
         push(proc_PC & 0xff);
         unsignedvalue=FLAGS_TO_BYTE;
         push(unsignedvalue);
         
         SET_I;
         lowbyte=mem_map[0xfffa];
         hibyte=mem_map[0xfffb];
         proc_PC=hibyte<<8|lowbyte;
      }

      opcode=mem_map[proc_PC++];
      totalcycles+=cycle_table[opcode];

      switch(opcode)
      {
         case OP_LDA_IMMEDIATE:
            proc_A=mem_map[proc_PC++];
            SETFLAGS(proc_A);
            break;

         case OP_STA_INDIRECT_Y:
            set_memory(do_indy(),proc_A);
            break;
		
         case OP_LDY_IMMEDIATE:
            proc_Y=mem_map[proc_PC++];
            SETFLAGS(proc_Y);
            break;
		
         case OP_LDX_IMMEDIATE:
            proc_X=mem_map[proc_PC++];
            SETFLAGS(proc_X);
            break;
											
         case OP_LDA_ABSOLUTE_0:
            proc_A=read_memory(do_abs());
            SETFLAGS(proc_A);
            break;

         case OP_LDA_ABSOLUTE_X:
            proc_A=read_memory(do_absx());
            SETFLAGS(proc_A);
            break;

         case OP_LDA_ABSOLUTE_Y:
            proc_A=read_memory(do_absy());
            SETFLAGS(proc_A);
            break;

         case OP_LDA_INDIRECT_X:
            proc_A=read_memory(do_indx());
            SETFLAGS(proc_A);
            break;

         case OP_LDA_INDIRECT_Y:
            proc_A=read_memory(do_indy());
            SETFLAGS(proc_A);
            break;

         case OP_STY_ABSOLUTE:
            set_memory(do_abs(),proc_Y);
            break;

         case OP_STA_ABSOLUTE_0:
            set_memory(do_abs(),proc_A);
            break;

         case OP_STA_ABSOLUTE_X:
            set_memory(do_absx(),proc_A);
            break;

         case OP_STA_ABSOLUTE_Y:
            set_memory(do_absy(),proc_A);
            break;

         case OP_STX_ABSOLUTE:
            set_memory(do_abs(),proc_X);
            break;
		
         case OP_BNE:
            signedvalue=mem_map[proc_PC++];
            if(!TST_Z) proc_PC+=signedvalue;
            break;

         case OP_BEQ:
            signedvalue=mem_map[proc_PC++];
            if(TST_Z) proc_PC+=signedvalue;
            break;

         case OP_BCC:
            signedvalue=mem_map[proc_PC++];
            if(!TST_C) proc_PC+=signedvalue;
            break;

         case OP_BCS:
            signedvalue=mem_map[proc_PC++];
            if(TST_C) proc_PC+=signedvalue;
            break;

         case OP_BMI:
            signedvalue=mem_map[proc_PC++];
            if(TST_N) proc_PC+=signedvalue;
            break;

         case OP_BPL:
            signedvalue=mem_map[proc_PC++];
            if(!TST_N) proc_PC+=signedvalue;
            break;

         case OP_BVC:
            signedvalue=mem_map[proc_PC++];
            if(!TST_V) proc_PC+=signedvalue;
            break;

         case OP_BVS:
            signedvalue=mem_map[proc_PC++];
            if(TST_V) proc_PC+=signedvalue;
            break;
         
         case OP_INY:
            proc_Y++;
            SETFLAGS(proc_Y);
            break;

         case OP_INX:
            proc_X++;
            SETFLAGS(proc_X);
            break;

         case OP_INC_ABSOLUTE_0:
            address=do_abs();
            unsignedvalue=read_memory(address);
            unsignedvalue++;
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue);
            break;

         case OP_INC_ABSOLUTE_X:
            address=do_absx();
            unsignedvalue=read_memory(address);
            unsignedvalue++;
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue);
            break;

         case OP_DEC_ZERO_0:
            address=do_zero();
            unsignedvalue=read_memory(address);
            unsignedvalue--;
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue);
            break;

         case OP_DEC_ZERO_X:
            address=do_zerox();
            unsignedvalue=read_memory(address);
            unsignedvalue--;
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue);
            break;

         case OP_INC_ZERO_0:
            address=do_zero();
            unsignedvalue=read_memory(address);
            unsignedvalue++;
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue);
            break;
                   
         case OP_INC_ZERO_X:
            address=do_zerox();
            unsignedvalue=read_memory(address);
            unsignedvalue++;
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue);
            break;

         case OP_LDA_ZERO_0:
            proc_A=read_memory(do_zero());
            SETFLAGS(proc_A);
            break;

         case OP_LDX_ZERO_0:
            proc_X=read_memory(do_zero());
            SETFLAGS(proc_X);
            break;

         case OP_LDY_ZERO_0:
            proc_Y=read_memory(do_zero());
            SETFLAGS(proc_Y);
            break;

         case OP_LDA_ZERO_X:
            proc_A=read_memory(do_zerox());
            SETFLAGS(proc_A);
            break;

         case OP_LDY_ZERO_X:
            proc_Y=read_memory(do_zerox());
            SETFLAGS(proc_Y);
            break;

         case OP_LDX_ZERO_Y:
            proc_X=read_memory(do_zeroy());
            SETFLAGS(proc_X);
            break;

         case OP_DEY:
            proc_Y--;
            SETFLAGS(proc_Y);
            break;

         case OP_DEX:
            proc_X--;
            SETFLAGS(proc_X);
            break;

         case OP_DEC_ABSOLUTE_0:
            address=do_abs();
            unsignedvalue=read_memory(address);
            unsignedvalue--;
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue);
            break;

         case OP_DEC_ABSOLUTE_X:
            address=do_absx();
            unsignedvalue=read_memory(address);
            unsignedvalue--;
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue);
            break;

         case OP_CMP_ABSOLUTE_0:
            unsignedvalue=read_memory(do_abs());
            compare(proc_A,unsignedvalue);
            break;

         case OP_CMP_ABSOLUTE_Y:
            unsignedvalue=read_memory(do_absy());
            compare(proc_A,unsignedvalue);
            break;

         case OP_CMP_ABSOLUTE_X:
            unsignedvalue=read_memory(do_absx());
            compare(proc_A,unsignedvalue);
            break;

         case OP_CPX_ABSOLUTE:
            unsignedvalue=read_memory(do_abs());
            compare(proc_X,unsignedvalue);
            break;

         case OP_CPY_ABSOLUTE:
            unsignedvalue=read_memory(do_abs());
            compare(proc_Y,unsignedvalue);
            break;

         case OP_CMP_IMMEDIATE:
            unsignedvalue=mem_map[proc_PC++];
            compare(proc_A,unsignedvalue);
            break;

         case OP_CMP_ZERO_0:
            unsignedvalue=read_memory(do_zero());
            compare(proc_A,unsignedvalue);
            break;

         case OP_CMP_ZERO_X:
            unsignedvalue=read_memory(do_zerox());
            compare(proc_A,unsignedvalue);
            break;

         case OP_CMP_INDIRECT_Y:
            unsignedvalue=read_memory(do_indy());
            compare(proc_A,unsignedvalue);
            break;

         case OP_CMP_INDIRECT_X:
            unsignedvalue=read_memory(do_indx());
            compare(proc_A,unsignedvalue);
            break;

         case OP_CPX_ZERO:
            unsignedvalue=read_memory(do_zero());
            compare(proc_X,unsignedvalue);
            break;

         case OP_CPY_ZERO:
            unsignedvalue=read_memory(do_zero());
            compare(proc_Y,unsignedvalue);
            break;

         case OP_CPX_IMMEDIATE:
            unsignedvalue=mem_map[proc_PC++];
            compare(proc_X,unsignedvalue);
            break;

         case OP_CPY_IMMEDIATE:
            unsignedvalue=mem_map[proc_PC++];
            compare(proc_Y,unsignedvalue);
            break;

         case OP_LDX_ABSOLUTE_0:
            proc_X=read_memory(do_abs());
            SETFLAGS(proc_X);
            break;

         case OP_LDY_ABSOLUTE_0:
            proc_Y=read_memory(do_abs());
            SETFLAGS(proc_Y);
            break;

         case OP_LDY_ABSOLUTE_X:
            proc_Y=read_memory(do_absx());
            SETFLAGS(proc_Y);
            break;
         
         case OP_JMP_ABSOLUTE:
            proc_PC=do_abs();
            break;

         case OP_JMP_INDIRECT:
            address=do_abs();
            lowbyte=mem_map[address++];
            hibyte=mem_map[address];
            proc_PC=(hibyte<<8|lowbyte);
            break;
      
         case OP_JSR:
            address=do_abs();
            proc_PC--;
            push(proc_PC >> 8);
            push(proc_PC & 0xff);
            proc_PC=address;
            break;

         case OP_RTS:
            lowbyte=pop();
            hibyte=pop();
            proc_PC=(hibyte<<8|lowbyte);
            proc_PC++;
            break;

         case OP_RTI:
            unsignedvalue=pop();
            BYTE_TO_FLAGS(unsignedvalue);
            lowbyte=pop();
            hibyte=pop();
            proc_PC=(hibyte<<8|lowbyte);
            irq_cycles=0;
            break;

         case OP_STA_ZERO_0:
            set_memory(do_zero(),proc_A);
            break;

         case OP_STX_ZERO_0:
            set_memory(do_zero(),proc_X);
            break;

         case OP_STX_ZERO_Y:
            set_memory(do_zeroy(),proc_X);
            break;

         case OP_STY_ZERO_0:
            set_memory(do_zero(),proc_Y);
            break;

         case OP_STY_ZERO_X:
            set_memory(do_zerox(),proc_Y);
            break;

         case OP_STA_ZERO_X:
            set_memory(do_zerox(),proc_A);
            break;

         case OP_STA_INDIRECT_X:
            set_memory(do_indx(),proc_A);
            break;

         case OP_TYA:
            proc_A=proc_Y;
            SETFLAGS(proc_A);
            break;

         case OP_TXS:
            proc_SP=proc_X;
            break;

         case OP_TXA:
            proc_A=proc_X;
            SETFLAGS(proc_A);
            break;

         case OP_TSX:
            proc_X=proc_SP;
            SETFLAGS(proc_X);
            break;

         case OP_TAY:
            proc_Y=proc_A;
            SETFLAGS(proc_Y);
            break;

         case OP_TAX:
            proc_X=proc_A;
            SETFLAGS(proc_X);
            break;

         case OP_CLD:
            CLR_D;
            break;

         case OP_CLC:
            CLR_C;
            break;

         case OP_CLI:
            CLR_I;
            break;

         case OP_CLV:
            CLR_V;
            break;

         case OP_AND_IMMEDIATE:
            unsignedvalue=mem_map[proc_PC++];
            proc_A&=unsignedvalue;
            SETFLAGS(proc_A);
            break;

         case OP_AND_ZERO_0:
            unsignedvalue=read_memory(do_zero());
            proc_A&=unsignedvalue;
            SETFLAGS(proc_A);
            break;

         case OP_AND_ZERO_X:
            unsignedvalue=read_memory(do_zerox());
            proc_A&=unsignedvalue;
            SETFLAGS(proc_A);
            break;

         case OP_AND_ABSOLUTE_0:
            unsignedvalue=read_memory(do_abs());
            proc_A&=unsignedvalue;
            SETFLAGS(proc_A);
            break;

         case OP_AND_ABSOLUTE_X:
            unsignedvalue=read_memory(do_absx());
            proc_A&=unsignedvalue;
            SETFLAGS(proc_A);
            break;

         case OP_AND_ABSOLUTE_Y:
            unsignedvalue=read_memory(do_absy());
            proc_A&=unsignedvalue;
            SETFLAGS(proc_A);
            break;
                   
         case OP_ORA_IMMEDIATE:
            unsignedvalue=mem_map[proc_PC++];
            proc_A|=unsignedvalue;
            SETFLAGS(proc_A);
            break;

         case OP_ORA_ZERO_0:
            unsignedvalue=read_memory(do_zero());
            proc_A|=unsignedvalue;
            SETFLAGS(proc_A);
            break;

         case OP_ORA_ZERO_X:
            unsignedvalue=read_memory(do_zerox());
            proc_A|=unsignedvalue;
            SETFLAGS(proc_A);
            break;
         
         case OP_ORA_ABSOLUTE_0:
            unsignedvalue=read_memory(do_abs());
            proc_A|=unsignedvalue;
            SETFLAGS(proc_A);
            break;

         case OP_ORA_ABSOLUTE_X:
            unsignedvalue=read_memory(do_absx());
            proc_A|=unsignedvalue;
            SETFLAGS(proc_A);
            break;

         case OP_ORA_ABSOLUTE_Y:
            unsignedvalue=read_memory(do_absy());
            proc_A|=unsignedvalue;
            SETFLAGS(proc_A);
            break;

         case OP_ORA_INDIRECT_Y:
            unsignedvalue=read_memory(do_indy());
            proc_A|=unsignedvalue;
            SETFLAGS(proc_A);
            break;

         case OP_EOR_IMMEDIATE:
            unsignedvalue=mem_map[proc_PC++];
            proc_A^=unsignedvalue;
            SETFLAGS(proc_A);
            break;

         case OP_EOR_ZERO_0:
            unsignedvalue=read_memory(do_zero());
            proc_A^=unsignedvalue;
            SETFLAGS(proc_A);
            break;

         case OP_EOR_ZERO_X:
            unsignedvalue=read_memory(do_zerox());
            proc_A^=unsignedvalue;
            SETFLAGS(proc_A);
            break;

         case OP_EOR_ABSOLUTE_0:
            unsignedvalue=read_memory(do_abs());
            proc_A^=unsignedvalue;
            SETFLAGS(proc_A);
            break;

         case OP_EOR_ABSOLUTE_X:
            unsignedvalue=read_memory(do_absx());
            proc_A^=unsignedvalue;
            SETFLAGS(proc_A);
            break;

         case OP_EOR_ABSOLUTE_Y:
            unsignedvalue=read_memory(do_absy());
            proc_A^=unsignedvalue;
            SETFLAGS(proc_A);
            break;

         case OP_EOR_INDIRECT_X:
            unsignedvalue=read_memory(do_indx());
            proc_A^=unsignedvalue;
            SETFLAGS(proc_A);
            break;

         case OP_EOR_INDIRECT_Y:
            unsignedvalue=read_memory(do_indy());
            proc_A^=unsignedvalue;
            SETFLAGS(proc_A);
            break;

         case OP_ASL_ZERO_0:
            address=do_zero();
            unsignedvalue=read_memory(address);
            STO_C (unsignedvalue & 0x80);
            unsignedvalue=(unsignedvalue<<1);
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue);
            break;

         case OP_ASL_ZERO_X:
            address=do_zerox();
            unsignedvalue=read_memory(address);
            STO_C (unsignedvalue & 0x80);
            unsignedvalue=(unsignedvalue<<1);
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue);
            break;

         case OP_ASL_ABSOLUTE_X:
            address=do_absx();
            unsignedvalue=read_memory(address);
            STO_C (unsignedvalue & 0x80);
            unsignedvalue=(unsignedvalue<<1);
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue);
            break;

         case OP_ASL_A:
            STO_C (proc_A & 0x80);
            proc_A=(proc_A<<1);
            SETFLAGS(proc_A);
            break;
                      
         case OP_ROL_A:
            spareunsigned=TST_C;
            STO_C (proc_A & 0x80);
            proc_A=(proc_A<<1);
            proc_A |= spareunsigned; 
            SETFLAGS(proc_A);
            break;
                        
         case OP_ROL_ZERO_0:
            address=do_zero();
            unsignedvalue=read_memory(address);
            spareunsigned=TST_C;
            STO_C (unsignedvalue & 0x80);
            unsignedvalue=(unsignedvalue<<1);
            unsignedvalue |= spareunsigned; 
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue);
            break;

         case OP_ROL_ZERO_X:
            address=do_zerox();
            unsignedvalue=read_memory(address);
            spareunsigned=TST_C;
            STO_C (unsignedvalue & 0x80);
            unsignedvalue=(unsignedvalue<<1);
            unsignedvalue |= spareunsigned; 
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue);
            break;

         case OP_ROL_ABSOLUTE_X:
            address=do_absx();
            unsignedvalue=read_memory(address);
            spareunsigned=TST_C;
            STO_C (unsignedvalue & 0x80);
            unsignedvalue=(unsignedvalue<<1);
            unsignedvalue |= spareunsigned; 
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue);
            break;

         case OP_ROR_A:
            spareunsigned=TST_C;
            STO_C (proc_A & 0x01); 
            proc_A>>=1; 
            if (spareunsigned) proc_A |= 0x80; 
            SETFLAGS(proc_A); 
            break;

         case OP_ROR_ZERO_0:
            address=do_zero();
            unsignedvalue=read_memory(address);
            spareunsigned=TST_C;
            STO_C (unsignedvalue & 0x01); 
            unsignedvalue>>=1; 
            if (spareunsigned) unsignedvalue |= 0x80; 
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue); 
            break;

         case OP_ROR_ZERO_X:
            address=do_zerox();
            unsignedvalue=read_memory(address);
            spareunsigned=TST_C;
            STO_C (unsignedvalue & 0x01); 
            unsignedvalue>>=1; 
            if (spareunsigned) unsignedvalue |= 0x80;
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue); 
            break;

         case OP_ROR_ABSOLUTE_X:
            address=do_absx();
            unsignedvalue=read_memory(address);
            spareunsigned=TST_C;
            STO_C (unsignedvalue & 0x01); 
            unsignedvalue>>=1; 
            if (spareunsigned) unsignedvalue |= 0x80;
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue); 
            break;

         case OP_LSR_A:
            STO_C (proc_A & 0x01); 
            proc_A>>=1;
            SETFLAGS(proc_A);
            break;

         case OP_LSR_ZERO_0:
            address=do_zero();
            unsignedvalue=read_memory(address);
            STO_C (unsignedvalue & 0x01); 
            unsignedvalue>>=1;
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue);
            break;

         case OP_LSR_ZERO_X:
            address=do_zerox();
            unsignedvalue=read_memory(address);
            STO_C (unsignedvalue & 0x01); 
            unsignedvalue>>=1;
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue);
            break;

         case OP_LSR_ABSOLUTE_X:
            address=do_absx();
            unsignedvalue=read_memory(address);
            STO_C (unsignedvalue & 0x01); 
            unsignedvalue>>=1;
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue);
            break;

         case OP_LSR_ABSOLUTE_0:
            address=do_abs();
            unsignedvalue=read_memory(address);
            STO_C (unsignedvalue & 0x01); 
            unsignedvalue>>=1;
            set_memory(address,unsignedvalue);
            SETFLAGS(unsignedvalue);
            break;

         case OP_ADC_IMMEDIATE:
            unsignedvalue=mem_map[proc_PC++];
            DO_ADC(unsignedvalue);
            break;

         case OP_ADC_ZERO_0:
            unsignedvalue=read_memory(do_zero());
            DO_ADC(unsignedvalue);
            break;

         case OP_ADC_ZERO_X:
            unsignedvalue=read_memory(do_zerox());
            DO_ADC(unsignedvalue);
            break;

         case OP_ADC_ABSOLUTE_0:
            unsignedvalue=read_memory(do_abs());
            DO_ADC(unsignedvalue);
            break;

         case OP_ADC_ABSOLUTE_Y:
            unsignedvalue=read_memory(do_absy());
            DO_ADC(unsignedvalue);
            break;

         case OP_ADC_ABSOLUTE_X:
            unsignedvalue=read_memory(do_absx());
            DO_ADC(unsignedvalue);
            break;

         case OP_ADC_INDIRECT_Y:
            unsignedvalue=read_memory(do_indy());
            DO_ADC(unsignedvalue);
            break;

         case OP_SBC_IMMEDIATE:
            unsignedvalue=mem_map[proc_PC++];
            DO_SBC(unsignedvalue);
            break;

         case OP_SBC_ZERO_0:
            unsignedvalue=read_memory(do_zero());
            DO_SBC(unsignedvalue);
            break;

         case OP_SBC_INDIRECT_Y:
            unsignedvalue=read_memory(do_indy());
            DO_SBC(unsignedvalue);
            break;

         case OP_SBC_ABSOLUTE_0:
            unsignedvalue=read_memory(do_abs());
            DO_SBC(unsignedvalue);
            break;

         case OP_SBC_ABSOLUTE_Y:
            unsignedvalue=read_memory(do_absy());
            DO_SBC(unsignedvalue);
            break;

         case OP_SBC_ABSOLUTE_X:
            unsignedvalue=read_memory(do_absx());
            DO_SBC(unsignedvalue);
            break;

         case OP_SBC_ZERO_X:
            unsignedvalue=read_memory(do_zerox());
            DO_SBC(unsignedvalue);
            break;

         case OP_BIT_ZERO:
            unsignedvalue=read_memory(do_zero());
            STO_N (unsignedvalue & 0x80); 
            STO_V (unsignedvalue & 0x40); 
            STO_Z ((proc_A & unsignedvalue) == 0); 
            break;

         case OP_BIT_ABSOLUTE:
            unsignedvalue=read_memory(do_abs());
            STO_N (unsignedvalue & 0x80); 
            STO_V (unsignedvalue & 0x40); 
            STO_Z ((proc_A & unsignedvalue) == 0); 
            break;

         case OP_SEC:
            SET_C;
            break;

         case OP_SED:
            SET_D;
            break;

         case OP_SEI:
            SET_I;
            break;

         case OP_PHA:
            push(proc_A);
            break;

         case OP_PLA:
            proc_A=pop();
            SETFLAGS(proc_A);
            break;

         case OP_PHP:
            unsignedvalue=FLAGS_TO_BYTE;
            push(unsignedvalue);
            break;

         case OP_PLP:
            unsignedvalue=pop();
            BYTE_TO_FLAGS(unsignedvalue);
            break;

         case OP_BRK:
            proc_PC+=2;
            push(proc_PC >> 8);
            push(proc_PC & 0xff);

            SET_I;

            unsignedvalue=FLAGS_TO_BYTE;
            push(unsignedvalue);

            lowbyte=mem_map[0xfffe];
            hibyte=mem_map[0xffff];
            proc_PC=(hibyte<<8|lowbyte);
            break;
            /*
            proc_PC--;
            if(video) close_graphics();
            printf("*BRK* opcode: %x - %x\n",opcode,mem_map[proc_PC]);
            printf("PC:%0.4x SP:%0.2x A:%0.2x X:%0.2x Y:%0.2x N:%0.2x Z:%0.2x C:%0.2x I:%0.2x D:%0.2x V:%0.2x\n",proc_PC,proc_SP,proc_A,proc_X,proc_Y,proc_N,proc_Z,proc_C,proc_I,proc_D,proc_V);
            getch();
            if(video) init_graphics();
            done=TRUE;
            break;
            */

         case OP_NOP:
            break;

         default:
            /*
            proc_PC--;
            if(video) close_graphics();
            printf("*BAD* opcode: %x - %x\n",opcode,mem_map[proc_PC]);
            printf("PC:%0.4x SP:%0.2x A:%0.2x X:%0.2x Y:%0.2x N:%0.2x Z:%0.2x C:%0.2x I:%0.2x D:%0.2x V:%0.2x\n",proc_PC,proc_SP,proc_A,proc_X,proc_Y,proc_N,proc_Z,proc_C,proc_I,proc_D,proc_V);
            done=TRUE;
            */
            reset_processor();
            break;
      }
   }
   return((unsigned long)totalcycles);
}

void compare(byte val1, byte val2)
{
   proc_C = (val1 >= val2);
   proc_Z = (val1 == val2); 
   proc_N = ((val1 - val2) & 0x80);
}
           
void push(byte val)
{
  short addr;
  addr = proc_SP + 0x100;
  proc_SP--;
  set_memory (addr, val);
}

byte pop(void)
{
  short addr;
  proc_SP++;
  addr = proc_SP + 0x100;
  return (mem_map[addr]);
}

void reset_processor(void)
{
   byte hibyte,lowbyte;

   proc_X=0;
   proc_Y=0;
   proc_A=0;
   proc_N=0;
   proc_Z=0;
   proc_C=0;
   proc_I=0;
   proc_D=0;
   proc_V=0;
   proc_SP=0xff;

   /* jump to HARDWARE_RESET vector at $fffc */
   lowbyte=mem_map[0xfffc];
   hibyte=mem_map[0xfffd];
   proc_PC=(hibyte<<8|lowbyte);
}


