#include "common.h"
#include "winsock2.h"

void main()
{
	SSL_load_error_strings();
	OpenSSL_add_all_algorithms();
	SSL_METHOD* meth = TLSv1_client_method();
	if (! meth)
	{
		cout << "Error in TLSv1_client_method %d" << ERR_peek_error() << endl;
		return;
	}
	
	SSL_CTX* ctx = SSL_CTX_new(meth);
	if (! ctx)
	{
		cout <<  "Error in SSL_CTX_New " <<  ERR_peek_error() << " due to " <<  ERR_reason_error_string(ERR_peek_error()) << endl;
		return;
	}

	SSL_CTX_set_mode(ctx, SSL_MODE_AUTO_RETRY);
	if (! SSL_CTX_set_cipher_list(ctx, "NULL-SHA"))
	{
		cout << "SSL_CTX_set_cipher_list error" << endl;
		return;
	}
	
	SOCKET listensock = socket(AF_INET, SOCK_STREAM, 0);
	if (listensock <= 0)
	{
		cout << "listensock error " << GetLastError() << endl;
		return;
	}
	
	struct sockaddr_in sa_serv;
    memset (&sa_serv, '\0', sizeof(sa_serv));
	sa_serv.sin_addr.s_addr = inet_addr("ccm-sdk.cisco.com");
	sa_serv.sin_family = AF_INET;
    sa_serv.sin_port = htons (8443);    
	if ( sa_serv.sin_addr.s_addr == INADDR_NONE) 
	{
		cout << "Error while resolving address " << ;
		goto cleanup;
	}

	int err = connect(listensock, (struct sockaddr*) &sa_serv, sizeof(sa_serv));
	if (err < 0)
	{
		cout << "connect fail. " << WSAGetLastError() << endl;
		goto cleanup;
	}
	
	SSL* ssl = SSL_new(ctx);
	if (! ssl)
	{
		cout << "ssl is null" << endl;
		goto cleanup;
	}
	
	SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
	
	err = SSL_set_fd(ssl, listensock);
	if (err <= 0)
	{
		cout << "SSL_set_fd fail " << err << endl;
		goto cleanup;
	}
	
	ERR_clear_error();
	
	err = SSL_connect(ssl);
	
	if (err <= 0)
	{
		cout << "SSL_connect fail " << err << endl;
		goto cleanup;
	}
	
	X508* cert = SSL_get_peer_certificate(ssl);
	if (! cert)
	{
		cout << "get peer cert fail " << endl;
		goto cleanup;
	}
	
	cout << "done" << endl;
cleanup:
	
}
