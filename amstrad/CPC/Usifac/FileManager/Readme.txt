This is a quick user's guide for a simple file manager for Amstrad cpc, equipped with USIfAC II interface:


Copy contents of the folder to usb flash drive root dir,and give to Basic prompt: RUN"FM (or RUN"FSM if you want to get file sizes along with file names,but note that respond is a bit slower compared to the plain filemanger showing only filenames)

Select 'Y'/'y' (Check with |STAT if your board has rev_4c firmware or newer, and then you can also choose "n"/"N")

Use keys:
- Left-Right arrows for changing pages. 
- Up/Down arrows for seeking file/dir names into each page.
- <Return> for taking action: 
                             -If selected name is a directory it will move into it. 
					  -If it's a "DSK" image it will give you a catalogue of the disk image(CPC6128/664) or it will reset (CPC464) and then you can access image by giving "CAT".
					  -If it's a SNA smapshot file, it will load it.
					  -If it's a file,it will try to execute it.
  
- <SPACE> Moves up a directory, if you are inside a sub folder you can also use "." or ".." at the top of first page

- <1> enables/disables treating of all names as directories. You get a note on top right corner of the screen when enabled. This is useful if some directories don't appear the <DIR> notification at the end.Alternatively you can remove the "archive" bit property, from all files/directories, then all directories will be shown properly (with <DIR> notification)

 
notes:

  - File manager supports up to ~1000 filenames/directories and maximum 50pages (25 filenames/page)
  - by continiously pressing up/down arrows you will get faster movement for quicker seeking,press momentarily for slower "row by row" seeking.
  -.txt and .asm contains the BASIC programs and assembly source code.
  - FM file is a small BASIC program,if you want,you can customize it, to remove the initial question,changing colors of letters/background etc.
  - If a game/program doesn't run directly through file manager,you can reset, give cat and run it from "clean start" (before that, make sure that "Return to root directory" is disabled by giving an: OUT &FBD1,65) 