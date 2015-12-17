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
	
	// �ı�"��¼���¹���ϵͳ"�����С
	LOGFONT LogFont;
	GetFont()->GetLogFont(&LogFont);
	LogFont.lfHeight+=LogFont.lfHeight/2;
	LogFont.lfWidth+=LogFont.lfWidth/2;
	m_font.CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_STATIC_LOGINTEXT)->SetFont(&m_font);

	// �����ݿ�Ϊ��״̬����ر�
	if(db.IsOpen()) db.Close();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLoginDlg::OnOK() 
{
	BOOL bLogin=FALSE;
	CString strPasswd,strCount;

	UpdateData(); // �������ݱ���
	if(!db.Open(m_strDSN)) return; // �������ݿ�
	strPasswd=CCrypt::Encrypt(m_strPasswd, 123); // ��������

	CRecordset rs(&db); // �����¼��
	rs.Open(CRecordset::forwardOnly,
		"select COUNT(ID) as COUNT from PERSON where ID='" + m_strUser
		+"' and PASSWD='" + strPasswd + "' and AUTHORITY='4'"); // ִ�в�ѯ
	rs.GetFieldValue("COUNT",strCount);
	rs.Close(); // �ر����ݼ�
	if(strCount=="1") // �ж���֤�Ƿ�ͨ��
	{
		EndDialog(IDOK); // �����Ի��򣬷���IDOK
	}
	else
	{
		MessageBox("��ȷ���û���������,ע���Сд!","��֤ʧ��");
		db.Close(); // �ر����ݿ�
	}
}
