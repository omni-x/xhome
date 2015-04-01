// OmniContactsEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "xCustomerEditDlg.h"


// XCustomerEditDlg 对话框

IMPLEMENT_DYNAMIC(XCustomerEditDlg, CBCGPDialog)

XCustomerEditDlg::XCustomerEditDlg(xCustomer& customer, bool bNew, CWnd* pParent)
	: CBCGPDialog(XCustomerEditDlg::IDD, pParent)
    , m_customer(customer)
    , m_bNewC(bNew)
{
    EnableVisualManagerStyle(TRUE, TRUE);
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
    ON_BN_CLICKED(IDOK, &XCustomerEditDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &XCustomerEditDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL XCustomerEditDlg::OnInitDialog()
{
    CBCGPDialog::OnInitDialog();
    

    LPCTSTR lpszString = m_bNewC ? "创建" : "编辑";

    CButton* pbtnOK = ((CButton*)GetDlgItem(IDOK));
    pbtnOK->SetWindowText(lpszString);
    
    UpdateUI(TRUE);
    
    return TRUE;
}

void XCustomerEditDlg::OnEnChangeEditName()
{
    
}

void XCustomerEditDlg::OnEnChangeEditAddress()
{
     
}

void XCustomerEditDlg::OnEnChangeEditTel()
{
    
}

void XCustomerEditDlg::OnEnChangeEditQQ()
{
    
}

void XCustomerEditDlg::OnCbnSelchangeComboGroup()
{

}

void XCustomerEditDlg::UpdateUI(BOOL bToUI)
{
    if( bToUI )
    {
        m_editName.SetWindowText(m_customer.name_.c_str());
        m_editTel.SetWindowText(m_customer.Tel_.c_str());
        m_editQQ.SetWindowText(m_customer.QQ_.c_str());
        m_cmbGroup.ResetContent();
//         const lpxCustomerGroupArray& arrGroup = m_pMgr->GetGroups();
//         for (unsigned int i = 0; i < arrGroup.size(); ++i)
//         {
//             int iAdd = m_cmbGroup.AddString(arrGroup[i]->text_.c_str());
//             m_cmbGroup.SetItemData(iAdd,(DWORD_PTR)(arrGroup[i]->id_));
//             if( m_Customer.id_ == arrGroup[i]->id_ )
//                 m_cmbGroup.SetCurSel(i);
//         }   
    }
    else
    {
        CString strTemp;
        m_editName.GetWindowText(strTemp);
        m_customer.name_ = strTemp;
        m_editTel.GetWindowText(strTemp);
        m_customer.Tel_ = strTemp;
        m_editQQ.GetWindowText(strTemp);
        m_customer.QQ_ = strTemp;
        int iCur = m_cmbGroup.GetCurSel();
        if( iCur != NULL )
            m_customer.group_ = (unsigned int)m_cmbGroup.GetItemData(iCur);
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

