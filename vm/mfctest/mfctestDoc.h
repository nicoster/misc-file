// mfctestDoc.h : interface of the CMfctestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCTESTDOC_H__08E7840E_8F31_41C4_B2C1_EFD74AF7BB4D__INCLUDED_)
#define AFX_MFCTESTDOC_H__08E7840E_8F31_41C4_B2C1_EFD74AF7BB4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMfctestDoc : public CDocument
{
protected: // create from serialization only
	CMfctestDoc();
	DECLARE_DYNCREATE(CMfctestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfctestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfctestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMfctestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCTESTDOC_H__08E7840E_8F31_41C4_B2C1_EFD74AF7BB4D__INCLUDED_)
