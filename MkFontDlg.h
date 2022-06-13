// MkFontDlg.h : header file
//

#if !defined(AFX_MKFONTDLG_H__9187C600_0170_4D36_9B80_F7164DFF3A6F__INCLUDED_)
#define AFX_MKFONTDLG_H__9187C600_0170_4D36_9B80_F7164DFF3A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum {
	ROTATE_0 =0,
	ROTATE_90  ,
	ROTATE_180 ,
	ROTATE_270 ,
	ROTATE_MIRROR_0,
	ROTATE_MIRROR_90,
	ROTATE_MIRROR_180,
	ROTATE_MIRROR_270,
};

#define ROTATE_MIR180_LCD  6
#define ROTATE    ROTATE_MIR180_LCD
/////////////////////////////////////////////////////////////////////////////
// CMkFontDlg dialog
BOOL WriteDIB( LPTSTR szFile, HANDLE hDIB);
BOOL WriteWindowToDIB( LPTSTR szFile, CWnd *pWnd );
HANDLE DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal );
class CMkFontDlg :  public CDialog
{
// Construction
public:
	WORD GetNextHzCode(BYTE* hzcode, int coderange);
	int m_iftsize;
	CComboBox * m_opcb_fon[2]; 
	CDC * m_pSrcDC;
	CDC m_Srcdc;
	CDC * m_pDstDC;
	CDC m_Dstdc;
	CMkFontDlg(CWnd* pParent = NULL);	// standard constructor
	static int CALLBACK EnumFontsProc(CONST LOGFONTA *, CONST TEXTMETRICA *, DWORD, LPARAM);

    FILE * GetFile(void);
    FILE * GetListFile(FILE * fp);
    void RotateBits(BYTE * pbuf, int w, int wc, int h); //w, img w;  wc, canvas witdh
// Dialog Data
	//{{AFX_DATA(CMkFontDlg)
	enum { IDD = IDD_MKFONT_DIALOG };
	int		m_iwitdh;
	int		m_iheight;
	int		m_ichsel;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMkFontDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMkFontDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtSelefont();
	afx_msg void OnBtCreate();
	afx_msg void OnDestroy();
	afx_msg void OnChangeWitdh();
	afx_msg void OnChangeHeight();
	afx_msg void OnBtBrows();
	afx_msg void OnRadio4();
	afx_msg void OnBtLock();
	afx_msg void OnOutofmemorySpWidth(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeCbFont();
	afx_msg void OnDeltaposSpWidth(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpHeight(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bLocked;
public:
	int m_nRotate;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MKFONTDLG_H__9187C600_0170_4D36_9B80_F7164DFF3A6F__INCLUDED_)
