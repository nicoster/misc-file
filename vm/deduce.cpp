#include "common.h"


#define 		auto_ptr<wstring> p((wstring*)0);

void main()
{
	wstring str(L"1");
	auto_ptr<wstring> p(new wstring(str));
}