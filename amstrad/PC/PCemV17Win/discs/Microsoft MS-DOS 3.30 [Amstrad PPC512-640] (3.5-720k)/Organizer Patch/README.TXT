AMSTRAD PPC SYSTEMS DISKS, PPC ORGANIZER + PATCH
----------------------------------------------------
Patch created by Banjo
banjo.media@hotmail.com
 28/01/2019
 v1.0
----------------------------------------------

ABOUT:
* This package will enable retro computer enthusiasts and those with nostalgia for Amstrad's PCs in the 1980's to 1990's
  to install the Systems Disks originally bundled with the Amstrad 512/640 PPC "luggable" computers (as well as use the
  unique "PPC Organizer" software that was only ever supplied with these computers) on a non-Amstrad retro PC, or on a
  virtual machine via an emulator like PCem or VirtualBox, or even via DOSBox.
* The patched version of "PPC Organizer" is necessary for all non-Amstrad PCs and virtual machines, since the original
  program required real Amstrad PPC hardware to run.


BEFORE YOU START:
* This package contains the System Disk floppy images (including both the original and "patched" version of disk 1) that you
  can image to real floppies or use in a virtual machine. Also included are loose file versions of the PPC Organizer software
  (pre-patched, for use on DOSBox, etc.) and the patch itself.
* The Amstrad PPC System Disks contain MS-DOS 3.30, and are only really of use to those restoring or emulating a PPC machine.
* The exception to this is the "PPC Organizer" software that is also included on the System Disks. This program - made for
  keeping track of contacts on your business laptop - was only ever available bundled with Amstrad PPC systems and normally
  will not run on any other computer due to hardware checks! The included patch will let you use "PPC Organizer" on a non-
  Amstrad (real) machine, or in a virtual machine or DOSBox.


PATCHING INSTRUCTIONS:
1) If you want to patch the program (i.e. you have an existing install or disk of PPC Organizer), simply copy the files from
   the "Patch" folder, overwriting when asked.
2) Follow the instructions below, depending on what kind of machine you are installing to.


INSTALLATION ON A REAL PC:
* If you want to install the system disks on a real (retro) PC, such as a non-Amstrad XT or AT, insert the patched
  System Disk 1 in the machine's floppy drive and boot it up. It should begin installation automatically.
* Most PPCs normally shipped without a hard drive, so expect to boot from the floppies. However, if you have a hard drive
  installed (the "Sprint" versions of the PPC had 20mb internal drive), you should be able to copy DOS to the hdd and boot
  from that; look up information on how to "install" DOS 3.30 online for help.


INSTALLATION ON A VIRTUAL PC:
* If you want to install the software on a virtual machine emulator, such as PCem (recommended) or VirtualBox,
  first create a period-approriate virtual machine.
* If using PCem, I recommend the "Amstrad PC1640" profile (8086/8 CPU), 640k of RAM, and CGA (green monochrome) graphics, as
  this is very similar to the original PPC640 the software was designed for. I also recommend either two 3.5" 720k floppy
  drives or one floppy drive and a 20mb hard drive.
* Make sure the floppy image of your patched System Disk is inserted in your virtual floppy A drive, then start the 
  virtual machine.


INSTALLATION THROUGH DOSBOX:
* If you want to use PPC Organizer in DOSBox, simply copy the folder "PPCORG" from the "Software" folder of this package to
  whichever folder your DOSBox uses as it's virtual C drive and edit your DOSBox config to emulate a period-appropriate
  machine.


CLOSING NOTES:
* When booted, the Amstrad PPC Series System Disk will give you the following:
  - Microsoft MS-DOS 3.30
  - Amstrad PPC Organizer


TECHNICAL INFO:
* John Elliot (see below) figured out how to make the included patch. To quote him when answering my queries about this:
  "You're correct that it's checking for PPC hardware - specifically, the video hardware. It writes to the CGA mode control
  register (03D8h) and checks that the video NMI system modifies the value written. The conditional jump to be patched out
  is at offset 5796 in RUNALC.EXE - replace 75 17 with 90 90."


CREDITS:
* John Elliott - for figuring out how to patch the PPC Organizer's exe file to make it run on non-original hardware. See: 
  https://www.vogons.org/viewtopic.php?f=61&t=62559#p725857
  Thanks, John! My patch was made entirely using his knowledge.
* Amstrad - now known mostly by retro gamers for their CPC console, their IBM-compatible PCs of the 1980's and 1990's -
  such as the PC1512, PC4386SX, PC5286 and Mega-PC (a PC-Sega Megadrive hybrid!) where the first home computers of many people.
* Cliff Lawson - Amstrad engineer and designer, and maintainer of the best Amstrad resource website.
  http://www.freetimeweb.nl/home/computer/alt/lawsons-amstrad-computer_site/web.ukonline.co.uk/cliff.lawson/index.htm
* FreeDOS - creators of the included new version of "xcopy", that works on modern PCs and DOSBox.
  http://www.freedos.org
* VOGONS - the best place for advice and discussion on old games, programs and machines, and making them work today.
  https://www.vogons.org
* DOSBox - the best way to run DOS games and programs on modern computers.
  https://www.dosbox.com/
* PCem - a virtual machine emulator for recreating early PCs. Highly recommended.
  https://pcem-emulator.co.uk/
