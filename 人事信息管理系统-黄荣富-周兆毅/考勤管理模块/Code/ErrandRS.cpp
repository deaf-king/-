// ErrandRS.cpp : implementation file
//

#include "stdafx.h"
#include "attendance.h"
#include "ErrandRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CErrandRS

IMPLEMENT_DYNAMIC(CErrandRS, CRecordset)

CErrandRS::CErrandRS(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CErrandRS)
	m_ID = 0;
	m_PERSON = _T("");
	m_DESCRIPTION = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;

	// 初始化CTime对象
	m_START_TIME=NULL;
	m_END_TIME=NULL;
}


CString CErrandRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=MISDB");
}

CString CErrandRS::GetDefaultSQL()
{
	return _T("[ERRAND]");
}

void CErrandRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CErrandRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[PERSON]"), m_PERSON);
	RFX_Date(pFX, _T("[START_TIME]"), m_START_TIME);
	RFX_Date(pFX, _T("[END_TIME]"), m_END_TIME);
	RFX_Text(pFX, _T("[DESCRIPTION]"), m_DESCRIPTION);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CErrandRS diagnostics

#ifdef _DEBUG
void CErrandRS::AssertValid() const
{
	CRecordset::AssertValid();
}

void CErrandRS::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
