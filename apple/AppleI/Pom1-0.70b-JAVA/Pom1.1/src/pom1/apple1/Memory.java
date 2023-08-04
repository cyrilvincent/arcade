// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Memory.java

package pom1.apple1;

import java.io.*;
import java.net.URL;

import sun.management.FileSystem;

// Referenced classes of package pom1.apple1:
//            Pia6820

public class Memory
{

    public Memory(Pia6820 pia)
    {
        appletMode = false;
        mem = new int[0x10000];
        reset();
        this.pia = pia;
        ram8k = false;
        writeInRom = true;
    }

    public Memory(Pia6820 pia, URL appletCodeBase, boolean appletMode)
    {
        this.appletMode = false;
        mem = new int[0x10000];
        this.appletMode = appletMode;
        this.appletCodeBase = appletCodeBase;
        reset();
        this.pia = pia;
        ram8k = false;
        writeInRom = true;
    }

    public void setRam8k(boolean b)
    {
        ram8k = b;
    }

    public void setWriteInRom(boolean b)
    {
        writeInRom = b;
    }

    public int read(int address)
    {
        if(address == 53267)
            return pia.readDspCr();
        if(address == 53266)
            return pia.readDsp();
        if(address == 53265)
            return pia.readKbdCr();
        if(address == 53264)
            return pia.readKbd();
        else
            return mem[address];
    }

    public void write(int address, int value)
    {
        if(address == 53267)
        {
            mem[address] = value;
            pia.writeDspCr(value);
            return;
        }
        if(address == 53266)
        {
            mem[address] = value;
            pia.writeDsp(value);
            return;
        }
        if(address == 53265)
        {
            mem[address] = value;
            pia.writeKbdCr(value);
            return;
        }
        if(address == 53264)
        {
            mem[address] = value;
            pia.writeKbd(value);
            return;
        }
        if(address >= 65280 && !writeInRom)
            return;
        if(ram8k && address >= 8192 && address < 65280)
        {
            return;
        } else
        {
            mem[address % 0x10000] = value;
            return;
        }
    }

    public void reset()
    {
        for(int i = 0; i < 0x10000; i++)
            mem[i] = 0;

        loadRom();
    }

    public int[] dumpMemory(int start, int end)
    {
        int fbrut[] = new int[(end - start) + 1];
        for(int i = 0; i < (end - start) + 1; i++)
            fbrut[i] = mem[start + i] & 0xff;

        return fbrut;
    }

    public void loadRom()
    {
        if(!appletMode)
        {
            String filename;
            int startingAddress;
            filename = System.getProperty("user.dir") + "/bios/" +
            	System.getProperty("ROMFILE", "apple1.rom");
            FileInputStream fis = null;
            try
            {
            	File romFile = new File(filename);
                fis = new FileInputStream(romFile);
                long romsize = romFile.length();
                startingAddress = (int) (65536 - romsize);
                for(int i = startingAddress; i < 0x10000; i++)
                    mem[i] = fis.read();
                fis.close();
            }
            catch(Exception e)
            {
                System.out.println(e);
            }
        } else
        {
            DataInputStream fis = null;
            try
            {
                URL u = new URL(appletCodeBase, "apple1.rom");
                int startingAddress = 65280;
                fis = new DataInputStream(u.openStream());
                for(int i = startingAddress; i < 0x10000; i++)
                    mem[i] = fis.read();

                fis.close();
            }
            catch(Exception e)
            {
                System.out.println(e);
                System.out.println("URL Error Access in Memory.class");
                return;
            }
        }
    }

    public static final int KBD = 53264;
    public static final int KBDCR = 53265;
    public static final int DSP = 53266;
    public static final int DSPCR = 53267;
    private boolean ram8k;
    private boolean writeInRom;
    private boolean appletMode;
    private int mem[];
    private Pia6820 pia;
    private URL appletCodeBase;
}
