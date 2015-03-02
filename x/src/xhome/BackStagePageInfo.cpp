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
// BackStagePageInfo.cpp : implementation file
//

#include "stdafx.h"
#include "xHome.h"
#include "mainfrm.h"
#include "BackStagePageInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const int xMargin = 5;
static const int yMargin = 5;

/////////////////////////////////////////////////////////////////////////////
// CBackStagePageInfo dialog

void CNewRibbonGalleryCtrl::OnDrawGalleryItem (CDC* pDC, CRect rectIcon, int nIconIndex, CBCGPRibbonPaletteIcon* /*pIcon*/, COLORREF clrText)
{
	const double dScale = globalData.GetRibbonImageScale ();
	rectIcon.top += (int)(yMargin * dScale);

	m_Icons.DrawEx(pDC, rectIcon, nIconIndex, CBCGPToolBarImages::ImageAlignHorzCenter, CBCGPToolBarImages::ImageAlignVertTop);

	CRect rectText = rectIcon;
	rectText.top += m_Icons.GetImageSize().cy + (int)(yMargin * dScale);
	rectText.DeflateRect((int)(xMargin * dScale), 0);

	COLORREF clrTextOld = (COLORREF)-1;

	if (clrText != (COLORREF)-1)
	{
		clrTextOld = pDC->SetTextColor(clrText);
	}

	pDC->DrawText(c_ViewNames[nIconIndex], rectText, DT_WORDBREAK | DT_CENTER);

	if (clrTextOld != (COLORREF)-1)
	{
		pDC->SetTextColor(clrTextOld);
	}
}


IMPLEMENT_DYNCREATE(CBackStagePageInfo, CBCGPDialog)

class BCGPView: public CView
{
	friend class CBackStagePageInfo;
};

CBackStagePageInfo::CBackStagePageInfo(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CBackStagePageInfo::IDD, pParent)
	, m_nItem (-1)
{
	//{{AFX_DATA_INIT(CBackStagePageInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	EnableLayout ();
}


void CBackStagePageInfo::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBackStagePageInfo)
	DDX_Control(pDX, IDC_BS_FORM_INFO_INFO, m_wndInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBackStagePageInfo, CBCGPDialog)
	//{{AFX_MSG_MAP(CBackStagePageInfo)
	ON_REGISTERED_MESSAGE(BCGM_ON_HIGHLIGHT_RIBBON_LIST_ITEM, OnShortcutHiglighted)
	ON_COMMAND(IDC_BS_FORM_INFO_GALLERY, OnShortcut)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBackStagePageInfo message handlers

BOOL CBackStagePageInfo::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();

	CRect rectWnd;

	CWnd* pWnd = GetDlgItem (IDC_BS_FORM_INFO_GALLERY);
	ASSERT(pWnd);
	pWnd->GetWindowRect (rectWnd);
	ScreenToClient (rectWnd);
	pWnd->DestroyWindow ();

	const double dScale = globalData.GetRibbonImageScale ();
	CSize sizeItem((int)(85 * dScale), (int)(115 * dScale));
	m_wndShortcuts.Create(rectWnd, this, IDC_BS_FORM_INFO_GALLERY);
	m_wndShortcuts.m_Icons.SetImageSize(CSize(64, 64));
	m_wndShortcuts.m_Icons.Load(IDB_SHORTCUTS_RIBBON_BS);
	m_wndShortcuts.m_Icons.SmoothResize (dScale);
	m_wndShortcuts.AddGroup (NULL, sizeItem, c_ViewCount);

	pWnd = GetDlgItem (IDC_BS_FORM_INFO_LABEL);
	ASSERT(pWnd);
	pWnd->SetFont (&globalData.fontCaption);

	m_wndInfo.SetFont (&globalData.fontBold);

	CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
	ASSERT_VALID(pLayout);

	pLayout->AddAnchor(IDC_BS_FORM_INFO_LABEL, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
	pLayout->AddAnchor(IDC_BS_FORM_INFO_SEP1, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
	pLayout->AddAnchor(m_wndShortcuts.GetSafeHwnd (), CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeBoth);
	pLayout->AddAnchor(IDC_BS_FORM_INFO_INFO, CBCGPStaticLayout::e_MoveTypeVert, CBCGPStaticLayout::e_SizeTypeHorz);
	pLayout->AddAnchor(IDC_BS_FORM_INFO_SEP2, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeVert);
	pLayout->AddAnchor(IDC_BS_FORM_INFO_PREVIEW, CBCGPStaticLayout::e_MoveTypeHorz, CBCGPStaticLayout::e_SizeTypeNone);

	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd ());
	if (pFrame != NULL)
	{
		int nItem = pFrame->GetOutlookBar ()->GetActiveShortcut ();
		m_wndShortcuts.SelectItem (nItem);
		OnShortcutHiglighted (nItem, 0L);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CBackStagePageInfo::OnShortcutHiglighted(WPARAM wParam, LPARAM /*lParam*/)
{
	LPCTSTR lpText = _T("");
	if (0 <= wParam && wParam < c_ViewCount)
	{
		lpText = c_ViewDescription[wParam];
	}

	m_wndInfo.SetWindowText (lpText);

	return 0L;
}

void CBackStagePageInfo::OnShortcut ()
{
	m_nItem = m_wndShortcuts.GetSelectedItem ();

	GetParent()->PostMessage(WM_CLOSE);
}

void CBackStagePageInfo::OnDestroy() 
{
	CBCGPDialog::OnDestroy();
	
	if (m_nItem != -1)
	{
		AfxGetMainWnd()->PostMessage(BCGM_CHANGE_ACTIVE_TAB, m_nItem, 0L);
	}
}
