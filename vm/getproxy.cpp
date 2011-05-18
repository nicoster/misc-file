//------------------------------------------------------------------
//  @ProxyType  代理类型，如HTTP,SOCKS,FTP...
//  @ProxyAddr  返回代理服务器的地址
//  @ProxyPort  返回代理服务器的端口
//  返回值
//    0: 无错误
//   -1: 查询IE的代理失败
//   -2: 无此类型的代理
//   -3: 其他错误
//   -4: 无代理设置信息
int GetIEProxy(CString ProxyType,CString &ProxyAddr,int &ProxyPort)
{
    unsigned long        nSize = 4096;
    char                 szBuf[4096] = { 0 };

// Read IE settings
    INTERNET_PROXY_INFO* pInfo = (INTERNET_PROXY_INFO*)szBuf;
    if (!InternetQueryOption(NULL, INTERNET_OPTION_PROXY, pInfo, &nSize))
    {
        return -1;  //查询IE的代理失败!
    }

    CString strTmp (pInfo->lpszProxy);
    if (strTmp.IsEmpty()) return -4;//无代理设置信息
    int nStart=0,nPos,nCurLen;

    CString strProxyType = ProxyType;
    strProxyType += "=";
//此时的结构如下
//socks=192.168.1.100:3080 https=192.168.1.100:808 http=192.168.1.100:808 gopher=192.168.1.100:808 ftp=192.168.1.100:808

    strTmp.MakeUpper();//转化为大写
    strProxyType.MakeUpper();
    nCurLen = strTmp.GetLength();

    nPos = strTmp.Find(strProxyType.GetBuffer(0),nStart);
    if (nPos>=0)
    {
        strTmp = strTmp.Right(nCurLen - nPos);
        strTmp.TrimLeft();
        nCurLen = strTmp.GetLength();
        //到此结构如下
        //HTTP=192.168.1.100:808 gopher=192.168.1.100:808 ftp=192.168.1.100:808

        //获取单独的协议部分
        nPos = strTmp.Find(" ",nStart);
        if (nPos>=0)
        {
            strTmp = strTmp.Left(nPos);
            strTmp.TrimRight();
            nCurLen = strTmp.GetLength();
            //到此结构如下
            //HTTP=192.168.1.100:808

            //取掉协议名称部分
            strTmp = strTmp.Right(nCurLen-strProxyType.GetLength());
            nCurLen = strTmp.GetLength();
            //到此结构如下
            //192.168.1.100:808
            nPos = strTmp.Find(":",nStart);
            if (nPos>0)//必须要大于0
            {
                ProxyAddr = strTmp.Left(nPos);

                strTmp = strTmp.Right(nCurLen-nPos-1);
                strTmp.TrimLeft();
                strTmp.TrimRight();

                ProxyPort = atoi(strTmp);
                return 0;
            }
            else
            {
                return -3;
            }



        }
        else
        {
            return -3;
        }
    }
    else
    {
        return -2;//无此类型的代理
    }

}
