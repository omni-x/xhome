#ifndef _XHomeCommonDef_H__
#define _XHomeCommonDef_H__

enum XMode
{
    e_ModeUndefined	= -1,
    e_ModeHome      = 0,
    e_ModeMail		= 1,
    e_ModeCalendar	= 2,
    e_ModeTasks     = 3,
    e_ModeMacros	= 4,
    e_ModeGantt		= 5,
    e_ModeCustomer  = 6,
	e_ModeColorBlock= 7,
    e_modeUser      = 8, 
    e_ModeMax       = 9,
};

const int c_ViewCount = 9;
const LPCTSTR c_ViewNames[c_ViewCount] =
{
    _T("Home"), 
    _T("Mail"),
    _T("Calendar"),
    _T("Tasks"),
    _T("Macros"),
    _T("Gantt"),
    _T("�ͻ�"),
	_T("ɫ��"), 
    _T("����Ա")
};
const LPCTSTR c_ViewDescription[c_ViewCount] =
{
    _T("Welcome to BCGControlBar Pro Demonstration! Please click Ribbon Control tab to activate appropriate view."),
    _T("The current view demonstrates Report Control in read-only mode. You can organize the structure by using \"Field Chooser\" and \"Group By Box\".  Click \"Flag\" to set the message status."),
    _T("This view demonstrates fully functional Calendar (Planner) control. You can create/edit/remove appointments and recurring events."),
    _T("This view demonstrates usage of Database Grid control in read-only mode. You can organize the structure by using \"Field Chooser\" and \"Group By Box\"."),
    _T("This view demonstrates advanced Edit control that can be used in development environments. In addition, you can see how to use Office 2007-style mini-toolbar (\"floaty\") in order to manipulate selected text. You can see IntelliSense in action by typing \"System.\", \"Drawing.\" or \"IO.\" (case-sensitive!)"),
    _T("This view demonstrates Gantt control."),
    _T("This view demonstrates Customer control."),
	_T("This view demonstrates Color control."), 
    _T("��ǰ��ͼ��ʾ���ǲ���Ա��")
};

const int c_CategoryCount = 6;
const LPCTSTR c_CategoryNames[c_CategoryCount] =
{
    _T("Blue Category"), 
    _T("Green Category"), 
    _T("Orange Category"), 
    _T("Purple Category"), 
    _T("Red Category"), 
    _T("Yellow Category")
};
const COLORREF c_CategoryColors[c_CategoryCount] =
{
    RGB (118, 158, 218), 
    RGB (135, 210, 126),
    RGB (244, 152,  89),
    RGB (150, 124, 210),
    RGB (229, 104, 111),
    RGB (255, 249,  90)
};

const int c_ShowasCount = 4;
const LPCTSTR c_ShowasNames[c_ShowasCount] =
{
    _T("Free"), 
    _T("Tentative"), 
    _T("Busy"), 
    _T("Out of Office")
};
const COLORREF c_ShowasColors[c_ShowasCount] =
{
    CLR_DEFAULT, 
    RGB (128, 128, 255),
    RGB (  0,   0, 255),
    RGB (128,   0, 128)
};

enum
{
    ID_RIBBON_NEW = 40000,      //�½�
    ID_RIBBON_REMOVE ,          //ɾ��
    ID_RIBBON_FIND ,            //����
    ID_RIBBON_IMPORT ,          //����
    ID_RIBBON_EXPORT ,          //����

    IDC_CUSTOMER_BAR,           //��ϵ��
    IDC_COLORBLOCK_BAR,         //ɫ��
    IDC_USER_BAR,               //�û�   
};

#endif
