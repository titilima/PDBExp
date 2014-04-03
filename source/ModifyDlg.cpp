///////////////////////////////////////////////////////////////////////////////
// 文件名：  ModifyDlg.cpp
// 创建时间：2007-11-11
// 作者：    李马
// 版权所有：Titi Studio (?) 2001-2007
//-----------------------------------------------------------------------------
// 说明：    整理对话框实现
///////////////////////////////////////////////////////////////////////////////

#include "LvStd.h"
#include "ModifyDlg.h"
#include "SymWrap.h"

typedef struct _tagModifyParam {
    CModifyDlg* This;    // 对话框指针
    enum SymTagEnum tag; // 导出符号的类型
    int idx;             // 当前枚举的成员索引
    int idxUseless;      // useless 项索引
    LONG offset;         // useless 项偏移量
    wstring str;         // 成员字符串
} MODIFYPARAM, *PMODIFYPARAM;

CModifyDlg::CModifyDlg(CDiaHelper* pDia, IDiaSymbol* pSymbol)
{
    m_pDia = pDia;
    m_pSymbol = pSymbol;
    m_bInited = FALSE;
}

BOOL CModifyDlg::cbAddMember(IDiaSymbol* pCurSymbol, PVOID pParam)
{
    CModifyDlg* pThis = (CModifyDlg*)pParam;

    CComBSTR bsName;
    pCurSymbol->get_name(&bsName);

    USES_CONVERSION;
    int cnt = pThis->m_list.GetItemCount();
    int idx = pThis->m_list.InsertItem(cnt, W2CT(bsName));

    TCHAR buf[32];
    LONG lOffset = 0;
    pCurSymbol->get_offset(&lOffset);
    wsprintf(buf, _T("+0x%x"), lOffset);
    pThis->m_list.SetItemText(idx, 1, buf);

    ULONGLONG ulSize = 0;
    SymPtr pType;
    pCurSymbol->get_type(&pType);
    pType->get_length(&ulSize);
    wsprintf(buf, _T("0x%x"), static_cast<DWORD>(ulSize));
    pThis->m_list.SetItemText(idx, 2, buf);

    pThis->m_list.SetCheckState(idx, TRUE);
    return FALSE;
}

BOOL CModifyDlg::cbEnumModify(IDiaSymbol* pCurSymbol, LPVOID pParam)
{
    PMODIFYPARAM p = (PMODIFYPARAM)pParam;

    if (SymTagEnum == p->tag) {
        if (p->This->m_list.GetCheckState(p->idx)) {
            CComVariant v;
            CComBSTR bsName;
            pCurSymbol->get_name(&bsName);
            pCurSymbol->get_value(&v);

            WCHAR buf[32];
            wsprintfW(buf, L"%x", v.intVal);
            p->str.append(L"&nbsp;&nbsp;&nbsp;&nbsp;");
            p->str.append(bsName);
            p->str.append(L" = 0x");
            p->str.append(buf);
            p->str.append(L";<br />\r\n");
        }
        ++p->idx;
        return FALSE;
    }

    if (p->This->m_list.GetCheckState(p->idx)) {
        // 输出先前积攒的 useless 项
        LONG offset;
        pCurSymbol->get_offset(&offset);
        LONG size = offset - p->offset;
        if (-1 != p->offset) {
            WCHAR buf[32];
            p->str.append(L"&nbsp;&nbsp;&nbsp;&nbsp;BYTE useless");
            wsprintfW(buf, L"%d[%d]", p->idxUseless, size);
            p->str.append(buf);
            p->str.append(L"; <font class=\"comment\">// +0x");
            wsprintfW(buf, L"%x(%0x)", p->offset, size);
            p->str.append(buf);
            p->str.append(L"</font><br />");

            ++p->idxUseless;
            p->offset = -1;
        }

        wstring str;
        CSym* sym = CSym::NewSym(pCurSymbol);
        sym->Format(&str);
        p->str += str;
        CSym::Delete(sym);
    }
    else
    {
        // 积攒 useless 项
        if (-1 == p->offset)
            pCurSymbol->get_offset(&p->offset);
    }

    ++p->idx;
    return FALSE;
}

void CModifyDlg::DumpModified(void)
{
    m_view.Clear();

    wstring str;
    CSym* sym = CSym::NewSym(m_pSymbol);
    sym->GetHeader(&str);
    CSym::Delete(sym);
    m_view.AddText(str.c_str());

    MODIFYPARAM mp;
    mp.This = this;
    m_pSymbol->get_symTag((PDWORD)&mp.tag);
    mp.idx = 0;
    mp.idxUseless = 0;
    mp.offset = -1;
    CSym::Enum(m_pSymbol, SymTagData, cbEnumModify, &mp);
    m_view.AddText(mp.str.c_str());

    // 剩余的 useless 项目
    if (-1 != mp.offset) {
        ULONGLONG size;
        m_pSymbol->get_length(&size);
        size -= mp.offset;
        str = L"&nbsp;&nbsp;&nbsp;&nbsp;BYTE useless";

        WCHAR buf[32];
        wsprintfW(buf, L"%d[%d]", mp.idxUseless, static_cast<DWORD>(size));
        str.append(buf);
        str.append(L"; <font class=\"comment\">// +0x");
        wsprintfW(buf, L"%x(%0x)", mp.offset, static_cast<DWORD>(size));
        str.append(buf);
        str.append(L"</font><br />");

        m_view.AddText(str.c_str());
    }

    m_view.AddText(L"};");
}

///////////////////////////////////////////////////////////////////////////////

#if 0

LRESULT CModifyDlg::OnNotify(
    int idCtrl,
    LPNMHDR pnmh,
    BOOL& bHandled)
{
    if (m_bInited && LVN_ITEMCHANGED == pnmh->code && IDC_LIST == pnmh->idFrom)
    {
        DumpModified();
        return 0;
    }
    else
    {
        bHandled = FALSE;
        return LDialog::OnNotify(idCtrl, pnmh, bHandled);
    }
}

#endif

///////////////////////////////////////////////////////////////////////////////

void CModifyDlg::OnCommand(
    WORD wNotifyCode,
    WORD wID,
    HWND hWndCtrl,
    BOOL& bHandled)
{
    switch (wID)
    {
    case IDCANCEL:
    case IDOK:          OnClose(bHandled);      break;
    case IDC_BTN_ALL:   OnBtnAll();             break;
    case IDC_BTN_COPY:  OnBtnCopy();            break;
    default:
        bHandled = FALSE;
    }
}

void CModifyDlg::OnBtnAll(void)
{
    m_bInited = FALSE;

    BOOL bSel = TRUE;
    int  cnt  = m_list.GetItemCount();
    for (int i = 0; i < cnt; ++i)
    {
        if (!m_list.GetCheckState(i))
        {
            bSel = FALSE;
            break;
        }
    }

    bSel = !bSel;
    for (int i = 0; i < cnt; ++i)
        m_list.SetCheckState(i, bSel);

    m_bInited = TRUE;
    DumpModified();
}

void CModifyDlg::OnBtnCopy(void)
{
    m_view.CopyAll();
    MessageBox(_T("所有文本已复制到剪贴板。"), _T("PDB Explorer"),
        MB_ICONINFORMATION);
}

///////////////////////////////////////////////////////////////////////////////

void CModifyDlg::OnClose(BOOL& bHandled)
{
    EndDialog(IDOK);
}

BOOL CModifyDlg::OnInitDialog(HWND hCtrlFocus, LPARAM lParam, BOOL& bHandled)
{
    wstring str;

    CComBSTR bsName;
    m_pSymbol->get_name(&bsName);
    str = L"Modify Symbols of ";
    str.append(bsName);
    SetWindowTextW(str.c_str());

    // 初始化列表
    m_list = GetDlgItem(IDC_LIST);
    m_list.InsertColumn(0, _T("Name"), 260);
    m_list.InsertColumn(1, _T("Offset"), 70);
    m_list.InsertColumn(2, _T("Size"), 70);
    m_list.SetExtendedListViewStyle(LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES
        | LVS_EX_FULLROWSELECT);
    CSym::Enum(m_pSymbol, SymTagData, cbAddMember, this);

    CWindow wndRect = GetDlgItem(IDC_ST_RECT);
    RECT rcView;
    //wndRect.GetRectInParent(&rcView);
    wndRect.ShowWindow(SW_HIDE);

    m_view.Create(*this, &rcView, NULL, 0, 0, IDC_VIEW_DETAIL, (PVOID)lParam);
    m_view.EnableHyperLink(FALSE);
    //m_view.SetEventHandler(this);

    m_bInited = TRUE;
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////

void CModifyDlg::OnDocumentComplete(void)
{
    DumpModified();
}
