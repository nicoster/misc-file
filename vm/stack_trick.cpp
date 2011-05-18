#include <windows.h>
#include <stdio.h>
#include <iostream.h>

int plus(int a, int b){printf("%d\n", a + b); return a + b; }

int fire_plus2(int n, int a, int b)
{
	if (n == 0) return 1;
	for (int i = 0; i < 5; i ++)
	{
		plus(a, b);
	}
	return 0;
}


#define CONNPOINT(iid, funcname, paramcount) \
void fire_##funcname(...)	 \
{ \
	if (iid == 0) return;	\
	char *pDst = 0, *pSrc = 0; \
	_asm{ mov pSrc, ebp}; \
	_asm{ sub esp, paramcount * 4}; \
	_asm{ mov pDst, esp}; \
	memcpy(pDst, pSrc + 8, paramcount * 4); \
	typedef void void_func_ptr(); \
	void_func_ptr *pfunc = (void_func_ptr*)funcname; \
	pfunc(); \
}

struct foo
{
		virtual void zoo(){}
		virtual void bar(int a, int b){}
};

CONNPOINT(2, plus, 2)

void main()
{
	foo *f = new foo();
	typedef void _stdcall void_func_ptr(); 
	void_func_ptr* p = (void_func_ptr*)f->bar;
	f->bar(1, 2);
//	fire_plus(1, 2);
//		fire_plus(1, 2);
}