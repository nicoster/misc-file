#include "common.h"

void main()
{
	HANDLE h = CreateEvent(0, TRUE, FALSE, 0);
	WaitForSingleObject(h, INFINITE);
}
