///////////////////////////////////////////////////////////////////////////////
// FileName:    DWebBrowserEvents2Info.hpp
// Created:     2014/04/03
// Author:      titilima
// CopyRight:   Titi Studio (?) 2001-2014
//-----------------------------------------------------------------------------
// Information: DWebBrowserEvents2 Helpers for SINK_ENTRY_INFO
///////////////////////////////////////////////////////////////////////////////

#ifndef DWEBBROWSEREVENTS2INFO_HPP
#define DWEBBROWSEREVENTS2INFO_HPP

#pragma once

class DWebBrowserEvents2Info
{
public:
    static _ATL_FUNC_INFO BeforeNavigate2;
    static _ATL_FUNC_INFO DocumentComplete;
    static _ATL_FUNC_INFO NewWindow2;
    static _ATL_FUNC_INFO TitleChange;
};

__declspec(selectany) _ATL_FUNC_INFO DWebBrowserEvents2Info::BeforeNavigate2 = {
    CC_STDCALL, VT_EMPTY, 7,
    {
        VT_DISPATCH,
        VT_VARIANT | VT_BYREF,
        VT_VARIANT | VT_BYREF,
        VT_VARIANT | VT_BYREF,
        VT_VARIANT | VT_BYREF,
        VT_VARIANT | VT_BYREF,
        VT_BOOL | VT_BYREF
    }
};

__declspec(selectany) _ATL_FUNC_INFO DWebBrowserEvents2Info::DocumentComplete = {
    CC_STDCALL, VT_EMPTY, 2, { VT_DISPATCH, VT_BYREF | VT_VARIANT }
};

__declspec(selectany) _ATL_FUNC_INFO DWebBrowserEvents2Info::NewWindow2 = {
    CC_STDCALL, VT_EMPTY, 2, { VT_BYREF | VT_DISPATCH, VT_BYREF | VT_BOOL }
};

__declspec(selectany) _ATL_FUNC_INFO DWebBrowserEvents2Info::TitleChange = {
    CC_STDCALL, VT_EMPTY, 1, { VT_BSTR }
};

#endif // DWEBBROWSEREVENTS2INFO_HPP
