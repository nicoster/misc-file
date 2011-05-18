#include "common.h"

struct CTriPolicy 
{
public:
	CTriPolicy():m_bAutomaticUpdates(FALSE), m_bPremiumServices(FALSE), m_bSecureCollaboration(FALSE), 
				m_bIMInt(FALSE), m_bIMExt(FALSE), m_bDisableIMCatchInt(FALSE), m_bDisableIMCatchExt(FALSE),
				m_bLocalArchive(FALSE), m_bVoIPInt(FALSE), m_bVoIPExt(FALSE), m_bVideoInt(FALSE), m_bVideoExt(FALSE),
				m_bDesktopShareInt(FALSE), m_bDesktopShareExt(FALSE), m_bRemoteControlInt(FALSE), m_bRemoteControlExt(FALSE),
				m_bFileTransferInt(FALSE), m_bFileTransferExt(FALSE), m_bFileXferVirusScan(FALSE), m_bHasSpace(FALSE), m_bCreateSpace(FALSE),
				m_bIMAESEncode(FALSE), m_bIMSSLEncode(FALSE), m_bIMNOEncode(FALSE), m_bIMIntWhitelist(FALSE)
	{

	}

public:
	BOOL m_bAutomaticUpdates;
	BOOL m_bPremiumServices;
	BOOL m_bSecureCollaboration;
	BOOL m_bIMInt;
	BOOL m_bIMExt;
	BOOL m_bIMIntWhitelist;
	BOOL m_bDisableIMCatchInt;
	BOOL m_bDisableIMCatchExt;
	BOOL m_bLocalArchive;
	BOOL m_bVoIPInt;
	BOOL m_bVoIPExt;
	BOOL m_bVideoInt;
	BOOL m_bVideoExt;
	BOOL m_bDesktopShareInt;
	BOOL m_bDesktopShareExt;
	BOOL m_bRemoteControlInt;
	BOOL m_bRemoteControlExt;
	BOOL m_bFileTransferInt;
	BOOL m_bFileTransferExt;
	BOOL m_bFileXferVirusScan;
	BOOL 
		m_bHasSpace, 
		/* nick 08-1-15 18:51  */
		m_bCreateSpace;
	BOOL m_bIMAESEncode,
		m_bIMSSLEncode,
		m_bIMNOEncode;
};

#define _rainfo wcout
#define _MAKE_WSTR(x)           L#x
#define MAKE_WSTR(x) _MAKE_WSTR(x)

void main()
{
	CTriPolicy policy;
	memset(&policy, 0xff, sizeof(policy));
#ifdef _DEBUG
#define ON_POLICY(policy_value) policy.m_b##policy_value = GetPrivateProfileIntW(L"policy", MAKE_WSTR(policy_value), policy.m_b##policy_value, L"c:\\policy.ini"); _rainfo << MAKE_WSTR(policy_value) L": " << policy.m_b##policy_value << endl;

	ON_POLICY(AutomaticUpdates);
//	ON_POLICY(PremiumServices);by winkle 23/4/2008
	ON_POLICY(SecureCollaboration);
	ON_POLICY(IMInt);
	ON_POLICY(IMExt);
	ON_POLICY(IMIntWhitelist);
	ON_POLICY(DisableIMCatchInt);
	ON_POLICY(DisableIMCatchExt);
	ON_POLICY(LocalArchive);
	ON_POLICY(VoIPExt);
	ON_POLICY(VoIPInt);
	ON_POLICY(VideoInt);
	ON_POLICY(VideoExt);
	ON_POLICY(DesktopShareInt);
	ON_POLICY(DesktopShareExt);
	ON_POLICY(RemoteControlInt);
	ON_POLICY(RemoteControlExt);
	ON_POLICY(FileTransferInt);
	ON_POLICY(FileTransferExt);
	ON_POLICY(FileXferVirusScan);
	ON_POLICY(HasSpace);
	ON_POLICY(CreateSpace);
//DEL 	ON_POLICY(IMAESEncode);
//DEL 	ON_POLICY(IMSSLEncode);
//DEL 	ON_POLICY(IMNOEncode);
#undef ON_POLICY
#endif	
}