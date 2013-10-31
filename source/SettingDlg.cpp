///////////////////////////////////////////////////////////////////////////////
// FileName:    SettingDlg.cpp
// Created:     2007/11/12
// Author:      titilima
// CopyRight:   Titi Studio (?) 2001-2013
//-----------------------------------------------------------------------------
// Information: Settings Dialog
///////////////////////////////////////////////////////////////////////////////

#include "LvStd.h"
#include "SettingDlg.h"
#include <atldlgs.h>

static const TCHAR szSec_Setting[] = _T("Setting");
static const TCHAR szKey_Template[] = _T("Template");
static const TCHAR szKey_MaxHistory[] = _T("MaxHistory");

CSettingDlg::CSettingDlg(void)
{
    // Nothing
}

///////////////////////////////////////////////////////////////////////////////

void CSettingDlg::OnClose(void)
{
    EndDialog(IDCANCEL);
}

BOOL CSettingDlg::OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
{
    DoDataExchange();

    TCHAR str[MAX_PATH];
    GetPrivateProfileString(szSec_Setting, szKey_Template, _T(""), str, MAX_PATH, g_strIni.c_str());
    SetDlgItemText(IDC_EDT_TEMPLATE, str);

    int cnt = GetPrivateProfileInt(szSec_Setting, szKey_MaxHistory, 20, g_strIni.c_str());
    if (cnt < 10)
        cnt = 10;
    if (30 < cnt)
        cnt = 30;
    SetDlgItemInt(IDC_EDT_EXPCNT, cnt, FALSE);

    m_spin = GetDlgItem(IDC_SPIN);
    m_spin.SetBuddy(GetDlgItem(IDC_EDT_EXPCNT));
    m_spin.SetRange32(10, 30);
    m_spin.SetPos32(cnt);

    return FALSE;
}

void CSettingDlg::OnOKCancel(UINT, int nID, CWindow)
{
    if (IDOK == nID) {
        TCHAR str[MAX_PATH];
        GetDlgItemText(IDC_EDT_TEMPLATE, str, MAX_PATH);
        if (_T('\0') != str[0]) {
            WritePrivateProfileString(szSec_Setting, szKey_Template, str, g_strIni.c_str());
        }

        wsprintf(str, _T("%d"), GetDlgItemInt(IDC_EDT_EXPCNT, NULL, FALSE));
        WritePrivateProfileString(szSec_Setting, szKey_MaxHistory, str, g_strIni.c_str());
    }
    EndDialog(nID);
}

void CSettingDlg::OnOpen(UINT, int, CWindow)
{
    CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("*.htm;*.html\0*.htm;*.html\0\0"));
    if (dlg.DoModal(m_hWnd)) {
        SetDlgItemText(IDC_EDT_TEMPLATE, dlg.m_szFileName);
    }
}
