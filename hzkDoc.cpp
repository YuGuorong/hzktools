// hzkDoc.cpp : implementation of the CHzkDoc class
//

#include "stdafx.h"
#include "hzk.h"

#include "hzkDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHzkDoc

IMPLEMENT_DYNCREATE(CHzkDoc, CDocument)

BEGIN_MESSAGE_MAP(CHzkDoc, CDocument)
	//{{AFX_MSG_MAP(CHzkDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHzkDoc construction/destruction

CHzkDoc::CHzkDoc()
{
	// TODO: add one-time construction code here

}

CHzkDoc::~CHzkDoc()
{
}

BOOL CHzkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHzkDoc serialization

void CHzkDoc::Serialize(CArchive& ar)
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
// CHzkDoc diagnostics

#ifdef _DEBUG
void CHzkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHzkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHzkDoc commands
