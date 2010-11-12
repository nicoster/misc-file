/* 08-4-9
	demo program for MiniDumpWriteDump
	by nick
*/

#include <windows.h>
#include <imagehlp.h>
#include <iostream>
using namespace std;
#pragma comment(lib, "dbghelp.lib")

#include <tlhelp32.h>

//#define FILENAME "c:\\demo.dmp"

bool IsDataSectionNeeded( const WCHAR* pModuleName )
{
    static WCHAR* modules[] =
        {
            L"apdata",
            L"wapiclient",
            L"xmppsdk",
            L"xmppmgr.dll",
            L"clientconfiginfo",
            L"ntdll",
        };

        //
    if ( pModuleName == 0 )asdfasdf
    {
// 		cout << "Parameter is null.";
        return false;
    }

    WCHAR szFileName[_MAX_FNAME] = L"", szExt[_MAX_FNAME];
    _wsplitpath( pModuleName, NULL, NULL, szFileName, szExt );

    if (wcsicmp(szExt, L".exe") == 0) return true;

    for (int i = 0; i < sizeof(modules) / sizeof(modules[0]); i ++)
        if (wcsicmp(szFileName, modules[i]) == 0) return true;

    return false;
}

BOOL CALLBACK MiniDumpCallback(
    PVOID                            pParam,
    const PMINIDUMP_CALLBACK_INPUT   pInput,
    PMINIDUMP_CALLBACK_OUTPUT        pOutput
)
{
    if ( pInput == 0 || pOutput == 0) return FALSE;
    switch ( pInput->CallbackType )
    {
    case ModuleCallback:
        if ( pOutput->ModuleWriteFlags & ModuleWriteDataSeg )
            if ( !IsDataSectionNeeded( pInput->Module.FullPath ) )
                pOutput->ModuleWriteFlags &= (~ModuleWriteDataSeg);

        // fall through
    case IncludeModuleCallback:
    case IncludeThreadCallback:
    case ThreadCallback:
    case ThreadExCallback:
        return TRUE;
    default:
        ;
    }
    return FALSE;
}

BOOL CreateMiniDump(
    string const& FILENAME, HANDLE hProcessSnap, DWORD dwProcessID,
    MINIDUMP_TYPE mdt)
{
    HANDLE hFile = CreateFile(FILENAME.c_str(), GENERIC_READ | GENERIC_WRITE,
                              0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

    BOOL nRet = 0;
    cout << "Creating " << FILENAME.c_str() << " - mini user dump" << endl;

    if ( ( hFile != NULL ) && ( hFile != INVALID_HANDLE_VALUE ) )
    {
		MINIDUMP_EXCEPTION_INFORMATION mdei; 
		mdei.ThreadId           = 0x4cc; 
		mdei.ExceptionPointers  = (PEXCEPTION_POINTERS)0x012e644 ; 
		mdei.ClientPointers     = FALSE; 

        MINIDUMP_CALLBACK_INFORMATION mci;
        mci.CallbackRoutine     = (MINIDUMP_CALLBACK_ROUTINE)MiniDumpCallback;
        mci.CallbackParam       = 0;

	tryagain:	
        nRet = MiniDumpWriteDump(hProcessSnap, dwProcessID, hFile, mdt, /*&mdei*/0, 0, &mci);
        if (! nRet)
        {
            DWORD err = GetLastError();
            if (err == 0x80070057 && (mdt & 0x00001800))
            {
                (DWORD&)mdt &= ~0x00001800;
                goto tryagain;
            }
            cout << "MiniDumpWriteDump err:" << hex << GetLastError() << endl;
        }

        CloseHandle( hFile );
    }
    else
    {
        cout << "CreateFile failed: " << FILENAME.c_str() << "\n";
        return FALSE;
    }

    if (nRet)
        cout << "Dump successfully written" << endl;
    else
        cout << "Dump written failed" << endl;
    
    return nRet;
}

DWORD GetProcessByName(string strImageName)
{
	_strlwr((char*)strImageName.c_str());
	if (strcmp(strImageName.substr(strImageName.length() - 4).c_str(), ".exe") != 0)
		strImageName += ".exe";

    PROCESSENTRY32 pe32 = {sizeof(PROCESSENTRY32)};    // 初始化结构

    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);     // 给系统内进程拍快照

    if (Process32First(hProcessSnap,&pe32))do
	{
        string strExeFile(pe32.szExeFile);
		_strlwr((char*)strExeFile.c_str());
		if (strcmp(strImageName.c_str(), strExeFile.c_str()) == 0)
			break;
    }
    while (Process32Next(hProcessSnap,&pe32));

    ::CloseHandle(hProcessSnap);

    return pe32.th32ProcessID;
}

int main(int argc, char** argv)
{
    cout << "MakeDump v1.10 - Write dump for a process\n"
        "Copyright (C) 2009 Nick Xiao (nickx@sz.webex.com)\n"
        "Webex - www.webex.com\n\n";
    
    if (argc < 2 || argc > 4)
    {
        cout << "Usage:\n\t" << argv[0] << " PID [DumpFilePath] [/f]" << endl
            << "\t" << argv[0] << " ImageName [DumpFilePath] [/f]" << endl
            << "\n\t" << "/f\tMake a full dump" << endl;
        return 1;
    }

    DWORD dwProcessID = atoi(argv[1]);

	if (! dwProcessID) 
	{
		dwProcessID = GetProcessByName(argv[1]);
	}

	HANDLE hProcessSnap = ::OpenProcess(PROCESS_ALL_ACCESS, TRUE, dwProcessID);
	if (!hProcessSnap)
	{
        DWORD dw = GetLastError();
		cout << "OpenProcess failed. err:" << dw;
		return 2;
	}
    
    MINIDUMP_TYPE mdt;
    BOOL nRet = FALSE;
    if (argc == 2 || (argc == 3 && lstrcmpiA(argv[2], "/f") != 0))
    {
        mdt       = (MINIDUMP_TYPE)(
                                  MiniDumpWithIndirectlyReferencedMemory |
                                  MiniDumpWithDataSegs|
                                  MiniDumpWithHandleData|
                                  0x00000800/*MiniDumpWithFullMemoryInfo*/ |
                                  0x00001000/*MiniDumpWithThreadInfo*/ |
                                  MiniDumpWithUnloadedModules |
                                  MiniDumpScanMemory
                              );
    
    string strMDump(argv[argc - 1]);
    strMDump += ".mini.dmp";
    nRet = CreateMiniDump(strMDump, hProcessSnap, dwProcessID, mdt);
    }    
    else if (argc == 4 || (argc == 3 && lstrcmpiA(argv[2], "/f") == 0))
    {
        mdt       = (MINIDUMP_TYPE)(
                                      MiniDumpWithPrivateReadWriteMemory|
                                      MiniDumpWithIndirectlyReferencedMemory |
                                      MiniDumpWithDataSegs|
                                      MiniDumpWithHandleData|
                                      0x00000800/*MiniDumpWithFullMemoryInfo*/ |
                                      0x00001000/*MiniDumpWithThreadInfo*/ |
                                      MiniDumpWithUnloadedModules |
                                      MiniDumpScanMemory
                                  );
        
        string strFDump(argv[argc - 2]);
        strFDump += ".full.dmp";
        nRet = CreateMiniDump(strFDump, hProcessSnap, dwProcessID, mdt) || nRet;
    }
    
    CloseHandle(hProcessSnap);
    cout << endl;
    return nRet ? 0 : 4;
}
