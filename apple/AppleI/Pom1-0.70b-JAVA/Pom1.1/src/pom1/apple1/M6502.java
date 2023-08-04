// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: packimports(3)
// Source File Name:   M6502.java

package pom1.apple1;


// Referenced classes of package pom1.apple1:
//            Memory

public class M6502
    implements Runnable
{
	protected boolean valid = false;

    public M6502(Memory mem, int freq, int synchroMillis)
    {
        runner = null;
        lastTime = System.currentTimeMillis();
        this.mem = mem;
        M = true;
        I = true;
        D = false;
        IRQ = false;
        NMI = false;
        stackPointer = 255;
        programCounter = memReadAbsolute(65532);
        cyclesBeforeSynchro = synchroMillis * freq;
        this.synchroMillis = synchroMillis;
    }

    public void setSpeed(int freq, int synchroMillis)
    {
        cyclesBeforeSynchro = synchroMillis * freq;
        this.synchroMillis = synchroMillis;
    }

    public void reset()
    {
        I = true;
        stackPointer = 255;
        programCounter = memReadAbsolute(65532);
    }

    public void IRQ(boolean state)
    {
        IRQ = state;
    }

    public void NMI()
    {
        NMI = true;
    }

    public void start()
    {
        if(runner == null)
        {
            runner = new Thread(this);
            runner.start();
        }
    }

    public void stop()
    {
        if(runner != null)
            runner = null;
    }

    public void setStepping()
    {
        stepping = true;
    }

    public void stopStepping()
    {
        stepping = false;
    }

    public void takeStep()
    {
        takeStep = true;
    }

    public void run()
    {
        for(Thread thisThread = Thread.currentThread(); runner == thisThread;)
        {
            synchronize();
            for(cycles = 0; cycles < cyclesBeforeSynchro;)
            {
                if(stepping)
                    while(!takeStep) ;
                if(!I && IRQ)
                    handleIRQ();
                if(NMI)
                    handleNMI();
                executeOpcode();
            }

        }

    }

    protected void updateDebugDisplay()
    {
    }

    public boolean executeOpcode()
    {
    	valid = true;

        int opcode = mem.read(programCounter++);
        switch(opcode)
        {
        case 0: // '\0'
            Imm();
            BRK();
            break;

        case 1: // '\001'
            IndZeroX();
            ORA();
            break;

        case 2: // '\002'
            Hang();
            break;

        case 3: // '\003'
            Unoff();
            break;

        case 4: // '\004'
            Unoff2();
            break;

        case 5: // '\005'
            Zero();
            ORA();
            break;

        case 6: // '\006'
            Zero();
            ASL();
            break;

        case 7: // '\007'
            Unoff();
            break;

        case 8: // '\b'
            Imp();
            PHP();
            break;

        case 9: // '\t'
            Imm();
            ORA();
            break;

        case 10: // '\n'
            Imp();
            ASL_A();
            break;

        case 11: // '\013'
            Imm();
            AND();
            break;

        case 12: // '\f'
            Unoff3();
            break;

        case 13: // '\r'
            Abs();
            ORA();
            break;

        case 14: // '\016'
            Abs();
            ASL();
            break;

        case 15: // '\017'
            Unoff();
            break;

        case 16: // '\020'
            Rel();
            BPL();
            break;

        case 17: // '\021'
            IndZeroY();
            ORA();
            break;

        case 18: // '\022'
            Hang();
            break;

        case 19: // '\023'
            Unoff();
            break;

        case 20: // '\024'
            Unoff2();
            break;

        case 21: // '\025'
            ZeroX();
            ORA();
            break;

        case 22: // '\026'
            ZeroX();
            ASL();
            break;

        case 23: // '\027'
            Unoff();
            break;

        case 24: // '\030'
            Imp();
            CLC();
            break;

        case 25: // '\031'
            AbsY();
            ORA();
            break;

        case 26: // '\032'
            Unoff1();
            break;

        case 27: // '\033'
            Unoff();
            break;

        case 28: // '\034'
            Unoff3();
            break;

        case 29: // '\035'
            AbsX();
            ORA();
            break;

        case 30: // '\036'
            WAbsX();
            ASL();
            break;

        case 31: // '\037'
            Unoff();
            break;

        case 32: // ' '
            JSR();
            break;

        case 33: // '!'
            IndZeroX();
            AND();
            break;

        case 34: // '"'
            Hang();
            break;

        case 35: // '#'
            Unoff();
            break;

        case 36: // '$'
            Zero();
            BIT();
            break;

        case 37: // '%'
            Zero();
            AND();
            break;

        case 38: // '&'
            Zero();
            ROL();
            break;

        case 39: // '\''
            Unoff();
            break;

        case 40: // '('
            Imp();
            PLP();
            break;

        case 41: // ')'
            Imm();
            AND();
            break;

        case 42: // '*'
            Imp();
            ROL_A();
            break;

        case 43: // '+'
            Imm();
            AND();
            break;

        case 44: // ','
            Abs();
            BIT();
            break;

        case 45: // '-'
            Abs();
            AND();
            break;

        case 46: // '.'
            Abs();
            ROL();
            break;

        case 47: // '/'
            Unoff();
            break;

        case 48: // '0'
            Rel();
            BMI();
            break;

        case 49: // '1'
            IndZeroY();
            AND();
            break;

        case 50: // '2'
            Hang();
            break;

        case 51: // '3'
            Unoff();
            break;

        case 52: // '4'
            Unoff2();
            break;

        case 53: // '5'
            ZeroX();
            AND();
            break;

        case 54: // '6'
            ZeroX();
            ROL();
            break;

        case 55: // '7'
            Unoff();
            break;

        case 56: // '8'
            Imp();
            SEC();
            break;

        case 57: // '9'
            AbsY();
            AND();
            break;

        case 58: // ':'
            Unoff1();
            break;

        case 59: // ';'
            Unoff();
            break;

        case 60: // '<'
            Unoff3();
            break;

        case 61: // '='
            AbsX();
            AND();
            break;

        case 62: // '>'
            WAbsX();
            ROL();
            break;

        case 63: // '?'
            Unoff();
            break;

        case 64: // '@'
            Imp();
            RTI();
            break;

        case 65: // 'A'
            IndZeroX();
            EOR();
            break;

        case 66: // 'B'
            Hang();
            break;

        case 67: // 'C'
            Unoff();
            break;

        case 68: // 'D'
            Unoff2();
            break;

        case 69: // 'E'
            Zero();
            EOR();
            break;

        case 70: // 'F'
            Zero();
            LSR();
            break;

        case 71: // 'G'
            Unoff();
            break;

        case 72: // 'H'
            Imp();
            PHA();
            break;

        case 73: // 'I'
            Imm();
            EOR();
            break;

        case 74: // 'J'
            Imp();
            LSR_A();
            break;

        case 75: // 'K'
            Unoff();
            break;

        case 76: // 'L'
            Abs();
            JMP();
            break;

        case 77: // 'M'
            Abs();
            EOR();
            break;

        case 78: // 'N'
            Abs();
            LSR();
            break;

        case 79: // 'O'
            Unoff();
            break;

        case 80: // 'P'
            Rel();
            BVC();
            break;

        case 81: // 'Q'
            IndZeroY();
            EOR();
            break;

        case 82: // 'R'
            Hang();
            break;

        case 83: // 'S'
            Unoff();
            break;

        case 84: // 'T'
            Unoff2();
            break;

        case 85: // 'U'
            ZeroX();
            EOR();
            break;

        case 86: // 'V'
            ZeroX();
            LSR();
            break;

        case 87: // 'W'
            Unoff();
            break;

        case 88: // 'X'
            Imp();
            CLI();
            break;

        case 89: // 'Y'
            AbsY();
            EOR();
            break;

        case 90: // 'Z'
            Unoff1();
            break;

        case 91: // '['
            Unoff();
            break;

        case 92: // '\\'
            Unoff3();
            break;

        case 93: // ']'
            AbsX();
            EOR();
            break;

        case 94: // '^'
            WAbsX();
            LSR();
            break;

        case 95: // '_'
            Unoff();
            break;

        case 96: // '`'
            Imp();
            RTS();
            break;

        case 97: // 'a'
            IndZeroX();
            ADC();
            break;

        case 98: // 'b'
            Hang();
            break;

        case 99: // 'c'
            Unoff();
            break;

        case 100: // 'd'
            Unoff2();
            break;

        case 101: // 'e'
            Zero();
            ADC();
            break;

        case 102: // 'f'
            Zero();
            ROR();
            break;

        case 103: // 'g'
            Unoff();
            break;

        case 104: // 'h'
            Imp();
            PLA();
            break;

        case 105: // 'i'
            Imm();
            ADC();
            break;

        case 106: // 'j'
            Imp();
            ROR_A();
            break;

        case 107: // 'k'
            Unoff();
            break;

        case 108: // 'l'
            Ind();
            JMP();
            break;

        case 109: // 'm'
            Abs();
            ADC();
            break;

        case 110: // 'n'
            Abs();
            ROR();
            break;

        case 111: // 'o'
            Unoff();
            break;

        case 112: // 'p'
            Rel();
            BVS();
            break;

        case 113: // 'q'
            IndZeroY();
            ADC();
            break;

        case 114: // 'r'
            Hang();
            break;

        case 115: // 's'
            Unoff();
            break;

        case 116: // 't'
            Unoff2();
            break;

        case 117: // 'u'
            ZeroX();
            ADC();
            break;

        case 118: // 'v'
            ZeroX();
            ROR();
            break;

        case 119: // 'w'
            Unoff();
            break;

        case 120: // 'x'
            Imp();
            SEI();
            break;

        case 121: // 'y'
            AbsY();
            ADC();
            break;

        case 122: // 'z'
            Unoff1();
            break;

        case 123: // '{'
            Unoff();
            break;

        case 124: // '|'
            Unoff3();
            break;

        case 125: // '}'
            AbsX();
            ADC();
            break;

        case 126: // '~'
            WAbsX();
            ROR();
            break;

        case 127: // '\177'
            Unoff();
            break;

        case 128:
            Unoff2();
            break;

        case 129:
            IndZeroX();
            STA();
            break;

        case 130:
            Unoff2();
            break;

        case 131:
            Unoff();
            break;

        case 132:
            Zero();
            STY();
            break;

        case 133:
            Zero();
            STA();
            break;

        case 134:
            Zero();
            STX();
            break;

        case 135:
            Unoff();
            break;

        case 136:
            Imp();
            DEY();
            break;

        case 137:
            Unoff2();
            break;

        case 138:
            Imp();
            TXA();
            break;

        case 139:
            Unoff();
            break;

        case 140:
            Abs();
            STY();
            break;

        case 141:
            Abs();
            STA();
            break;

        case 142:
            Abs();
            STX();
            break;

        case 143:
            Unoff();
            break;

        case 144:
            Rel();
            BCC();
            break;

        case 145:
            WIndZeroY();
            STA();
            break;

        case 146:
            Hang();
            break;

        case 147:
            Unoff();
            break;

        case 148:
            ZeroX();
            STY();
            break;

        case 149:
            ZeroX();
            STA();
            break;

        case 150:
            ZeroY();
            STX();
            break;

        case 151:
            Unoff();
            break;

        case 152:
            Imp();
            TYA();
            break;

        case 153:
            WAbsY();
            STA();
            break;

        case 154:
            Imp();
            TXS();
            break;

        case 155:
            Unoff();
            break;

        case 156:
            Unoff();
            break;

        case 157:
            WAbsX();
            STA();
            break;

        case 158:
            Unoff();
            break;

        case 159:
            Unoff();
            break;

        case 160:
            Imm();
            LDY();
            break;

        case 161:
            IndZeroX();
            LDA();
            break;

        case 162:
            Imm();
            LDX();
            break;

        case 163:
            Unoff();
            break;

        case 164:
            Zero();
            LDY();
            break;

        case 165:
            Zero();
            LDA();
            break;

        case 166:
            Zero();
            LDX();
            break;

        case 167:
            Unoff();
            break;

        case 168:
            Imp();
            TAY();
            break;

        case 169:
            Imm();
            LDA();
            break;

        case 170:
            Imp();
            TAX();
            break;

        case 171:
            Unoff();
            break;

        case 172:
            Abs();
            LDY();
            break;

        case 173:
            Abs();
            LDA();
            break;

        case 174:
            Abs();
            LDX();
            break;

        case 175:
            Unoff();
            break;

        case 176:
            Rel();
            BCS();
            break;

        case 177:
            IndZeroY();
            LDA();
            break;

        case 178:
            Hang();
            break;

        case 179:
            Unoff();
            break;

        case 180:
            ZeroX();
            LDY();
            break;

        case 181:
            ZeroX();
            LDA();
            break;

        case 182:
            ZeroY();
            LDX();
            break;

        case 183:
            Unoff();
            break;

        case 184:
            Imp();
            CLV();
            break;

        case 185:
            AbsY();
            LDA();
            break;

        case 186:
            Imp();
            TSX();
            break;

        case 187:
            Unoff();
            break;

        case 188:
            AbsX();
            LDY();
            break;

        case 189:
            AbsX();
            LDA();
            break;

        case 190:
            AbsY();
            LDX();
            break;

        case 191:
            Unoff();
            break;

        case 192:
            Imm();
            CPY();
            break;

        case 193:
            IndZeroX();
            CMP();
            break;

        case 194:
            Unoff2();
            break;

        case 195:
            Unoff();
            break;

        case 196:
            Zero();
            CPY();
            break;

        case 197:
            Zero();
            CMP();
            break;

        case 198:
            Zero();
            DEC();
            break;

        case 199:
            Unoff();
            break;

        case 200:
            Imp();
            INY();
            break;

        case 201:
            Imm();
            CMP();
            break;

        case 202:
            Imp();
            DEX();
            break;

        case 203:
            Unoff();
            break;

        case 204:
            Abs();
            CPY();
            break;

        case 205:
            Abs();
            CMP();
            break;

        case 206:
            Abs();
            DEC();
            break;

        case 207:
            Unoff();
            break;

        case 208:
            Rel();
            BNE();
            break;

        case 209:
            IndZeroY();
            CMP();
            break;

        case 210:
            Hang();
            break;

        case 211:
            Unoff();
            break;

        case 212:
            Unoff2();
            break;

        case 213:
            ZeroX();
            CMP();
            break;

        case 214:
            ZeroX();
            DEC();
            break;

        case 215:
            Unoff();
            break;

        case 216:
            Imp();
            CLD();
            break;

        case 217:
            AbsY();
            CMP();
            break;

        case 218:
            Unoff1();
            break;

        case 219:
            Unoff();
            break;

        case 220:
            Unoff3();
            break;

        case 221:
            AbsX();
            CMP();
            break;

        case 222:
            WAbsX();
            DEC();
            break;

        case 223:
            Unoff();
            break;

        case 224:
            Imm();
            CPX();
            break;

        case 225:
            IndZeroX();
            SBC();
            break;

        case 226:
            Unoff2();
            break;

        case 227:
            Unoff();
            break;

        case 228:
            Zero();
            CPX();
            break;

        case 229:
            Zero();
            SBC();
            break;

        case 230:
            Zero();
            INC();
            break;

        case 231:
            Unoff();
            break;

        case 232:
            Imp();
            INX();
            break;

        case 233:
            Imm();
            SBC();
            break;

        case 234:
            Imp();
            NOP();
            break;

        case 235:
            Imm();
            SBC();
            break;

        case 236:
            Abs();
            CPX();
            break;

        case 237:
            Abs();
            SBC();
            break;

        case 238:
            Abs();
            INC();
            break;

        case 239:
            Unoff();
            break;

        case 240:
            Rel();
            BEQ();
            break;

        case 241:
            IndZeroY();
            SBC();
            break;

        case 242:
            Hang();
            break;

        case 243:
            Unoff();
            break;

        case 244:
            Unoff2();
            break;

        case 245:
            ZeroX();
            SBC();
            break;

        case 246:
            ZeroX();
            INC();
            break;

        case 247:
            Unoff();
            break;

        case 248:
            Imp();
            SED();
            break;

        case 249:
            AbsY();
            SBC();
            break;

        case 250:
            Unoff1();
            break;

        case 251:
            Unoff();
            break;

        case 252:
            Unoff3();
            break;

        case 253:
            AbsX();
            SBC();
            break;

        case 254:
            WAbsX();
            INC();
            break;

        case 255:
            Unoff();
            break;
        }

        return valid;
    }

    public int[] dumpState()
    {
        int state[] = new int[6];
        state[0] = programCounter;
        state[1] = getStatusRegisterByte();
        state[2] = accumulator;
        state[3] = xRegister;
        state[4] = yRegister;
        state[5] = stackPointer;
        return state;
    }

    public void loadState(int state[])
    {
        programCounter = state[0];
        setStatusRegisterByte(state[1]);
        accumulator = state[2];
        xRegister = state[3];
        yRegister = state[4];
        stackPointer = state[5];
    }

    protected void setStatusRegisterByte(int statusRegister)
    {
        if((statusRegister & 0x80) == 128)
            N = true;
        if((statusRegister & 0x40) == 64)
            V = true;
        if((statusRegister & 0x20) == 32)
            M = true;
        if((statusRegister & 0x10) == 16)
            B = true;
        if((statusRegister & 8) == 8)
            D = true;
        if((statusRegister & 4) == 4)
            I = true;
        if((statusRegister & 2) == 2)
            Z = true;
        if((statusRegister & 1) == 1)
            C = true;
    }

    protected void setStatusRegisterNZ(byte val)
    {
        N = val < 0;
        Z = val == 0;
    }

    protected void setFlagCarry(int val)
    {
        C = (val & 0x100) != 0;
    }

    protected void setFlagBorrow(int val)
    {
        C = (val & 0x100) == 0;
    }

    protected int getStatusRegisterByte()
    {
        statusRegister = 0;
        if(N)
            statusRegister |= 0x80;
        if(V)
            statusRegister |= 0x40;
        if(M)
            statusRegister |= 0x20;
        if(B)
            statusRegister |= 0x10;
        if(D)
            statusRegister |= 8;
        if(I)
            statusRegister |= 4;
        if(Z)
            statusRegister |= 2;
        if(C)
            statusRegister |= 1;
        return statusRegister;
    }

    protected void synchronize()
    {
        int realTimeMillis = (int)(System.currentTimeMillis() - lastTime);
        int sleepMillis = synchroMillis - realTimeMillis;
        if(sleepMillis < 0)
            sleepMillis = 5;
        try
        {
            Thread.sleep(sleepMillis);
        }
        catch(Exception e)
        {
            System.out.println(e);
        }
        lastTime = System.currentTimeMillis();
    }

    protected void Imp()
    {
        cycles++;
    }

    protected void Imm()
    {
        op = programCounter++;
    }

    protected void Zero()
    {
        op = mem.read(programCounter++);
        cycles++;
    }

    protected void ZeroX()
    {
        op = mem.read(programCounter++) + xRegister & 0xff;
        cycles++;
    }

    protected void ZeroY()
    {
        op = mem.read(programCounter++) + yRegister & 0xff;
        cycles++;
    }

    protected void Abs()
    {
        op = memReadAbsolute(programCounter);
        programCounter += 2;
        cycles += 2;
    }

    protected void AbsX()
    {
        opL = mem.read(programCounter++) + xRegister;
        opH = mem.read(programCounter++) << 8;
        cycles += 2;
        if(opL >= 256)
            cycles++;
        op = opH + opL;
    }

    protected void AbsY()
    {
        opL = mem.read(programCounter++) + yRegister;
        opH = mem.read(programCounter++) << 8;
        cycles += 2;
        if(opL >= 256)
            cycles++;
        op = opH + opL;
    }

    protected void Ind()
    {
        ptrL = mem.read(programCounter++);
        ptrH = mem.read(programCounter++) << 8;
        op = mem.read(ptrH + ptrL);
        ptrL = ptrL + 1 & 0xff;
        op += mem.read(ptrH + ptrL) << 8;
        cycles += 4;
    }

    protected void IndZeroX()
    {
        ptr = xRegister + mem.read(programCounter++);
        op = mem.read(ptr);
        op += mem.read(ptr + 1 & 0xff) << 8;
        cycles += 3;
    }

    protected void IndZeroY()
    {
        ptr = mem.read(programCounter++);
        opL = mem.read(ptr) + yRegister;
        opH = (mem.read(ptr + 1) & 0xff) << 8;
        cycles += 3;
        if(opL >= 256)
            cycles++;
        op = opH + opL;
    }

    protected void Rel()
    {
        op = mem.read(programCounter++);
        if(op >= 128)
            op = -(256 - op);
        op = op + programCounter & 0xffff;
        cycles++;
    }

    protected void WAbsX()
    {
        opL = mem.read(programCounter++) + xRegister;
        opH = mem.read(programCounter++) << 8;
        cycles += 3;
        op = opH + opL;
    }

    protected void WAbsY()
    {
        opL = mem.read(programCounter++) + yRegister;
        opH = mem.read(programCounter++) << 8;
        cycles += 3;
        op = opH + opL;
    }

    protected void WIndZeroY()
    {
        ptr = mem.read(programCounter++);
        opL = mem.read(ptr) + yRegister;
        opH = mem.read(ptr + 1 & 0xff) << 8;
        cycles += 4;
        op = opH + opL;
    }

    protected void LDA()
    {
        accumulator = mem.read(op);
        setStatusRegisterNZ((byte)accumulator);
        cycles++;
    }

    protected void LDX()
    {
        xRegister = mem.read(op);
        setStatusRegisterNZ((byte)xRegister);
        cycles++;
    }

    protected void LDY()
    {
        yRegister = mem.read(op);
        setStatusRegisterNZ((byte)yRegister);
        cycles++;
    }

    protected void STA()
    {
        mem.write(op, accumulator & 0xff);
        cycles++;
    }

    protected void STX()
    {
        mem.write(op, xRegister & 0xff);
        cycles++;
    }

    protected void STY()
    {
        mem.write(op, yRegister & 0xff);
        cycles++;
    }

    protected void ADC()
    {
        int Op1 = accumulator;
        int Op2 = mem.read(op);
        cycles++;
        if(D)
        {
            Z = (Op1 + Op2 + (C ? 1 : 0) & 0xff) == 0;
            tmp = (Op1 & 0xf) + (Op2 & 0xf) + (C ? 1 : 0);
            tmp = tmp >= 10 ? tmp + 6 : tmp;
            accumulator = tmp;
            tmp = (Op1 & 0xf0) + (Op2 & 0xf0) + (tmp & 0xf0);
            N = (byte)tmp < 0;
            V = ((Op1 ^ tmp) & ~(Op1 ^ Op2) & 0x80) != 0;
            tmp = accumulator & 0xf | (tmp >= 160 ? tmp + 96 : tmp);
            C = tmp >= 256;
            accumulator = tmp & 0xff;
        } else
        {
            tmp = Op1 + Op2 + (C ? 1 : 0);
            accumulator = tmp & 0xff;
            V = ((Op1 ^ accumulator) & ~(Op1 ^ Op2) & 0x80) != 0;
            setFlagCarry(tmp);
            setStatusRegisterNZ((byte)accumulator);
        }
    }

    protected void SBC()
    {
        int Op1 = accumulator;
        int Op2 = mem.read(op);
        cycles++;
        if(D)
        {
            tmp = (Op1 & 0xf) - (Op2 & 0xf) - (C ? 0 : 1);
            tmp = (tmp & 0x10) != 0 ? tmp - 6 : tmp;
            accumulator = tmp;
            tmp = (Op1 & 0xf0) - (Op2 & 0xf0) - (accumulator & 0x10);
            accumulator = accumulator & 0xf | ((tmp & 0x100) != 0 ? tmp - 96 : tmp);
            tmp = Op1 - Op2 - (C ? 0 : 1);
            setFlagBorrow(tmp);
            setStatusRegisterNZ((byte)tmp);
        } else
        {
            tmp = Op1 - Op2 - (C ? 0 : 1);
            accumulator = tmp & 0xff;
            V = ((Op1 ^ Op2) & (Op1 ^ accumulator) & 0x80) != 0;
            setFlagBorrow(tmp);
            setStatusRegisterNZ((byte)accumulator);
        }
    }

    protected void CMP()
    {
        tmp = accumulator - mem.read(op);
        cycles++;
        setFlagBorrow(tmp);
        setStatusRegisterNZ((byte)tmp);
    }

    protected void CPX()
    {
        tmp = xRegister - mem.read(op);
        cycles++;
        setFlagBorrow(tmp);
        setStatusRegisterNZ((byte)tmp);
    }

    protected void CPY()
    {
        tmp = yRegister - mem.read(op);
        cycles++;
        setFlagBorrow(tmp);
        setStatusRegisterNZ((byte)tmp);
    }

    protected void AND()
    {
        accumulator &= mem.read(op) & 0xff;
        cycles++;
        setStatusRegisterNZ((byte)accumulator);
    }

    protected void ORA()
    {
        accumulator |= mem.read(op) & 0xff;
        cycles++;
        setStatusRegisterNZ((byte)accumulator);
    }

    protected void EOR()
    {
        accumulator ^= mem.read(op) & 0xff;
        cycles++;
        setStatusRegisterNZ((byte)accumulator);
    }

    protected void ASL()
    {
        btmp = (byte)(mem.read(op) & 0xff);
        mem.write(op, btmp);
        C = btmp < 0;
        btmp <<= 1;
        setStatusRegisterNZ(btmp);
        mem.write(op, btmp & 0xff);
        cycles += 3;
    }

    protected void ASL_A()
    {
        tmp = accumulator << 1;
        accumulator = tmp & 0xff;
        setFlagCarry(tmp);
        setStatusRegisterNZ((byte)accumulator);
    }

    protected void LSR()
    {
        btmp = (byte)(mem.read(op) & 0xff);
        cycles += 2;
        C = (btmp & 1) != 0;
        btmp = (byte)((btmp & 0xff) >> 1);
        setStatusRegisterNZ(btmp);
        mem.write(op, btmp & 0xff);
        cycles++;
    }

    protected void LSR_A()
    {
        C = (accumulator & 1) != 0;
        accumulator >>= 1;
        setStatusRegisterNZ((byte)accumulator);
    }

    protected void ROL()
    {
        btmp = (byte)(mem.read(op) & 0xff);
        cycles += 2;
        boolean newCarry = btmp < 0;
        btmp = (byte)((btmp & 0xff) << 1 | (C ? 1 : 0));
        C = newCarry;
        setStatusRegisterNZ(btmp);
        mem.write(op, btmp & 0xff);
        cycles++;
    }

    protected void ROL_A()
    {
        tmp = accumulator << 1 | (C ? 1 : 0);
        accumulator = tmp & 0xff;
        setFlagCarry(tmp);
        setStatusRegisterNZ((byte)accumulator);
    }

    protected void ROR()
    {
        btmp = (byte)(mem.read(op) & 0xff);
        cycles += 2;
        boolean newCarry = (btmp & 1) != 0;
        btmp = (byte)((btmp & 0xff) >> 1 | (C ? 0x80 : 0));
        C = newCarry;
        setStatusRegisterNZ(btmp);
        mem.write(op, btmp & 0xff);
        cycles++;
    }

    protected void ROR_A()
    {
        tmp = accumulator | (C ? 0x100 : 0);
        C = (accumulator & 1) != 0;
        accumulator = tmp >> 1;
        setStatusRegisterNZ((byte)accumulator);
    }

    protected void INC()
    {
        btmp = (byte)(mem.read(op) & 0xff);
        mem.write(op, btmp);
        btmp++;
        setStatusRegisterNZ(btmp);
        mem.write(op, btmp & 0xff);
        cycles += 2;
    }

    protected void DEC()
    {
        btmp = (byte)(mem.read(op) & 0xff);
        mem.write(op, btmp);
        btmp--;
        setStatusRegisterNZ(btmp);
        mem.write(op, btmp & 0xff);
        cycles += 2;
    }

    protected void INX()
    {
        xRegister = xRegister + 1 & 0xff;
        setStatusRegisterNZ((byte)xRegister);
    }

    protected void INY()
    {
        yRegister = yRegister + 1 & 0xff;
        setStatusRegisterNZ((byte)yRegister);
    }

    protected void DEX()
    {
        xRegister = xRegister - 1 & 0xff;
        setStatusRegisterNZ((byte)xRegister);
    }

    protected void DEY()
    {
        yRegister = yRegister - 1 & 0xff;
        setStatusRegisterNZ((byte)yRegister);
    }

    protected void BIT()
    {
        btmp = (byte)(mem.read(op) & 0xff);
        V = (btmp & 0x40) != 0;
        N = btmp < 0;
        Z = (btmp & accumulator) == 0;
        cycles++;
    }

    protected void PHA()
    {
        mem.write(256 + stackPointer, accumulator & 0xff);
        stackPointer = stackPointer - 1 & 0xff;
        cycles++;
    }

    protected void PHP()
    {
        statusRegister = getStatusRegisterByte();
        mem.write(256 + stackPointer, statusRegister & 0xff);
        stackPointer = stackPointer - 1 & 0xff;
        cycles++;
    }

    protected void PLA()
    {
        mem.read(stackPointer + 256);
        stackPointer = stackPointer + 1 & 0xff;
        accumulator = mem.read(stackPointer + 256) & 0xff;
        setStatusRegisterNZ((byte)accumulator);
        cycles += 2;
    }

    protected void PLP()
    {
        mem.read(stackPointer + 256);
        stackPointer = stackPointer + 1 & 0xff;
        statusRegister = mem.read(stackPointer + 256) & 0xff;
        setStatusRegisterByte(statusRegister);
        cycles += 2;
    }

    protected void BRK()
    {
        mem.read(op);
        pushProgramCounter();
        PHP();
        //I = true;
        B = true;
        programCounter = memReadAbsolute(65534);
        cycles += 3;
    }

    protected void RTI()
    {
        mem.read(stackPointer + 256);
        PLP();
        popProgramCounter();
        cycles++;
    }

    protected void JMP()
    {
        programCounter = op;
    }

    protected void RTS()
    {
        mem.read(stackPointer + 256);
        popProgramCounter();
        mem.read(programCounter++);
        cycles += 2;
    }

    protected void JSR()
    {
        opL = mem.read(programCounter++) & 0xff;
        mem.read(stackPointer + 256);
        pushProgramCounter();
        programCounter = opL + ((mem.read(programCounter) & 0xff) << 8);
        cycles += 3;
    }

    protected void branch()
    {
        cycles++;
        if((programCounter & 0xff00) != (op & 0xff00))
            cycles++;
        programCounter = op;
    }

    protected void BNE()
    {
        if(!Z)
            branch();
    }

    protected void BEQ()
    {
        if(Z)
            branch();
    }

    protected void BVC()
    {
        if(!V)
            branch();
    }

    protected void BVS()
    {
        if(V)
            branch();
    }

    protected void BCC()
    {
        if(!C)
            branch();
    }

    protected void BCS()
    {
        if(C)
            branch();
    }

    protected void BPL()
    {
        if(!N)
            branch();
    }

    protected void BMI()
    {
        if(N)
            branch();
    }

    protected void TAX()
    {
        xRegister = accumulator;
        setStatusRegisterNZ((byte)accumulator);
    }

    protected void TXA()
    {
        accumulator = xRegister;
        setStatusRegisterNZ((byte)accumulator);
    }

    protected void TAY()
    {
        yRegister = accumulator;
        setStatusRegisterNZ((byte)accumulator);
    }

    protected void TYA()
    {
        accumulator = yRegister;
        setStatusRegisterNZ((byte)accumulator);
    }

    protected void TXS()
    {
        stackPointer = xRegister;
    }

    protected void TSX()
    {
        xRegister = stackPointer;
        setStatusRegisterNZ((byte)xRegister);
    }

    protected void CLC()
    {
        C = false;
    }

    protected void SEC()
    {
        C = true;
    }

    protected void CLI()
    {
        I = false;
    }

    protected void SEI()
    {
        I = true;
    }

    protected void CLV()
    {
        V = false;
    }

    protected void CLD()
    {
        D = false;
    }

    protected void SED()
    {
        D = true;
    }

    protected void NOP()
    {
    }

    protected void Unoff()
    {
        valid = false;
    }

    protected void Unoff1()
    {
        valid = false;
    }

    protected void Unoff2()
    {
        programCounter++;
        valid = false;
    }

    protected void Unoff3()
    {
        programCounter += 2;
        valid = false;
    }

    protected void Hang()
    {
        valid = false;
        programCounter--;
    }

    protected void handleIRQ()
    {
        pushProgramCounter();
        mem.write(256 + stackPointer, (byte)(getStatusRegisterByte() & 0xffffffef));
        stackPointer--;
        I = true;
        programCounter = memReadAbsolute(65534);
        cycles += 8;
    }

    protected void handleNMI()
    {
        pushProgramCounter();
        mem.write(256 + stackPointer, (byte)(getStatusRegisterByte() & 0xffffffef));
        stackPointer--;
        I = true;
        NMI = false;
        programCounter = memReadAbsolute(65530);
        cycles += 8;
    }

    protected int memReadAbsolute(int adr)
    {
        return mem.read(adr) | (mem.read(adr + 1) & 0xff) << 8;
    }

    protected void pushProgramCounter()
    {
        mem.write(stackPointer + 256, (byte)(programCounter >> 8));
        stackPointer = stackPointer - 1 & 0xff;
        mem.write(stackPointer + 256, (byte)programCounter);
        stackPointer = stackPointer - 1 & 0xff;
        cycles += 2;
    }

    protected void popProgramCounter()
    {
        stackPointer = stackPointer + 1 & 0xff;
        programCounter = mem.read(stackPointer + 256) & 0xff;
        stackPointer = stackPointer + 1 & 0xff;
        programCounter += (mem.read(stackPointer + 256) & 0xff) << 8;
        cycles += 2;
    }

    protected Memory mem;
    protected int accumulator;
    protected int xRegister;
    protected int yRegister;
    protected boolean N;
    protected boolean V;
    protected boolean M;
    protected boolean B;
    protected boolean D;
    protected boolean I;
    protected boolean Z;
    protected boolean C;
    protected int statusRegister;
    protected int programCounter;
    protected int stackPointer;
    protected boolean IRQ;
    protected boolean NMI;
    protected volatile Thread runner;
    protected byte btmp;
    protected int op;
    protected int opL;
    protected int opH;
    protected int ptr;
    protected int ptrH;
    protected int ptrL;
    protected int tmp;
    protected long lastTime;
    protected int cycles;
    protected int cyclesBeforeSynchro;
    protected int synchroMillis;
    protected boolean stepping;
    protected boolean takeStep;
}
