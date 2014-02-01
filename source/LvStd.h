///////////////////////////////////////////////////////////////////////////////
// FileName:    LvStd.h
// Created:     2013/10/30
// Author:      titilima
// CopyRight:   Titi Studio (?) 2001-2013
//-----------------------------------------------------------------------------
// Information: Pre-compiled header
///////////////////////////////////////////////////////////////////////////////

#ifndef LVSTD_H
#define LVSTD_H

#pragma once

/**
 * ATL & WTL Headers
 */

#include <atlbase.h>
#include <atltypes.h>
#include <atlapp.h>
extern CAppModule _Module;
#include <atlwin.h>
#include <atlcrack.h>
#include <atlctrls.h>
#include <atlddx.h>

/**
 * STL Headers
 */

#include <string>

typedef std::basic_string<TCHAR> String;

using namespace std;

/**
 * Local Headers
 */

#include "resource.h"

/**
 * Global Variables
 */

extern basic_string<TCHAR> g_strIni;

#endif // LVSTD_H
