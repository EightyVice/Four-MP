#include "CSQMysql.h"

#pragma comment(lib, "../shared/mysql/libmysql.lib")

SQInteger register_global_func(HSQUIRRELVM v, SQFUNCTION f, const SQChar *fname);

MYSQL * CSQMysql::pLastMysql = NULL;
std::vector<MYSQL *> CSQMysql::vAllMySql;

CSQMysql::CSQMysql(SQVM * v)
{
	register_global_func(v, _mysql_connect, _SC("mysql_connect"));
	register_global_func(v, _mysql_close, _SC("mysql_close"));
	register_global_func(v, _mysql_select_db, _SC("mysql_select_db"));
	register_global_func(v, _mysql_errno, _SC("mysql_errno"));
	register_global_func(v, _mysql_error, _SC("mysql_error"));
	register_global_func(v, _mysql_ping, _SC("mysql_ping"));
	register_global_func(v, _mysql_change_user, _SC("mysql_change_user"));
	register_global_func(v, _mysql_query, _SC("mysql_query"));
	register_global_func(v, _mysql_free_result, _SC("mysql_free_result"));
	register_global_func(v, _mysql_insert_id, _SC("mysql_insert_id"));
	register_global_func(v, _mysql_data_seek, _SC("mysql_data_seek"));
	register_global_func(v, _mysql_row_seek, _SC("mysql_row_seek"));
	register_global_func(v, _mysql_field_seek, _SC("mysql_field_seek"));
	register_global_func(v, _mysql_num_rows, _SC("mysql_num_rows"));
	register_global_func(v, _mysql_num_fields, _SC("mysql_num_fields"));
	register_global_func(v, _mysql_fetch_row, _SC("mysql_fetch_row"));
	register_global_func(v, _mysql_get_host_info, _SC("mysql_get_host_info"));
	register_global_func(v, _mysql_get_client_info, _SC("mysql_get_client_info"));
	register_global_func(v, _mysql_get_proto_info, _SC("mysql_get_proto_info"));
	register_global_func(v, _mysql_get_server_info, _SC("mysql_get_server_info"));
	register_global_func(v, _mysql_info, _SC("mysql_info"));
	register_global_func(v, _mysql_list_dbs, _SC("mysql_list_dbs"));
	register_global_func(v, _mysql_list_fields, _SC("mysql_list_fields"));
	register_global_func(v, _mysql_list_processes, _SC("mysql_list_processes"));
	register_global_func(v, _mysql_list_tables, _SC("mysql_list_tables"));
	register_global_func(v, _mysql_stat, _SC("mysql_stat"));
	register_global_func(v, _mysql_thread_id, _SC("mysql_thread_id"));
	register_global_func(v, _mysql_affected_rows, _SC("mysql_affected_rows"));
	register_global_func(v, _mysql_fetch_lengths, _SC("mysql_fetch_lengths"));
	register_global_func(v, _mysql_real_escape_string, _SC("mysql_real_escape_string"));
	register_global_func(v, _mysql_escape_string, _SC("mysql_escape_string"));
	register_global_func(v, _mysql_fetch_field, _SC("mysql_fetch_field"));
	register_global_func(v, _mysql_field_name, _SC("mysql_field_name"));
	register_global_func(v, _mysql_field_table, _SC("mysql_field_table"));
	register_global_func(v, _mysql_field_len, _SC("mysql_field_len"));
	register_global_func(v, _mysql_field_type, _SC("mysql_field_type"));
	register_global_func(v, _mysql_field_flags, _SC("mysql_field_flags"));

	register_global_func(v, _mysql_result, _SC("mysql_result"));
	register_global_func(v, _mysql_fetch_assoc, _SC("mysql_fetch_assoc"));
	register_global_func(v, _mysql_fetch_array, _SC("mysql_fetch_array"));
	
}

CSQMysql::~CSQMysql()
{
	for(std::vector<MYSQL *>::const_iterator i = vAllMySql.begin(); i != vAllMySql.end(); i++)
	{
		MYSQL * pM = *i;
		delete pM;
		pM = NULL;
	}
}

int CSQMysql::_mysql_connect(SQVM * v)
{
#ifndef UNICODE
	const char * pszServer = NULL, * pszUser = NULL, * pszPassword = NULL;
	sq_getstring(v, 2, &pszServer);
	sq_getstring(v, 3, &pszUser);
	sq_getstring(v, 4, &pszPassword);
#else
	char * pszServer = NULL, * pszUser = NULL, * pszPassword = NULL;
	const wchar_t * pServer = NULL, * pUser = NULL, * pPassword = NULL; 
	sq_getstring(v, 2, &pServer);
	sq_getstring(v, 3, &pUser);
	sq_getstring(v, 4, &pPassword);

	int iLen = wcslen(pServer);
	pszServer = new char[iLen+1];
	wcstombs(pszServer, pServer, iLen);

	iLen = wcslen(pUser);
	pszUser = new char[iLen+1];
	wcstombs(pszUser, pUser, iLen);

	iLen = wcslen(pPassword);
	pszPassword = new char[iLen+1];
	wcstombs(pszPassword, pPassword, iLen);
#endif

	MYSQL * pMySql = new MYSQL;
	memset(pMySql, 0, sizeof(MYSQL));

	if(!mysql_init(pMySql))
	{
#ifdef UNICODE
		wprintf(L"Error: can't create MySQL-descriptor [%s@%s]\n", pUser, pPassword);
		delete [] pszServer;
		delete [] pszUser;
		delete [] pszPassword;
#else
		printf("Error: can't create MySQL-descriptor [%s@%s]\n", pszUser, pszPassword);
#endif
		delete pMySql;
		return 0;
	}

	if(!mysql_real_connect(pMySql, pszServer, pszUser, pszPassword, "", 3306, NULL, NULL))
	{
		sq_pushuserpointer(v, pMySql);
	}
	else
	{
		sq_pushuserpointer(v, pMySql);
	}

#ifdef UNICODE
	delete [] pszServer;
	delete [] pszUser;
	delete [] pszPassword;
#endif

	vAllMySql.push_back(pMySql);
	pLastMysql = pMySql;
	return 1;
}

int CSQMysql::_mysql_close(SQVM * v)
{
	MYSQL * pMySql = NULL;

	if(sq_gettop(v) < 2)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);
	}

	mysql_close(pMySql);
	delete pMySql;

	if(pMySql == pLastMysql)
	{
		vAllMySql.pop_back();
		if(vAllMySql.size() > 0)
		{
			pLastMysql = *vAllMySql.end();
		}
		else
		{
			pLastMysql = NULL;
		}
	}

	sq_pushbool(v, true);
	return 1;
}

int CSQMysql::_mysql_errno(SQVM * v)
{
	MYSQL * pMySql = NULL;

	if(sq_gettop(v) < 2)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);
	}

	sq_pushinteger(v, mysql_errno(pMySql));
	return 1;
}

int CSQMysql::_mysql_error(SQVM * v)
{
	MYSQL * pMySql = NULL;

	if(sq_gettop(v) < 2)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);
	}

#ifndef UNICODE
	sq_pushstring(v, mysql_error(pMySql), -1);
#else
	const char * pszError = mysql_error(pMySql);
	int iLen = strlen(pszError);
	wchar_t * pError = new wchar_t[iLen + 1];
	mbstowcs(pError, pszError, iLen);

	sq_pushstring(v, pError, -1);
#endif
	return 1;
}

int CSQMysql::_mysql_ping(SQVM * v)
{
	MYSQL * pMySql = NULL;

	if(sq_gettop(v) < 2)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);
	}

	sq_pushinteger(v, mysql_ping(pMySql));
	return 1;
}

int CSQMysql::_mysql_select_db(SQVM * v)
{
	MYSQL * pMySql = NULL;

#ifndef UNICODE
	const char * pszDB = NULL;
	sq_getstring(v, 2, &pszDB);
#else
	char * pszDB = NULL;
	const wchar_t * pDB = NULL;
	sq_getstring(v, 2, &pDB);

	int iLen = wcslen(pDB);
	pszDB = new char[iLen+1];
	wcstombs(pszDB, pDB, iLen);
#endif

	if(sq_gettop(v) < 3)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 3, (SQUserPointer *)&pMySql);
	}

	sq_pushinteger(v, mysql_select_db(pMySql, pszDB));

#ifdef UNICODE
	delete [] pszDB;
#endif

	return 1;
}

int CSQMysql::_mysql_change_user(SQVM * v)
{
	MYSQL * pMySql = NULL;

#ifndef UNICODE
	const char * pszUser = NULL, * pszPassword = NULL, * pszDB = NULL;
	sq_getstring(v, 2, &pUser);
	sq_getstring(v, 3, &pPassword);
#else
	char * pszUser = NULL, * pszPassword = NULL, * pszDB = NULL;
	const wchar_t * pUser = NULL, * pPassword = NULL, * pDB = NULL;

	sq_getstring(v, 2, &pUser);
	sq_getstring(v, 3, &pPassword);

	int iLen = wcslen(pUser);
	pszUser = new char[iLen+1];
	wcstombs(pszUser, pUser, iLen);

	iLen = wcslen(pPassword);
	pszPassword = new char[iLen+1];
	wcstombs(pszPassword, pPassword, iLen);
#endif

	if(sq_gettop(v) < 4)
	{
#ifndef UNICODE
		sq_getstring(v,4, &pszDB);
#else
		sq_getstring(v,4, &pDB);

		iLen = wcslen(pDB);
		pszDB = new char[iLen+1];
		wcstombs(pszDB, pDB, iLen);
#endif
	}

	if(sq_gettop(v) < 5)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 5, (SQUserPointer *)&pMySql);
	}

	sq_pushinteger(v, mysql_change_user(pMySql, pszUser, pszPassword, pszDB));

#ifdef UNICODE
	delete [] pszUser;
	delete [] pszPassword;
	delete [] pszDB;
#endif
	return 1;
}

int CSQMysql::_mysql_query(SQVM * v)
{
	MYSQL * pMySql = NULL;

#ifndef UNICODE
	const char * pszQ = NULL;
	sq_getstring(v, 2, &pszQ);
#else
	char * pszQ = NULL;
	const wchar_t * pQ = NULL;
	sq_getstring(v, 2, &pQ);

	int iLen = wcslen(pQ);
	pszQ = new char[iLen+1];
	wcstombs(pszQ, pQ, iLen);
#endif

	if(sq_gettop(v) < 3)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 3, (SQUserPointer *)&pMySql);
	}

	if(mysql_query(pMySql, pszQ) != 0) {} //return 0;

#ifdef UNICODE
	delete [] pszQ;
#endif

	sq_pushuserpointer(v, mysql_store_result(pMySql));
	return 1;
}

int CSQMysql::_mysql_insert_id(SQVM * v)
{
	MYSQL * pMySql = NULL;

	if(sq_gettop(v) < 2)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);
	}

	sq_pushinteger(v, mysql_insert_id(pMySql));
	return 1;
}

int CSQMysql::_mysql_free_result(SQVM * v)
{
	MYSQL_RES * pRes = NULL;
	sq_getuserpointer(v, 2, (SQUserPointer *)&pRes);

	if(!pRes) return 0;

	mysql_free_result(pRes);
	sq_pushbool(v, true);
	return 1;
}

int CSQMysql::_mysql_data_seek(SQVM * v)
{
	MYSQL_RES * pRes = NULL;
	sq_getuserpointer(v, 2, (SQUserPointer *)&pRes);

	my_ulonglong iOffset = NULL;
	sq_getinteger(v, 3, (SQInteger *)&iOffset);

	mysql_data_seek(pRes, iOffset);
	sq_pushbool(v, true);
	return 1;
}

int CSQMysql::_mysql_row_seek(SQVM * v)
{
	MYSQL_RES * pRes = NULL;
	sq_getuserpointer(v, 2, (SQUserPointer *)&pRes);

	MYSQL_ROW_OFFSET iOffset = NULL;
	sq_getinteger(v, 3, (SQInteger *)&iOffset);

	mysql_row_seek(pRes, iOffset);
	sq_pushbool(v, true);
	return 1;
}

int CSQMysql::_mysql_field_seek(SQVM * v)
{
	MYSQL_RES * pRes = NULL;
	sq_getuserpointer(v, 2, (SQUserPointer *)&pRes);

	my_ulonglong iOffset = NULL;
	sq_getinteger(v, 3, (SQInteger *)&iOffset);

	mysql_field_seek(pRes, iOffset);
	sq_pushbool(v, true);
	return 1;
}

int CSQMysql::_mysql_num_rows(SQVM * v)
{
	MYSQL_RES * pRes = NULL;
	sq_getuserpointer(v, 2, (SQUserPointer *)&pRes);

	if(!pRes) return 0;

	sq_pushinteger(v, mysql_num_rows(pRes));
	return 1;
}

int CSQMysql::_mysql_num_fields(SQVM * v)
{
	MYSQL_RES * pRes = NULL;
	sq_getuserpointer(v, 2, (SQUserPointer *)&pRes);

	if(!pRes) return 0;

	sq_pushinteger(v, mysql_num_fields(pRes));
	return 1;
}

int CSQMysql::_mysql_fetch_row(SQVM * v)
{
	MYSQL_RES * pRes = NULL;
	sq_getuserpointer(v, 2, (SQUserPointer *)&pRes);

	if(!pRes) return 0;

	MYSQL_ROW mRow = mysql_fetch_row(pRes);

	unsigned int dwNumFields = mysql_num_fields(pRes);

	sq_newarray(v, 0);
	for(unsigned int i = 0; i < dwNumFields; i++)
	{
#ifndef UNICODE
		sq_pushstring(v, mRow[i], -1);
#else
		int iLen = strlen(mRow[i]);
		wchar_t * pRow = new wchar_t[iLen+1];
		mbstowcs(pRow, mRow[i], iLen);
		sq_pushstring(v, pRow, -1);
#endif
		sq_arrayappend(v, -2);
	}
    sq_push(v, -1);

	return 1;
}

int CSQMysql::_mysql_get_host_info(SQVM * v)
{
	MYSQL * pMySql = NULL;

	if(sq_gettop(v) < 2)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);
	}

#ifndef UNICODE
	sq_pushstring(v, mysql_get_host_info(pMySql), -1);
#else
	const char * pszInfo = mysql_get_host_info(pMySql);
	int iLen = strlen(pszInfo);
	wchar_t * pInfo = new wchar_t[iLen + 1];
	mbstowcs(pInfo, pszInfo, iLen);

	sq_pushstring(v, pInfo, -1);
#endif
	return 1;
}

int CSQMysql::_mysql_get_client_info(SQVM * v)
{
#ifndef UNICODE
	sq_pushstring(v, mysql_get_client_info(), -1);
#else
	const char * pszInfo = mysql_get_client_info();
	int iLen = strlen(pszInfo);
	wchar_t * pInfo = new wchar_t[iLen + 1];
	mbstowcs(pInfo, pszInfo, iLen);

	sq_pushstring(v, pInfo, -1);
#endif
	return 1;
}

int CSQMysql::_mysql_get_proto_info(SQVM * v)
{
	MYSQL * pMySql = NULL;

	if(sq_gettop(v) < 2)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);
	}

	sq_pushinteger(v, mysql_get_proto_info(pMySql));
	return 1;
}

int CSQMysql::_mysql_get_server_info(SQVM * v)
{
	MYSQL * pMySql = NULL;

	if(sq_gettop(v) < 2)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);
	}

#ifndef UNICODE
	sq_pushstring(v, mysql_get_server_info(pMySql), -1);
#else
	const char * pszInfo = mysql_get_server_info(pMySql);
	int iLen = strlen(pszInfo);
	wchar_t * pInfo = new wchar_t[iLen + 1];
	mbstowcs(pInfo, pszInfo, iLen);

	sq_pushstring(v, pInfo, -1);
#endif
	return 1;
}

int CSQMysql::_mysql_info(SQVM * v)
{
	MYSQL * pMySql = NULL;

	if(sq_gettop(v) < 2)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);
	}

#ifndef UNICODE
	sq_pushstring(v, mysql_info(pMySql), -1);
#else
	const char * pszInfo = mysql_info(pMySql);
	int iLen = strlen(pszInfo);
	wchar_t * pInfo = new wchar_t[iLen + 1];
	mbstowcs(pInfo, pszInfo, iLen);

	sq_pushstring(v, pInfo, -1);
#endif
	return 1;
}

int CSQMysql::_mysql_list_dbs(SQVM * v)
{
	MYSQL * pMySql = NULL;

	if(sq_gettop(v) < 2)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);
	}

	sq_pushuserpointer(v, mysql_list_dbs(pMySql, NULL));
	return 1;
}

int CSQMysql::_mysql_list_fields(SQVM * v)
{
	MYSQL * pMySql = NULL;

#ifndef UNICODE
	const char * pszTable = NULL;
	sq_getstring(v, 2, &pszTable);
#else
	char * pszTable = NULL;
	const wchar_t * pTable = NULL;
	sq_getstring(v, 2, &pTable);

	int iLen = wcslen(pTable);
	pszTable = new char[iLen+1];
	wcstombs(pszTable, pTable, iLen);
#endif

	if(sq_gettop(v) < 3)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 3, (SQUserPointer *)&pMySql);
	}

	sq_pushuserpointer(v, mysql_list_fields(pMySql, pszTable, NULL));

#ifdef UNICODE
	delete [] pszTable;
#endif
	return 1;
}

int CSQMysql::_mysql_list_processes(SQVM * v)
{
	MYSQL * pMySql = NULL;

	if(sq_gettop(v) < 2)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);
	}

	sq_pushuserpointer(v, mysql_list_processes(pMySql));
	return 1;
}

int CSQMysql::_mysql_list_tables(SQVM * v)
{
	MYSQL * pMySql = NULL;

	if(sq_gettop(v) < 2)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);
	}

	sq_pushuserpointer(v, mysql_list_tables(pMySql, NULL));
	return 1;
}

int CSQMysql::_mysql_stat(SQVM * v)
{
	MYSQL * pMySql = NULL;

	if(sq_gettop(v) < 2)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);
	}

#ifndef UNICODE
	sq_pushstring(v, mysql_stat(pMySql), -1);
#else
	const char * pszStat = mysql_stat(pMySql);
	int iLen = strlen(pszStat);
	wchar_t * pStat = new wchar_t[iLen + 1];
	mbstowcs(pStat, pszStat, iLen);

	sq_pushstring(v, pStat, -1);
#endif
	return 1;
}

int CSQMysql::_mysql_thread_id(SQVM * v)
{
	MYSQL * pMySql = NULL;

	if(sq_gettop(v) < 2)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);
	}

	sq_pushinteger(v, mysql_thread_id(pMySql));
	return 1;
}

int CSQMysql::_mysql_affected_rows(SQVM * v)
{
	MYSQL * pMySql = NULL;

	if(sq_gettop(v) < 2)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);
	}

	sq_pushinteger(v, mysql_affected_rows(pMySql));
	return 1;
}

int CSQMysql::_mysql_fetch_lengths(SQVM * v)
{
	MYSQL_RES * pRes = NULL;
	sq_getuserpointer(v, 2, (SQUserPointer *)&pRes);

	if(!pRes) return 0;

	unsigned long * mRow = mysql_fetch_lengths(pRes);
	unsigned int dwNumFields = mysql_num_fields(pRes);

	sq_newarray(v, 0);
	for(unsigned int i = 0; i < dwNumFields; i++)
	{
		sq_pushinteger(v, mRow[i]);
		sq_arrayappend(v, -2);
	}
    sq_push(v, -1);

	return 1;
}

int CSQMysql::_mysql_real_escape_string(SQVM * v)
{
	MYSQL * pMySql = NULL;

#ifndef UNICODE
	const char * pszFrom = NULL;
	sq_getstring(v, 2, &pszFrom);
#else
	char * pszFrom = NULL;
	const wchar_t * pFrom = NULL;
	sq_getstring(v, 2, &pFrom);

	int iLen = wcslen(pFrom);
	pszFrom = new char[iLen+1];
	wcstombs(pszFrom, pFrom, iLen);
#endif

	if(sq_gettop(v) < 3)
	{
		pMySql = pLastMysql;
	}
	else
	{
		sq_getuserpointer(v, 3, (SQUserPointer *)&pMySql);
	}

	unsigned int len = strlen(pszFrom);

	char * to = new char[len*2 + 1];
	mysql_real_escape_string(pMySql, to, pszFrom, len);

#ifndef UNICODE
	sq_pushstring(v, to, -1);
	delete [] to;
#else
	wchar_t * wto = new wchar_t[len*2 + 1];
	mbstowcs(wto, to, len*2 + 1);
	sq_pushstring(v, wto, -1);
	delete [] wto;
	delete [] pszFrom;
#endif
	return 1;
}

int CSQMysql::_mysql_escape_string(SQVM * v)
{
#ifndef UNICODE
	const char * pszFrom = NULL;
	sq_getstring(v, 2, &pszFrom);
#else
	char * pszFrom = NULL;
	const wchar_t * pFrom = NULL;
	sq_getstring(v, 2, &pFrom);

	int iLen = wcslen(pFrom);
	pszFrom = new char[iLen+1];
	wcstombs(pszFrom, pFrom, iLen);
#endif

	unsigned int len = strlen(pszFrom);

	char * to = new char[len*2 + 1];
	mysql_escape_string(to, pszFrom, len);

#ifndef UNICODE
	sq_pushstring(v, to, -1);
	delete [] to;
#else
	wchar_t * wto = new wchar_t[len*2 + 1];
	mbstowcs(wto, to, len*2 + 1);
	sq_pushstring(v, wto, -1);
	delete [] wto;
	delete [] pszFrom;
#endif
	return 1;
}

int CSQMysql::_mysql_fetch_field(SQVM * v)
{
	MYSQL_RES * pMySql = NULL;

	sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);

	if(!pMySql) return 0;

	if(sq_gettop(v) >= 3)
	{
		int iFieldOffset = 0;
		sq_getinteger(v, 3, &iFieldOffset);
		mysql_field_seek(pMySql, iFieldOffset);
	}

	MYSQL_FIELD * mField = mysql_fetch_field(pMySql);
	
	sq_newtable(v); 

	sq_pushstring(v, _SC("name"), -1);
#ifndef UNICODE
	sq_pushstring(v, mField->name, -1);
#else
	int iLen = strlen(mField->name);
	wchar_t * pData = new wchar_t[iLen + 1];
	mbstowcs(pData, mField->name, iLen);
	sq_pushstring(v, pData, -1);
#endif
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, _SC("table"), -1);
#ifndef UNICODE
	sq_pushstring(v, mField->table, -1);
#else
	iLen = strlen(mField->table);
	pData = new wchar_t[iLen + 1];
	mbstowcs(pData, mField->table, iLen);
	sq_pushstring(v, pData, -1);
#endif
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, _SC("db"), -1);
#ifndef UNICODE
	sq_pushstring(v, mField->db, -1);
#else
	iLen = strlen(mField->db);
	pData = new wchar_t[iLen + 1];
	mbstowcs(pData, mField->db, iLen);
	sq_pushstring(v, pData, -1);
#endif
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, _SC("max_length"), -1);
	sq_pushinteger(v, mField->max_length);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, _SC("type"), -1);
	switch(mField->type)
	{
	case MYSQL_TYPE_DECIMAL: sq_pushstring(v, _SC("DECIMAL"), -1); break;
	case MYSQL_TYPE_TINY: sq_pushstring(v, _SC("TINY"), -1); break;
	case MYSQL_TYPE_SHORT: sq_pushstring(v, _SC("SHORT"), -1); break;
	case MYSQL_TYPE_LONG: sq_pushstring(v, _SC("LONG"), -1); break;
	case MYSQL_TYPE_FLOAT: sq_pushstring(v, _SC("FLOAT"), -1); break;
	case MYSQL_TYPE_DOUBLE: sq_pushstring(v, _SC("DOUBLE"), -1); break;
	case MYSQL_TYPE_NULL: sq_pushstring(v, _SC("NULL"), -1); break;
	case MYSQL_TYPE_TIMESTAMP: sq_pushstring(v, _SC("TIMESTAMP"), -1); break;
	case MYSQL_TYPE_LONGLONG: sq_pushstring(v, _SC("LONGLONG"), -1); break;
	case MYSQL_TYPE_INT24: sq_pushstring(v, _SC("INT24"), -1); break;
	case MYSQL_TYPE_DATE: sq_pushstring(v, _SC("DATE"), -1); break;
	case MYSQL_TYPE_TIME: sq_pushstring(v, _SC("TIME"), -1); break;
	case MYSQL_TYPE_DATETIME: sq_pushstring(v, _SC("DATETIME"), -1); break;
	case MYSQL_TYPE_YEAR: sq_pushstring(v, _SC("YEAR"), -1); break;
	case MYSQL_TYPE_NEWDATE: sq_pushstring(v, _SC("NEWDATE"), -1); break;
	case MYSQL_TYPE_VARCHAR: sq_pushstring(v, _SC("VARCHAR"), -1); break;
	case MYSQL_TYPE_BIT: sq_pushstring(v, _SC("BIT"), -1); break;
	case MYSQL_TYPE_NEWDECIMAL: sq_pushstring(v, _SC("NEWDECIMAL"), -1); break;
	case MYSQL_TYPE_ENUM: sq_pushstring(v, _SC("ENUM"), -1); break;
	case MYSQL_TYPE_SET: sq_pushstring(v, _SC("SET"), -1); break;
	case MYSQL_TYPE_TINY_BLOB: sq_pushstring(v, _SC("TINY_BLOB"), -1); break;
	case MYSQL_TYPE_MEDIUM_BLOB: sq_pushstring(v, _SC("MEDIUM_BLOB"), -1); break;
	case MYSQL_TYPE_LONG_BLOB: sq_pushstring(v, _SC("LONG_BLOB"), -1); break;
	case MYSQL_TYPE_BLOB: sq_pushstring(v, _SC("BLOB"), -1); break;
	case MYSQL_TYPE_VAR_STRING: sq_pushstring(v, _SC("VAR_STRING"), -1); break;
	case MYSQL_TYPE_STRING: sq_pushstring(v, _SC("STRING"), -1); break;
	case MYSQL_TYPE_GEOMETRY: sq_pushstring(v, _SC("GEOMETRY"), -1); break;
	default: sq_pushinteger(v, mField->type); break;
	}
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, _SC("not_null"), -1);
	sq_pushbool(v, mField->flags & NOT_NULL_FLAG);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, _SC("primary_key"), -1);
	sq_pushbool(v, mField->flags & PRI_KEY_FLAG);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, _SC("unique_key"), -1);
	sq_pushbool(v, mField->flags & UNIQUE_KEY_FLAG);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, _SC("blob"), -1);
	sq_pushbool(v, mField->flags & BLOB_FLAG);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, _SC("unsigned"), -1);
	sq_pushbool(v, mField->flags & UNSIGNED_FLAG);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, _SC("zerofill"), -1);
	sq_pushbool(v, mField->flags & ZEROFILL_FLAG);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, _SC("binary"), -1);
	sq_pushbool(v, mField->flags & BINARY_FLAG);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, _SC("flags"), -1);
	sq_pushinteger(v, mField->flags);
	sq_newslot(v, -3, SQFalse);

	sq_push(v, -1);

	delete mField;

	return 1;
}

int CSQMysql::_mysql_field_type(SQVM * v)
{
	MYSQL_RES * pMySql = NULL;

	sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);

	if(!pMySql) return 0;

	if(sq_gettop(v) >= 3)
	{
		int iFieldOffset = 0;
		sq_getinteger(v, 3, &iFieldOffset);
		mysql_field_seek(pMySql, iFieldOffset);
	}

	MYSQL_FIELD * mField = mysql_fetch_field(pMySql);
	
	switch(mField->type)
	{
	case MYSQL_TYPE_DECIMAL: sq_pushstring(v, _SC("DECIMAL"), -1); break;
	case MYSQL_TYPE_TINY: sq_pushstring(v, _SC("TINY"), -1); break;
	case MYSQL_TYPE_SHORT: sq_pushstring(v, _SC("SHORT"), -1); break;
	case MYSQL_TYPE_LONG: sq_pushstring(v, _SC("LONG"), -1); break;
	case MYSQL_TYPE_FLOAT: sq_pushstring(v, _SC("FLOAT"), -1); break;
	case MYSQL_TYPE_DOUBLE: sq_pushstring(v, _SC("DOUBLE"), -1); break;
	case MYSQL_TYPE_NULL: sq_pushstring(v, _SC("NULL"), -1); break;
	case MYSQL_TYPE_TIMESTAMP: sq_pushstring(v, _SC("TIMESTAMP"), -1); break;
	case MYSQL_TYPE_LONGLONG: sq_pushstring(v, _SC("LONGLONG"), -1); break;
	case MYSQL_TYPE_INT24: sq_pushstring(v, _SC("INT24"), -1); break;
	case MYSQL_TYPE_DATE: sq_pushstring(v, _SC("DATE"), -1); break;
	case MYSQL_TYPE_TIME: sq_pushstring(v, _SC("TIME"), -1); break;
	case MYSQL_TYPE_DATETIME: sq_pushstring(v, _SC("DATETIME"), -1); break;
	case MYSQL_TYPE_YEAR: sq_pushstring(v, _SC("YEAR"), -1); break;
	case MYSQL_TYPE_NEWDATE: sq_pushstring(v, _SC("NEWDATE"), -1); break;
	case MYSQL_TYPE_VARCHAR: sq_pushstring(v, _SC("VARCHAR"), -1); break;
	case MYSQL_TYPE_BIT: sq_pushstring(v, _SC("BIT"), -1); break;
	case MYSQL_TYPE_NEWDECIMAL: sq_pushstring(v, _SC("NEWDECIMAL"), -1); break;
	case MYSQL_TYPE_ENUM: sq_pushstring(v, _SC("ENUM"), -1); break;
	case MYSQL_TYPE_SET: sq_pushstring(v, _SC("SET"), -1); break;
	case MYSQL_TYPE_TINY_BLOB: sq_pushstring(v, _SC("TINY_BLOB"), -1); break;
	case MYSQL_TYPE_MEDIUM_BLOB: sq_pushstring(v, _SC("MEDIUM_BLOB"), -1); break;
	case MYSQL_TYPE_LONG_BLOB: sq_pushstring(v, _SC("LONG_BLOB"), -1); break;
	case MYSQL_TYPE_BLOB: sq_pushstring(v, _SC("BLOB"), -1); break;
	case MYSQL_TYPE_VAR_STRING: sq_pushstring(v, _SC("VAR_STRING"), -1); break;
	case MYSQL_TYPE_STRING: sq_pushstring(v, _SC("STRING"), -1); break;
	case MYSQL_TYPE_GEOMETRY: sq_pushstring(v, _SC("GEOMETRY"), -1); break;
	default: sq_pushinteger(v, mField->type); break;
	}

	delete mField;

	return 1;
}

int CSQMysql::_mysql_field_name(SQVM * v)
{
	MYSQL_RES * pMySql = NULL;

	sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);

	if(!pMySql) return 0;

	if(sq_gettop(v) >= 3)
	{
		int iFieldOffset = 0;
		sq_getinteger(v, 3, &iFieldOffset);
		mysql_field_seek(pMySql, iFieldOffset);
	}

	MYSQL_FIELD * mField = mysql_fetch_field(pMySql);
#ifndef UNICODE
	sq_pushstring(v, mField->name, -1);
#else
	int iLen = strlen(mField->name);
	wchar_t * pData = new wchar_t[iLen + 1];
	mbstowcs(pData, mField->name, iLen);
	sq_pushstring(v, pData, -1);
#endif
	delete mField;

	return 1;
}

int CSQMysql::_mysql_field_table(SQVM * v)
{
	MYSQL_RES * pMySql = NULL;

	sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);

	if(!pMySql) return 0;

	if(sq_gettop(v) >= 3)
	{
		int iFieldOffset = 0;
		sq_getinteger(v, 3, &iFieldOffset);
		mysql_field_seek(pMySql, iFieldOffset);
	}

	MYSQL_FIELD * mField = mysql_fetch_field(pMySql);
#ifndef UNICODE
	sq_pushstring(v, mField->table, -1);
#else
	int iLen = strlen(mField->table);
	wchar_t * pData = new wchar_t[iLen + 1];
	mbstowcs(pData, mField->table, iLen);
	sq_pushstring(v, pData, -1);
#endif
	delete mField;

	return 1;
}

int CSQMysql::_mysql_field_len(SQVM * v)
{
	MYSQL_RES * pMySql = NULL;

	sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);

	if(!pMySql) return 0;

	if(sq_gettop(v) >= 3)
	{
		int iFieldOffset = 0;
		sq_getinteger(v, 3, &iFieldOffset);
		mysql_field_seek(pMySql, iFieldOffset);
	}

	MYSQL_FIELD * mField = mysql_fetch_field(pMySql);
	
	sq_newtable(v); 
	sq_pushinteger(v, mField->max_length);
	delete mField;

	return 1;
}

int CSQMysql::_mysql_field_flags(SQVM * v)
{
	MYSQL_RES * pMySql = NULL;

	sq_getuserpointer(v, 2, (SQUserPointer *)&pMySql);

	if(!pMySql) return 0;

	if(sq_gettop(v) >= 3)
	{
		int iFieldOffset = 0;
		sq_getinteger(v, 3, &iFieldOffset);
		mysql_field_seek(pMySql, iFieldOffset);
	}

	MYSQL_FIELD * mField = mysql_fetch_field(pMySql);
	
	sq_newtable(v); 

	sq_pushstring(v, _SC("not_null"), -1);
	sq_pushbool(v, mField->flags & NOT_NULL_FLAG);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, _SC("primary_key"), -1);
	sq_pushbool(v, mField->flags & PRI_KEY_FLAG);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, _SC("unique_key"), -1);
	sq_pushbool(v, mField->flags & UNIQUE_KEY_FLAG);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, _SC("blob"), -1);
	sq_pushbool(v, mField->flags & BLOB_FLAG);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, _SC("unsigned"), -1);
	sq_pushbool(v, mField->flags & UNSIGNED_FLAG);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, _SC("zerofill"), -1);
	sq_pushbool(v, mField->flags & ZEROFILL_FLAG);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, _SC("binary"), -1);
	sq_pushbool(v, mField->flags & BINARY_FLAG);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, _SC("flags"), -1);
	sq_pushinteger(v, mField->flags);
	sq_newslot(v, -3, SQFalse);

	sq_push(v, -1);

	delete mField;

	return 1;
}

int CSQMysql::_mysql_result(SQVM * v)
{
	MYSQL_RES * pRes = NULL;
	int iRowOffset = 0;
	int iFieldOffset = -1;

	sq_getuserpointer(v, 2, (SQUserPointer *)&pRes);

	sq_getinteger(v, 3, &iRowOffset);
	mysql_data_seek(pRes, iRowOffset);

	if(sq_gettop(v) >= 4)
	{
		sq_getinteger(v, 4, &iFieldOffset);
	}

	if(!pRes) return 0;

	MYSQL_ROW mRow = mysql_fetch_row(pRes);

	if(iFieldOffset >= 0) 
	{
#ifndef UNICODE
		sq_pushstring(v, mRow[iFieldOffset], -1);
#else
		int iLen = strlen(mRow[iFieldOffset]);
		wchar_t * pRow = new wchar_t[iLen+1];
		mbstowcs(pRow, mRow[iFieldOffset], iLen);
		sq_pushstring(v, pRow, -1);
#endif
	}
	else
	{
		unsigned int dwNumFields = mysql_num_fields(pRes);

		sq_newarray(v, 0);
		for(unsigned int i = 0; i < dwNumFields; i++)
		{
#ifndef UNICODE
		sq_pushstring(v, mRow[i], -1);
#else
		int iLen = strlen(mRow[i]);
		wchar_t * pRow = new wchar_t[iLen+1];
		mbstowcs(pRow, mRow[i], iLen);
		sq_pushstring(v, pRow, -1);
#endif
			sq_arrayappend(v, -2);
		}
		sq_push(v, -1);
	}

	return 1;
}

int CSQMysql::_mysql_fetch_assoc(SQVM * v)
{
	MYSQL_RES * pRes = NULL;
	sq_getuserpointer(v, 2, (SQUserPointer *)&pRes);

	if(!pRes) return 0;

	MYSQL_ROW mRow = mysql_fetch_row(pRes);

	unsigned int dwNumFields = mysql_num_fields(pRes);

	sq_newtable(v); 

	for(unsigned int i = 0; i < dwNumFields; i++)
	{
		MYSQL_FIELD * pField = mysql_fetch_field(pRes);
#ifndef UNICODE
		sq_pushstring(v, pField->name, -1);
		sq_pushstring(v, mRow[i], -1);
#else
		int iLen = strlen(pField->name);
		wchar_t * pRow = new wchar_t[iLen+1];
		mbstowcs(pRow, pField->name, iLen);
		sq_pushstring(v, pRow, -1);

		iLen = strlen(mRow[i]);
		pRow = new wchar_t[iLen+1];
		mbstowcs(pRow, mRow[i], iLen);
		sq_pushstring(v, pRow, -1);
#endif
		sq_newslot(v, -3, SQFalse);
	}
    sq_push(v, -1);

	return 1;
}

int CSQMysql::_mysql_fetch_array(SQVM * v)
{
	MYSQL_RES * pRes = NULL;
	sq_getuserpointer(v, 2, (SQUserPointer *)&pRes);

	if(!pRes) return 0;

	MYSQL_ROW mRow = mysql_fetch_row(pRes);

	unsigned int dwNumFields = mysql_num_fields(pRes);

	sq_newtable(v); 

	for(unsigned int i = 0; i < dwNumFields; i++)
	{
		MYSQL_FIELD * pField = mysql_fetch_field(pRes);
#ifndef UNICODE
		sq_pushstring(v, pField->name, -1);
		sq_pushstring(v, mRow[i], -1);
#else
		int iLen = strlen(pField->name);
		wchar_t * pRow = new wchar_t[iLen+1];
		mbstowcs(pRow, pField->name, iLen);
		sq_pushstring(v, pRow, -1);

		iLen = strlen(mRow[i]);
		pRow = new wchar_t[iLen+1];
		mbstowcs(pRow, mRow[i], iLen);
		sq_pushstring(v, pRow, -1);
#endif
		sq_newslot(v, -3, SQFalse);

		sq_pushinteger(v, i);
#ifndef UNICODE
		sq_pushstring(v, mRow[i], -1);
#else
		sq_pushstring(v, pRow, -1);
#endif
		sq_newslot(v, -3, SQFalse);
	}
    sq_push(v, -1);

	return 1;
}