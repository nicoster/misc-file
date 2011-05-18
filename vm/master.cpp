#include "common.h"

int   main(int   argc,   char*   argv[])   
{   
	HRESULT   hr   =   NOERROR;     
	g_pApp   =   new   CApp;   
	if   (!g_pApp)   
		return   -1;   
	if   (FAILED(hr   =   CoInitialize(NULL)))   
		return   -1;   
	char*   myarg[]={"","http://www.21cn.com"};   
	wchar_t*   myhtmltxt=L"<html><body><b>afdsf</b></body></html>";   
	if(FAILED(g_pApp->Init(2,myarg)))   
	{   
		goto   Error;   
	}   
	g_pApp->Run();   
	if(g_pApp->m_pMSHTML)   
	{   
		IHTMLElement*   pelem=NULL;   
		g_pApp->m_pMSHTML->get_body(&pelem);   
		if(pelem!=NULL)   
		{   
			BSTR   bstrsrc;   
			bstrsrc=SysAllocString(myhtmltxt);   
			pelem->put_innerHTML(bstrsrc);   
			SysFreeString(bstrsrc);   
			pelem->get_innerHTML(&bstrsrc);   
			MessageBoxW(NULL,bstrsrc,L"msg",MB_OK);   
			SysFreeString(bstrsrc);   
			pelem->Release();   
		}   
		wchar_t   temp[]=L"http://www.test.net";   
		BSTR   bstrurl;//=SysAllocString(temp);   
		g_pApp->m_pMSHTML->get_URL(&bstrurl);   
		MessageBoxW(NULL,bstrurl,L"msg",MB_OK);   
		SysFreeString(bstrurl);   
	}   
	else   
		MessageBox(NULL,"m_pMSHTML   is   null","msg",MB_OK);   
	g_pApp->Term();   
Error:   
	if   (g_pApp)   g_pApp->Release();   
	CoUninitialize();   
	if   (FAILED(hr))   
		return   -1;   
	else   
		return   0;   
}     