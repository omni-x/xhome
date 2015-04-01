
#include "stdafx.h"
#include "../xHome.h"
#include "../xHomeDoc.h"
#include "../xMainfrm.h"

#include "xCustomerView.h"
#include "xCustomerEditDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


enum
{
    GridCoulmn_Name = 0,    // 姓名
    GridCoulmn_Tel,         // 电话
    GridCoulmn_QQ,          // QQ
    GridCoulmn_Address,     // 地址  
    GridCoulmn_Group,       // 群组
    GridCoulmn_Max,

};


//////////////////////////////////////////////////////////////////////////
// XCustomerView

IMPLEMENT_DYNCREATE(XCustomerView, CBCGPReportView)

BEGIN_MESSAGE_MAP(XCustomerView, CBCGPReportView)
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

XCustomerView::XCustomerView()
{

}

XCustomerView::~XCustomerView()
{

}

BOOL XCustomerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CBCGPReportView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// XCustomerView drawing

void XCustomerView::OnDraw(CDC* pDC)
{
	CBCGPReportView::OnDraw (pDC);
}

/////////////////////////////////////////////////////////////////////////////
// XCustomerView printing

void XCustomerView::OnFilePrintPreview() 
{
	BCGPPrintPreview (this);
}

BOOL XCustomerView::OnPreparePrinting(CPrintInfo* pInfo)
{
#ifdef _BCGSUITE_INC_
	return DoPreparePrinting(pInfo);
#else
	return BCGPPreparePrinting (this, pInfo);
#endif
}

/////////////////////////////////////////////////////////////////////////////
// XCustomerView diagnostics

#ifdef _DEBUG
void XCustomerView::AssertValid() const
{
	CBCGPReportView::AssertValid();
}

void XCustomerView::Dump(CDumpContext& dc) const
{
	CBCGPReportView::Dump(dc);
}

XHomeDoc* XCustomerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(XHomeDoc)));
	return (XHomeDoc*)m_pDocument;
}
#endif //_DEBUG


void XCustomerView::OnContextMenu(CWnd*, CPoint point)
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

void XCustomerView::OnInitialUpdate() 
{
	CBCGPReportView::OnInitialUpdate();
}



int XCustomerView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPReportView::OnCreate(lpCreateStruct) == -1)
		return -1;

    InitGridCtrl();
    FillData();
	return 0;
}

void XCustomerView::OnDestroy() 
{
	CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
	ASSERT_VALID (pReportCtrl);

	pReportCtrl->SaveState (NULL);

	CBCGPReportView::OnDestroy();
}

LRESULT XCustomerView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    if(message == BCGM_GRID_ITEM_DBLCLICK)
    {
        CBCGPGridItem* pItem = (CBCGPGridItem*)lParam;
        if( pItem != NULL )
        {
            CBCGPGridRow* pRow = pItem->GetParentRow();
            if( pRow != NULL )
            {
                unsigned int id = (unsigned int)pRow->GetData();
                const lpxCustomer pCustomer = m_arrCustomer[id];
                if( pCustomer != NULL )
                {
                    XCustomerEditDlg dlg(*pCustomer, false);
                    dlg.DoModal();
                }
            }
        }
    }
    return CBCGPReportView::WindowProc(message,wParam,lParam);
}

BOOL XCustomerView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	NMHDR* pNMHDR = (NMHDR*)(lParam);
	if (pNMHDR != NULL && pNMHDR->code == BCGPGN_SELCHANGED)
	{
		*pResult = 0L;
		return TRUE;
	}
	
	return CBCGPReportView::OnNotify(wParam, lParam, pResult);
}

void XCustomerView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CBCGPReportView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if (bActivate)
	{
		
	}
}

void XCustomerView::OnNew()
{
    lpxCustomer customer = new xCustomer;
    XCustomerEditDlg dlg(*customer, true);
    if (IDOK == dlg.DoModal())
    {
        XShop* shop = theApp.curShop();
        if ( shop->addCustomer(*customer) )
        {
            FillData(*customer);
            m_arrCustomer.push_back(customer);
            return;
        }
    }
    SAFE_DELETE(customer);
}

void XCustomerView::OnDel()
{

}

void XCustomerView::OnFind()
{
    AfxMessageBox("OnFind");
}

void XCustomerView::OnImport()
{
    AfxMessageBox("OnImport");
}

void XCustomerView::OnExport()
{
    AfxMessageBox("OnExport");
}

void XCustomerView::FillData()
{
    XShop* shop = theApp.curShop();
    if (shop == NULL)
    {
        return;
    }
    shop->getCustomer(m_arrCustomer);
    for (unsigned int i = 0; i < m_arrCustomer.size();++i)
    {
        FillData(*m_arrCustomer[i], FALSE);
    }
}

void XCustomerView::FillData(const xCustomer& customer, BOOL bRedraw)
{
    CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
    CBCGPGridRow* pRow = pReportCtrl->CreateRow (pReportCtrl->GetColumnCount ());
    pRow->GetItem (GridCoulmn_Name)->SetValue (customer.name_.c_str());
    pRow->GetItem (GridCoulmn_Tel)->SetValue (customer.Tel_.c_str());
    pRow->GetItem (GridCoulmn_QQ)->SetValue (customer.QQ_.c_str());
    pRow->GetItem (GridCoulmn_Group)->SetValue ("group");
    pRow->SetData((DWORD_PTR)(customer.id_));
    pReportCtrl->AddRow (pRow, FALSE);
    if (bRedraw)
    {
        pReportCtrl->AdjustLayout ();
    }
}

void XCustomerView::InitGridCtrl()
{
    CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
    ASSERT_VALID (pReportCtrl);

    CBCGPGridColors theme;
    CBCGPVisualManager::GetInstance ()->OnSetGridColorTheme(pReportCtrl, theme);
    pReportCtrl->SendMessage(BCGM_ONSETCONTROLVMMODE, TRUE);
    pReportCtrl->SetColorTheme(theme);


    LPCTSTR szText[GridCoulmn_Max] = { "姓名", "电话", "QQ" ,"地址" , "群组" };
    int iWidth[GridCoulmn_Max]     = {  100,    100,   100,   200,    100  };
    for (int i = 0; i < GridCoulmn_Max;++i)
    {
        pReportCtrl->InsertColumn(i,szText[i],iWidth[i]);
    }
    pReportCtrl->EnableFilterBar (TRUE, _T("<all>"));
    pReportCtrl->SetWholeRowSel (TRUE);
    pReportCtrl->EnableMarkSortedColumn (TRUE, FALSE);
    pReportCtrl->EnableHeader (TRUE, BCGP_GRID_HEADER_MOVE_ITEMS | BCGP_GRID_HEADER_SORT);
    pReportCtrl->EnableRowHeader (TRUE);
    pReportCtrl->SetReadOnly ();
    pReportCtrl->EnableInvertSelOnCtrl ();
}