#include "CScript.h"
#include <stdarg.h>
#include "SQUIRREL/sqstdio.h"

CScript::CScript(const SChar * pszScriptName)
{
#ifdef USE_SQUIRREL
	pSquirrel = new CSquirrel();
#endif

	this->LoadScript(pszScriptName);
}

CScript::~CScript()
{
#ifdef USE_SQUIRREL
	delete pSquirrel;
#endif
}

bool CScript::LoadScript(const SChar * pszScriptName)
{
	bool bResult = true;
#ifdef USE_SQUIRREL
	bResult &= pSquirrel->LoadScript(pszScriptName);
#endif
	return bResult;
}

bool CScript::CallFunction(const SChar * pszCallback, void * pRetVal, const SChar * pszParamMask, ...)
{
	va_list arglist;
	va_start(arglist, pszParamMask);

	bool bResult = true;

#ifdef USE_SQUIRREL
	bResult &= pSquirrel->CallFunction(pszCallback, pRetVal, pszParamMask, arglist);
#endif

	va_end(arglist);
	return bResult;
}