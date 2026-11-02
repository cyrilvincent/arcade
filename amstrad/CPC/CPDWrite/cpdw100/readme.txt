v1.00 CPDWrite - Copy Protected Disk Writer
                 Copyright (c) 1997 by Ulrich Doewich


SYNOPSIS .................................................................

 CPDWrite is a command line driven utility, used to write emulator disk
 images to any disk drive attached to the PC. Currently supported are the
 most popular emulator image formats of the Amstrad CPC range and the Atari
 ST.

 Use CPDWrite to write .DSK (normal or extended), .MSA (normal or
 uncompressed; single or multi-part) and .ST images to floppy disks. In
 doing so, CPDWrite will attempt to recreate any copy protection schemes
 that the image might hold.


DISCLAIMER ...............................................................

 This software is provided as is. The author accepts no responsibility for
 damages occurring as a direct or indirect result of using this software.


SOFTWARE LICENSE .........................................................

 CPDWrite is Fairware - if you find yourself using it extensively, I would
 be delighted if you showed your appreciation by sending me a donation. How
 much that might be is entirely up to you. Please see the HOW TO GET IN
 TOUCH section below for my complete address. Thanks.


GETTING STARTED ..........................................................

 Minimum system requirements are:

   386 based PC
   4MB RAM
   MS-DOS v2.0
   5.25", 3.5" or 3" disk drive

 Before you start using CPDWrite, you should load the supplied CPDWRITE.CFG
 file into a text editor (such as EDIT - supplied with all versions of DOS),
 and verify that the defaults given match your particular setup. The
 configuration file consists of a few keywords denoted my the # character.
 These keywords are case insensitive. They should be followed by their
 corresponding value, separated from the keyword by spaces, tabs or equal
 signs. Comments start with a semicolon (;) anywhere on the line. Keywords
 may also be commented out.

 NOTES

 - The #TRACKS keyword is used to specify the maximum amount of tracks to be
   written. If this value is less than the amount of tracks in the image,
   only as many tracks as specified here are written to the disk. If it is
   greater, the surplus in tracks is cleared ("unformatted") on the disk. If
   #TRACKS is set to 0, CPDWrite will use the value specified in the image
   as the number of tracks to write.

 - The #STEP setting has a special function and is only of relevance if you
   use an unusual drive or drive/ media combination (eg. use of a 3" drive,
   or a 360K disk in a 1.2MB drive). In those cases the #STEP parameter
   needs to be set to 2.


USAGE ....................................................................

 CPDWrite may only be used from an MS-DOS prompt. Attempts to run it from
 within any Windows environment will fail, since CPDWrite talks to the PCs
 hardware directly (an action Windows frowns upon). Having said that, here's
 the command line syntax:

CPDWRITE.EXE filename.ext <B> <S>

 A filename is mandatory and can include a full path reference. The
 extension must be included to indicate the type of the image file. All
 other command line switches are optional and can be given in any order, and
 in any case.

 Option B will override the default and redirect all writes to drive B.

 Option S will override the default and redirect all writes to the second
 side of the chosen drive.


OPERATION ................................................................

 While CPDWrite is working, it will display the progress via a track and
 side indicator. Please note that some copy protection schemes require
 longer write times on specific tracks. If CPDWrite takes longer than 2
 minutes on a track, it's save to say something went wrong - please see the
 HOW TO GET IN TOUCH section below in such cases.

 If for some reason you want to abort the write process, use the ESCape key
 to do so. CPDWrite will terminate _before_ writing the current track.


HOW TO GET IN TOUCH ......................................................

 If you want to let me know what you think about CPDWrite, or have a
 suggestion for a future version, drop me a line via one of the following
 methods:

 e-mail:
   ulrich.doewich@shaw.wave.ca

 snail mail:
   Ulrich Doewich
   112 Tea Rose Street
   Markham, Ontario L6C 1X3
   Canada

 You can always find the latest version of CPDWrite and other utilities
 authored by me on the official CPE web site at:

   http://www.tor.shaw.wave.ca/~doewich/cpc

 If you have an image which CPDWrite fails to write to disk, please e-mail
 me a ZIPped copy with a short description of the problem.


ACKNOWLEDGEMENTS .........................................................

 Thanks must go out to..

   Simon Tatham (anakin@pobox.com) and Julian Hall (jules@earthcorp.com),
   for creating NASM - The Netwide Assembler. Anyone interested in this
   _free_ x86 assembler that can produce both 16 and 32bit code should point
   their browser to: http://www.csv.warwick.ac.uk/~csusb/nasm/

   Michael Tippach for creating WDOSX - an excellent freeware 32bit DOS
   extender. Go to http://www.geocities.com/SiliconValley/Park/4493/ for
   more info.

   NEC for writing such a comprehensive User's Manual on the uPD765-A. It
   was a tremendous help for delving into some of the deeper secrets of this
   infamous floppy controller.

   Discology, a CPC disc copier, from which I gleaned (via the FDC debug
   output of CPE) the techniques for recreating some of the copy protection
   schemes out there.

 ..and the following people, which helped in the development process at some
 point or another:

   Kevin Thacker
   Sergio Bayarri
   Damien Burke


HISTORY ..................................................................

 v0.01  May 02, 1997 - 18:20
 v0.02  May 03, 1997 - 16:37
 v0.03  May 03, 1997 - 20:00
 v0.04  May 03, 1997 - 20:24
 v0.05  May 05, 1997 - 12:03  fixed the command-line bug
 v0.06  May 06, 1997 - 23:05  worked on interrupt service routines
 v0.07  May 10, 1997 - 21:02  first working image written!
 v0.08  May 11, 1997 - 00:13  fixed 10 sectors problem
 v0.09  May 14, 1997 - 22:15  new number of tracks calculation
 v0.10  May 19, 1997 - 16:31  improved fault checking
 v0.11  Aug 01, 1997 - 18:53  implemented general write track routine
 v0.12  Aug 01, 1997 - 20:39  generic DSK writing
 v0.13  Aug 02, 1997 - 13:41  preliminary extended DSK support
 v0.14  Aug 02, 1997 - 16:18  CM and unformatted track support
 v0.15  Aug 04, 1997 - 16:59  detection of empty sectors
 v0.16  Aug 04, 1997 - 23:03  updated ST format pre-processor
 v0.17  Aug 05, 1997 - 13:31  preliminary MSA format support
 v0.18  Aug 05, 1997 - 15:39  added RLE decoding to MSA support
 v0.19  Aug 05, 1997 - 19:34  dynamic GAP#3 size calculation
 v0.20  Aug 07, 1997 - 23:42  check for DE sectors + correction of N for format
 v0.21  Aug 10, 1997 - 15:44  preliminary DE sector support (added third case)
 v0.22  Aug 11, 1997 - 13:36  improved DE sector support (added first case)
 v0.23  Aug 12, 1997 - 13:13  changed sector error code handling
 v0.24  Aug 13, 1997 - 21:59  support for multiple IDs per track
 v0.25  Aug 14, 1997 - 11:56  added debugging output
 v0.26  Aug 14, 1997 - 12:31  assembling debug info in memory
 v0.27  Aug 17, 1997 - 12:48  completed DE sector support (added second case)
 v0.28  Aug 18, 1997 - 13:55  fixed normal DSK support
 v0.29  Aug 22, 1997 - 16:07  completely rewrote probe_table
 v0.30  Aug 23, 1997 - 13:36  optimized probe_table
 v0.31  Aug 23, 1997 - 14:55  support for unformatted tracks in normal DSK format
 v0.32  Sep 01, 1997 - 23:43  added command line switches for drive B & side 2
 v0.33  Sep 02, 1997 - 16:18  aborting now possible via ESCape key
 v0.34  Sep 11, 1997 - 17:04  preliminary .CFG file support
 v0.35  Sep 11, 1997 - 19:42  completed configuration file support
 v0.36  Sep 20, 1997 - 13:33  fixed split MSA support
 v0.37  Sep 24, 1997 - 18:40  user definable size of GAP#3 for format command
 v0.38  Sep 24, 1997 - 23:06  improved dynamic GAP#3 size calculation
 v0.39  Sep 25, 1997 - 14:10  added more error messages
 v0.40  Sep 25, 1997 - 21:03  improved error checking in probe_table
 v0.41  Sep 27, 1997 - 13:01  increased timer resolution
 v0.42  Sep 29, 1997 - 21:57  converted to non-DMA mode for all operations
 v0.43  Sep 30, 1997 - 13:27  finally got non-DMA mode to work
 v0.44  Oct 03, 1997 - 11:53  support for 8K sector protections
 v0.45  Oct 03, 1997 - 19:57  utilizing timer2 for precise DE sector recreation
 v0.46  Oct 05, 1997 - 12:46  improved repeating IDs detection
 v0.47  Oct 06, 1997 - 14:14  fixed bugs in GAP#3 size calculation & probe_table
 v0.48  Oct 06, 1997 - 20:21  error recovery via timeout in FDC_execwrite
 v0.49  Oct 07, 1997 - 23:29  major rewrite of pt_specialfmt
 v0.50  Oct 08, 1997 - 14:30  fixed a bug related to new pt_specialfmt routine
 v0.51  Oct 09, 1997 - 14:48  added corruption check to DSK & EDSK image parsing

 v1.00  Oct 14, 1997 - 11:27  first public release
