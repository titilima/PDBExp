///////////////////////////////////////////////////////////////////////////////
// FileName:    Utilities.cpp
// Created:     2014/02/01
// Author:      titilima
// CopyRight:   Titi Studio (?) 2001-2014
//-----------------------------------------------------------------------------
// Information: Utilities functions/classes.
///////////////////////////////////////////////////////////////////////////////

#include "LvStd.h"
#include "Utilities.h"

void CopyToClipboard(HWND hOwner, const CComBSTR &str)
{
    HGLOBAL hMem = GlobalAlloc(GHND | GMEM_SHARE, (str.Length() + 1) * sizeof(WCHAR));
    PWSTR pStr = (PWSTR)GlobalLock(hMem);
    lstrcpyW(pStr, str);
    GlobalUnlock(hMem);
    OpenClipboard(hOwner);
    EmptyClipboard();
    SetClipboardData(CF_UNICODETEXT, hMem);
    CloseClipboard();
    GlobalFree(hMem);
}

bool IsEmpty(const CComBSTR &str)
{
    return NULL != str.m_str && str.Length() > 0;
}

int Window::GetText(HWND hWnd, String *strText)
{
    int nLength = GetWindowTextLength(hWnd);
    strText->resize(nLength);
    return GetWindowText(hWnd, const_cast<PTSTR>(strText->c_str()), nLength + 1);
}
