/// \file
/// \brief Header file that defines data types and functions that are used in the console.
/// \details See individual description.
/// \author FaTony

#pragma once

#include <string>

#if defined (CONUNICODE)
typedef wchar_t conchar;
typedef std::wstring constring;
typedef std::wfstream confstream;
#define CONSTRING(string) L ## string
#else
typedef char conchar;
typedef std::string constring;
typedef std::fstream confstream;
#define CONSTRING(string) string
#endif

#if defined (CONUNICODE)
#define con_atoi _wtoi
#define con_atof _wtof
#define con_strlen wcslen
#define con_strcmp wcscmp
#define con_strstr wcsstr
#define con_scprintf _scwprintf
#define con_vscprintf _vscwprintf
#define con_printf wprintf
#define con_strcpy wcscpy
#define con_strncpy wcsncpy
#define con_sprintf(string, size, format) swprintf(string, size, format
#define con_vsprintf(string, size, format, arglist) vswprintf(string, size, format, arglist)
#define con_getch _getwch
#else
#define con_atoi atoi
#define con_atof atof
#define con_strlen strlen
#define con_strcmp strcmp
#define con_strstr strstr
#define con_scprintf _scprintf
#define con_vscprintf _vscprintf
#define con_printf printf
#define con_strcpy strcpy
#define con_strncpy strncpy
#define con_sprintf(string, size, format) sprintf(string, format
#define con_vsprintf(string, size, format, arglist) vsprintf(string, format, arglist)
#define con_getch _getch
#endif