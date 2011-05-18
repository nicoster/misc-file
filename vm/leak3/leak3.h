// leak3.h : main header file for the LEAK3 application
//

#if !defined(AFX_LEAK3_H__744D1071_386A_47D0_ABAF_707B365AC93C__INCLUDED_)
#define AFX_LEAK3_H__744D1071_386A_47D0_ABAF_707B365AC93C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLeak3App:
// See leak3.cpp for the implementation of this class
//

class CLeak3App : public CWinApp
{
public:
	CLeak3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeak3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CLeak3App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEAK3_H__744D1071_386A_47D0_ABAF_707B365AC93C__INCLUDED_)
