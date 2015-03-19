
#include "stdafx.h"
#include "../xHome.h"
#include "../xHomeDoc.h"
#include "../xMainfrm.h"

#include "CustomerView.h"
#include "CustomerEditDlg.h"


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
// CCustomerView

IMPLEMENT_DYNCREATE(CCustomerView, CBCGPReportView)

BEGIN_MESSAGE_MAP(CCustomerView, CBCGPReportView)
	//{{AFX_MSG_MAP(CCustomerView)
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
// CCustomerView construction/destruction

CCustomerView::CCustomerView()
{
	m_pMgr = new CCustomerMgr;

}

CCustomerView::~CCustomerView()
{
    if( m_pMgr != NULL )
        delete m_pMgr;
    m_pMgr = NULL;
}

BOOL CCustomerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CBCGPReportView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCustomerView drawing

void CCustomerView::OnDraw(CDC* pDC)
{
	CBCGPReportView::OnDraw (pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CCustomerView printing

void CCustomerView::OnFilePrintPreview() 
{
	BCGPPrintPreview (this);
}

BOOL CCustomerView::OnPreparePrinting(CPrintInfo* pInfo)
{
#ifdef _BCGSUITE_INC_
	return DoPreparePrinting(pInfo);
#else
	return BCGPPreparePrinting (this, pInfo);
#endif
}

/////////////////////////////////////////////////////////////////////////////
// CCustomerView diagnostics

#ifdef _DEBUG
void CCustomerView::AssertValid() const
{
	CBCGPReportView::AssertValid();
}

void CCustomerView::Dump(CDumpContext& dc) const
{
	CBCGPReportView::Dump(dc);
}

XHomeDoc* CCustomerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(XHomeDoc)));
	return (XHomeDoc*)m_pDocument;
}
#endif //_DEBUG


void CCustomerView::OnContextMenu(CWnd*, CPoint point)
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

void CCustomerView::OnInitialUpdate() 
{
	CBCGPReportView::OnInitialUpdate();
}



int CCustomerView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPReportView::OnCreate(lpCreateStruct) == -1)
		return -1;

    InitGridCtrl();
    m_pMgr->Load();

    FillData();
	return 0;
}

void CCustomerView::OnDestroy() 
{
	CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
	ASSERT_VALID (pReportCtrl);

	pReportCtrl->SaveState (NULL);

	CBCGPReportView::OnDestroy();
}

LRESULT CCustomerView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    if(message == BCGM_GRID_ITEM_DBLCLICK)
    {
        CBCGPGridItem* pItem = (CBCGPGridItem*)lParam;
        if( pItem != NULL )
        {
            CBCGPGridRow* pRow = pItem->GetParentRow();
            if( pRow != NULL )
            {
                unsigned int id_ = (unsigned int)pRow->GetData();

                const lpxCustomer pCustomer = m_pMgr->GetCustomer(id_);
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

BOOL CCustomerView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	NMHDR* pNMHDR = (NMHDR*)(lParam);
	if (pNMHDR != NULL && pNMHDR->code == BCGPGN_SELCHANGED)
	{
		*pResult = 0L;
		return TRUE;
	}
	
	return CBCGPReportView::OnNotify(wParam, lParam, pResult);
}

void CCustomerView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CBCGPReportView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if (bActivate)
	{
		
	}
}

void CCustomerView::OnNew()
{
    xCustomer customer;
    XCustomerEditDlg dlg(customer, true);
    dlg.DoModal();
}

void CCustomerView::OnDel()
{

}

void CCustomerView::OnFind()
{
    AfxMessageBox("OnFind");
}

void CCustomerView::OnImport()
{
    AfxMessageBox("OnImport");
}

void CCustomerView::OnExport()
{
    AfxMessageBox("OnExport");
}

void CCustomerView::FillData()
{
    CBCGPReportCtrl* pReportCtrl = GetReportCtrl ();
    ASSERT_VALID (pReportCtrl);

    const lpxCustomerArray& arrCustomer = m_pMgr->GetCustomers();

    for (unsigned int i = 0; i < arrCustomer.size();++i)
    {
        const xCustomer* pCustomer = arrCustomer[i];

        CBCGPGridRow* pRow = pReportCtrl->CreateRow (pReportCtrl->GetColumnCount ());

        pRow->GetItem (GridCoulmn_Name)->SetValue (pCustomer->name_.c_str());
        pRow->GetItem (GridCoulmn_Tel)->SetValue (pCustomer->Tel_.c_str());
        pRow->GetItem (GridCoulmn_QQ)->SetValue (pCustomer->QQ_.c_str());
        pRow->GetItem (GridCoulmn_Group)->SetValue ("Group Demo");

        pRow->SetData((DWORD_PTR)(pCustomer->id_));

        pReportCtrl->AddRow (pRow, FALSE);
    }
}

void CCustomerView::InitGridCtrl()
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