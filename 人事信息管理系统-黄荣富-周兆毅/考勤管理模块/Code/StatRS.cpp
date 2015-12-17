// StatRS.cpp : implementation file
//

#include "stdafx.h"
#include "attendance.h"
#include "StatRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatRS

IMPLEMENT_DYNAMIC(CStatRS, CRecordset)

CStatRS::CStatRS(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CStatRS)
	m_ID = 0;
	m_YEAR_MONTH = _T("");
	m_PERSON = _T("");
	m_WORK_HOUR = 0;
	m_OVER_HOUR = 0;
	m_LEAVE_HDAY = 0;
	m_ERRAND_HDAY = 0;
	m_LATE_TIMES = 0;
	m_EARLY_TIMES = 0;
	m_ABSENT_TIMES = 0;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CStatRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=MISDB");
}

CString CStatRS::GetDefaultSQL()
{
	return _T("[ATTENDANCE_STAT]");
}

void CStatRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CStatRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[YEAR_MONTH]"), m_YEAR_MONTH);
	RFX_Text(pFX, _T("[PERSON]"), m_PERSON);
	RFX_Int(pFX, _T("[WORK_HOUR]"), m_WORK_HOUR);
	RFX_Long(pFX, _T("[OVER_HOUR]"), m_OVER_HOUR);
	RFX_Int(pFX, _T("[LEAVE_HDAY]"), m_LEAVE_HDAY);
	RFX_Int(pFX, _T("[ERRAND_HDAY]"), m_ERRAND_HDAY);
	RFX_Byte(pFX, _T("[LATE_TIMES]"), m_LATE_TIMES);
	RFX_Byte(pFX, _T("[EARLY_TIMES]"), m_EARLY_TIMES);
	RFX_Byte(pFX, _T("[ABSENT_TIMES]"), m_ABSENT_TIMES);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CStatRS diagnostics

#ifdef _DEBUG
void CStatRS::AssertValid() const
{
	CRecordset::AssertValid();
}

void CStatRS::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
