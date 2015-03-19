#include "stdafx.h"
#include "xNewShopDlg.h"


IMPLEMENT_DYNAMIC(XNewShopDlg, CBCGPDialog)

XNewShopDlg::XNewShopDlg(CWnd* pParent)
	: CBCGPDialog(XNewShopDlg::IDD, pParent)
{
    EnableVisualManagerStyle(TRUE, TRUE);
}

XNewShopDlg::~XNewShopDlg()
{
}

void XNewShopDlg::DoDataExchange(CDataExchange* pDX)
{
    DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
    CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XNewShopDlg, CBCGPDialog)
END_MESSAGE_MAP()


BOOL XNewShopDlg::OnInitDialog()
{
    CBCGPDialog::OnInitDialog();

    return TRUE;
}

void XNewShopDlg::OnOK()
{
    m_strName.Empty();
    m_editName.GetWindowText(m_strName);


    CBCGPDialog::OnOK();
}

void XNewShopDlg::OnCancel()
{
    CBCGPDialog::OnCancel();
}
