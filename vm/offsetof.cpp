#include "common.h"


struct foo
{
//	int n[100];
	int a, b, c;
} bar;

void main()
{
	cout << &bar << "," << &bar.c << endl;
	size_t offset = (size_t)&((foo*)0)->c;
	cout << offset << endl;

}