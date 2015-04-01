#ifndef _XColorView_H__
#define _XColorView_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ColorBlockState_Nor   0
#define ColorBlockState_Sel   0x00000001
#define ColorBlockState_Over  0x00000002

struct XColorItem
{
    xColorCard      clrCard;
	CRect		    rtPos;
	DWORD		    dwState;
    XColorItem()
	{
		dwState = ColorBlockState_Nor;
	}
};

typedef std::vector<XColorItem*> XColorItemArray;

class XColorView : public CView
{
protected: // create from serialization only
	XColorView();
	DECLARE_DYNCREATE(XColorView)

	// Attributes
public:
	XHomeDoc* GetDocument();

public:
    BOOL         OnEraseBkgnd(CDC* pDC);
	int          OnCreate(LPCREATESTRUCT lpCreateStruct) ;
	void         OnDestroy();
	void         OnMouseMove(UINT nFlags, CPoint point);
    BOOL         OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void         OnLButtonDown(UINT nFlags, CPoint point);
	void         OnLButtonUp(UINT nFlags, CPoint point);
    void         OnLButtonDblClk(UINT nFlags, CPoint point);
	void         OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

protected:
    void         OnClickBlock(XColorItem* pItem);
    void         OnDBClickBlock(XColorItem* pItem);

	// Implementation
public:
	virtual ~XColorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg void OnFilePrintPreview();

	afx_msg void OnNew();
	afx_msg void OnDel();
	afx_msg void OnFind();
	afx_msg void OnImport();
	afx_msg void OnExport();

	DECLARE_MESSAGE_MAP()

public:
	XColorItem*			Add(int id, unsigned int card, DWORD dwColor);
	BOOL				Del(unsigned int card);
	void				Clear();
	XColorItem*			Find(unsigned int card);
    XColorItem*         GetCurSel();

protected:
	void				CalcPos();
	XColorItem*			Hittest(CPoint point);
protected:
	XColorItemArray		m_arrColorItem;
	BOOL				m_bCalcPos;
	XColorItem*			m_pHittest;
};

#ifndef _DEBUG  
inline XHomeDoc* XColorView::GetDocument()
{ return (XHomeDoc*)m_pDocument; }
#endif

#endif 
