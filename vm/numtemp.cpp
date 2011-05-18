#include <windows.h>
template<DWORD szTip = 2, DWORD szInfo = NULL, DWORD szInfoTitle = NULL, HICON hIcon = NULL>
struct foo
{
	enum{D = szTip};
};
typedef void * PVOID;
struct bar : public PVOID{};
void main(){foo<>::D;}