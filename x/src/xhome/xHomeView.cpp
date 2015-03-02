//
// XHomeView.cpp : implementation of the XHomeView class
//

#include "stdafx.h"
#include "xHome.h"
#include "xHomeDoc.h"
#include "xHomeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// XHomeView

IMPLEMENT_DYNCREATE(XHomeView, CView)

XHomeView::XHomeView()
{
}

XHomeView::~XHomeView()
{
}


BEGIN_MESSAGE_MAP(XHomeView, CView)
	//{{AFX_MSG_MAP(XHomeView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// XHomeView drawing

void XHomeView::OnDraw(CDC* /*pDC*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// XHomeView diagnostics

#ifdef _DEBUG
void XHomeView::AssertValid() const
{
	CView::AssertValid();
}

void XHomeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// XHomeView message handlers
