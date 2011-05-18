// mfctestView.cpp : implementation of the CMfctestView class
//

#include "stdafx.h"
#include "mfctest.h"

#include "mfctestDoc.h"
#include "mfctestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfctestView

IMPLEMENT_DYNCREATE(CMfctestView, CView)

BEGIN_MESSAGE_MAP(CMfctestView, CView)
	//{{AFX_MSG_MAP(CMfctestView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfctestView construction/destruction

CMfctestView::CMfctestView()
{
	// TODO: add construction code here

}

CMfctestView::~CMfctestView()
{
}

BOOL CMfctestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMfctestView drawing

void CMfctestView::OnDraw(CDC* pDC)
{
	CMfctestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMfctestView printing

BOOL CMfctestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMfctestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMfctestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMfctestView diagnostics

#ifdef _DEBUG
void CMfctestView::AssertValid() const
{
	CView::AssertValid();
}

void CMfctestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfctestDoc* CMfctestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfctestDoc)));
	return (CMfctestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfctestView message handlers
