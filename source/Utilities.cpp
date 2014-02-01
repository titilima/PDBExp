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

int Window::GetText(HWND hWnd, String *strText)
{
    int nLength = GetWindowTextLength(hWnd);
    strText->resize(nLength);
    return GetWindowText(hWnd, const_cast<PTSTR>(strText->c_str()), nLength + 1);
}
