#include "CSquirrel.h"
#include <stdio.h>
#include <stdarg.h>

#include "SQUIRREL/sqstdaux.h"
#include "SQUIRREL/sqstdblob.h"
#include "SQUIRREL/sqstdio.h"
#include "SQUIRREL/sqstdmath.h"
#include "SQUIRREL/sqstdstring.h"
#include "SQUIRREL/sqstdsystem.h"

#include "CSQFile.h"
#include "CSQMysql.h"

#pragma comment(lib, "../shared/SQUIRREL/squirrel.lib")
#pragma comment(lib, "../shared/SQUIRREL/sqstdlib.lib")

SQInteger register_global_func(HSQUIRRELVM v, SQFUNCTION f, const SQChar *fname)
{
    sq_pushroottable(v);
    sq_pushstring(v, fname, -1);
    sq_newclosure(v, f, 0);
    sq_createslot(v, -3);
    sq_pop(v, 1);
    return 1;
}

CSquirrel::CSquirrel()
{
	this->pSQVM = sq_open(1024);
	sq_setprintfunc(this->pSQVM, CSquirrel::print,  CSquirrel::error);

	sq_pushroottable(this->pSQVM);

	sqstd_register_bloblib(this->pSQVM);
	sqstd_register_iolib(this->pSQVM);
	sqstd_register_systemlib(this->pSQVM);
	sqstd_register_mathlib(this->pSQVM);
	sqstd_register_stringlib(this->pSQVM);

	CSQFile(this->pSQVM);
	CSQMysql(this->pSQVM);

	sqstd_seterrorhandlers(this->pSQVM);
}

CSquirrel::~CSquirrel()
{
	sq_close(this->pSQVM);
}

bool CSquirrel::LoadScript(const SQChar * pszScriptName)
{
	return SQ_SUCCEEDED(sqstd_dofile(this->pSQVM, pszScriptName, SQTrue, SQTrue));
}

SQVM * CSquirrel::GetVM()
{
	return this->pSQVM;
}

bool CSquirrel::CallFunction(const SQChar * pszCallback, void * pRetVal, const wchar_t * pszParamMask, char * pszArg)
{
	int top = sq_gettop(this->pSQVM);

	sq_pushroottable(this->pSQVM);
	sq_pushstring(this->pSQVM, pszCallback, -1);
	if (SQ_SUCCEEDED(sq_get(this->pSQVM, -2))) 
	{
		sq_pushroottable(this->pSQVM);
		for(unsigned int i = 1; i < wcslen(pszParamMask); i++)
		{
			switch(pszParamMask[i])
			{
			case 'd': 
			case 'i': 
				sq_pushinteger(this->pSQVM, va_arg(pszArg, int));
				break;
			case 'f': 
				sq_pushfloat(this->pSQVM, (float)va_arg(pszArg, double));
				break;
			case 's': 
				sq_pushstring(this->pSQVM, va_arg(pszArg, SQChar*), -1);
				break;
			case '0': 
				sq_pushnull(this->pSQVM);
				break;
			}
		}

		if(SQ_FAILED(sq_call(this->pSQVM, 3, pszParamMask[0] != '0', SQTrue)))
		{
			return false;
		}

		switch(pszParamMask[0])
		{
		case 'd': 
		case 'i': 
			sq_getinteger(this->pSQVM, sq_gettop(this->pSQVM), (SQInteger*)pRetVal);
			break;
		case 'f': 
			sq_getfloat(this->pSQVM, sq_gettop(this->pSQVM), (SQFloat*)pRetVal);
			break;
		case 's': 
			sq_getstring(this->pSQVM, sq_gettop(this->pSQVM), (const SQChar**)&pRetVal);
			break;
		}
	}
	sq_settop(this->pSQVM, top);
	return true;
}

void CSquirrel::print(SQVM * v, const SQChar *string, ...)
{
#ifndef UNICODE
	va_list arglist;
    va_start(arglist, string);
	vprintf(string, arglist);
    va_end(arglist);
#else
	va_list arglist;
    va_start(arglist, string);
	vwprintf(string, arglist);
    va_end(arglist);
#endif
}

void CSquirrel::error(SQVM * v, const SQChar *string, ...)
{
#ifndef UNICODE
	va_list arglist;
    va_start(arglist, string);
	printf("Error: ");
	vprintf(string, arglist);
    va_end(arglist);
#else
	va_list arglist;
    va_start(arglist, string);
	wprintf(L"Error: ");
	vwprintf(string, arglist);
    va_end(arglist);
#endif
}