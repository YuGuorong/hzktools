// DlgMode.cpp : implementation file
//

#include "stdafx.h"
#include "hzk.h"
#include "DlgMode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMode dialog


CDlgMode::CDlgMode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMode)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgMode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMode)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMode, CDialog)
	//{{AFX_MSG_MAP(CDlgMode)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMode message handlers
