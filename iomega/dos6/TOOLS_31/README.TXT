
                           README FILE
                          July 21, 1998
                 IomegaWare Software Version 1.0
     
     Contents
     Section  #     Topic
           1   Using the Guest Program
           2   Software Installation Troubleshooting
           3   Electronic Manuals
           4   Cautions and Technical Notes
                    Microsoft Disk Copy Utilities
                    FDISK
                    32-bit Access
                    Windows Format Utility
                    Microsoft Backup
                    Compression
                    Installing Applications to the Zip Drive
           5   Pass-Through on the Parallel Port Zip Drive
                    Printers
                    Other Pass-Through Devices
           6   Optimizing Parallel Port Zip Drive Transfer Speed
                    Under DOS

          
     _________________________________________________________
     Section 1
     Using the Guest Program
     
     The Guest program allows you to use a portable Zip drive on
     another computer without having to permanently install
     either an Iomega driver or Zip Tools software.
     
     There are versions of Guest for Windows 95/98, Windows 3.1/DOS
     and Macintosh systems:  

       *  For Windows 95/98, run GUEST9X.EXE from the Windows/DOS
          Install disk (floppy or CD).  If you encounter any problems, see
          "GUEST9x.HLP" on the Install diskette.

       *  For Windows 3.1/DOS systems, run GUEST.EXE from the
          from the Windows/DOS Install diskette.  Refer to the
          GUESTHLP.TXT file on the Install diskette for
          additional information on using GUEST.EXE with IBM-
          compatible PC's.
     
      *   For information on using Guest on Macintosh systems,
          refer to the GUESTHLP.TXT file on the Windows/DOS
          Install diskette.
     
     NOTE:  On Windows 3.1, DOS, or Macintosh systems, running
     the Guest program provides a temporary driver installation
     that is removed when the computer is shut down or restarted. 
     Running Guest permanently installs the drivers needed to
     support Iomega hardware under Windows 95/98.
     
     
     _________________________________________________________
     Section 2
     Software Installation Troubleshooting
     
     Refer to the MANUAL.EXE file on the Windows/DOS Install
     diskette for software troubleshooting information on
     computers running Windows 95/98, Windows 3.1, and DOS.  Section
     4 in this Readme file contains detailed instructions on
     accessing MANUAL.EXE.

     Note for users of Adaptec EZ-SCSI:
     For information on using Iomega software and Adaptec EZ-SCSI
     on the same system, refer to "Special Information for Users
     of Adaptec EZ-SCSI" in Appendix A of MANUAL.EXE.
     
     
     
     _________________________________________________________
     Section 3
     Electronic Manuals
     
     The Iomega software package for Windows/DOS includes two
     electronic manuals:

      *   The "Iomega Installation Manual" (MANUAL.EXE) which
          contains complete installation and problem-solving
          information for Iomega software under Windows 95/98,
          Windows 3.1, and DOS.

      *   The "User's Reference Manual" (REFMAN.EXE) which
          contains reference information on Iomega SCSI software,
          including the Iomega Driver, configuration program, and
          Iomega SCSI Utilities.

     To access the Installation Manual, insert the Windows/DOS
     "Install" disk in an appropriate drive (floppy or CD-ROM),
     go to the DOS prompt, and type:
     
               A: <Enter> (or D: where D is your CD-ROM drive)
               MANUAL <Enter>
     
     You can also run the Installation Manual from the Windows
     File Manager by selecting drive A: and double-clicking on
     MANUAL.EXE.  Under Windows 95/98, you can access the
     Installation Manual by double-clicking on the floppy drive
     in My Computer and then double-clicking on the "Manual"
     icon.
     

     The User's Reference Manual is located in the DOSSTUFF
     directory on the Zip "tools" disk and installed with the
     Iomega SCSI software package.  Use the following procedure
     if you want to access the reference manual before installing
     your software:

      1.  Insert the "Install" disk (floppy or CD) for
          Windows/DOS into the appropriate computer drive and the
          "tools" disk into the Jaz drive.

      2.  Go to the DOS prompt and type:

               a:guest.exe <Enter> (Install floppy in drive A)

                         or
    
               b:guest.exe <Enter> (Install floppy in drive B)

      3.  Note the drive letter Guest assigns to your Zip drive
          and use it in place of "d:" in the following command
          line:

               d:\dosstuff\refman <Enter>


     If you install Iomega SCSI software using the INSTALL
     program, you can access the User's Reference manual from the
     C:\IOMEGA directory after the software installation is
     complete.  Go to the DOS prompt and type:

                    c: <Enter>
                    cd \iomega <Enter>
                    refman <Enter>


     _________________________________________________________
     Section 4
     Cautions and Technical Notes

     
     ______________________________
     Section 4.1
     Microsoft Disk Copy Utilities
     
     CAUTION! 
     Do NOT use DISKCOPY.EXE or the Windows 95/98 right mouse
     CopyDisk utility with your Zip drive.  These utilities were
     designed for use with floppy drives and do not work
     correctly with other removable drives.  Use an Iomega disk
     copying utility to copy disks (either Copy Machine or Iomega
     SCSI Disk Copy).


     ______________________________
     Section 4.2
     FDISK

     CAUTION! 
     Do not use FDISK on any removable disk.  FDISK is designed
     for partitioning fixed disks.  Partitioning any type of
     removable media can lead to unexpected results.


     ______________________________
     Section 4.3
     32-bit Access

     If you are using Windows 3.11 or Windows for Workgroups and
     want to use Copy Machine, make sure that 32-bit disk and
     file access is turned off. (This option is available when
     changing virtual memory options under "386 Enhanced" in the
     Windows Control Panel.)

     NOTE: Windows 3.1 does not support 32-bit access for
     removable disks drives. If 32-bit access is not turned off,
     the hard drive will NOT appear in the Copy Machine window.

     
     ______________________________
     Section 4.4
     Windows Format Utility

     If you are using Windows 3.1, do not use the format utility
     available in Windows File Manager to format Zip disks.  Use
     an Iomega format utility (either Iomega SCSI Format or
     Format in Iomega Tools).

     
     ______________________________
     Section 4.5
     Microsoft Backup

     Microsoft Backup does not support removable disk drives
     other than floppy drives.  You can use Copy Machine to copy
     files on your hard disk to the Zip drive, or you can use the
     Windows File Manager to drag-and-drop files you want to back
     up to Zip disks.

     
     ______________________________
     Section 4.6
     Compression
     
     CAUTION! 
     If you are using a compression utility on a removable disk
     (for example, a Zip disk), you should make that disk
     nonremovable (or lock the disk in the drive) whenever the
     compressed volume is mounted.  Removing a disk while the
     compressed volume is mounted could result in lost data.  To
     remove the disk, first unmount the compressed volume, then
     unlock the drive.  Refer to the electronic "User's Reference
     Manual" (REFMAN.EXE) for detailed information on locking and
     unlocking drives.
     
     CAUTION! 
     Do not use any disk compression software to compress
     removable boot disks.


     Iomega SCSI Utilities with Stacker 4.0
     
     When using Stacker 4.0 and Iomega SCSI, mounted, stacked
     drives will not appear on the graphical user interface
     screen for the Iomega SCSI Utilities.  In order to use an
     Iomega SCSI utility on a stacked drive, you must first
     unmount the drive.
     
          
     ______________________________
     Section 4.7
     Installing Applications to the Zip Drive

     Certain applications and games will install only to a fixed
     disk.  To install these programs to the Zip drive, use the
     Iomega Tools "Make Nonremovable" or "Lock" utility to make
     the Zip drive appear as a hard drive to the system.  After
     the software installation is complete, use "Make Removable"
     or "Unlock" to restore disk removability.



     _________________________________________________________
     Section 5
     Pass-Through on the Parallel Port Zip Drive
     
     This section describes how to handle problems you may
     encounter when connecting printers or other parallel port
     devices to the pass-through connector on the Zip drive.


     ______________________________
     Section 5.1
     Printers
     
     The parallel port Zip drive supports most printers on the
     pass-through connector; however, some printers require
     exclusive use of the parallel port and will not work
     correctly when connected to the Zip pass-through.  Because
     these printers cannot share the parallel port, your system
     may stop responding if you attempt to use the printer and
     your Zip drive at the same time (for example, if you attempt
     to print a file from a Zip disk).

     If you are having problems with your printer when it is
     connected to the Zip pass-through connector, try the
     following:

       *  Try powering on your computer, printer, and Zip drive
          all at the same time by plugging them into the same
          power strip and applying power at the power strip.
     
       *  If you are using Windows 3.1, disable Disk Watch by
          removing it from your Windows Startup folder and then
          restarting Windows.  Disk Watch periodically wakes up
          the Zip drive and checks its status, which temporarily
          disables the Zip pass-through.

       *  Some Print Cache programs may conflict with the
          parallel port Zip drive.  If you have Print Cache on
          your system, disable the audio warning messages for
          both Windows and DOS using the reinstall procedure in
          the Print Cache manual.  (If you encounter problems
          reinstalling, please contact your Print Cache Software
          Technical Support.)

       *  If you have Microsoft Print System installed on your
          computer, try using it to disable bi-directional
          communication to the printer.  (Remove the check mark
          from the box next to "Use bi-directional
          communication.")

       *  Try setting your printer to "Print to File" whenever
          it's not in use.  This will enable you to use your Zip
          drive without problems as long as you are not printing. 
          When you want to print a file from your hard disk (or
          any disk other than a Zip disk), close any files that
          may be open on your Zip disk and return the printer
          setting to normal.  Do not attempt to access your Zip
          drive until the print job is completed and you have
          changed the printer setting back to "Print to File."

     If you are unable to use your printer and the Zip drive at
     the same time, the best solution is to add an additional
     parallel port to your computer, then use the Zip drive on
     one parallel port and your printer on the other.  Most
     computer stores carry simple I/O cards that let you easily
     add a new parallel port.  Warp Nine Engineering (formerly
     FarPoint Communications) produces an I/O card, F/PortPlus,
     which is fully compatible with the Zip drive and will
     improve your drive's performance.  (Information on this card
     is available from Iomega's Automated FAX Help system at
     (801)778-5763, or you can contact Warp Nine Engineering at
     http://www.fapo.com.)  Contact your computer dealer if you
     wish to purchase a card.


     ______________________________
     Section 5.2
     Other parallel port devices

     Parallel port devices other than printers may or may not
     work on the Zip pass-through connector.  This problem exists
     because computer parallel ports were not originally designed
     for devices other than printers.  If you try placing a
     device other than a printer on the Zip pass-through, or
     place the Zip drive on another device's pass-through, there
     are no guarantees that it will work correctly.  

     In the future there will be a standard for daisy-chaining
     devices on the parallel port; when this standard is
     implemented, Iomega will also conform to it.  In the mean
     time, try the suggestions listed under Section 7.1 for
     solving printer problems.  If your parallel port devices
     still do not operate correctly on the Zip pass-through
     connector, or the Zip drive does not operate correctly on
     their pass-through, you may want to think about adding an
     extra parallel port to your computer as described in
     Section 7.1.



     _________________________________________________________
     Section 6
     Optimizing Parallel Port Zip Drive Transfer Speed under DOS

     The parallel port model of the Zip drive supports three
     modes of data transfer which have different transfer speeds. 
     To ensure the broadest base of compatibility for the Zip
     drive, the Iomega installation software for DOS
     automatically uses the most compatible, but slowest,
     transfer mode.  In this mode, the transfer speed for the Zip
     drive is about 2MB to 6MB per minute, depending on the
     computer's processor speed.

     If the computer has a bi-directional parallel port, the Zip
     drive can be set to use a mode which provides data transfer
     speeds of 6MB to 17MB per minute, depending on the
     computer's processor speed.  (If you are not sure whether
     your computer has a bi-directional parallel port, refer to
     the owner's manual that came with your computer.)
     
     The fastest mode supported by the Zip drive requires a
     special "Enhanced Parallel Port" (EPP) chip set to be
     present on the host computer.  In this mode, the data
     transfer speed for the Zip drive is about 17MB to 22MB per
     minute, depending on the computer's processor speed. 
     Because of the variety of EPP chip sets, and because there
     are some chip sets that mimic a true EPP chip but do not
     support EPP transfers, not all systems with "EPP" can
     support this mode for the Zip drive.
     
     Iomega software for Zip includes a parallel port accelerator
     that can automatically set up both your computer and your
     Iomega software to use the fastest transfer mode for the Zip
     drive that is supported by your computer hardware.  Under
     Windows 95/98, you can run the parallel port accelerator by
     double-clicking on the icon in the Iomega Tools folder on
     your Start Programs menu.  For Windows 3.1, double click on
     the "Parallel Port Accelerator" icon in your Iomega Zip
     Tools Windows group.  

     Under DOS, run the OPTPPM1.EXE utility as follows:
     
     Step 1: If you have not already done so, install your Zip
     software package following the instructions in step 10 of
     the Zip Installation Guide.

     Step 2: Go to the DOS prompt for drive C: and type:

               cd \iomega <Enter>
               optppm1 <Enter>
     
     
     NOTE:  If you wish to restore the default settings on your
     system, run "OPTPPM1.EXE /NIBBLE" from the DOS prompt. 
     (This works under Windows 3.1 as well as DOS.)
