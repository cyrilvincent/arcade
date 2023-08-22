Readme.txt -- Altair32 version 3.31.1400
Release date:  10/06/2012
Document date: 2:24 PM 10/6/2012
e-mail: altair3a2@verizon.net
Web Site:	http://www.classiccmp.org/altair32


Installing the Altair32
=======================

This document describes the steps required to install the Altair32 Emulator.

There are no special requirements for installing the emulator, and no setup
program is provided or required. Therefore, you can unZip the distribution
archive into any subdirectory. Several subdirectories will be created that
contain the help files, sample programs, disk images, and related items.

If you elect to install the Front Panel Support Package first (required if 
you plan on re-compiling the Altair32 Emulator), it will install in a 
subdirectory called "Altair32" which is also a convenient place to install
the emulator files.

If you installed the Front Panel Support Package, it contains a DLL library 
file for use when re-compiling the Altair32 from the source files. This 
library (a file having the "lbr" extension) should be copied from the Front
 Panel Support Package installation directory to the folder used by your 
compiler for other library files. The Altair32 is built using Microsoft 
Visual Studio .NET 2003 and in that version, the library folder is located 
here:  Program Files\Microsoft Visual Studio NET 2003\VC7\lib. 

If you have specified a folder within your build environment for "custom" 
or "user" libraries, you may put the Front Panel library in that directory 
providing the linker has been configured to use that folder. Common errors 
relating to misplaced link libraries is a message about unresolved external 
references.

A support bulletin board has been established at http://www.altair32.com. 
Follow the link found on that page to the Support BBS.


Release Notes - New
===================

This version includes several new features and a few bug fixes to enhancements 
the overall stability of the emulator. The file "Global Change Log.txt"  has
the complete details of what changed in this release.


To Do List
==========
* Get serial ports on the front panel hooked into the emulation context.
* Rewrite certain functions to improve speed and eliminate unsafe
	static buffers.
* Test hard disk emulation.


