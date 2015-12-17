// OvertimeRS.cpp : implementation file
//

#include "stdafx.h"
#include "attendance.h"
#include "OvertimeRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COvertimeRS

IMPLEMENT_DYNAMIC(COvertimeRS, CRecordset)

COvertimeRS::COvertimeRS(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(COvertimeRS)
	m_ID = 0;
	m_PERSON = _T("");
	m_WORK_HOURS = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;

	m_WORK_DATE=NULL; // 初始化CTime对象
}


CString COvertimeRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=MISDB");
}

CString COvertimeRS::GetDefaultSQL()
{
	return _T("[OVERTIME]");
}

void COvertimeRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(COvertimeRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[PERSON]"), m_PERSON);
	RFX_Byte(pFX, _T("[WORK_HOURS]"), m_WORK_HOURS);
	RFX_Date(pFX, _T("[WORK_DATE]"), m_WORK_DATE);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// COvertimeRS diagnostics

#ifdef _DEBUG
void COvertimeRS::AssertValid() const
{
	CRecordset::AssertValid();
}

void COvertimeRS::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
