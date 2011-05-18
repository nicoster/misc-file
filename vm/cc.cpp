#define WIN32_LEAN_AND_MEAN                
#include <windows.h>

#pragma comment(linker, "/ENTRY:WinMain") 

#pragma comment(linker, "/SECTION:SW")       
#pragma comment(linker, "/MERGE:.data=SW") 
#pragma comment(linker, "/MERGE:.text=SW")  
#pragma comment(linker, "/MERGE:.rdata=SW")

#pragma comment(linker, "/ALIGN:4096")

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR,int)
{
	DEVMODE mode;
	ZeroMemory(&mode, sizeof(mode));
	mode.dmSize = sizeof(mode);
	mode.dmFields = DM_COLOR | DM_PELSWIDTH | DM_PELSHEIGHT;
	
	RECT rt;
	SystemParametersInfo(SPI_GETWORKAREA, NULL, &rt, NULL);
	if (rt.right != 640)
	{
		mode.dmPelsHeight = 480;
		mode.dmPelsWidth = 640;
		mode.dmColor = 16;
	}
	else
	{
		mode.dmPelsHeight = 768;
		mode.dmPelsWidth = 1024;
		mode.dmColor = 32;
	}
	
	return ChangeDisplaySettings(&mode, 0);
}
