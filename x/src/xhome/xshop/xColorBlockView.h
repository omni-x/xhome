#ifndef _CColorBlockView_H__
#define _CColorBlockView_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ColorBlockState_Nor   0
#define ColorBlockState_Sel   0x00000001
#define ColorBlockState_Over  0x00000002

struct ColorBlock
{
	unsigned int iID;
	DWORD		 dwColor;

	CRect		 rtPos;
	DWORD		 dwState;

	ColorBlock()
	{
		dwState = ColorBlockState_Nor;
	}
};

typedef std::vector<ColorBlock*> ColorBlockArray;

class CColorBlockView : public CView
{
protected: // create from serialization only
	CColorBlockView();
	DECLARE_DYNCREATE(CColorBlockView)

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
    void         OnClickBlock(ColorBlock* pBlock);
    void         OnDBClickBlock(ColorBlock* pBlock);

	// Implementation
public:
	virtual ~CColorBlockView();
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
	ColorBlock*			Add(unsigned int iID,DWORD dwColor);
	BOOL				Del(unsigned int iID);
	void				Clear();
	ColorBlock*			Find(unsigned int iID);
    ColorBlock*         GetCurSel();

protected:
	void				CalcPos();
	ColorBlock*			Hittest(CPoint point);
protected:
	ColorBlockArray		m_arrColor;
	BOOL				m_bCalcPos;
	ColorBlock*			m_pHittest;
};

#ifndef _DEBUG  
inline XHomeDoc* CColorBlockView::GetDocument()
{ return (XHomeDoc*)m_pDocument; }
#endif

#endif 
