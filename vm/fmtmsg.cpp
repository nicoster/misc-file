#include <windows.h>
#include <stdio.h>

void main()
{
	char buf[128];
	FormatMessage(FORMAT_MESSAGE_FROM_STRING,
		"%%tt", 0, 0, buf, sizeof(buf), 0);
	printf(buf);
}
