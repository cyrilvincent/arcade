[English]
README.TXT                  MATROX GRAPHICS INC.              1998.11.24

                    Matrox PowerDesk for Windows 95/98
                             Revision 4.28.037


Contents
========

- Description of this release
- Installation
- More information
- Registry settings
- Notes, problems, and limitations
- Matrox Diagnostic program
- IRQSET.EXE program
- Matrox TV output


Description of this release
===========================

This product includes a Windows 95/98 display driver AND the Matrox
PowerDesk for Windows 95/98, which allows: virtual desktop, hardware 
pan and zoom, DirectDraw/Direct3D driver and more...


Installation
============

To install both Matrox PowerDesk and the Matrox display driver, start the
included "setup" program.

The setup program first asks you which language you want to use, then 
to choose between a "Typical" or "Custom" installation. With a 
"Typical" installation, the setup program installs all Matrox PowerDesk
utilities in the default "\Program Files\Matrox MGA PowerDesk" folder.
We recommend you use "Typical".

After PowerDesk is installed, the setup program automatically changes
the Windows 95/98 display driver, then prompts you to restart your computer
for all changes to take effect.

You can customize the installation process by editing the "mga.ini"
file. For example, you can change the default installation path, default
driver performance switches, default schemes, and so on. The file is
self-documented. This type of customization is for advanced users only.


More information
================

For more information on settings, refresh rates etc., see the WordPad
file "online.doc". This file is included on the Matrox disk, and installed
in your "\Program Files\Matrox MGA PowerDesk\" folder.


Registry settings
=================

PowerDesk settings are kept in the Windows 95/98 registry, under the keys:

HKEY_LOCAL_MACHINE\SOFTWARE\MATROX\POWERDESK 
HKEY_LOCAL_MACHINE\SOFTWARE\MATROX\DESKNAV
HKEY_LOCAL_MACHINE\SOFTWARE\MATROX\COLOR CONTROL


Notes, problems, and limitations
================================

- DirectDraw, Direct3D and DirectVideo support

  The DirectDraw driver we provide is compatible with DirectX 2 (and
  later) and includes Direct3D support. For our DirectDraw/Direct3D
  driver to be called, and benefit from hardware acceleration,
  Microsoft DirectX 2 (or later) MUST be installed, even for programs
  originally made for DirectX 1.

  We provide DirectX on the Matrox CD-ROM. The latest DirectX is
  available from the Microsoft Web site, and is included with many 
  DirectX programs.

  IMPORTANT: If the DirectX setup program prompts you to replace the
  existing display drivers, click "No". Otherwise, the setup program 
  installs display drivers which are not as optimized as the Matrox 
  drivers and which do not support PowerDesk software.

  Note that depending on the origin of your Microsoft DirectX software, 
  it may not include DirectVideo support. For faster playback of Indeo 
  and Cinepak AVI files, you should install Microsoft DirectVideo 
  support. 

- Matrox bus mastering

  This driver supports bus mastering. Bus mastering is a feature that 
  allows expansion cards to perform tasks at the same time as your 
  computer's CPU. If you have a fast Pentium computer (faster than 
  166 MHz), the display performance of most programs is improved when 
  bus mastering is used.

  To use bus mastering with 3D (DirectX) programs, your graphics card 
  needs an interrupt request (IRQ). Most computers automatically assign 
  an IRQ to graphics cards, but some do not. If your graphics card hasn't 
  been assigned an IRQ, programs that use Matrox bus mastering may not 
  work properly. For more information, see your Matrox or system manual.

  The Millennium graphics card doesn't support bus mastering. Also, some 
  older computers may not support bus mastering at all.

- Adobe Type Manager limitation

  With Adobe Type Manager installed, you cannot run the driver if
  the "Advanced Graphics Acceleration Settings" is set to none. Note
  that ATM is installed as part of Adobe Acrobat Reader. This is an
  Adobe problem documented in the Windows 95/98 "display.txt" file.

- Monitors in interlaced mode

  Some older monitors such as the NEC 3D and many "SuperVGA" monitors
  do not support non-interlaced mode in all resolutions. The Matrox display 
  driver does not properly handle interlaced mode with the Windows 95/98 
  monitor selection method. If you have one of these monitors, please 
  use the Matrox Monitor selection method.

- DirectDraw and Automatic Power Management

  As stated in "Microsoft DirectX release Notes", September 30, 1995, a 
  DirectDraw game may be unable to restore properly if it is suspended 
  by Automatic Power Management utilities.

- Installation in different language versions of Windows 95/98

  If you install software in a language different from the language of 
  your operating system (for example, English software on a Japanese 
  system), you may have problems with text and dialog box controls being 
  cut off. This is because of differences in system fonts.

- Millennium 3D acceleration library

  The "Millennium 3D acceleration library" is no longer supported. (For
  users of the Millennium graphics card, this option was available in 
  previous versions of Matrox PowerDesk for Windows 95.) The performance
  of a few older 3D programs may be affected. 3D acceleration is
  supported for programs that use DirectX.

- VESA modes

  DOS programs running in DOS full-screen mode are handled by the 
  Matrox Video BIOS. The BIOS supports all standard VGA modes, AND many
  VESA VBE 1.2 and 2.0 modes:

     VESA Graphics Modes
  Mode   Resolution  Colors            
  
  100h   640x400     256        
  101h   640x480     256 
  110h   640x480     32K
  111h   640x480     64K
  112h   640x480     16.8M
  102h   800x600     16
  103h   800x600     256
  113h   800x600     32K
  114h   800x600     64K
  115h   800x600     16.8M
  105h   1024x768    256
  116h   1024x768    32K
  117h   1024x768    64K
  118h   1024x768    16.8M(*)
  107h   1280x1024   256
  119h   1280X1024   32K(*)
  11Ah   1280X1024   64K(*)
  11Ch   1600X1200   256
  11Dh   1600X1200   32K(*)
  11Eh   1600X1200   64K(*)

  (*) requires 4Mb memory

       Text Modes
  Mode   Columns     Rows

  108h      80         60
  109h     132         25
  10Bh     132         50
  10Ch     132         60


Matrox Diagnostic program
=========================

Restart your computer and close all other programs before running Matrox
Diagnostic. 

The Matrox Diagnostic program tests the bus mastering feature of your 
system and if another program is using bus mastering at the same time (a 
3D game for example), a system error may occur.


IRQSET.EXE program
==================

If you have a 3D program for Windows 95/98 that doesn't start or stops 
running, you may be having a problem with bus mastering. The Matrox card
needs an Interrupt Request (IRQ) number for bus mastering to work
properly and some computers do not automatically give the Matrox card an
IRQ. You can manually assign your Matrox card an IRQ through the 
IRQSET.EXE program we provide.

First, check for an IRQ number:

  (1) Right-click "My Computer" on the Windows desktop background.
  (2) Click the "Properties" menu item.
  (3) Click the "Device Manager" tab.
  (4) Click the "Properties" button.
  (5) Check if the Matrox display driver appears in the IRQ list. 
      If it does, there is no need to manually assign an IRQ and you
      can stop here.
      IF NOT, note which IRQ number (10, 11 or 12) is not used and 
      continue with the instructions below.

To manually assign an IRQ (PCI graphics card only):

  (1) Open your "autoexec.bat" file with the Windows 95/98 Notepad program.
      Your autoexec.bat file is in the root directory of your boot 
      drive.

  (2) Add a line to your autoexec.bat with the path to "IRQSET", 
      followed by the IRQ you want to use (the unused number you noted 
      above). For example, to assign your Matrox card IRQ 10, insert the
      following line in your autoexec.bat (INCLUDING the quotation 
      marks):

           C:"\Program Files\Matrox MGA PowerDesk\IRQSET" -i A
		
      (The path you use MIGHT be different if you have a customized 
      installation of Matrox PowerDesk on your computer.)

      The above example is for IRQ 10. To use a different IRQ, replace
      "A" with ONE of the following letters (capitalized):

          B (for IRQ 11)
          C (for IRQ 12)

  (3) Save the changes to the autoexec.bat and exit Notepad.

  (4) Restart your computer for the changes to take effect.


Matrox TV output
================

Certain models of Matrox graphics cards support TV output. With TV output 
support, you can view or record your computer display with a TV or video 
recorder connected to your graphics card.

Notes
-----
When viewing the output of your computer on a TV, your computer monitor 
also uses TV settings. TV settings have lower resolutions and refresh rates 
than typical computer monitor settings. Lower refresh rates may result in 
more noticeable flicker.

Because some computer monitors don't support TV settings, a computer 
monitor may become garbled or unusable while TV output mode is used. If 
this happens, simply turn off your computer monitor and use your TV to view 
your computer display. Your computer monitor will work normally when you 
disable TV output mode.

Recommendation
--------------
- While playing games using TV output, we recommend you use a 640 x 480 
  display resolution. This is because the resolution capabilities of TVs are 
  lower than most computer monitors. If you use a higher display resolution 
  (800 x 600 or 1024 x 768), the display on your TV may not look as sharp as 
  the display of your computer monitor -- that is, some of the extra detail 
  may be harder to see on your TV.

- Matrox default advanced TV output settings are good for viewing most 
  computer graphics (for example, computer games or your Windows desktop) on
  most TVs. Based on broadcast standards, there are advanced TV output 
  settings that are better suited for viewing full-screen video (for example,
  from a video file). These settings are:

  NTSC
     Brightness : 180
     Contrast   : 234
     Saturation : 137
     Hue        : 0

  PAL
     Brightness : 167
     Contrast   : 255
     Saturation : 138
     Hue        : 0

  To access these settings with PowerDesk for Windows 95/98, click "Start" ->
  "Programs" -> "Matrox PowerDesk" -> "Matrox Display Properties" -> 
  "Settings" -> "Advanced" -> "TV Out". For more information on these
  settings, see context-sensitive Help.

  Note: For ideal settings, you may also need to adjust the settings on your 
  TV. The default brightness, contrast, saturation and hue settings on most 
  consumer video devices are higher than broadcast standards. These settings 
  are usually OK for viewing video but may not look OK with computer graphics.
  (This is why Matrox default TV output settings are lower than what's ideal
  for video.) For more information on how to adjust settings on your TV, see 
  your TV manual.

More information
----------------
For more information on display settings, see your Matrox manual and online 
documentation. For information on how to change the display resolution of a 
game you're using, see its documentation.

Note: The Matrox zoom and virtual desktop features aren't supported in TV 
output mode.
