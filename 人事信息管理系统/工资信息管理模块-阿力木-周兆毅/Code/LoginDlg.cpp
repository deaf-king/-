// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Salary.h"
#include "LoginDlg.h"
#include "Crypt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern _ConnectionPtr pTheConn; // Connection����
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
	DDX_CBString(pDX, IDC_CMD_DSN, m_strDSN);
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
	//CFont *pFont=GetFont();
	//m_font.CreatePointFont(10,NULL);
	LOGFONT LogFont;
	GetFont()->GetLogFont(&LogFont);
	LogFont.lfHeight+=LogFont.lfHeight/2;
	LogFont.lfWidth+=LogFont.lfWidth/2;
	m_font.CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_STATIC_LOGINTEXT)->SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLoginDlg::OnOK() 
{
	CString str,strPasswd;
	_RecordsetPtr pRS; // Recordset����

	UpdateData();// ��������
	// �����ݿ�
	if(pTheConn->GetState()==adStateClosed)
		pTheConn->Open(m_strDSN.AllocSysString(),"","",-1);
	pRS.CreateInstance(__uuidof(Recordset)); // ����Recordset����ʵ��
	strPasswd=CCrypt::Encrypt(m_strPasswd,123); // �������
	// ���ù�������
	str="ID='" + m_strUser
		+ "' and PASSWD='" + strPasswd
		+ "' and AUTHORITY='5'";
	try
	{
		pRS->Filter=str.AllocSysString();
		pRS->Open("PERSON",
			pTheConn.GetInterfacePtr(),
			adOpenStatic,adLockReadOnly,adCmdTable);
	}
	catch(_com_error *e)
	{
		CString Error = e->ErrorMessage();
		AfxMessageBox(e->ErrorMessage());
	}
	catch(...)
	{
		AfxMessageBox("�����ݼ��������!");
	}

	int a=pRS->RecordCount;
	if(pRS->RecordCount==1) // �ж���֤�Ƿ�ͨ��
	{
		EndDialog(IDOK); // �رնԻ���
	}
	else
		MessageBox("��ȷ���û��������룬ע���Сд!", "��֤ʧ��");
}
