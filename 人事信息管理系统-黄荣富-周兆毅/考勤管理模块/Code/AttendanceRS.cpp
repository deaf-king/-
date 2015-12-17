// AttendanceRS.cpp : implementation file
//

#include "stdafx.h"
#include "Attendance.h"
#include "AttendanceRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAttendanceRS

IMPLEMENT_DYNAMIC(CAttendanceRS, CRecordset)

CAttendanceRS::CAttendanceRS(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CAttendanceRS)
	m_ID = 0;
	m_PERSON = _T("");
	m_IN_OUT = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;

	m_IO_TIME=NULL; // ³õÊ¼»¯m_IO_TIME //very important
}


CString CAttendanceRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=MISDB");
}

CString CAttendanceRS::GetDefaultSQL()
{
	return _T("[ATTENDANCE]");
}

void CAttendanceRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAttendanceRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[PERSON]"), m_PERSON);
	RFX_Text(pFX, _T("[IN_OUT]"), m_IN_OUT);
	RFX_Date(pFX, _T("[IO_TIME]"), m_IO_TIME);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CAttendanceRS diagnostics

#ifdef _DEBUG
void CAttendanceRS::AssertValid() const
{
	CRecordset::AssertValid();
}

void CAttendanceRS::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
