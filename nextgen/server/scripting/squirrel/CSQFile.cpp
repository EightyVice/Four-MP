#include "CSQFile.h"
#include <stdio.h>
#include <io.h>

#ifdef _WIN32
#include <windows.h>
#endif

SQInteger register_global_func(HSQUIRRELVM v, SQFUNCTION f, const SQChar *fname);

CSQFile::CSQFile(SQVM * v)
{
	register_global_func(v, _fopen, _SC("fopen"));
	register_global_func(v, _fclose, _SC("fclose"));
	register_global_func(v, _feof, _SC("feof"));
	register_global_func(v, _fprint, _SC("fprint"));
	register_global_func(v, _fprint, _SC("fprintf"));
	register_global_func(v, _fputs, _SC("fputs"));
	register_global_func(v, _fgets, _SC("fgets"));
	register_global_func(v, _fread, _SC("fread"));
	register_global_func(v, _fread, _SC("fread_s"));
	register_global_func(v, _fread, _SC("fread_str"));
	register_global_func(v, _fread, _SC("fread_string"));
	register_global_func(v, _fread_int, _SC("fread_i"));
	register_global_func(v, _fread_int, _SC("fread_int"));
	register_global_func(v, _fread_int, _SC("fread_integer"));
	register_global_func(v, _fread_float, _SC("fread_f"));
	register_global_func(v, _fread_float, _SC("fread_float"));
	register_global_func(v, _fwrite, _SC("fwrite"));
	register_global_func(v, _fseek, _SC("fseek"));
	register_global_func(v, _ftell, _SC("ftell"));
	register_global_func(v, _access, _SC("access"));
	register_global_func(v, _remove, _SC("remove"));
	register_global_func(v, _rename, _SC("rename"));
}

CSQFile::~CSQFile()
{

}

int CSQFile::_fopen(SQVM *v)
{
#ifdef UNICODE
	const wchar_t * pszFileName, * pszMode;
	sq_getstring(v, 2, &pszFileName);
	sq_getstring(v, 3, &pszMode);

	sq_pushuserpointer(v, _wfopen(pszFileName, pszMode));
#else
	const char * pszFileName, * pszMode;
	sq_getstring(v, 2, &pszFileName);
	sq_getstring(v, 3, &pszMode);

	sq_pushuserpointer(v, fopen(pszFileName, pszMode));
#endif
	return 1;
}

int CSQFile::_fclose(SQVM *v)
{
	FILE * pFile;
	sq_getuserpointer(v, 2, (SQUserPointer*)&pFile);

	if(!pFile) fclose(pFile);

	sq_pushbool(v, true);
	return 1;
}

int CSQFile::_feof(SQVM *v)
{
	FILE * pFile;
	sq_getuserpointer(v, 2, (SQUserPointer*)&pFile);

	sq_pushinteger(v, feof(pFile));
	return 1;
}

int CSQFile::_fprint(SQVM *v)
{
	FILE * pFile;
	sq_getuserpointer(v, 2, (SQUserPointer*)&pFile);

#ifdef UNICODE
	const wchar_t * pszData;
	sq_getstring(v, 3, &pszData);
	sq_pushinteger(v, fwprintf(pFile, pszData));
#else
	const char * pszData;
	sq_getstring(v, 3, &pszData);
	sq_pushinteger(v, fprintf(pFile, pszData));
#endif
	return 1;
}

int CSQFile::_fputs(SQVM *v)
{
	FILE * pFile;
	sq_getuserpointer(v, 2, (SQUserPointer*)&pFile);

#ifdef UNICODE
	const wchar_t * pszData;
	sq_getstring(v, 3, &pszData);
	sq_pushinteger(v, fputws(pszData, pFile));
#else
	const char * pszData;
	sq_getstring(v, 3, &pszData);
	sq_pushinteger(v, fputs(pszData, pFile));
#endif
	return 1;
}

int CSQFile::_fgets(SQVM *v)
{
	FILE * pFile;
	int iSize = 1024;
	sq_getuserpointer(v, 2, (SQUserPointer*)&pFile);

	if(sq_gettop(v) >= 3)
		sq_getinteger(v, 3, &iSize);

	if(iSize <= 0) return 0;
	
#ifdef UNICODE
	wchar_t * pszData = new wchar_t[iSize];
	memset(pszData, 0, sizeof(wchar_t) * iSize);
	fgetws(pszData, iSize, pFile);
	sq_pushstring(v, pszData, -1);
#else
	char * pszData = new wchar_t[iSize];
	memset(pszData, 0, sizeof(wchar_t) * iSize);
	fgets(pszData, iSize, pFile);
	sq_pushstring(v, pszData, -1);
#endif
	return 1;
}

int CSQFile::_fread(SQVM *v)
{
	FILE * pFile;
	int iSize = 0;
	sq_getuserpointer(v, 2, (SQUserPointer*)&pFile);
	sq_getinteger(v, 3, &iSize);

	if(iSize <= 0) return 0;
	
#ifdef UNICODE
	wchar_t * pszData = new wchar_t[iSize];
	memset(pszData, 0, sizeof(wchar_t) * iSize);
	fread(pszData, sizeof(wchar_t), iSize, pFile);
	sq_pushstring(v, pszData, -1);
#else
	char * pszData = new wchar_t[iSize];
	memset(pszData, 0, sizeof(wchar_t) * iSize);
	fread(pszData, sizeof(char), iSize, pFile);
	sq_pushstring(v, pszData, -1);
#endif
	return 1;
}

int CSQFile::_fread_int(SQVM *v)
{
	FILE * pFile;
	int iSize = 1;
	sq_getuserpointer(v, 2, (SQUserPointer*)&pFile);

	if(sq_gettop(v) >= 3)
		sq_getinteger(v, 3, &iSize);

	if(iSize <= 0) return 0;
	
	int * pszData = new int[iSize];
	memset(pszData, 0, sizeof(int) * iSize);
	fread(pszData, sizeof(int), iSize, pFile);
	
	if(iSize > 1)
	{
		sq_newarray(v, 0);
		for(int i = 0; i < iSize; i++)
		{
			sq_pushinteger(v, pszData[i]);
			sq_arrayappend(v, -2);
		}
		sq_push(v, -1);
	}
	else
	{
		sq_pushinteger(v, pszData[0]);
	}

	return 1;
}

int CSQFile::_fread_float(SQVM *v)
{
	FILE * pFile;
	int iSize = 1;
	sq_getuserpointer(v, 2, (SQUserPointer*)&pFile);

	if(sq_gettop(v) >= 3)
		sq_getinteger(v, 3, &iSize);

	if(iSize <= 0) return 0;
	
	float * pszData = new float[iSize];
	memset(pszData, 0, sizeof(float) * iSize);
	fread(pszData, sizeof(float), iSize, pFile);
	
	if(iSize > 1)
	{
		sq_newarray(v, 0);
		for(int i = 0; i < iSize; i++)
		{
			sq_pushfloat(v, pszData[i]);
			sq_arrayappend(v, -2);
		}
		sq_push(v, -1);
	}
	else
	{
		sq_pushfloat(v, pszData[0]);
	}

	return 1;
}

int CSQFile::_fwrite(SQVM *v)
{
	FILE * pFile;
	sq_getuserpointer(v, 2, (SQUserPointer*)&pFile);

	switch(sq_gettype(v,3))
	{
	case OT_INTEGER:
		{
			int pszData;
			sq_getinteger(v, 3, &pszData);
			sq_pushinteger(v, fwrite(&pszData, sizeof(int), 1, pFile));
		} break;
	case OT_FLOAT:
		{
			float pszData;
			sq_getfloat(v, 3, &pszData);
			sq_pushinteger(v, fwrite(&pszData, sizeof(float), 1, pFile));
		} break;
	case OT_STRING:
		{
#ifdef UNICODE
			const wchar_t * pszData;
			int iSize = 0;
			sq_getstring(v, 3, &pszData);
			if(sq_gettop(v) >= 4)
				sq_getinteger(v, 4, &iSize);

			if(iSize <= 0)	iSize = wcslen(pszData);

			sq_pushinteger(v, fwrite(pszData, sizeof(wchar_t), iSize, pFile));
#else
			const char * pszData;
			int iSize = 0;
			sq_getstring(v, 3, &pszData);
			if(sq_gettop(v) >= 4)
				sq_getinteger(v, 4, &iSize);

			if(iSize <= 0)	iSize = strlen(pszData);

			sq_pushinteger(v, fwrite(pszData, sizeof(char), iSize, pFile));
#endif
		} break;
	}
	return 1;
}

int CSQFile::_fseek(SQVM *v)
{
	FILE * pFile;
	int iOffset, iOrigin;
	sq_getuserpointer(v, 2, (SQUserPointer*)&pFile);
	sq_getinteger(v, 3, &iOffset);
	sq_getinteger(v, 4, &iOrigin);

	sq_pushinteger(v, fseek(pFile, iOffset, iOrigin));
	return 1;
}

int CSQFile::_ftell(SQVM *v)
{
	FILE * pFile;
	sq_getuserpointer(v, 2, (SQUserPointer*)&pFile);

	sq_pushinteger(v, ftell(pFile));
	return 1;
}

int CSQFile::_access(SQVM *v)
{
#ifdef UNICODE
	const wchar_t * pszFileName;
	sq_getstring(v, 2, &pszFileName);
	sq_pushinteger(v, _waccess(pszFileName, 0));
#else
	const char * pszFileName;
	sq_getstring(v, 2, &pszFileName);
	sq_pushinteger(v, access(pszFileName, 0));
#endif
	return 1;
}

int CSQFile::_remove(SQVM *v)
{
#ifdef UNICODE
	const wchar_t * pszFileName;
	sq_getstring(v, 2, &pszFileName);
	sq_pushinteger(v, _wremove(pszFileName));
#else
	const char * pszFileName;
	sq_getstring(v, 2, &pszFileName);
	sq_pushinteger(v, remove(pszFileName));
#endif
	return 1;
}

int CSQFile::_rename(SQVM *v)
{
#ifdef UNICODE
	const wchar_t * pszFileName, * pszNewFileName;

	sq_getstring(v, 2, &pszFileName);
	sq_getstring(v, 3, &pszNewFileName);

	sq_pushinteger(v, _wrename(pszFileName, pszNewFileName));
#else
	const char * pszFileName, * pszNewFileName;

	sq_getstring(v, 2, &pszFileName);
	sq_getstring(v, 3, &pszNewFileName);

	sq_pushinteger(v, rename(pszFileName, pszNewFileName));
#endif
	return 1;
}
	