#pragma once
#define USE_SQUIRREL

#include <stdio.h>

#ifdef USE_SQUIRREL
#include "squirrel/CSquirrel.h"
#endif

#ifdef UNICODE
#define _MOW(a) L##a
typedef wchar_t SChar;
#else
#define _MOW(a) a
typedef char SChar;
#endif

class CScript
{
public:
	CScript(const SChar * pszScriptName = NULL);
	~CScript();

	bool LoadScript(const SChar * pszScriptName);
	bool CallFunction(const SChar * pszCallback, void * pRetVal, const SChar * pszParamMask, ...);
private:

#ifdef USE_SQUIRREL
	CSquirrel * pSquirrel;
#endif
};