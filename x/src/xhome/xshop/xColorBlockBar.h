#ifndef _ColorBlockBar_H__
#define _ColorBlockBar_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MailBar.h : header file
//

class CColorBlockBar : public CTreeCtrl
{
// Construction
public:
	CColorBlockBar();

// Attributes
public:

// Operations
public:

// Overrides
	virtual BOOL Create(CWnd* pParentWnd, UINT nID);

// Implementation
public:
	virtual ~CColorBlockBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMailBar)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	CImageList		m_ImageList;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif 

