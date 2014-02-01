///////////////////////////////////////////////////////////////////////////////
// FileName:    CmbEx.cpp
// Created:     2007/10/28
// Author:      titilima
// CopyRight:   Titi Studio (?) 2001-2007
//-----------------------------------------------------------------------------
// Information: PDB Explorer ComboBox
///////////////////////////////////////////////////////////////////////////////

#include "LvStd.h"
#include "CmbEx.h"
#include "Utilities.h"

typedef CWindowImpl<CCmbEx, CComboBox> BaseComboBox;

CCmbEx::CCmbEx(void) : m_list(this, 1)
{
    // Nothing
}

BOOL CCmbEx::Create(DWORD dwStyle, LPRECT lpRect, HWND hWndParent, UINT nID)
{
    if (NULL == BaseComboBox::Create(hWndParent, *lpRect, NULL, dwStyle, 0, nID)) {
        ATLASSERT(false);
        return FALSE;
    }

    m_list.SubclassWindow(FindWindowEx(m_hWnd, NULL, _T("ComboLBox"), NULL));
    m_edit = FindWindowEx(m_hWnd, NULL, WC_EDIT, NULL);

    return TRUE;
}

int CCmbEx::FindString(PCTSTR lpszString)
{
    // CComboBoxT::FindString will create the item if not found.
    // So use CListBoxT::FindString instead.
    return m_list.FindString(0, lpszString);
}

///////////////////////////////////////////////////////////////////////////////

void CCmbEx::OnEditUpdate(UINT, int, CWindow wndCtl)
{
    ATLASSERT(m_edit.m_hWnd == wndCtl.m_hWnd);

    String str;
    int nLength = Window::GetText(m_edit, &str);
    if (nLength > 0) {
        int idx = FindString(str.c_str());
        if (CB_ERR != idx) {
            // Must use CListBoxT::SetCurSel,
            // because CComboBoxT::SetCurSel will change edit's text.
            m_list.SetCurSel(idx);
            m_edit.SetSel(nLength, -1);
        }
    }
}

void CCmbEx::OnKeyDown(UINT nChar, UINT, UINT)
{
    if (VK_RETURN == nChar) {
        GetParent().SendMessage(WM_COMMAND, IDOK, reinterpret_cast<LPARAM>(m_hWnd));
    } else {
        SetMsgHandled(FALSE);
    }
}

void CCmbEx::OnListLButtonDblClk(UINT, CPoint)
{
    GetParent().SendMessage(WM_COMMAND, IDOK, (LPARAM)m_hWnd);
}
