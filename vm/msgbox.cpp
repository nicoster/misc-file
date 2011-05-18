#define WIN32_LEAN_AND_MEAN
#define UNICODE
#define _UNICODE

#include <windows.h>


//~ int APIENTRY WinMain(HINSTANCE hInstance,
                     //~ HINSTANCE hPrevInstance,
                     //~ LPSTR     lpCmdLine,
                     //~ int       nCmdShow)
int main()
{
 	wchar_t wzBuffer[128];
	DWORD dwInterval = 1000, dwCount = 10;


	for(DWORD a = 0 ; a < dwCount ; a++)
	{
		wsprintf(wzBuffer, L"mensagem %d", a);

		MessageBox(NULL, wzBuffer, L"LOG", MB_OK);
		Sleep(dwInterval);

	}

	return 0;
}
