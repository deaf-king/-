// StatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Attendance.h"
#include "StatDlg.h"
#include "PersonRS.h"
#include "CounterRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDatabase db;
extern CTime StrToTime(CString str);
/////////////////////////////////////////////////////////////////////////////
// CStatDlg dialog


CStatDlg::CStatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatDlg::IDD, pParent)
{
	CTime End_t=CTime::GetCurrentTime(); // 当前时间
	CTimeSpan tp(30,0,0,0); // 时间间隔为30天
	//{{AFX_DATA_INIT(CStatDlg)
	m_strTime = End_t.Format("%Y-%m");
	m_STime = End_t-tp;
	m_ETime = End_t;
	m_bSeekbytime = FALSE;
	m_bSeekbyperson = FALSE;
	m_strSeektime = _T("");
	m_strPersonID = _T("");
	m_strPersonName = _T("");
	//}}AFX_DATA_INIT
}


void CStatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatDlg)
	DDX_Control(pDX, IDC_STAT_PROGRESS, m_cProgress);
	DDX_Control(pDX, IDC_STAT_LIST, m_cList);
	DDX_Text(pDX, IDC_STAT_EDT_TIME, m_strTime);
	DDX_DateTimeCtrl(pDX, IDC_STAT_DATETIMEPICKER_STARTTIME, m_STime);
	DDX_DateTimeCtrl(pDX, IDC_STAT_DATETIMEPICKER_ENDTIME, m_ETime);
	DDX_Check(pDX, IDC_STAT_CHK_SEEKBYTIME, m_bSeekbytime);
	DDX_Check(pDX, IDC_STAT_CHK_SEEKBYPERSON, m_bSeekbyperson);
	DDX_Text(pDX, IDC_STAT_EDT_SEEKTIME, m_strSeektime);
	DDX_Text(pDX, IDC_STAT_EDT_SEEKPERSONID, m_strPersonID);
	DDX_Text(pDX, IDC_STAT_EDT_SEEKPERSONNAME, m_strPersonName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatDlg, CDialog)
	//{{AFX_MSG_MAP(CStatDlg)
	ON_EN_CHANGE(IDC_STAT_EDT_SEEKPERSONID, OnChangeStatEdtSeekpersonid)
	ON_BN_CLICKED(IDC_STAT_BTN_SEEK, OnStatBtnSeek)
	ON_BN_CLICKED(IDC_STAT_BTN_STAT, OnStatBtnStat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatDlg message handlers

void CStatDlg::OnChangeStatEdtSeekpersonid() 
{
	UpdateData(); // 更新数据

	CPersonRS rs(&db); // 构造记录集
	rs.m_strFilter = "ID='" + m_strPersonID + "'"; // 设置过滤条件
	rs.Open(); // 打开记录集
	if(rs.GetRecordCount()==1) // 判断员工记录是否存在
	{
		m_strPersonName=rs.m_NAME; // 得到员工姓名
	}
	else m_strPersonName.Empty(); // 清除员工姓名的显示
	rs.Close(); // 关闭记录集
	UpdateData(FALSE); // 更新界面数据
}

void CStatDlg::OnStatBtnSeek() 
{
	CString strFilter; // 保存过滤字符串
	CStatRS rs(&db); // 构造统计数据表

	UpdateData(); // 更新数据
	// 判断根据员工号过滤
	if(m_bSeekbyperson) strFilter="PERSON='" + m_strPersonID + "'";
	// 判断根据年月过滤
	if(m_bSeekbytime)
	{
		if(!strFilter.IsEmpty())  // 如果已有过滤条件
			strFilter += " and "; // 需添加and连接符
		// 设置时间过滤条件
		strFilter += "YEAR_MONTH=#" + m_strSeektime + "#";
	}
	if(!strFilter.IsEmpty()) // 判断是否有过滤字符串
	{
		rs.m_strFilter=strFilter; // 设置过滤条件
	}
	UpdateList(rs); // 更新列表框
}

BOOL CStatDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// 为List添加网格
	m_cList.SetExtendedStyle(LVS_EX_GRIDLINES);
	// 设置List的列
	int nWidth=100;
	m_cList.InsertColumn(0, "记录编号", LVCFMT_LEFT, 80);
	m_cList.InsertColumn(1, "员工号", LVCFMT_LEFT, 50);
	m_cList.InsertColumn(2, "年月", LVCFMT_LEFT, nWidth);
	m_cList.InsertColumn(3, "正常工作时间(小时)", LVCFMT_LEFT, nWidth+40);
	m_cList.InsertColumn(4, "加班时间(小时)", LVCFMT_LEFT, nWidth);
	m_cList.InsertColumn(5, "请假时间(半天)", LVCFMT_LEFT, nWidth);
	m_cList.InsertColumn(6, "出差时间(半天)", LVCFMT_LEFT, nWidth);
	m_cList.InsertColumn(7, "迟到次数", LVCFMT_LEFT, nWidth-30);
	m_cList.InsertColumn(8, "早退次数", LVCFMT_LEFT, nWidth-30);
	m_cList.InsertColumn(9, "旷工次数", LVCFMT_LEFT, nWidth-30);
	CStatRS rs(&db); // 构造出勤记录表
	UpdateList(rs); // 更新List
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStatDlg::UpdateList(CStatRS& rs)
{
	int i=0;
	CString str;
	rs.Open(); // 打开统计数据表
	m_cList.DeleteAllItems(); // 清除列表框内容
	while(!rs.IsEOF()) // 对数据表中所有记录进行处理
	{
		m_cList.InsertItem(i, ""); // 添加新Item
		str.Format("%d", rs.m_ID); // 转换为字符串
		m_cList.SetItemText(i, 0, str);
		m_cList.SetItemText(i, 1, rs.m_PERSON);
		m_cList.SetItemText(i, 2, rs.m_YEAR_MONTH);
		str.Format("%d", rs.m_WORK_HOUR);
		m_cList.SetItemText(i, 3, str);
		str.Format("%d", rs.m_OVER_HOUR);
		m_cList.SetItemText(i, 4, str);
		str.Format("%d", rs.m_LEAVE_HDAY);
		m_cList.SetItemText(i, 5, str);
		str.Format("%d", rs.m_ERRAND_HDAY);
		m_cList.SetItemText(i, 6, str);
		str.Format("%d", rs.m_LATE_TIMES);
		m_cList.SetItemText(i, 7, str);
		str.Format("%d", rs.m_EARLY_TIMES);
		m_cList.SetItemText(i, 8, str);
		str.Format("%d", rs.m_ABSENT_TIMES);
		m_cList.SetItemText(i, 9, str);
		rs.MoveNext(); // 跳到下一条记录
		i++;
	}
	rs.Close(); // 关闭统计数据表
}

void CStatDlg::OnStatBtnStat() 
{
	CRecordset rs_Q_attend(&db); // 构造Q_attend记录集
	CRecordset rs_Q_leave(&db);  // 构造Q_leave记录集
	CRecordset rs_Q_errand(&db);  // 构造Q_errand记录集
	CTimeSpan tp_1(1,0,0,0); // 构造一个1天的CTimeSpan
	CTimeSpan tp_02(0,2,0,0); // 构造一个2小时的CTimeSpan
	CTimeSpan TimeSpan[4]; // 保存上下班时间
	int nHours[2]; // 保存上下午工作时间
	CString strSTime,strETime; // 保存始末时间
	CTime TimeStamp, LateTime, EarlyTime,WorkStart,WorkEnd; // 保存中间判断时间
	int nWorkHour,nOverHour,nLeaveHDay,nErrandHDay; // 保存时间间隔长度
	BOOL bLate,bEarly,bAbsent,bLeave,bErrand; // 保存判断结果
	int nLateTimes,nEarlyTimes,nAbsentTimes; // 保存次数
	CString cstr[4]; // 暂存起始时间
	char str[4][9]; // 暂存起始时间
	int i,j,n,counter; // 用于循环和计数
	CString strTmp,strTmp1,strTmp2; // 临时变量
	// 临时变量,年,月,日,时,分,秒
	int nHour,nMinute,nSecond;
	CString strFileName=".\\workplan.ini"; // INI文件名

	UpdateData(); // 更新数据
	// 读取INI文件
	GetPrivateProfileString("WorkPlan", "Time1", "08:00:00", str[0], 9, strFileName);
	GetPrivateProfileString("WorkPlan", "Time2", "12:00:00", str[1], 9, strFileName);
	GetPrivateProfileString("WorkPlan", "Time3", "14:00:00", str[2], 9, strFileName);
	GetPrivateProfileString("WorkPlan", "Time4", "18:00:00", str[3], 9, strFileName);
	for(i=0; i<4; i++) cstr[i]=str[i];

	// 定义四个时间间隔变量并初始化为INI文件中的值
	CTimeSpan *pTS;
	for(i=0; i<4; i++)
	{
		sscanf(cstr[i].Left(2), "%d", &nHour);		// 得到时
		sscanf(cstr[i].Mid(3,2), "%d", &nMinute);	// 得到分
		sscanf(cstr[i].Mid(6,2), "%d", &nSecond);	// 得到秒
		// 构造一个时间间隔变量
		pTS=new CTimeSpan(0,nHour,nMinute,nSecond);
		TimeSpan[i]=*pTS; // 赋值
		delete pTS;
	}
	nHours[0]=(TimeSpan[1]-TimeSpan[0]).GetTotalHours(); // 计算上午工作时间
	if((TimeSpan[1]-TimeSpan[0]).GetMinutes()>30) nHours[0]++; // 四舍五入
	nHours[1]=(TimeSpan[3]-TimeSpan[2]).GetTotalHours(); // 计算下午工作时间
	if((TimeSpan[3]-TimeSpan[2]).GetMinutes()>30) nHours[1]++; // 四舍五入
	// 转换统计开始时间
	strSTime="#"+m_STime.Format("%Y-%m-%d")+"#";
	// 转换统计结束时间，且天数加1
	strETime="#"+(m_ETime+tp_1).Format("%Y-%m-%d")+"#";
	// 提取员工列表
	CPersonRS rs_person(&db); // 构造员工表
	rs_person.m_strFilter="STATE='T'"; // 设置过滤器，提取员工列表
	rs_person.Open(); // 打开员工表
	n=rs_person.GetRecordCount(); // 记录员工人数
	i=0; // 初始化已处理员工人数
	m_cProgress.SetRange(0,n); // 设置进度条
	m_cProgress.SetPos(0); // 初始化进度条
	while(!rs_person.IsEOF()) // 依次对每个员工进行统计
	{
		//获取出勤记录
		// 执行查询
		rs_Q_attend.Open(CRecordset::forwardOnly,
			"select IN_OUT,IO_TIME from ATTENDANCE\
			where PERSON='" + rs_person.m_ID
			+ "' and IO_TIME>" + strSTime
			+ " and IO_TIME<" +strETime
			+ " order by IO_TIME");
		strTmp1.Empty(); // 清空strTmp1
		// 初始化
		nWorkHour=nOverHour=0;
		nLeaveHDay=nErrandHDay=0;
		nLateTimes=nEarlyTimes=nAbsentTimes=0;
		TimeStamp=m_STime; // 初始化时间戳为统计开始时间
		while(TimeStamp < m_ETime+tp_02) // 判断是否超出统计结束时间
		{
			if(TimeStamp.GetDayOfWeek()!=1 &&
			   TimeStamp.GetDayOfWeek()!=7) // 判断是否工作日
			{
				for(j=0;j<=1;j++) // 遍历班次
				{
					LateTime=TimeStamp+TimeSpan[2*j]; // 设置迟到时间
					EarlyTime=TimeStamp+TimeSpan[2*j+1]; // 设置早退时间
					// 判断是否请假
					rs_Q_leave.Open(CRecordset::forwardOnly,
						"select ID from LEAVE where\
						PERSON='" + rs_person.m_ID
						+ "' and START_TIME<#"
						+ LateTime.Format("%Y-%m-%d %H:%M:%S")
						+ "# and END_TIME>#"
						+ EarlyTime.Format("%Y-%m-%d %H:%M:%S")
						+ "#");
					bLeave=(rs_Q_leave.GetRecordCount()>0);	// 判断是否有请假记录
					rs_Q_leave.Close(); // 关闭记录集
					// 判断是否出差
					rs_Q_errand.Open(CRecordset::forwardOnly,
						"select ID from ERRAND where\
						PERSON='" + rs_person.m_ID
						+ "' and START_TIME<#"
						+ LateTime.Format("%Y-%m-%d %H:%M:%S")
						+ "# and END_TIME>#"
						+ EarlyTime.Format("%Y-%m-%d %H:%M:%S")
						+ "#");
					bErrand=(rs_Q_errand.GetRecordCount()>0); // 判断是否有出差记录
					rs_Q_errand.Close(); // 关闭记录集
					if(bLeave) // 如果有请假记录
						nLeaveHDay++; // 请假记录加1
					else if(bErrand) // 如果有出差记录
					{
						nErrandHDay++; // 出差计数加1
						nWorkHour+=nHours[j]; // 按正常班累加工作时间
					}
					else // 正常上班
					{
						WorkStart=LateTime; // 设置工作开始时间
						WorkEnd=EarlyTime; // 设置工作结束时间
						bLate=TRUE; // 初始化迟到判断
						bAbsent=FALSE; // 初始化旷工判断
						// 判断是否迟到
						if(!rs_Q_attend.IsEOF() && // 记录集不空
							strTmp1.IsEmpty()) // 空,第一次GetFieldValue
							rs_Q_attend.GetFieldValue("IO_TIME",strTmp1); // 得到IO_TIME
						while(!rs_Q_attend.IsEOF()
							&& StrToTime(strTmp1)<=LateTime)
						{// 根据时间顺序判断是否迟到
							// 得到IN_OUT
							rs_Q_attend.GetFieldValue("IN_OUT",strTmp2);
							bLate=(strTmp2=="O"); // 判断上班时间前是否报到
							rs_Q_attend.MoveNext(); // 跳到下一条出勤记录
							// 得到IO_TIME
							if(!rs_Q_attend.IsEOF())
								rs_Q_attend.GetFieldValue("IO_TIME",strTmp1);
						}
						// 判断是否旷工
						if(bLate) // 判断是否迟到
						{
							if(!rs_Q_attend.IsEOF() && StrToTime(strTmp1)<EarlyTime)
								WorkStart=StrToTime(strTmp1); // 记录迟到时间
							else bAbsent=TRUE; // 如果下班前仍未报到记为旷工
						}
						bEarly=FALSE;
						// 判断是否早退
						while(!rs_Q_attend.IsEOF() && StrToTime(strTmp1)<EarlyTime)
						{
							// 得到IN_OUT
							rs_Q_attend.GetFieldValue("IN_OUT",strTmp2);
							bEarly=(strTmp2=="O"); // 判断是否有早退
							if(bEarly)
							{
								// 将早退时间记录为工作结束时间
								WorkEnd=StrToTime(strTmp1);
							}
							else WorkEnd=EarlyTime; // 将下班时间记录为工作结束时间
							rs_Q_attend.MoveNext(); // 跳至下一条出勤记录
							// 得到IO_TIME
							if(!rs_Q_attend.IsEOF())
								rs_Q_attend.GetFieldValue("IO_TIME",strTmp1);
						}
						// 如果旷工，增加旷工次数记录
						if(bAbsent) nAbsentTimes++;
						else
						{
							// 如果迟到，增加迟到次数记录
							if(bLate) nLateTimes++;
							// 如果早退，增加早退次数记录
							if(bEarly) nEarlyTimes++;
							// 计算实际工作时间
							nWorkHour+=(WorkEnd-WorkStart).GetTotalHours();
							if((WorkEnd-WorkStart).GetMinutes()>30)
								nWorkHour++; // 四舍五入
						}
					}
				} // End of 遍历班次
			} // End of 是否工作日
			TimeStamp+=tp_1; // 推进一天
		} // End of TimeStamp < m_ETime+tp_02
		rs_Q_attend.Close(); // 关闭Q_attend记录集
		// 统计加班时间
		CRecordset rs_Q_overtime(&db); // 构造Q_overtime记录集
		rs_Q_overtime.Open(CRecordset::forwardOnly,
			"select sum(WORK_HOURS) as SUM from OVERTIME\
			where PERSON='" + rs_person.m_ID
			+ "' and WORK_DATE>#"
			+ m_STime.Format("%Y-%m-%d %H:%M:%S")
			+ "# and WORK_DATE<#"
			+ m_ETime.Format("%Y-%m-%d %H:%M:%S")
			+ "#");
		if(rs_Q_overtime.GetRecordCount()>0) // 有记录
		{
			// 提取加班时间
			rs_Q_overtime.GetFieldValue("SUM",strTmp);
			sscanf(strTmp,"%d",&nOverHour);
		}
		else nOverHour=0; // 无记录
		rs_Q_overtime.Close();
		// 判断是否已有该月考勤记录
		CStatRS rs_stat(&db); // 构造统计数据表
		// 设置过滤串
		rs_stat.m_strFilter="PERSON='" + rs_person.m_ID
			+ "' and YEAR_MONTH='" + m_strTime + "'";
		rs_stat.Open(); // 打开数据表
		if(rs_stat.GetRecordCount()==0) // 判断是否有该月份考勤记录
		{
			// 获取计数
			CCounterRS rs_counter(&db); // 构造计数器表
			rs_counter.m_strFilter = "ID='S'"; // 设置过滤器，提取计数值
			rs_counter.Open(); // 打开计数器记录表
			counter=rs_counter.m_COUNTER_VALUE; // 提取计数值
			counter++; // 计数值加1
			rs_counter.Edit(); // 编辑计数器
			rs_counter.m_COUNTER_VALUE=counter; // 保存当前计数
			rs_counter.Update(); // 提交修改
			rs_counter.Close(); // 关闭计数器记录表
			// 追加统计记录
			rs_stat.AddNew();
			rs_stat.m_ID=counter;
			rs_stat.m_YEAR_MONTH=m_strTime;
			rs_stat.m_PERSON=rs_person.m_ID;
			rs_stat.m_WORK_HOUR=nWorkHour;
			rs_stat.m_OVER_HOUR=nOverHour;
			rs_stat.m_LEAVE_HDAY=nLeaveHDay;
			rs_stat.m_ERRAND_HDAY=nErrandHDay;
			rs_stat.m_LATE_TIMES=nLateTimes;
			rs_stat.m_EARLY_TIMES=nEarlyTimes;
			rs_stat.m_ABSENT_TIMES=nAbsentTimes;
			rs_stat.Update(); // 提交修改
		}
		else
		{
			// 记录已存在修改数据
			rs_stat.Edit();
			rs_stat.m_WORK_HOUR=nWorkHour;
			rs_stat.m_OVER_HOUR=nOverHour;
			rs_stat.m_LEAVE_HDAY=nLeaveHDay;
			rs_stat.m_ERRAND_HDAY=nErrandHDay;
			rs_stat.m_LATE_TIMES=nLateTimes;
			rs_stat.m_EARLY_TIMES=nEarlyTimes;
			rs_stat.m_ABSENT_TIMES=nAbsentTimes;
			rs_stat.Update(); // 提交修改
		}
		rs_stat.Close(); // 关闭数据表
		i++; // 已统计员工数加1
		m_cProgress.SetPos(i); // 显示统计进度
		rs_person.MoveNext(); // 跳到下一个员工记录
	}
	rs_person.Close(); // 关闭员工表
	CStatRS rs_stat(&db); // 构造统计数据表
	UpdateList(rs_stat); // 更新列表框
}
