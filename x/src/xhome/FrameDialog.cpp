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
// FrameDialog.cpp : implementation file
//

#include "stdafx.h"
#include "xHome.h"
#include "FrameDialog.h"

#include "OptionsPage.h"
#include "ResourcePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CBCGPRibbonBarEx, CBCGPRibbonBar)

void CBCGPRibbonBarEx::OnUpdateCmdUI (CBCGPFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	CBCGPRibbonBar::OnUpdateCmdUI (pTarget, bDisableIfNoHndler);
}

BEGIN_MESSAGE_MAP(CBCGPRibbonBarEx, CBCGPRibbonBar)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrameDialog

IMPLEMENT_DYNCREATE(CFrameDialog, CBCGPFrameWnd)

CFrameDialog::CFrameDialog()
	: m_hWndTop    (NULL)
	, m_nIDResource(NULL)
	, m_pParentWnd (NULL)
	, m_pMainWnd   (NULL)
{
}

CFrameDialog::CFrameDialog(UINT nIDResource, CWnd* pParentWnd /*= NULL*/)
	: m_hWndTop    (NULL)
	, m_nIDResource(nIDResource)
	, m_pParentWnd (pParentWnd)
	, m_pMainWnd   (NULL)
{
}

CFrameDialog::~CFrameDialog()
{
}


BEGIN_MESSAGE_MAP(CFrameDialog, CBCGPFrameWnd)
	//{{AFX_MSG_MAP(CFrameDialog)
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(BCGM_ON_RIBBON_CUSTOMIZE, OnRibbonCustomize)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrameDialog message handlers

LRESULT CFrameDialog::OnKickIdle(WPARAM, LPARAM)
{
	SendMessageToDescendants(WM_IDLEUPDATECMDUI, (WPARAM)TRUE, 0, TRUE, TRUE);
    return 0L;
}

int CFrameDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!CreateRibbonBar ())
	{
		TRACE0("Failed to create ribbon bar\n");
		return -1;      // fail to create
	};

	if (!CreateStatusBar ())
	{
		TRACE0("Failed to create ribbon bar\n");
		return -1;      // fail to create
	};

	if (!CreateOtherBars ())
	{
		return -1;      // fail to create
	}

	m_wndRibbonBar.RecalcLayout ();

	return 0;
}

void CFrameDialog::OnClose() 
{
	if (m_pPrintPreviewFrame != NULL)
	{
		CBCGPFrameWnd::OnClose();
		return;
	}

	EndDialog(IDCANCEL);
}

void CFrameDialog::PostNcDestroy()
{
}

BOOL CFrameDialog::OnEraseBkgnd (CDC*)
{
	return FALSE;
}

BOOL CFrameDialog::LoadPanelImages ()
{
	return FALSE;
}

BOOL CFrameDialog::CreateRibbonBar ()
{
	if (!m_wndRibbonBar.Create (this))
	{
		return FALSE;      // fail to create
	}

#ifndef _BCGSUITE_INC_
	m_wndRibbonBar.SetScenicLook (theApp.GetAppOptions().m_bScenicRibbon);
	m_wndRibbonBar.EnableMinimizeButton (theApp.GetAppOptions().m_bRibbonMinimizeButton);

	if (theApp.GetVisualTheme() >= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_WHITE &&
		theApp.GetVisualTheme() <= CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_DARK_GRAY)
	{
		m_wndRibbonBar.SetBackgroundImage(theApp.m_nBackgroundImage == 0 ? 0 : IDR_RIBBON_BACKGROUND1 + theApp.m_nBackgroundImage - 1);
	}
#endif

	//-------------------
	// Load panel images:
	//-------------------
	if (!LoadPanelImages ())
	{
		TRACE0("Failed to load panel images\n");
		return FALSE;
	}

	//-----------------
	// Add main button:
	//-----------------
	AddMainCategory ();

	//----------
	// Add tabs:
	//----------
	AddTabs ();

	//-----------------------------------
	// Add quick access toolbar commands:
	//-----------------------------------
	AddQAT ();

	SetKeys ();

	return TRUE;
}

BOOL CFrameDialog::CreateStatusBar ()
{
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return FALSE;
	}

	return TRUE;
}

BOOL CFrameDialog::CreateOtherBars ()
{
	return TRUE;
}

void CFrameDialog::AddMainCategory ()
{
	m_MainButton.SetImage (IDB_MAIN);
	m_MainButton.SetToolTipText (_T("File"));
	m_MainButton.SetDescription (_T("Click here to see everything you can do with your document, including saving, printing or sharing it with others"));

#ifdef _BCGSUITE_INC_
	m_wndRibbonBar.SetApplicationButton (&m_MainButton, CSize (45, 45));
#else
	m_MainButton.SetScenicText (theApp.GetAppOptions().m_bScenicRibbon ? theApp.GetAppOptions().m_strScenicRibbonLabel : _T(""));
	m_wndRibbonBar.SetMainButton (&m_MainButton, CSize (45, 45));
#endif
}

void CFrameDialog::AddTabs ()
{
}

void CFrameDialog::AddQAT ()
{
}

void CFrameDialog::SetKeys ()
{
	m_MainButton.SetKeys (_T("f"));
}

HWND CFrameDialog::PreModal()
{
	// cannot call DoModal on a dialog already constructed as modeless
	ASSERT(m_hWnd == NULL);

	// allow OLE servers to disable themselves
	CWinApp* pApp = AfxGetApp();
	if (pApp != NULL)
		pApp->EnableModeless(FALSE);

	// find parent HWND
	HWND hWnd = CWnd::GetSafeOwner_(m_pParentWnd->GetSafeHwnd(), &m_hWndTop);

	// hook for creation of dialog
	AfxHookWindowCreate(this);

	// return window to use as parent for dialog
	return hWnd;
}

void CFrameDialog::PostModal()
{
	AfxUnhookWindowCreate();   // just in case
	Detach();               // just in case

	// re-enable windows
	if (::IsWindow(m_hWndTop))
		::EnableWindow(m_hWndTop, TRUE);
	m_hWndTop = NULL;
	CWinApp* pApp = AfxGetApp();
	if (pApp != NULL)
		pApp->EnableModeless(TRUE);
}

class XRibbonPanel: public CBCGPRibbonPanel
{
	friend class CFrameDialog;
};

UINT_PTR CFrameDialog::DoModal ()
{
	HWND hWndParent = PreModal();
	AfxUnhookWindowCreate();
	BOOL bEnableParent = FALSE;
	if (hWndParent != NULL && ::IsWindowEnabled(hWndParent))
	{
		::EnableWindow(hWndParent, FALSE);
		bEnableParent = TRUE;
	}

#ifndef _BCGSUITE_INC_
	UINT nNextPanelID = XRibbonPanel::m_nNextPanelID;
	CFrameWnd* pTopLevel = g_pBCGPTopLevelFrame;

	CWinApp* pApp = AfxGetApp ();
	CWnd* pMainWnd = pApp->m_pMainWnd;
	pApp->m_pMainWnd = this;
#endif

	TRY
	{
		DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME;

		AfxHookWindowCreate(this);
		if (LoadFrame(m_nIDResource, 
			dwStyle | FWS_ADDTOTITLE, 
			hWndParent != NULL ? CWnd::FromHandle (hWndParent) : NULL, NULL))//&context)
		{
#ifndef _BCGSUITE_INC_
			BCGCBProSetTopLevelFrame (this);
#endif

			OnUpdateFrameTitle (TRUE);

			if (m_nFlags & WF_CONTINUEMODAL)
			{
				// enter modal loop
				DWORD dwFlags = MLF_SHOWONIDLE;
				if (GetStyle() & DS_NOIDLEMSG)
					dwFlags |= MLF_NOIDLEMSG;
				VERIFY(RunModalLoop(dwFlags) == m_nModalResult);
			}

			// hide the window before enabling the parent, etc.
			if (m_hWnd != NULL)
				SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW|
					SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOZORDER);
		}
	}
	CATCH_ALL(e)
	{
		do { e->Delete(); } while (0);
		m_nModalResult = -1;
	}
	END_CATCH_ALL

#ifndef _BCGSUITE_INC_
	if (pMainWnd != NULL)
	{
		pApp->m_pMainWnd = pMainWnd;
		pMainWnd = NULL;
	}

	BCGCBProSetTopLevelFrame (pTopLevel);
	XRibbonPanel::m_nNextPanelID = nNextPanelID;
#endif

	if (bEnableParent)
		::EnableWindow(hWndParent, TRUE);
	if (hWndParent != NULL && ::GetActiveWindow() == m_hWnd)
		::SetActiveWindow(hWndParent);

	// destroy modal window
	DestroyWindow();
	PostModal();

	return m_nModalResult;
}

BOOL CFrameDialog::PreCreateWindow(CREATESTRUCT& cs)
{
	m_dockManager.Create (this);

#ifdef _BCGSUITE_INC_
	m_Impl.SetDockingManager (&m_dockManager);
#else
	m_Impl.SetDockManager (&m_dockManager);
#endif

	if( !CFrameWnd::PreCreateWindow (cs))
		return FALSE;

	WNDCLASS wndcls;

	if (GetClassInfo (AfxGetInstanceHandle (), cs.lpszClass, &wndcls))
	{
		HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(IDR_MAINFRAME), RT_GROUP_ICON);
		HICON hIcon = ::LoadIcon(hInst, MAKEINTRESOURCE(IDR_MAINFRAME));

		// register a very similar WNDCLASS but without CS_HREDRAW and CS_VREDRAW styles:

		UINT nStyle = wndcls.style & ~(CS_HREDRAW | CS_VREDRAW);

		cs.lpszClass = AfxRegisterWndClass (nStyle, wndcls.hCursor, wndcls.hbrBackground, hIcon);
	}

	return TRUE;
}

BOOL CFrameDialog::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, 
							 CWnd* pParentWnd, CCreateContext* pContext)
{
	CWaitCursor wc;

	if (!CFrameWnd::LoadFrame (nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

	ModifyStyleEx (WS_EX_OVERLAPPEDWINDOW, WS_EX_WINDOWEDGE);

	m_nFlags |= WF_CONTINUEMODAL;
	m_nModalResult = -1;

#ifdef _BCGSUITE_INC_
	CDockingManager* pDockManager = GetDockingManager ();
#else
	CBCGPDockManager* pDockManager = GetDockManager ();
#endif

	if (pDockManager != NULL)
	{
#ifdef _BCGSUITE_INC_
		CWnd* pDockSite = pDockManager->GetDockSiteFrameWnd ();
#else
		CWnd* pDockSite = pDockManager->GetDockSite ();
#endif

		if (pDockSite != NULL)
		{
			CRect rectWnd;
			pDockSite->SetRedraw (FALSE);
			pDockSite->GetWindowRect (rectWnd);
			pDockSite->SetWindowPos (NULL, 0, 0, 
				rectWnd.Width () + 1, rectWnd.Height () + 1, 
				SWP_NOZORDER |  SWP_NOMOVE | SWP_NOACTIVATE);
			pDockSite->SetWindowPos (NULL, 0, 0, 
				rectWnd.Width (), rectWnd.Height (), 
				SWP_NOZORDER |  SWP_NOMOVE | SWP_NOACTIVATE);
			pDockSite->SetRedraw (TRUE);
			pDockSite->RedrawWindow (NULL, NULL, 
				RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);
		}
	}

	// Force resize:
	CRect rectWindow;
	GetWindowRect (rectWindow);

	SetWindowPos (&wndTop, 0, 0, rectWindow.Width () + 1, rectWindow.Height () + 1, 
		SWP_NOMOVE | SWP_NOZORDER);
	SetWindowPos (&wndTop, 0, 0, rectWindow.Width (), rectWindow.Height (), 
		SWP_NOMOVE | SWP_NOZORDER);

	return TRUE;
}

void CFrameDialog::OnOK()
{
	if (!UpdateData(TRUE))
	{
		TRACE0("UpdateData failed during dialog termination.\n");
		// the UpdateData routine will set focus to correct item
		return;
	}

	EndDialog(IDOK);
}

void CFrameDialog::OnCancel()
{
	EndDialog(IDCANCEL);
}

void CFrameDialog::EndDialog(int nResult)
{
	ASSERT(::IsWindow(m_hWnd));

	if (m_pPrintPreviewFrame != NULL)
	{
		CBCGPFrameWnd::OnClose();
	}

	if (m_nFlags & (WF_MODALLOOP|WF_CONTINUEMODAL))
		EndModalLoop(nResult);
}

void CFrameDialog::OnGetMinMaxInfo (MINMAXINFO FAR* lpMMI)
{
	CBCGPFrameWnd::OnGetMinMaxInfo (lpMMI);

	lpMMI->ptMinTrackSize.x = 400;
	lpMMI->ptMinTrackSize.y = 400;
}

void CFrameDialog::OnToolsOptions ()
{
	ShowOptions (0);
}

LRESULT CFrameDialog::OnRibbonCustomize (WPARAM /*wp*/, LPARAM /*lp*/)
{
	ShowOptions (1);
	return 1;
}

void CFrameDialog::ShowOptions (int nPage)
{
	// Create "Customize" page:
	CBCGPRibbonCustomizePage pageCustomize (&m_wndRibbonBar);

	// Add "popular" items:
	CList<UINT, UINT> lstPopular;

	lstPopular.AddTail (ID_FILE_SAVE);
	lstPopular.AddTail (ID_FILE_PRINT_PREVIEW);
	lstPopular.AddTail (ID_FILE_PRINT_DIRECT);

	pageCustomize.AddCustomCategory (_T("Popular Commands"), lstPopular);

	// Add hidden commands:
	CList<UINT,UINT> lstHidden;
	m_wndRibbonBar.GetItemIDsList (lstHidden, TRUE);

	pageCustomize.AddCustomCategory (_T("Commands not in the Ribbon"), lstHidden);

	// Add all commands:
	CList<UINT,UINT> lstAll;
	m_wndRibbonBar.GetItemIDsList (lstAll);

	pageCustomize.AddCustomCategory (_T("All Commands"), lstAll);

	// Create "Options" and "Resources" pages:
	//COptionsPage pageOptions;
	CResourcePage pageRes;

	// Create property sheet:
	COptionsPropSheet propSheet (this, nPage);
	propSheet.EnablePageHeader (max (60, globalData.GetTextHeight () * 3));

	propSheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;

#ifdef _BCGSUITE_INC_
	propSheet.SetLook (CMFCPropertySheet::PropSheetLook_List, 124);
#else
	propSheet.SetLook (CBCGPPropertySheet::PropSheetLook_List, 124);
#endif

	//propSheet.AddPage (&pageOptions);
	propSheet.AddPage (&pageCustomize);
	propSheet.AddPage (&pageRes);

	if (propSheet.DoModal() != IDOK)
	{
		return;
	}
}

void CFrameDialog::CompleteCategories (CBCGPRibbonButton& btn)
{
	CBCGPToolBarImages& images = btn.GetParentCategory ()->GetSmallImages ();
	int count = images.GetCount ();
	images.Load (IDB_CATEGORY_HC, NULL, TRUE);

	for (int i = 0; i < c_CategoryCount; i++)
	{
		btn.AddSubItem (new CBCGPRibbonButton (ID_CATEGORY_1 + i, c_CategoryNames[i], count + i, -1));
	}

	btn.SetDefaultCommand (FALSE);
}
