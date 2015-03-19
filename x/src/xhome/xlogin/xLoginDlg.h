#pragma once
#include "afxwin.h"
#include "../resource.h"

class XLoginDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(XLoginDlg)

public:
	XLoginDlg(XShop* shop, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XLoginDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
  
    virtual BOOL OnInitDialog();
    virtual void OnOK();

protected:
    CBCGPEdit m_editUser;
    CBCGPEdit m_editPassword;

private:
    XShop*  m_curShop;
};
