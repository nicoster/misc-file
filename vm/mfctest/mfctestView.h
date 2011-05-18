// mfctestView.h : interface of the CMfctestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCTESTVIEW_H__60708B18_4F8C_43D6_B3E8_AAF9A0E1E1F7__INCLUDED_)
#define AFX_MFCTESTVIEW_H__60708B18_4F8C_43D6_B3E8_AAF9A0E1E1F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMfctestView : public CView
{
protected: // create from serialization only
	CMfctestView();
	DECLARE_DYNCREATE(CMfctestView)

// Attributes
public:
	CMfctestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfctestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfctestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMfctestView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mfctestView.cpp
inline CMfctestDoc* CMfctestView::GetDocument()
   { return (CMfctestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCTESTVIEW_H__60708B18_4F8C_43D6_B3E8_AAF9A0E1E1F7__INCLUDED_)
