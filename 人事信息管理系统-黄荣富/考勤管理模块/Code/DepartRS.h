#if !defined(AFX_DEPARTRS_H__38619023_ABFA_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_DEPARTRS_H__38619023_ABFA_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DepartRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDepartRS recordset

class CDepartRS : public CRecordset
{
public:
	CDepartRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDepartRS)

// Field/Param Data
	//{{AFX_FIELD(CDepartRS, CRecordset)
	CString	m_ID;
	CString	m_NAME;
	CString	m_MANAGER;
	CString	m_INTRO;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDepartRS)
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

#endif // !defined(AFX_DEPARTRS_H__38619023_ABFA_11D6_8649_0088CC174723__INCLUDED_)
