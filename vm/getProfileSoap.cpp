#include "common.h"
#import "msxml3.dll"
using namespace MSXML2;
#import "mssoap1.dll" \
	exclude("IStream", "ISequentialStream", "_LARGE_INTEGER", \
	"_ULARGE_INTEGER", "tagSTATSTG", "_FILETIME")
using namespace MSSOAPLib;

void main()
{
	CoInitialize(NULL);

	ISoapSerializerPtr Serializer;
	ISoapReaderPtr Reader;
	ISoapConnectorPtr Connector;
	

	HRESULT hr = E_FAIL;
	try
	{
		wstring strSoapAction(L"getProfileDetailSoap");
		
		// Connect to the service
		Connector.CreateInstance(__uuidof(HttpConnector));
		Connector->Property["EndPointURL"] = L"https://cucm.qa.webex.com:8443/webdialer/services/WebdialerSoapService70?wsdl";
		Connector->Property["SoapAction"] = strSoapAction.c_str();
		//TODO: set proxy here

		CComVariant timeout(30000);
		Connector->Property[_T("Timeout")] = &timeout; // milliseconds, 30 seconds here

		hr = Connector->Connect();

		// Begin message
		Connector->BeginMessage();

		// Create the SoapSerializer
		Serializer.CreateInstance(__uuidof(SoapSerializer));
		
		CComPtr<IStream> spStream = NULL;
		hr = CreateStreamOnHGlobal(0, TRUE, (IStream**)&spStream);
		cout << hex << hr << endl;

		// Connect the serializer to the input stream of the connector
		Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));
		//~ Serializer->Init(_variant_t((IUnknown*)spStream));
		
		// Build the SOAP Message
		hr = Serializer->startEnvelope(_T(""),_T(""),_T(""));
		hr = Serializer->startBody(_T(""));
		
		wstring strNamespaceURI, //(L"https://cucm.qa.webex.com:8443/"), 
			strUserID(L"ttang2"), strPassword(L"123456"), strPrefix;
		
		Serializer->startElement(strSoapAction.c_str(), strNamespaceURI.c_str(), _T(""), strPrefix.c_str());

		Serializer->startElement(_T("cred"), L"", _T(""), _T(""));
		Serializer->startElement(_T("userID"), strNamespaceURI.c_str(), _T(""), _T(""));
		Serializer->writeString(strUserID.c_str());
		Serializer->endElement();
		Serializer->startElement(_T("password"), strNamespaceURI.c_str(), _T(""), _T(""));
		Serializer->writeString(strPassword.c_str());
		Serializer->endElement();
		Serializer->endElement(); //end Credential
		//~ Serializer->startElement(_T("UserID"), strNamespaceURI.c_str(), _T(""), _T(""));
		//~ Serializer->writeString(strUserID.c_str());
		//~ Serializer->endElement();

		Serializer->endElement(); //end soap action

		Serializer->endBody();
		Serializer->endEnvelope();
		
		LARGE_INTEGER liBegin = {0};
		HRESULT hr = spStream->Seek(liBegin, STREAM_SEEK_SET, NULL);
		cout << hex << hr << endl;
		
		char buf[51200];
		memset(buf, 0, 51200);
		ULONG len = 0;
		hr = spStream->Read(buf, 51200, &len);
		cout << hr << endl;
		{
			USES_CONVERSION;
			WCHAR* str = A2W(buf);
			wcout << str << endl;
		}

		// Send the message to the web service
		Connector->EndMessage();
	}
	catch (const _com_error& e)
	{
		wcout << _T("WebDialerCtrl::GetProfile() err: ") << hex << e.Error();
		return;
	}	
	
	char buf[51200];
	memset(buf, 0, 51200);
	ULONG len = 0;
	Connector->OutputStream->Read(buf, 51200, &len);
	{
		USES_CONVERSION;
		WCHAR* str = A2W(buf);
		wcout << str;
	}
	
}
