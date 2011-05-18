#include "common.h"

#include <Iphlpapi.h>
#pragma comment(lib, "Iphlpapi.lib")

#define _raerr0 wcout
#define _rainfo0 wcout
#define APUTIL_API 

APUTIL_API BOOL IsLanAvailable()
{
	DWORD len = 0;
	PIP_ADAPTER_INFO pAdapter = NULL;
	MIB_IFROW zSNMP = {0};
	int nRet;

	nRet=GetAdaptersInfo(pAdapter, &len);
	if (nRet != ERROR_BUFFER_OVERFLOW)
	{
		_raerr0 << nRet << L"," << GetLastError() << endl;
		return FALSE;
	}

	auto_ptr<_IP_ADAPTER_INFO> buf((PIP_ADAPTER_INFO)new char[len]);
	nRet=GetAdaptersInfo(buf.get(),&len);

	if (nRet != ERROR_SUCCESS)
	{
		_raerr0 << nRet << L"," << GetLastError() << endl;
		return FALSE;
	}

	pAdapter = buf.get();

	try
	{
		while (pAdapter != NULL )
		{
			zSNMP.dwIndex = pAdapter->Index;
			nRet=GetIfEntry(&zSNMP);
			if (nRet!=NO_ERROR)
			{
				_raerr0 << nRet << L"," << GetLastError() << endl;
				return FALSE;
			}

			_rainfo0 << L"dwOperStatus:" << zSNMP.dwOperStatus << L" dwAdminStatus:" << zSNMP.dwAdminStatus << endl;

			if (MIB_IF_OPER_STATUS_CONNECTED == zSNMP.dwOperStatus ||
				MIB_IF_OPER_STATUS_OPERATIONAL == zSNMP.dwOperStatus)
			{
				if (stricmp(pAdapter->IpAddressList.IpAddress.String, "0.0.0.0") != 0 &&
					stricmp(pAdapter->GatewayList.IpAddress.String, "0.0.0.0") != 0 )
					return TRUE;
			}
			pAdapter = pAdapter->Next;
		}
	}
	catch(...)
	{
		_rainfo0 << L"exception!";
	}

	return FALSE;
}

void main(){cout << "ret:" << IsLanAvailable() << endl;}