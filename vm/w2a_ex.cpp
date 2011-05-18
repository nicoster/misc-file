#include "common.h"

#define U2W_EX(lpa) A2W_CP_EX(lpa, 0, CP_UTF8)

#define W2U_EX(lpw) (\
	((_lpw_ex = lpw) == NULL) ? NULL : (\
	_convert_ex = (lstrlenW(_lpw_ex)+1) * 3,\
	FAILED(::ATL::AtlMultiply(&_convert_ex, _convert_ex, static_cast<int>(sizeof(WCHAR)))) ? NULL : \
	ATLW2AHELPER(	\
	(LPSTR)_ATL_SAFE_ALLOCA(_convert_ex, _ATL_SAFE_ALLOCA_DEF_THRESHOLD), \
	_lpw_ex, \
	_convert_ex, \
	(CP_UTF8))))

void main()
{
	USES_CONVERSION_EX;
	
	char* u = W2U_EX(L"һ");
	
	
	int const len = 1024 * 1024 * 1024;
	wchar_t *w = new wchar_t[len + 1];
	w[len] = 0;
	for (int i = 0; i < len; i ++)
	{
		w[i] = L'A';
	}
	
	char* a = W2A_EX(w, 0);
}