sz81   - a ZX81 and ZX80 emulator using SDL

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.


*** Please see README.z81 for information about [x]z81, zx81get and
the contents of games-etc and the saverom folders. Contained within
this document is information specific to sz81 only ***


Description
===========

sz81 is a Sinclair ZX80/ZX81 emulator very much based upon the work of
Ian Collier's xz80 and Russell Marks's z81 but employing the highly
portable SDL and including additional functionality and features for
desktop computers and portable devices.

Features:
 * Virtual keyboard with adjustable opacity, autohide on newline,
   sticky shift or toggle shift
 * Control bar with access to several regularly used options
 * Runtime options including a joystick configurator
 * Joystick control remapping within the emulator
 * Full keyboard, mouse and joystick support throughout
 * Runtime switchable scaling up to 3x on supported platforms
 * Toggling between a window and fullscreen on supported platforms
 * Support for portrait orientated screens such as 240x320 and 480x640
 * The ability to run centred within any resolution
 * Maximum porting potential since it only requires SDL


Controls
========

For the PC:

    Click screen - Toggle virtual keyboard and control bar
    Backspace    - Rubout i.e. equivalent to using SHIFT + 0
    Comma        - Equivalent to using SHIFT + .
    Cursors      - Equivalent to using SHIFT + 5, 6, 7 and 8
    -/=          - Decrease/increase the volume (if supported)
    ALT + R      - Cycle between 960x720, 640x480 and 320x240

    F1           - Toggle to Config/Keyboard Screen.

    F3           - About, Help window.

    F4           - Sound card trigger: No sound(default), QuickSilva 
                   Zon-x sound card.

    F8           - invert screen color.

    F9           - Activate the control remapper for remapping
                   joystick controls to keyboard controls.
    F10          - Exit emulator.
    F11          - Toggle between fullscreen and a window.
    F12          - Reset Emulator.


    Clicking the screen (or F1) brings up the virtual keyboard and the
    control bar giving access to several very useful options. These
    are listed below alongside their keyboard equivalents :-

    Exit          - Exit emulator (F10)
    Reset         - Reset emulator (F12)
    Autohide      - Toggle vkeyb between autohide and don't hide (F6)
    Shift Type    - Toggle between sticky shift and toggle shift (F7)
    Invert Screen - Toggle between not inverse and inverse video (F8)
    Opacity DN/UP - Reduce (HOME) or increase (END) vkeyb opacity
    Options       - Toggle the runtime options (ESCAPE) (navigate with
                    page up and page down, the cursor keys and enter,
                    the mouse or the joystick)

    To access the ZX81's file selector type "J", SHIFT + "P" twice and
    newline from within the emulator. For the ZX80 simply type LOAD or
    SAVE to access the file zx80prog.p located within the current
    working directory.

    Configuring a Joystick
    ----------------------
    If you have a digital or analogue joystick plugged in and you'd
    like to use it then open the runtime options (ESCAPE from within
    the emulator or select the rightmost icon on the control bar) and
    utilise the joystick configurator using either the cursor keys and
    enter, directly with the mouse or the joystick once configured.
    Select a control on the graphical joystick representation (the
    selector will blink) and follow the instructions configuring as
    many of the controls as you possibly can for optimum usability.

    Joystick Control Remapping
    --------------------------
    When the virtual keyboard is visible, position the selector over
    the function that you would like to assign to a joystick control
    and press the control remapper (the selector will blink). Then
    press a joystick control to remap the function to the control.
    Existing controls that have been remapped are active within the
    emulator (you cannot remap GUI controls) and new controls are
    universally active. It is possible to include the SHIFT modifier
    within the control as long as it is active before you initiate
    remapping. To cancel remapping press the control remapper again.

For the Amiga:

    As above section "For the PC" plus:

    Tooltypes
    ---------

    sz81 can be configured using tooltypes, which correspond directly
    to command-line options.  Full details of options can be obtained
    with "sz81 -h".  A list of tooltype equivalents follows:

    -a[q;z;s] AYSOUND=QUICKSILVA|ZONX|STEREO
    -d        SHOWDEVICES
    -i        INVERT
    -l        AUTOLIST
    -L        NOLOADHOOK
    -o        ZX80
    -p        ZXPRINTER=<pbm ouput file>
    -r        REFRESH=<1-50>
    -s        SOUND
    -S        NOSAVEHOOK
    -T        TAGULA
    -u        UNEXPANDED
    -V        VSYNC

    Additional tooltypes:
       RESOURCEFILE=<sz81rc file>

    File Selector
    -------------

    The Amiga build uses standard ASL requesters instead of sz81's
    built-in file selector.  It will also allow choosing a ZX80
    file instead of being hard-coded to zx80prog.o

For the Sharp Zaurus:

    Click screen - Toggle virtual keyboard and control bar
    Backspace    - Rubout i.e. equivalent to using SHIFT + 0
    Comma        - Equivalent to using SHIFT + .
    Cursors      - Equivalent to using SHIFT + 5, 6, 7 and 8
    -/=          - Decrease/increase the volume (if supported)

    See PC controls for an explanation of the control bar and how to
    access the file selector.

For the GPH GP2X:

    Within the emulator (remappable)  | Within the GUI
    ----------------------------------+----------------------
    LTrigger     - SHIFT              | SHIFT/Page up
    RTrigger     -                    | Page down
    Joy Left     - O                  | Selector left
    Joy Right    - P                  | Selector right
    Joy Up       - Q                  | Selector up
    Joy Down     - A                  | Selector down
    Select       - Runtime options    | Control remapper
    Start        - Virtual keyboard   |
    Button A     - Newline            | Select (selector hit)
    Button B     - Newline            | Newline
    Button Y     - Rubout (SHIFT + 0) | Rubout (SHIFT + 0)
    Button X     - Space              | Space

    See PC controls for an explanation of the control bar, how to
    access the file selector and joystick control remapping.


Installation
============

To function correctly sz81 expects to find the zx80.rom and zx81.rom
ROMs which are not included within the source package. You might find
them at ftp://ftp.nvg.ntnu.no/pub/sinclair/roms, or perhaps through
searching the internet for "zx80.rom" and "zx81.rom".

Extract the sz81 source package, copy the zx80.rom and zx81.rom ROMs
into the data folder and change into the extracted directory.

For the PC:

    Comment/uncomment the PREFIX BINDIR DOCDIR PACKAGE_DATA_DIR group
    at the top of the Makefile depending on whether you want to do a
    local install, system-wide install or run from the source folder
    (default) and then type :-

    make clean
    make
    (If you're running from the source folder then that's it, but if
    you're installing this locally or system-wide then continue)
    (Installing system-wide requires that you login as root now)
    make install

For the Amiga (requires SDK):

    gmake -f Makefile.amigaos4

    To get all the required files together in RAM:sz81:
    gmake -f Makefile.amigaos4 install

    The directory can then be dragged to final location.

For the Sharp Zaurus (requires SDK):

    make clean
    make -f Makefile.zaurus

    Install sz81_2.1.x_zaurus.ipk using Add/Remove Software.

For the GPH GP2X (requires SDK):

    make clean
    make -f Makefile.gp2x

    Extract sz81_2.1.x_gp2x.tar.gz and copy the contents onto your SD
    card. Note that for Open2x there's Makefile.open2x if you prefer a
    statically linked makefile for this more up-to-date toolchain.


Contacting Us
=============

Please visit the project's support page at
http://sourceforge.net/projects/sz81/support/
or http://sz81.sourceforge.net/download/

2010-04-26

Win32 Dev-C++/GCC/Win32 SDL libs version By Gilles & XavSnap.(2010-10)


