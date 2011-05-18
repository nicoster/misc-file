#include <comutil.h>
#include <iostream.h>
#pragma comment(lib, "comsupp.lib")

enum foo{bar, zoo};
void main()
{
	_asm int 3;
	_variant_t a(L"2008-04-10 09:13:50");
	
	foo f;
	f = foo(2);
	
//	cout << long(a);
}
