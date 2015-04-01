#pragma once

#include "../resource.h"

// XColorPickerDlg dialog

class XColorPickerDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(XColorPickerDlg)

public:
	XColorPickerDlg(xColorCard& clrCard, CWnd* pParent = NULL);   // standard constructor
	virtual ~XColorPickerDlg();

// Dialog Data
	enum { IDD = IDD_X_DIALOG_COLOR };


    CBCGPColorButton	m_ColorPicker;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnColorPicker();

	DECLARE_MESSAGE_MAP()

private:
    xColorCard& m_clrCard;

public:
    CString m_strRGB;
    int m_nCard;
};
