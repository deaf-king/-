// LeaveRS.cpp : implementation file
//

#include "stdafx.h"
#include "attendance.h"
#include "LeaveRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeaveRS

IMPLEMENT_DYNAMIC(CLeaveRS, CRecordset)

CLeaveRS::CLeaveRS(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CLeaveRS)
	m_ID = 0;
	m_PERSON = _T("");
	m_REASON = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;

	// 初始化CTime对象
	m_START_TIME=NULL;
	m_END_TIME=NULL;
}


CString CLeaveRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=MISDB");
}

CString CLeaveRS::GetDefaultSQL()
{
	return _T("[LEAVE]");
}

void CLeaveRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CLeaveRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[PERSON]"), m_PERSON);
	RFX_Date(pFX, _T("[START_TIME]"), m_START_TIME);
	RFX_Date(pFX, _T("[END_TIME]"), m_END_TIME);
	RFX_Text(pFX, _T("[REASON]"), m_REASON);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CLeaveRS diagnostics

#ifdef _DEBUG
void CLeaveRS::AssertValid() const
{
	CRecordset::AssertValid();
}

void CLeaveRS::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
