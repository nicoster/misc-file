#include <windows.h>
#pragma comment(lib, "advapi32.lib")
BOOL AdjustDebugPrivilege(void)
{
    HANDLE Token;
    TOKEN_PRIVILEGES TokenPrivileges;
    DWORD ReturnLength = 0;
    if(OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &Token))
        if(LookupPrivilegeValue(NULL, "SeDebugPrivilege", &TokenPrivileges.Privileges[0].Luid))
        {
            TokenPrivileges.PrivilegeCount = 1;
            TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            AdjustTokenPrivileges(Token, FALSE, &TokenPrivileges,
                    sizeof (TOKEN_PRIVILEGES), NULL, NULL);
			return((GetLastError() == ERROR_SUCCESS));
        }
    return (FALSE);
}

void main()
{
	MessageBox(NULL, AdjustDebugPrivilege() ? 
		"Has debug privilege" : "Has no debug privilege", "info", MB_OK);
}
