///////////////////////////////////////////////////////////////////////////////
// FileName:    PEAnalyzer.h
// Created:     2008/10/30
// Author:      titilima
// CopyRight:   Titi Studio (?) 2001-2013
//-----------------------------------------------------------------------------
// Information: PE Analyzer
///////////////////////////////////////////////////////////////////////////////

#ifndef PEANALYZER_H
#define PEANALYZER_H

#pragma once

typedef enum _tagSignType {
    ErrorSign = -1,
    NoSign = 0,
    CVSign
} SIGNTYPE;

class CPEAnalyzer
{
public:
    CPEAnalyzer(void);
    ~CPEAnalyzer(void);
public:
    BOOL Open(__in PCTSTR lpFileName);
    void Close(void);
    BOOL IsPE(void);
    SIGNTYPE GetSignature(__out PTSTR lpString, __out PTSTR lpPdbFile);
private:
    PVOID RvaToRaw(__in DWORD dwRva);
private:
    HANDLE m_hFile;
    HANDLE m_hMapping;
    PVOID m_pvBase;
};

#endif // PEANALYZER_H
