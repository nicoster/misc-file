#include <windows.h>
/*
cl.exe /LD /nologo /MD /W3 /GX /Gm /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /I../include /I"D:\MY HEADER COLLECTION\XP SDK INCLUDE" disabledep.cpp /link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /subsystem:windows /incremental:yes /pdb:disabledep.pdb /debug /machine:I386 /out:"disabledep.dll" /align:16 /opt:ref
*/

_declspec(dllexport) BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID /*reserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
		typedef 
		DWORD
		(CALLBACK * NTSETINFORMATIONPROCESS)(
		  IN HANDLE               ProcessHandle,
		  IN DWORD ProcessInformationClass,
		  IN PVOID                ProcessInformation,
		  IN ULONG                ProcessInformationLength );

		NTSETINFORMATIONPROCESS NtSetInformationProcess;
		
		NtSetInformationProcess = (NTSETINFORMATIONPROCESS)
			 GetProcAddress(LoadLibrary("ntdll.dll"), "NtSetInformationProcess");
		
		DWORD ExecuteFlags = 2;
		NtSetInformationProcess(
			GetCurrentProcess(),    // (HANDLE)-1
			/*ProcessExecuteFlags*/0x22,
			&ExecuteFlags,         // ptr to 0x2
			sizeof(ExecuteFlags)); // 0x4
	}
	return TRUE;
}