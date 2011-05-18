#include <afxcmn.h>

class foo
{
public:
	CString getname()
	{
		return m_str;
	}
	CString m_str;
};

void main(void)
{
	_asm int 3;
	foo f;
	f.m_str = L"aaa";
	CString str = f.getname();
}