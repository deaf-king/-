// FormulaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Salary.h"
#include "FormulaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormulaDlg dialog


CFormulaDlg::CFormulaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFormulaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFormulaDlg)
	m_nOvertime = 0;
	m_nErrand = 0;
	m_nLate = 0;
	m_nAbsent = 0;
	//}}AFX_DATA_INIT
}


void CFormulaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormulaDlg)
	DDX_Text(pDX, IDC_EDT_OVERTIME, m_nOvertime);
	DDX_Text(pDX, IDC_EDT_ERRAND, m_nErrand);
	DDX_Text(pDX, IDC_EDT_LATE, m_nLate);
	DDX_Text(pDX, IDC_EDT_ABSENT, m_nAbsent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormulaDlg, CDialog)
	//{{AFX_MSG_MAP(CFormulaDlg)
	ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormulaDlg message handlers

void CFormulaDlg::OnBtnReset() 
{
	CString strFileName=".\\formula.ini"; // INI�ļ���
	// ��ȡINI�ļ�
	m_nOvertime=GetPrivateProfileInt("Formula", "OverTime", 150, strFileName);
	m_nErrand=GetPrivateProfileInt("Formula", "Errand", 100, strFileName);
	m_nLate=GetPrivateProfileInt("Formula", "Late", 10, strFileName);
	m_nAbsent=GetPrivateProfileInt("Formula", "Absent", 50, strFileName);
	UpdateData(FALSE); // ���½�������
}

BOOL CFormulaDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	OnBtnReset(); // ���á��ָ�ȱʡ���á���ť������
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFormulaDlg::OnBtnSave() 
{
	UpdateData(); // ��������
	CString strFileName=".\\formula.ini"; // INI�ļ���
	CString str;
	// �޸ļӰ��
	str.Format("%d",m_nOvertime);
	WritePrivateProfileString("Formula", "OverTime", str, strFileName);
	// �޸ĳ����
	str.Format("%d",m_nErrand);
	WritePrivateProfileString("Formula", "Errand", str, strFileName);
	// �޸ĳٵ����˷���
	str.Format("%d",m_nLate);
	WritePrivateProfileString("Formula", "Late", str, strFileName);
	// �޸Ŀ�������
	str.Format("%d",m_nAbsent);
	WritePrivateProfileString("Formula", "Absent", str, strFileName);
}
