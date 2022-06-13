#if !defined(AFX_DLGMODE_H__E729182F_2BAC_4D0A_9666_2089A560AB96__INCLUDED_)
#define AFX_DLGMODE_H__E729182F_2BAC_4D0A_9666_2089A560AB96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMode dialog

class CDlgMode : public CDialog
{
// Construction
public:
	CDlgMode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMode)
	enum { IDD = IDD_DIALOG2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMode)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMODE_H__E729182F_2BAC_4D0A_9666_2089A560AB96__INCLUDED_)
