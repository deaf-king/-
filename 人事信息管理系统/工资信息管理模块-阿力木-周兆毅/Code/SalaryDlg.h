// SalaryDlg.h : header file
//
//{{AFX_INCLUDES()
#include "datagrid.h"
//}}AFX_INCLUDES

#if !defined(AFX_SALARYDLG_H__393241C7_AFD8_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_SALARYDLG_H__393241C7_AFD8_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSalaryDlg dialog

class CSalaryDlg : public CDialog
{
// Construction
public:
	_RecordsetPtr m_pCurDGrs; // 指向右键弹出菜单时的DG相关的Recordset对象
	void RightClick(CDataGrid& DG, _RecordsetPtr pDGrs, short Button, long X, long Y);
	HACCEL m_hAccTable;
	void UpdateDG(_RecordsetPtr pDGrs, CDataGrid& cDG, int index);
	void AddRecord(CString strPersonID);
	// 与几个DataGrid相关的Recordset对象
	_RecordsetPtr m_pDG1rs,m_pDG2rs,m_pDG3rs,m_pDG4rs,m_pDG5rs;
	CStatusBar m_wndStatusBar;
	CSalaryDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSalaryDlg)
	enum { IDD = IDD_SALARY_DIALOG };
	CString	m_strDepartID;
	CDataGrid	m_cDG1;
	CString	m_strDepartName;
	CString	m_strPersonID;
	CString	m_strPersonName;
	float	m_fBasicSalary;
	CString	m_strYearMonth;
	CDataGrid	m_cDG2;
	CDataGrid	m_cDG3;
	CDataGrid	m_cDG4;
	CDataGrid	m_cDG5;
	BOOL	m_bFixed;
	CString	m_strItemName;
	float	m_fMoney;
	CString	m_strDesription;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSalaryDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSalaryDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSystemConnect();
	afx_msg void OnSystemDisconnect();
	afx_msg void OnChangeEdtDepartid();
	afx_msg void OnDestroy();
	afx_msg void OnDblClickDatagrid1();
	afx_msg void OnChangeEdtPersonid();
	afx_msg void OnBtnChangesalary();
	afx_msg void OnBtnAddPerson();
	afx_msg void OnBtnAddList();
	afx_msg void OnConfigFormula();
	afx_msg void OnSystemExit();
	afx_msg void OnCalculateStat();
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	afx_msg void OnMouseDownDatagrid2(short Button, short Shift, long X, long Y);
	afx_msg void OnMouseDownDatagrid3(short Button, short Shift, long X, long Y);
	afx_msg void OnMouseDownDatagrid4(short Button, short Shift, long X, long Y);
	afx_msg void OnMouseDownDatagrid5(short Button, short Shift, long X, long Y);
	afx_msg void OnDeleteRecord();
	afx_msg void OnPreviewView();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SALARYDLG_H__393241C7_AFD8_11D6_8649_0088CC174723__INCLUDED_)
