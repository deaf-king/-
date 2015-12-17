// Salary.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Salary.h"
#include "SalaryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSalaryApp

BEGIN_MESSAGE_MAP(CSalaryApp, CWinApp)
	//{{AFX_MSG_MAP(CSalaryApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSalaryApp construction

CSalaryApp::CSalaryApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSalaryApp object

CSalaryApp theApp;
_ConnectionPtr pTheConn; // Connection对象

/////////////////////////////////////////////////////////////////////////////
// CSalaryApp initialization

BOOL CSalaryApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	::CoInitialize(NULL); // 初始化COM环境

	pTheConn.CreateInstance(__uuidof(Connection)); // 创建实例

	CSalaryDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CSalaryApp::ExitInstance() 
{
	// 如Connection对象是打开的则关闭它
	if(pTheConn->GetState()==adStateOpen) pTheConn->Close();
	pTheConn.Release(); // 释放Connection对象
	::CoUninitialize(); // 关闭COM环境
	return CWinApp::ExitInstance();
}
