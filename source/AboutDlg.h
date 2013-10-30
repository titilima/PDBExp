///////////////////////////////////////////////////////////////////////////////
// FileName:    AboutDlg.h
// Created:     2007/11/12
// Author:      titilima
// CopyRight:   Titi Studio (?) 2001-2013
//-----------------------------------------------------------------------------
// Information: About Dialog
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <atlctrlx.h>

class CAboutDlg : public CDialogImpl<CAboutDlg>, public CWinDataExchange<CAboutDlg>
{
public:
    CAboutDlg(void);
    enum { IDD = IDD_DLG_ABOUT };
public:
    BEGIN_MSG_MAP_EX(CAboutDlg)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_INITDIALOG(OnInitDialog)

        COMMAND_ID_HANDLER_EX(IDCANCEL, OnOKCancel)
        COMMAND_ID_HANDLER_EX(IDOK, OnOKCancel)
    END_MSG_MAP()
    BEGIN_DDX_MAP(CAboutDlg)
        DDX_CONTROL(IDC_ST_HOMEPAGE, m_stHome)
        DDX_CONTROL(IDC_ST_MAIL, m_stMail)
    END_DDX_MAP()
private:
    BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);
    void OnLButtonDown(UINT nFlags, CPoint point);
    void OnMouseMove(UINT nFlags, CPoint point);
    void OnOKCancel(UINT uNotifyCode, int nID, CWindow wndCtl);
private:
    CHyperLink m_stHome;
    CHyperLink m_stMail;
};
