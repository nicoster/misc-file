#include <windows.h>
#include <wininet.h>
#include <iostream.h>

typedef DWORD dword_t;
void main()
{
	HINTERNET hinet, hconn, hfile;
	hinet = InternetOpen("wininet", INTERNET_OPEN_TYPE_DIRECT, 0, 0, 0);
	if (hinet)
	{
 		hconn = InternetConnect( hinet, "services.xmethods.net", 80, "", "", INTERNET_SERVICE_HTTP, 0, 0 );
		if (hconn)
		{
			hfile = HttpOpenRequest( hconn, "POST", "/soap", NULL, NULL, NULL,
				INTERNET_FLAG_KEEP_CONNECTION
				| INTERNET_FLAG_IGNORE_CERT_CN_INVALID
				| INTERNET_FLAG_IGNORE_CERT_DATE_INVALID
				| INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP
				| INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS
//				| (url_comp.scheme_type==INTERNET_SCHEME_HTTPS?INTERNET_FLAG_SECURE:0)
				, 0 );
			
		}
		
		char* data_to_post = 
		"<?xml version=\"1.0\" encoding=\"UTF-8\"?><soap:Envelope xmlns:myns=\"urn:xmethods-CurrencyExchange\" xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><soap:Body soap:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><myns:getRate><country1>usa</country1><country2>india</country2></myns:getRate></soap:Body></soap:Envelope>";
		_asm int 3;
		char* header = "SOAPAction: urn:xmethods-CurrencyExchange/getRate\r\n Content-Type: \"text/xml; charset=iso-8859-1\"\r\n";
		BOOL send_ok = HttpSendRequest( hfile, header, -1/*strlen(header)*/, data_to_post, strlen(data_to_post));
//		BOOL send_ok = HttpSendRequest( hfile, NULL, -1, data_to_post, strlen(data_to_post));

		dword_t code, len = sizeof(code);
		if(HttpQueryInfo( hfile, HTTP_QUERY_STATUS_CODE|HTTP_QUERY_FLAG_NUMBER, (void*)&code, &len, NULL ) )
		{
		}
		cout<<code<<endl;
	}
}
