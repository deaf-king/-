// Attendance.h : main header file for the ATTENDANCE application
//

#if !defined(AFX_ATTENDANCE_H__80105765_AAB7_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_ATTENDANCE_H__80105765_AAB7_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAttendanceApp:
// See Attendance.cpp for the implementation of this class
//

class CAttendanceApp : public CWinApp
{
public:
	CAttendanceApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttendanceApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAttendanceApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATTENDANCE_H__80105765_AAB7_11D6_8649_0088CC174723__INCLUDED_)
