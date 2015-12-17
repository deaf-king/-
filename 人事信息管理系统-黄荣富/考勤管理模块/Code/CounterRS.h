#if !defined(AFX_COUNTERRS_H__38619024_ABFA_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_COUNTERRS_H__38619024_ABFA_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CounterRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCounterRS recordset

class CCounterRS : public CRecordset
{
public:
	CCounterRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCounterRS)

// Field/Param Data
	//{{AFX_FIELD(CCounterRS, CRecordset)
	CString	m_ID;
	int		m_COUNTER_VALUE;
	CString	m_DESCRIPTION;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCounterRS)
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

#endif // !defined(AFX_COUNTERRS_H__38619024_ABFA_11D6_8649_0088CC174723__INCLUDED_)
