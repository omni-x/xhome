
#include "stdafx.h"
#include "../xHome.h"
#include "../xHomeDoc.h"
#include "../xMainfrm.h"

#include "xOrderView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



//////////////////////////////////////////////////////////////////////////
// XCustomerView

IMPLEMENT_DYNCREATE(XOrderView, CBCGPReportView)

BEGIN_MESSAGE_MAP(XOrderView, CBCGPReportView)
	//{{AFX_MSG_MAP(XCustomerView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_RIBBON_NEW,     OnNew)
    ON_COMMAND(ID_RIBBON_REMOVE,  OnDel)
    ON_COMMAND(ID_RIBBON_FIND,    OnFind)
    ON_COMMAND(ID_RIBBON_IMPORT,  OnImport)
    ON_COMMAND(ID_RIBBON_EXPORT,  OnExport)
	//}}AFX_MSG_MAP
	ON_WM_CONTEXTMENU()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// XCustomerView construction/destruction

XOrderView::XOrderView()
{
}

XOrderView::~XOrderView()
{
  
}

BOOL XOrderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CBCGPReportView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// XOrderView drawing

void XOrderView::OnDraw(CDC* pDC)
{
	CBCGPReportView::OnDraw (pDC);
}

/////////////////////////////////////////////////////////////////////////////
// XOrderView printing

void XOrderView::OnFilePrintPreview() 
{
	BCGPPrintPreview (this);
}

BOOL XOrderView::OnPreparePrinting(CPrintInfo* pInfo)
{
#ifdef _BCGSUITE_INC_
	return DoPreparePrinting(pInfo);
#else
	return BCGPPreparePrinting (this, pInfo);
#endif
}

/////////////////////////////////////////////////////////////////////////////
// XOrderView diagnostics

#ifdef _DEBUG
void XOrderView::AssertValid() const
{
	CBCGPReportView::AssertValid();
}

void XOrderView::Dump(CDumpContext& dc) const
{
	CBCGPReportView::Dump(dc);
}

XHomeDoc* XOrderView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(XHomeDoc)));
	return (XHomeDoc*)m_pDocument;
}
#endif //_DEBUG


void XOrderView::OnContextMenu(CWnd*, CPoint point)
{
	if (point == CPoint (-1, -1))
	{
		CBCGPGridRow* pSel = GetReportCtrl ()->GetCurSel ();
		if (pSel != NULL)
		{
			CRect rect = pSel->GetRect ();
			ClientToScreen (&rect);

			point.x = rect.left;
			point.y = rect.bottom;
		}
	}

	theApp.ShowPopupMenu (IDR_MAIL_MENU, point, this);
}

void XOrderView::OnInitialUpdate() 
{
	CBCGPReportView::OnInitialUpdate();
}



int XOrderView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPReportView::OnCreate(lpCreateStruct) == -1)
		return -1;

 
	return 0;
}

void XOrderView::OnDestroy() 
{
	CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
	ASSERT_VALID (pReportCtrl);

	pReportCtrl->SaveState (NULL);

	CBCGPReportView::OnDestroy();
}

LRESULT XOrderView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    if(message == BCGM_GRID_ITEM_DBLCLICK)
    {
        CBCGPGridItem* pItem = (CBCGPGridItem*)lParam;
        if( pItem != NULL )
        {
            CBCGPGridRow* pRow = pItem->GetParentRow();
            if( pRow != NULL )
            {
               
            }
        }

    }
    return CBCGPReportView::WindowProc(message,wParam,lParam);
}

BOOL XOrderView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	NMHDR* pNMHDR = (NMHDR*)(lParam);
	if (pNMHDR != NULL && pNMHDR->code == BCGPGN_SELCHANGED)
	{
		*pResult = 0L;
		return TRUE;
	}
	
	return CBCGPReportView::OnNotify(wParam, lParam, pResult);
}

void XOrderView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CBCGPReportView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if (bActivate)
	{
		
	}
}

void XOrderView::OnNew()
{
}

void XOrderView::OnDel()
{

}

void XOrderView::OnFind()
{
    AfxMessageBox("OnFind");
}

void XOrderView::OnImport()
{
    AfxMessageBox("OnImport");
}

void XOrderView::OnExport()
{
    AfxMessageBox("OnExport");
}

void XOrderView::FillData()
{
    CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
    ASSERT_VALID (pReportCtrl);

   
}

void XOrderView::InitGridCtrl()
{
    CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
    ASSERT_VALID (pReportCtrl);

    CBCGPGridColors theme;
    CBCGPVisualManager::GetInstance ()->OnSetGridColorTheme(pReportCtrl, theme);
    pReportCtrl->SendMessage(BCGM_ONSETCONTROLVMMODE, TRUE);
    pReportCtrl->SetColorTheme(theme);


    pReportCtrl->EnableFilterBar (TRUE, _T("<all>"));
    pReportCtrl->SetWholeRowSel (TRUE);
    pReportCtrl->EnableMarkSortedColumn (TRUE, FALSE);
    pReportCtrl->EnableHeader (TRUE, BCGP_GRID_HEADER_MOVE_ITEMS | BCGP_GRID_HEADER_SORT);
    pReportCtrl->EnableRowHeader (TRUE);
    pReportCtrl->SetReadOnly ();
    pReportCtrl->EnableInvertSelOnCtrl ();
}