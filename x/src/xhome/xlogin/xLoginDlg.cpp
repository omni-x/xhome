#include "stdafx.h"
#include "xLoginDlg.h"


IMPLEMENT_DYNAMIC(XLoginDlg, CBCGPDialog)

XLoginDlg::XLoginDlg(XShop* shop, CWnd* pParent)
	: CBCGPDialog(XLoginDlg::IDD, pParent)
    , m_curShop(shop)
{
    
}

XLoginDlg::~XLoginDlg()
{
}

void XLoginDlg::DoDataExchange(CDataExchange* pDX)
{
    DDX_Control(pDX, IDC_EDIT_USER, m_editUser);
    DDX_Control(pDX, IDC_EDIT_PASSWORD, m_editPassword);
    CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XLoginDlg, CBCGPDialog)
END_MESSAGE_MAP()


BOOL XLoginDlg::OnInitDialog()
{
    CBCGPDialog::OnInitDialog();
    EnableVisualManagerStyle(TRUE, TRUE);
    return TRUE;
}

void XLoginDlg::OnOK()
{
    CString strUser;
    CString strPassword;
    m_editUser.GetWindowText(strUser);
    m_editPassword.GetWindowText(strPassword);
    bool rc = m_curShop->userCheck((LPTSTR)(LPCTSTR)strUser, (LPTSTR)(LPCTSTR)strPassword);
    if( rc ) 
        CBCGPDialog::OnOK();
    else
        CBCGPDialog::OnCancel();
}
