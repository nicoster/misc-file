#include <windows.h>
#include <atlbase.h>
#include <atlconv.h>
#include <comdef.h>
void main()
{
::CoInitialize( NULL );
	
	USES_CONVERSION;
	CComBSTR bstr;

	HRESULT hr;
	// {000209FF-0000-0000-C000-000000000046} = word.application.9
	CLSID clsid = {0x209ff,0,0,{0xc0,0,0,0,0,0,0,0x46}};
	LPOLESTR lpwProgID = NULL;
	
	hr = ::ProgIDFromCLSID( clsid, &lpwProgID );
	if ( SUCCEEDED(hr) )
	{
		::MessageBoxW( NULL, lpwProgID, L"ProgID", MB_OK );

		IMalloc * pMalloc = NULL;
		hr = ::CoGetMalloc( 1, &pMalloc );  // ȡ�� IMalloc
		if ( SUCCEEDED(hr) )
		{
			pMalloc->Free( lpwProgID );  // �ͷ�ProgID�ڴ�
			pMalloc->Release();          // �ͷ�IMalloc
		}
	}

	::CoUninitialize();
}