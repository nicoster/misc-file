#include "common.h"

void main()
{
	ofstream of("d:\\a.txt");
	USES_CONVERSION;
	CComBSTR bstr("this is a test");
	of << W2A(bstr);
}