#if !defined(AFX_PAGE2_H__678D0383_ABEA_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_PAGE2_H__678D0383_ABEA_11D6_8649_0088CC174723__INCLUDED_

#include "OvertimeRS.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage2 dialog

class CPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPage2)

// Construction
public:
	void UpdateList(COvertimeRS& rs);
	CPage2();
	~CPage2();

// Dialog Data
	//{{AFX_DATA(CPage2)
	enum { IDD = IDD_PROPPAGE_2 };
	CListCtrl	m_cList;
	int		m_nHour;
	CString	m_strPersonID;
	CString	m_strPersonName;
	CTime	m_Date;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPage2)
	afx_msg void OnChangeEdtOvertimePersonid();
	afx_msg void OnBtnOvertimeAdd();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnOvertimeDeleteattend();
	afx_msg void OnBtnOvertimeSeekio();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE2_H__678D0383_ABEA_11D6_8649_0088CC174723__INCLUDED_)
