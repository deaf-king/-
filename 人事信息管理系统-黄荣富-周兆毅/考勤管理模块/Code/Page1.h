#if !defined(AFX_PAGE1_H__678D0381_ABEA_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_PAGE1_H__678D0381_ABEA_11D6_8649_0088CC174723__INCLUDED_

#include "AttendanceRS.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage1 dialog

class CPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPage1)

// Construction
public:
	void UpdateList(CAttendanceRS& rs);
	void IO_Add(CString strPersonID);
	CPage1();
	~CPage1();

// Dialog Data
	//{{AFX_DATA(CPage1)
	enum { IDD = IDD_PROPPAGE_1 };
	CListCtrl	m_cList;
	CProgressCtrl	m_cProgress;
	CString	m_strIOTime;
	CString	m_strDepartID;
	CString	m_strDepartName;
	CString	m_strPersonID;
	CString	m_strPersonName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPage1)
	afx_msg void OnChangeEdtDepartid();
	afx_msg void OnChangeEdtPersonid();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAddperson();
	afx_msg void OnBtnAdddepart();
	afx_msg void OnBtnAddall();
	afx_msg void OnBtnDeleteattend();
	afx_msg void OnBtnSeekio();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE1_H__678D0381_ABEA_11D6_8649_0088CC174723__INCLUDED_)
