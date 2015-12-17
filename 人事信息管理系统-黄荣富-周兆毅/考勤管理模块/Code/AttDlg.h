#if !defined(AFX_ATTDLG_H__678D0382_ABEA_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_ATTDLG_H__678D0382_ABEA_11D6_8649_0088CC174723__INCLUDED_

#include "Page1.h"	// Added by ClassView
#include "Page2.h"	// Added by ClassView
#include "Page3.h"	// Added by ClassView
#include "Page4.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AttDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAttDlg dialog

class CAttDlg : public CDialog
{
// Construction
public:
	CPage1 m_Page1; // ³öÇÚÒ³
	CPage2 m_Page2; // ¼Ó°àÒ³
	CPage3 m_Page3; // Çë¼ÙÒ³
	CPage4 m_Page4; // ³ö²îÒ³
	CPropertySheet m_Sheet;
	CAttDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAttDlg)
	enum { IDD = IDD_DLG_ATTENDANCE };
	CTime	m_StartTime;
	CTime	m_EndTime;
	CString	m_strPersonID;
	CString	m_strName;
	BOOL	m_bSeekbyperson;
	BOOL	m_bSeekbytime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAttDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdtSeekpersonid();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATTDLG_H__678D0382_ABEA_11D6_8649_0088CC174723__INCLUDED_)
