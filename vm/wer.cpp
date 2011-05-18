#define UNICODE
#define _UNICODE
//#include <windows.h>
#include "common.h"
#include "errorrep.h"

static WCHAR szPath[MAX_PATH+1];
static WCHAR szFR[] = L"\\System32\\FaultRep.dll";

WCHAR * GetFullPathToFaultrepDll(void)
{
    WCHAR *lpRet = NULL;
    UINT rc;
	
    rc = GetSystemWindowsDirectory(szPath, ARRAYSIZE(szPath));
    if (rc == 0 || rc > ARRAYSIZE(szPath) - ARRAYSIZE(szFR) - 1)
        return NULL;
	
    wcscat(szPath, szFR);
    return szPath;
}
static LONG WINAPI MyExceptionFilter( struct _EXCEPTION_POINTERS * pExceptionPointers )
{
	LONG lRet = EXCEPTION_CONTINUE_SEARCH;
	WCHAR * psz = GetFullPathToFaultrepDll();
	if ( psz )
	{
		HMODULE hFaultRepDll = LoadLibrary( psz ) ;
		if ( hFaultRepDll )
		{
			pfn_REPORTFAULT pfn = (pfn_REPORTFAULT)GetProcAddress( hFaultRepDll,
				"ReportFault") ;
			if ( pfn )
			{
				EFaultRepRetVal rc = pfn( pExceptionPointers, 0) ;
				lRet = EXCEPTION_EXECUTE_HANDLER;
            }
			FreeLibrary(hFaultRepDll );
        }
    }
    return lRet ;
}
int __cdecl main(int argc, char **argv)
{
    DWORD  *pdw = NULL;
    BOOL   fUseGlobalExceptionFilter = FALSE;
	
    // There are two ways to handle unexpected exception in applications.
    //  Either
    //   define a global unhandled exception filter that will get called
    //    if nothing else handles the exception.
    //   use a __try / __except block to catch exceptions and define your
    //    own filter function.
    //  Both methods will be demonstated below. If the user of this app passed
    //   "UseGlobalFilter" as an argument to this test application, we will
    //   use a global unhandled exception filter. Otherwise, we will use a
    //   __try / __except block.
	
    // Use a global unhandled exception filter
    if (argc > 1 && _stricmp(argv[1], "UseGlobalFilter") == 0)
    {
        // Set the global unhandled exception filter to the exception filter
        //  function we defined above.
		SetUnhandledExceptionFilter(MyExceptionFilter);
		
        // cause a fault
        *pdw = 1;
    }
	
	
    // Use __try / __except blocks
    else
    {
		__try
        {
            // cause a fault
            *pdw = 1;
        }
		
        // we need to pass the structure returned by GetExceptionInformation()
        //  to the filter.
        // Note that the pointer returned by this function is only valid during
        //  the execution of the filter (that is, within the parenthesis of the
        //  __except() statement). If it needs to be saved, you must copy the
        //  contents of the structure somewhere else.
        __except(MyExceptionFilter(GetExceptionInformation()))
        {
		// we don't do anything interesting in this handler
        }
    }
	
    return 0;
} 