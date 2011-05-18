#include <comdef.h>
#include <iostream>
using namespace std;

void main()
{
	_bstr_t bstr;
	
	if (bstr.length() == 0)
		cout << 1;
	else
		cout << 2;
	
	return;
	//~ string str = (char*)_bstr_t((wchar_t*)0);
	_bstr_t b(L"{09461346-4C7F-11D1-8222-444553540000}");
	DWORD dw = WideCharToMultiByte(0, 0, b, 1024, 0, 0, 0, 0);
	cout << dw << endl;
	char* ch = (char*)b;
	cout << wcslen(b);
	
	//~ wstring str2;
	//~ str2 += "Login";
}