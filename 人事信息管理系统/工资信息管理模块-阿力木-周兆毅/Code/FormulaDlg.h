#if !defined(AFX_FORMULADLG_H__780CCF87_B16F_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_FORMULADLG_H__780CCF87_B16F_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormulaDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormulaDlg dialog

class CFormulaDlg : public CDialog
{
// Construction
public:
	CFormulaDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFormulaDlg)
	enum { IDD = IDD_DLG_FORMULA };
	int		m_nOvertime;
	int		m_nErrand;
	int		m_nLate;
	int		m_nAbsent;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormulaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFormulaDlg)
	afx_msg void OnBtnReset();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMULADLG_H__780CCF87_B16F_11D6_8649_0088CC174723__INCLUDED_)
