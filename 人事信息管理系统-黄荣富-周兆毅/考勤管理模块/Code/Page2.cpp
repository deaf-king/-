// Page2.cpp : implementation file
//

#include "stdafx.h"
#include "Attendance.h"
#include "Page2.h"
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
// CPage2 property page

IMPLEMENT_DYNCREATE(CPage2, CPropertyPage)

CPage2::CPage2() : CPropertyPage(CPage2::IDD)
{
	//{{AFX_DATA_INIT(CPage2)
	m_nHour = 0;
	m_strPersonID = _T("");
	m_strPersonName = _T("");
	m_Date = CTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage2)
	DDX_Control(pDX, IDC_LIST2, m_cList);
	DDX_Text(pDX, IDC_EDT_OVERTIME_HOUR, m_nHour);
	DDX_Text(pDX, IDC_EDT_OVERTIME_PERSONID, m_strPersonID);
	DDX_Text(pDX, IDC_EDT_OVERTIME_PERSONNAME, m_strPersonName);
	DDX_DateTimeCtrl(pDX, IDC_OVERTIME_DATETIMEPICKER, m_Date);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CPage2)
	ON_EN_CHANGE(IDC_EDT_OVERTIME_PERSONID, OnChangeEdtOvertimePersonid)
	ON_BN_CLICKED(IDC_BTN_OVERTIME_ADD, OnBtnOvertimeAdd)
	ON_BN_CLICKED(IDC_BTN_OVERTIME_DELETEATTEND, OnBtnOvertimeDeleteattend)
	ON_BN_CLICKED(IDC_BTN_OVERTIME_SEEKIO, OnBtnOvertimeSeekio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage2 message handlers

void CPage2::OnChangeEdtOvertimePersonid() 
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

void CPage2::OnBtnOvertimeAdd() 
{
	int counter; // 用于保存计数
	CCounterRS rs_counter(&db); // 构造计数器记录表

	UpdateData(); // 更新数据
	if(m_strPersonName.IsEmpty()) return; // 判断员工号是否正确
// 记录编号
	rs_counter.m_strFilter = "ID='O'"; // 设置过滤器，提取计数值
	rs_counter.Open(); // 打开计数器记录表
	counter=rs_counter.m_COUNTER_VALUE; // 提取计数值
	counter++; // 计数值加1
	rs_counter.Edit(); // 编辑计数器
	rs_counter.m_COUNTER_VALUE=counter; // 保存当前计数
	rs_counter.Update(); // 提交修改
	rs_counter.Close(); // 关闭计数器记录表
// 添加记录
	COvertimeRS rs_overtime(&db); // 构造加班记录表
	rs_overtime.Open(); // 打开表
	rs_overtime.AddNew(); // 新增一项记录
	// 设置字段值
	rs_overtime.m_ID=counter;
	rs_overtime.m_PERSON=m_strPersonID;
	rs_overtime.m_WORK_HOURS=m_nHour;
	rs_overtime.m_WORK_DATE=m_Date;
	rs_overtime.Update(); // 更新数据库
	rs_overtime.Close(); // 关闭加班记录表
	UpdateList(rs_overtime); // 更新列表框
}

BOOL CPage2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// 为List添加网格
	m_cList.SetExtendedStyle(LVS_EX_GRIDLINES);
	// 设置List的列
	int nWidth=110;
	m_cList.InsertColumn(0, "记录编号", LVCFMT_LEFT, nWidth);
	m_cList.InsertColumn(1, "员工号", LVCFMT_LEFT, nWidth);
	m_cList.InsertColumn(2, "加班时间", LVCFMT_LEFT, nWidth);
	m_cList.InsertColumn(3, "加班日期", LVCFMT_LEFT, nWidth);
	COvertimeRS rs(&db); // 构造加班记录表
	UpdateList(rs); // 更新List	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage2::UpdateList(COvertimeRS &rs)
{
	int i=0;
	CString strID,strWorkHours,strTime;
	rs.Open(); // 打开加班记录表
	m_cList.DeleteAllItems(); // 清除列表框内容
	while(!rs.IsEOF()) // 对数据表中所有记录进行处理
	{
		m_cList.InsertItem(i, ""); // 添加新Item
		strID.Format("%d", rs.m_ID); // 转换为字符串
		m_cList.SetItemText(i, 0, strID);
		m_cList.SetItemText(i, 1, rs.m_PERSON);
		strWorkHours.Format("%d",rs.m_WORK_HOURS);
		m_cList.SetItemText(i, 2, strWorkHours);
		m_cList.SetItemText(i, 3, rs.m_WORK_DATE.Format("%Y-%m-%d"));
		rs.MoveNext(); // 跳到下一条记录
		i++;
	}
	rs.Close(); // 关闭加班记录表
}

void CPage2::OnBtnOvertimeDeleteattend() 
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
		strSQL="delete from OVERTIME where ID=" + m_cList.GetItemText(nItem, 0);
		db.ExecuteSQL(strSQL); // 执行
	}
	COvertimeRS rs(&db); // 构造加班记录表
	UpdateList(rs); // 更新列表框
}

void CPage2::OnBtnOvertimeSeekio() 
{
	COvertimeRS rs(&db); // 构造加班记录表

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
		strFilter += "WORK_DATE>#" + strSTime + "#"; // 添加开始时间过滤
		strFilter += " and WORK_DATE<#" + strETime + "#"; // 添加结束时间过滤
	}
	if(strFilter.GetLength()>0) // 判断是否有过滤条件
		rs.m_strFilter=strFilter; // 设置Filter
	UpdateList(rs); // 更新列表框
}
