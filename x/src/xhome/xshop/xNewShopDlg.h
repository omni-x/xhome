#pragma once
#include "afxwin.h"
#include "../resource.h"

class XNewShopDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(XNewShopDlg)

public:
	XNewShopDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XNewShopDlg();

// 对话框数据
	enum { IDD = IDD_X_DIALOG_STORE };

public:
    CString GetName(){return m_strName;}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
  
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();

protected:
    CBCGPEdit m_editName;
    CString m_strName;
};
