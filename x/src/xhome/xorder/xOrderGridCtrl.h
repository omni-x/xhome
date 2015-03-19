#ifndef _XOrderGridCtrl_H__
#define _XOrderGridCtrl_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class XOrderGridCtrl : public CBCGPReportCtrl
{
// Construction
public:
	XOrderGridCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	virtual int CompareGroup (const CBCGPGridRow* pRow1, const CBCGPGridRow* pRow2, int iColumn);
	virtual CString GetGroupName (int nGroupCol, CBCGPGridItem* pItem);
	
// Implementation
public:
	virtual ~XOrderGridCtrl();

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
