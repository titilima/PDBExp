///////////////////////////////////////////////////////////////////////////////
// FileName:    CmbEx.h
// Created:     2013/11/05
// Author:      titilima
// CopyRight:   Titi Studio (?) 2001-2013
//-----------------------------------------------------------------------------
// Information: PDB Explorer ComboBox
///////////////////////////////////////////////////////////////////////////////

#ifndef CMBEX_H
#define CMBEX_H

#pragma once

class CCmbEx : public CWindowImpl<CCmbEx, CComboBox>
{
public:
    CCmbEx(void);
    DECLARE_WND_CLASS(_T("PDBExp_ComboBox"))
public:
    BOOL Create(DWORD dwStyle, LPRECT lpRect, HWND hWndParent, UINT nID);
public:
    int FindString(PCTSTR lpszString);
public:
    BEGIN_MSG_MAP_EX(CCmbEx)
        MSG_WM_KEYDOWN(OnKeyDown)
        COMMAND_CODE_HANDLER_EX(EN_UPDATE, OnEditUpdate)
    ALT_MSG_MAP(1)
        MSG_WM_LBUTTONDBLCLK(OnListLButtonDblClk)
    END_MSG_MAP()
private:
    void OnEditUpdate(UINT uNotifyCode, int nID, CWindow wndCtl);
    void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    void OnListLButtonDblClk(UINT nFlags, CPoint point);
private:
    CContainedWindowT<CListBox> m_list;
    CEdit m_edit;
};

#endif // CMBEX_H
