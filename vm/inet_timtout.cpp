#include "common.h"
#include <wininet.h>
#pragma comment( lib, "wininet.lib" )

void main()
{
	HINTERNET hinet = InternetOpen(_T(""), INTERNET_OPEN_TYPE_DIRECT, 0, 0, 0);
	DWORD dw = 0, len = sizeof(dw);
	InternetQueryOption(hinet, INTERNET_OPTION_SEND_TIMEOUT , &dw, &len);
}