#include "common.h"
#define _MAKE_STR(x)           #x
#define MAKE_STR(x) _MAKE_STR(x)
#define _MAKE_WSTR(x)           L#x
#define MAKE_WSTR(x) _MAKE_WSTR(x)


void main()
{
	char* str = MAKE_STR(1);
	wchar_t* str2 = MAKE_WSTR(1);
}