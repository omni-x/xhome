#include "stdafx.h"
#include "../xHome.h"
#include "./xOrderGridCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COrderGridCtrl

XOrderGridCtrl::XOrderGridCtrl()
{
	SetScrollBarsStyle (CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER);
}

XOrderGridCtrl::~XOrderGridCtrl()
{
}


BEGIN_MESSAGE_MAP(XOrderGridCtrl, CBCGPReportCtrl)
END_MESSAGE_MAP()


BOOL DoCompareGroupOrder (const CBCGPGridRow* pRow1, const CBCGPGridRow* pRow2, int iColumn)
{
	UNREFERENCED_PARAMETER(pRow1);
	UNREFERENCED_PARAMETER(pRow2);
	UNREFERENCED_PARAMETER(iColumn);

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// COrderGridCtrl message handlers

int XOrderGridCtrl::CompareGroup (const CBCGPGridRow* pRow1, const CBCGPGridRow* pRow2, int iColumn)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pRow1);
	ASSERT_VALID (pRow2);

	if (DoCompareGroupOrder (pRow1, pRow2, iColumn))
	{
		return 0;
	}

	return CBCGPReportCtrl::CompareGroup (pRow1, pRow2, iColumn);
}

CString XOrderGridCtrl::GetGroupName (int iColumn, CBCGPGridItem* pItem)
{
	ASSERT_VALID (this);
	ASSERT_VALID (pItem);

	return CBCGPReportCtrl::GetGroupName (iColumn, pItem);
}
