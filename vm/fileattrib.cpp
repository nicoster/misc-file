#include "common.h"

void main()
{
	wstring strPath = L"d:\\a.xml";
	SYSTEMTIME stCreate;
	WIN32_FILE_ATTRIBUTE_DATA info;
	if (GetFileAttributesExW(strPath.c_str(), GetFileExInfoStandard, &info))
	{
		//~ // Convert the last-write time to local time.
		//~ if (!FileTimeToLocalFileTime(&ftWrite, &ftLocal))
			//~ return FALSE;
	
		// Convert the local file time from UTC to system time.
		FileTimeToSystemTime(& info.ftLastWriteTime, &stCreate);
	
		WCHAR lpszString[MAX_PATH];
		// Build a string showing the date and time.
		wsprintfW(lpszString, L"%d-%02d-%02d  %02d:%02d:%02d",
			stCreate.wYear, stCreate.wDay, stCreate.wMonth,
			stCreate.wHour, stCreate.wMinute, stCreate.wSecond);
		
		wcout << lpszString;
	}
	
}