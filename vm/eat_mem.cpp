#include <windows.h>
void main()
{
	for (int i = 0; i < 200; i ++)
	{
		char* p = new char[1024 * 1024];
		ZeroMemory(p, 1024 * 1024);
	}
	MSG msg;
	while(GetMessage(&msg, 0, 0, 0))DispatchMessage(&msg);
}