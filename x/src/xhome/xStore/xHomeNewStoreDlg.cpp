#include "stdafx.h"
#include "xHomeNewStoreDlg.h"


IMPLEMENT_DYNAMIC(CNewStoreDlg, CBCGPDialog)

CNewStoreDlg::CNewStoreDlg(CWnd* pParent)
	: CBCGPDialog(CNewStoreDlg::IDD, pParent)
{
    EnableVisualManagerStyle(TRUE, TRUE);
}

CNewStoreDlg::~CNewStoreDlg()
{
}

void CNewStoreDlg::DoDataExchange(CDataExchange* pDX)
{
    DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
    CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNewStoreDlg, CBCGPDialog)
END_MESSAGE_MAP()


BOOL CNewStoreDlg::OnInitDialog()
{
    CBCGPDialog::OnInitDialog();

    return TRUE;
}

void CNewStoreDlg::OnOK()
{
    m_strName.Empty();
    m_editName.GetWindowText(m_strName);


    CBCGPDialog::OnOK();
}

void CNewStoreDlg::OnCancel()
{
    CBCGPDialog::OnCancel();
}
