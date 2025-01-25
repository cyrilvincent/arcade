//Pyron
//http://www.msfn.org/board/solved-drivers-cd-t12566-pid-159358-page-80.html#entry159358

#include "windows.h"
int APIENTRY WinMain(HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR     lpCmdLine,
                    int       nCmdShow )
{

    SHELLEXECUTEINFO mySHELLEXECUTEINFO;

    mySHELLEXECUTEINFO.cbSize=sizeof(SHELLEXECUTEINFO);
    mySHELLEXECUTEINFO.fMask=SEE_MASK_NOCLOSEPROCESS;
    mySHELLEXECUTEINFO.hwnd=NULL;
    mySHELLEXECUTEINFO.lpVerb="Open";
    mySHELLEXECUTEINFO.lpFile="cmd.exe";
    mySHELLEXECUTEINFO.lpParameters="/C setup.cmd";
    mySHELLEXECUTEINFO.lpDirectory=".";
    mySHELLEXECUTEINFO.nShow=SW_SHOW; //NULL or SW_SHOW

    ShellExecuteEx(&mySHELLEXECUTEINFO);
    WaitForSingleObject(mySHELLEXECUTEINFO.hProcess,INFINITE);

    return 0;
}
