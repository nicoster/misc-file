#include "common.h"

void main()
{
	getchar();
		memset(0, 0, 1);
	try
	{
		char buf[1];
//		memset(buf, 0, 2048);
		memset(0, 0, 1);
	}
	catch(...)
	{
		cout << "catch!";
	}
	cout << "no man land.";
}