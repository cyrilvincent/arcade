// This script installs shortcut in Windows Program Menu
// and registry keys so that Euphoric can be launched by double-clicking
// tape or disk images.


Shell = WScript.CreateObject("WScript.Shell");
FullName = WScript.ScriptFullName;
DskCenterPath = FullName.substr(0, FullName.length-WScript.ScriptName.length);

fso = new ActiveXObject("Scripting.FileSystemObject");
MenuPath = Shell.SpecialFolders("Programs")+"\\DskCenter Multi-Systems Release";     
if ( ! fso.FolderExists(MenuPath) )
	fso.CreateFolder(MenuPath);     

answer=Shell.Popup("This scrip will install a new folder in Windows Program Menu \n"
		+"\n"
		+"\n"
		+"\n"
		+"Read DskCenter info ?\n"
		,0,"DskCenter links",4+32);
if (answer==6)
	Shell.Run("notepad "+DskCenterPath+"Info DskCenter.txt",1,true);

// Création du raccourci DskCenter.lnk
link = Shell.CreateShortcut(MenuPath + "\\DskCenter.lnk");
link.Description = "DskCenter";
link.IconLocation = DskCenterPath + "Help\\png\\DskCenter.ico";
link.TargetPath = DskCenterPath + "DskCenter.exe";
link.WindowStyle = 3;
link.WorkingDirectory = DskCenterPath;
link.Save();

// Création du raccourci info DskCenter.
link = Shell.CreateShortcut(MenuPath + "\\ReadMe.lnk");
link.Arguments = "";
link.Description = "ReadMe";
link.IconLocation = DskCenterPath + "Help\\png\\Info.ico";
link.TargetPath = DskCenterPath + "Info DskCenter.txt";
link.WindowStyle = 3;
link.WorkingDirectory = DskCenterPath;
link.Save();

// Création du raccourci help
link = Shell.CreateShortcut(MenuPath + "\\help.lnk");
link.Arguments = "";
link.Description = "Help.Fr";
link.IconLocation = DskCenterPath + "Help\\png\\Help.ico";
link.TargetPath = DskCenterPath + "\\help\\index_FR.htm";
link.WindowStyle = 3;
link.WorkingDirectory = DskCenterPath;
link.Save();



// key =  "HKEY_CLASSES_ROOT\\"
// Shell.RegWrite( key + "Applications\\DskCenter.exe\\shell\\open\\command\\", "\""+DskCenterPath+"DskCenter.exe\" \"%1\"");
// Shell.RegWrite( key + ".dsk\\", "DskCenter.Disk");

