// WorkplanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Attendance.h"
#include "WorkplanDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkplanDlg dialog


CWorkplanDlg::CWorkplanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWorkplanDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWorkplanDlg)
	m_Time1 = 0;
	m_Time2 = 0;
	m_Time3 = 0;
	m_Time4 = 0;
	//}}AFX_DATA_INIT
}


void CWorkplanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWorkplanDlg)
	DDX_DateTimeCtrl(pDX, IDC_WORKSTAT_DATETIMEPICKER1, m_Time1);
	DDX_DateTimeCtrl(pDX, IDC_WORKSTAT_DATETIMEPICKER2, m_Time2);
	DDX_DateTimeCtrl(pDX, IDC_WORKSTAT_DATETIMEPICKER3, m_Time3);
	DDX_DateTimeCtrl(pDX, IDC_WORKSTAT_DATETIMEPICKER4, m_Time4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWorkplanDlg, CDialog)
	//{{AFX_MSG_MAP(CWorkplanDlg)
	ON_BN_CLICKED(IDC_WORKPLAN_RESET, OnWorkplanReset)
	ON_BN_CLICKED(IDC_WORKPLAN_MODIFY, OnWorkplanModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkplanDlg message handlers

void CWorkplanDlg::OnWorkplanReset() 
{
	CString cstr[4];
	char str[4][9];
	int i;
	int nHour,nMinute,nSecond; // 时，分，秒
	CString strFileName=".\\workplan.ini"; // INI文件名

	// 读取INI文件
	GetPrivateProfileString("WorkPlan", "Time1", "08:00:00", str[0], 9, strFileName);
	GetPrivateProfileString("WorkPlan", "Time2", "12:00:00", str[1], 9, strFileName);
	GetPrivateProfileString("WorkPlan", "Time3", "14:00:00", str[2], 9, strFileName);
	GetPrivateProfileString("WorkPlan", "Time4", "18:00:00", str[3], 9, strFileName);
	for(i=0; i<4; i++) cstr[i]=str[i];
	// 定义四个时间变量并初始化为INI文件中的值
	sscanf(cstr[0].Left(2), "%d", &nHour);		// 得到时
	sscanf(cstr[0].Mid(3,2), "%d", &nMinute);	// 得到分
	sscanf(cstr[0].Mid(6,2), "%d", &nSecond);	// 得到秒
	CTime t1(2002,1,1,nHour,nMinute,nSecond);	// 初始化t1

	sscanf(cstr[1].Left(2), "%d", &nHour);		// 得到时
	sscanf(cstr[1].Mid(3,2), "%d", &nMinute);	// 得到分
	sscanf(cstr[1].Mid(6,2), "%d", &nSecond);	// 得到秒
	CTime t2(2002,1,1,nHour,nMinute,nSecond);	// 初始化t2

	sscanf(cstr[2].Left(2), "%d", &nHour);		// 得到时
	sscanf(cstr[2].Mid(3,2), "%d", &nMinute);	// 得到分
	sscanf(cstr[2].Mid(6,2), "%d", &nSecond);	// 得到秒
	CTime t3(2002,1,1,nHour,nMinute,nSecond);	// 初始化t3

	sscanf(cstr[3].Left(2), "%d", &nHour);		// 得到时
	sscanf(cstr[3].Mid(3,2), "%d", &nMinute);	// 得到分
	sscanf(cstr[3].Mid(6,2), "%d", &nSecond);	// 得到秒
	CTime t4(2002,1,1,nHour,nMinute,nSecond);	// 初始化t4

	// 设置成员变量
	m_Time1=t1;
	m_Time2=t2;
	m_Time3=t3;
	m_Time4=t4;
	UpdateData(FALSE); // 更新界面数据	
}

void CWorkplanDlg::OnWorkplanModify() 
{
	CString strFileName=".\\workplan.ini"; // INI文件名

	UpdateData(); // 更新数据

	WritePrivateProfileString("WorkPlan", "Time1",
		m_Time1.Format("%H:%M:%S"), strFileName);
	WritePrivateProfileString("WorkPlan", "Time2",
		m_Time2.Format("%H:%M:%S"), strFileName);
	WritePrivateProfileString("WorkPlan", "Time3",
		m_Time3.Format("%H:%M:%S"), strFileName);
	WritePrivateProfileString("WorkPlan", "Time4",
		m_Time4.Format("%H:%M:%S"), strFileName);
}

BOOL CWorkplanDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	OnWorkplanReset(); // 初始化时间设置
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
