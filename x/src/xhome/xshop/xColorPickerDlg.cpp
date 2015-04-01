#include "stdafx.h"
#include "../xHome.h"
#include "xColorPickerDlg.h"


// XColorPickerDlg dialog

IMPLEMENT_DYNAMIC(XColorPickerDlg, CBCGPDialog)

XColorPickerDlg::XColorPickerDlg(xColorCard& clrCard, CWnd* pParent /*=NULL*/)
	: CBCGPDialog(XColorPickerDlg::IDD, pParent)
    , m_clrCard(clrCard)
    , m_nCard(0)
{
    EnableVisualManagerStyle(TRUE, TRUE);  
}

XColorPickerDlg::~XColorPickerDlg()
{
}

void XColorPickerDlg::DoDataExchange(CDataExchange* pDX)
{
    CBCGPDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COLOR_PICKER, m_ColorPicker);
    DDX_Text(pDX, IDC_RGB, m_strRGB);
    DDX_Text(pDX, IDC_EDIT_NUM, m_nCard);
}


BEGIN_MESSAGE_MAP(XColorPickerDlg, CBCGPDialog)
    ON_BN_CLICKED(IDC_COLOR_PICKER, OnColorPicker)
END_MESSAGE_MAP()


// XColorPickerDlg message handlers


BOOL XColorPickerDlg::OnInitDialog() 
{
    CBCGPDialog::OnInitDialog();

    m_ColorPicker.EnableAutomaticButton (_T("自动"), RGB (255, 0, 255));
    m_ColorPicker.EnableOtherButton (_T("其它"));
    m_ColorPicker.SetColor(m_clrCard.rgb_);
    m_ColorPicker.SetColors(CBCGPColor::GetRGBArray());
    m_ColorPicker.SetColumnsNumber (14);

    m_nCard = m_clrCard.card_;
    m_strRGB.Format (_T("%d,%d,%d"), GetRValue (m_clrCard.rgb_), GetGValue (m_clrCard.rgb_), GetBValue (m_clrCard.rgb_));

    return TRUE;
}

void XColorPickerDlg::OnColorPicker() 
{
    COLORREF color = m_ColorPicker.GetColor ();

    m_strRGB.Format (_T("%d,%d,%d"), 
        GetRValue (color),
        GetGValue (color),
        GetBValue (color));

    UpdateData (FALSE);
}

void XColorPickerDlg::OnOK()
{
    UpdateData (TRUE);
    m_clrCard.card_ = m_nCard;
    m_clrCard.rgb_ = m_ColorPicker.GetColor();
    CBCGPDialog::OnOK();
}
