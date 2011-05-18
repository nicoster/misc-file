#include <iostream.h>
#include <winsock2.h>

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")
#pragma comment(lib, "ws2_32.lib")

#define CHK_NULL(x) if ((x)==NULL) exit (1)
#define CHK_ERR(err,s) if ((err)==-1) { perror(s); exit(1); }
#define CHK_SSL(err) if ((err)==-1) { ERR_print_errors_fp(stderr); exit(2); }


void main()
{

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2),&wsaData))
    {
        cout<<"init winsock failed!"<<endl;
        return;
    }

    SOCKET s;
    SOCKADDR_IN server;
    int len=sizeof(server);
 	struct hostent *hp;
  	unsigned int addr;
    char szHost[] = "ccm-sdk.cisco.com";
    
    s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (s==INVALID_SOCKET)
    {
        cout<<"create socket failed!"<<endl;
        return;
    }
    
    if (isalpha(szHost[0]))
    {   /* server address is a name */
        hp = gethostbyname(szHost);
    }
    else
    { /* Convert nnn.nnn address to a usable one */
        addr = inet_addr(szHost);
        hp = gethostbyaddr((char *)&addr,4,AF_INET);
    }

    memset(&server,0,sizeof(server));
    memcpy(&(server.sin_addr),hp->h_addr,hp->h_length);
    server.sin_family = hp->h_addrtype;
    server.sin_port = htons(443);


//DEL 	addr.sin_port=htons(nPort);
//DEL 	addr.sin_family=AF_INET;
//DEL 	addr.sin_addr.s_addr=inet_addr(szHost);
    if ( server.sin_addr.s_addr == INADDR_NONE)
    {
        // cout<< "Error while resolving address ";
        return ;
    }
    if (connect(s,(sockaddr *)&server,len)==SOCKET_ERROR)
    {
        cout << "connect fail. " << WSAGetLastError() << endl;
        return;
    }
    else
    {
        cout<<"connect success!"<<endl;
    }

    int err;
    SSL_CTX* ctx;
    SSL* ssl;
    X509* server_cert;
    char* str;
//char buf [4096];
    SSL_METHOD *meth;

    SSLeay_add_ssl_algorithms();
    meth = TLSv1_client_method();
    SSL_load_error_strings();
    ctx = SSL_CTX_new (meth);
    CHK_NULL(ctx);
    SSL_CTX_set_mode(ctx, SSL_MODE_AUTO_RETRY);

    //~ if (! SSL_CTX_set_cipher_list(ctx, "RC4-MD5"/*"NULL-SHA"*/))
    //~ {
    //~ cout << "SSL_CTX_set_cipher_list error" << endl;
    //~ return;
    //~ }

    ssl = SSL_new (ctx);
    CHK_NULL(ssl);

    SSL_set_fd (ssl, s);
    err = SSL_connect (ssl);
    CHK_SSL(err);

    cout<<"SSL connection using "<< SSL_get_cipher (ssl)<<endl;
    server_cert = SSL_get_peer_certificate (ssl);
    CHK_NULL(server_cert);

    {
        FILE* fp = fopen("d:\\a.cer", "w");
        if (fp) PEM_write_X509(fp, server_cert);
    }
    cout<<"Server certificate: "<<endl;

    str = X509_NAME_oneline (X509_get_subject_name (server_cert),0,0);
    CHK_NULL(str);
    cout<<"\t subject: "<<endl<<str<<endl;
    OPENSSL_free (str);

    str = X509_NAME_oneline (X509_get_issuer_name (server_cert),0,0);
    CHK_NULL(str);
    cout<<"\t issuer: "<<endl<<str<<endl;
    OPENSSL_free (str);
    X509_free (server_cert);

    SSL_shutdown (ssl);

    closesocket(s);
    SSL_free (ssl);
    SSL_CTX_free (ctx);

    WSACleanup();
cleanup:
    ;
}