// leak3View.h : interface of the CLeak3View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEAK3VIEW_H__7A306EA6_5BA2_4565_85D1_304CA903D22A__INCLUDED_)
#define AFX_LEAK3VIEW_H__7A306EA6_5BA2_4565_85D1_304CA903D22A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLeak3View : public CView
{
protected: // create from serialization only
	CLeak3View();
	DECLARE_DYNCREATE(CLeak3View)

// Attributes
public:
	CLeak3Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeak3View)
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
	virtual ~CLeak3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLeak3View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in leak3View.cpp
inline CLeak3Doc* CLeak3View::GetDocument()
   { return (CLeak3Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEAK3VIEW_H__7A306EA6_5BA2_4565_85D1_304CA903D22A__INCLUDED_)
