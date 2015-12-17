// DepartRS.cpp : implementation file
//

#include "stdafx.h"
#include "Attendance.h"
#include "DepartRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDepartRS

IMPLEMENT_DYNAMIC(CDepartRS, CRecordset)

CDepartRS::CDepartRS(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDepartRS)
	m_ID = _T("");
	m_NAME = _T("");
	m_MANAGER = _T("");
	m_INTRO = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CDepartRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=MISDB");
}

CString CDepartRS::GetDefaultSQL()
{
	return _T("[DEPARTMENT]");
}

void CDepartRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDepartRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[NAME]"), m_NAME);
	RFX_Text(pFX, _T("[MANAGER]"), m_MANAGER);
	RFX_Text(pFX, _T("[INTRO]"), m_INTRO);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDepartRS diagnostics

#ifdef _DEBUG
void CDepartRS::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDepartRS::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
