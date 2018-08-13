#include <io.h>
#include <stdio.h>

#include "sq.h"

SQInteger sq_fopen(SQVM *v)
{
	const SQChar *filename;
	const SQChar *mode;
	sq_getstring(v, 2, &filename);
	sq_getstring(v, 3, &mode);

	FILE *f = _wfopen(filename, mode);
	sq_pushuserpointer(v, f);

	return 1;
}

SQInteger sq_fclose(SQVM *v)
{
	FILE * f = NULL;
	sq_getuserpointer(v, 2, (SQUserPointer*)&f);
	fclose(f);

	return 1;
}

SQInteger sq_feof(SQVM *v)
{
	FILE * f = NULL;
	sq_getuserpointer(v, 2, (SQUserPointer*)&f);
	int s = feof(f);
	sq_pushinteger(v, s);

	return 1;
}

SQInteger sq_fprint(SQVM *v)
{
	FILE * f = NULL;
	const wchar_t * data;

	sq_getuserpointer(v, 2, (SQUserPointer*)&f);
	sq_getstring(v, 3, &data);

	int s = fwprintf(f, data);
	sq_pushinteger(v, s);

	return 1;
}

SQInteger sq_fputs(SQVM *v)
{
	FILE * f = NULL;
	const wchar_t * data;

	sq_getuserpointer(v, 2, (SQUserPointer*)&f);
	sq_getstring(v, 3, &data);

	int s = fputws(data, f);
	sq_pushinteger(v, s);

	return 1;
}

SQInteger sq_fgets(SQVM *v)
{
	FILE * f = NULL;

	sq_getuserpointer(v, 2, (SQUserPointer*)&f);

	wchar_t * buf = new wchar_t[1024];
	fgetws(buf, 1024, f);
	
	sq_pushstring(v, buf, -1);
	//delete buf;

	return 1;
}

SQInteger sq_fread(SQVM *v)
{
	FILE * f = NULL;
	int size = 0;

	sq_getuserpointer(v, 2, (SQUserPointer*)&f);
	sq_getinteger(v, 3, &size);

	SQChar * buf = new SQChar[size+1];
	fread(buf, sizeof(SQChar), size, f);
	buf[size] = 0;
	
	sq_pushstring(v, buf, -1);
	//delete buf;

	return 1;
}

SQInteger sq_fwrite(SQVM *v)
{
	FILE * f = NULL;
	const SQChar * data;
	int size;

	sq_getuserpointer(v, 2, (SQUserPointer*)&f);
	sq_getstring(v, 3, &data);
	sq_getinteger(v, 4, &size);
	
	size = fwrite(data, sizeof(SQChar), size, f);
	sq_pushinteger(v, size);

	return 1;
}

SQInteger sq_fseek(SQVM *v)
{
	FILE *f = NULL;
	int offset = 0, origin = 0;

	sq_getuserpointer(v, 2, (SQUserPointer*)&f);
	sq_getinteger(v, 3, &offset);
	sq_getinteger(v, 4, &origin);

	int s = fseek(f, offset, origin);
	sq_pushinteger(v, s);

	return 1;
}

SQInteger sq_ftell(SQVM *v)
{
	FILE *f = NULL;

	sq_getuserpointer(v, 2, (SQUserPointer*)&f);

	int s = ftell(f);
	sq_pushinteger(v, s);

	return 1;
}

SQInteger sq_access(SQVM *v)
{
	const wchar_t * filename;
	sq_getstring(v, 2, &filename);

	bool s = _waccess(filename, 0) != -1;
	sq_pushbool(v, s);

	return 1;
}

SQInteger sq_remove(SQVM *v)
{
	const wchar_t * filename;
	sq_getstring(v, 2, &filename);

	int s = _wremove(filename);
	sq_pushinteger(v, s);
	return 1;
}

SQInteger sq_rename(SQVM *v)
{
	const wchar_t * fn;
	const wchar_t * nfn;

	sq_getstring(v, 2, &fn);
	sq_getstring(v, 3, &nfn);

	int s = _wrename(fn, nfn);
	sq_pushinteger(v, s);

	return 1;
}

void RegFileSQFunc(SQVM * v)
{
	register_global_func(v, sq_fopen, L"fopen");
	register_global_func(v, sq_fclose, L"fclose");
	register_global_func(v, sq_feof, L"feof");
	register_global_func(v, sq_fprint, L"fprint");
	register_global_func(v, sq_fputs, L"fputs");
	register_global_func(v, sq_fwrite, L"fwrite");
	register_global_func(v, sq_fgets, L"fgets");
	register_global_func(v, sq_fread, L"fread");
	register_global_func(v, sq_fseek, L"fseek");
	register_global_func(v, sq_ftell, L"ftell");
	register_global_func(v, sq_remove, L"remove");
	register_global_func(v, sq_rename, L"rename");
	register_global_func(v, sq_access, L"access");
}