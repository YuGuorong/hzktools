#if !defined(AFX_DLGINPUT_H__5435243D_FF69_42BF_B7A3_FFB3907C602C__INCLUDED_)
#define AFX_DLGINPUT_H__5435243D_FF69_42BF_B7A3_FFB3907C602C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInput dialog

class CDlgInput : public CDialog
{ 
// Construction
public:
	int m_nCharWidth;
	int m_nCharHeigh;
	CDlgInput(int width,int heigh, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInput)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInput)
	afx_msg void OnChangeWidth();
	afx_msg void OnPaint();
	afx_msg void OnChangeHeigh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINPUT_H__5435243D_FF69_42BF_B7A3_FFB3907C602C__INCLUDED_)
