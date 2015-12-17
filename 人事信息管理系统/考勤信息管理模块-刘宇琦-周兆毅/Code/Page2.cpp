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

void CPage2::OnBtnOvertimeAdd() 
{
	int counter; // ���ڱ������
	CCounterRS rs_counter(&db); // �����������¼��

	UpdateData(); // ��������
	if(m_strPersonName.IsEmpty()) return; // �ж�Ա�����Ƿ���ȷ
// ��¼���
	rs_counter.m_strFilter = "ID='O'"; // ���ù���������ȡ����ֵ
	rs_counter.Open(); // �򿪼�������¼��
	counter=rs_counter.m_COUNTER_VALUE; // ��ȡ����ֵ
	counter++; // ����ֵ��1
	rs_counter.Edit(); // �༭������
	rs_counter.m_COUNTER_VALUE=counter; // ���浱ǰ����
	rs_counter.Update(); // �ύ�޸�
	rs_counter.Close(); // �رռ�������¼��
// ��Ӽ�¼
	COvertimeRS rs_overtime(&db); // ����Ӱ��¼��
	rs_overtime.Open(); // �򿪱�
	rs_overtime.AddNew(); // ����һ���¼
	// �����ֶ�ֵ
	rs_overtime.m_ID=counter;
	rs_overtime.m_PERSON=m_strPersonID;
	rs_overtime.m_WORK_HOURS=m_nHour;
	rs_overtime.m_WORK_DATE=m_Date;
	rs_overtime.Update(); // �������ݿ�
	rs_overtime.Close(); // �رռӰ��¼��
	UpdateList(rs_overtime); // �����б��
}

BOOL CPage2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// ΪList�������
	m_cList.SetExtendedStyle(LVS_EX_GRIDLINES);
	// ����List����
	int nWidth=110;
	m_cList.InsertColumn(0, "��¼���", LVCFMT_LEFT, nWidth);
	m_cList.InsertColumn(1, "Ա����", LVCFMT_LEFT, nWidth);
	m_cList.InsertColumn(2, "�Ӱ�ʱ��", LVCFMT_LEFT, nWidth);
	m_cList.InsertColumn(3, "�Ӱ�����", LVCFMT_LEFT, nWidth);
	COvertimeRS rs(&db); // ����Ӱ��¼��
	UpdateList(rs); // ����List	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage2::UpdateList(COvertimeRS &rs)
{
	int i=0;
	CString strID,strWorkHours,strTime;
	rs.Open(); // �򿪼Ӱ��¼��
	m_cList.DeleteAllItems(); // ����б������
	while(!rs.IsEOF()) // �����ݱ������м�¼���д���
	{
		m_cList.InsertItem(i, ""); // �����Item
		strID.Format("%d", rs.m_ID); // ת��Ϊ�ַ���
		m_cList.SetItemText(i, 0, strID);
		m_cList.SetItemText(i, 1, rs.m_PERSON);
		strWorkHours.Format("%d",rs.m_WORK_HOURS);
		m_cList.SetItemText(i, 2, strWorkHours);
		m_cList.SetItemText(i, 3, rs.m_WORK_DATE.Format("%Y-%m-%d"));
		rs.MoveNext(); // ������һ����¼
		i++;
	}
	rs.Close(); // �رռӰ��¼��
}

void CPage2::OnBtnOvertimeDeleteattend() 
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
		strSQL="delete from OVERTIME where ID=" + m_cList.GetItemText(nItem, 0);
		db.ExecuteSQL(strSQL); // ִ��
	}
	COvertimeRS rs(&db); // ����Ӱ��¼��
	UpdateList(rs); // �����б��
}

void CPage2::OnBtnOvertimeSeekio() 
{
	COvertimeRS rs(&db); // ����Ӱ��¼��

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
		strFilter += "WORK_DATE>#" + strSTime + "#"; // ��ӿ�ʼʱ�����
		strFilter += " and WORK_DATE<#" + strETime + "#"; // ��ӽ���ʱ�����
	}
	if(strFilter.GetLength()>0) // �ж��Ƿ��й�������
		rs.m_strFilter=strFilter; // ����Filter
	UpdateList(rs); // �����б��
}
