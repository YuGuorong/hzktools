// hzkView.h : interface of the CHzkView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HZKVIEW_H__2FFA6B81_6DCB_485B_BF3D_12DBB342C46E__INCLUDED_)
#define AFX_HZKVIEW_H__2FFA6B81_6DCB_485B_BF3D_12DBB342C46E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHzkView : public CView
{ 
protected: // create from serialization only
	CHzkView();
	DECLARE_DYNCREATE(CHzkView)

// Attributes
public:
	CDC m_dc;
	CBitmap *	m_obitmap ;  
	CHzkDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHzkView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	UINT m_npages;
	BOOL m_bDrawing;
	UINT m_npage_size;
	void Refresh(void);
	UINT DrawFont(CDC *pDC );
	int m_nXchar;
	void MakeRataFond( char * filesave, char * filesrc);
	virtual ~CHzkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHzkView)
	afx_msg void OnButtonadd();
	afx_msg void OnFileOpen();
	afx_msg void OnButton32772();
	afx_msg void OnFileSave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void On12Rotation();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnBtnrotate();
	afx_msg void OnBtnNew();
};

#ifndef _DEBUG  // debug version in hzkView.cpp
inline CHzkDoc* CHzkView::GetDocument()
   { return (CHzkDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HZKVIEW_H__2FFA6B81_6DCB_485B_BF3D_12DBB342C46E__INCLUDED_)
