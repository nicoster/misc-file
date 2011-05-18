CAppConfig::CAppConfig()
{
    init();
}

CAppConfig::~CAppConfig()
{
    release();
}

void CAppConfig::init()
{
    setDNSFlushRegistry();
}

void CAppConfig::release()
{
    setDNSFlushRegistry(FALSE);
}


BOOL CAppConfig::setDNSFlushRegistry(BOOL bSet)
{
    LPCTSTR vista_flush_key = _T("VISTA_DNS_FLUSH_TIME");
    LPCTSTR MaxTTLLimit = _T("SYSTEM\\CurrentControlSet\\Services\\DNSCache\\Parameters\\MaxCacheEntryTtlLimit");
    DWORD data = 0;
    DWORD type = REG_BINARY;
    if (bSet)
    {
        if (CheckOsVersion()>=MS_VISTA) //only for VistOS
        {
            BOOL breg = getRegistryValue(HKEY_LOCAL_MACHINE,
                                         MaxTTLLimit,
                                         type,
                                         (LPBYTE)&data);
            if (breg && data<=300 && data>0)
            {
                RAUtil_SetCfgInt("General", (TCHAR*)vista_flush_key, -1); //no change
            }
            else if (data>300||data==0)
            {
                RAUtil_SetCfgInt("General", (TCHAR*)vista_flush_key, data); //keep data value, set to 300
                data = 300;
                BOOL breg1 = setRegistryValue(HKEY_LOCAL_MACHINE,
                                              MaxTTLLimit,
                                              REG_BINARY,
                                              (LPBYTE)&data,
                                              sizeof(DWORD));
            }
            else if (!breg)
            {
                RAUtil_SetCfgInt("General",(TCHAR*)vista_flush_key , 0);
                data = 300;
                BOOL breg1 = setRegistryValue(HKEY_LOCAL_MACHINE,
                                              MaxTTLLimit,
                                              REG_BINARY,
                                              (LPBYTE)&data,
                                              sizeof(DWORD));
            }
        }
    }
    else //unset the Registry
    {
        if (CheckOsVersion()>=MS_VISTA)
        {
            int v = RAUtil_GetCfgInt(_T("General"),(TCHAR*)vista_flush_key, -1);
            switch (v)
            {
            case -1:
                break;
            case 0:
                deleteRegistryValue(HKEY_LOCAL_MACHINE,MaxTTLLimit);
                break;
            default:
                setRegistryValue(HKEY_LOCAL_MACHINE,
                                 MaxTTLLimit,
                                 REG_BINARY,
                                 (LPBYTE)&v,
                                 sizeof(DWORD));
                break;
            }

            tstring subkey(_T("SoftWare\\MyWebExPC\\Config\\RA\\General\\"));
            subkey+=vista_flush_key;
            long rt = deleteRegistryValue(HKEY_LOCAL_MACHINE,subkey.c_str());
        }
    }
    return TRUE;
}

BOOL CAppConfig::getRegistryValue(HKEY hkeyroot, tstring value, DWORD& type, LPBYTE data)
{
    BOOL bRet = TRUE;
    HKEY hKey = NULL;
    tstring k,v ;
    tstring::size_type pos = value.rfind(_T('\\'));
    if (pos==tstring::npos)
        return FALSE;
    k = value.substr(0,pos);
    v  = value.substr(pos+1);
    if (RegOpenKeyEx(hkeyroot, k.c_str(), 0,
                     KEY_READ, &hKey) != ERROR_SUCCESS)
        return FALSE;

    DWORD dwLength = MAX_PATH;
    {
        if (ERROR_SUCCESS!=RegQueryValueEx(hKey, v.c_str(), NULL, &type, (LPBYTE)data, &dwLength))
            bRet = FALSE;
    }

    RegCloseKey(hKey);
    return bRet;
}


BOOL CAppConfig::setRegistryValue(HKEY hkeyroot, tstring value, DWORD type, LPBYTE data, DWORD datalen)
{
    BOOL bRet = TRUE;
    HKEY hKey = NULL;
    tstring k,v ;
    tstring::size_type pos = value.rfind(_T('\\'));
    if (pos==tstring::npos)
        return FALSE;
    k = value.substr(0,pos);
    v  = value.substr(pos+1);
    if (RegOpenKeyEx(hkeyroot, k.c_str(), 0,
                     KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
        return FALSE;

    long rt=RegSetValueEx(hKey, v.c_str(),
                          NULL, type, data,
                          datalen);
    if (rt!=ERROR_SUCCESS)
    {
        bRet = FALSE;
    }

    RegCloseKey(hKey);
    return bRet;
}

BOOL CAppConfig::deleteRegistryValue(HKEY hkeyroot, tstring value)
{
    BOOL bRet = TRUE;
    HKEY hKey = NULL;
    tstring k,v ;
    tstring::size_type pos = value.rfind(_T('\\'));
    if (pos==tstring::npos)
        return FALSE;
    k = value.substr(0,pos);
    v  = value.substr(pos+1);
    if (RegOpenKeyEx(hkeyroot, k.c_str(), 0,
                     KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
        return FALSE;

    long rt=RegDeleteValue(hKey, v.c_str());
    if (rt!=ERROR_SUCCESS)
    {
        bRet = FALSE;
    }

    RegCloseKey(hKey);
    return bRet;
}
