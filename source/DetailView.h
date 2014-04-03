///////////////////////////////////////////////////////////////////////////////
// FileName:    DetailView.h
// Created:     2007/11/02
// Author:      titilima
// CopyRight:   Titi Studio (?) 2001-2014
//-----------------------------------------------------------------------------
// Information: Symbole Detail View Class
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 文件名：  DetailView.h
// 创建时间：2007-11-2
// 作者：    李马
// 版权所有：Titi Studio (?) 2001-2007
//-----------------------------------------------------------------------------
// 说明：    符号详细信息类
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <dia2.h>
#include <cvconst.h>
#include <ExDispid.h>

#include "DWebBrowserEvents2Info.hpp"

class CDetailView : public CAxWindow
                  , public IDocHostUIHandlerDispatch
                  , public IDispEventSimpleImpl<0, CDetailView, &DIID_DWebBrowserEvents2>
{
public:
    CDetailView(void);
public:
    void AddText(PCWSTR pszText);
    void Clear(void);
    void Copy(void);
    void CopyAll(void);
    IDiaSymbol* DetachCurrentSymbol(void);
    void EnableHyperLink(__in BOOL bEnable);
    void Finalize(void);
    IDiaSymbol* GetCurrentSymbol(void);
    BOOL GetText(string *pStr);
    void SetCurrentSymbol(__in IDiaSymbol* pCurSymbol);
public:
    BEGIN_SINK_MAP(CDetailView)
        SINK_ENTRY_INFO(0, DIID_DWebBrowserEvents2, DISPID_BEFORENAVIGATE2, BeforeNavigate2, &DWebBrowserEvents2Info::BeforeNavigate2)
        SINK_ENTRY_INFO(0, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE, DocumentComplete, &DWebBrowserEvents2Info::DocumentComplete)
    END_SINK_MAP()
private:
    void BeforeNavigate2(IDispatch *pDisp, VARIANT *url, VARIANT *Flags, VARIANT *TargetFrameName,
        VARIANT *PostData, VARIANT *Headers, VARIANT_BOOL *Cancel);
    void DocumentComplete(IDispatch *pDisp, VARIANT *URL);
private:
    // IUnknown
    STDMETHOD(QueryInterface)(REFIID riid, void **ppvObject);
    STDMETHOD_(ULONG, AddRef)(void);
    STDMETHOD_(ULONG, Release)(void);
    // IDispatch
    STDMETHOD(GetTypeInfoCount)(UINT *pctinfo);
    STDMETHOD(GetTypeInfo)(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo);
    STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid,
        DISPID *rgDispId);
    STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
        DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);
    // IDocHostUIHandlerDispatch
    STDMETHOD(ShowContextMenu)(DWORD dwID, DWORD x, DWORD y, IUnknown* pcmdtReserved,
        IDispatch* pdispReserved, HRESULT* dwRetVal);
    STDMETHOD(GetHostInfo)(PDWORD pdwFlags, PDWORD pdwDoubleClick);
    STDMETHOD(ShowUI)(DWORD dwID, IUnknown* pActiveObject, IUnknown* pCommandTarget,
        IUnknown* pFrame, IUnknown* pDoc, HRESULT* dwRetVal);
    STDMETHOD(HideUI)(void);
    STDMETHOD(UpdateUI)(void);
    STDMETHOD(EnableModeless)(VARIANT_BOOL fEnable);
    STDMETHOD(OnDocWindowActivate)(VARIANT_BOOL fActivate);
    STDMETHOD(OnFrameWindowActivate)(VARIANT_BOOL fActivate);
    STDMETHOD(ResizeBorder)(long left, long top, long right, long bottom, IUnknown* pUIWindow,
        VARIANT_BOOL fFrameWindow);
    STDMETHOD(TranslateAccelerator)(DWORD_PTR hWnd, DWORD nMessage, DWORD_PTR wParam,
        DWORD_PTR lParam, BSTR bstrGuidCmdGroup, DWORD nCmdID, HRESULT* dwRetVal);
    STDMETHOD(GetOptionKeyPath)(BSTR* pbstrKey, DWORD dw);
    STDMETHOD(GetDropTarget)(IUnknown* pDropTarget, IUnknown** ppDropTarget);
    STDMETHOD(GetExternal)(IDispatch** ppDispatch);
    STDMETHOD(TranslateUrl)(DWORD dwTranslate, BSTR bstrURLIn, BSTR* pbstrURLOut);
    STDMETHOD(FilterDataObject)(IUnknown* pDO, IUnknown** ppDORet);
private:
    CComPtr<IDiaSymbol> m_pCurSymbol;
};
