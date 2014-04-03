///////////////////////////////////////////////////////////////////////////////
// FileName:    DetailView.cpp
// Created:     2007/11/02
// Author:      titilima
// CopyRight:   Titi Studio (?) 2001-2014
//-----------------------------------------------------------------------------
// Information: Symbole Detail View Class
///////////////////////////////////////////////////////////////////////////////

#include "LvStd.h"
#include "DetailView.h"
#include "Utilities.h"

static HRESULT GetDocument(CDetailView *dv, IDispatch **ppDoc)
{
    CComPtr<IWebBrowser2> wb2;
    HRESULT hr = dv->QueryControl(&wb2);
    if (FAILED(hr)) {
        return hr;
    }

    return wb2->get_Document(ppDoc);
}

static HRESULT GetBody(CDetailView *dv, IHTMLElement **ppBody)
{
    AdapterPtr<IHTMLDocument2, IDispatch> doc;
    HRESULT hr = GetDocument(dv, &doc);
    if (FAILED(hr)) {
        return hr;
    }

    return doc->get_body(ppBody);
}

CDetailView::CDetailView(void)
{
    // Nothing
}

void CDetailView::AddText(PCWSTR pszText)
{
    CComPtr<IHTMLElement> body;
    if (SUCCEEDED(GetBody(this, &body))) {
        CComBSTR bsText(pszText);
        body->insertAdjacentHTML(CComBSTR("beforeEnd"), bsText);
    }
}

void CDetailView::Clear(void)
{
    CComPtr<IHTMLElement> body;
    if (SUCCEEDED(GetBody(this, &body))) {
        body->put_innerText(CComBSTR());
    }

    SetCurrentSymbol(NULL);
}

void CDetailView::Copy(void)
{
    AdapterPtr<IHTMLDocument2, IDispatch> doc;
    if (FAILED(GetDocument(this, &doc))) {
        return;
    }

    CComPtr<IHTMLSelectionObject> pSel;
    doc->get_selection(&pSel);

    AdapterPtr<IHTMLTxtRange, IDispatch> pTxt;
    pSel->createRange(&pTxt);

    CComBSTR bsSel;
    pTxt->get_text(&bsSel);
    if (!IsEmpty(bsSel)) {
        CopyToClipboard(*this, bsSel);
    }
}

void CDetailView::CopyAll(void)
{
    CComPtr<IHTMLElement> body;
    if (SUCCEEDED(GetBody(this, &body))) {
        CComBSTR bsSel;
        body->get_innerText(&bsSel);
        if (!IsEmpty(bsSel)) {
            CopyToClipboard(*this, bsSel);
        }
    }
}

IDiaSymbol* CDetailView::DetachCurrentSymbol(void)
{
    IDiaSymbol* pRet = m_pCurSymbol;
    m_pCurSymbol     = NULL;
    return pRet;
}

void CDetailView::Finalize(void)
{
    m_pCurSymbol.Release();
}

IDiaSymbol* CDetailView::GetCurrentSymbol(void)
{
    return m_pCurSymbol;
}

BOOL CDetailView::GetText(string *pStr)
{
    CComPtr<IWebBrowser2> wb2;
    QueryControl(&wb2);

    AdapterPtr<IHTMLDocument2, IDispatch> doc;
    wb2->get_Document(&doc);

    AdapterPtr<IHTMLElement, IHTMLElement> body;
    doc->get_body(&body);

    CComBSTR bsSel;
    body->get_innerText(&bsSel);

    USES_CONVERSION;
    pStr->assign(W2CA(bsSel));
    return !pStr->empty();
}

void CDetailView::SetCurrentSymbol(__in IDiaSymbol* pCurSymbol)
{
    m_pCurSymbol = pCurSymbol;
}

///////////////////////////////////////////////////////////////////////////////

#if 0

int CDetailView::OnCreate(LPCREATESTRUCT lpCreateStruct, BOOL& bHandled)
{
    CreateAxCtrl(CLSID_WebBrowser);
    Connect(DIID_DWebBrowserEvents2);

    QueryCtrl(IID_IWebBrowser2, (PVOID*)&m_pWB2);

    RECT rc;
    GetClientRect(&rc);
    m_pWB2->put_Left(rc.left);
    m_pWB2->put_Top(rc.top);
    m_pWB2->put_Width(rc.right);
    m_pWB2->put_Height(rc.bottom);

    WCHAR strExe[MAX_PATH];
    ::GetModuleFileNameW(NULL, strExe, MAX_PATH);

    LStringW strPage;
    strPage.Attach((PWSTR)lpCreateStruct->lpCreateParams);
    if (0 == strPage.GetLength())
        strPage.Format(L"res://%s/%d", strExe, IDR_HTML);

    LVariant url = strPage;
    m_pWB2->Navigate2(&url, NULL, NULL, NULL, NULL);

    CComPtr<IDispatch> pDisp = NULL;
    m_pWB2->get_Document(&pDisp);
    m_pDoc = pDisp;
    return 0;
}

#endif

///////////////////////////////////////////////////////////////////////////////

#if 0

void CDetailView::BeforeNavigate2(
    IDispatch *pDisp,
    VARIANT *url,
    VARIANT *Flags,
    VARIANT *TargetFrameName,
    VARIANT *PostData,
    VARIANT *Headers,
    VARIANT_BOOL *Cancel)
{
    *Cancel = VARIANT_TRUE;

    if (NULL == m_pEventHandler || !m_bEnable) {
        return;
    }

    if (PathFileExistsW(url->bstrVal)) {
        m_pEventHandler->OnNewFileDrop(url->bstrVal);
    } else {
        if (0 == wcsncmp(url->bstrVal, L"sym://", 6)) {
            DWORD id = _wtoi(url->bstrVal + 6);
            m_pEventHandler->OnSymbolChange(id);
        }
    }
}

void CDetailView::DocumentComplete(IDispatch *pDisp, VARIANT *URL)
{
    if (NULL != m_pEventHandler) {
        m_pEventHandler->OnDocumentComplete();
    }
}

#endif

///////////////////////////////////////////////////////////////////////////////

// IDocHostUIHandlerDispatch

STDMETHODIMP CDetailView::ShowContextMenu(
    DWORD dwID,
    DWORD x, DWORD y,
    IUnknown* pcmdtReserved,
    IDispatch* pdispReserved,
    HRESULT* dwRetVal)
{
    return E_NOTIMPL;
}

STDMETHODIMP CDetailView::GetHostInfo(PDWORD pdwFlags, PDWORD pdwDoubleClick)
{
    return E_NOTIMPL;
}

STDMETHODIMP CDetailView::ShowUI(
    DWORD dwID,
    IUnknown* pActiveObject,
    IUnknown* pCommandTarget,
    IUnknown* pFrame,
    IUnknown* pDoc,
    HRESULT* dwRetVal)
{
    return E_NOTIMPL;
}

STDMETHODIMP CDetailView::HideUI(void)
{
    return E_NOTIMPL;
}

STDMETHODIMP CDetailView::UpdateUI(void)
{
    return E_NOTIMPL;
}

STDMETHODIMP CDetailView::EnableModeless(VARIANT_BOOL fEnable)
{
    return E_NOTIMPL;
}

STDMETHODIMP CDetailView::OnDocWindowActivate(VARIANT_BOOL fActivate)
{
    return E_NOTIMPL;
}

STDMETHODIMP CDetailView::OnFrameWindowActivate(VARIANT_BOOL fActivate)
{
    return E_NOTIMPL;
}

STDMETHODIMP CDetailView::ResizeBorder(
    long left, long top, long right, long bottom,
    IUnknown* pUIWindow,
    VARIANT_BOOL fFrameWindow)
{
    return E_NOTIMPL;
}

STDMETHODIMP CDetailView::TranslateAccelerator(
    DWORD_PTR hWnd,
    DWORD nMessage,
    DWORD_PTR wParam,
    DWORD_PTR lParam,
    BSTR bstrGuidCmdGroup,
    DWORD nCmdID,
    HRESULT* dwRetVal)
{
    return E_NOTIMPL;
}

STDMETHODIMP CDetailView::GetOptionKeyPath(BSTR* pbstrKey, DWORD dw)
{
    return E_NOTIMPL;
}

STDMETHODIMP CDetailView::GetDropTarget(IUnknown* pDropTarget, IUnknown** ppDropTarget)
{
    return E_NOTIMPL;
}

STDMETHODIMP CDetailView::GetExternal(IDispatch** ppDispatch)
{
    return E_NOTIMPL;
}

STDMETHODIMP CDetailView::TranslateUrl(DWORD dwTranslate, BSTR bstrURLIn, BSTR* pbstrURLOut)
{
    return E_NOTIMPL;
}

STDMETHODIMP CDetailView::FilterDataObject(IUnknown* pDO, IUnknown** ppDORet)
{
    return E_NOTIMPL;
}
