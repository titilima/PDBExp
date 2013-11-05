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

class CLbEx : public LListBox, protected LSubclassWnd
{
    PDL_DECLARE_WINCLASS(CLbEx)
public:
    CLbEx& operator=(__in HWND hWnd);
protected:
    void OnLButtonDblClk(UINT uFlags, int x, int y, BOOL& bHandled);
};

class CCmbEx : public CWindowImpl<CComboBox>
{
    PDL_DECLARE_WINCLASS(CCmbEx)
public:
    BOOL Create(__in PCTSTR lpWindowName, __in DWORD dwStyle,
        __in LPCRECT lpRect, __in HWND hWndParent, __in UINT nID,
        __in PVOID lpParam);
public:
    int FindString(__in LPCTSTR lpszString);
protected:
    void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags, BOOL& bHandled);
    void OnCommand(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL& bHandled);
private:
    CContainedWindow<CListBox> m_list;
    CEdit m_edit;
};

#endif // CMBEX_H
