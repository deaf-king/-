// SalaryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Salary.h"
#include "SalaryDlg.h"
#include "LoginDlg.h"
#include "FormulaDlg.h"
#include "PreviewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern _ConnectionPtr pTheConn;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSalaryDlg dialog

CSalaryDlg::CSalaryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSalaryDlg::IDD, pParent)
{
	CTime t=CTime::GetCurrentTime();
	//{{AFX_DATA_INIT(CSalaryDlg)
	m_strDepartID = _T("");
	m_strDepartName = _T("");
	m_strPersonID = _T("");
	m_strPersonName = _T("");
	m_fBasicSalary = 0.0f;
	m_strYearMonth = t.Format("%Y-%m");
	m_bFixed = FALSE;
	m_strItemName = _T("");
	m_fMoney = 0.0f;
	m_strDesription = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSalaryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSalaryDlg)
	DDX_Text(pDX, IDC_EDT_DEPARTID, m_strDepartID);
	DDV_MaxChars(pDX, m_strDepartID, 3);
	DDX_Control(pDX, IDC_DATAGRID1, m_cDG1);
	DDX_Text(pDX, IDC_EDT_DEPARTNAME, m_strDepartName);
	DDX_Text(pDX, IDC_EDT_PERSONID, m_strPersonID);
	DDX_Text(pDX, IDC_EDT_PERSONNAME, m_strPersonName);
	DDX_Text(pDX, IDC_EDT_BASICSALARY, m_fBasicSalary);
	DDX_Text(pDX, IDC_EDT_YEARMONTH, m_strYearMonth);
	DDX_Control(pDX, IDC_DATAGRID2, m_cDG2);
	DDX_Control(pDX, IDC_DATAGRID3, m_cDG3);
	DDX_Control(pDX, IDC_DATAGRID4, m_cDG4);
	DDX_Control(pDX, IDC_DATAGRID5, m_cDG5);
	DDX_Check(pDX, IDC_CHK_FIXED, m_bFixed);
	DDX_CBString(pDX, IDC_CMB_ITEMNAME, m_strItemName);
	DDX_Text(pDX, IDC_EDT_MONEY, m_fMoney);
	DDX_Text(pDX, IDC_EDT_DESCRIPTION, m_strDesription);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSalaryDlg, CDialog)
	//{{AFX_MSG_MAP(CSalaryDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDM_SYSTEM_CONNECT, OnSystemConnect)
	ON_COMMAND(IDM_SYSTEM_DISCONNECT, OnSystemDisconnect)
	ON_EN_CHANGE(IDC_EDT_DEPARTID, OnChangeEdtDepartid)
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_EDT_PERSONID, OnChangeEdtPersonid)
	ON_BN_CLICKED(IDC_BTN_CHANGESALARY, OnBtnChangesalary)
	ON_BN_CLICKED(IDC_BTN_ADD_PERSON, OnBtnAddPerson)
	ON_BN_CLICKED(IDC_BTN_ADD_LIST, OnBtnAddList)
	ON_COMMAND(IDM_CONFIG_FORMULA, OnConfigFormula)
	ON_COMMAND(IDM_SYSTEM_EXIT, OnSystemExit)
	ON_COMMAND(IDM_CALCULATE_STAT, OnCalculateStat)
	ON_WM_MENUSELECT()
	ON_COMMAND(IDM_MENU_DELETERECORD, OnDeleteRecord)
	ON_COMMAND(IDM_PREVIEW_VIEW, OnPreviewView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_INDICATOR_MESSAGE,        // status line indicator
	ID_INDICATOR_LOGIN
};

/////////////////////////////////////////////////////////////////////////////
// CSalaryDlg message handlers

BOOL CSalaryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	// ������Ŀȱʡѡ��Ϊ����
	((CButton*)GetDlgItem(IDC_RADIO_BONUS))->SetCheck(TRUE);
	// ����״̬��
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	CRect rect;
	GetClientRect(&rect);
	// �趨״̬��
	m_wndStatusBar.SetPaneInfo(0,ID_INDICATOR_MESSAGE, 
							   SBPS_NORMAL,rect.Width()/2);
	m_wndStatusBar.SetPaneInfo(1,ID_INDICATOR_LOGIN,SBPS_STRETCH,0);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,
    ID_INDICATOR_LOGIN);
	// ���ؼ��ټ�
	m_hAccTable=::LoadAccelerators(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR));
	// ����DataGrid��Ҫ�õ�Recordset����
	m_pDG1rs.CreateInstance(__uuidof(Recordset)); // DataGrid1���
	m_pDG2rs.CreateInstance(__uuidof(Recordset)); // DataGrid2���
	m_pDG3rs.CreateInstance(__uuidof(Recordset)); // DataGrid3���
	m_pDG4rs.CreateInstance(__uuidof(Recordset)); // DataGrid4���
	m_pDG5rs.CreateInstance(__uuidof(Recordset)); // DataGrid5���
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSalaryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSalaryDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSalaryDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSalaryDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// �ͷ�DataGrid��Ҫ�õ�Recordset����
	m_pDG1rs.Release(); // DataGrid1���
	m_pDG2rs.Release(); // DataGrid2���
	m_pDG3rs.Release(); // DataGrid3���
	m_pDG4rs.Release(); // DataGrid4���
	m_pDG5rs.Release(); // DataGrid5���
}

void CSalaryDlg::OnSystemConnect() // ��ʾ�û���¼����
{
	CLoginDlg LoginDlg;
	if(LoginDlg.DoModal()==IDOK) // ��֤ͨ��
		m_wndStatusBar.SetPaneText(1, "�����ӵ����ݿ�: " + LoginDlg.m_strDSN);
}

void CSalaryDlg::OnSystemDisconnect() // �Ͽ�����
{
	// �ر�Connetion����
	if(pTheConn->GetState()==adStateOpen)
		pTheConn->Close();
	m_wndStatusBar.SetPaneText(1, "��δ��¼���ݿ⣬�밴F2��¼");
}

void CSalaryDlg::OnChangeEdtDepartid() 
{
	if(pTheConn->GetState()==adStateClosed) return; // ���ݿ�δ���򷵻�
	UpdateData(); // ��������

	CString str;
	_variant_t Value;
	_RecordsetPtr pRS; // Recordset����
	pRS.CreateInstance(__uuidof(Recordset)); // ����
	// ����DataGrid1����
	str="select ID,NAME from PERSON where DEPARTMENT like '"
		+ m_strDepartID + "' and STATE='T'";
	if(m_pDG1rs->GetState()==adStateOpen) m_pDG1rs->Close(); // �ر�Recordset
	// ��Recordset
	m_pDG1rs->Open(str.AllocSysString(),
		pTheConn.GetInterfacePtr(),
		adOpenStatic,adLockReadOnly,adCmdText);
	// ����DataGrid1
	m_cDG1.SetRefDataSource((LPUNKNOWN)m_pDG1rs);
	// ���²�������
	str="select NAME from DEPARTMENT where ID='" + m_strDepartID + "'";
	pRS->Open(str.AllocSysString(),
			pTheConn.GetInterfacePtr(),
			adOpenStatic,adLockReadOnly,adCmdText);
	if(pRS->RecordCount==1) // �жϼ�¼�Ƿ����
	{
		Value=pRS->GetCollect("NAME"); // �õ���������
		if(Value.vt!=VT_NULL) m_strDepartName=(char*)_bstr_t(Value);
	}
	else
		m_strDepartName.Empty(); // �����������

	UpdateData(FALSE); // ���½�������
	pRS.Release(); // �ͷ�
}

BEGIN_EVENTSINK_MAP(CSalaryDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CSalaryDlg)
	ON_EVENT(CSalaryDlg, IDC_DATAGRID1, -601 /* DblClick */, OnDblClickDatagrid1, VTS_NONE)
	ON_EVENT(CSalaryDlg, IDC_DATAGRID2, -605 /* MouseDown */, OnMouseDownDatagrid2, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(CSalaryDlg, IDC_DATAGRID3, -605 /* MouseDown */, OnMouseDownDatagrid3, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(CSalaryDlg, IDC_DATAGRID4, -605 /* MouseDown */, OnMouseDownDatagrid4, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	ON_EVENT(CSalaryDlg, IDC_DATAGRID5, -605 /* MouseDown */, OnMouseDownDatagrid5, VTS_I2 VTS_I2 VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CSalaryDlg::OnDblClickDatagrid1() 
{
	UpdateData(); // ��������
	_variant_t Value;
	if(m_pDG1rs->GetState()==adStateOpen) // �ж��б��Ƿ��
	{
		Value=m_pDG1rs->GetCollect("ID"); // �õ�Ա����
		m_strPersonID=(char*)_bstr_t(Value);
	}
	UpdateData(FALSE); // ���½�������
	OnChangeEdtPersonid(); // �ı�Ա����Ϣ
}

void CSalaryDlg::OnChangeEdtPersonid() 
{
	// ���ݿ�δ�����򷵻�
	if(pTheConn->GetState()==adStateClosed) return;

	UpdateData(); // ��������
	CString str;
	_variant_t Value;
	_RecordsetPtr pRS; // Recordset����
	str="select NAME from PERSON where ID='"
		+ m_strPersonID + "' and STATE='T'";
	pRS.CreateInstance(__uuidof(Recordset)); // ����
	// ��Recordset
	pRS->Open(str.AllocSysString(),
		pTheConn.GetInterfacePtr(),
		adOpenStatic,adLockReadOnly,adCmdText);
	if(pRS->RecordCount==1) // �жϼ�¼�Ƿ����
	{
	// ����Ա������
		Value=pRS->GetCollect("NAME"); // �õ�Ա������
		if(Value.vt!=VT_NULL) m_strPersonName=(char*)_bstr_t(Value);
	// ���»�������
		pRS->Close(); // �ر�
		str="PERSON='" + m_strPersonID + "'";
		pRS->Filter=str.AllocSysString();
		// ��Recordset
		pRS->Open("SALARY_SET",
			pTheConn.GetInterfacePtr(),
			adOpenKeyset,adLockOptimistic,adCmdTable);
		if(pRS->RecordCount==1) // �жϼ�¼�Ƿ����
		{
			Value=pRS->GetCollect("SALARY"); // �õ�����
			if(Value.vt!=VT_NULL) m_fBasicSalary=Value.fltVal;
		}
		else // ��Ӽ�¼
		{
			m_fBasicSalary=0; // ȱʡ����
			pRS->AddNew();
			pRS->Fields->GetItem("PERSON")->PutValue(m_strPersonID.AllocSysString());
			pRS->Fields->GetItem("SALARY")->PutValue(_variant_t(m_fBasicSalary));
			pRS->Update();
		}
	// ���š����Ļ������ʡ���ť
		GetDlgItem(IDC_BTN_CHANGESALARY)->EnableWindow(TRUE);
	// ���¡��̶������������б�
		UpdateDG(m_pDG2rs, m_cDG2, 2);
	// ���¡��¶Ƚ����б�
		UpdateDG(m_pDG3rs, m_cDG3, 3);
	// ���¡��¶ȸ����������б�
		UpdateDG(m_pDG4rs, m_cDG4, 4);
	// ���¡��¶ȿ۷����б�
		UpdateDG(m_pDG5rs, m_cDG5, 5);
	}
	else
	{
		m_strPersonName.Empty(); // ���Ա������
		m_fBasicSalary=0; // �������
		// ��ֹ�����Ļ������ʡ���ť
		GetDlgItem(IDC_BTN_CHANGESALARY)->EnableWindow(FALSE);
		// �����DataGrid
		if(m_pDG2rs->GetState()==adStateOpen) m_pDG2rs->Close();
		if(m_pDG3rs->GetState()==adStateOpen) m_pDG3rs->Close();
		if(m_pDG4rs->GetState()==adStateOpen) m_pDG4rs->Close();
		if(m_pDG5rs->GetState()==adStateOpen) m_pDG5rs->Close();
		m_cDG2.Refresh();
		m_cDG3.Refresh();
		m_cDG4.Refresh();
		m_cDG5.Refresh();
	}

	UpdateData(FALSE); // ���½�������
	pRS.Release(); // �ͷ�
}

void CSalaryDlg::OnBtnChangesalary() 
{
	// ���ݿ�δ�����򷵻�
	if(pTheConn->GetState()==adStateClosed) return;

	CString str;
	_variant_t Value;
	_RecordsetPtr pRS; // Recordset����
	pRS.CreateInstance(__uuidof(Recordset)); // ����
	UpdateData(); // ��������
	// ��Recordset
	str="PERSON='" + m_strPersonID + "'";
	pRS->Filter=str.AllocSysString(); // ���ù�������
	pRS->Open("SALARY_SET",
		pTheConn.GetInterfacePtr(),
		adOpenKeyset,adLockOptimistic,adCmdTable);
	if(pRS->RecordCount==1) // �жϼ�¼�Ƿ����
	{
		// ���¹���
		pRS->Fields->GetItem("SALARY")->PutValue(_variant_t(m_fBasicSalary));
		pRS->Update();
	}
	pRS.Release(); // �ͷ�
}

void CSalaryDlg::AddRecord(CString strPersonID)
{
	CString strType; // ��Ŀ����
	long counter; // ���ڱ������
	CString strYearMonth; // ���ڱ���������Ϣ
	_RecordsetPtr pRS; // Recordset����
	pRS.CreateInstance(__uuidof(Recordset)); // ����

	if(m_bFixed) strYearMonth="0000000"; // �ж��Ƿ�̶�����
	else strYearMonth=m_strYearMonth; // ��ȡ������Ϣ
	pRS->Filter="ID='R'"; // ���ù�����
	// �򿪼�������
	pRS->Open("COUNTER",
		pTheConn.GetInterfacePtr(),
		adOpenKeyset,adLockOptimistic,adCmdTable);
	counter=pRS->GetCollect("COUNTER_VALUE").iVal; // ��ȡ����ֵ
	counter++; // ����ֵ��1
	pRS->Fields->GetItem("COUNTER_VALUE")->PutValue(_variant_t(counter));
	pRS->Update(); // ����
	pRS->Close(); // �ر�
	// ��Ӽ�¼
	// �õ���Ŀ����
	if(((CButton*)GetDlgItem(IDC_RADIO_BONUS))->GetCheck()) strType="0";
	else if(((CButton*)GetDlgItem(IDC_RADIO_FULI))->GetCheck()) strType="1";
	else if(((CButton*)GetDlgItem(IDC_RADIO_JINTIE))->GetCheck()) strType="2";
	else strType="3";
	// �򿪱�
	pRS->Open("SALARY_OTHER",
		pTheConn.GetInterfacePtr(),
		adOpenKeyset,adLockOptimistic,adCmdTable);
	pRS->AddNew(); // ����¼�¼
	pRS->Fields->GetItem("ID")->PutValue(_variant_t(counter));
	pRS->Fields->GetItem("YEARMONTH")->PutValue(strYearMonth.AllocSysString());
	pRS->Fields->GetItem("PERSON")->PutValue(strPersonID.AllocSysString());
	pRS->Fields->GetItem("TYPE")->PutValue(strType.AllocSysString());
	pRS->Fields->GetItem("NAME")->PutValue(m_strItemName.AllocSysString());
	pRS->Fields->GetItem("MONEY")->PutValue(_variant_t(m_fMoney));
	pRS->Fields->GetItem("DESCRIPTION")->PutValue(m_strDesription.AllocSysString());
	pRS->Update(); // ����
	pRS.Release(); // �ͷ�
}

void CSalaryDlg::OnBtnAddPerson() 
{
	// ���ݿ�δ�����򷵻�
	if(pTheConn->GetState()==adStateClosed) return;
	UpdateData(); // ��������
	// �����ݷ���
	if(m_strItemName.IsEmpty() || m_strPersonName.IsEmpty()) return;
	AddRecord(m_strPersonID); // ��Ӽ�¼
	// ˢ�¸��б�
	UpdateDG(m_pDG2rs,m_cDG2,2);
	UpdateDG(m_pDG3rs,m_cDG3,3);
	UpdateDG(m_pDG4rs,m_cDG4,4);
	UpdateDG(m_pDG5rs,m_cDG5,5);
}

void CSalaryDlg::UpdateDG(_RecordsetPtr pDGrs, CDataGrid& cDG, int index)
{
	CString str;
	// ����index�õ���������
	switch(index)
	{
	case 2:
		str="PERSON='" + m_strPersonID + "' and YEARMONTH='0000000'";
		break;
	case 3:
		str="PERSON='" + m_strPersonID
			+ "' and YEARMONTH='" + m_strYearMonth
			+ "' and TYPE='0'";
		break;
	case 4:
		str="(PERSON='" + m_strPersonID
			+ "' and YEARMONTH='" + m_strYearMonth
			+ "' and TYPE='1') or " +
			"(PERSON='" + m_strPersonID
			+ "' and YEARMONTH='" + m_strYearMonth
			+ "' and TYPE='2')";
		break;
	case 5:
		str="PERSON='" + m_strPersonID
			+ "' and YEARMONTH='" + m_strYearMonth
			+ "' and TYPE='3'";
		break;
	default:
		return;
	}
	if(pDGrs->GetState()==adStateOpen) pDGrs->Close(); // �ر�Recordset
	pDGrs->Filter=str.AllocSysString(); // �趨��������
	// ��Recordset
	pDGrs->Open("SALARY_OTHER",
		pTheConn.GetInterfacePtr(),
		adOpenKeyset,adLockOptimistic,adCmdTable);
	int n=m_pDG2rs->RecordCount;
	// ����DataGrid
	cDG.SetRefDataSource((LPUNKNOWN)pDGrs);
}

void CSalaryDlg::OnBtnAddList() 
{
	UpdateData(); // ��������
	_variant_t Value;
	CString strPersonID;
	// �ж����ݿ��Ƿ�����
	if(pTheConn->GetState()==adStateClosed) return;
	if(m_pDG1rs->GetState()==adStateClosed) return;
	m_pDG1rs->MoveFirst(); // �ƶ���ͷ
	while(!m_pDG1rs->adoEOF) // ����Ա���б�
	{
		Value=m_pDG1rs->GetCollect("ID"); // �õ�Ա����
		strPersonID=(char*)_bstr_t(Value);
		AddRecord(strPersonID);
		m_pDG1rs->MoveNext();
	}
	// ˢ�¸��б�
	UpdateDG(m_pDG2rs,m_cDG2,2);
	UpdateDG(m_pDG3rs,m_cDG3,3);
	UpdateDG(m_pDG4rs,m_cDG4,4);
	UpdateDG(m_pDG5rs,m_cDG5,5);
}

void CSalaryDlg::OnConfigFormula() // ��ʾ��ʽ��������
{
	CFormulaDlg FormulaDlg;
	FormulaDlg.DoModal();
}

void CSalaryDlg::OnSystemExit() 
{
	EndDialog(IDOK); // �˳�����
}

void CSalaryDlg::OnCalculateStat() 
{
	CString str; // ��ʱ����
	int Rate_overtime,Money_errand,Money_late,Money_absent; // ��¼�м���
	long counter; // �������ֵ
	CString strYearMonth,strPerson,strAddDetail,strSubDetail; // ����˵����Ϣ
	float basic,bonus,add_total,sub_total,total,temp; // �����м���
	_RecordsetPtr pRS; // ��ʱRecordset����

	// ���ݿ�δ�����򷵻�
	if(pTheConn->GetState()==adStateClosed) return;
	UpdateData(); // ��������
	// ��ȡ����
	CString strFileName=".\\formula.ini"; // INI�ļ���
	Rate_overtime=GetPrivateProfileInt("Formula", "OverTime", 150, strFileName);
	Money_errand=GetPrivateProfileInt("Formula", "Errand", 100, strFileName);
	Money_late=GetPrivateProfileInt("Formula", "Late", 10, strFileName);
	Money_absent=GetPrivateProfileInt("Formula", "Absent", 50, strFileName);
	strYearMonth=m_strYearMonth; // ��ȡͳ���·�
	// ����Ա���б�
	_RecordsetPtr pRS_person;
	pRS_person.CreateInstance(__uuidof(Recordset)); // ����Recordset����
	// ��Recordset����
	pRS_person->Open("select ID from PERSON where STATE='T'",
			pTheConn.GetInterfacePtr(),
			adOpenKeyset,adLockOptimistic,adCmdText);
	while(!pRS_person->adoEOF) // ����Ա���б�
	{
		strPerson=(char*)_bstr_t(pRS_person->GetCollect("ID")); // ��ȡԱ����
		strAddDetail.Empty(); // ������ӽ��˵��
		strSubDetail.Empty(); // ����۳����˵��
		basic=0; // ��ʼ����������
		bonus=0; // ��ʼ����������
		add_total=0; // ��ʼ�����ӽ��
		sub_total=0; // ��ʼ���۳����
		total=0;
		pRS.CreateInstance(__uuidof(Recordset)); // ����Recordset����
	// ��ȡԱ����������
		str="select SALARY from SALARY_SET where PERSON='" + strPerson + "'";
		if(pRS->GetState()==adStateOpen) pRS->Close();
		pRS->Open(str.AllocSysString(),
			pTheConn.GetInterfacePtr(),
			adOpenStatic,adLockReadOnly,adCmdText);
		basic=pRS->GetCollect("SALARY").fltVal; // ��ȡԱ����������
		pRS->Close(); // �ر�Recordset����
	// ��ȡԱ�����ڼ�¼��������ع��ʶ�
		str="select * from ATTENDANCE_STAT where YEAR_MONTH='"
			+ strYearMonth
			+ "' and PERSON='" +strPerson + "'";
		pRS->Open(str.AllocSysString(),
			pTheConn.GetInterfacePtr(),
			adOpenKeyset,adLockOptimistic,adCmdText);
		basic*=pRS->GetCollect("WORK_HOUR").iVal; // �����������
		// ����Ӱ��
		temp=basic*pRS->GetCollect("OVER_HOUR").iVal*Rate_overtime/100.0;
		if(temp>0) // �ж��Ƿ��мӰ��
		{
			add_total+=temp; // ���Ӹ��ӽ��
			str.Format("%.f",temp); // ת��tempΪ�ַ���
			strAddDetail+="�Ӱ��:"+str+";"; // ���Ӹ��ӽ��˵��
		}
		// ��������
		temp=Money_errand*pRS->GetCollect("ERRAND_HDAY").iVal;
		if(temp>0) // �ж��Ƿ��мӰ��
		{
			add_total+=temp; // ���Ӹ��ӽ��
			str.Format("%.f",temp); // ת��tempΪ�ַ���
			strAddDetail+="���÷�:"+str+";"; // ���Ӹ��ӽ��˵��
		}
		// �����󹤷�
		temp=Money_late*(pRS->GetCollect("LATE_TIMES").bVal
						+pRS->GetCollect("EARLY_TIMES").bVal)
			+Money_absent*pRS->GetCollect("ABSENT_TIMES").bVal;
		if(temp>0) // �ж��Ƿ����󹤷�
		{
			sub_total+=temp; // ���ӿ۳����
			str.Format("%.f",temp); // ת��tempΪ�ַ���
			strSubDetail+="�󹤷�:"+str+";"; // ���ӿ۳����˵��
		}
		pRS->Close(); // �ر�Recordset����
	// ͳ�ƽ����¼
		str="select NAME,MONEY from SALARY_OTHER where (YEARMONTH='"
			+ strYearMonth + "' or YEARMONTH='0000000')"
			+ " and PERSON='" +strPerson
			+ "' and TYPE='0'";
		pRS->Open(str.AllocSysString(),
			pTheConn.GetInterfacePtr(),
			adOpenKeyset,adLockOptimistic,adCmdText);
		while(!pRS->adoEOF) // ���ζ����м�¼���в���
		{
			bonus+=pRS->GetCollect("MONEY").fltVal; // ���ӽ����
			pRS->MoveNext(); // ������һ����¼
		}
		pRS->Close(); // �ر�Recordset����
	// ͳ�Ƹ�����¼
		str="select NAME,MONEY from SALARY_OTHER where (YEARMONTH='"
			+ strYearMonth + "' or YEARMONTH='0000000')"
			+ " and PERSON='" +strPerson
			+ "' and TYPE='1'";
		pRS->Open(str.AllocSysString(),
			pTheConn.GetInterfacePtr(),
			adOpenKeyset,adLockOptimistic,adCmdText);
		while(!pRS->adoEOF) // ���ζ����м�¼���в���
		{
			temp=pRS->GetCollect("MONEY").fltVal; // ��ȡ�������
			add_total+=temp; // ���Ӹ��ӽ��
			str.Format("%.f",temp); // ת��tempΪ�ַ���
			// ���Ӹ��ӽ��˵��
			CString strTmp=(char*)_bstr_t(pRS->GetCollect("NAME"));
			strAddDetail+=strTmp + ":" + str + ";";
			pRS->MoveNext(); // ������һ����¼
		}
		pRS->Close(); // �ر�Recordset����
	// ͳ�ƽ�����¼
		str="select NAME,MONEY from SALARY_OTHER where (YEARMONTH='"
			+ strYearMonth + "' or YEARMONTH='0000000')"
			+ " and PERSON='" +strPerson
			+ "' and TYPE='2'";
		pRS->Open(str.AllocSysString(),
			pTheConn.GetInterfacePtr(),
			adOpenKeyset,adLockOptimistic,adCmdText);
		while(!pRS->adoEOF) // ���ζ����м�¼���в���
		{
			temp=pRS->GetCollect("MONEY").fltVal; // ��ȡ�������
			add_total+=temp; // ���Ӹ��ӽ��
			str.Format("%.f",temp); // ת��tempΪ�ַ���
			// ���Ӹ��ӽ��˵��
			CString strTmp=(char*)_bstr_t(pRS->GetCollect("NAME"));
			strAddDetail+=strTmp + ":" + str + ";";
			pRS->MoveNext(); // ������һ����¼
		}
		pRS->Close(); // �ر�Recordset����
	// ͳ�ƿ۷���¼
		str="select NAME,MONEY from SALARY_OTHER where (YEARMONTH='"
			+ strYearMonth + "' or YEARMONTH='0000000')"
			+ " and PERSON='" +strPerson
			+ "' and TYPE='3'";
		pRS->Open(str.AllocSysString(),
			pTheConn.GetInterfacePtr(),
			adOpenKeyset,adLockOptimistic,adCmdText);
		while(!pRS->adoEOF) // ���ζ����м�¼���в���
		{
			temp=pRS->GetCollect("MONEY").fltVal; // ��ȡ�۷����
			sub_total+=temp; // ���ӿ۷����
			str.Format("%.f",temp); // ת��tempΪ�ַ���
			// ���ӿ۷����˵��
			CString strTmp=(char*)_bstr_t(pRS->GetCollect("NAME"));
			strSubDetail+=strTmp + ":" + str + ";";
			pRS->MoveNext(); // ������һ����¼
		}
		pRS->Close(); // �ر�Recordset����
	// ����ʵ�����
		total=basic+bonus+add_total-sub_total;
		if(total<0) total=0; // ��֤ʵ����С��0
	// ���빤�ʼ�¼
		str="YEARMONTH='"+strYearMonth+"' and PERSON='"+strPerson+"'";
		pRS->Filter=str.AllocSysString(); // ���ù�������
		// �򿪹��ʱ�
		pRS->Open("SALARY",
			pTheConn.GetInterfacePtr(),
			adOpenKeyset,adLockOptimistic,adCmdTable);
		if(pRS->RecordCount==0) // �ж��Ƿ���ڸ��·ݼ�¼
		{ // �޾ɼ�¼,���½���¼
			// �򿪼�������
			_RecordsetPtr pRS_counter;
			pRS_counter.CreateInstance(__uuidof(Recordset));
			pRS_counter->Filter="ID='Y'"; // ���ù�������
			pRS_counter->Open("COUNTER",
					pTheConn.GetInterfacePtr(),
					adOpenKeyset,adLockOptimistic,adCmdTable);
			counter=pRS_counter->GetCollect("COUNTER_VALUE").iVal; // ��ȡ����ֵ
			counter++; // ����ֵ��1
			pRS_counter->Fields->GetItem("COUNTER_VALUE")->PutValue(_variant_t(counter));
			pRS_counter->Update(); // ����
			pRS_counter->Close(); // �ر�
			pRS_counter.Release(); // �ͷ�
			// ׷�ӹ��ʼ�¼
			pRS->AddNew();
			pRS->Fields->GetItem("ID")->PutValue(_variant_t(counter));
			pRS->Fields->GetItem("YEARMONTH")->PutValue(strYearMonth.AllocSysString());
			pRS->Fields->GetItem("PERSON")->PutValue(strPerson.AllocSysString());
			pRS->Fields->GetItem("BASIC")->PutValue(_variant_t(basic));
			pRS->Fields->GetItem("BONUS")->PutValue(_variant_t(bonus));
			pRS->Fields->GetItem("ADD_DETAIL")->PutValue(strAddDetail.AllocSysString());
			pRS->Fields->GetItem("ADD_TOTAL")->PutValue(_variant_t(add_total));
			pRS->Fields->GetItem("SUB_DETAIL")->PutValue(strSubDetail.AllocSysString());
			pRS->Fields->GetItem("SUB_TOTAL")->PutValue(_variant_t(sub_total));
			pRS->Fields->GetItem("TOTAL")->PutValue(_variant_t(total));
			pRS->Update(); // ����
		}
		else // �оɼ�¼���޸ļ�¼
		{
			pRS->Fields->GetItem("BASIC")->PutValue(_variant_t(basic));
			pRS->Fields->GetItem("BONUS")->PutValue(_variant_t(bonus));
			pRS->Fields->GetItem("ADD_DETAIL")->PutValue(strAddDetail.AllocSysString());
			pRS->Fields->GetItem("ADD_TOTAL")->PutValue(_variant_t(add_total));
			pRS->Fields->GetItem("SUB_DETAIL")->PutValue(strSubDetail.AllocSysString());
			pRS->Fields->GetItem("SUB_TOTAL")->PutValue(_variant_t(sub_total));
			pRS->Fields->GetItem("TOTAL")->PutValue(_variant_t(total));
			pRS->Update(); // ����
		}
		pRS->Close(); // �ر�Recordset����
		pRS->Release(); // �ͷ�
	// ������һ��Ա����¼
		pRS_person->MoveNext();
	}
	pRS_person.Release(); // �ͷ�
}

BOOL CSalaryDlg::PreTranslateMessage(MSG* pMsg) 
{
	// �����ݼ�
	TranslateAccelerator(m_hWnd, m_hAccTable, pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}

void CSalaryDlg::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu)
{// ����˵����Prompt
	CDialog::OnMenuSelect(nItemID, nFlags, hSysMenu);
    if (nItemID != 0) // ����Ϊ0(seperatorʱ)
    {
		CString strStatusText;
		strStatusText.LoadString( nItemID );
		if (!strStatusText.IsEmpty())
		m_wndStatusBar.SetPaneText(0, strStatusText);
	}
}

void CSalaryDlg::RightClick(CDataGrid& DG, _RecordsetPtr pDGrs, short Button, long X, long Y)
{
	// ���Ҽ������򷵻�
	if(Button!=2) return;
	// �õ�DataGrid��������
	CRect rc;
	DG.GetWindowRect(&rc);
	// �õ���갴��ʱλ��
	CPoint pt;
	pt.x=X+rc.left;
	pt.y=Y+rc.top;
	// �����Ҽ��˵�
	CMenu popup;
	popup.CreatePopupMenu();
	popup.AppendMenu(MF_ENABLED,IDM_MENU_DELETERECORD,"ɾ����ǰ��¼(&Z)");
	popup.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pt.x,pt.y,this);
	// ��¼��ǰ����DataGrid
	m_pCurDGrs=pDGrs;
}

void CSalaryDlg::OnMouseDownDatagrid2(short Button, short Shift, long X, long Y) 
{
	RightClick(m_cDG2, m_pDG2rs, Button, X, Y); // �����Ҽ��˵�
}

void CSalaryDlg::OnMouseDownDatagrid3(short Button, short Shift, long X, long Y) 
{
	RightClick(m_cDG3, m_pDG3rs, Button, X, Y); // �����Ҽ��˵�
}

void CSalaryDlg::OnMouseDownDatagrid4(short Button, short Shift, long X, long Y) 
{
	RightClick(m_cDG4, m_pDG4rs, Button, X, Y); // �����Ҽ��˵�
}

void CSalaryDlg::OnMouseDownDatagrid5(short Button, short Shift, long X, long Y) 
{
	RightClick(m_cDG5, m_pDG5rs, Button, X, Y); // �����Ҽ��˵�
}

void CSalaryDlg::OnDeleteRecord()
{
	// ���ݿ�δ�����򷵻�
	if(pTheConn->GetState()==adStateClosed) return;
	// Recordset�����״̬��ɾ����ǰ��¼
	if(m_pCurDGrs->GetState()==adStateOpen)
		m_pCurDGrs->Delete(adAffectCurrent); // ɾ����ǰ��¼
}

void CSalaryDlg::OnPreviewView() // �鿴���¹���
{
	// ���ݿ�δ�����򷵻�
	if(pTheConn->GetState()==adStateClosed) return;
	UpdateData(); // ��������

	CPreviewDlg dlg;
	dlg.m_strYearMonth=m_strYearMonth;
	dlg.DoModal(); // ��ʾ���¹��ʼ�����
}
