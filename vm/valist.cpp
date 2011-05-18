#include <stdio.h>
#include <stdarg.h>


int f1(int i, ...)
{
	int k;
	va_list  p;
	va_start( p, i);
	
	k = va_arg(p, int);
	while(k != -1)
	{
		printf("%d\n", k);
		
		k= va_arg(p, int);
	}	
	va_end(p);
	
	return 0;
}

int f2(int i, ...)
{
	va_list ap, ap2;
	va_start(ap, i);
	ap2 = ap;
	while (*ap != -1)  ((int*&)ap)++;
	int arg_bytes = ap - ap2;
	_asm push -1;
	while(ap != ap2)
	{
		((int*&)ap) --;
		int tmp = *(int*)ap;
		_asm push tmp;
	}
	int bRet = f1(i);
	arg_bytes += 4;	// for -1 pushed
	_asm add esp, arg_bytes ;
	return bRet;
}

struct foo{int a,b;};

void main()
{
	foo f = {100, 101};
	f2(3, 1, 2, f, -1);
}