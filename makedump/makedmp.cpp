//////////////////////////////////////////////////////////////////////////////
//
#include <windows.h>
#include <sstream>
#include <commctrl.h>
using namespace std;

#pragma warning(disable: 4075 4108)
/*
cl.exe /LD /nologo /MD /W3 /GX /Gm /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /I../include /I"D:\MY HEADER COLLECTION\XP SDK INCLUDE" makedmp.cpp /link kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /subsystem:windows /incremental:yes /pdb:makedmp.pdb /debug /machine:I386 /out:"makedmp.dll" /align:16 /opt:ref
*/

enum {ID_TASKMGR_BASE = 30500, ID_MAKEDUMP_MINI, ID_MAKEDUMP_FULL};

HWND g_hwndTaskmgr = 0, g_hwndProcess = 0;
WNDPROC g_fnOriginProcessesTab = 0;
char g_szPath[MAX_PATH] = {0};

#ifdef _DEBUG
class logstream : public ostream
{
public:
    explicit logstream() : ostream(&m_streambuf)
    {}
    ~logstream()
    {
        *this << ends;
        OutputDebugString(str().c_str());
    }
public:
    stringbuf *rdbuf() const
    {
        return ((stringbuf *)&m_streambuf);
    }
    string str()
    {
        return m_streambuf.str();
    }
private:
    stringbuf m_streambuf;
};
#else
struct logstream{template <class T> logstream& operator << (T const& whatever){return *this;}};
#endif

#define log (logstream&)logstream() << "mkdmp, "
#define err log << "err, "

#define CHK_RET(x) do{if (!(x)) {err << #x; return;}}while(0)
#define CHK_BREAK(x) if (!(x)) {err << #x; break;}

LRESULT CALLBACK ProcessesTabWndProc(
    HWND hwnd,      // handle to window
    UINT uMsg,      // message identifier
    WPARAM wParam,  // first message parameter
    LPARAM lParam   // second message parameter
)
{
    switch ( uMsg )
    {
    case WM_COMMAND:
        switch ( wParam )
        {
        case ID_MAKEDUMP_MINI:
        case ID_MAKEDUMP_FULL:
        {
            LVITEM lvi = {LVIF_PARAM | LVIF_TEXT};
//            ZeroMemory(&lvi, sizeof(lvi));
//            lvi.mask = LVIF_PARAM | LVIF_TEXT;
            lvi.iItem = ListView_GetNextItem(g_hwndProcess, -1, LVNI_SELECTED);
            char szImageName[MAX_PATH] = {0};
            lvi.pszText = szImageName;
            lvi.cchTextMax = MAX_PATH - 1;
        
            ::SendMessage( g_hwndProcess, LVM_GETITEM, 0, (LPARAM)&lvi );

            CHK_BREAK(lvi.lParam);

            char* pos = strrchr(szImageName, '.');
            if (pos) *pos = '\0';
            log << szImageName;
            
            DWORD dwProcess = *((DWORD*)lvi.lParam + 2);
            log << "pid:" << dwProcess;
            char szCmdline[MAX_PATH] = {0};
            sprintf(szCmdline, "/c \"title %s.exe:%d - Make Dump&&(\"%s\\makedump\" %d %%SystemDrive%%\\%s%s||echo.)&&pause\"", szImageName, dwProcess, g_szPath, dwProcess, szImageName, wParam == ID_MAKEDUMP_FULL ? " /f" : "");
            log << szCmdline;
            ShellExecute(NULL, "open", "cmd.exe", szCmdline, NULL, SW_SHOW);

            break;
        }
        default:
            break;
        }

    case WM_INITMENUPOPUP:
        HMENU hMenu = (HMENU)wParam;
        if ( GetMenuItemID(hMenu, 0 ) == /*TASKMGR_END_PROCESS_CMD*/40028)
        {
            InsertMenu( hMenu, 0, MF_BYPOSITION | MF_SEPARATOR, 0, 0);
            InsertMenu( hMenu, 0, MF_BYPOSITION, ID_MAKEDUMP_MINI, "Create &Brief Dump File" );
            InsertMenu( hMenu, 0, MF_BYPOSITION, ID_MAKEDUMP_FULL, "C&reate Detailed Dump File" );
        }
        break;
    }

    return CallWindowProc(
               g_fnOriginProcessesTab,
               hwnd,
               uMsg,
               wParam,
               lParam );
}

BOOL CALLBACK EnumChildProc( HWND hwnd, LPARAM lParam )
{
    if ( (DWORD)GetDlgCtrlID( hwnd ) == /*TASKMGR_PROCESS_LIST_DLG_ID*/ 0x3F1  )
    {
        g_hwndProcess = hwnd;
        return FALSE;
    }

    return TRUE;
}

void CALLBACK OnInit(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{
    log << "Init..";
    KillTimer(hWnd, nIDEvent);
    
    char* pos = strrchr(g_szPath, '\\');
    CHK_RET(pos);
    *pos = '\0';
    log << g_szPath;
    
    TCHAR szCaption[0x100] = {0};
    LoadString(0, 10003/*TASKMGR_IDS_WINDOW_CAPTION*/, szCaption, 0x100 );
    CHK_RET(strlen(szCaption));
    log << szCaption;
    g_hwndTaskmgr = FindWindow( (LPCTSTR)32770, szCaption );
    CHK_RET(g_hwndTaskmgr);
    EnumChildWindows(g_hwndTaskmgr, EnumChildProc, 0);
    CHK_RET(g_hwndProcess);

    g_fnOriginProcessesTab = (WNDPROC)SetWindowLong(
                               GetParent(g_hwndProcess),
                               GWL_WNDPROC,
                               (LONG)ProcessesTabWndProc );
}

// setdll.exe needs a exported func
_declspec(dllexport) BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID /*reserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        log << "DllMain";
        GetModuleFileName(hinst, g_szPath, MAX_PATH - 1);
        log << g_szPath;
        SetTimer(0, 1, 500, OnInit);
    }

    return TRUE;
}