// mfctest.h : main header file for the MFCTEST application
//

#if !defined(AFX_MFCTEST_H__39A437D1_FC6F_404F_B895_E5C3DFB8B59C__INCLUDED_)
#define AFX_MFCTEST_H__39A437D1_FC6F_404F_B895_E5C3DFB8B59C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMfctestApp:
// See mfctest.cpp for the implementation of this class
//

class CMfctestApp : public CWinApp
{
public:
	CMfctestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfctestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMfctestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCTEST_H__39A437D1_FC6F_404F_B895_E5C3DFB8B59C__INCLUDED_)
