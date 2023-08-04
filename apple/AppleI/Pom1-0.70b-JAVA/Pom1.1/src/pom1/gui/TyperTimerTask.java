// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ClipboardHandler.java

package pom1.gui;

import java.awt.EventQueue;
import java.awt.event.KeyEvent;
import java.util.TimerTask;
import pom1.apple1.Screen;

class TyperTimerTask extends TimerTask
{

    TyperTimerTask(String data, Screen screen)
    {
        this.data = data;
        this.screen = screen;
    }

    public void sendNextCharacter()
    {
        char key = data.charAt(i++);
        screen.dispatchEvent(new KeyEvent(screen, 400, 0L, 0, 0, key));
        if(i == data.length())
            cancel();
    }

    public void run()
    {
        EventQueue.invokeLater(typeCharacter);
    }

    String data;
    int i;
    private Screen screen;
    final Runnable typeCharacter = new Runnable() 
    {
        public void run()
        {
            sendNextCharacter();
        }
    };
}
