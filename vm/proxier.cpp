
//C源代码：客户端怎样通过proxy进行连接，支持https, socks5代理
//版权说明
//此代码为遥志软件版权所有，任何形式的商业行为的使用都必须征得遥志软件的授权和同意
//base64编码
static void to64frombits(unsigned char *out, const unsigned char *in, int inlen)
{
    const char base64digits[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    for (; inlen >= 3; inlen -= 3)
    {
        *out++ = base64digits[in[0] >> 2];
        *out++ = base64digits[((in[0] << 4) & 0x30) | (in[1] >> 4)];
        *out++ = base64digits[((in[1] << 2) & 0x3c) | (in[2] >> 6)];
        *out++ = base64digits[in[2] & 0x3f];
        in += 3;
    }
    if (inlen > 0)
    {
        unsigned char fragment;

        *out++ = base64digits[in[0] >> 2];
        fragment = (in[0] << 4) & 0x30;
        if (inlen > 1)
            fragment |= in[1] >> 4;
        *out++ = base64digits[fragment];
        *out++ = (inlen < 2) ? '=' : base64digits[(in[1] << 2) & 0x3c];
        *out++ = '=';
    }
    *out = '\0';
};

//-- connect proxy
BOOL ConnectEx(SOCKET sock, const char *lpszDestHost, int nDestPort, const char * lpszProxyAddress, const int nProxyPort, const char * lpszProxyProtocol, BOOL bNeedAuth, const char * lpszUserName, const char * lpszPassword)
{
//connect to proxy
    char szBuffer[1024 + 1] = {""};
    int nLen = 0;

    SOCKADDR_IN saProxy;
    saProxy.sin_family = AF_INET;
    saProxy.sin_port = nProxyPort;
    saProxy.sin_addr.S_un.S_addr= inet_addr(lpszProxyAddress);
    if (saProxy.sin_addr.S_un.S_addr == INADDR_NONE)
    {
        LPHOSTENT lphost;
        lphost = gethostbyname(lpszProxyAddress);
        if (lphost != NULL)
            saProxy.sin_addr.S_un.S_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
        else
        {
            return 0;
        }
    }

    if (connect(sock, (SOCKADDR*)&saProxy, sizeof(SOCKADDR)))
    {
        return 0;
    }

    if (stricmp(lpszProxyProtocol, "HTTPS") == 0 || stricmp(lpszProxyProtocol, "HTTP") == 0 )
    {
        if (bNeedAuth)
        {
//Proxy-Authorization: Basic
            char szAuth[1024 + 1] = {""};
            char szAuthT[1024 + 1] = {""};
            sprintf(szAuthT, "%s:%s", lpszUserName,lpszPassword);
            to64frombits((UCHAR *)szAuth, (UCHAR *)szAuthT, strlen(szAuthT));
            sprintf(szBuffer, "CONNECT %s:%d HTTP/1.0\r\nProxy-Authorization: Basic %s\r\n\r\n", lpszDestHost, nDestPort, szAuth);
        }
        else
        {
            sprintf(szBuffer, "CONNECT %s:%d HTTP/1.0\r\n\r\n", lpszDestHost, nDestPort);
        }

        nLen = strlen(szBuffer);
        send(sock, szBuffer, nLen, 0);
        nLen = 1024;
        recv(sock, szBuffer, nLen, 0);
        if (strnicmp(szBuffer, "HTTP/1.0 200", strlen("HTTP/1.0 200")) == 0 ||
                strnicmp(szBuffer, "HTTP/1.1 200", strlen("HTTP/1.1 200")) == 0)
        {
            return 1;
        }
        return 0;
    }

    if (stricmp(lpszProxyProtocol, "SOCKS5") == 0)
    {
//auth
        nLen = 0;
        if (bNeedAuth)
        {
            szBuffer[0] = 5;
            szBuffer[1] = 2;
            szBuffer[2] = 0;
            szBuffer[3] = 2;
            nLen = 4;
            send(sock, szBuffer, nLen, 0);
            nLen = 2;
            recv(sock, szBuffer, nLen, 0);
            if (szBuffer[0] == 5)
            {
//need auth
                if (szBuffer[1] == 2)
                {
                    szBuffer[0] = 1;
                    nLen = strlen(lpszUserName);
                    szBuffer[1] = nLen;
                    strcpy(szBuffer+2, lpszUserName);
                    nLen += 2;
                    szBuffer[nLen] = strlen(lpszPassword);
                    strcpy(szBuffer+nLen+1, lpszPassword);
                    nLen = nLen + 1 + strlen(lpszPassword);
                    send(sock, szBuffer, nLen, 0);
                    nLen = 2;
                    recv(sock, szBuffer, nLen, 0);
                    if (szBuffer[1] != 0)
                    {
                        return 0;
                    }
                }
                else
                {
                    if (szBuffer[1] != 0)
                    {
                        return 0;
                    }
                }
            }
            else
                return 0;

        }
        else
        {
            szBuffer[0] = 5;
            szBuffer[1] = 1;
            szBuffer[2] = 0;
            nLen = 3;
            send(sock, szBuffer, nLen, 0);
            nLen = 2;
            recv(sock, szBuffer, nLen, 0);
            if (szBuffer[0] != 5 || szBuffer[1] != 0)
            {
                return 0;
            }
        }
//translate DestAddr
        szBuffer[0] = 5;
        szBuffer[1] = 1;
        szBuffer[2] = 0;
        szBuffer[3] = 3;//DOMAIN
        szBuffer[4] = strlen(lpszDestHost);//domain len
        strcpy(szBuffer+5, lpszDestHost);
        unsigned short uPort = htons(nDestPort);
        memcpy(szBuffer+5+strlen(lpszDestHost), &uPort, 2);
        nLen = 5 + strlen(lpszDestHost) + 2;
        send(sock, szBuffer, nLen, 0);
        nLen = 10;
        recv(sock, szBuffer, nLen, 0);
        if (szBuffer[0] != 5 || szBuffer[1] != 0)
        {
            return 0;
        }
        return 1;
    }
    return 0;
}

