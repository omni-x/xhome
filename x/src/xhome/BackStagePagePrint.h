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
#if !defined(AFX_BACKSTAGEPAGEPRINT_H__080E2FC7_C2A5_49C7_A6D3_00171E307EC7__INCLUDED_)
#define AFX_BACKSTAGEPAGEPRINT_H__080E2FC7_C2A5_49C7_A6D3_00171E307EC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BackStagePagePrint.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBackStagePagePrint window

class CBackStagePagePrint : public CBCGPRibbonBackstagePagePrint
{
	DECLARE_DYNCREATE(CBackStagePagePrint)

// Construction
public:
	CBackStagePagePrint(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBackStagePagePrint();

// Dialog Data
	//{{AFX_DATA(CBCGPBackStagePagePrint)
	enum { IDD = IDD_BS_FORM_PRINT };
	CBCGPRibbonComboGalleryCtrl	m_wndType;
	//}}AFX_DATA

	virtual void OnInitPrintControls();

public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBackStagePagePrint)
	public:
	virtual BOOL OnInitDialog();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBackStagePagePrint)
	afx_msg void OnSelectType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	virtual void InitializePrintInfo();
	virtual BOOL PreparePrintInfo();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKSTAGEPAGEPRINT_H__080E2FC7_C2A5_49C7_A6D3_00171E307EC7__INCLUDED_)
