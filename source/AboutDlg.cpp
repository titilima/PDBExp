///////////////////////////////////////////////////////////////////////////////
// 文件名：  AboutDlg.cpp
// 创建时间：2007-11-12
// 作者：    李马
// 版权所有：Titi Studio (?) 2001-2007
//-----------------------------------------------------------------------------
// 说明：    关于对话框实现
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
