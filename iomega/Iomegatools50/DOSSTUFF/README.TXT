
                           README FILE
                           May 2, 1996
                  Zip Tools Software, Version 5.0
     
     Contents
     
     Section  #     Topic
           1   Using the 100MB Zip "tools" Disk
           2   Using the Guest Program
           3   Installing Zip Support on DOS-Only Systems
                    Iomega Driver for DOS
                    Zip Tools under DOS
           4   Installation Troubleshooting
                    Duplicate drive letters
                    No drive letter available for the Zip drive
                    Guest does not assign a drive letter to the
                         Zip drive
                    Other problems
                    Special Information for Users of 
                         Adaptec EZ-SCSI
           5   Electronic Manuals
           6   Cautions
           7   Pass-Through on the Parallel Port Zip Drive
                    Printers
                    Other Pass-Through Devices
           8   Optimizing Parallel Port Zip Drive Transfer Speed
                    Under DOS

          
     _________________________________________________________
     Section 1
     Using the 100MB Zip "tools" Disk
     
     The 100MB Zip "tools" disk included with your Zip drive is a
     special dual-format disk which contains Zip Tools software
     for BOTH Windows/DOS and Macintosh systems.  Before you can
     write any files to the disk, the disk format must be set as
     EITHER Windows/DOS (IBM-compatible PC) or Macintosh (which
     allows you to store your files safely but eliminates the
     Tools software files stored under the other format type). 
     Running the software Setup program under either Windows 95
     or Windows 3.1 automatically sets the "tools" disk format to
     Windows/DOS and reclaims the Macintosh portion of the disk
     for use on PC systems.  Similarly, running the Zip Install
     program for Macintosh, sets the "tools" disk format to
     Macintosh and erases the PC portion of the disk.  If you are
     installing Zip software support on a DOS-only system, you
     need to run the Reclaim program as described in your Zip
     Installation Guide to set the disk format and unlock the
     disk.
     
     If you use your Zip drive on both PC and Macintosh systems
     and want to install Zip Tools on both system types, you need
     to purchase an additional "tools" disk for installing Zip
     Tools on your second system.  (See your Zip Accessory Guide
     for ordering information.)
     
     NOTE:  The Zip "tools" disk can be used to reinstall Zip
     Tools software on the SAME system type (PC or Macintosh) as
     the initial installation.  Be sure not to delete any of the
     original files from the disk in case you ever need to
     reinstall your Zip Tools software.
     
     
     _________________________________________________________
     Section 2
     Using the Guest Program
     
     The Guest program allows you to use a portable Zip drive on
     another computer without having to permanently install
     either an Iomega driver or Zip Tools software.  All you have
     to do is connect the Zip drive to the computer and to an
     Iomega Zip power supply, and then run the Guest program from
     a floppy diskette to load the Guest driver.
     
     There are versions of Guest for Windows 95, Windows 3.1/DOS
     and Macintosh systems:  

       *  For Windows 95, run Guest95 from the "Install" floppy
          diskette for Windows/DOS.  If you encounter any
          problems, see "Help for Guest95" on the "Install"
          diskette.

       *  For Windows 3.1/DOS systems, run GUEST.EXE from the
          "Install" floppy diskette for Windows/DOS.  Refer to
          the GUESTHLP.TXT file on the "Install" diskette for
          additional information on using GUEST.EXE with IBM-
          compatible PC's.  (If you install Zip Tools software
          under Windows, you will find the same information in
          "Guest Help" in the Iomega Zip Tools group.)  
     
      *   For information on using Guest on Macintosh systems,
          refer to "Guest Help" on the "Install" floppy diskette
          for Macintosh.
     
     NOTE:  On Windows 3.1, DOS, or Macintosh systems, running
     the Guest program provides a temporary driver installation
     that is removed when the computer is shut down or restarted. 
     Running Guest95 permanently installs the drivers needed to
     support Iomega hardware under Windows 95.
     
     
     _________________________________________________________
     Section 3
     Installing Zip Support on DOS-Only Systems
     
     Many of the application programs included in the Zip Tools
     software package require Windows 3.1 or Windows 95.  If you
     do not have Windows on your computer, you can still use the
     Zip drive, but you will not be able to use the Zip Tools
     software that requires Windows.  This section describes the
     software support for Zip drives available for DOS systems
     that do not have Windows.
     
     
     ______________________________
     Section 3.1
     Iomega Driver for DOS
     
     Running the INSTALL program from the DOSSTUFF directory on
     the Zip "tools" disk installs Iomega SCSI software to
     support your Zip drive.  The Iomega SCSI Driver installs as
     a device (SCSIDRVR.SYS) in the computer's CONFIG.SYS file, 
     and because of the way DOS handles drive letter assignments,
     this can shift your existing drive letters.
     
     Iomega software for Zip includes a TSR version of the Iomega
     Driver (GUEST.EXE) which will not cause any driver letter
     shifts when it is installed.  If you prefer using the TSR
     version of the Driver, you can manually install it in your
     AUTOEXEC.BAT file.  Refer to "Special Procedures" in the
     electronic "Installation Manual" (MANUAL.EXE) for
     instructions.  (See Section 5 in this file for detailed
     instructions on accessing the electronic manuals.)
     

     
     ______________________________
     Section 3.2
     Zip Tools under DOS
     
     Iomega SCSI software includes a set of utilities that run
     under DOS.  The Iomega SCSI Utilities handle a number of
     tasks related to using removable SCSI drives and disks,
     including Zip drives and disks.  You can use these utilities
     to set software protection options on your Zip disks, copy
     data to or from Zip disks, format Zip disks, or lock the Zip
     drive so that you can install software to a Zip disk.
     
     You can run the Utilities in an easy-to-use menu mode or
     from the DOS command line.  To start the utilities in menu
     mode, go to the DOS prompt for drive C: (the drive where
     your Iomega SCSI software is installed) and type:
     
                    cd \IOMEGA <Enter>
                    SCSIUTIL <Enter>
     
     If you need help running the Utilities, press <F1> anywhere
     in the Utilities.  Complete reference information on the
     Iomega SCSI Utilities is contained in the electronic "User's
     Reference Manual" (REFMAN.EXE).  (See Section 5 in this file
     for information on accessing the electronic manuals.)
     
     
     _________________________________________________________
     Section 4
     Installation Troubleshooting
     
     This section includes information for the following
     problems:
     
       4.1     Duplicate drive letters
       4.2     No drive letter available for the Zip drive
       4.3     Guest does not assign a drive letter to the Zip
                    drive
       4.4     Other problems
       4.5     Special Information for Users of Adaptec EZ-SCSI
     
     
     _______________________________
     Section 4.1
     Duplicate drive letters
     
     If you see two drive letters for your Zip drive or other
     drive you are using with the Guest driver (GUEST.EXE),
     reboot the computer immediately.  Using your Zip drive when
     duplicate drive letters are present on the system can result
     in data loss.  
     
     After the computer reboots, do not load the Guest driver. 
     You do not need to use Guest to access the Zip drive on this
     system because the Zip drive is already being assigned a
     drive letter.

     Windows 95 Users: If you see multiple drive letters for your
     Zip drive or other Iomega drives, refer to the problem
     solving information in the electronic "Installation Manual"
     (MANUAL.EXE) that is included on the "Install" floppy
     diskette for Windows/DOS. 
     
     
     ______________________________
     Section 4.2
     No drive letter available for the Zip drive
     
     You may see this problem when using the Guest program on
     DOS/Windows 3.1 systems.  For detailed problem-solving
     information, refer to the GUESTHLP.TXT file which is located
     on the "Install" floppy for Windows/DOS.
     
     
     _____________________________
     Section 4.3
     Guest does not assign a drive letter to the Zip drive
     
     If you run the Guest program and it informs you that no
     drive letters were added, and yet you cannot access the Zip
     drive, there is probably a hardware installation problem. 
     Carefully check the steps involved in installing your Zip
     drive.  If you have installed a new adapter, check the
     adapter installation as well.  If you have more than one
     drive connected to a single SCSI adapter, you may have a
     SCSI ID conflict or termination problem.  For detailed
     suggestions to help solve any of these installation
     problems, refer to the electronic "Installation Manual"
     (MANUAL.EXE) located on the "Install" floppy diskette for
     Windows/DOS.
     
     
     _____________________________
     Section 4.4
     Other problems
     
     If you encounter other problems while installing or using
     Zip Tools software or Iomega SCSI, refer to the electronic
     "Installation Manual" (MANUAL.EXE) for additional problem
     solving information. 
     
     
     _____________________________
     Section 4.5
     Special Information for Users of Adaptec EZ-SCSI

     Zip Tools and/or Iomega SCSI software can be used on the
     same system as Adaptec EZ-SCSI without problems if you:

       1. Use the Iomega SCSI driver to support your Iomega
          drives.  (If you are using Zip Tools software under
          Windows 3.1, you must run both the Setup program under
          Windows to install Zip Tools and the Install program
          under DOS to install Iomega SCSI.  See the electronic
          "Installation Manual" (MANUAL.EXE) for detailed
          instructions.)

       2. Use the /I option with SCSICFG.EXE to tell the Iomega
          SCSI software to ignore devices you want controlled by
          the Adaptec ASPIDISK.SYS device driver.

       3. Use the /ID option with ASPIDISK.SYS to specify the
          devices you want it to support.

     NOTE:  Without the /ID option, ASPIDISK.SYS will take
     control of all SCSI devices, including your Iomega drives,
     and you will be unable to use your Zip Tools software or
     Iomega SCSI Utilities.  

     The remaining information in this section explains how to
     use the /ID option with ASPIDISK.SYS and the /I option with
     SCSICFG.EXE.
     
     Using the /ID Option with ASPIDISK.SYS:

     The /ID option is used to specify the devices you want
     supported by your EZ-SCSI software.  To use this option,
     open your CONFIG.SYS file and locate the DEVICE line for
     ASPIDISK.SYS, for example:

               device=c:\scsi\aspidisk.sys /d /pause

     Leave at least one blank space after the last option on the
     line and add an option of the form:

     /ID=[SCSI ID#]+[SCSI ID#]+ ... +[Adapter ID#:SCSI ID#]...

     Where each device you want ASPIDISK.SYS to support is
     specified by its SCSI ID number.  The adapter ID number need
     not be specified if there is only one SCSI adapter in the
     computer, or if the devices to be supported are connected to
     the first SCSI adapter in the computer.  (The adapter ID
     number for the first SCSI adapter is 0; for the second
     adapter the ID number is 1.)

     For example, if you want ASPIDISK.SYS to control a SCSI hard
     drive at SCSI ID 2 on the first or only SCSI adapter, you
     would need edit the CONFIG.SYS file and add /ID=2 to the end
     of the DEVICE line for ASPIDISK.SYS.  (You would also need
     to add /I:2 to the end of the DEVICE line for SCSICFG.EXE in
     the CONFIG.SYS file to tell Iomega SCSI to ignore the SCSI
     hard drive.)

     The following example would tell the ASPIDISK driver to
     support the devices at SCSI ID 0 and SCSI ID 1 on the first
     or only SCSI adapter:

          device=c:\dosstuff\aspidisk.sys /d /pause /id=0+1

     Here are three other examples of command line syntax for the
     ID option.  The second and third examples assume that the
     computer has two host adapters.

          /id=0+4+6      Support devices at SCSI ID's 0, 4, and 6
                         on host adapter #0

          /id=0+1:4+2    Support device at SCSI ID 0 on host
                         adapter #0.  Support device at SCSI ID 4
                         on host adapter #1.  Support device at
                         SCSI ID 2 on host adapter #0.

          /id=0+1+2+1:1  Support devices at SCSI ID's 0, 1, and 2
                         on host adapter #0.  Support device at
                         SCSI ID 1 on host adapter #1.



     Using the /I Option with SCSICFG.EXE:

     To tell Iomega SCSI software to ignore devices you want
     controlled by the Adaptec device driver, modify the DEVICE
     line for SCSICFG.EXE in the CONFIG.SYS file as follows:

          DEVICE=C:\IOMEGA\SCSICFG.EXE /I:[ID,LUN,PORT]

     Where [ID,LUN,PORT] specify the SCSI ID number, logical unit
     number (LUN), and port address (hexadecimal) of the device
     you want SCSICFG to ignore.  If the device specified is a
     host adapter, SCSICFG will ignore all devices connected to
     the adapter.

     For example, the following command line would tell SCSICFG
     to ignore a SCSI hard disk at SCSI ID 0:

          DEVICE=C:\IOMEGA\SCSICFG.EXE /I:0



     _________________________________________________________
     Section 5
     Electronic Manuals

     The Iomega software package for Windows/DOS includes two
     electronic manuals:

      *   The "Iomega Installation Manual" (MANUAL.EXE) which
          contains complete installation and problem-solving
          information for Iomega software under Windows 95,
          Windows 3.1, and DOS, including reference information
          on Iomega ASPI managers.

      *   The "User's Reference Manual" (REFMAN.EXE) which
          contains reference information on Iomega SCSI software,
          including the Iomega Driver, configuration program, and
          Iomega SCSI Utilities.

     To access the Installation Manual, insert the Windows/DOS
     "Install" diskette in a floppy drive (the example below
     assumes drive A:), go to the DOS prompt, and type:
     
               A: <Enter>
               MANUAL <Enter>
     
     You can also run the Installation Manual from the Windows
     File Manager by selecting drive A: and double-clicking on
     MANUAL.EXE.  Under Windows 95, you can access the
     Installation Manual by double-clicking on the floppy drive
     in My Computer and then double-clicking on the "Manual"
     icon.
     

     The User's Reference Manual is located in the DOSSTUFF
     directory on the Zip "tools" disk and installed with the
     Iomega SCSI software package.  Use the following procedure
     if you want to access the reference manual before installing
     your software:

      1.  Insert the "Install" floppy diskette for Windows/DOS
          into the computer's floppy drive and the 100MB "tools"
          disk into the Zip drive.

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
     Section 6
     Cautions

     Observe the following cautions if you are installing Zip
     software for Windows 3.1 and/or DOS.
     
     
     ______________________________
     Section 6.1
     DOS DISKCOPY
     
     CAUTION! 
     When used with removable disks (for example, Zip disks, Jaz
     disks, Bernoulli disks, etc.), DOS DISKCOPY does not create
     a copy of the source disk on the target disk.  DOS DISKCOPY
     executes as if copying data from the source to the target
     disk; however, after completion, the target disk is
     unreadable and must be reformatted.  Use an Iomega disk
     copying utility to copy disks (either Copy Machine or Iomega
     SCSI Disk Copy).
     
     
     ______________________________
     Section 6.2
     Compression
     
     Stacker 4.0 works with removable disks supported by
     GUEST.EXE (for example, Zip disks); however, do not reboot
     when Stacker asks if you want to reboot to remove TSR's. 
     Rebooting removes the Guest driver and eliminates access to
     the Zip drive.

     DoubleSpace and DriveSpace do not work with disks supported
     by GUEST.EXE, but they do work with the Iomega SCSI driver. 
     If you want to use DoubleSpace or DriveSpace to compress
     your Zip disks or other removable disks, install the Iomega
     SCSI driver in your CONFIG.SYS file to support your
     removable drives.  Refer to the electronic "Installation
     Manual" (MANUAL.EXE) for detailed instructions on running
     the INSTALL program from the DOSSTUFF directory on the Zip
     "tools" disk.  If you use Windows, also install your Zip
     Tools software for Windows by running the Setup program
     after installing Iomega SCSI.

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
     Section 6.3
     Shifting Drive Letters
     
     The following caution applies only if you are installing Zip
     support on a DOS-only system or if you choose to install the
     Iomega Driver, SCSIDRVR.SYS, in your CONFIG.SYS file.
     
     CAUTION! 
     Installing the Iomega SCSI driver may cause your drive
     letters (including network drives) to change.  This could
     affect Windows applications that reference existing drives. 
     Check your Windows groups and "ini" files.  For additional
     information, refer to "Relocating Drive Letters" in the
     electronic "Installation Manual" (MANUAL.EXE).


     
     _________________________________________________________
     Section 7
     Pass-Through on the Parallel Port Zip Drive
     
     This section describes how to handle problems you may
     encounter when connecting printers or other parallel port
     devices to the pass-through connector on the Zip drive.


     ______________________________
     Section 7.1
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
         add a new parallel port.  FarPoint Communications produces
         an I/O card which is fully compatible with the Zip drive and
         will improve your drive's performance.  (Information on this
         card is available from Iomega's Automated FAX Help system at
         (801)778-5763.)  Contact your computer dealer if you wish to
         purchase a card.


         ______________________________
         Section 7.2
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
         Section 8
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
         Windows 95, you can run the parallel port accelerator by
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
