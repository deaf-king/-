#if !defined(AFX_ERRANDRS_H__41670861_AC79_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_ERRANDRS_H__41670861_AC79_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ErrandRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CErrandRS recordset

class CErrandRS : public CRecordset
{
public:
	CErrandRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CErrandRS)

// Field/Param Data
	//{{AFX_FIELD(CErrandRS, CRecordset)
	int		m_ID;
	CString	m_PERSON;
	CTime	m_START_TIME;
	CTime	m_END_TIME;
	CString	m_DESCRIPTION;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CErrandRS)
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

#endif // !defined(AFX_ERRANDRS_H__41670861_AC79_11D6_8649_0088CC174723__INCLUDED_)
