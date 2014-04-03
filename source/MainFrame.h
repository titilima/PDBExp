///////////////////////////////////////////////////////////////////////////////
// FileName:    MainFrame.h
// Created:     2007/10/28
// Author:      titilima
// CopyRight:   Titi Studio (?) 2001-2007
//-----------------------------------------------------------------------------
// Information: Main Frame Window Class
///////////////////////////////////////////////////////////////////////////////

#ifndef MAINFRAME_H
#define MAINFRAME_H

#pragma once

#include <list>

#include <atlsplit.h>

#include "CmbEx.h"
#include "DetailView.h"
#include "DiaHelper.h"
#include "DownLoader.h"
#include "DWebBrowserEvents2Info.hpp"

typedef struct _tagExpInfo {
    IDiaSymbol* pSymbol;
} EXPINFO, *PEXPINFO;

typedef CWinTraits<WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS> PDBExpFrame;

class CMainFrame : public CWindowImpl<CMainFrame, CWindow, PDBExpFrame>
                 , public IDispEventSimpleImpl<0, CMainFrame, &DIID_DWebBrowserEvents2>
{
public:
    CMainFrame(void);
    ~CMainFrame(void);
    DECLARE_WND_CLASS_EX(_T("PDBExp"), 0, COLOR_BTNFACE)
private:
    void AddExpItem(__in IDiaSymbol* pSymbol);
    static BOOL cbAddEnum(IDiaSymbol* pCurSymbol, LPVOID pParam);
    static BOOL cbAddTypedef(IDiaSymbol* pCurSymbol, LPVOID pParam);
    static BOOL cbAddUDT(IDiaSymbol* pCurSymbol, LPVOID pParam);
    static void cbDumpString(LPCWSTR pszString, LPVOID pParam);
    void CheckCommandState(void);
    static void DestroyExpItem(PVOID ptr);
    void DumpSymbol(__in IDiaSymbol* pSymbol);
    void Open(__in LPCWSTR pszPdbFile);
    void Refresh(void);
public:
    BEGIN_MSG_MAP_EX(CMainFrame)
    END_MSG_MAP()
    BEGIN_SINK_MAP(CMainFrame)
        SINK_ENTRY_INFO(0, DIID_DWebBrowserEvents2, DISPID_BEFORENAVIGATE2, BeforeNavigate2, &DWebBrowserEvents2Info::BeforeNavigate2)
        SINK_ENTRY_INFO(0, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE, DocumentComplete, &DWebBrowserEvents2Info::DocumentComplete)
    END_SINK_MAP()
private:
    int OnCreate(LPCREATESTRUCT lpCreateStruct, BOOL& bHandled);
    void OnDestroy(BOOL& bHandled);
    void OnDropFiles(HDROP hDropInfo, BOOL& bHandled);
    virtual void OnFinalMessage(HWND /* hWnd */) { delete this; }
    void OnSize(UINT nType, int cx, int cy, BOOL& bHandled);
private:
    void BeforeNavigate2(IDispatch *pDisp, VARIANT *url, VARIANT *Flags, VARIANT *TargetFrameName,
        VARIANT *PostData, VARIANT *Headers, VARIANT_BOOL *Cancel);
    void DocumentComplete(IDispatch *pDisp, VARIANT *URL);
private:
    void OnCommand(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL& bHandled);
    void OnAbout(void);
    void OnBack(void);
    void OnCopy(void);
    void OnCopyAll(void);
    void OnExit(void);
    void OnModify(void);
    void OnNext(void);
    void OnOk(void);
    void OnOpen(void);
    void OnSave(void);
    void OnSetting(void);
    void OnDownLoad(void);
private:
    void OnSymbolChange(DWORD id);
    void OnNewFileDrop(LPCWSTR lpFileName);
private:
    HFONT m_hFont;
    CToolBarCtrl m_tb;
    CImageList m_iml;
    CCmbEx m_cbSymbols;
    CDetailView m_vDetail;
    CSplitterWindow m_split;
    CStatusBarCtrl m_status;
    CDiaHelper m_dia;
    std::wstring m_wsIni;
    std::list<EXPINFO> m_lstHistory;
    std::list<EXPINFO>::iterator m_itCurrent;
    int m_nMaxHistory;
    CDownLoader m_DnLdr;
};

#endif // MAINFRAME_H
