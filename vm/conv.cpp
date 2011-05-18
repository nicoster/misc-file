#include "common.h"

/* nick 07-12-25 16:15 wide char to multi bytes  safely. remember to delete*/
#define W2M_SAFE(lpw, codepage) (\
	((_lpw = lpw) == NULL) ? NULL : (\
		_convert = (lstrlenW(_lpw)+1)*3,\
		_lpa = new char[_convert], \
		memset((void*)_lpa, 0, _convert), \
		ATLW2AHELPER((LPSTR)_lpa, _lpw, _convert, codepage)))

#define W2A_SAFE(lpw) W2M_SAFE(lpw, CP_ACP)
#define W2U_SAFE(lpw) W2M_SAFE(lpw, CP_UTF8)

#define M2W_SAFE(lpa, codepage) (\
	((_lpa = lpa) == NULL) ? NULL : (\
		_convert = (lstrlenA(_lpa)+1),\
		_lpw = (LPWSTR)new char[_convert*2], \
		memset((void*)_lpw, 0, _convert*2), \
		ATLA2WHELPER((LPWSTR)_lpw, _lpa, _convert, codepage)))
//~ #define M2W_SAFE(lpa, codepage) (\
	//~ ((_lpa = lpa) == NULL) ? NULL : (\
		//~ _convert = (lstrlenA(_lpa)+1),\
		//~ ATLA2WHELPER((LPWSTR) new char[_convert*2], _lpa, _convert, codepage)))

#define A2W_SAFE(lpw) M2W_SAFE(lpw, CP_ACP)
#define U2W_SAFE(lpw) M2W_SAFE(lpw, CP_UTF8)

void main()
{
	USES_CONVERSION;
	char* p = W2A_SAFE(L"aaa\n");
	cout << p;
	wchar_t* pw = A2W_SAFE(p);
	wcout << pw;
}