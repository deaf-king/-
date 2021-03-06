// Page4.cpp : implementation file
//

#include "stdafx.h"
#include "Attendance.h"
#include "Page4.h"
#include "PersonRS.h"
#include "CounterRS.h"
#include "AttDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDatabase db;
/////////////////////////////////////////////////////////////////////////////
// CPage4 property page

IMPLEMENT_DYNCREATE(CPage4, CPropertyPage)

CPage4::CPage4() : CPropertyPage(CPage4::IDD)
{
	// 得到当前时间并格式化
	CTime t=CTime::GetCurrentTime();
	CString str=t.Format("%Y-%m-%d %H:%M");
	//{{AFX_DATA_INIT(CPage4)
	m_strSTime = str;
	m_strETime = str;
	m_strPersonID = _T("");
	m_strPersonName = _T("");
	m_strDescription = _T("");
	//}}AFX_DATA_INIT
}

CPage4::~CPage4()
{
}

void CPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage4)
	DDX_Control(pDX, IDC_LIST4, m_cList);
	DDX_Text(pDX, IDC_EDT_ERRAND_STARTTIME, m_strSTime);
	DDX_Text(pDX, IDC_EDT_ERRAND_ENDTIME, m_strETime);
	DDX_Text(pDX, IDC_EDT_ERRAND_PERSONID, m_strPersonID);
	DDX_Text(pDX, IDC_EDT_ERRAND_PERSONNAME, m_strPersonName);
	DDX_Text(pDX, IDC_EDT_ERRAND_DESCRIPTION, m_strDescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage4, CPropertyPage)
	//{{AFX_MSG_MAP(CPage4)
	ON_EN_CHANGE(IDC_EDT_ERRAND_PERSONID, OnChangeEdtErrandPersonid)
	ON_BN_CLICKED(IDC_BTN_ERRAND_ADD, OnBtnErrandAdd)
	ON_BN_CLICKED(IDC_BTN_ERRAND_DELETEATTEND, OnBtnErrandDeleteattend)
	ON_BN_CLICKED(IDC_BTN_ERRAND_SEEKIO, OnBtnErrandSeekio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage4 message handlers

BOOL CPage4::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// 为List添加网格
	m_cList.SetExtendedStyle(LVS_EX_GRIDLINES);
	// 设置List的列
	int nWidth=90;
	m_cList.InsertColumn(0, "记录编号", LVCFMT_LEFT, nWidth-20);
	m_cList.InsertColumn(1, "员工号", LVCFMT_LEFT, nWidth-20);
	m_cList.InsertColumn(2, "开始时间", LVCFMT_LEFT, nWidth+20);
	m_cList.InsertColumn(3, "结束时间", LVCFMT_LEFT, nWidth+20);
	m_cList.InsertColumn(4, "具体描述", LVCFMT_LEFT, nWidth);
	CErrandRS rs(&db); // 构造出差记录表
	UpdateList(rs); // 更新List		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage4::UpdateList(CErrandRS &rs)
{
	int i=0;
	CString strID,strSTime,strETime;
	rs.Open(); // 打开出差记录表
	m_cList.DeleteAllItems(); // 清除列表框内容
	while(!rs.IsEOF()) // 对数据表中所有记录进行处理
	{
		m_cList.InsertItem(i, ""); // 添加新Item
		strID.Format("%d", rs.m_ID); // 转换为字符串
		m_cList.SetItemText(i, 0, strID);
		m_cList.SetItemText(i, 1, rs.m_PERSON);
		strSTime=rs.m_START_TIME.Format("%y-%m-%d %H:%M");
		m_cList.SetItemText(i, 2, strSTime);
		strETime=rs.m_END_TIME.Format("%y-%m-%d %H:%M");
		m_cList.SetItemText(i, 3, strETime);
		m_cList.SetItemText(i, 4, rs.m_DESCRIPTION);
		rs.MoveNext(); // 跳到下一条记录
		i++;
	}
	rs.Close(); // 关闭出差记录表
}

void CPage4::OnChangeEdtErrandPersonid() 
{
	UpdateData(); // 更新数据

	CPersonRS rs(&db); // 构造PERSON记录表
	rs.m_strFilter = "ID='" + m_strPersonID + "'"; // 设置过滤条件
	rs.Open(); // 打开记录表
	if(rs.GetRecordCount()==1) // 判断员工号是否正确
	{
		m_strPersonName=rs.m_NAME; // 提取员工姓名
	}
	else m_strPersonName.Empty(); // 清除员工姓名显示
	rs.Close(); // 关闭记录表
	UpdateData(FALSE); // 更新界面数据
}

void CPage4::OnBtnErrandAdd() 
{
	int counter; // 用于计数
	CCounterRS rs_counter(&db); // 构造计数器记录表

	UpdateData(); // 更新数据
// 记录编号
	rs_counter.m_strFilter = "ID='E'"; // 设置过滤器，提取计数值
	rs_counter.Open(); // 打开计数器记录表
	counter=rs_counter.m_COUNTER_VALUE; // 提取计数值
	counter++; // 计数值加1
	rs_counter.Edit(); // 编辑计数器
	rs_counter.m_COUNTER_VALUE=counter; // 保存当前计数
	rs_counter.Update(); // 提交修改
	rs_counter.Close(); // 关闭计数器记录表
// 添加记录
	int nYear,nMonth,nDay,nHour,nMinute; // 年,月,日,时,分
	// 转换起始时间类型
	sscanf(m_strSTime.Left(4), "%d", &nYear); // 得到年
	sscanf(m_strSTime.Mid(5,2), "%d", &nMonth); // 得到月
	sscanf(m_strSTime.Mid(8,2), "%d", &nDay); // 得到日
	sscanf(m_strSTime.Mid(11,2), "%d", &nHour); // 得到时
	sscanf(m_strSTime.Mid(14,2), "%d", &nMinute); // 得到分
	// 得到起始时间
	CTime S_time(nYear,nMonth,nDay,nHour,nMinute,0);
	// 转换结束时间类型
	sscanf(m_strETime.Left(4), "%d", &nYear); // 得到年
	sscanf(m_strETime.Mid(5,2), "%d", &nMonth); // 得到月
	sscanf(m_strETime.Mid(8,2), "%d", &nDay); // 得到日
	sscanf(m_strETime.Mid(11,2), "%d", &nHour); // 得到时
	sscanf(m_strETime.Mid(14,2), "%d", &nMinute); // 得到分
	// 得到结束时间
	CTime E_time(nYear,nMonth,nDay,nHour,nMinute,0);
	
	CErrandRS rs_errand(&db); // 构造出差记录表
	rs_errand.Open(); // 打开出差记录表
	rs_errand.AddNew(); // 追加出差记录
	rs_errand.m_ID=counter;
	rs_errand.m_PERSON=m_strPersonID;
	rs_errand.m_START_TIME=S_time;
	rs_errand.m_END_TIME=E_time;
	rs_errand.m_DESCRIPTION=m_strDescription;
	rs_errand.Update();
	rs_errand.Close(); // 关闭出差记录表
	UpdateList(rs_errand); // 更新列表框
}

void CPage4::OnBtnErrandDeleteattend() 
{
	CString strSQL;
	int nItem;
	// 得到第一个被选择Item的位置
	POSITION pos = m_cList.GetFirstSelectedItemPosition();
	if(pos==NULL)
	{
		AfxMessageBox("没有选择记录!");
		return;
	}
	while(pos) // 遍历所有被选Item
	{
		nItem=m_cList.GetNextSelectedItem(pos); // 得到Item Index
		// 构造SQL语句
		strSQL="delete from ERRAND where ID=" + m_cList.GetItemText(nItem, 0);
		db.ExecuteSQL(strSQL); // 执行
	}
	CErrandRS rs(&db); // 构造出差记录表
	UpdateList(rs); // 更新列表框
}

void CPage4::OnBtnErrandSeekio() 
{
	CErrandRS rs(&db); // 构造出差记录表

	CAttDlg *pDlg; // 指向包含本对象的CAttDlg的指针
	CString strFilter; // 用于保存过滤字符串
	CString strSTime,strETime; // 起始，结束时间

	pDlg=(CAttDlg*)GetParent()->GetParent(); // 得到指针
	pDlg->UpdateData(); // 更新数据

	strSTime=pDlg->m_StartTime.Format("%Y-%m-%d");
	strETime=pDlg->m_EndTime.Format("%Y-%m-%d");

	if(pDlg->m_bSeekbyperson) // 判断是否根据员工号检索
		strFilter="PERSON='" + pDlg->m_strPersonID + "'"; // 添加过滤条件
	if(pDlg->m_bSeekbytime) // 判断是否有时间范围
	{
		if(strFilter.GetLength()>0) // 判断是否已有过滤条件
			strFilter += " and "; //如果是，需要添加and连接符
		strFilter += "END_TIME>#" + strSTime + "#"; // 添加开始时间过滤
		strFilter += " and START_TIME<#" + strETime + "#"; // 添加结束时间过滤
	}
	if(strFilter.GetLength()>0) // 判断是否有过滤条件
		rs.m_strFilter=strFilter; // 设置Filter
	UpdateList(rs); // 更新列表框
}
