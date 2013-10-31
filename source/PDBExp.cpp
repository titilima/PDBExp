///////////////////////////////////////////////////////////////////////////////
// FileName:    PDBExp.cpp
// Created:     2007/10/28
// Author:      titilima
// CopyRight:   Titi Studio (?) 2001-2013
//-----------------------------------------------------------------------------
// Information: Program Entry
///////////////////////////////////////////////////////////////////////////////

#include "LvStd.h"
#include "MainFrame.h"
#include "Version.h"

#include "resource.h"

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, PTSTR, int nShowCmd)
{
    AtlInitCommonControls(ICC_WIN95_CLASSES);
    _Module.Init(NULL, hInstance);

    WNDCLASS wc = { 0 };
    wc.hbrBackground = PDL_SYSBRUSH(COLOR_BTNFACE);
    wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = theApp->LoadIcon(MAKEINTRESOURCE(IDI_MAIN_ICON));
    wc.hInstance = theApp->GetInstance();
    wc.lpszClassName = _T("PDBExp");
    wc.lpszMenuName = MAKEINTRESOURCE(IDR_MAIN_MENU);

    CMainFrame frameWnd(&wc);
    if (!frameWnd.Create(NULL, PDBEXP_WNDCAPTION,
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, NULL))
    {
        return -1;
    }

    frameWnd.CenterWindow(NULL, WNDPOS_HCENTER | WNDPOS_VCENTER);
    frameWnd.ShowWindow(nShowCmd);

    MSG msg;
    HACCEL hAccTable = LoadAccelerators(hInstance,
        MAKEINTRESOURCE(IDR_ACCELERATOR));
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (0 == TranslateAccelerator(frameWnd.GetSafeHWND(),
            hAccTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    _Module.Term();
    return (int)msg.wParam;
}
