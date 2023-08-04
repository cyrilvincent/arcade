#define N_BIT 0x80
#define V_BIT 0x40
#define D_BIT 0x08
#define I_BIT 0x04
#define Z_BIT 0x02
#define C_BIT 0x01

#define SETFLAGS(val) \
{ \
   proc_Z = ((val) == 0); \
   proc_N = (((val) & 0x80) != 0); \
}

#define FLAGS_TO_BYTE  (proc_N << 7 | proc_V << 6 | proc_D << 3 | \
                        proc_I << 2 | proc_Z << 1 | proc_C)

#define BYTE_TO_FLAGS(b) \
{ \
   proc_N = (((b) & N_BIT) != 0); \
   proc_V = (((b) & V_BIT) != 0); \
   proc_D = (((b) & D_BIT) != 0); \
   proc_I = (((b) & I_BIT) != 0); \
   proc_Z = (((b) & Z_BIT) != 0); \
   proc_C = (((b) & C_BIT) != 0); \
}   

#define DO_ADC(data) \
{ \
   word wtemp; \
   word nib1, nib2; \
	word result1, result2; \
	word result3, result4; \
   if(TST_D) \
   { \
		wtemp = proc_A; \
		nib1 = data & 0xf; \
		nib2 = wtemp & 0xf; \
		result1 = nib1+nib2+TST_C; /* Add carry */ \
		if(result1 >= 10) \
		{ \
			result1 = result1 - 10; \
			result2 = 1; \
		} \
		else \
			result2 = 0; \
		nib1 = (data & 0xf0) >> 4; \
		nib2 = (wtemp & 0xf0) >> 4; \
		result3 = nib1+nib2+result2; \
		if(result3 >= 10) \
		{ \
			result3 = result3 - 10; \
			result4 = 1; \
		 \
      } \
		else \
			result4 = 0; \
		STO_C (result4); \
		CLR_V; \
		wtemp = (result3 << 4) | (result1); \
      proc_A = wtemp; \
      SETFLAGS(proc_A); \
	} \
	else \
	{ \
		wtemp = proc_A; \
		wtemp += TST_C;	   /* add carry */ \
		wtemp += data; \
		STO_C (wtemp & 0x100); \
		STO_V ((((proc_A ^ data) & 0x80) == 0) && (((proc_A ^ wtemp) & 0x80) != 0)); \
      proc_A = wtemp; \
      SETFLAGS(proc_A); \
	} \
}

#define DO_SBC(data) \
{ \
   word wtemp; \
	int nib1, nib2; \
	int result1, result2; \
	int result3, result4; \
	if (TST_D) \
	{ \
		wtemp = proc_A; \
		nib1 = data & 0xf; \
		nib2 = wtemp & 0xf; \
		result1 = nib2-nib1-!TST_C; /* Sub borrow */ \
		if(result1 < 0) \
		{ \
			result1 += 10; \
			result2 = 1; \
		} \
		else \
			result2 = 0; \
		nib1 = (data & 0xf0) >> 4; \
		nib2 = (wtemp & 0xf0) >> 4; \
		result3 = nib2-nib1-result2; \
		if(result3 < 0) \
		{ \
			result3 += 10; \
			result4 = 1; \
		} \
		else \
			result4 = 0; \
		STO_C (!result4); \
		CLR_V; \
		wtemp = (result3 << 4) | (result1); \
      proc_A = wtemp; \
      SETFLAGS(proc_A); \
	} \
	else \
	{ \
		wtemp = proc_A; \
		wtemp += TST_C; \
		wtemp += (data ^ 0xff); \
		STO_C (wtemp & 0x100); \
		STO_V ((((proc_A ^ data) & 0x80) == 0) && (((proc_A ^ wtemp) & 0x80) != 0)); \
      proc_A = wtemp; \
      SETFLAGS(proc_A); \
	} \
}


#define STO_N(val) { proc_N = ((val) != 0); }
#define SET_N { proc_N = 1; }
#define CLR_N { proc_N = 0; }
#define TST_N (proc_N)

#define STO_V(val) { proc_V = ((val) != 0); }
#define SET_V { proc_V = 1; }
#define CLR_V { proc_V = 0; }
#define TST_V (proc_V)

#define STO_D(val) { proc_D = ((val) != 0); }
#define SET_D { proc_D = 1; }
#define CLR_D { proc_D = 0; }
#define TST_D (proc_D)

#define STO_I(val) { proc_I = ((val) != 0); }
#define SET_I { proc_I = 1; }
#define CLR_I { proc_I = 0; }
#define TST_I (proc_I)

#define STO_Z(val) { proc_Z = ((val) != 0); }
#define SET_Z { proc_Z = 1; }
#define CLR_Z { proc_Z = 0; }
#define TST_Z (proc_Z)

#define STO_C(val) { proc_C = ((val) != 0); }
#define SET_C { proc_C = 1; }
#define CLR_C { proc_C = 0; }
#define TST_C (proc_C)

