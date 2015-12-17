// Page3.cpp : implementation file
//

#include "stdafx.h"
#include "Attendance.h"
#include "Page3.h"
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
// CPage3 property page

IMPLEMENT_DYNCREATE(CPage3, CPropertyPage)

CPage3::CPage3() : CPropertyPage(CPage3::IDD)
{
	// �õ���ǰʱ�䲢��ʽ��
	CTime t=CTime::GetCurrentTime();
	CString str=t.Format("%Y-%m-%d %H:%M");
	//{{AFX_DATA_INIT(CPage3)
	m_strSTime = str;
	m_strETime = str;
	m_strReason = _T("");
	m_strPersonID = _T("");
	m_strPersonName = _T("");
	//}}AFX_DATA_INIT
}

CPage3::~CPage3()
{
}

void CPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage3)
	DDX_Control(pDX, IDC_LIST3, m_cList);
	DDX_Text(pDX, IDC_EDT_LEAVE_STARTTIME, m_strSTime);
	DDX_Text(pDX, IDC_EDT_LEAVE_ENDTIME, m_strETime);
	DDX_Text(pDX, IDC_EDT_LEAVE_REASON, m_strReason);
	DDX_Text(pDX, IDC_EDT_LEAVE_PERSONID, m_strPersonID);
	DDX_Text(pDX, IDC_EDT_LEAVE_PERSONNAME, m_strPersonName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage3, CPropertyPage)
	//{{AFX_MSG_MAP(CPage3)
	ON_EN_CHANGE(IDC_EDT_LEAVE_PERSONID, OnChangeEdtLeavePersonid)
	ON_BN_CLICKED(IDC_BTN_LEAVE_ADD, OnBtnLeaveAdd)
	ON_BN_CLICKED(IDC_BTN_LEAVE_DELETEATTEND, OnBtnLeaveDeleteattend)
	ON_BN_CLICKED(IDC_BTN_LEAVE_SEEKIO, OnBtnLeaveSeekio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage3 message handlers

void CPage3::OnChangeEdtLeavePersonid() 
{
	UpdateData(); // ��������

	CPersonRS rs(&db); // ����PERSON��¼��
	rs.m_strFilter = "ID='" + m_strPersonID + "'"; // ���ù�������
	rs.Open(); // �򿪼�¼��
	if(rs.GetRecordCount()==1) // �ж�Ա�����Ƿ���ȷ
	{
		m_strPersonName=rs.m_NAME; // ��ȡԱ������
	}
	else m_strPersonName.Empty(); // ���Ա��������ʾ
	rs.Close(); // �رռ�¼��
	UpdateData(FALSE); // ���½�������
}

BOOL CPage3::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// ΪList�������
	m_cList.SetExtendedStyle(LVS_EX_GRIDLINES);
	// ����List����
	int nWidth=90;
	m_cList.InsertColumn(0, "��¼���", LVCFMT_LEFT, nWidth-20);
	m_cList.InsertColumn(1, "Ա����", LVCFMT_LEFT, nWidth-20);
	m_cList.InsertColumn(2, "��ʼʱ��", LVCFMT_LEFT, nWidth+20);
	m_cList.InsertColumn(3, "����ʱ��", LVCFMT_LEFT, nWidth+20);
	m_cList.InsertColumn(4, "Ե��", LVCFMT_LEFT, nWidth);
	CLeaveRS rs(&db); // ������ټ�¼��
	UpdateList(rs); // ����List	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage3::UpdateList(CLeaveRS &rs)
{
	int i=0;
	CString strID,strSTime,strETime;
	rs.Open(); // �򿪼Ӱ��¼��
	m_cList.DeleteAllItems(); // ����б������
	while(!rs.IsEOF()) // �����ݱ������м�¼���д���
	{
		m_cList.InsertItem(i, ""); // �����Item
		strID.Format("%d", rs.m_ID); // ת��Ϊ�ַ���
		m_cList.SetItemText(i, 0, strID);
		m_cList.SetItemText(i, 1, rs.m_PERSON);
		strSTime=rs.m_START_TIME.Format("%y-%m-%d %H:%M");
		m_cList.SetItemText(i, 2, strSTime);
		strETime=rs.m_END_TIME.Format("%y-%m-%d %H:%M");
		m_cList.SetItemText(i, 3, strETime);
		m_cList.SetItemText(i, 4, rs.m_REASON);
		rs.MoveNext(); // ������һ����¼
		i++;
	}
	rs.Close(); // �رռ�¼��
}

void CPage3::OnBtnLeaveAdd() 
{
	int counter; // ���ڼ���
	CCounterRS rs_counter(&db); // �����������¼��

	UpdateData(); // ��������
// ��¼���
	rs_counter.m_strFilter = "ID='L'"; // ���ù���������ȡ����ֵ
	rs_counter.Open(); // �򿪼�������¼��
	counter=rs_counter.m_COUNTER_VALUE; // ��ȡ����ֵ
	counter++; // ����ֵ��1
	rs_counter.Edit(); // �༭������
	rs_counter.m_COUNTER_VALUE=counter; // ���浱ǰ����
	rs_counter.Update(); // �ύ�޸�
	rs_counter.Close(); // �رռ�������¼��
// ��Ӽ�¼
	int nYear,nMonth,nDay,nHour,nMinute; // ��,��,��,ʱ,��
	// ת����ʼʱ������
	sscanf(m_strSTime.Left(4), "%d", &nYear); // �õ���
	sscanf(m_strSTime.Mid(5,2), "%d", &nMonth); // �õ���
	sscanf(m_strSTime.Mid(8,2), "%d", &nDay); // �õ���
	sscanf(m_strSTime.Mid(11,2), "%d", &nHour); // �õ�ʱ
	sscanf(m_strSTime.Mid(14,2), "%d", &nMinute); // �õ���
	// �õ���ʼʱ��
	CTime S_time(nYear,nMonth,nDay,nHour,nMinute,0);
	// ת������ʱ������
	sscanf(m_strETime.Left(4), "%d", &nYear); // �õ���
	sscanf(m_strETime.Mid(5,2), "%d", &nMonth); // �õ���
	sscanf(m_strETime.Mid(8,2), "%d", &nDay); // �õ���
	sscanf(m_strETime.Mid(11,2), "%d", &nHour); // �õ�ʱ
	sscanf(m_strETime.Mid(14,2), "%d", &nMinute); // �õ���
	// �õ�����ʱ��
	CTime E_time(nYear,nMonth,nDay,nHour,nMinute,0);
	
	CLeaveRS rs_leave(&db); // ������ټ�¼��
	rs_leave.Open(); // ����ټ�¼��
	rs_leave.AddNew(); // ׷����ټ�¼
	rs_leave.m_ID=counter;
	rs_leave.m_PERSON=m_strPersonID;
	rs_leave.m_START_TIME=S_time;
	rs_leave.m_END_TIME=E_time;
	rs_leave.m_REASON=m_strReason;
	rs_leave.Update();
	rs_leave.Close(); // �ر���ټ�¼��
	UpdateList(rs_leave); // �����б��
}

void CPage3::OnBtnLeaveDeleteattend() 
{
	CString strSQL;
	int nItem;
	// �õ���һ����ѡ��Item��λ��
	POSITION pos = m_cList.GetFirstSelectedItemPosition();
	if(pos==NULL)
	{
		AfxMessageBox("û��ѡ���¼!");
		return;
	}
	while(pos) // �������б�ѡItem
	{
		nItem=m_cList.GetNextSelectedItem(pos); // �õ�Item Index
		// ����SQL���
		strSQL="delete from LEAVE where ID=" + m_cList.GetItemText(nItem, 0);
		db.ExecuteSQL(strSQL); // ִ��
	}
	CLeaveRS rs(&db); // ������ټ�¼��
	UpdateList(rs); // �����б��
}

void CPage3::OnBtnLeaveSeekio() 
{
	CLeaveRS rs(&db); // ������ټ�¼��

	CAttDlg *pDlg; // ָ������������CAttDlg��ָ��
	CString strFilter; // ���ڱ�������ַ���
	CString strSTime,strETime; // ��ʼ������ʱ��

	pDlg=(CAttDlg*)GetParent()->GetParent(); // �õ�ָ��
	pDlg->UpdateData(); // ��������

	strSTime=pDlg->m_StartTime.Format("%Y-%m-%d");
	strETime=pDlg->m_EndTime.Format("%Y-%m-%d");

	if(pDlg->m_bSeekbyperson) // �ж��Ƿ����Ա���ż���
		strFilter="PERSON='" + pDlg->m_strPersonID + "'"; // ��ӹ�������
	if(pDlg->m_bSeekbytime) // �ж��Ƿ���ʱ�䷶Χ
	{
		if(strFilter.GetLength()>0) // �ж��Ƿ����й�������
			strFilter += " and "; //����ǣ���Ҫ���and���ӷ�
		strFilter += "END_TIME>#" + strSTime + "#"; // ��ӿ�ʼʱ�����
		strFilter += " and START_TIME<#" + strETime + "#"; // ��ӽ���ʱ�����
	}
	if(strFilter.GetLength()>0) // �ж��Ƿ��й�������
		rs.m_strFilter=strFilter; // ����Filter
	UpdateList(rs); // �����б��
}
