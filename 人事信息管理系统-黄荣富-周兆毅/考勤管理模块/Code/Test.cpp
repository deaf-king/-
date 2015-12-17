// Test.cpp : implementation file
//

#include "stdafx.h"
#include "attendance.h"
#include "Test.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTest

IMPLEMENT_DYNAMIC(CTest, CRecordset)

CTest::CTest(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CTest)
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CTest::GetDefaultConnect()
{
	return _T("ODBC;DSN=");
}

CString CTest::GetDefaultSQL()
{
	return _T("");
}

void CTest::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTest)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTest diagnostics

#ifdef _DEBUG
void CTest::AssertValid() const
{
	CRecordset::AssertValid();
}

void CTest::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
