//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2014 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// BCGPOrganizerView.h : interface of the XHomeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCGPORGANIZERVIEW_H__C7BFD049_7188_4AAE_8E51_7FCFF0DAAD64__INCLUDED_)
#define AFX_BCGPORGANIZERVIEW_H__C7BFD049_7188_4AAE_8E51_7FCFF0DAAD64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class XHomeView : public CView
{
protected:
	XHomeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(XHomeView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(XHomeView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~XHomeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(XHomeView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPORGANIZERVIEW_H__C7BFD049_7188_4AAE_8E51_7FCFF0DAAD64__INCLUDED_)
