#include "common.h"

/* nick 07-11-22 15:02 	WCHAR -> UTF8
	pay attention to the 3 in  "_convert = (lstrlenW(_lpw)+1)*3"
	a Chinese character usually occupies 3 bytes in utf-8 encoding.
 */
#define W2U(lpw) (\
	((_lpw = lpw) == NULL) ? NULL : (\
		_convert = (lstrlenW(_lpw)+1)*3,\
		ATLW2AHELPER((LPSTR) alloca(_convert), _lpw, _convert, CP_UTF8)))

/* nick 07-11-29 16:59 	UTF8->WCHAR */
#define U2W(lpa) (\
	((_lpa = lpa) == NULL) ? NULL : (\
		_convert = (lstrlenA(_lpa)+1),\
		ATLA2WHELPER((LPWSTR) alloca(_convert*2), _lpa, _convert, CP_UTF8)))
		
void main()
{
	USES_CONVERSION;
	
	char u[] = { 0xC3, 0xA3, 0xC2, 0x82, 0xC2, 0xB3, 0};
	wchar_t* w = U2W(u);
	
	char* s =  W2U(L"Äã");
	w = A2W(s);
	int3;
}