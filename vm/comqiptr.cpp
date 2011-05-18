#include <atlbase.h>

CComPtr<IUnknown> unk1;
CComQIPtr<IUnknown, &IID_IUnknown> unk;

void main()
{
	if (unk1) 
	{
		_asm int 3;
	}
	else
	{
		_asm int 3;
	}
}