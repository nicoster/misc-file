#include <windows.h>
#include <process.h>

unsigned __stdcall  proc(void*){ Sleep(100000); return 0;}
void main()
{
	unsigned threadID;
//	_beginthread( proc, 10240, NULL );
	_beginthreadex( NULL, 1024 * 1024 * 2, proc, NULL, 0, &threadID );

	Sleep(1000000);
}