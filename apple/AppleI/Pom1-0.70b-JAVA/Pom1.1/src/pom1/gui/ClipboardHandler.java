// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   ClipboardHandler.java

package pom1.gui;

import java.awt.Toolkit;
import java.awt.datatransfer.*;
import java.io.IOException;
import java.io.PrintStream;
import java.util.Timer;
import pom1.apple1.Pia6820;
import pom1.apple1.Screen;

// Referenced classes of package pom1.gui:
//            TyperTimerTask

public class ClipboardHandler
{

    public ClipboardHandler()
    {
    }

    public static void sendDataToApple1(Pia6820 pia, Screen screen)
    {
        if(pia.getKbdInterrups())
        {
            String data = getClipboardContents();
            TyperTimerTask typerTask = new TyperTimerTask(data, screen);
            theTimer.schedule(typerTask, 0L, 100L);
        }
    }

    public static String getClipboardContents()
    {
        String data = "";
        Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        Transferable contents = clipboard.getContents(null);
        boolean hasTransferableText = contents != null && contents.isDataFlavorSupported(DataFlavor.stringFlavor);
        if(hasTransferableText)
            try
            {
                data = (String)contents.getTransferData(DataFlavor.stringFlavor);
            }
            catch(UnsupportedFlavorException ex)
            {
                System.out.println(ex);
            }
            catch(IOException ex)
            {
                System.out.println(ex);
            }
        return data;
    }

    static Timer theTimer = new Timer();

}
