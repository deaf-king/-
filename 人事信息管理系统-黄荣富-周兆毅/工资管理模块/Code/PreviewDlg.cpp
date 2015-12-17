// PreviewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Salary.h"
#include "PreviewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern _ConnectionPtr pTheConn; // Connection����
/////////////////////////////////////////////////////////////////////////////
// CPreviewDlg dialog


CPreviewDlg::CPreviewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPreviewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPreviewDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPreviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreviewDlg)
	DDX_Control(pDX, IDC_DATAGRID_SALARY, m_cDG);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreviewDlg, CDialog)
	//{{AFX_MSG_MAP(CPreviewDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreviewDlg message handlers

BOOL CPreviewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_RecordsetPtr m_pRS; // Recordset����
	m_pRS.CreateInstance(__uuidof(Recordset)); // ����ʵ��
	CString strSQL;
	// дSQL���
	strSQL="select PERSON.ID,PERSON.NAME,SALARY.BASIC,\
		SALARY.BONUS,SALARY.ADD_DETAIL,SALARY.ADD_TOTAL,\
		SALARY.SUB_DETAIL,SALARY.SUB_TOTAL,SALARY.TOTAL\
		from SALARY,PERSON where SALARY.PERSON=PERSON.ID\
		and SALARY.YEARMONTH='" + m_strYearMonth + "' order by PERSON.ID";
	// ��Recordset����
	try{
		m_pRS->Open(strSQL.AllocSysString(),
			pTheConn.GetInterfacePtr(),
			adOpenKeyset,adLockReadOnly,adCmdText);
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
	m_cDG.SetRefDataSource((LPUNKNOWN)m_pRS);
	m_pRS.Release(); // �ͷ�
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
