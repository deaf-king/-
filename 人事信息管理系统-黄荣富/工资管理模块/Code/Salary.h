// Salary.h : main header file for the SALARY application
//

#if !defined(AFX_SALARY_H__393241C5_AFD8_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_SALARY_H__393241C5_AFD8_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSalaryApp:
// See Salary.cpp for the implementation of this class
//

class CSalaryApp : public CWinApp
{
public:
	CSalaryApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSalaryApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSalaryApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SALARY_H__393241C5_AFD8_11D6_8649_0088CC174723__INCLUDED_)
