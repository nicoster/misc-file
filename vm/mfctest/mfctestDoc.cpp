// mfctestDoc.cpp : implementation of the CMfctestDoc class
//

#include "stdafx.h"
#include "mfctest.h"

#include "mfctestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfctestDoc

IMPLEMENT_DYNCREATE(CMfctestDoc, CDocument)

BEGIN_MESSAGE_MAP(CMfctestDoc, CDocument)
	//{{AFX_MSG_MAP(CMfctestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfctestDoc construction/destruction

CMfctestDoc::CMfctestDoc()
{
	// TODO: add one-time construction code here

}

CMfctestDoc::~CMfctestDoc()
{
}

BOOL CMfctestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMfctestDoc serialization

void CMfctestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMfctestDoc diagnostics

#ifdef _DEBUG
void CMfctestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMfctestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfctestDoc commands
