#include "stdafx.h"
#include "../xHome.h"
#include "../xHomeDoc.h"
#include "../xMainfrm.h"

#include "xColorPickerDlg.h"
#include "XColorView.h "


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BLOCK_WIDTH 96
#define BLOCK_HEIGHT 116
#define BLOCK_TITLT_HEIGHT 26
//////////////////////////////////////////////////////////////////////////
// CCustomerView

IMPLEMENT_DYNCREATE(XColorView, CView)

BEGIN_MESSAGE_MAP(XColorView, CView)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_VSCROLL()
    ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_RIBBON_NEW,     OnNew)
	ON_COMMAND(ID_RIBBON_REMOVE,  OnDel)
	ON_COMMAND(ID_RIBBON_FIND,    OnFind)
	ON_COMMAND(ID_RIBBON_IMPORT,  OnImport)
	ON_COMMAND(ID_RIBBON_EXPORT,  OnExport)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomerView construction/destruction

XColorView::XColorView()
{
	m_bCalcPos = FALSE;
	m_pHittest = NULL;
}

XColorView::~XColorView()
{
}

BOOL XColorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class CViewor styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCustomerView drawing

void XColorView::OnDraw(CDC* pDC)
{
	if( m_bCalcPos )
		CalcPos();

	CRect rtClient;
	GetClientRect(rtClient);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC,rtClient.Width(),rtClient.Height());

	HGDIOBJ hOld = memDC.SelectObject(bitmap);

    memDC.SetBkMode(TRANSPARENT);
	memDC.FillSolidRect(rtClient,RGB(255,255,255));

	size_t iCount = m_arrColorItem.size();
	for(size_t i = 0; i < iCount ;i++)
	{
		XColorItem* pBlock = m_arrColorItem[i];

		if( pBlock->rtPos.top > rtClient.bottom || pBlock->rtPos.bottom < rtClient.top )
			continue;

        CRect rtColor = pBlock->rtPos;
        rtColor.bottom -= BLOCK_TITLT_HEIGHT;
		memDC.FillSolidRect(rtColor, pBlock->clrCard.rgb_);

        CRect rtText = rtColor;
        rtText.top = rtText.bottom;
        rtText.bottom = rtText.top + BLOCK_TITLT_HEIGHT;
        
        CString strText;
        strText.Format(_T("%d"), pBlock->clrCard.card_);
        memDC.DrawText(strText,rtText,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

		if( pBlock->dwState & ColorBlockState_Sel )
		{
            CRect rtTemp = rtColor;
            rtTemp.InflateRect(2,2,2,2);
            memDC.FillSolidRect(rtTemp, pBlock->clrCard.rgb_);
        }
		else if( pBlock->dwState & ColorBlockState_Over )
		{
            CRect rtTemp = rtColor;
            rtTemp.InflateRect(2,2,2,2);
            memDC.FillSolidRect(rtTemp, pBlock->clrCard.rgb_);
		}
	}

	pDC->BitBlt(0,0,rtClient.Width(),rtClient.Height(),&memDC,0,0,SRCCOPY);
	memDC.SelectObject(hOld);

	bitmap.DeleteObject();
	memDC.DeleteDC();


}

/////////////////////////////////////////////////////////////////////////////
// CCustomerView printing

void XColorView::OnFilePrintPreview() 
{
	BCGPPrintPreview (this);
}

BOOL XColorView::OnPreparePrinting(CPrintInfo* pInfo)
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
void XColorView::AssertValid() const
{
	CView::AssertValid();
}

void XColorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

XHomeDoc* XColorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(XHomeDoc)));
	return (XHomeDoc*)m_pDocument;
}
#endif //_DEBUG


void XColorView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
}



int XColorView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

    // temp
	{
// 		for(int i = 0; i < 100; i++)
// 		{
// 			ColorBlock* pTemp = new ColorBlock;
// 			pTemp->iID = i;
// 			pTemp->dwColor = RGB(i*5%255,i*15%255,i*25%255);
// 
// 			m_arrColor.push_back(pTemp);
// 		}
		m_bCalcPos = TRUE;
	}
	

	return 0;
}

void XColorView::OnDestroy() 
{
	

	CView::OnDestroy();
}

void XColorView::OnMouseMove(UINT nFlags, CPoint point)
{
	XColorItem* pHit = Hittest(point);
	if( pHit != NULL && m_pHittest != pHit )
	{
		if( m_pHittest != NULL )
			m_pHittest->dwState &= ~ColorBlockState_Over;
		m_pHittest = pHit;
		m_pHittest->dwState |= ColorBlockState_Over;

		Invalidate(FALSE);
	}

	CView::OnMouseMove(nFlags,point);
}

void XColorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	XColorItemArray::iterator itor = m_arrColorItem.begin();
	while(itor != m_arrColorItem.end())
	{
		(*itor)->dwState &= ~ColorBlockState_Sel;
		itor++;
	}

    Invalidate();
	CView::OnLButtonDown(nFlags,point);
}

void XColorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	XColorItem* pHit = Hittest(point);
	if( pHit != NULL  )
	{
		pHit->dwState |= ColorBlockState_Sel;

        OnClickBlock(pHit);
	}

    Invalidate();
	CView::OnLButtonUp(nFlags,point);
}

void XColorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    XColorItem* pHit = Hittest(point);
    if( pHit != NULL  )
    {
        pHit->dwState |= ColorBlockState_Sel;

        OnDBClickBlock(pHit);
    }

    Invalidate();

    CView::OnLButtonDblClk(nFlags,point);
}

LRESULT XColorView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	
	return CView::WindowProc(message,wParam,lParam);
}

BOOL XColorView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	NMHDR* pNMHDR = (NMHDR*)(lParam);
	if (pNMHDR != NULL && pNMHDR->code == BCGPGN_SELCHANGED)
	{
		*pResult = 0L;
		return TRUE;
	}

	return CView::OnNotify(wParam, lParam, pResult);
}

void XColorView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if (bActivate)
	{

	}
}

void XColorView::OnClickBlock(XColorItem* pItem)
{
    UNREFERENCED_PARAMETER(pItem);
}

void XColorView::OnDBClickBlock(XColorItem* pItem)
{
    UNREFERENCED_PARAMETER(pItem);
}

void XColorView::OnNew()
{
    xColorCard clrCard;
    XColorPickerDlg clrPickerDlg(clrCard);
    if (IDOK == clrPickerDlg.DoModal())
    {
        XShop* shop = theApp.curShop();
        if ( shop->addColor(clrCard.card_, "", clrCard.rgb_ ) )
        {
            Add(clrCard.id_, clrCard.card_, clrCard.rgb_);
            return;
        }
    }
}

void XColorView::OnDel()
{

}

void XColorView::OnFind()
{
	AfxMessageBox("OnFind");
}

void XColorView::OnImport()
{
	AfxMessageBox("OnImport");
}

void XColorView::OnExport()
{
	AfxMessageBox("OnExport");
}

XColorItem* XColorView::Add(int id, unsigned int card, DWORD dwColor)
{
	XColorItem* pTemp = Find(card);
	if( pTemp == NULL )
	{
		pTemp = new XColorItem;
        pTemp->clrCard.id_ = id;
		pTemp->clrCard.card_ = card;
		pTemp->clrCard.rgb_  = dwColor;
		m_arrColorItem.push_back(pTemp);
		m_bCalcPos = TRUE;
		return pTemp;
	}
	else
	{
		if(IDYES == AfxMessageBox(_T("已经存在，是否覆盖？"),MB_YESNO))
		{
			pTemp->clrCard.rgb_ = dwColor;
		}
		return pTemp;
	}
}

BOOL XColorView::Del(unsigned int card)
{
	XColorItemArray::iterator itor = m_arrColorItem.begin();
	while(itor != m_arrColorItem.end())
	{
		if((*itor)->clrCard.card_ == card )
		{
			XColorItem* pItem = *itor;
			if( pItem == m_pHittest )
				m_pHittest = NULL;

			delete pItem;

			m_bCalcPos = TRUE;
			return TRUE;
		}

		itor++;
	}

	return FALSE;
}

void XColorView::Clear()
{
	XColorItemArray::iterator itor = m_arrColorItem.begin();
	while(itor != m_arrColorItem.end())
	{
		XColorItem* pColor = *itor;
		delete pColor;

		itor++;
	}

	m_arrColorItem.clear();
	m_bCalcPos = TRUE;
	m_pHittest = NULL;
}

XColorItem* XColorView::Find(unsigned int card)
{
	XColorItemArray::iterator itor = m_arrColorItem.begin();
	while(itor != m_arrColorItem.end())
	{
		if((*itor)->clrCard.card_ == card )
			return (*itor);

		itor++;
	}

	return NULL;
}

XColorItem* XColorView::GetCurSel()
{
    XColorItemArray::iterator itor = m_arrColorItem.begin();
    while(itor != m_arrColorItem.end())
    {
        if((*itor)->dwState & ColorBlockState_Sel )
            return (*itor);

        itor++;
    }

    return NULL;
}

void XColorView::CalcPos()
{
	if( !m_bCalcPos )
		return;

	int iPos = GetScrollPos(SB_VERT);
	iPos = max(0,iPos);

	m_bCalcPos = FALSE;
	CRect rtClient;
	GetClientRect(rtClient);
    int iSpace = 3;

	rtClient.DeflateRect(iSpace,iSpace,iSpace,iSpace);

	CRect rtTemp = rtClient;
	rtTemp.bottom = rtTemp.top + BLOCK_HEIGHT;
	rtTemp.right = rtTemp.left - iSpace;
	size_t iCount = m_arrColorItem.size();
	for(size_t i = 0; i < iCount ;i++)
	{
		XColorItem* pBlock = m_arrColorItem[i];

		rtTemp.left = rtTemp.right + iSpace;
		rtTemp.right = rtTemp.left + BLOCK_WIDTH;
		if( rtTemp.right > rtClient.right )
		{
			rtTemp.left = rtClient.left;
			rtTemp.right = rtTemp.left + BLOCK_WIDTH;
			rtTemp.top = rtTemp.bottom + iSpace;
			rtTemp.bottom = rtTemp.top + BLOCK_HEIGHT;
		}

		pBlock->rtPos = rtTemp;
        pBlock->rtPos.MoveToY(pBlock->rtPos.top - iPos);
	}

	if( rtTemp.bottom > rtClient.bottom)
	{
		ShowScrollBar(SB_VERT,TRUE);
		
		SCROLLINFO info;
		ZeroMemory(&info,sizeof(SCROLLINFO));
		info.cbSize = sizeof(SCROLLINFO);
		info.fMask = SIF_PAGE|SIF_RANGE;
        info.nPage = BLOCK_HEIGHT;
		info.nMin = 0;
		info.nMax = rtTemp.bottom - rtClient.Height() + BLOCK_HEIGHT;

		SetScrollInfo(SB_VERT,&info);
	}
	else
	{
		ShowScrollBar(SB_VERT,FALSE);
	}
}

XColorItem* XColorView::Hittest(CPoint point)
{
	XColorItemArray::iterator itor = m_arrColorItem.begin();
	while(itor != m_arrColorItem.end())
	{
		if(((*itor)->rtPos).PtInRect(point) )
			return (*itor);

		itor++;
	}

	return NULL;
}

void XColorView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CView::OnVScroll(nSBCode,nPos,pScrollBar);

    SCROLLINFO info;
    ZeroMemory(&info,sizeof(SCROLLINFO));
    info.cbSize = sizeof(SCROLLINFO);
    info.fMask= SIF_ALL;
    GetScrollInfo(SB_VERT,&info);

    int iStep = 10;

    if (SB_THUMBTRACK == nSBCode)
    {
        info.nPos= /*nPos;*/info.nTrackPos;
    }
    else if (nSBCode == SB_LINEUP)
    {
        info.nPos -= iStep;
        if (info.nPos < info.nMin)
        {
            info.nPos = info.nMin;
        }
    }
    else if (nSBCode == SB_LINEDOWN)
    {
        info.nPos += iStep;
        if (info.nPos > info.nMax)
        {
            info.nPos = info.nMax;
        }
    }
    else if (nSBCode == SB_PAGEUP)
    {
        info.nPos -= info.nPage;
        if (info.nPos < info.nMin)
        {
            info.nPos = info.nMin;
        }
    }
    else if (nSBCode == SB_PAGEDOWN)
    {
        info.nPos += info.nPage;
        if (info.nPos > info.nMax)
        {
            info.nPos = info.nMax;
        }
    }
    else if (SB_THUMBPOSITION == nSBCode)
    {
        info.nPos = info.nTrackPos;
    }
    else if (nSBCode == SB_ENDSCROLL)
    {
    }

    info.fMask = SIF_POS;
    SetScrollInfo(SB_VERT,&info, TRUE);

    m_bCalcPos = TRUE;
    Invalidate();
}

BOOL XColorView::OnEraseBkgnd(CDC* pDC)
{
    pDC->SetBkMode(TRANSPARENT);
    return TRUE;
}

BOOL XColorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    if(zDelta<0)
        SendMessage(WM_VSCROLL,SB_PAGEDOWN,0);
    else
        SendMessage(WM_VSCROLL,SB_PAGEUP,0);
    return CView::OnMouseWheel(nFlags,zDelta,pt);
}