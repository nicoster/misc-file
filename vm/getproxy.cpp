//------------------------------------------------------------------
//  @ProxyType  �������ͣ���HTTP,SOCKS,FTP...
//  @ProxyAddr  ���ش���������ĵ�ַ
//  @ProxyPort  ���ش���������Ķ˿�
//  ����ֵ
//    0: �޴���
//   -1: ��ѯIE�Ĵ���ʧ��
//   -2: �޴����͵Ĵ���
//   -3: ��������
//   -4: �޴���������Ϣ
int GetIEProxy(CString ProxyType,CString &ProxyAddr,int &ProxyPort)
{
    unsigned long        nSize = 4096;
    char                 szBuf[4096] = { 0 };

// Read IE settings
    INTERNET_PROXY_INFO* pInfo = (INTERNET_PROXY_INFO*)szBuf;
    if (!InternetQueryOption(NULL, INTERNET_OPTION_PROXY, pInfo, &nSize))
    {
        return -1;  //��ѯIE�Ĵ���ʧ��!
    }

    CString strTmp (pInfo->lpszProxy);
    if (strTmp.IsEmpty()) return -4;//�޴���������Ϣ
    int nStart=0,nPos,nCurLen;

    CString strProxyType = ProxyType;
    strProxyType += "=";
//��ʱ�Ľṹ����
//socks=192.168.1.100:3080 https=192.168.1.100:808 http=192.168.1.100:808 gopher=192.168.1.100:808 ftp=192.168.1.100:808

    strTmp.MakeUpper();//ת��Ϊ��д
    strProxyType.MakeUpper();
    nCurLen = strTmp.GetLength();

    nPos = strTmp.Find(strProxyType.GetBuffer(0),nStart);
    if (nPos>=0)
    {
        strTmp = strTmp.Right(nCurLen - nPos);
        strTmp.TrimLeft();
        nCurLen = strTmp.GetLength();
        //���˽ṹ����
        //HTTP=192.168.1.100:808 gopher=192.168.1.100:808 ftp=192.168.1.100:808

        //��ȡ������Э�鲿��
        nPos = strTmp.Find(" ",nStart);
        if (nPos>=0)
        {
            strTmp = strTmp.Left(nPos);
            strTmp.TrimRight();
            nCurLen = strTmp.GetLength();
            //���˽ṹ����
            //HTTP=192.168.1.100:808

            //ȡ��Э�����Ʋ���
            strTmp = strTmp.Right(nCurLen-strProxyType.GetLength());
            nCurLen = strTmp.GetLength();
            //���˽ṹ����
            //192.168.1.100:808
            nPos = strTmp.Find(":",nStart);
            if (nPos>0)//����Ҫ����0
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
        return -2;//�޴����͵Ĵ���
    }

}
