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
// EditDialogBar.cpp : implementation file
//

#include "stdafx.h"
#include "EditDialogBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CEditDialogBar, CBCGPDialogBar, VERSIONABLE_SCHEMA | 1)

/////////////////////////////////////////////////////////////////////////////
// CEditDialogBar

CEditDialogBar::CEditDialogBar()
{
	EnableVisualManagerStyle ();
	EnableLayout ();
}

CEditDialogBar::~CEditDialogBar()
{
}


BEGIN_MESSAGE_MAP(CEditDialogBar, CBCGPDialogBar)
	//{{AFX_MSG_MAP(CEditDialogBar)
	ON_MESSAGE(WM_INITDIALOG, HandleInitDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CEditDialogBar message handlers

LRESULT CEditDialogBar::HandleInitDialog(WPARAM wParam, LPARAM lParam)
{
	if (!CBCGPDialogBar::HandleInitDialog (wParam, lParam))
	{
		return 0L;
	}

	return OnInitDialogBar();
}

BOOL CEditDialogBar::OnInitDialogBar()
{
	return TRUE;
}
