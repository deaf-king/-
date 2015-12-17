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
	// �õ���ǰʱ�䲢��ʽ��
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
	
	// �������ȱʡΪ��
	((CButton*)GetDlgItem(IDC_RADIO_OUT))->SetCheck(TRUE);
	// ΪList�������
	m_cList.SetExtendedStyle(LVS_EX_GRIDLINES);
	// ����List����
	int nWidth=110;
	m_cList.InsertColumn(0, "��¼���", LVCFMT_LEFT, nWidth);
	m_cList.InsertColumn(1, "Ա����", LVCFMT_LEFT, nWidth);
	m_cList.InsertColumn(2, "�������", LVCFMT_LEFT, nWidth);
	m_cList.InsertColumn(3, "ʱ��", LVCFMT_LEFT, nWidth);
	CAttendanceRS rs(&db); // ������ڼ�¼��
	UpdateList(rs); // ����List
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage1::OnChangeEdtDepartid() 
{
	UpdateData(); // ��������

	CDepartRS rs(&db); // �����¼��
	rs.m_strFilter = "ID='" + m_strDepartID + "'"; // ���ù�������
	rs.Open(); // �򿪼�¼��
	if(rs.GetRecordCount()==1) // �жϲ��Ŵ��������Ƿ���ȷ
	{
		m_strDepartName=rs.m_NAME; // ��ȡ��������
	}
	else m_strDepartName.Empty(); // �����������
	rs.Close(); // �رռ�¼��
	UpdateData(FALSE); // ���½�������
}

void CPage1::OnChangeEdtPersonid() 
{
	UpdateData(); // ��������

	CPersonRS rs(&db); // ����PERSON��¼��
	rs.m_strFilter = "ID='" + m_strPersonID + "'"; // ���ù�������
	rs.Open(); // �򿪼�¼��
	if(rs.GetRecordCount()==1) // �ж�Ա�����Ƿ���ȷ
	{
		m_strPersonName=rs.m_NAME; // ��ȡԱ������
		m_strDepartID=rs.m_DEPARTMENT; // ��ȡԱ�����ڲ��ű��
	}
	else m_strPersonName.Empty(); // ���Ա��������ʾ
	rs.Close(); // �رռ�¼��
	UpdateData(FALSE); // ���½�������
	OnChangeEdtDepartid(); // ��ʾ��������
}

// ��ӳ��ڼ�¼����
void CPage1::IO_Add(CString strPersonID)
{
	int counter; // ���ڼ���
	CString strIO; // ����������
	CCounterRS rs_counter(&db); // �����������¼��
// ��¼���
	rs_counter.m_strFilter = "ID='A'"; // ���ù���������ȡ����ֵ
	rs_counter.Open(); // �򿪼�������¼��
	counter=rs_counter.m_COUNTER_VALUE; // ��ȡ����ֵ
	counter++; // ����ֵ��1
	rs_counter.Edit(); // �༭������
	rs_counter.m_COUNTER_VALUE=counter; // ���浱ǰ����
	rs_counter.Update(); // �ύ�޸�
	rs_counter.Close(); // �رռ�������¼��
// ��Ӽ�¼
	// �ж�ȷ���������
	if(((CButton*)GetDlgItem(IDC_RADIO_OUT))->GetCheck())
		strIO="O";
	else strIO="I";
	// ת������ʱ������
	int nYear,nMonth,nDay,nHour,nMinute; // ��,��,��,ʱ,��
	sscanf(m_strIOTime.Left(4), "%d", &nYear); // �õ���
	sscanf(m_strIOTime.Mid(5,2), "%d", &nMonth); // �õ���
	sscanf(m_strIOTime.Mid(8,2), "%d", &nDay); // �õ���
	sscanf(m_strIOTime.Mid(11,2), "%d", &nHour); // �õ�ʱ
	sscanf(m_strIOTime.Mid(14,2), "%d", &nMinute); // �õ���
	// �õ�����ʱ��
	CTime IO_time(nYear,nMonth,nDay,nHour,nMinute,0);
	CAttendanceRS rs_attendance(&db); // ���쿼�ڼ�¼��
	rs_attendance.Open(); // �򿪿��ڼ�¼��
	rs_attendance.AddNew(); // ׷�ӿ��ڼ�¼
	rs_attendance.m_ID=counter;
	rs_attendance.m_PERSON=strPersonID;
	rs_attendance.m_IN_OUT=strIO;
	rs_attendance.m_IO_TIME=IO_time;
	rs_attendance.Update();
	rs_attendance.Close(); // �رտ��ڼ�¼��
	UpdateList(rs_attendance); // �����б��
}

void CPage1::OnBtnAddperson() // ׷�ӵ���Ա�����ڼ�¼
{
	if(!m_strPersonName.IsEmpty()) // �ж�Ա���Ƿ����
	{
		IO_Add(m_strPersonID); // ׷�ӵ���Ա����¼
	}
}

void CPage1::OnBtnAdddepart() // ׷�Ӳ���Ա�����ڼ�¼
{
	int i,n; // ���ڱ����¼����
	CPersonRS rs_person(&db); // ����Ա����Ϣ��

	if(m_strDepartName.IsEmpty()) return; // �жϲ��Ŵ����Ƿ���ȷ
	// ���ù�������
	rs_person.m_strFilter="DEPARTMENT='"+m_strDepartID+"' and STATE='T'";
	rs_person.Open(); // ��Ա����Ϣ��
	n=rs_person.GetRecordCount(); // ��ȡԱ������
	i=0; // ��ʼ������Ӽ�¼����
	// ��ʼ��������
	m_cProgress.SetRange(0, n);
	m_cProgress.SetPos(0);
	while(!rs_person.IsEOF()) // �����ݱ������м�¼���д���
	{
		IO_Add(rs_person.m_ID); // ��ӵ�ǰԱ�����ڼ�¼
		rs_person.MoveNext(); // ������һ��Ա����¼
		m_cProgress.SetPos(++i); // ��ʾ����
	}
	rs_person.Close(); // �ر�Ա����Ϣ��
}

void CPage1::OnBtnAddall() // �������Ա�����ڼ�¼
{
	int i,n; // ���ڱ����¼����
	CPersonRS rs_person(&db); // ����Ա����Ϣ��

	// ���ù�������,��ȡԱ���б�
	rs_person.m_strFilter = "STATE='T'";
	rs_person.Open(); // ��Ա����Ϣ��
	n=rs_person.GetRecordCount(); // ��ȡԱ������
	i=0; // ��ʼ������Ӽ�¼����
	// ��ʼ��������
	m_cProgress.SetRange(0, n);
	m_cProgress.SetPos(0);
	while(!rs_person.IsEOF()) // �����ݱ������м�¼���д���
	{
		IO_Add(rs_person.m_ID); // ��ӵ�ǰԱ�����ڼ�¼
		rs_person.MoveNext(); // ������һ��Ա����¼
		m_cProgress.SetPos(++i); // ��ʾ����
	}
	rs_person.Close(); // �ر�Ա����Ϣ��
}

void CPage1::UpdateList(CAttendanceRS& rs) // �����б������
{
	int i=0;
	CString strID,strTime;
	rs.Open(); // �򿪳��ڼ�¼��
	m_cList.DeleteAllItems(); // ����б������
	while(!rs.IsEOF()) // �����ݱ������м�¼���д���
	{
		m_cList.InsertItem(i, ""); // �����Item
		strID.Format("%d", rs.m_ID); // ת��Ϊ�ַ���
		m_cList.SetItemText(i, 0, strID);
		m_cList.SetItemText(i, 1, rs.m_PERSON);
		m_cList.SetItemText(i, 2, rs.m_IN_OUT);
		m_cList.SetItemText(i, 3, rs.m_IO_TIME.Format("%Y-%m-%d %H:%M"));
		rs.MoveNext(); // ������һ����¼
		i++;
	}
	rs.Close(); // �رճ��ڼ�¼��
}

void CPage1::OnBtnDeleteattend() // ɾ�����ڼ�¼�б�����ѡ��¼
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
		strSQL="delete from ATTENDANCE where ID="
			+ m_cList.GetItemText(nItem, 0);
		db.ExecuteSQL(strSQL); // ִ��
	}
	CAttendanceRS rs(&db); // ������ڼ�¼��
	UpdateList(rs); // �����б��
}

void CPage1::OnBtnSeekio() 
{
	CAttendanceRS rs(&db); // ������ڼ�¼��

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
		strFilter += "IO_TIME>#" + strSTime + "#"; // ��ӿ�ʼʱ�����
		strFilter += " and IO_TIME<#" + strETime + "#"; // ��ӽ���ʱ�����
	}
	if(strFilter.GetLength()>0) // �ж��Ƿ��й�������
		rs.m_strFilter=strFilter; // ����Filter
	UpdateList(rs); // �����б��
}
