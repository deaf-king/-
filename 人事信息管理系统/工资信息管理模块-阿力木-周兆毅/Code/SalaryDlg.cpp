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
	// 设置项目缺省选择为奖金
	((CButton*)GetDlgItem(IDC_RADIO_BONUS))->SetCheck(TRUE);
	// 创建状态条
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	CRect rect;
	GetClientRect(&rect);
	// 设定状态条
	m_wndStatusBar.SetPaneInfo(0,ID_INDICATOR_MESSAGE, 
							   SBPS_NORMAL,rect.Width()/2);
	m_wndStatusBar.SetPaneInfo(1,ID_INDICATOR_LOGIN,SBPS_STRETCH,0);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,
    ID_INDICATOR_LOGIN);
	// 加载加速键
	m_hAccTable=::LoadAccelerators(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR));
	// 创建DataGrid需要用的Recordset对象
	m_pDG1rs.CreateInstance(__uuidof(Recordset)); // DataGrid1相关
	m_pDG2rs.CreateInstance(__uuidof(Recordset)); // DataGrid2相关
	m_pDG3rs.CreateInstance(__uuidof(Recordset)); // DataGrid3相关
	m_pDG4rs.CreateInstance(__uuidof(Recordset)); // DataGrid4相关
	m_pDG5rs.CreateInstance(__uuidof(Recordset)); // DataGrid5相关
	
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
	
	// 释放DataGrid需要用的Recordset对象
	m_pDG1rs.Release(); // DataGrid1相关
	m_pDG2rs.Release(); // DataGrid2相关
	m_pDG3rs.Release(); // DataGrid3相关
	m_pDG4rs.Release(); // DataGrid4相关
	m_pDG5rs.Release(); // DataGrid5相关
}

void CSalaryDlg::OnSystemConnect() // 显示用户登录窗口
{
	CLoginDlg LoginDlg;
	if(LoginDlg.DoModal()==IDOK) // 认证通过
		m_wndStatusBar.SetPaneText(1, "已连接到数据库: " + LoginDlg.m_strDSN);
}

void CSalaryDlg::OnSystemDisconnect() // 断开连接
{
	// 关闭Connetion对象
	if(pTheConn->GetState()==adStateOpen)
		pTheConn->Close();
	m_wndStatusBar.SetPaneText(1, "尚未登录数据库，请按F2登录");
}

void CSalaryDlg::OnChangeEdtDepartid() 
{
	if(pTheConn->GetState()==adStateClosed) return; // 数据库未打开则返回
	UpdateData(); // 更新数据

	CString str;
	_variant_t Value;
	_RecordsetPtr pRS; // Recordset对象
	pRS.CreateInstance(__uuidof(Recordset)); // 创建
	// 更新DataGrid1数据
	str="select ID,NAME from PERSON where DEPARTMENT like '"
		+ m_strDepartID + "' and STATE='T'";
	if(m_pDG1rs->GetState()==adStateOpen) m_pDG1rs->Close(); // 关闭Recordset
	// 打开Recordset
	m_pDG1rs->Open(str.AllocSysString(),
		pTheConn.GetInterfacePtr(),
		adOpenStatic,adLockReadOnly,adCmdText);
	// 设置DataGrid1
	m_cDG1.SetRefDataSource((LPUNKNOWN)m_pDG1rs);
	// 更新部门名称
	str="select NAME from DEPARTMENT where ID='" + m_strDepartID + "'";
	pRS->Open(str.AllocSysString(),
			pTheConn.GetInterfacePtr(),
			adOpenStatic,adLockReadOnly,adCmdText);
	if(pRS->RecordCount==1) // 判断记录是否存在
	{
		Value=pRS->GetCollect("NAME"); // 得到部门名称
		if(Value.vt!=VT_NULL) m_strDepartName=(char*)_bstr_t(Value);
	}
	else
		m_strDepartName.Empty(); // 清除部门名称

	UpdateData(FALSE); // 更新界面数据
	pRS.Release(); // 释放
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
	UpdateData(); // 更新数据
	_variant_t Value;
	if(m_pDG1rs->GetState()==adStateOpen) // 判断列表是否打开
	{
		Value=m_pDG1rs->GetCollect("ID"); // 得到员工号
		m_strPersonID=(char*)_bstr_t(Value);
	}
	UpdateData(FALSE); // 更新界面数据
	OnChangeEdtPersonid(); // 改变员工信息
}

void CSalaryDlg::OnChangeEdtPersonid() 
{
	// 数据库未连接则返回
	if(pTheConn->GetState()==adStateClosed) return;

	UpdateData(); // 更新数据
	CString str;
	_variant_t Value;
	_RecordsetPtr pRS; // Recordset对象
	str="select NAME from PERSON where ID='"
		+ m_strPersonID + "' and STATE='T'";
	pRS.CreateInstance(__uuidof(Recordset)); // 创建
	// 打开Recordset
	pRS->Open(str.AllocSysString(),
		pTheConn.GetInterfacePtr(),
		adOpenStatic,adLockReadOnly,adCmdText);
	if(pRS->RecordCount==1) // 判断记录是否存在
	{
	// 更新员工姓名
		Value=pRS->GetCollect("NAME"); // 得到员工姓名
		if(Value.vt!=VT_NULL) m_strPersonName=(char*)_bstr_t(Value);
	// 更新基本工资
		pRS->Close(); // 关闭
		str="PERSON='" + m_strPersonID + "'";
		pRS->Filter=str.AllocSysString();
		// 打开Recordset
		pRS->Open("SALARY_SET",
			pTheConn.GetInterfacePtr(),
			adOpenKeyset,adLockOptimistic,adCmdTable);
		if(pRS->RecordCount==1) // 判断记录是否存在
		{
			Value=pRS->GetCollect("SALARY"); // 得到工资
			if(Value.vt!=VT_NULL) m_fBasicSalary=Value.fltVal;
		}
		else // 添加记录
		{
			m_fBasicSalary=0; // 缺省工资
			pRS->AddNew();
			pRS->Fields->GetItem("PERSON")->PutValue(m_strPersonID.AllocSysString());
			pRS->Fields->GetItem("SALARY")->PutValue(_variant_t(m_fBasicSalary));
			pRS->Update();
		}
	// 开放“更改基本工资”按钮
		GetDlgItem(IDC_BTN_CHANGESALARY)->EnableWindow(TRUE);
	// 更新“固定福利津贴”列表
		UpdateDG(m_pDG2rs, m_cDG2, 2);
	// 更新“月度奖金”列表
		UpdateDG(m_pDG3rs, m_cDG3, 3);
	// 更新“月度福利津贴”列表
		UpdateDG(m_pDG4rs, m_cDG4, 4);
	// 更新“月度扣发”列表
		UpdateDG(m_pDG5rs, m_cDG5, 5);
	}
	else
	{
		m_strPersonName.Empty(); // 清除员工姓名
		m_fBasicSalary=0; // 清除工资
		// 禁止“更改基本工资”按钮
		GetDlgItem(IDC_BTN_CHANGESALARY)->EnableWindow(FALSE);
		// 清除各DataGrid
		if(m_pDG2rs->GetState()==adStateOpen) m_pDG2rs->Close();
		if(m_pDG3rs->GetState()==adStateOpen) m_pDG3rs->Close();
		if(m_pDG4rs->GetState()==adStateOpen) m_pDG4rs->Close();
		if(m_pDG5rs->GetState()==adStateOpen) m_pDG5rs->Close();
		m_cDG2.Refresh();
		m_cDG3.Refresh();
		m_cDG4.Refresh();
		m_cDG5.Refresh();
	}

	UpdateData(FALSE); // 更新界面数据
	pRS.Release(); // 释放
}

void CSalaryDlg::OnBtnChangesalary() 
{
	// 数据库未连接则返回
	if(pTheConn->GetState()==adStateClosed) return;

	CString str;
	_variant_t Value;
	_RecordsetPtr pRS; // Recordset对象
	pRS.CreateInstance(__uuidof(Recordset)); // 创建
	UpdateData(); // 更新数据
	// 打开Recordset
	str="PERSON='" + m_strPersonID + "'";
	pRS->Filter=str.AllocSysString(); // 设置过滤条件
	pRS->Open("SALARY_SET",
		pTheConn.GetInterfacePtr(),
		adOpenKeyset,adLockOptimistic,adCmdTable);
	if(pRS->RecordCount==1) // 判断记录是否存在
	{
		// 更新工资
		pRS->Fields->GetItem("SALARY")->PutValue(_variant_t(m_fBasicSalary));
		pRS->Update();
	}
	pRS.Release(); // 释放
}

void CSalaryDlg::AddRecord(CString strPersonID)
{
	CString strType; // 项目类型
	long counter; // 用于保存计数
	CString strYearMonth; // 用于保存年月信息
	_RecordsetPtr pRS; // Recordset对象
	pRS.CreateInstance(__uuidof(Recordset)); // 创建

	if(m_bFixed) strYearMonth="0000000"; // 判断是否固定津贴
	else strYearMonth=m_strYearMonth; // 提取年月信息
	pRS->Filter="ID='R'"; // 设置过滤器
	// 打开计数器表
	pRS->Open("COUNTER",
		pTheConn.GetInterfacePtr(),
		adOpenKeyset,adLockOptimistic,adCmdTable);
	counter=pRS->GetCollect("COUNTER_VALUE").iVal; // 提取计数值
	counter++; // 计数值加1
	pRS->Fields->GetItem("COUNTER_VALUE")->PutValue(_variant_t(counter));
	pRS->Update(); // 更新
	pRS->Close(); // 关闭
	// 添加记录
	// 得到项目类型
	if(((CButton*)GetDlgItem(IDC_RADIO_BONUS))->GetCheck()) strType="0";
	else if(((CButton*)GetDlgItem(IDC_RADIO_FULI))->GetCheck()) strType="1";
	else if(((CButton*)GetDlgItem(IDC_RADIO_JINTIE))->GetCheck()) strType="2";
	else strType="3";
	// 打开表
	pRS->Open("SALARY_OTHER",
		pTheConn.GetInterfacePtr(),
		adOpenKeyset,adLockOptimistic,adCmdTable);
	pRS->AddNew(); // 添加新纪录
	pRS->Fields->GetItem("ID")->PutValue(_variant_t(counter));
	pRS->Fields->GetItem("YEARMONTH")->PutValue(strYearMonth.AllocSysString());
	pRS->Fields->GetItem("PERSON")->PutValue(strPersonID.AllocSysString());
	pRS->Fields->GetItem("TYPE")->PutValue(strType.AllocSysString());
	pRS->Fields->GetItem("NAME")->PutValue(m_strItemName.AllocSysString());
	pRS->Fields->GetItem("MONEY")->PutValue(_variant_t(m_fMoney));
	pRS->Fields->GetItem("DESCRIPTION")->PutValue(m_strDesription.AllocSysString());
	pRS->Update(); // 更新
	pRS.Release(); // 释放
}

void CSalaryDlg::OnBtnAddPerson() 
{
	// 数据库未连接则返回
	if(pTheConn->GetState()==adStateClosed) return;
	UpdateData(); // 更新数据
	// 无数据返回
	if(m_strItemName.IsEmpty() || m_strPersonName.IsEmpty()) return;
	AddRecord(m_strPersonID); // 添加记录
	// 刷新各列表
	UpdateDG(m_pDG2rs,m_cDG2,2);
	UpdateDG(m_pDG3rs,m_cDG3,3);
	UpdateDG(m_pDG4rs,m_cDG4,4);
	UpdateDG(m_pDG5rs,m_cDG5,5);
}

void CSalaryDlg::UpdateDG(_RecordsetPtr pDGrs, CDataGrid& cDG, int index)
{
	CString str;
	// 根据index得到过滤条件
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
	if(pDGrs->GetState()==adStateOpen) pDGrs->Close(); // 关闭Recordset
	pDGrs->Filter=str.AllocSysString(); // 设定过滤条件
	// 打开Recordset
	pDGrs->Open("SALARY_OTHER",
		pTheConn.GetInterfacePtr(),
		adOpenKeyset,adLockOptimistic,adCmdTable);
	int n=m_pDG2rs->RecordCount;
	// 设置DataGrid
	cDG.SetRefDataSource((LPUNKNOWN)pDGrs);
}

void CSalaryDlg::OnBtnAddList() 
{
	UpdateData(); // 更新数据
	_variant_t Value;
	CString strPersonID;
	// 判断数据库是否连接
	if(pTheConn->GetState()==adStateClosed) return;
	if(m_pDG1rs->GetState()==adStateClosed) return;
	m_pDG1rs->MoveFirst(); // 移动到头
	while(!m_pDG1rs->adoEOF) // 遍历员工列表
	{
		Value=m_pDG1rs->GetCollect("ID"); // 得到员工号
		strPersonID=(char*)_bstr_t(Value);
		AddRecord(strPersonID);
		m_pDG1rs->MoveNext();
	}
	// 刷新各列表
	UpdateDG(m_pDG2rs,m_cDG2,2);
	UpdateDG(m_pDG3rs,m_cDG3,3);
	UpdateDG(m_pDG4rs,m_cDG4,4);
	UpdateDG(m_pDG5rs,m_cDG5,5);
}

void CSalaryDlg::OnConfigFormula() // 显示公式调整窗口
{
	CFormulaDlg FormulaDlg;
	FormulaDlg.DoModal();
}

void CSalaryDlg::OnSystemExit() 
{
	EndDialog(IDOK); // 退出程序
}

void CSalaryDlg::OnCalculateStat() 
{
	CString str; // 临时变量
	int Rate_overtime,Money_errand,Money_late,Money_absent; // 记录中间结果
	long counter; // 保存计数值
	CString strYearMonth,strPerson,strAddDetail,strSubDetail; // 保存说明信息
	float basic,bonus,add_total,sub_total,total,temp; // 保存中间结果
	_RecordsetPtr pRS; // 临时Recordset对象

	// 数据库未连接则返回
	if(pTheConn->GetState()==adStateClosed) return;
	UpdateData(); // 更新数据
	// 读取参数
	CString strFileName=".\\formula.ini"; // INI文件名
	Rate_overtime=GetPrivateProfileInt("Formula", "OverTime", 150, strFileName);
	Money_errand=GetPrivateProfileInt("Formula", "Errand", 100, strFileName);
	Money_late=GetPrivateProfileInt("Formula", "Late", 10, strFileName);
	Money_absent=GetPrivateProfileInt("Formula", "Absent", 50, strFileName);
	strYearMonth=m_strYearMonth; // 获取统计月份
	// 遍历员工列表
	_RecordsetPtr pRS_person;
	pRS_person.CreateInstance(__uuidof(Recordset)); // 创建Recordset对象
	// 打开Recordset对象
	pRS_person->Open("select ID from PERSON where STATE='T'",
			pTheConn.GetInterfacePtr(),
			adOpenKeyset,adLockOptimistic,adCmdText);
	while(!pRS_person->adoEOF) // 遍历员工列表
	{
		strPerson=(char*)_bstr_t(pRS_person->GetCollect("ID")); // 获取员工号
		strAddDetail.Empty(); // 清除附加金额说明
		strSubDetail.Empty(); // 清除扣除金额说明
		basic=0; // 初始化基本工资
		bonus=0; // 初始化红利奖金
		add_total=0; // 初始化附加金额
		sub_total=0; // 初始化扣除金额
		total=0;
		pRS.CreateInstance(__uuidof(Recordset)); // 创建Recordset对象
	// 获取员工基本工资
		str="select SALARY from SALARY_SET where PERSON='" + strPerson + "'";
		if(pRS->GetState()==adStateOpen) pRS->Close();
		pRS->Open(str.AllocSysString(),
			pTheConn.GetInterfacePtr(),
			adOpenStatic,adLockReadOnly,adCmdText);
		basic=pRS->GetCollect("SALARY").fltVal; // 获取员工基本工资
		pRS->Close(); // 关闭Recordset对象
	// 获取员工出勤记录，计算相关工资额
		str="select * from ATTENDANCE_STAT where YEAR_MONTH='"
			+ strYearMonth
			+ "' and PERSON='" +strPerson + "'";
		pRS->Open(str.AllocSysString(),
			pTheConn.GetInterfacePtr(),
			adOpenKeyset,adLockOptimistic,adCmdText);
		basic*=pRS->GetCollect("WORK_HOUR").iVal; // 计算基本工资
		// 计算加班费
		temp=basic*pRS->GetCollect("OVER_HOUR").iVal*Rate_overtime/100.0;
		if(temp>0) // 判断是否有加班费
		{
			add_total+=temp; // 增加附加金额
			str.Format("%.f",temp); // 转换temp为字符串
			strAddDetail+="加班费:"+str+";"; // 增加附加金额说明
		}
		// 计算出差费
		temp=Money_errand*pRS->GetCollect("ERRAND_HDAY").iVal;
		if(temp>0) // 判断是否有加班费
		{
			add_total+=temp; // 增加附加金额
			str.Format("%.f",temp); // 转换temp为字符串
			strAddDetail+="差旅费:"+str+";"; // 增加附加金额说明
		}
		// 计算误工费
		temp=Money_late*(pRS->GetCollect("LATE_TIMES").bVal
						+pRS->GetCollect("EARLY_TIMES").bVal)
			+Money_absent*pRS->GetCollect("ABSENT_TIMES").bVal;
		if(temp>0) // 判断是否有误工费
		{
			sub_total+=temp; // 增加扣除金额
			str.Format("%.f",temp); // 转换temp为字符串
			strSubDetail+="误工费:"+str+";"; // 增加扣除金额说明
		}
		pRS->Close(); // 关闭Recordset对象
	// 统计奖金记录
		str="select NAME,MONEY from SALARY_OTHER where (YEARMONTH='"
			+ strYearMonth + "' or YEARMONTH='0000000')"
			+ " and PERSON='" +strPerson
			+ "' and TYPE='0'";
		pRS->Open(str.AllocSysString(),
			pTheConn.GetInterfacePtr(),
			adOpenKeyset,adLockOptimistic,adCmdText);
		while(!pRS->adoEOF) // 依次对所有记录进行操作
		{
			bonus+=pRS->GetCollect("MONEY").fltVal; // 增加奖金额
			pRS->MoveNext(); // 跳到下一条记录
		}
		pRS->Close(); // 关闭Recordset对象
	// 统计福利记录
		str="select NAME,MONEY from SALARY_OTHER where (YEARMONTH='"
			+ strYearMonth + "' or YEARMONTH='0000000')"
			+ " and PERSON='" +strPerson
			+ "' and TYPE='1'";
		pRS->Open(str.AllocSysString(),
			pTheConn.GetInterfacePtr(),
			adOpenKeyset,adLockOptimistic,adCmdText);
		while(!pRS->adoEOF) // 依次对所有记录进行操作
		{
			temp=pRS->GetCollect("MONEY").fltVal; // 提取福利金额
			add_total+=temp; // 增加附加金额
			str.Format("%.f",temp); // 转换temp为字符串
			// 增加附加金额说明
			CString strTmp=(char*)_bstr_t(pRS->GetCollect("NAME"));
			strAddDetail+=strTmp + ":" + str + ";";
			pRS->MoveNext(); // 跳到下一条记录
		}
		pRS->Close(); // 关闭Recordset对象
	// 统计津贴记录
		str="select NAME,MONEY from SALARY_OTHER where (YEARMONTH='"
			+ strYearMonth + "' or YEARMONTH='0000000')"
			+ " and PERSON='" +strPerson
			+ "' and TYPE='2'";
		pRS->Open(str.AllocSysString(),
			pTheConn.GetInterfacePtr(),
			adOpenKeyset,adLockOptimistic,adCmdText);
		while(!pRS->adoEOF) // 依次对所有记录进行操作
		{
			temp=pRS->GetCollect("MONEY").fltVal; // 提取津贴金额
			add_total+=temp; // 增加附加金额
			str.Format("%.f",temp); // 转换temp为字符串
			// 增加附加金额说明
			CString strTmp=(char*)_bstr_t(pRS->GetCollect("NAME"));
			strAddDetail+=strTmp + ":" + str + ";";
			pRS->MoveNext(); // 跳到下一条记录
		}
		pRS->Close(); // 关闭Recordset对象
	// 统计扣发记录
		str="select NAME,MONEY from SALARY_OTHER where (YEARMONTH='"
			+ strYearMonth + "' or YEARMONTH='0000000')"
			+ " and PERSON='" +strPerson
			+ "' and TYPE='3'";
		pRS->Open(str.AllocSysString(),
			pTheConn.GetInterfacePtr(),
			adOpenKeyset,adLockOptimistic,adCmdText);
		while(!pRS->adoEOF) // 依次对所有记录进行操作
		{
			temp=pRS->GetCollect("MONEY").fltVal; // 提取扣发金额
			sub_total+=temp; // 增加扣发金额
			str.Format("%.f",temp); // 转换temp为字符串
			// 增加扣发金额说明
			CString strTmp=(char*)_bstr_t(pRS->GetCollect("NAME"));
			strSubDetail+=strTmp + ":" + str + ";";
			pRS->MoveNext(); // 跳到下一条记录
		}
		pRS->Close(); // 关闭Recordset对象
	// 计算实发金额
		total=basic+bonus+add_total-sub_total;
		if(total<0) total=0; // 保证实发金额不小于0
	// 插入工资记录
		str="YEARMONTH='"+strYearMonth+"' and PERSON='"+strPerson+"'";
		pRS->Filter=str.AllocSysString(); // 设置过滤条件
		// 打开工资表
		pRS->Open("SALARY",
			pTheConn.GetInterfacePtr(),
			adOpenKeyset,adLockOptimistic,adCmdTable);
		if(pRS->RecordCount==0) // 判断是否存在该月份记录
		{ // 无旧记录,则新建记录
			// 打开计数器表
			_RecordsetPtr pRS_counter;
			pRS_counter.CreateInstance(__uuidof(Recordset));
			pRS_counter->Filter="ID='Y'"; // 设置过滤条件
			pRS_counter->Open("COUNTER",
					pTheConn.GetInterfacePtr(),
					adOpenKeyset,adLockOptimistic,adCmdTable);
			counter=pRS_counter->GetCollect("COUNTER_VALUE").iVal; // 提取计数值
			counter++; // 计数值加1
			pRS_counter->Fields->GetItem("COUNTER_VALUE")->PutValue(_variant_t(counter));
			pRS_counter->Update(); // 更新
			pRS_counter->Close(); // 关闭
			pRS_counter.Release(); // 释放
			// 追加工资记录
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
			pRS->Update(); // 更新
		}
		else // 有旧记录则修改记录
		{
			pRS->Fields->GetItem("BASIC")->PutValue(_variant_t(basic));
			pRS->Fields->GetItem("BONUS")->PutValue(_variant_t(bonus));
			pRS->Fields->GetItem("ADD_DETAIL")->PutValue(strAddDetail.AllocSysString());
			pRS->Fields->GetItem("ADD_TOTAL")->PutValue(_variant_t(add_total));
			pRS->Fields->GetItem("SUB_DETAIL")->PutValue(strSubDetail.AllocSysString());
			pRS->Fields->GetItem("SUB_TOTAL")->PutValue(_variant_t(sub_total));
			pRS->Fields->GetItem("TOTAL")->PutValue(_variant_t(total));
			pRS->Update(); // 更新
		}
		pRS->Close(); // 关闭Recordset对象
		pRS->Release(); // 释放
	// 跳至下一个员工记录
		pRS_person->MoveNext();
	}
	pRS_person.Release(); // 释放
}

BOOL CSalaryDlg::PreTranslateMessage(MSG* pMsg) 
{
	// 处理快捷键
	TranslateAccelerator(m_hWnd, m_hAccTable, pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}

void CSalaryDlg::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu)
{// 处理菜单项的Prompt
	CDialog::OnMenuSelect(nItemID, nFlags, hSysMenu);
    if (nItemID != 0) // 可能为0(seperator时)
    {
		CString strStatusText;
		strStatusText.LoadString( nItemID );
		if (!strStatusText.IsEmpty())
		m_wndStatusBar.SetPaneText(0, strStatusText);
	}
}

void CSalaryDlg::RightClick(CDataGrid& DG, _RecordsetPtr pDGrs, short Button, long X, long Y)
{
	// 非右键按下则返回
	if(Button!=2) return;
	// 得到DataGrid窗口坐标
	CRect rc;
	DG.GetWindowRect(&rc);
	// 得到鼠标按下时位置
	CPoint pt;
	pt.x=X+rc.left;
	pt.y=Y+rc.top;
	// 弹出右键菜单
	CMenu popup;
	popup.CreatePopupMenu();
	popup.AppendMenu(MF_ENABLED,IDM_MENU_DELETERECORD,"删除当前记录(&Z)");
	popup.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pt.x,pt.y,this);
	// 记录当前所在DataGrid
	m_pCurDGrs=pDGrs;
}

void CSalaryDlg::OnMouseDownDatagrid2(short Button, short Shift, long X, long Y) 
{
	RightClick(m_cDG2, m_pDG2rs, Button, X, Y); // 弹出右键菜单
}

void CSalaryDlg::OnMouseDownDatagrid3(short Button, short Shift, long X, long Y) 
{
	RightClick(m_cDG3, m_pDG3rs, Button, X, Y); // 弹出右键菜单
}

void CSalaryDlg::OnMouseDownDatagrid4(short Button, short Shift, long X, long Y) 
{
	RightClick(m_cDG4, m_pDG4rs, Button, X, Y); // 弹出右键菜单
}

void CSalaryDlg::OnMouseDownDatagrid5(short Button, short Shift, long X, long Y) 
{
	RightClick(m_cDG5, m_pDG5rs, Button, X, Y); // 弹出右键菜单
}

void CSalaryDlg::OnDeleteRecord()
{
	// 数据库未连接则返回
	if(pTheConn->GetState()==adStateClosed) return;
	// Recordset对象打开状态则删除当前记录
	if(m_pCurDGrs->GetState()==adStateOpen)
		m_pCurDGrs->Delete(adAffectCurrent); // 删除当前记录
}

void CSalaryDlg::OnPreviewView() // 查看本月工资
{
	// 数据库未连接则返回
	if(pTheConn->GetState()==adStateClosed) return;
	UpdateData(); // 更新数据

	CPreviewDlg dlg;
	dlg.m_strYearMonth=m_strYearMonth;
	dlg.DoModal(); // 显示本月工资计算结果
}
