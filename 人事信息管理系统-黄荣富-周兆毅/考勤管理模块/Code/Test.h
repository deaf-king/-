#if !defined(AFX_TEST_H__04BD362F_AD7B_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_TEST_H__04BD362F_AD7B_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Test.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTest recordset

class CTest : public CRecordset
{
public:
	CTest(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTest)

// Field/Param Data
	//{{AFX_FIELD(CTest, CRecordset)
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest)
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

#endif // !defined(AFX_TEST_H__04BD362F_AD7B_11D6_8649_0088CC174723__INCLUDED_)
