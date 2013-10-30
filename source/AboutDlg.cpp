///////////////////////////////////////////////////////////////////////////////
// FileName:    AboutDlg.cpp
// Created:     2007/11/12
// Author:      titilima
// CopyRight:   Titi Studio (?) 2001-2013
//-----------------------------------------------------------------------------
// Information: About Dialog
///////////////////////////////////////////////////////////////////////////////

#include "LvStd.h"
#include "AboutDlg.h"
#include "Version.h"
#include <ShellAPI.h>

CAboutDlg::CAboutDlg(void)
{
    //
}

///////////////////////////////////////////////////////////////////////////////

BOOL CAboutDlg::OnInitDialog(CWindow, LPARAM)
{
    DoDataExchange();

    CWindow wndVer = GetDlgItem(IDC_ST_VER);
    wndVer.SetWindowText(PDBEXP_WNDCAPTION);

    return FALSE;
}

void CAboutDlg::OnLButtonDown(UINT, CPoint point)
{
    SendMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
}

void CAboutDlg::OnOKCancel(UINT, int, CWindow)
{
    EndDialog(IDOK);
}
