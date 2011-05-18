#include <windows.h>
#include <tchar.h>
#include <iostream>
using namespace std;
struct sync_cout_t {
	sync_cout_t(){InitializeCriticalSection(&cs_);}
	~sync_cout_t(){DeleteCriticalSection(&cs_);}
	CRITICAL_SECTION cs_;
	template<class T>
	sync_cout_t& operator << (T const& rhs){EnterCriticalSection(&cs_); std::cout << rhs;  LeaveCriticalSection(&cs_); return *this;}
	typedef ostream::_Myt _Myt;
	_Myt& operator<<(_Myt& (__cdecl *_F)(_Myt&)){return ((*_F)(std::cout)); }
} sync_cout;

void main()
{
	_asm int 3;
	sync_cout<<_T("a")<<_T("b")<<endl;
	cout<<endl;
}