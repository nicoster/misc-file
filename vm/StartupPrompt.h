template<LPCWTSTR szTip, LPCWSTR szInfo = NULL, LPCWSTR szInfoTitle = NULL, HICON hIcon = NULL>
class CStartupPrompt
{
	const WCHAR* STARTUPPROMPTWNDCLASS = L"startup_prompt";
	WNDCLASSW wc;
	HWND hwnd;
	NOTIFYICONDATAW nid;
	
	CStartupPrompt()
	{
		memset(this, 0, sizeof(CStartupPrompt));
		wc.lpfnWndProc = DefWindowProc;
		wc.lpszClassName = STARTUPPROMPTWNDCLASS;
		if (!RegisterClassW(&wc)) return FALSE;
		hwnd = CreateWindowW(STARTUPPROMPTWNDCLASS, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		
		nid.cbSize = sizeof(NOTIFYICONDATAW);
		nid.hWnd = hwnd;
		nid.uFlags = NIF_INFO | NIF_TIP | NIF_ICON;
		nid.hIcon = hIcon ? ::LoadIcon(::GetModuleHandle(NULL),MAKEINTRESOURCE(IDR_MAINFRAME)) : hIcon;
		wcscpy_s(nid.szTip, szTip);

#if (_WIN32_IE >= 0x0500)
		if (szInfo)	wcscpy_s(nid.szInfo, szInfo);
		if (szInfoTitle) wcscpy_s(nid.szInfoTitle, szInfoTitle);
		nid.dwInfoFlags = NIIF_INFO;
#endif
		Shell_NotifyIconW(NIM_ADD, &nid);
	}
	
	~CStartupPrompt()
	{
		Shell_NotifyIconW(NIM_DELETE, &nid);
		DestroyWindow(hwnd);
		UnregisterClassW(STARTUPPROMPTWNDCLASS, NULL);
	}
}