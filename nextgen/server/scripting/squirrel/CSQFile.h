#pragma once
#include "SQUIRREL/squirrel.h"

class CSQFile
{
public:
	CSQFile(SQVM * v);
	~CSQFile();
private:
	static int _fopen(SQVM *v); // FILE fopen(string filename, string mode)
	static int _fclose(SQVM *v); // bool fclose(FILE_POINTER fp);
	static int _feof(SQVM *v); // int feof(FILE_POINTER fp)
	static int _fprint(SQVM *v); // int fprint[f](FILE_POINTER fp, string data)
	static int _fputs(SQVM *v); // int fputs(FILE_POINTER fp, string data)
	static int _fgets(SQVM *v); // string fgets(FILE_POINTER fp [, int maxsize])
	static int _fread(SQVM *v); // string fread[_s[tr[ing]]](FILE_POINTER fp, int size)
	static int _fread_int(SQVM *v); // int fread_i[nt[eger]](FILE_POINTER fp)
	static int _fread_float(SQVM *v); // float fread_f[loat](FILE_POINTER fp)
	static int _fwrite(SQVM *v); // int fwrite(FILE_POINTER fp, [string|int|float] data, int size)
	static int _fseek(SQVM *v); // int fseek(FILE_POINTER fp, int offset, int origin)
	static int _ftell(SQVM *v); // int ftell(FILE_POINTER fp)
	static int _access(SQVM *v); // int access(string filename)
	static int _remove(SQVM *v); // int remove(string filename)
	static int _rename(SQVM *v); // int rename(string filename, string newfilename)
};