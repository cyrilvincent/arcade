// This script installs shortcut in Windows Program Menu


Shell = WScript.CreateObject("WScript.Shell");
FullName = WScript.ScriptFullName;
sZ81Path = FullName.substr(0, FullName.length-WScript.ScriptName.length-9);

fso = new ActiveXObject("Scripting.FileSystemObject");
MenuPath = Shell.SpecialFolders("Programs")+"\\sZ81 emulator";     
if ( ! fso.FolderExists(MenuPath) )
	fso.CreateFolder(MenuPath);     

answer=Shell.Popup("This scrip will install a new folder in Windows Program Menu \n"
		+"\n"
		+"\n"
		+"\n"
		+"\n"
		+"\n"
		+"Read sZ81 info ?\n"
		,0,"sZ81 links",4+32);
if (answer==6)
	Shell.Run("notepad "+sZ81Path+"\ReadMe.TXT",1,true);

// Création du raccourci sZ81.lnk
link = Shell.CreateShortcut(MenuPath + "\\sZ81.lnk");
link.Description = "sZ81 - Zx81 emulator";
link.IconLocation = sZ81Path + "WinSetup\\sZ81.ico";
link.TargetPath = sZ81Path + "sZ81.exe";
link.WindowStyle = 0;
link.WorkingDirectory = sZ81Path ;
link.Save();

// Création du raccourci sZ81_Help.lnk
link = Shell.CreateShortcut(MenuPath + "\\sZ81 Help.lnk");
link.Description = "sZ81 Help - Zx81 emulator";
link.IconLocation = sZ81Path + "WinSetup\\help.ico";
link.TargetPath = sZ81Path + "sZ81.exe";
link.Arguments = "-h";
link.WindowStyle = 0;
link.WorkingDirectory = sZ81Path ;
link.Save();

// Création du raccourci sZ81_TreeForth.lnk
link = Shell.CreateShortcut(MenuPath + "\\sZ81_TreeForth.lnk");
link.Description = "sZ81 - TreeForth ROM (ZX81-NTSC emulator)";
link.IconLocation = sZ81Path + "WinSetup\\4TH.ico";
link.TargetPath = sZ81Path + "sZ81.exe";
link.Arguments = "-f";
link.WindowStyle = 0;
link.WorkingDirectory = sZ81Path ;
link.Save();

// Création du raccourci sZ81-ZX80.lnk
link = Shell.CreateShortcut(MenuPath + "\\sZx81_ZX80.lnk");
link.Description = "sZ81 - ZX80 emulator";
link.IconLocation = sZ81Path + "WinSetup\\ZX80.ico";
link.TargetPath = sZ81Path + "sZ81.exe";
link.Arguments = "-o";
link.WindowStyle = 0;
link.WorkingDirectory = sZ81Path ;
link.Save();

// Création du raccourci sZx81.lnk (ZonX)
link = Shell.CreateShortcut(MenuPath + "\\sZ81_ZonX.lnk");
link.Description = "sZ81 + ZonX sound card emulator";
link.IconLocation = sZ81Path + "WinSetup\\ZonX.ico";
link.TargetPath = sZ81Path + "sZ81.exe";
link.Arguments = "-a zs";
link.WindowStyle = 0;
link.WorkingDirectory = sZ81Path ;
link.Save();

// Création du raccourci sZ81.lnk (QuickSilva)
link = Shell.CreateShortcut(MenuPath + "\\sZ81_QS.lnk");
link.Description = "sZ81 + QuickSilva sound card emulator";
link.IconLocation = sZ81Path + "WinSetup\\QS.ico";
link.TargetPath = sZ81Path + "sZ81.exe";
link.Arguments = "-a qs";
link.WindowStyle = 0;
link.WorkingDirectory = sZ81Path ;
link.Save();

// Création du raccourci sZ81.lnk (STEREO)
link = Shell.CreateShortcut(MenuPath + "\\sZ81_ST.lnk");
link.Description = "sZ81 + Stereo sound card emulator";
link.IconLocation = sZ81Path + "WinSetup\\ST.ico";
link.TargetPath = sZ81Path + "sZ81.exe";
link.Arguments = "-a s";
link.WindowStyle = 0;
link.WorkingDirectory = sZ81Path ;
link.Save();

// Création du raccourci info.
link = Shell.CreateShortcut(MenuPath + "\\ReadMe.lnk");
link.Arguments = "";
link.Description = "sZ81 ReadMe";
link.IconLocation = sZ81Path + "WinSetup\\help.ico";
link.TargetPath = sZ81Path + "readme.TXT";
link.WindowStyle = 2;
link.WorkingDirectory = sZ81Path ;
link.Save();

 key =  "HKEY_CLASSES_ROOT\\"
 Shell.RegWrite( key + "Applications\\sZ81.EXE\\shell\\open\\command\\", "\""+sZ81Path+"sZ81.exe\" \"%1\"");
 Shell.RegWrite( key + ".P\\", "sZ81.P");
 Shell.RegWrite( key + ".O\\", "sZ81.O");
 Shell.RegWrite( key + ".81\\", "sZ81.81");
 Shell.RegWrite( key + ".Z81\\", "sZ81.Z81");


 Shell.RegWrite( key + "sZ81.P\\", "sZ81 ZX81 P Tape");
 Shell.RegWrite( key + "sZ81.O\\", "sZ81 ZX80 O Tape");
 Shell.RegWrite( key + "sZ81.81\\", "sZ81 ZX81 81 Tape");
 Shell.RegWrite( key + "sZ81.Z81\\", "sZ81 ZX81 Z81 Memory snap");


 Shell.RegWrite( key + "sZ81.P\\DefaultIcon\\", sZ81Path+"WinSetup\\Pfiles.ico");
 Shell.RegWrite( key + "sZ81.O\\DefaultIcon\\", sZ81Path+"WinSetup\\Ofiles.ico");
 Shell.RegWrite( key + "sZ81.81\\DefaultIcon\\", sZ81Path+"WinSetup\\Pfiles.ico");
 Shell.RegWrite( key + "sZ81.Z81\\DefaultIcon\\", sZ81Path+"WinSetup\\Z81files.ico");

 Shell.RegWrite( key + "sZ81.P\\shell\\Launch sZ81\\command\\", "\""+sZ81Path+"sZ81.EXE\"\"%1\"");
 Shell.RegWrite( key + "sZ81.O\\shell\\Launch sZ81\\command\\", "\""+sZ81Path+"sZ81.EXE\"\"-o %1\"");
 Shell.RegWrite( key + "sZ81.81\\shell\\Launch sZ81\\command\\", "\""+sZ81Path+"sZ81.EXE\"\"%1\"");
 Shell.RegWrite( key + "sZ81.Z81\\shell\\Launch sZ81\\command\\", "\""+sZ81Path+"sZ81.EXE\"\"%1\"");

