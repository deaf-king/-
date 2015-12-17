// AttendanceDlg.h : header file
//

#if !defined(AFX_ATTENDANCEDLG_H__80105767_AAB7_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_ATTENDANCEDLG_H__80105767_AAB7_11D6_8649_0088CC174723__INCLUDED_

#include "StatDlg.h"
#include "AttDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAttendanceDlg dialog

class CAttendanceDlg : public CDialog
{
// Construction
public:
	CBrush m_brush;
	CStatDlg* m_pStatDlg;
	CAttDlg* m_pAttDlg;
	CFont m_font;
	CAttendanceDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAttendanceDlg)
	enum { IDD = IDD_ATTENDANCE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttendanceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAttendanceDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnRelogin();
	afx_msg void OnBtnConfig();
	afx_msg void OnBtnRecord();
	afx_msg void OnBtnStatistics();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATTENDANCEDLG_H__80105767_AAB7_11D6_8649_0088CC174723__INCLUDED_)
