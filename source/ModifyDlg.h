///////////////////////////////////////////////////////////////////////////////
// 文件名：  ModifyDlg.h
// 创建时间：2007-11-11
// 作者：    李马
// 版权所有：Titi Studio (?) 2001-2007
//-----------------------------------------------------------------------------
// 说明：    整理对话框
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "DiaHelper.h"
#include "DetailView.h"

#include "resource.h"

class CModifyDlg : public CDialogImpl<CModifyDlg>
{
public:
    CModifyDlg(CDiaHelper* pDia, IDiaSymbol* pSymbol);
    enum { IDD = IDD_DLG_MODIFY };
private:
    static BOOL cbAddMember(IDiaSymbol* pCurSymbol, LPVOID pParam);
    static BOOL cbEnumModify(IDiaSymbol* pCurSymbol, LPVOID pParam);
    void DumpModified(void);
private:
    LRESULT OnNotify(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
private:
    void OnCommand(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL& bHandled);
    void OnBtnAll(void);
    void OnBtnCopy(void);
private:
    void OnClose(BOOL& bHandled);
    BOOL OnInitDialog(HWND hCtrlFocus, LPARAM lParam, BOOL& bHandled);
private:
    void OnDocumentComplete(void);
private:
    CListViewCtrl m_list;
    CDetailView m_view;
    IDiaSymbol* m_pSymbol;
    CDiaHelper* m_pDia;
    BOOL m_bInited;
};
