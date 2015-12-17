// AttendanceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Attendance.h"
#include "AttendanceDlg.h"
#include "LoginDlg.h"
#include "WorkplanDlg.h"
#include "AttDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CAttendanceDlg dialog

CAttendanceDlg::CAttendanceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAttendanceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAttendanceDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAttendanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAttendanceDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAttendanceDlg, CDialog)
	//{{AFX_MSG_MAP(CAttendanceDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_RELOGIN, OnBtnRelogin)
	ON_BN_CLICKED(IDC_BTN_CONFIG, OnBtnConfig)
	ON_BN_CLICKED(IDC_BTN_RECORD, OnBtnRecord)
	ON_BN_CLICKED(IDC_BTN_STATISTICS, OnBtnStatistics)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttendanceDlg message handlers

BOOL CAttendanceDlg::OnInitDialog()
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
	// 改变标题字体大小
	LOGFONT LogFont;
	GetFont()->GetLogFont(&LogFont);
	LogFont.lfHeight+=LogFont.lfHeight/2;
	LogFont.lfWidth+=LogFont.lfWidth/2;
	m_font.CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_STATIC_HEAD)->SetFont(&m_font);

	// 初始化对话框指针为空
	m_pAttDlg=NULL;
	m_pStatDlg=NULL;

	// 创建背景画刷
	m_brush.CreateSolidBrush(RGB(0, 255, 255));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAttendanceDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAttendanceDlg::OnPaint() 
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
HCURSOR CAttendanceDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAttendanceDlg::OnBtnExit() 
{
	EndDialog(IDCANCEL); // 退出主对话框，关闭程序
}

void CAttendanceDlg::OnBtnRelogin() 
{
	// 隐藏主对话框
	ShowWindow(SW_HIDE);
	// 显示登录对话框
	CLoginDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		ShowWindow(SW_SHOW); // 显示对话框
	}
	else EndDialog(IDCANCEL); // 退出程序
}

void CAttendanceDlg::OnBtnConfig() 
{
	// 显示工作时间设置对话框
	CWorkplanDlg dlg;
	dlg.DoModal();
}

void CAttendanceDlg::OnBtnRecord() 
{
	// 非模态显示出勤记录对话框
	if(!m_pAttDlg) // 指针为空，创建对话框
	{
		m_pAttDlg=new CAttDlg();
		m_pAttDlg->Create(IDD_DLG_ATTENDANCE, this);
		m_pAttDlg->ShowWindow(SW_SHOW);
	}
	else // 对话框已创建
		m_pAttDlg->ShowWindow(SW_SHOW); // 显示窗口
}

void CAttendanceDlg::OnBtnStatistics() 
{
	// 非模态显示考勤统计对话框
	if(!m_pStatDlg) // 指针为空，创建对话框
	{
		m_pStatDlg=new CStatDlg();
		m_pStatDlg->Create(IDD_DLG_STAT, this);
		m_pStatDlg->ShowWindow(SW_SHOW);
	}
	else // 对话框已创建
		m_pStatDlg->ShowWindow(SW_SHOW); // 显示窗口
}

HBRUSH CAttendanceDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	pDC->SetBkMode(TRANSPARENT); // 设置背景模式
	return m_brush; // 返回画刷
}
