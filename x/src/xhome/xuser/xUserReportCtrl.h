#ifndef _xUserReportCtrl_H__
#define _xUserReportCtrl_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class XUserReportCtrl : public CBCGPReportCtrl
{
// Construction
public:
	XUserReportCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	virtual int CompareGroup (const CBCGPGridRow* pRow1, const CBCGPGridRow* pRow2, int iColumn);
	virtual CString GetGroupName (int nGroupCol, CBCGPGridItem* pItem);
	
// Implementation
public:
	virtual ~XUserReportCtrl();

	//--------------
	// Drag and drop
	//--------------
	virtual BOOL OnHideInsertedGroupColumn (int /*nColumn*/) const
	{
		return TRUE;
	}

protected:
	DECLARE_MESSAGE_MAP()
};

#endif 
