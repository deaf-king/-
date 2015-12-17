// Attendance.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Attendance.h"
#include "AttendanceDlg.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAttendanceApp

BEGIN_MESSAGE_MAP(CAttendanceApp, CWinApp)
	//{{AFX_MSG_MAP(CAttendanceApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttendanceApp construction

CAttendanceApp::CAttendanceApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAttendanceApp object

CAttendanceApp theApp;
CDatabase db;

/////////////////////////////////////////////////////////////////////////////
// CAttendanceApp initialization

BOOL CAttendanceApp::InitInstance()
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

	// ��ʾ��¼�Ի���
	CLoginDlg LoginDlg;
	if(LoginDlg.DoModal()!=IDOK) return FALSE;
	// ��ʾ���Ի���
	CAttendanceDlg dlg;
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

int CAttendanceApp::ExitInstance() 
{
	if(db.IsOpen()) db.Close();// �ر����ݿ�
	return CWinApp::ExitInstance();
}

// ȫ�ֺ�������ʱ�䴮ת��ΪCTime�ͱ���
CTime StrToTime(CString str)
{// ʱ�䴮��ʽ "%Y-%m-%d %H:%M:%S",��"1999-01-01 11:11:11"
	int nYear,nMonth,nDay,nHour,nMinute,nSecond;
	sscanf(str.Left(4), "%d", &nYear); // �õ���
	sscanf(str.Mid(5,2), "%d", &nMonth); // �õ���
	sscanf(str.Mid(8,2), "%d", &nDay); // �õ���
	sscanf(str.Mid(11,2), "%d", &nHour); // �õ�ʱ
	sscanf(str.Mid(14,2), "%d", &nMinute); // �õ���
	sscanf(str.Mid(17,2), "%d", &nSecond); // �õ���
	// ����CTime����
	CTime result(nYear,nMonth,nDay,nHour,nMinute,nSecond);
	return result;
}
