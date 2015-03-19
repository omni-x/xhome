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
// OutputBar.cpp : implementation file
//

#include "stdafx.h"
#include "xHome.h"
#include "xMainfrm.h"
#include "OutputBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputBar::COutputBar()
{
}

COutputBar::~COutputBar()
{
}

BEGIN_MESSAGE_MAP(COutputBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(COutputBar)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void COutputBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBCGPMemDC memDC (dc, this);
	CDC* pDC = &memDC.GetDC ();

	CRect rect;
	GetClientRect (rect);

	pDC->FillSolidRect (rect, globalData.IsHighContastMode() ? globalData.clrWindow : globalData.clrBarHilite);

	CRect rectBorder = rect;
	rectBorder.DeflateRect (1, 1);

	CFont* pOldFont = pDC->SelectObject (&globalData.fontRegular);
	pDC->SetTextColor (globalData.IsHighContastMode() ? globalData.clrWindowText : globalData.clrBarText);
	pDC->SetBkMode (TRANSPARENT);

	rect.DeflateRect (10, 10);

	pDC->DrawText (m_strText, rect, DT_WORDBREAK);

	pDC->SelectObject (pOldFont);
	
	pDC->Draw3dRect (rectBorder, globalData.clrBarShadow, globalData.clrBarShadow);
}

void COutputBar::UpdateInfo (int nType)
{
	m_strText.Empty ();
	if (0 <= nType && nType < c_ViewCount)
	{
		m_strText = c_ViewDescription[nType];
	}

	RedrawWindow ();
}

void COutputBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	
	RedrawWindow ();
	
}

BOOL COutputBar::OnEraseBkgnd(CDC* /*pDC*/) 
{
	return TRUE;
}

int COutputBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}
