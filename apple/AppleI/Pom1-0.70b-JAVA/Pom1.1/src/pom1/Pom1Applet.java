// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Pom1Applet.java

package pom1;

import java.applet.Applet;
import java.awt.Graphics;

import pom1.apple1.Keyboard;
import pom1.apple1.M6502;
import pom1.apple1.Memory;
import pom1.apple1.Pia6820;
import pom1.apple1.Screen;

public class Pom1Applet extends Applet
{

    public Pom1Applet()
    {
    }

    public void init()
    {
        int pixelSize = 1;
        java.net.URL appletCodeBase = getCodeBase();
        screen = new Screen(pixelSize, appletCodeBase, true);
        pia = new Pia6820(screen);
        new Keyboard(screen, pia);
        mem = new Memory(pia, appletCodeBase, true);
        micro = new M6502(mem, 1000, 50);
        add(screen);
        try
        {
            Thread.sleep(10000L);
        }
        catch(Exception exception) { }
    }

    public void start()
    {
        micro.reset();
        micro.start();
        System.out.println("Pom1 Start Ok");
    }

    public void stop()
    {
        micro.stop();
        System.out.println("Pom1 Stop OK");
    }

    public void destroy()
    {
    }

    public void paint(Graphics g)
    {
        screen.update(g);
    }

    private Memory mem;
    private M6502 micro;
    private Pia6820 pia;
    private Screen screen;
}
