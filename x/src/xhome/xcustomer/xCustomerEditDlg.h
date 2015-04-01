#pragma once
#include "afxwin.h"
#include "../resource.h"
#include "../../../include/xCustomer.h"
#include "xCustomerMgr.h"

class XCustomerEditDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(XCustomerEditDlg)

public:
	XCustomerEditDlg(xCustomer& customer, bool bNew, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~XCustomerEditDlg();

// 对话框数据
	enum { IDD = IDD_X_CUSTOMER_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

protected:
    void UpdateUI(BOOL bToUI);

private:
    xCustomer&  m_customer;
    bool        m_bNewC;

public:
    CBCGPEdit m_editName;
    CBCGPEdit m_editTel;
    CBCGPEdit m_editQQ;
    CBCGPComboBox m_cmbGroup;
  
    virtual BOOL OnInitDialog();
    virtual void OnOK(){};
    virtual void OnCancel(){};
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnEnChangeEditName();
    afx_msg void OnEnChangeEditTel();
    afx_msg void OnEnChangeEditQQ();
    afx_msg void OnCbnSelchangeComboGroup();
    afx_msg void OnEnChangeEditAddress();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
};
