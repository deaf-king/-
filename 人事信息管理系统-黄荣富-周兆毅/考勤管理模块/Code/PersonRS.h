#if !defined(AFX_PERSONRS_H__38619022_ABFA_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_PERSONRS_H__38619022_ABFA_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PersonRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPersonRS recordset

class CPersonRS : public CRecordset
{
public:
	CPersonRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPersonRS)

// Field/Param Data
	//{{AFX_FIELD(CPersonRS, CRecordset)
	CString	m_ID;
	CString	m_PASSWD;
	CString	m_AUTHORITY;
	CString	m_NAME;
	CString	m_SEX;
	CTime	m_BIRTHDAY;
	CString	m_DEPARTMENT;
	CString	m_JOB;
	CString	m_EDU_LEVEL;
	CString	m_SPECIALTY;
	CString	m_ADDRESS;
	CString	m_TEL;
	CString	m_EMAIL;
	CString	m_STATE;
	CString	m_REMARK;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersonRS)
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

#endif // !defined(AFX_PERSONRS_H__38619022_ABFA_11D6_8649_0088CC174723__INCLUDED_)
