#pragma once
#include "afxwin.h"
#include "../resource.h"

class XNewShopDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(XNewShopDlg)

public:
	XNewShopDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~XNewShopDlg();

// �Ի�������
	enum { IDD = IDD_X_DIALOG_STORE };

public:
    CString GetName(){return m_strName;}

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
  
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();

protected:
    CBCGPEdit m_editName;
    CString m_strName;
};
