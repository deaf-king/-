#if !defined(AFX_STATDLG_H__4A06B8A1_ABF5_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_STATDLG_H__4A06B8A1_ABF5_11D6_8649_0088CC174723__INCLUDED_

#include "StatRS.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatDlg dialog

class CStatDlg : public CDialog
{
// Construction
public:
	void UpdateList(CStatRS& rs);
	CStatDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStatDlg)
	enum { IDD = IDD_DLG_STAT };
	CProgressCtrl	m_cProgress;
	CListCtrl	m_cList;
	CString	m_strTime;
	CTime	m_STime;
	CTime	m_ETime;
	BOOL	m_bSeekbytime;
	BOOL	m_bSeekbyperson;
	CString	m_strSeektime;
	CString	m_strPersonID;
	CString	m_strPersonName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStatDlg)
	afx_msg void OnChangeStatEdtSeekpersonid();
	afx_msg void OnStatBtnSeek();
	virtual BOOL OnInitDialog();
	afx_msg void OnStatBtnStat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATDLG_H__4A06B8A1_ABF5_11D6_8649_0088CC174723__INCLUDED_)
