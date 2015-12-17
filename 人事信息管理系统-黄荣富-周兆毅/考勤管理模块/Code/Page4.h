#if !defined(AFX_PAGE4_H__6AFEEA08_ABF0_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_PAGE4_H__6AFEEA08_ABF0_11D6_8649_0088CC174723__INCLUDED_

#include "ErrandRS.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage4 dialog

class CPage4 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPage4)

// Construction
public:
	void UpdateList(CErrandRS& rs);
	CPage4();
	~CPage4();

// Dialog Data
	//{{AFX_DATA(CPage4)
	enum { IDD = IDD_PROPPAGE_4 };
	CListCtrl	m_cList;
	CString	m_strSTime;
	CString	m_strETime;
	CString	m_strPersonID;
	CString	m_strPersonName;
	CString	m_strDescription;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPage4)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdtErrandPersonid();
	afx_msg void OnBtnErrandAdd();
	afx_msg void OnBtnErrandDeleteattend();
	afx_msg void OnBtnErrandSeekio();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE4_H__6AFEEA08_ABF0_11D6_8649_0088CC174723__INCLUDED_)
