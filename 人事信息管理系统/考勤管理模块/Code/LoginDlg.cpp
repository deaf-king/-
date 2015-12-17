// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Attendance.h"
#include "LoginDlg.h"
#include "Crypt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDatabase db;
/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	m_strDSN = _T("MISDB");
	m_strUser = _T("");
	m_strPasswd = _T("");
	//}}AFX_DATA_INIT
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_CBString(pDX, IDC_CMB_DSN, m_strDSN);
	DDX_Text(pDX, IDC_EDT_USER, m_strUser);
	DDX_Text(pDX, IDC_EDT_PASSWD, m_strPasswd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

BOOL CLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// 改变"登录人事管理系统"字体大小
	LOGFONT LogFont;
	GetFont()->GetLogFont(&LogFont);
	LogFont.lfHeight+=LogFont.lfHeight/2;
	LogFont.lfWidth+=LogFont.lfWidth/2;
	m_font.CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_STATIC_LOGINTEXT)->SetFont(&m_font);

	// 如数据库为打开状态，则关闭
	if(db.IsOpen()) db.Close();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLoginDlg::OnOK() 
{
	BOOL bLogin=FALSE;
	CString strPasswd,strCount;

	UpdateData(); // 更新数据变量
	if(!db.Open(m_strDSN)) return; // 连接数据库
	strPasswd=CCrypt::Encrypt(m_strPasswd, 123); // 加密密码

	CRecordset rs(&db); // 构造记录集
	rs.Open(CRecordset::forwardOnly,
		"select COUNT(ID) as COUNT from PERSON where ID='" + m_strUser
		+"' and PASSWD='" + strPasswd + "' and AUTHORITY='4'"); // 执行查询
	rs.GetFieldValue("COUNT",strCount);
	rs.Close(); // 关闭数据集
	if(strCount=="1") // 判断认证是否通过
	{
		EndDialog(IDOK); // 结束对话框，返回IDOK
	}
	else
	{
		MessageBox("请确认用户名和密码,注意大小写!","认证失败");
		db.Close(); // 关闭数据库
	}
}
