#pragma once
#include "SQUIRREL/squirrel.h"

class CSquirrel
{
public:
	CSquirrel();
	~CSquirrel();

	bool LoadScript(const SQChar * pszScriptName);
	SQVM * GetVM();
	bool CallFunction(const SQChar * pszCallback, void * pRetVal, const wchar_t * pszParamMask, char * pszArg);
private:

	static void print(SQVM * v, const SQChar *string, ...);
	static void error(SQVM * v, const SQChar *string, ...);

	SQVM * pSQVM;
};