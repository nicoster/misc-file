#include <windows.h>
#include <iostream.h>

void main()
{
	HWND h = FindWindow(0, "WebEx AIM Pro");
	cout << h << endl;
	PostMessage(h, 1624/*WM_TRI_SILENTEXIT*/, 0, 0);
}