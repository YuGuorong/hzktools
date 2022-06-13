// hzkDoc.h : interface of the CHzkDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HZKDOC_H__0E8FBF32_35B8_4BCD_B04E_F57B58CA528B__INCLUDED_)
#define AFX_HZKDOC_H__0E8FBF32_35B8_4BCD_B04E_F57B58CA528B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHzkDoc : public CDocument
{
protected: // create from serialization only
	CHzkDoc();
	DECLARE_DYNCREATE(CHzkDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHzkDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHzkDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHzkDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HZKDOC_H__0E8FBF32_35B8_4BCD_B04E_F57B58CA528B__INCLUDED_)
