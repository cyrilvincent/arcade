// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Pia6820.java

package pom1.apple1;

import java.io.PrintStream;

// Referenced classes of package pom1.apple1:
//            Screen

public class Pia6820
{

    public Pia6820(Screen screen)
    {
        this.screen = screen;
        echo = System.getProperty("ECHO", "N").equalsIgnoreCase("Y");
        reset();
    }

    public void setKbdInterrups(boolean b)
    {
        kbdInterrups = b;
    }

    public boolean getKbdInterrups()
    {
        return kbdInterrups;
    }

    public boolean getDspOutput()
    {
        return dspOutput;
    }

    public void writeDspCr(int dspCr)
    {
        if(!dspOutput)
        {
            if(dspCr >= 128)
                dspOutput = true;
            dspCr = 0;
        } else
        {
            this.dspCr = dspCr;
        }
    }

    public void writeDsp(int dsp)
    {
        if(dsp >= 128)
            dsp -= 128;
        if(echo)
            if(dsp == 13)
                System.out.println();
            else
                System.out.print((char)dsp);
        screen.outputDsp(dsp);
        this.dsp = dsp;
    }

    public void writeKbdCr(int kbdCr)
    {
        if(!kbdInterrups)
        {
            if(kbdCr >= 128)
            {
                kbdInterrups = true;
                kbdCr = 0;
            }
        } else
        {
            this.kbdCr = kbdCr;
        }
    }

    public void writeKbd(int kbd)
    {
        this.kbd = kbd;
    }

    public int readDspCr()
    {
        return dspCr;
    }

    public int readDsp()
    {
        return dsp;
    }

    public int readKbdCr()
    {
        if(kbdInterrups && kbdCr >= 128)
        {
            kbdCr = 0;
            return 167;
        } else
        {
            return kbdCr;
        }
    }

    public int readKbd()
    {
        return kbd;
    }

    public void reset()
    {
        kbdInterrups = false;
        kbdCr = 0;
        dspOutput = false;
        dspCr = 0;
    }

    private int dspCr;
    private int dsp;
    private int kbdCr;
    private int kbd;
    private boolean kbdInterrups;
    private boolean dspOutput;
    private Screen screen;
    private boolean echo;
}
