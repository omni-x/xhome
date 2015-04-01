#ifndef _CustomerView_H__
#define _CustomerView_H__


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./xCustomerReportCtrl.h"
#include "../../../include/xCustomer.h"
#include "xCustomerMgr.h"

// XCustomerView
class XCustomerView : public CBCGPReportView
{
protected: // create from serialization only
	XCustomerView();
	DECLARE_DYNCREATE(XCustomerView)

// Attributes
public:
	XHomeDoc* GetDocument();

public:

    // Overrides
    CBCGPGridCtrl* CreateGrid ()
    {
        return new CCustomerReportCtrl;
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
	virtual ~XCustomerView();
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
    void    FillData(const xCustomer& customer, BOOL bRedraw = TRUE);

protected:
    lpxCustomerArray m_arrCustomer;
};

#ifndef _DEBUG  
inline XHomeDoc* XCustomerView::GetDocument()
   { return (XHomeDoc*)m_pDocument; }
#endif

#endif 
