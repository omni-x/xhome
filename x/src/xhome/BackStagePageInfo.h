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
#if !defined(AFX_BACKSTAGEPAGEINFO_H__8AF195CB_7D3C_4679_95FA_85A33E715802__INCLUDED_)
#define AFX_BACKSTAGEPAGEINFO_H__8AF195CB_7D3C_4679_95FA_85A33E715802__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BackStagePageInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBackStagePageInfo dialog

class CNewRibbonGalleryCtrl : public CBCGPRibbonGalleryCtrl
{
public:
	virtual void OnDrawGalleryItem (CDC* pDC, CRect rectIcon, int nIconIndex, CBCGPRibbonPaletteIcon* pIcon, COLORREF clrText);

	CBCGPToolBarImages	m_Icons;
};

class CBackStagePageInfo : public CBCGPDialog
{
	DECLARE_DYNCREATE(CBackStagePageInfo)

// Construction
public:
	CBackStagePageInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBackStagePageInfo)
	enum { IDD = IDD_BS_FORM_INFO };
	CBCGPStatic	m_wndInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBackStagePageInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBackStagePageInfo)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnShortcutHiglighted(WPARAM wParam, LPARAM lParam);
	afx_msg void OnShortcut();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CNewRibbonGalleryCtrl	m_wndShortcuts;
	int						m_nItem;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKSTAGEPAGEINFO_H__8AF195CB_7D3C_4679_95FA_85A33E715802__INCLUDED_)
