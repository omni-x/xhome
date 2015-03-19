#ifndef _CustomerBar_H__
#define _CustomerBar_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MailBar.h : header file
//

class CCustomerBar : public CTreeCtrl
{
// Construction
public:
	CCustomerBar();

// Attributes
public:

// Operations
public:

// Overrides
	virtual BOOL Create(CWnd* pParentWnd, UINT nID);

// Implementation
public:
	virtual ~CCustomerBar();

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

#endif // !defined(AFX_MAILBAR_H__00D25365_98E4_44F5_A634_A01A7101B338__INCLUDED_)
