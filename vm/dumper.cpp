/* 08-4-9 
	demo program for MiniDumpWriteDump 
	by nick
*/

#include <windows.h>
#include <imagehlp.h>
#include <iostream.h>
#pragma comment(lib, "dbghelp.lib")

#define FILENAME "c:\\demo.dmp"

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		cout << "Usage:\n\t" << argv[0] << " PID" << endl;
		return 1;
	}
	DWORD dwProcessID = atoi(argv[1]);
	HANDLE hFile = CreateFile(FILENAME, GENERIC_READ | GENERIC_WRITE, 
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ); 

	int nRet = 0;

	if( ( hFile != NULL ) && ( hFile != INVALID_HANDLE_VALUE ) ) 
	{
		MINIDUMP_TYPE mdt       = (MINIDUMP_TYPE)(MiniDumpWithDataSegs | MiniDumpWithHandleData);

		HANDLE hProcessSnap = ::OpenProcess(PROCESS_ALL_ACCESS, TRUE, dwProcessID);
		if (!hProcessSnap)
		{
			CloseHandle( hFile );
			cout << "OpenProcess failed. Invalid PID?";
			return 2;
		}
		
		nRet = MiniDumpWriteDump(hProcessSnap, dwProcessID, hFile, mdt, 0, 0, 0); 
		cout << "MiniDumpWriteDump return " << nRet << " (" << GetLastError() << ")" << endl;

		CloseHandle( hFile );
		CloseHandle(hProcessSnap);
	}
	else
	{
		cout << "CreateFile failed: " FILENAME "\n";
		return 3;
	}
	
	if (nRet)
		cout << "Dump file " FILENAME " has been generated." << endl;
	else
		cout << "Dump file failed" << endl;
	return nRet ? 0 : 4;
}