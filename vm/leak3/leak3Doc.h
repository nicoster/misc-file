// leak3Doc.h : interface of the CLeak3Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEAK3DOC_H__53FDEBF4_FA2C_46CF_82E5_BBF8512C1A9E__INCLUDED_)
#define AFX_LEAK3DOC_H__53FDEBF4_FA2C_46CF_82E5_BBF8512C1A9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLeak3Doc : public CDocument
{
protected: // create from serialization only
	CLeak3Doc();
	DECLARE_DYNCREATE(CLeak3Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeak3Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLeak3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLeak3Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEAK3DOC_H__53FDEBF4_FA2C_46CF_82E5_BBF8512C1A9E__INCLUDED_)
