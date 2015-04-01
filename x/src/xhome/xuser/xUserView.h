#ifndef _UserView_H__
#define _UserView_H__


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./xUserReportCtrl.h"
#include "../../../include/xUser.h"

// XUserView
class XUserView : public CBCGPReportView
{
protected: // create from serialization only
	XUserView();
	DECLARE_DYNCREATE(XUserView)

// Attributes
public:
	XHomeDoc* GetDocument();

public:
    // Overrides
    CBCGPGridCtrl* CreateGrid ()
    {
        return new XUserReportCtrl;
    }

public:
    int OnCreate(LPCREATESTRUCT lpCreateStruct) ;
    void OnDestroy();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual void OnInitialUpdate();
protected:
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
    virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

    // Implementation
public:
	virtual ~XUserView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);	   
    afx_msg void OnFilePrintPreview();

    afx_msg void OnNew();
    afx_msg void OnDel();
    afx_msg void OnFind();
    afx_msg void OnImport();
    afx_msg void OnExport();

	DECLARE_MESSAGE_MAP()


protected:
    void    InitGridCtrl();
    void    FillData();
};

#ifndef _DEBUG  
inline XHomeDoc* XUserView::GetDocument()
   { return (XHomeDoc*)m_pDocument; }
#endif

#endif 
