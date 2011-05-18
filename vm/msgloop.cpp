#include <windows.h>

void main()
{
	MSG msg;
	while(GetMessage(&msg, 0, 0, 0))
		DispatchMessage(&msg);
}