//#define _UNICODE
//#define UNICODE
#include <atlbase.h>
#include <iostream>
#include <comcat.h>
using namespace std;

void main(void)
{
	HRESULT hr;
	ICatInformation* pci = 0;

	CoInitialize(NULL);
	
	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, NULL, CLSCTX_INPROC_SERVER, IID_ICatInformation, (void**)&pci);
	
	CATID catid[1];
	catid[0] = CATID_Control;
	IEnumCLSID* pEnum = 0;
	
	hr = pci->EnumClassesOfCategories(1, catid, 0, 0, &pEnum);
	
	GUID guids[1];
	ULONG ulNum = 1;
	
	hr = pEnum->Next(1, guids, &ulNum);
	
	while( hr == S_OK)
	{
		WCHAR* pProgID = 0;
		ProgIDFromCLSID(guids[0], &pProgID);
		
		WCHAR* pCLSIDString = 0;
		StringFromCLSID(guids[0], &pCLSIDString);
		
		USES_CONVERSION;
		cout<< (pProgID ? W2A(pProgID) : "NoName") << " - " << W2A(pCLSIDString) << endl;
		
//		cout<< pProgID << " - " << *pCLSIDString << endl;
		
		CoTaskMemFree(pProgID);
		CoTaskMemFree(pCLSIDString);
		
		hr = pEnum->Next(1, guids, &ulNum);
	}
	
}