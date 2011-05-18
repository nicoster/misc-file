template<LPCWTSTR szTip, LPCWSTR szInfo = NULL, LPCWSTR szInfoTitle = NULL, HICON hIcon = NULL>
class QuietPrompt
{
//	const WCHAR* QUIETPROMPTWNDCLASS = L"quiet_prompt";
//	WNDCLASSW wc;
//	HWND hwnd_;
	NOTIFYICONDATAW nid_;
	static HWND GetWndHandle()
	{
		static struct WndHolder
		{
			HWND hwnd_;
			WndHolder(){hwnd_ = CreateWindowW(L"STATIC", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);}
			~WndHolder(){DestroyWindow(hwnd_);}
		} wh;
		return wh.hwnd_;
	}
	
	QuietPrompt()
	{
//		memset(this, 0, sizeof(QuietPrompt));
//		wc.lpfnWndProc = DefWindowProc;
//		wc.lpszClassName = QUIETPROMPTWNDCLASS;
//		if (!RegisterClassW(&wc)) return FALSE;
		nid_.cbSize = sizeof(NOTIFYICONDATAW);
		nid_.hWnd = GetWndHandle();
		nid_.uFlags = NIF_INFO | NIF_TIP | NIF_ICON;
		nid_.hIcon = hIcon ? ::LoadIcon(::GetModuleHandle(NULL),MAKEINTRESOURCE(IDR_MAINFRAME)) : hIcon;
		wcscpy(nid_.szTip, szTip);

#if (_WIN32_IE >= 0x0500)
		if (szInfo)	wcscpy(nid_.szInfo, szInfo);
		if (szInfoTitle) wcscpy(nid_.szInfoTitle, szInfoTitle);
		nid_.dwInfoFlags = NIIF_INFO;
#endif
		Shell_NotifyIconW(NIM_ADD, &nid_);
	}
	
	~QuietPrompt()
	{
		Shell_NotifyIconW(NIM_DELETE, &nid_);
//		DestroyWindow(hwnd_);
//		UnregisterClassW(QUIETPROMPTWNDCLASS, NULL);
	}
}