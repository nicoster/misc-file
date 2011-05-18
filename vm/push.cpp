#include "common.h"

void main()
{
	int * p;
	_asm 
	{
		push 4
		push 3
		push 2
		push 1
		mov eax, esp
//		add eax, 0xc
		mov p, eax
	}
	cout << *p;
}