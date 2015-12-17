#if !defined(AFX_ATTENDANCERS_H__38619021_ABFA_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_ATTENDANCERS_H__38619021_ABFA_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AttendanceRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAttendanceRS recordset

class CAttendanceRS : public CRecordset
{
public:
	CAttendanceRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAttendanceRS)

// Field/Param Data
	//{{AFX_FIELD(CAttendanceRS, CRecordset)
	int		m_ID;
	CString	m_PERSON;
	CString	m_IN_OUT;
	CTime	m_IO_TIME;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttendanceRS)
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

#endif // !defined(AFX_ATTENDANCERS_H__38619021_ABFA_11D6_8649_0088CC174723__INCLUDED_)
