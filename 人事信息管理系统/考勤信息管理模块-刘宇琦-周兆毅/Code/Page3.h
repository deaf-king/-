#if !defined(AFX_PAGE3_H__6AFEEA01_ABF0_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_PAGE3_H__6AFEEA01_ABF0_11D6_8649_0088CC174723__INCLUDED_

#include "LeaveRS.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage3 dialog

class CPage3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPage3)

// Construction
public:
	void UpdateList(CLeaveRS& rs);
	CPage3();
	~CPage3();

// Dialog Data
	//{{AFX_DATA(CPage3)
	enum { IDD = IDD_PROPPAGE_3 };
	CListCtrl	m_cList;
	CString	m_strSTime;
	CString	m_strETime;
	CString	m_strReason;
	CString	m_strPersonID;
	CString	m_strPersonName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPage3)
	afx_msg void OnChangeEdtLeavePersonid();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnLeaveAdd();
	afx_msg void OnBtnLeaveDeleteattend();
	afx_msg void OnBtnLeaveSeekio();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE3_H__6AFEEA01_ABF0_11D6_8649_0088CC174723__INCLUDED_)
