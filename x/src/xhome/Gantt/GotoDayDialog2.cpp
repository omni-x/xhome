//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2014 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// GotoDayDialog2.cpp : implementation file
//

#include "stdafx.h"
#include "../resource.h"
#include "GotoDayDialog2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGotoDayDialog2 dialog

CGotoDayDialog2::CGotoDayDialog2(const COleDateTime& date, 
	int nFirstDayOfWeek /*= 0*/, 
	CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CGotoDayDialog2::IDD, pParent)
	, m_Date (date)
	, m_nFirstDayOfWeek(0)
{
	EnableVisualManagerStyle (TRUE, TRUE);

	//{{AFX_DATA_INIT(CGotoDayDialog2)
	//}}AFX_DATA_INIT

	ASSERT (0 <= nFirstDayOfWeek);
	ASSERT (nFirstDayOfWeek <= 6);

	m_nFirstDayOfWeek = nFirstDayOfWeek;
}


void CGotoDayDialog2::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGotoDayDialog2)
	DDX_Control(pDX, IDC_DATETIMEPICKER, m_DateTimePicker);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGotoDayDialog2, CBCGPDialog)
	//{{AFX_MSG_MAP(CGotoDayDialog2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CGotoDayDialog2::OnOK ()
{
	if (!UpdateData ())
	{
		return;
	}

	m_Date = m_DateTimePicker.GetDate();

	CBCGPDialog::OnOK ();
}

/////////////////////////////////////////////////////////////////////////////
// CGotoDayDialog2 message handlers

BOOL CGotoDayDialog2::OnInitDialog() 
{
	CBCGPDialog::OnInitDialog();
	
	m_DateTimePicker.SizeToContent();
	
	m_DateTimePicker.SetState (
		CBCGPDateTimeCtrl::DTM_DROPCALENDAR | 
		CBCGPDateTimeCtrl::DTM_DATE,
		CBCGPDateTimeCtrl::DTM_SPIN |
		CBCGPDateTimeCtrl::DTM_DROPCALENDAR | 
		CBCGPDateTimeCtrl::DTM_DATE |
		CBCGPDateTimeCtrl::DTM_TIME24H |
		CBCGPDateTimeCtrl::DTM_CHECKBOX |
		CBCGPDateTimeCtrl::DTM_TIME | 
		CBCGPDateTimeCtrl::DTM_TIME24HBYLOCALE);

	m_DateTimePicker.SetFirstDayOfWeek (m_nFirstDayOfWeek);

	m_DateTimePicker.SetDate (m_Date);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
