// Decompiled by Jad v1.5.8e. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.geocities.com/kpdus/jad.html
// Decompiler options: packimports(3) 
// Source File Name:   Gui.java

package pom1.gui;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import pom1.apple1.*;

// Referenced classes of package pom1.gui:
//            ClipboardHandler

public class Gui
    implements WindowListener, ActionListener
{

    public Gui()
    {
        initVariable();
        initApple1();
        initGui();
    }

    public void actionPerformed(ActionEvent evt)
    {
        if(guiMenuFileLoad.equals(evt.getSource()))
        {
            fileLoad();
            return;
        }
        if(guiMenuFileSave.equals(evt.getSource()))
        {
            fileSave();
            return;
        }
        if(guiMenuFileExit.equals(evt.getSource()))
            System.exit(0);
        if(guiMenuFilePaste.equals(evt.getSource()))
            ClipboardHandler.sendDataToApple1(pia, screen);
        if(guiMenuEmulatorReset.equals(evt.getSource()))
        {
            pia.reset();
            micro.reset();
            return;
        }
        if(guiMenuEmulatorHardReset.equals(evt.getSource()))
        {
            micro.stop();
            micro.reset();
            screen.reset();
            pia.reset();
            mem.reset();
            try
            {
                Thread.sleep(200L);
            }
            catch(Exception e)
            {
                System.out.println(e);
            }
            micro.start();
            return;
        }
        if(guiMenuConfigScreen.equals(evt.getSource()))
        {
            configScreen();
            return;
        }
        if(guiMenuConfigMemory.equals(evt.getSource()))
        {
            configMemory();
            return;
        }
        if(guiMenuDebugShow.equals(evt.getSource()))
        {
            debugShow();
            return;
        }
        if(guiMenuDebugDispose.equals(evt.getSource()))
        {
            debugDispose();
            return;
        }
        if(guiMenuHelpAbout.equals(evt.getSource()))
        {
            aboutPom1();
            return;
        }
        if(btSave.equals(evt.getSource()))
        {
            fileSaveExec();
            return;
        }
        if(btLoad.equals(evt.getSource()))
        {
            fileLoadExec();
            return;
        }
        if(btScreen.equals(evt.getSource()))
        {
            configScreenExec();
            return;
        }
        if(btMemory.equals(evt.getSource()))
        {
            configMemoryExec();
            return;
        } else
        {
            return;
        }
    }

    public void windowClosing(WindowEvent e)
    {
        if(guiFrame.equals(e.getSource()))
            System.exit(0);
        if(guiDialog.equals(e.getSource()))
            guiDialog.dispose();
    }

    public void windowActivated(WindowEvent e)
    {
        if(guiFrame.equals(e.getSource()))
            guiFrame.toFront();
        if(guiDialog.equals(e.getSource()))
            guiDialog.toFront();
    }

    public void windowClosed(WindowEvent windowevent)
    {
    }

    public void windowDeactivated(WindowEvent windowevent)
    {
    }

    public void windowDeiconified(WindowEvent e)
    {
        if(guiFrame.equals(e.getSource()))
            guiFrame.toFront();
        if(guiDialog.equals(e.getSource()))
            guiDialog.toFront();
    }

    public void windowIconified(WindowEvent windowevent)
    {
    }

    public void windowOpened(WindowEvent e)
    {
        if(guiFrame.equals(e.getSource()))
            guiFrame.toFront();
        if(guiDialog.equals(e.getSource()))
            guiDialog.toFront();
    }

    private void initGui()
    {
        guiFrame = new Frame("Pom1 : Apple1 Java Emulator");
        guiFrame.setLayout(new BorderLayout());
        guiMenuBar = new MenuBar();
        guiMenuFile = new Menu("File");
        guiMenuFileLoad = new MenuItem("Load Memory");
        guiMenuFileLoad.addActionListener(this);
        guiMenuFileSave = new MenuItem("Save Memory");
        guiMenuFileSave.addActionListener(this);
        guiMenuFileSeparator = new MenuItem("-");
        guiMenuFileSeparator.addActionListener(this);
        guiMenuFilePaste = new MenuItem("Paste");
        guiMenuFilePaste.addActionListener(this);
        guiMenuFileExit = new MenuItem("Exit");
        guiMenuFileExit.addActionListener(this);
        guiMenuFile.add(guiMenuFileLoad);
        guiMenuFile.add(guiMenuFileSave);
        guiMenuFile.add(guiMenuFileSeparator);
        guiMenuFile.add(guiMenuFilePaste);
        guiMenuFile.add(guiMenuFileSeparator);
        guiMenuFile.add(guiMenuFileExit);
        guiMenuBar.add(guiMenuFile);
        guiMenuEmulator = new Menu("Emulator");
        guiMenuEmulatorReset = new MenuItem("Reset");
        guiMenuEmulatorReset.addActionListener(this);
        guiMenuEmulatorHardReset = new MenuItem("Hard Reset");
        guiMenuEmulatorHardReset.addActionListener(this);
        guiMenuEmulator.add(guiMenuEmulatorReset);
        guiMenuEmulator.add(guiMenuEmulatorHardReset);
        guiMenuBar.add(guiMenuEmulator);
        guiMenuConfig = new Menu("Config");
        guiMenuConfigScreen = new MenuItem("Screen");
        guiMenuConfigScreen.addActionListener(this);
        guiMenuConfig.add(guiMenuConfigScreen);
        guiMenuConfigMemory = new MenuItem("Memory");
        guiMenuConfigMemory.addActionListener(this);
        guiMenuConfig.add(guiMenuConfigMemory);
        guiMenuBar.add(guiMenuConfig);
        guiMenuDebug = new Menu("Debug");
        guiMenuDebugShow = new MenuItem("Show");
        guiMenuDebugShow.addActionListener(this);
        guiMenuDebugDispose = new MenuItem("Dispose");
        guiMenuDebugDispose.addActionListener(this);
        guiMenuDebug.add(guiMenuDebugShow);
        guiMenuDebug.add(guiMenuDebugDispose);
        guiMenuBar.add(guiMenuDebug);
        guiMenuHelp = new Menu("Help");
        guiMenuHelpAbout = new MenuItem("About");
        guiMenuHelpAbout.addActionListener(this);
        guiMenuHelp.add(guiMenuHelpAbout);
        guiMenuBar.add(guiMenuHelp);
        guiDialog = new Dialog(guiFrame, true);
        guiDialog.addWindowListener(this);
        startHexTxt = new TextField("0000", 4);
        endHexTxt = new TextField("FFFF", 4);
        rawCbox = new Checkbox("Raw Data");
        btSave = new Button("Save");
        btSave.addActionListener(this);
        btLoad = new Button("Load");
        btLoad.addActionListener(this);
        cbg = new CheckboxGroup();
        btScreen = new Button("OK");
        btScreen.addActionListener(this);
        miscTxt = new TextField("", 2);
        wRomCbox = new Checkbox("Write in ROM enabled");
        btMemory = new Button("OK");
        btMemory.addActionListener(this);
        bt6502 = new Button("OK");
        bt6502.addActionListener(this);
        guiFrame.addWindowListener(this);
        guiFrame.setMenuBar(guiMenuBar);
        guiFrame.add(screen);
        guiFrame.setVisible(true);
        Insets i = guiFrame.getInsets();
        guiFrame.setSize((280 * pixelSize + (i.left + i.right)) - 2, (192 * pixelSize + (i.top + i.bottom)) - 2);
        guiFrame.setResizable(false);
        guiFrame.setVisible(true);
        screen.requestFocus();
    }

    private void initApple1()
    {
        screen = new Screen(pixelSize);
        pia = new Pia6820(screen);
        new Keyboard(screen, pia);
        mem = new Memory(pia);
        boolean use65C02 = System.getProperty("65C02", "N").equalsIgnoreCase("Y");
        micro = new M65C02(mem, 1000, 50, use65C02);
        micro.start();
    }

    private void initVariable()
    {
        pixelSize = 2;
        terminalSpeed = 60;
        writeInRom = true;
        ram8k = false;
    }

    private void debugShow()
    {
    }

    private void debugDispose()
    {
    }

    private void fileLoad()
    {
        guiDialog.removeAll();
        guiDialog.setTitle("Load memory");
        guiDialog.setLayout(new FlowLayout());
        guiDialog.add(new Label("Starting Address (Hex): "));
        guiDialog.add(startHexTxt);
        guiDialog.add(new Label("(Used only if Raw data is checked)"));
        guiDialog.add(rawCbox);
        guiDialog.add(btLoad);
        Button cancel = new Button("Cancel");
        cancel.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent e)
            {
                guiDialog.dispose();
            }

        });
        guiDialog.add(cancel);
        Point point = new Point();
        point = guiFrame.getLocation();
        int x = (int)point.getX();
        int y = (int)point.getY();
        guiDialog.setLocation(60 + x, 70 + y);
        guiDialog.setSize(220, 130);
        guiDialog.setVisible(true);
    }

    private void fileLoadExec()
    {
        int start = hexStringToInt(startHexTxt.getText());
        if(start == -1)
            return;
        String fileName = new String();
        FileDialog fileDialog = new FileDialog(guiFrame, "Load Memory ...", 0);
        fileDialog.setVisible(true);
        if(fileDialog.getFile() == null)
            return;
        fileName = fileDialog.getDirectory() + File.separator + fileDialog.getFile();
        FileInputStream fis = null;
        if(rawCbox.getState())
            try
            {
                fis = new FileInputStream(fileName);
                int size = fis.available();
                for(int i = start; i < start + size; i++)
                    mem.write(i, fis.read());

                fis.close();
            }
            catch(Exception e)
            {
                System.out.println(e);
            }
        else
            try
            {
                int lastaddress = 0;
                fis = new FileInputStream(fileName);
                BufferedReader _br = new BufferedReader(new InputStreamReader(fis));
                do
                {
                    String _strLine = _br.readLine();
                    if(_strLine == null)
                        break;
                    if(_strLine.length() != 0 && _strLine.charAt(0) != '/')
                    {
                        int semipos = _strLine.indexOf(':');
                        int address;
                        if(semipos == 0)
                        {
                            address = lastaddress + 1;
                        } else
                        {
                            String _address = _strLine.substring(0, semipos);
                            address = hexStringToInt(_address);
                        }
                        if(address != -1)
                        {
                            int offset;
                            for(offset = semipos + 1; _strLine.charAt(offset) == ' '; offset++);
                            for(int i = offset; i < _strLine.length(); i += 3)
                            {
                                String _value = _strLine.substring(i, i + 2);
                                int value = hexStringToInt(_value);
                                if(value == -1)
                                    break;
                                lastaddress = address + (i - offset) / 3;
                                mem.write(lastaddress, value);
                            }

                        }
                    }
                } while(true);
            }
            catch(Exception e)
            {
                System.out.println(e);
            }
        guiDialog.dispose();
        guiFrame.toFront();
    }

    private void fileSave()
    {
        guiDialog.removeAll();
        guiDialog.setTitle("Save memory");
        guiDialog.setLayout(new FlowLayout());
        guiDialog.add(new Label("From(Hex): "));
        guiDialog.add(startHexTxt);
        guiDialog.add(new Label("To(Hex): "));
        guiDialog.add(endHexTxt);
        guiDialog.add(rawCbox);
        guiDialog.add(btSave);
        Button cancel = new Button("Cancel");
        cancel.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent e)
            {
                guiDialog.dispose();
            }

        });
        guiDialog.add(cancel);
        Point point = new Point();
        point = guiFrame.getLocation();
        int x = (int)point.getX();
        int y = (int)point.getY();
        guiDialog.setLocation(60 + x, 70 + y);
        guiDialog.setSize(210, 130);
        guiDialog.setVisible(true);
    }

    private void fileSaveExec()
    {
        int start = hexStringToInt(startHexTxt.getText());
        int end = hexStringToInt(endHexTxt.getText());
        if((start == -1) | (end == -1))
            return;
        int fbrut[] = new int[(end - start) + 1];
        fbrut = mem.dumpMemory(start, end);
        String fileName = new String();
        FileDialog fileDialog = new FileDialog(guiFrame, "Save Memory ...", 1);
        fileDialog.setVisible(true);
        if(fileDialog.getFile() == null)
            return;
        if(rawCbox.getState())
        {
            fileName = fileDialog.getDirectory() + File.separator + fileDialog.getFile();
            FileOutputStream fos = null;
            try
            {
                fos = new FileOutputStream(fileName);
                for(int i = 0; i < (end - start) + 1; i++)
                    fos.write(fbrut[i]);

                fos.close();
            }
            catch(IOException e)
            {
                System.out.println(e);
            }
        } else
        {
            fileName = fileDialog.getDirectory() + File.separator + fileDialog.getFile();
            FileOutputStream fos = null;
            StringBuffer _buf = new StringBuffer(4 * ((end - start) + 1));
            _buf.append("// Pom1 Save : " + fileDialog.getFile() + "\r\n");
            int j = start;
            for(int i = 0; i < (end - start) + 1;)
            {
                if((j % 8 == 0) | (j == start))
                    _buf.append("\r\n" + toHex4(j) + ": ");
                _buf.append(toHex(fbrut[i]) + " ");
                i++;
                j++;
            }

            try
            {
                fos = new FileOutputStream(fileName);
                fos.write(_buf.toString().getBytes());
                fos.close();
            }
            catch(IOException e)
            {
                System.out.println(e);
            }
        }
        guiDialog.dispose();
    }

    private void configScreen()
    {
        guiDialog.removeAll();
        guiDialog.setTitle("Screen Configuration");
        guiDialog.setLayout(new FlowLayout());
        guiDialog.add(new Label("Choose the Pixel Size :"));
        guiDialog.add(new Checkbox("x1", cbg, pixelSize == 1));
        guiDialog.add(new Checkbox("x2", cbg, pixelSize == 2));
        guiDialog.add(new Checkbox(" Or choose the Scanlines", cbg, scanlines));
        guiDialog.add(new Label("Terminal speed in Charac/s :"));
        miscTxt.setText((new Integer(terminalSpeed)).toString());
        guiDialog.add(miscTxt);
        guiDialog.add(new Label("  "));
        guiDialog.add(btScreen);
        Point point = new Point();
        point = guiFrame.getLocation();
        int x = (int)point.getX();
        int y = (int)point.getY();
        guiDialog.setLocation(60 + x, 70 + y);
        guiDialog.setSize(315, 140);
        guiDialog.setVisible(true);
    }

    private void configScreenExec()
    {
        String _str = cbg.getSelectedCheckbox().getLabel();
        if(_str == "x1")
        {
            pixelSize = 1;
            scanlines = false;
        }
        if(_str == "x2")
        {
            pixelSize = 2;
            scanlines = false;
        }
        if(_str == " Or choose the Scanlines")
        {
            pixelSize = 2;
            scanlines = true;
        }
        Insets i = guiFrame.getInsets();
        guiFrame.setSize(280 * pixelSize + (i.left + i.right), 192 * pixelSize + (i.top + i.bottom));
        screen.setPixelSize(pixelSize);
        screen.setScanline(scanlines);
        terminalSpeed = Integer.decode(miscTxt.getText()).intValue();
        screen.setTerminalSpeed(terminalSpeed);
        guiDialog.dispose();
        screen.repaint();
    }

    private void configMemory()
    {
        guiDialog.removeAll();
        guiDialog.setTitle("Memory Configuration");
        guiDialog.setLayout(new FlowLayout());
        guiDialog.add(new Label("Apple I available RAM size :"));
        guiDialog.add(new Checkbox("8kb", cbg, ram8k));
        guiDialog.add(new Checkbox("Max", cbg, !ram8k));
        wRomCbox.setState(writeInRom);
        guiDialog.add(new Label("    "));
        guiDialog.add(wRomCbox);
        guiDialog.add(new Label("    "));
        guiDialog.add(new Label("IRQ/BRK vector :"));
        miscTxt.setText(toHex(mem.read(65535)) + toHex(mem.read(65534)));
        guiDialog.add(miscTxt);
        guiDialog.add(new Label("    "));
        guiDialog.add(btMemory);
        Point point = new Point();
        point = guiFrame.getLocation();
        int x = (int)point.getX();
        int y = (int)point.getY();
        guiDialog.setLocation(60 + x, 70 + y);
        guiDialog.setSize(320, 150);
        guiDialog.setVisible(true);
    }

    private void configMemoryExec()
    {
        String _str = cbg.getSelectedCheckbox().getLabel();
        if(_str == "8kb")
            ram8k = true;
        if(_str == "Max")
            ram8k = false;
        mem.setRam8k(ram8k);
        writeInRom = wRomCbox.getState();
        mem.setWriteInRom(writeInRom);
        int brkVector = hexStringToInt(miscTxt.getText());
        mem.write(65534, brkVector & 0xff);
        mem.write(65535, brkVector / 256 & 0xff);
        guiDialog.dispose();
    }

    private void aboutPom1()
    {
        TextArea ta = new TextArea(" *Pom1 0.7b* the Java Apple I Emulator\nWritten by Verhille Arnaud\nE.mail : gist@wanadoo.fr\nhttp://www.chez.com/apple1/\n\nEnhanced by Ken Wessen (21/2/06)\n\nThanks to :\nSteve Wozniak (The Brain)\nFabrice Frances (Java Microtan Emulator)\nAchim Breidenbach from Boinx Software \n(Sim6502, Online 'Apple-1 Operation Manual')\nJuergen Buchmueller (MAME and MESS 6502 core)\nFrancis Limousy (for his help, and his friendship)\nStephano Priore from the MESS DEV\nJoe Torzewski (Apple I owners Club)\nTom Owad (http://applefritter.com/apple1/)", 23, 45, 3);
        ta.setEditable(false);
        guiDialog.removeAll();
        guiDialog.setTitle("About Pom1");
        guiDialog.setLayout(new FlowLayout());
        guiDialog.add(ta);
        Point point = new Point();
        point = guiFrame.getLocation();
        int x = (int)point.getX();
        int y = (int)point.getY();
        guiDialog.setLocation(60 + x, 70 + y);
        guiDialog.setSize(375, 250);
        guiDialog.pack();
        guiDialog.setVisible(true);
    }

    private int hexStringToInt(String s)
    {
        return Integer.parseInt(s, 16);
    }

    private String toHex(int i)
    {
        String s = Integer.toHexString(i).toUpperCase();
        if(i < 16)
            s = "0" + s;
        return s;
    }

    private String toHex4(int i)
    {
        String s = Integer.toHexString(i).toUpperCase();
        if(i < 4096)
        {
            s = "0" + s;
            if(i < 256)
            {
                s = "0" + s;
                if(i < 16)
                    s = "0" + s;
            }
        }
        return s;
    }

    private Frame guiFrame;
    private MenuBar guiMenuBar;
    private Menu guiMenuFile;
    private Menu guiMenuEmulator;
    private Menu guiMenuConfig;
    private Menu guiMenuDebug;
    private Menu guiMenuHelp;
    private MenuItem guiMenuFileLoad;
    private MenuItem guiMenuFileSave;
    private MenuItem guiMenuFileSeparator;
    private MenuItem guiMenuFilePaste;
    private MenuItem guiMenuFileExit;
    private MenuItem guiMenuEmulatorReset;
    private MenuItem guiMenuEmulatorHardReset;
    private MenuItem guiMenuConfigScreen;
    private MenuItem guiMenuConfigMemory;
    private MenuItem guiMenuDebugShow;
    private MenuItem guiMenuDebugDispose;
    private MenuItem guiMenuHelpAbout;
    private Dialog guiDialog;
    private Button btSave;
    private Button btLoad;
    private TextField startHexTxt;
    private TextField endHexTxt;
    private TextField miscTxt;
    private Checkbox rawCbox;
    private Checkbox wRomCbox;
    private CheckboxGroup cbg;
    private Button btScreen;
    private Button btMemory;
    private Button bt6502;
    private int pixelSize;
    private boolean scanlines;
    private int terminalSpeed;
    private boolean writeInRom;
    private boolean ram8k;
    private Memory mem;
    private M6502 micro;
    private Pia6820 pia;
    private Screen screen;

}
