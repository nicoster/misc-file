//
//write by Gxter
//
//ͨ������ϵͳ�����ĵ�ַ��ʵ��HOOK API
//
#include "stdio.h"
#include "windows.h"
#include "tchar.h"


BYTE addr_old[8] = {0};
//BYTE addr_new[8] = { 0xB8, 0x20, 0x10, 0x40, 0x00, 0xFF, 0xE0, 0x00 }; //��2��3��4��5����Ҫ�ֹ������ģ���Ҫ�Ĳ��裩
BYTE addr_new[] = { 0xc2, 0x04, 0x00};//0xB8, 0x20, 0x10, 0x40, 0x00, 0xFF, 0xE0, 0x00 }; //��2��3��4��5����Ҫ�ֹ������ģ���Ҫ�Ĳ��裩

DWORD pfnMsgBox=0; //API������ַ


int WINAPI MessageBoxProxy(IN HWND hWnd, IN LPCSTR lpText, IN LPCSTR lpCaption, IN UINT uType)
{
int ret = 0;

DWORD dwOldProtect;
MEMORY_BASIC_INFORMATION   mbi;

::VirtualQuery((void *)pfnMsgBox, &mbi, sizeof(mbi));
::VirtualProtect((void *)pfnMsgBox, 8, PAGE_READWRITE, &dwOldProtect);

// д��ԭ����ִ�д���
::WriteProcessMemory(::GetCurrentProcess(),
    (void *)pfnMsgBox,
    addr_old,
    sizeof(DWORD)*2,
    NULL);

::VirtualProtect((void *)pfnMsgBox, 8, mbi.Protect, 0);

ret=MessageBox(hWnd,"gxter","gxter",uType);

return ret;
}

void PatchSetUnhandledExceptionFilter()
{
	static BYTE RETURN_CODE[] = { 0xc2, 0x04, 0x00}; // __asm ret 4
	MEMORY_BASIC_INFORMATION   mbi;
	DWORD dwOldProtect = 0;
	DWORD pfnSetFilter =(DWORD)GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "SetUnhandledExceptionFilter");
	VirtualQuery((void *)pfnSetFilter, &mbi, sizeof(mbi) );
	VirtualProtect( (void *)pfnSetFilter, 8, PAGE_READWRITE, &dwOldProtect);
	
	WriteProcessMemory(GetCurrentProcess(),	(void *)pfnSetFilter,	RETURN_CODE,	sizeof(RETURN_CODE), NULL);
	VirtualProtect((void *)pfnMsgBox, 8, mbi.Protect, 0);
}

LONG __stdcall MyFilter(_EXCEPTION_POINTERS *){return 0;}
typedef LONG __stdcall FILTERPROC(_EXCEPTION_POINTERS *);
//----------------------------------------------�������
int main()
{
DWORD dwOldProtect;
MEMORY_BASIC_INFORMATION   mbi;

MessageBox(NULL,_T("Hook Demo!"),_T("API Hook"),MB_ICONINFORMATION);
pfnMsgBox=(DWORD)GetProcAddress(GetModuleHandle(_T("kernel32.dll")),_T("SetUnhandledExceptionFilter"));
printf("api��ڵ�ַ: %x\n",pfnMsgBox);


VirtualQuery( (void *)pfnMsgBox, &mbi, sizeof(mbi) );
//�޸�����Ҫ�ĵĵ�ַ��ҳ���ԣ�Ϊ�ɶ���д
VirtualProtect( (void *)pfnMsgBox, 8, PAGE_READWRITE, &dwOldProtect);

// ����ԭ����ִ�д���
//~ memcpy(addr_old, (void *)pfnMsgBox, 8);

// д���µ�ִ�д���
WriteProcessMemory(   GetCurrentProcess(),
    (void *)pfnMsgBox,
        addr_new,
    sizeof(addr_new),
    NULL);
//�޸�Ϊԭ������������
VirtualProtect((void *)pfnMsgBox, 8, mbi.Protect, 0);

//FILTERPROC proc = (FILTERPROC)1;

SetUnhandledExceptionFilter(MyFilter);
//printf("%d\n", dw);

//���������������ʱ��������ҵĺ���������
MessageBox(NULL,_T("Hook Demo!"),_T("API Hook"),MB_ICONINFORMATION);


getchar();
return 0;
}