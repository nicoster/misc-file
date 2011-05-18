#include "common.h"

struct foo
{
	static DWORD WINAPI InitSecurityThreadProc(LPVOID p){}
};
void main()
{
	QueueUserWorkItem(foo::InitSecurityThreadProc, 0, 0);
}