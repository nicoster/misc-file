#include <windows.h>

#pragma comment(lib, "advapi32.lib")

BOOL AddDebugPrivilege(void)
{
    HANDLE Token;
    TOKEN_PRIVILEGES TokenPrivileges, PreviousState;
    DWORD ReturnLength = 0;
    if(OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &Token))
        if(LookupPrivilegeValue(NULL, "SeDebugPrivilege", &TokenPrivileges.Privileges[0].Luid))
        {
            TokenPrivileges.PrivilegeCount = 1;
            TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
            return (AdjustTokenPrivileges(Token, FALSE, &TokenPrivileges,
                    sizeof (TOKEN_PRIVILEGES), &PreviousState, &ReturnLength));
        }
    return (FALSE);
}

void main(void)
{
	MessageBox(NULL, AddDebugPrivilege() ? "Has Debug Privilege." : "Has No Debug Privilege.", "info", MB_OK);
}