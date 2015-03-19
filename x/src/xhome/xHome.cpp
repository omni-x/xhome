//
// xHome.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "xHome.h"

#include "xMainfrm.h"
#include "xHomeDoc.h"
#include "xHomeView.h"
#include "xlogin/xLoginDlg.h"

#include "RibbonTooltipCtrl.h"
#include "Planner/PlannerTooltipCtrl.h"
#include "Gantt/GanttTooltipCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CString s_szKeyPlanner (_T("Options\\Planner"));
static CString s_szKeyGantt (_T("Options\\Gantt"));

CPlannerOptions::CPlannerOptions()
	: m_clrBackground        (CLR_DEFAULT)
	, m_Type                 (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE_FIRST)
	, m_ShowToolTip          (2)
	, m_DrawFlags            ((DWORD)-1)
	, m_WorkFirstDayOfWeek   (-1)
	, m_WorkHourFirst        ( 9.0)
	, m_WorkHourLast         (18.0)
	, m_ViewHourFirst        ( 0)
	, m_ViewHourLast         (23)
	, m_DefaultImages        (FALSE)
	, m_DefaultClockIcons    (FALSE)
	, m_DefaultUpDownIcons   (FALSE)
	, m_bUpDownIconsChanged  (FALSE)
	, m_DayTimeDelta         (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA_FIRST)
	, m_WeekDrawTimeFinish   (TRUE)
	, m_WeekDrawTimeIcons    (FALSE)
	, m_MonthDrawTimeFinish  (TRUE)
	, m_MonthDrawTimeIcons   (FALSE)
	, m_MonthCompressWeekend (TRUE)
	, m_bImagesChanged       (FALSE)
	, m_bClockIconsChanged   (FALSE)
	, m_CalendarGradientFill (FALSE)
	, m_CalendarWeekNumbers  (TRUE)
{
}

void CPlannerOptions::Load ()
{
	m_clrBackground        = (COLORREF) theApp.GetSectionInt (s_szKeyPlanner, _T("BackColor"), (int) m_clrBackground);
	m_Type                 = (CBCGPPlannerManagerCtrl::BCGP_PLANNER_TYPE) theApp.GetSectionInt (s_szKeyPlanner, _T("Type"), (int) m_Type);
	m_ShowToolTip          = (int) theApp.GetSectionInt (s_szKeyPlanner, _T("ShowToolTip"), (int) m_ShowToolTip);
	m_DrawFlags            = (DWORD) theApp.GetSectionInt (s_szKeyPlanner, _T("DrawFlags"), (int) m_DrawFlags);
	m_WorkFirstDayOfWeek   = theApp.GetSectionInt (s_szKeyPlanner + _T("\\Work"), _T("FirstDayOfWeek"), m_WorkFirstDayOfWeek);
	m_WorkHourFirst        = theApp.GetSectionInt (s_szKeyPlanner + _T("\\Work"), _T("HourFirst"), (int) (m_WorkHourFirst * 100.0)) / 100.0;
	m_WorkHourLast         = theApp.GetSectionInt (s_szKeyPlanner + _T("\\Work"), _T("HourLast"), (int) (m_WorkHourLast * 100.0)) / 100.0;
	m_ViewHourFirst        = theApp.GetSectionInt (s_szKeyPlanner + _T("\\Work"), _T("ViewHourFirst"), m_ViewHourFirst);
	m_ViewHourLast         = theApp.GetSectionInt (s_szKeyPlanner + _T("\\Work"), _T("ViewHourLast"), m_ViewHourLast);
	m_DefaultImages        = (BOOL) theApp.GetSectionInt (s_szKeyPlanner, _T("DefaultImages"), (int) m_DefaultImages);
	m_DefaultClockIcons    = (BOOL) theApp.GetSectionInt (s_szKeyPlanner, _T("DefaultClockIcons"), (int) m_DefaultClockIcons);
	m_DefaultUpDownIcons   = (BOOL) theApp.GetSectionInt (s_szKeyPlanner, _T("DefaultUpDownIcons"), (int) m_DefaultUpDownIcons);
	m_DayTimeDelta         = (CBCGPPlannerView::BCGP_PLANNER_TIME_DELTA) theApp.GetSectionInt (s_szKeyPlanner + _T("\\Day"), _T("TimeScale"), (int) m_DayTimeDelta);
	m_WeekDrawTimeFinish   = (BOOL) theApp.GetSectionInt (s_szKeyPlanner + _T("\\Week"), _T("DrawTimeFinish"), (int) m_WeekDrawTimeFinish);
	m_WeekDrawTimeIcons    = (BOOL) theApp.GetSectionInt (s_szKeyPlanner + _T("\\Week"), _T("DrawTimeIcons"), (int) m_WeekDrawTimeIcons);
	m_MonthDrawTimeFinish  = (BOOL) theApp.GetSectionInt (s_szKeyPlanner + _T("\\Month"), _T("DrawTimeFinish"), (int) m_MonthDrawTimeFinish);
	m_MonthDrawTimeIcons   = (BOOL) theApp.GetSectionInt (s_szKeyPlanner + _T("\\Month"), _T("DrawTimeIcons"), (int) m_MonthDrawTimeIcons);
	m_MonthCompressWeekend = (BOOL) theApp.GetSectionInt (s_szKeyPlanner + _T("\\Month"), _T("CompressWeekend"), (int) m_MonthCompressWeekend);

	m_CalendarGradientFill = (BOOL) theApp.GetSectionInt (s_szKeyPlanner + _T("\\Calendar"), _T("GradientFill"), (int) m_CalendarGradientFill);
	m_CalendarWeekNumbers  = (BOOL) theApp.GetSectionInt (s_szKeyPlanner + _T("\\Calendar"), _T("WeekNumbers"), (int) m_CalendarWeekNumbers);

	m_bImagesChanged = !m_DefaultImages;
	m_bClockIconsChanged = !m_DefaultClockIcons;
	m_bUpDownIconsChanged = !m_DefaultUpDownIcons;
}

void CPlannerOptions::Save ()
{
	theApp.WriteSectionInt (s_szKeyPlanner, _T("BackColor"), (int) m_clrBackground);
	theApp.WriteSectionInt (s_szKeyPlanner, _T("Type"), (int) m_Type);
	theApp.WriteSectionInt (s_szKeyPlanner, _T("ShowToolTip"), (int) m_ShowToolTip);
	theApp.WriteSectionInt (s_szKeyPlanner, _T("DrawFlags"), (int) m_DrawFlags);
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Work"), _T("FirstDayOfWeek"), m_WorkFirstDayOfWeek);
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Work"), _T("HourFirst"), (int) (m_WorkHourFirst * 100.0));
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Work"), _T("HourLast"), (int) (m_WorkHourLast * 100.0));
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Work"), _T("ViewHourFirst"), m_ViewHourFirst);
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Work"), _T("ViewHourLast"), m_ViewHourLast);
	theApp.WriteSectionInt (s_szKeyPlanner, _T("DefaultImages"), (int) m_DefaultImages);
	theApp.WriteSectionInt (s_szKeyPlanner, _T("DefaultClockIcons"), (int) m_DefaultClockIcons);
	theApp.WriteSectionInt (s_szKeyPlanner, _T("DefaultUpDownIcons"), (int) m_DefaultUpDownIcons);
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Day"), _T("TimeScale"), (int) m_DayTimeDelta);
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Week"), _T("DrawTimeFinish"), (int) m_WeekDrawTimeFinish);
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Week"), _T("DrawTimeIcons"), (int) m_WeekDrawTimeIcons);
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Month"), _T("DrawTimeFinish"), (int) m_MonthDrawTimeFinish);
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Month"), _T("DrawTimeIcons"), (int) m_MonthDrawTimeIcons);
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Month"), _T("CompressWeekend"), (int) m_MonthCompressWeekend);

	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Calendar"), _T("GradientFill"), (int) m_CalendarGradientFill);
	theApp.WriteSectionInt (s_szKeyPlanner + _T("\\Calendar"), _T("WeekNumbers"), (int) m_CalendarWeekNumbers);
}


CGanttOptions::CGanttOptions()
	: m_clrBackground        (CLR_DEFAULT)
	, m_ShowToolTip          (2)
{
}

void CGanttOptions::Load ()
{
	m_clrBackground        = (COLORREF) theApp.GetSectionInt (s_szKeyGantt, _T("BackColor"), (int) m_clrBackground);
	m_ShowToolTip          = (int) theApp.GetSectionInt (s_szKeyGantt, _T("ShowToolTip"), (int) m_ShowToolTip);
}

void CGanttOptions::Save ()
{
	theApp.WriteSectionInt (s_szKeyGantt, _T("BackColor"), (int) m_clrBackground);
	theApp.WriteSectionInt (s_szKeyGantt, _T("ShowToolTip"), (int) m_ShowToolTip);
}

/////////////////////////////////////////////////////////////////////////////
// XHomeApp

BEGIN_MESSAGE_MAP(XHomeApp, CBCGPWinApp)
	//{{AFX_MSG_MAP(XHomeApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CBCGPWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CBCGPWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// XHomeApp construction

XHomeApp::XHomeApp()
{
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2007_BLUE, ID_VIEW_APPLOOK_1);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2007_BLACK, ID_VIEW_APPLOOK_2);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2007_SILVER, ID_VIEW_APPLOOK_3);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2007_AQUA, ID_VIEW_APPLOOK_4);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2010_BLUE, ID_VIEW_APPLOOK_6, TRUE);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2010_SILVER, ID_VIEW_APPLOOK_7);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2010_BLACK, ID_VIEW_APPLOOK_8);
	AddVisualTheme(BCGP_VISUAL_THEME_SCENIC, ID_VIEW_APPLOOK_5);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2013_WHITE, ID_VIEW_APPLOOK_9);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2013_GRAY, ID_VIEW_APPLOOK_10);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2013_DARK_GRAY, ID_VIEW_APPLOOK_11);

	m_bShowFloaty = TRUE;
	m_bShowToolTips = TRUE;
	m_bShowKeyTips = TRUE;
	m_bShowToolTipDescr = TRUE;

	m_nBackgroundImage = 1;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only XHomeApp object

XHomeApp theApp;

/////////////////////////////////////////////////////////////////////////////
// XHomeApp initialization

BOOL XHomeApp::InitInstance()
{
	CBCGPWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#if _MSC_VER < 1400
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("BCGSoft\\BCGControlBarPro\\Examples"));

	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	SetRegistryBase (_T("Settings2"));


    if ( !InitRoot() )
        return FALSE;

	m_OptionsPlanner.Load ();
	m_OptionsGantt.Load ();

	m_bShowFloaty = GetInt (_T("ShowFloaty"), TRUE);
	m_bShowToolTips = GetInt (_T("ShowToolTips"), TRUE);
	m_bShowKeyTips = GetInt (_T("ShowKeyTips"), TRUE);
	m_bShowToolTipDescr = GetInt (_T("ShowToolTipDescription"), TRUE);
	m_nBackgroundImage = GetInt(_T("BackgroundImage"), 1);

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;
	globalData.m_nMaxToolTipWidth = 150;

	theApp.GetTooltipManager ()->SetTooltipParams (
		0xFFFF,
		RUNTIME_CLASS (CRibbonTooltipCtrl),
		&params);
	
	if (m_OptionsPlanner.m_ShowToolTip == 2)
	{
		GetTooltipManager ()->SetTooltipParams (
			BCGP_TOOLTIP_TYPE_PLANNER,
			RUNTIME_CLASS (CPlannerTooltipCtrl),
			&params);
	}

	if (m_OptionsGantt.m_ShowToolTip == 2)
	{
 		GetTooltipManager ()->SetTooltipParams (
 			BCGP_TOOLTIP_TYPE_GANTT,
 			RUNTIME_CLASS (CGanttTooltipCtrl),
 			&params);
	}

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(XHomeDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(XHomeView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	if (globalData.m_nBitsPerPixel < 16)
	{
		AfxMessageBox (_T("The current display settings will not allow this application to display itself properly.\r\nPlease change the display color setting to 'Highest (32 bit)' and run this application again"));
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// XHomeApp message handlers

int XHomeApp::ExitInstance() 
{
	WriteInt (_T("ShowFloaty"), m_bShowFloaty);
	WriteInt (_T("ShowToolTips"), m_bShowToolTips);
	WriteInt (_T("ShowKeyTips"), m_bShowKeyTips);
	WriteInt (_T("ShowToolTipDescription"), m_bShowToolTipDescr);
	WriteInt (_T("BackgroundImage"), m_nBackgroundImage);

	m_OptionsPlanner.Save ();
	m_OptionsGantt.Save ();

    UninitRoot();

	return CBCGPWinApp::ExitInstance();
}

void XHomeApp::OnAppAbout()
{
	BCGPShowAboutDlg (AFX_IDS_APP_TITLE);
}

void XHomeApp::PreLoadState ()
{
	CBCGPContextMenuManager* pManager = GetContextMenuManager();

	pManager->AddMenu (_T("Output"), IDR_OUTPUT_MENU);
	pManager->AddMenu (_T("Mail"), IDR_MAIL_MENU);
	pManager->AddMenu (_T("Planner Appointment"), IDR_PLANNER_APPOINTMENT);
	pManager->AddMenu (_T("Planner Time Bar"), IDR_PLANNER_TIMEBAR);
	pManager->AddMenu (_T("Planner Day View"), IDR_PLANNER_CLIENT_DAY);
	pManager->AddMenu (_T("Planner Work Week View"), IDR_PLANNER_CLIENT_WORK_WEEK);
	pManager->AddMenu (_T("Planner Week View"), IDR_PLANNER_CLIENT_WEEK);
	pManager->AddMenu (_T("Planner Month View"), IDR_PLANNER_CLIENT_MONTH);
	pManager->AddMenu (_T("Tasks"), IDR_TASKS_MENU);
	pManager->AddMenu (_T("Macros Edit"), IDR_EDIT_MENU);
	pManager->AddMenu (_T("Macros Edit Margin"), IDR_EDIT_POPUP_SELECTIONMARGIN);
	pManager->AddMenu (_T("Gantt View"), IDR_GANTT_CLIENT);
	pManager->AddMenu (_T("Gantt Task"), IDR_GANTT_TASK);
	
	pManager->AddMenu (_T("Edit"), IDR_EDITCTRL_MENU);
	//pManager->AddMenu (_T("Category"), IDR_CATEGORY_MENU);
}

void XHomeApp::UpdateCalendar (BOOL bUpdateCalendar /*= TRUE*/)
{
	CMainFrame* pFrame = (CMainFrame*) AfxGetMainWnd ();
	ASSERT_VALID (pFrame);

	if (bUpdateCalendar)
	{
		XHomeDoc* pDoc = (XHomeDoc*) 
			pFrame->GetActiveDocument ();

		if (pDoc != NULL)
		{
			ASSERT_VALID (pDoc);
			pDoc->UpdateCalendar (m_OptionsPlanner);
		}

		pFrame->UpdateCalendar ();
	}
	else
	{
		//DR:
		//pFrame->GetPropBar ().Update ();
	}

	//------------------------
	// Set tooltip parameters:
	//------------------------
	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;
	globalData.m_nMaxToolTipWidth = 150;

	GetTooltipManager ()->SetTooltipParams (
		BCGP_TOOLTIP_TYPE_PLANNER,
		m_OptionsPlanner.m_ShowToolTip == 2 ?
			RUNTIME_CLASS (CPlannerTooltipCtrl) :
			RUNTIME_CLASS (CBCGPToolTipCtrl),
		&params);
}

void XHomeApp::UpdateGantt (BOOL bUpdateGantt /*= TRUE*/)
{
	CMainFrame* pFrame = (CMainFrame*) AfxGetMainWnd ();
	ASSERT_VALID (pFrame);

	if (bUpdateGantt)
	{
		XHomeDoc* pDoc = (XHomeDoc*) 
			pFrame->GetActiveDocument ();

		if (pDoc != NULL)
		{
			ASSERT_VALID (pDoc);
			pDoc->UpdateGantt (m_OptionsGantt);
		}

		pFrame->UpdateCalendar ();
	}
	else
	{
		//DR:
		//pFrame->GetPropBar ().Update ();
	}

	//------------------------
	// Set tooltip parameters:
	//------------------------
	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;
	globalData.m_nMaxToolTipWidth = 150;

	GetTooltipManager ()->SetTooltipParams (
		BCGP_TOOLTIP_TYPE_GANTT,
		m_OptionsGantt.m_ShowToolTip == 2 ?
			RUNTIME_CLASS (CPlannerTooltipCtrl) :
			RUNTIME_CLASS (CBCGPToolTipCtrl),
		&params);
}

void XHomeApp::OnBeforeChangeVisualTheme(CBCGPAppOptions& appOptions, CWnd* pMainWnd)
{
	CBCGPWinApp::OnBeforeChangeVisualTheme(appOptions, pMainWnd);

	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, pMainWnd);
	if (pFrame->GetSafeHwnd () != NULL)
	{
		pFrame->OnBeforeChangeVisualTheme(m_ActiveTheme);
	}
}

void XHomeApp::OnAfterChangeVisualTheme(CWnd* pMainWnd)
{
	CBCGPWinApp::OnAfterChangeVisualTheme(pMainWnd);

	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, pMainWnd);
	if (pFrame->GetSafeHwnd () != NULL)
	{
		pFrame->OnAfterChangeVisualTheme(m_ActiveTheme);
	}
}

/////////////////////////////////////////////////////////////////////////////
// XHomeApp message handlers

BOOL XHomeApp::InitRoot()
{
    m_xRoot.init();
    XShopMgr* shopmgr = m_xRoot.getShopMgr();
    if (shopmgr->getShopCount() == 0)
    {
        XShop* shop = shopmgr->newShop();
        shop->install("chengdu.local");
    }

    XLoginDlg login(shopmgr->curShop());
    if ( IDOK == login.DoModal() )
        return TRUE;
    return FALSE;
}

BOOL XHomeApp::UninitRoot()
{

    return TRUE;
}
