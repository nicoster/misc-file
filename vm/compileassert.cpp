#include <windows.h>
#include <iostream.h>
template<class RET_TYPE = BYTE>
struct bits
{
	int ret_type_should_be_less_than_DWORD[(sizeof(RET_TYPE) > 1) * -2 + 1];
//	bits(){cout<<sizeof(ret_type_should_be_less_than_DWORD);}
};

void main()
{
	bits<DWORD> b;
	
}