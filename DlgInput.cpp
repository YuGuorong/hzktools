// DlgInput.cpp : implementation file
//

#include "stdafx.h"
#include "hzk.h"
#include "DlgInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInput dialog


CDlgInput::CDlgInput(int width,int heigh, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInput)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nCharWidth = width;
	m_nCharHeigh = heigh;
	
}


void CDlgInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInput)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInput, CDialog)
	//{{AFX_MSG_MAP(CDlgInput)
	ON_EN_CHANGE(IDC_WIDTH, OnChangeWidth)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_HEIGH, OnChangeHeigh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInput message handlers


void CDlgInput::OnChangeWidth() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CWnd * pctrl = this->GetDlgItem(IDC_WIDTH);
	CString str ;
	pctrl->GetWindowText(str); 
	if( str.IsEmpty() )
		str = "0";
	this->m_nCharWidth = atoi((LPCTSTR)str);
}

void CDlgInput::OnChangeHeigh() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CWnd * pctrl = this->GetDlgItem(IDC_HEIGH);
	CString str ;
	pctrl->GetWindowText(str); 
	if( str.IsEmpty() )
		str = "0";
	this->m_nCharHeigh = atoi((LPCTSTR)str);
	
}


void CDlgInput::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
	CString str ;
	CWnd * pctrl = this->GetDlgItem(IDC_WIDTH);
	str.Format("%d",this->m_nCharWidth );
	pctrl->SetWindowText(str); 
	
	pctrl = this->GetDlgItem(IDC_HEIGH);
	str.Format("%d",this->m_nCharHeigh );
	pctrl->SetWindowText(str); 
}

