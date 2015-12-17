#if !defined(AFX_WORKPLANDLG_H__189CC607_AB4C_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_WORKPLANDLG_H__189CC607_AB4C_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WorkplanDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWorkplanDlg dialog

class CWorkplanDlg : public CDialog
{
// Construction
public:
	CWorkplanDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWorkplanDlg)
	enum { IDD = IDD_DLG_WORKPLAN };
	CTime	m_Time1;
	CTime	m_Time2;
	CTime	m_Time3;
	CTime	m_Time4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkplanDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWorkplanDlg)
	afx_msg void OnWorkplanReset();
	afx_msg void OnWorkplanModify();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKPLANDLG_H__189CC607_AB4C_11D6_8649_0088CC174723__INCLUDED_)
