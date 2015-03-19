#include "stdafx.h"
#include "../xHome.h"
#include "./CustomerReportCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomerReportCtrl

CCustomerReportCtrl::CCustomerReportCtrl()
{
	SetScrollBarsStyle (CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER);
}

CCustomerReportCtrl::~CCustomerReportCtrl()
{
}


BEGIN_MESSAGE_MAP(CCustomerReportCtrl, CBCGPReportCtrl)
END_MESSAGE_MAP()


BOOL DoCompareGroup (const CBCGPGridRow* pRow1, const CBCGPGridRow* pRow2, int iColumn)
{
	switch (iColumn)
	{
	case 7:	// Created
	case 8:	// Received
		{
			COleDateTime date1 = (DATE) pRow1->GetItem (iColumn)->GetValue ();
			COleDateTime date2 = (DATE) pRow2->GetItem (iColumn)->GetValue ();

			return date1.GetYear () == date2.GetYear () &&
				date1.GetMonth () == date2.GetMonth () &&
				date1.GetDay () == date2.GetDay ();
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CCustomerReportCtrl message handlers

int CCustomerReportCtrl::CompareGroup (const CBCGPGridRow* pRow1, const CBCGPGridRow* pRow2, int iColumn)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pRow1);
	ASSERT_VALID (pRow2);

	if (DoCompareGroup (pRow1, pRow2, iColumn))
	{
		return 0;
	}

	return CBCGPReportCtrl::CompareGroup (pRow1, pRow2, iColumn);
}

CString CCustomerReportCtrl::GetGroupName (int iColumn, CBCGPGridItem* pItem)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pItem);

	if (iColumn == 7 ||	// Created
		iColumn == 8)	// Received
	{
		COleDateTime date = (DATE) pItem->GetValue ();

		CString strGroup;
		strGroup.Format (_T("%s: %s"), 
			m_Columns.GetColumnName (iColumn),
			date.Format (VAR_DATEVALUEONLY));

		return strGroup;
	}

	return CBCGPReportCtrl::GetGroupName (iColumn, pItem);
}
