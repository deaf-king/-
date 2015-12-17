// PersonRS.cpp : implementation file
//

#include "stdafx.h"
#include "Attendance.h"
#include "PersonRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPersonRS

IMPLEMENT_DYNAMIC(CPersonRS, CRecordset)

CPersonRS::CPersonRS(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CPersonRS)
	m_ID = _T("");
	m_PASSWD = _T("");
	m_AUTHORITY = _T("");
	m_NAME = _T("");
	m_SEX = _T("");
	m_DEPARTMENT = _T("");
	m_JOB = _T("");
	m_EDU_LEVEL = _T("");
	m_SPECIALTY = _T("");
	m_ADDRESS = _T("");
	m_TEL = _T("");
	m_EMAIL = _T("");
	m_STATE = _T("");
	m_REMARK = _T("");
	m_nFields = 15;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;

	m_BIRTHDAY=NULL; // 初始化CTime对象
}


CString CPersonRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=MISDB");
}

CString CPersonRS::GetDefaultSQL()
{
	return _T("[PERSON]");
}

void CPersonRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CPersonRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[PASSWD]"), m_PASSWD);
	RFX_Text(pFX, _T("[AUTHORITY]"), m_AUTHORITY);
	RFX_Text(pFX, _T("[NAME]"), m_NAME);
	RFX_Text(pFX, _T("[SEX]"), m_SEX);
	RFX_Date(pFX, _T("[BIRTHDAY]"), m_BIRTHDAY);
	RFX_Text(pFX, _T("[DEPARTMENT]"), m_DEPARTMENT);
	RFX_Text(pFX, _T("[JOB]"), m_JOB);
	RFX_Text(pFX, _T("[EDU_LEVEL]"), m_EDU_LEVEL);
	RFX_Text(pFX, _T("[SPECIALTY]"), m_SPECIALTY);
	RFX_Text(pFX, _T("[ADDRESS]"), m_ADDRESS);
	RFX_Text(pFX, _T("[TEL]"), m_TEL);
	RFX_Text(pFX, _T("[EMAIL]"), m_EMAIL);
	RFX_Text(pFX, _T("[STATE]"), m_STATE);
	RFX_Text(pFX, _T("[REMARK]"), m_REMARK);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CPersonRS diagnostics

#ifdef _DEBUG
void CPersonRS::AssertValid() const
{
	CRecordset::AssertValid();
}

void CPersonRS::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
