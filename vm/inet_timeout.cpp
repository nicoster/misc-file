#include "common.h"
#include <wininet.h>
#pragma comment( lib, "wininet.lib" )

void main()
{
	HINTERNET hinet = InternetOpen(_T(""), INTERNET_OPEN_TYPE_DIRECT, 0, 0, 0);
	
	DWORD dw = 44440, len = sizeof(dw);
	InternetSetOption(hinet, INTERNET_OPTION_CONNECT_TIMEOUT, &dw, len);
	
	InternetQueryOption(hinet, INTERNET_OPTION_CONNECT_TIMEOUT , &dw, &len);
	cout << dw << endl;
	InternetQueryOption(hinet, INTERNET_OPTION_SEND_TIMEOUT , &dw, &len);
	cout << dw << endl;
	InternetQueryOption(hinet, INTERNET_OPTION_RECEIVE_TIMEOUT , &dw, &len);
	cout << dw << endl;
}