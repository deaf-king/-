// Page1.cpp : implementation file
//

#include "stdafx.h"
#include "Attendance.h"
#include "Page1.h"
#include "DepartRS.h"
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
// CPage1 property page

IMPLEMENT_DYNCREATE(CPage1, CPropertyPage)

CPage1::CPage1() : CPropertyPage(CPage1::IDD)
{
	// 得到当前时间并格式化
	CTime t=CTime::GetCurrentTime();
	CString str=t.Format("%Y-%m-%d %H:%M");
	//{{AFX_DATA_INIT(CPage1)
	m_strIOTime = str;
	m_strDepartID = _T("");
	m_strDepartName = _T("");
	m_strPersonID = _T("");
	m_strPersonName = _T("");
	//}}AFX_DATA_INIT
}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage1)
	DDX_Control(pDX, IDC_LIST1, m_cList);
	DDX_Control(pDX, IDC_PROGRESS1, m_cProgress);
	DDX_Text(pDX, IDC_EDT_IOTIME, m_strIOTime);
	DDX_Text(pDX, IDC_EDT_DEPARTID, m_strDepartID);
	DDX_Text(pDX, IDC_EDT_DEPARTNAME, m_strDepartName);
	DDX_Text(pDX, IDC_EDT_PERSONID, m_strPersonID);
	DDX_Text(pDX, IDC_EDT_PERSONNAME, m_strPersonName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CPage1)
	ON_EN_CHANGE(IDC_EDT_DEPARTID, OnChangeEdtDepartid)
	ON_EN_CHANGE(IDC_EDT_PERSONID, OnChangeEdtPersonid)
	ON_BN_CLICKED(IDC_BTN_ADDPERSON, OnBtnAddperson)
	ON_BN_CLICKED(IDC_BTN_ADDDEPART, OnBtnAdddepart)
	ON_BN_CLICKED(IDC_BTN_ADDALL, OnBtnAddall)
	ON_BN_CLICKED(IDC_BTN_DELETEATTEND, OnBtnDeleteattend)
	ON_BN_CLICKED(IDC_BTN_SEEKIO, OnBtnSeekio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage1 message handlers

BOOL CPage1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// 出入情况缺省为出
	((CButton*)GetDlgItem(IDC_RADIO_OUT))->SetCheck(TRUE);
	// 为List添加网格
	m_cList.SetExtendedStyle(LVS_EX_GRIDLINES);
	// 设置List的列
	int nWidth=110;
	m_cList.InsertColumn(0, "记录编号", LVCFMT_LEFT, nWidth);
	m_cList.InsertColumn(1, "员工号", LVCFMT_LEFT, nWidth);
	m_cList.InsertColumn(2, "出入情况", LVCFMT_LEFT, nWidth);
	m_cList.InsertColumn(3, "时间", LVCFMT_LEFT, nWidth);
	CAttendanceRS rs(&db); // 构造出勤记录表
	UpdateList(rs); // 更新List
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage1::OnChangeEdtDepartid() 
{
	UpdateData(); // 更新数据

	CDepartRS rs(&db); // 构造记录集
	rs.m_strFilter = "ID='" + m_strDepartID + "'"; // 设置过滤条件
	rs.Open(); // 打开记录集
	if(rs.GetRecordCount()==1) // 判断部门代码输入是否正确
	{
		m_strDepartName=rs.m_NAME; // 提取部门名称
	}
	else m_strDepartName.Empty(); // 清除部门名称
	rs.Close(); // 关闭记录集
	UpdateData(FALSE); // 更新界面数据
}

void CPage1::OnChangeEdtPersonid() 
{
	UpdateData(); // 更新数据

	CPersonRS rs(&db); // 构造PERSON记录表
	rs.m_strFilter = "ID='" + m_strPersonID + "'"; // 设置过滤条件
	rs.Open(); // 打开记录表
	if(rs.GetRecordCount()==1) // 判断员工号是否正确
	{
		m_strPersonName=rs.m_NAME; // 提取员工姓名
		m_strDepartID=rs.m_DEPARTMENT; // 提取员工所在部门编号
	}
	else m_strPersonName.Empty(); // 清除员工姓名显示
	rs.Close(); // 关闭记录表
	UpdateData(FALSE); // 更新界面数据
	OnChangeEdtDepartid(); // 显示部门名称
}

// 添加出勤记录函数
void CPage1::IO_Add(CString strPersonID)
{
	int counter; // 用于计数
	CString strIO; // 保存出入情况
	CCounterRS rs_counter(&db); // 构造计数器记录表
// 记录编号
	rs_counter.m_strFilter = "ID='A'"; // 设置过滤器，提取计数值
	rs_counter.Open(); // 打开计数器记录表
	counter=rs_counter.m_COUNTER_VALUE; // 提取计数值
	counter++; // 计数值加1
	rs_counter.Edit(); // 编辑计数器
	rs_counter.m_COUNTER_VALUE=counter; // 保存当前计数
	rs_counter.Update(); // 提交修改
	rs_counter.Close(); // 关闭计数器记录表
// 添加记录
	// 判断确定出入情况
	if(((CButton*)GetDlgItem(IDC_RADIO_OUT))->GetCheck())
		strIO="O";
	else strIO="I";
	// 转换出入时间类型
	int nYear,nMonth,nDay,nHour,nMinute; // 年,月,日,时,分
	sscanf(m_strIOTime.Left(4), "%d", &nYear); // 得到年
	sscanf(m_strIOTime.Mid(5,2), "%d", &nMonth); // 得到月
	sscanf(m_strIOTime.Mid(8,2), "%d", &nDay); // 得到日
	sscanf(m_strIOTime.Mid(11,2), "%d", &nHour); // 得到时
	sscanf(m_strIOTime.Mid(14,2), "%d", &nMinute); // 得到分
	// 得到出入时间
	CTime IO_time(nYear,nMonth,nDay,nHour,nMinute,0);
	CAttendanceRS rs_attendance(&db); // 构造考勤记录表
	rs_attendance.Open(); // 打开考勤记录表
	rs_attendance.AddNew(); // 追加考勤记录
	rs_attendance.m_ID=counter;
	rs_attendance.m_PERSON=strPersonID;
	rs_attendance.m_IN_OUT=strIO;
	rs_attendance.m_IO_TIME=IO_time;
	rs_attendance.Update();
	rs_attendance.Close(); // 关闭考勤记录表
	UpdateList(rs_attendance); // 更新列表框
}

void CPage1::OnBtnAddperson() // 追加单个员工考勤记录
{
	if(!m_strPersonName.IsEmpty()) // 判断员工是否存在
	{
		IO_Add(m_strPersonID); // 追加单个员工记录
	}
}

void CPage1::OnBtnAdddepart() // 追加部门员工考勤记录
{
	int i,n; // 用于保存记录条数
	CPersonRS rs_person(&db); // 构造员工信息表

	if(m_strDepartName.IsEmpty()) return; // 判断部门代号是否正确
	// 设置过滤条件
	rs_person.m_strFilter="DEPARTMENT='"+m_strDepartID+"' and STATE='T'";
	rs_person.Open(); // 打开员工信息表
	n=rs_person.GetRecordCount(); // 获取员工人数
	i=0; // 初始化已添加记录条数
	// 初始化进度条
	m_cProgress.SetRange(0, n);
	m_cProgress.SetPos(0);
	while(!rs_person.IsEOF()) // 对数据表中所有记录进行处理
	{
		IO_Add(rs_person.m_ID); // 添加当前员工出勤记录
		rs_person.MoveNext(); // 跳到下一个员工记录
		m_cProgress.SetPos(++i); // 显示进度
	}
	rs_person.Close(); // 关闭员工信息表
}

void CPage1::OnBtnAddall() // 添加所有员工出勤记录
{
	int i,n; // 用于保存记录条数
	CPersonRS rs_person(&db); // 构造员工信息表

	// 设置过滤条件,提取员工列表
	rs_person.m_strFilter = "STATE='T'";
	rs_person.Open(); // 打开员工信息表
	n=rs_person.GetRecordCount(); // 获取员工人数
	i=0; // 初始化已添加记录条数
	// 初始化进度条
	m_cProgress.SetRange(0, n);
	m_cProgress.SetPos(0);
	while(!rs_person.IsEOF()) // 对数据表中所有记录进行处理
	{
		IO_Add(rs_person.m_ID); // 添加当前员工出勤记录
		rs_person.MoveNext(); // 跳到下一个员工记录
		m_cProgress.SetPos(++i); // 显示进度
	}
	rs_person.Close(); // 关闭员工信息表
}

void CPage1::UpdateList(CAttendanceRS& rs) // 更新列表框内容
{
	int i=0;
	CString strID,strTime;
	rs.Open(); // 打开出勤记录表
	m_cList.DeleteAllItems(); // 清除列表框内容
	while(!rs.IsEOF()) // 对数据表中所有记录进行处理
	{
		m_cList.InsertItem(i, ""); // 添加新Item
		strID.Format("%d", rs.m_ID); // 转换为字符串
		m_cList.SetItemText(i, 0, strID);
		m_cList.SetItemText(i, 1, rs.m_PERSON);
		m_cList.SetItemText(i, 2, rs.m_IN_OUT);
		m_cList.SetItemText(i, 3, rs.m_IO_TIME.Format("%Y-%m-%d %H:%M"));
		rs.MoveNext(); // 跳到下一条记录
		i++;
	}
	rs.Close(); // 关闭出勤记录表
}

void CPage1::OnBtnDeleteattend() // 删除出勤记录列表中所选记录
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
		strSQL="delete from ATTENDANCE where ID="
			+ m_cList.GetItemText(nItem, 0);
		db.ExecuteSQL(strSQL); // 执行
	}
	CAttendanceRS rs(&db); // 构造出勤记录表
	UpdateList(rs); // 更新列表框
}

void CPage1::OnBtnSeekio() 
{
	CAttendanceRS rs(&db); // 构造出勤记录表

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
		strFilter += "IO_TIME>#" + strSTime + "#"; // 添加开始时间过滤
		strFilter += " and IO_TIME<#" + strETime + "#"; // 添加结束时间过滤
	}
	if(strFilter.GetLength()>0) // 判断是否有过滤条件
		rs.m_strFilter=strFilter; // 设置Filter
	UpdateList(rs); // 更新列表框
}
