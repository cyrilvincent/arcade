// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Screen.java

package pom1.apple1;

import java.awt.*;
import java.io.*;
import java.net.URL;

public class Screen extends Canvas
{

    public Screen(int pixelSize)
    {
        lastTime = System.currentTimeMillis();
        loggingOutput = false;
        appletMode = false;
        charac = new int[128][8];
        screenTbl = new int[40][24];
        loadCharac();
        this.pixelSize = pixelSize;
        if(pixelSize == 1)
            scanline = false;
        terminalSpeed = 60;
        reset();
    }

    public Screen(int pixelSize, URL appletCodeBase, boolean appletMode)
    {
        lastTime = System.currentTimeMillis();
        loggingOutput = false;
        this.appletMode = false;
        charac = new int[128][8];
        screenTbl = new int[40][24];
        this.appletMode = appletMode;
        scanline = false;
        this.appletCodeBase = appletCodeBase;
        loadCharac();
        this.pixelSize = pixelSize;
        terminalSpeed = 60;
        reset();
    }

    public void setPixelSize(int ps)
    {
        pixelSize = ps;
    }

    public void setScanline(boolean scanline)
    {
        this.scanline = scanline;
    }

    public void setTerminalSpeed(int ts)
    {
        terminalSpeed = ts;
    }

    public int getTerminalSpeed()
    {
        return terminalSpeed;
    }

    public void reset()
    {
        indexX = indexY = 0;
        initScreenTbl();
        repaint();
    }

    public void outputDsp(int dsp)
    {
        if(loggingOutput)
            System.out.print((char)dsp);
        switch(dsp)
        {
        case 10: // '\n'
            indexX = 0;
            indexY++;
            break;

        case 13: // '\r'
            indexX = 0;
            indexY++;
            break;

        default:
            screenTbl[indexX][indexY] = dsp;
            indexX++;
            break;

        case 0: // '\0'
        case 127: // '\177'
            break;
        }
        if(indexX == 40)
        {
            indexX = 0;
            indexY++;
        }
        if(indexY == 24)
        {
            newLine();
            indexY--;
        }
        repaint();
        synchronizeOutput();
    }

    public void update(Graphics gc)
    {
        if(offScrImg == null)
            offScrImg = createImage(280 * pixelSize, 192 * pixelSize);
        Graphics og = offScrImg.getGraphics();
        paint(og);
        gc.drawImage(offScrImg, 0, 0, this);
        og.dispose();
    }

    public void paint(Graphics gc)
    {
        gc.setColor(Color.black);
        gc.fillRect(0, 0, 280 * pixelSize, 192 * pixelSize);
        gc.setColor(Color.green);
        for(int i = 0; i < 40; i++)
        {
            for(int j = 0; j < 24; j++)
            {
                int xPosition = i * (pixelSize * 7);
                int yPosition = j * (pixelSize * 8);
                drawCharac(gc, xPosition, yPosition, screenTbl[i][j]);
            }

        }

        drawCharac(gc, indexX * (pixelSize * 7), indexY * (pixelSize * 8), 1);
    }

    private void synchronizeOutput()
    {
        int sleepMillis = (int)((long)(1000 / terminalSpeed) - (System.currentTimeMillis() - lastTime));
        if(sleepMillis > 0)
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

    private void drawCharac(Graphics gc, int xPosition, int yPosition, int characNumber)
    {
        gc.setColor(Color.green);
        for(int k = 0; k < 8; k++)
        {
            for(int l = 1; l < 8; l++)
                if((charac[characNumber][k] & 1 << l) == 1 << l)
                    gc.fillRect(xPosition + pixelSize * (l - 1), yPosition + pixelSize * k, pixelSize, pixelSize - (scanline ? 1 : 0));

        }

    }

    private void loadCharac()
    {
        if(!appletMode)
        {
            String filename = System.getProperty("user.dir") + "/bios/apple1.vid";
            FileInputStream fis = null;
            try
            {
                fis = new FileInputStream(filename);
                for(int i = 0; i < 128; i++)
                {
                    for(int j = 0; j < 8; j++)
                        charac[i][j] = fis.read();

                }

                fis.close();
                charac[95][6] = 63;
            }
            catch(Exception e)
            {
                System.out.println(e);
            }
        } else
        {
            try
            {
                URL u = new URL(appletCodeBase, "apple1.vid");
                DataInputStream fis = null;
                fis = new DataInputStream(u.openStream());
                for(int i = 0; i < 128; i++)
                {
                    for(int j = 0; j < 8; j++)
                        charac[i][j] = fis.read();

                }

                fis.close();
            }
            catch(Exception e)
            {
                System.out.println(e);
                System.out.println("URL Error Access in Screen.class");
                return;
            }
        }
    }

    private void initScreenTbl()
    {
        for(int i = 0; i < 40; i++)
        {
            for(int j = 0; j < 24; j++)
                screenTbl[i][j] = 0;

        }

    }

    private void newLine()
    {
        for(int i = 0; i < 40; i++)
        {
            for(int j = 0; j < 23; j++)
                screenTbl[i][j] = screenTbl[i][j + 1];

        }

        for(int i = 0; i < 40; i++)
            screenTbl[i][23] = 0;

    }

    private int charac[][];
    private int screenTbl[][];
    private int indexX;
    private int indexY;
    private int pixelSize;
    private boolean scanline;
    private int terminalSpeed;
    private Image offScrImg;
    private long lastTime;
    private boolean loggingOutput;
    private boolean appletMode;
    private URL appletCodeBase;
}
