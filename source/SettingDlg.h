///////////////////////////////////////////////////////////////////////////////
// FileName:    SettingDlg.h
// Created:     2007/11/12
// Author:      titilima
// CopyRight:   Titi Studio (?) 2001-2013
//-----------------------------------------------------------------------------
// Information: Settings Dialog
///////////////////////////////////////////////////////////////////////////////

#ifndef SETTINGDLG_H
#define SETTINGDLG_H

#pragma once

class CSettingDlg : public CDialogImpl<CSettingDlg>, public CWinDataExchange<CSettingDlg>
{
public:
    CSettingDlg(void);
    enum { IDD = IDD_DLG_SETTING };
public:
    BEGIN_MSG_MAP_EX(CSettingDlg)
        MSG_WM_CLOSE(OnClose)
        MSG_WM_INITDIALOG(OnInitDialog)

        COMMAND_ID_HANDLER_EX(IDCANCEL, OnOKCancel)
        COMMAND_ID_HANDLER_EX(IDOK, OnOKCancel)
        COMMAND_ID_HANDLER_EX(IDC_BTN_OPEN, OnOpen)
    END_MSG_MAP()
    BEGIN_DDX_MAP(CSettingDlg)
        DDX_CONTROL_HANDLE(IDC_SPIN, m_spin)
    END_DDX_MAP()
private:
    void OnClose(void);
    BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam);
    void OnOKCancel(UINT uNotifyCode, int nID, CWindow wndCtl);
    void OnOpen(UINT uNotifyCode, int nID, CWindow wndCtl);
private:
    CUpDownCtrl m_spin;
};

#endif // SETTINGDLG_H
