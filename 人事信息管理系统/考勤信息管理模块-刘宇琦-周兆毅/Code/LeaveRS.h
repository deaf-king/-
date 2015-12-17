#if !defined(AFX_LEAVERS_H__3C642242_AC1E_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_LEAVERS_H__3C642242_AC1E_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LeaveRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLeaveRS recordset

class CLeaveRS : public CRecordset
{
public:
	CLeaveRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CLeaveRS)

// Field/Param Data
	//{{AFX_FIELD(CLeaveRS, CRecordset)
	int		m_ID;
	CString	m_PERSON;
	CTime	m_START_TIME;
	CTime	m_END_TIME;
	CString	m_REASON;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeaveRS)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEAVERS_H__3C642242_AC1E_11D6_8649_0088CC174723__INCLUDED_)
