// CounterRS.cpp : implementation file
//

#include "stdafx.h"
#include "Attendance.h"
#include "CounterRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCounterRS

IMPLEMENT_DYNAMIC(CCounterRS, CRecordset)

CCounterRS::CCounterRS(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CCounterRS)
	m_ID = _T("");
	m_COUNTER_VALUE = 0;
	m_DESCRIPTION = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CCounterRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=MISDB");
}

CString CCounterRS::GetDefaultSQL()
{
	return _T("[COUNTER]");
}

void CCounterRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CCounterRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[ID]"), m_ID);
	RFX_Int(pFX, _T("[COUNTER_VALUE]"), m_COUNTER_VALUE);
	RFX_Text(pFX, _T("[DESCRIPTION]"), m_DESCRIPTION);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCounterRS diagnostics

#ifdef _DEBUG
void CCounterRS::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCounterRS::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
