// AttDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Attendance.h"
#include "AttDlg.h"
#include "AttendanceDlg.h"
#include "PersonRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDatabase db;
/////////////////////////////////////////////////////////////////////////////
// CAttDlg dialog


CAttDlg::CAttDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAttDlg::IDD, pParent)
{
	// 设置起始时间
	CTime End_t=CTime::GetCurrentTime(); // 当前时间
	CTimeSpan tp(30,0,0,0); // 时间间隔为30天
	//{{AFX_DATA_INIT(CAttDlg)
	m_StartTime = End_t-tp;
	m_EndTime = End_t;
	m_strPersonID = _T("");
	m_strName = _T("");
	m_bSeekbyperson = FALSE;
	m_bSeekbytime = FALSE;
	//}}AFX_DATA_INIT
}


void CAttDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAttDlg)
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_StartTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_EndTime);
	DDX_Text(pDX, IDC_EDT_SEEKPERSONID, m_strPersonID);
	DDX_Text(pDX, IDC_EDT_SEEKPERSONNAME, m_strName);
	DDX_Check(pDX, IDC_CHK_SEEKBYPERSON, m_bSeekbyperson);
	DDX_Check(pDX, IDC_CHK_SEEKBYTIME, m_bSeekbytime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAttDlg, CDialog)
	//{{AFX_MSG_MAP(CAttDlg)
	ON_EN_CHANGE(IDC_EDT_SEEKPERSONID, OnChangeEdtSeekpersonid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttDlg message handlers

BOOL CAttDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Sheet.AddPage(&m_Page1); // 加第1页
	m_Sheet.AddPage(&m_Page2); // 加第2页
	m_Sheet.AddPage(&m_Page3); // 加第3页
	m_Sheet.AddPage(&m_Page4); // 加第4页

	m_Sheet.Create(this, WS_CHILD | WS_VISIBLE, 0); // 创建窗口
	m_Sheet.ModifyStyleEx (0, WS_EX_CONTROLPARENT); // 修改风格
	m_Sheet.ModifyStyle( 0, WS_TABSTOP ); // 修改风格

	// 设置窗口位置
	m_Sheet.SetWindowPos( NULL, 0, 100, 0, 0, 
			SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAttDlg::OnChangeEdtSeekpersonid() 
{
	UpdateData(); // 更新数据

	CPersonRS rs(&db); // 构造记录集
	rs.m_strFilter = "ID='" + m_strPersonID + "'"; // 设置过滤条件
	rs.Open(); // 打开记录集
	if(rs.GetRecordCount()==1) // 判断员工记录是否存在
	{
		m_strName=rs.m_NAME; // 得到员工姓名
	}
	else m_strName.Empty(); // 清除员工姓名的显示
	rs.Close(); // 关闭记录集
	UpdateData(FALSE); // 更新界面数据
}
