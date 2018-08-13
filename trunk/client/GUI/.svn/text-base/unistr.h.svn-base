#pragma once
#include <string>

#if defined (_UNICODE)
typedef std::wstring uistring;
typedef std::wstringstream unistream;
typedef wchar_t uichar;
#define _UI(x) L ## x
#define uislen(a) wcslen(a)
#define uiscmp(a,b) wcscmp(a,b)
#define uiscpy(a,b) wcscpy(a,b)
#define uiscpy_s(a,b,c) wcscpy_s(a,b,c)
#define uimemcpy(a,b,c) wmemcpy(a,b,c)
#define utoi(a) _wtoi(a)
#define utof(a) _wtof(a)
#else
typedef std::string uistring;
typedef std::stringstream unistream;
typedef char uichar;
#define _UI(x) x
#define uislen(a) strlen(a)
#define uiscmp(a,b) strcmp(a,b)
#define uiscpy(a,b) strcpy(a,b)
#define uiscpy_s(a,b,c) strcpy_s(a,b,c)
#define uimemcpy(a,b,c) memcpy(a,b,c)
#define utoi(a) atoi(a)
#define utof(a) atof(a)
#endif