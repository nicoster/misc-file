#include "common.h"

void main()
{
	throw 1;
	char c;
	ZeroMemory(0, 1);
	memset (0, 1, 1);
	memset (&c, 0, 1024);
}