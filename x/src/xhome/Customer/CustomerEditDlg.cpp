// OmniContactsEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CustomerEditDlg.h"


// XCustomerEditDlg 对话框

IMPLEMENT_DYNAMIC(XCustomerEditDlg, CBCGPDialog)

XCustomerEditDlg::XCustomerEditDlg(const xCustomer& customer, bool bNew, CWnd* pParent)
	: CBCGPDialog(XCustomerEditDlg::IDD, pParent)
{
    EnableVisualManagerStyle(TRUE, TRUE);
    m_Customer = customer;
    m_bNewCustomer = bNew;
    m_bInitUI = FALSE;  
}

XCustomerEditDlg::~XCustomerEditDlg()
{

}

void XCustomerEditDlg::DoDataExchange(CDataExchange* pDX)
{
    DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
    DDX_Control(pDX, IDC_EDIT_TEL, m_editTel);
    DDX_Control(pDX, IDC_EDIT_QQ, m_editQQ);
    DDX_Control(pDX, IDC_CMB_GROUP, m_cmbGroup);
    CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(XCustomerEditDlg, CBCGPDialog)
    ON_EN_CHANGE(IDC_EDIT_NAME, &XCustomerEditDlg::OnEnChangeEditName)
    ON_EN_CHANGE(IDC_CMB_GROUP, &XCustomerEditDlg::OnEnChangeEditTel)
    ON_EN_CHANGE(IDC_EDIT_QQ, &XCustomerEditDlg::OnEnChangeEditQQ)
    ON_CBN_SELCHANGE(IDC_CMB_GROUP, &XCustomerEditDlg::OnCbnSelchangeComboGroup)
    ON_WM_SYSCOMMAND()
    ON_BN_CLICKED(ID_OK, &XCustomerEditDlg::OnBnClickedOk)
    ON_BN_CLICKED(ID_CANCEL, &XCustomerEditDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL XCustomerEditDlg::OnInitDialog()
{
    CBCGPDialog::OnInitDialog();
    UpdateUI(TRUE);
    if ( m_bNewCustomer )
    {
        ((CButton*)GetDlgItem(IDOK))->SetWindowText("创建");
    }
    else
        ((CButton*)GetDlgItem(IDOK))->SetWindowText("更新");

    return TRUE;
}

void XCustomerEditDlg::OnEnChangeEditName()
{
    UpdateUI(FALSE);
}

void XCustomerEditDlg::OnEnChangeEditAddress()
{
     UpdateUI(FALSE);
}

void XCustomerEditDlg::OnEnChangeEditTel()
{
    UpdateUI(FALSE);
}

void XCustomerEditDlg::OnEnChangeEditQQ()
{
    UpdateUI(FALSE);
}

void XCustomerEditDlg::OnCbnSelchangeComboGroup()
{
    UpdateUI(FALSE);
}


void XCustomerEditDlg::UpdateUI(BOOL bToUI)
{
    if( m_bInitUI )
        return;

    if( bToUI )
    {
        m_bInitUI = TRUE;
        m_editName.SetWindowText(m_Customer.name_.c_str());
        m_editTel.SetWindowText(m_Customer.Tel_.c_str());
        m_editQQ.SetWindowText(m_Customer.QQ_.c_str());
        m_cmbGroup.ResetContent();
//         const lpxCustomerGroupArray& arrGroup = m_pMgr->GetGroups();
//         for (unsigned int i = 0; i < arrGroup.size(); ++i)
//         {
//             int iAdd = m_cmbGroup.AddString(arrGroup[i]->text_.c_str());
//             m_cmbGroup.SetItemData(iAdd,(DWORD_PTR)(arrGroup[i]->id_));
//             if( m_Customer.id_ == arrGroup[i]->id_ )
//                 m_cmbGroup.SetCurSel(i);
//         }   
        m_bInitUI = FALSE;
    }
    else
    {
        CString strTemp;
        m_editName.GetWindowText(strTemp);
        m_Customer.name_ = strTemp;
        m_editTel.GetWindowText(strTemp);
        m_Customer.Tel_ = strTemp;
        m_editQQ.GetWindowText(strTemp);
        m_Customer.QQ_ = strTemp;
        int iCur = m_cmbGroup.GetCurSel();
        if( iCur != NULL )
            m_Customer.id_ = (unsigned int)m_cmbGroup.GetItemData(iCur);
    } 
}

void XCustomerEditDlg::OnBnClickedOk()
{
    UpdateUI(FALSE);
    CBCGPDialog::OnOK();
}

void XCustomerEditDlg::OnBnClickedCancel()
{
    CBCGPDialog::OnCancel();
}

void XCustomerEditDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if( nID == SC_CLOSE)
    {
        OnBnClickedCancel();
        return;
    }
    CBCGPDialog::OnSysCommand(nID,lParam);
}

