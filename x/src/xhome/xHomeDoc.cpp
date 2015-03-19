//
// xHomeDoc.cpp : implementation of the XHomeDoc class
//

#include "stdafx.h"
#include "xMainfrm.h"
#include "xHome.h"
#include "xHomeDoc.h"

#include "Views/ShortcutsView.h"
#include "Views/MailView.h"
#include "Views/CalendarPlannerView.h"
#include "Views/TasksView.h"
#include "Views/MacrosEditView.h"
#include "Views/GanttView.h"

#include "./Customer/xCustomerView.h"
#include "./xshop/xColorBlockView.h"
#include "./xorder/xOrderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// XHomeDoc

IMPLEMENT_DYNCREATE(XHomeDoc, CDocument)

BEGIN_MESSAGE_MAP(XHomeDoc, CDocument)
	//{{AFX_MSG_MAP(XHomeDoc)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// XHomeDoc construction/destruction

XHomeDoc::XHomeDoc()
	: m_Mode                 (e_ModeUndefined)
	, m_bCalendarModified    (FALSE)
{
	for (int i = 0; i < c_ViewCount; i++)
	{
		m_pViews[i] = NULL;
	}

	m_date1 = COleDateTime::GetCurrentTime ();
	m_date1 = COleDateTime (m_date1.GetYear (), m_date1.GetMonth (), m_date1.GetDay (), 0, 0, 0);
	m_date2 = m_date1;

	TCHAR lpszFilePath [_MAX_PATH];
	if (::GetModuleFileName (NULL, lpszFilePath, _MAX_PATH) > 0)
	{
		TCHAR path_buffer[_MAX_PATH];   
		TCHAR drive[_MAX_DRIVE];   
		TCHAR dir[_MAX_DIR];

#if _MSC_VER < 1400
		_tsplitpath (lpszFilePath, drive, dir, NULL, NULL);
		_tmakepath (path_buffer, drive, dir, NULL, NULL);
#else
		_tsplitpath_s (lpszFilePath, drive, _MAX_DRIVE, dir, _MAX_DIR, NULL, 0, NULL, 0);
		_tmakepath_s (path_buffer, drive, dir, NULL, NULL);
#endif

		m_strPath = path_buffer;
	}
}

XHomeDoc::~XHomeDoc()
{
	theApp.WriteProfileInt (_T("Document"), _T("Mode"), (int)m_Mode);
}

BOOL XHomeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	if (m_Mode == e_ModeUndefined)
	{
		XMode mode = (XMode)theApp.GetProfileInt (_T("Document"), _T("Mode"), (int)e_ModeHome);
		SetMode (mode);
	}

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// XHomeDoc serialization

void XHomeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// XHomeDoc diagnostics

#ifdef _DEBUG
void XHomeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void XHomeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

void XHomeDoc::SetMode(XMode mode)
{
    if(m_Mode != mode)
    {
        //bool PrinPreview = m_Mode == e_ModeClientPrintPreview;

        CFrameWnd* pFrameWnd = DYNAMIC_DOWNCAST(CFrameWnd, AfxGetMainWnd());

        CView* pOldView = pFrameWnd->GetActiveView();
		if (pOldView == NULL)
		{
			pOldView = DYNAMIC_DOWNCAST(CView, pFrameWnd->GetDescendantWindow (AFX_IDW_PANE_FIRST, TRUE));
		}

        CView* pView = NULL;

		XMode modeOld = m_Mode;
		m_Mode = mode;

		pView = GetView (m_Mode);

        if(pOldView != pView)
        {
			if ((modeOld == e_ModeMail || modeOld == e_ModeTasks) && 
				pOldView != NULL)
			{
				CBCGPGridCtrl* pGridCtrl = ((CBCGPGridView*)(pOldView))->GetGridCtrl ();
				ASSERT_VALID (pGridCtrl);

				if (pGridCtrl->IsColumnsChooserVisible ())
				{
					pGridCtrl->ShowColumnsChooser (FALSE);
				}
			}

			// exchange view window ID's so RecalcLayout() works
			UINT temp = ::GetWindowLong(pOldView->m_hWnd, GWL_ID);
			::SetWindowLong(pOldView->m_hWnd, GWL_ID, ::GetWindowLong(pView->m_hWnd, GWL_ID));
			::SetWindowLong(pView->m_hWnd, GWL_ID, temp);

			// Display and update the new current view - hide the old one    
			pOldView->ShowWindow(SW_HIDE);
			pView->ShowWindow(SW_SHOW);

			pFrameWnd->SetActiveView (pView);

			pFrameWnd->RecalcLayout();

			pView->SendMessage(WM_IDLEUPDATECMDUI, (WPARAM)TRUE);
			pFrameWnd->SendMessage(WM_SETMESSAGESTRING, (WPARAM)AFX_IDS_IDLEMESSAGE, 0L);
			pFrameWnd->UpdateWindow();
        }

		SetTitle (c_ViewNames[m_Mode]);
    }
}

BOOL XHomeDoc::CreateViews(CFrameWnd* pFrameWnd, CCreateContext* pContext)
{
    ASSERT_VALID(pFrameWnd);
    ASSERT(pContext != NULL);

    UINT nID = AFX_IDW_PANE_FIRST + 1;

    CRuntimeClass* pClass[c_ViewCount] = 
    {
		RUNTIME_CLASS(CShortcutsView),
		RUNTIME_CLASS(CMailView),
        RUNTIME_CLASS(CCalendarPlannerView),
		RUNTIME_CLASS(CTasksView),
        RUNTIME_CLASS(CMacrosEditView),
		RUNTIME_CLASS(CGanttView),
        RUNTIME_CLASS(XCustomerView),
		RUNTIME_CLASS(XColorBlockView),
		RUNTIME_CLASS(XOrderView)
    };

    CCreateContext context = *pContext;

    for(long i = 0; i < c_ViewCount; i++)
    {
        m_pViews[i] = NULL;

        context.m_pNewViewClass = pClass[i];
        context.m_pLastView     = NULL;

        m_pViews[i] = (CView*)(pFrameWnd->CreateView(&context, nID));

        if(m_pViews[i] == NULL)
        {
            return FALSE;
        }

        m_pViews[i]->ShowWindow(SW_HIDE);

        nID++;
    }

	LoadMacros (IDR_EDITOR_MACROS_1, _T("Accessibility"));

    return TRUE;
}

void XHomeDoc::LoadMacros(UINT nID, CString strName)
{
	CMacrosEditView* pView = DYNAMIC_DOWNCAST(CMacrosEditView, GetView (e_ModeMacros));

	if (pView != NULL)
	{
		ASSERT_VALID (pView);
		pView->LoadExample (nID, strName);
	}
}


/////////////////////////////////////////////////////////////////////////////
// XHomeDoc commands

void XHomeDoc::SetDateInterval (const COleDateTime& date1, const COleDateTime& date2)
{
	m_date1 = date1;
	m_date2 = date2;
	UpdateAllViews (NULL);
}

void XHomeDoc::UpdateCalendar (const CPlannerOptions& options)
{
	for (POSITION pos = GetFirstViewPosition (); pos != NULL;)
	{
		CCalendarPlannerView* pView = DYNAMIC_DOWNCAST (CCalendarPlannerView,
			GetNextView (pos));

		if (pView != NULL)
		{
			pView->UpdateCalendar (options);
		}
	}
}

void XHomeDoc::UpdateGantt (const CGanttOptions& options)
{
	for (POSITION pos = GetFirstViewPosition (); pos != NULL;)
	{
		CGanttView* pView = DYNAMIC_DOWNCAST (CGanttView,
			GetNextView (pos));

		if (pView != NULL)
		{
			pView->UpdateGantt (options);
		}
	}
}

void XHomeDoc::SetModifiedFlag(BOOL bModified/* = TRUE*/)
{
	if (m_Mode == e_ModeCalendar)
	{
		m_bCalendarModified = bModified;
	}
}

BOOL XHomeDoc::SaveModified()
{
	if (m_bCalendarModified)
	{
		CCalendarPlannerView* pView = DYNAMIC_DOWNCAST(CCalendarPlannerView, GetView (e_ModeCalendar));

		if (pView != NULL)
		{
			ASSERT_VALID (pView);
			pView->Save (m_strPath);
		}
	}

	return TRUE;
}

void XHomeDoc::OnFileClose() 
{
}

void XHomeDoc::UpdateZoom (int index)
{
	if (index == -1)
	{
		CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd ());
		if (pFrame != NULL)
		{
			index = pFrame->GetZoomSlider ()->GetPos ();
		}
	}

	if (GetMode () == e_ModeGantt)
	{
		CGanttView* pView = DYNAMIC_DOWNCAST (CGanttView, GetView (e_ModeGantt));
		if (pView != NULL)
		{
			pView->UpdateZoom (index);
		}
	}
}
