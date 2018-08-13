#pragma once

#include "SQUIRREL/squirrel.h"
#include "mysql/my_global.h"
#include "mysql/mysql.h"
#include <vector>

class CSQMysql
{
public:
	CSQMysql(SQVM * v);
	~CSQMysql();

private:
	static MYSQL * pLastMysql;
	static std::vector<MYSQL *> vAllMySql;

	static int _mysql_connect(SQVM * v); // MYSQL_POINTER mysql_connect(string server, string user, string password)
	static int _mysql_close(SQVM * v); // void mysql_close([MYSQL_POINTER mp])
	static int _mysql_select_db(SQVM * v); // void mysql_select_db(string database [, MYSQL_POINTER mp])
	static int _mysql_errno(SQVM * v); // integer mysql_errno([MYSQL_POINTER mp])
	static int _mysql_error(SQVM * v); // string mysql_error([MYSQL_POINTER mp])
	static int _mysql_ping(SQVM * v); // integer mysql_ping([MYSQL_POINTER mp])
	static int _mysql_change_user(SQVM * v); // integer mysql_change_user(string user, string password [, string database [, MYSQL_POINTER mp]]) 
	static int _mysql_query(SQVM * v); // MYSQL_RESULT mysql_query(string query [, MYSQL_POINTER mp])
	static int _mysql_free_result(SQVM * v); // void mysql_free_result(MYSQL_RESULT mr)
	static int _mysql_insert_id(SQVM * v); // integer mysql_insert_id([MYSQL_POINTER mp])
	static int _mysql_data_seek(SQVM * v); // void mysql_data_seek(MYSQL_RESULT mr, integer offset)
	static int _mysql_row_seek(SQVM * v); // void mysql_row_seek(MYSQL_RESULT mr, integer offset)
	static int _mysql_field_seek(SQVM * v); // void mysql_field_seek(MYSQL_RESULT mr, integer offset)
	static int _mysql_num_rows(SQVM * v); // integer mysql_num_rows(MYSQL_RESULT mr)
	static int _mysql_num_fields(SQVM * v); // integer mysql_num_fields(MYSQL_RESULT mr)
	static int _mysql_fetch_row(SQVM * v);  // array mysql_num_fields(MYSQL_RESULT mr)
	static int _mysql_fetch_array(SQVM * v); // table mysql_num_fields(MYSQL_RESULT mr)
	static int _mysql_fetch_assoc(SQVM * v); // table mysql_num_fields(MYSQL_RESULT mr)
	static int _mysql_result(SQVM * v); // // string mysql_num_fields(MYSQL_RESULT mr, integer row_offset [, integer field_offset])
	static int _mysql_get_host_info(SQVM * v); // string mysql_get_host_info([MYSQL_POINTER mp])
	static int _mysql_get_client_info(SQVM * v); // string mysql_get_client_info()
	static int _mysql_get_proto_info(SQVM * v); // integer mysql_get_proto_info([MYSQL_POINTER mp])
	static int _mysql_get_server_info(SQVM * v); // string mysql_get_server_info([MYSQL_POINTER mp])
	static int _mysql_info(SQVM * v); // string mysql_info([MYSQL_POINTER mp])
	static int _mysql_list_dbs(SQVM * v); // MYSQL_RESULT mysql_list_dbs([MYSQL_POINTER mp])
	static int _mysql_list_fields(SQVM * v); // MYSQL_RESULT mysql_list_fields([MYSQL_POINTER mp])
	static int _mysql_list_processes(SQVM * v); // MYSQL_RESULT mysql_list_processes([MYSQL_POINTER mp])
	static int _mysql_list_tables(SQVM * v); // MYSQL_RESULT mysql_list_tables([MYSQL_POINTER mp])
	static int _mysql_stat(SQVM * v); // string mysql_stat([MYSQL_POINTER mp])
	static int _mysql_thread_id(SQVM * v); // integer mysql_thread_id([MYSQL_POINTER mp])
	static int _mysql_affected_rows(SQVM * v); // ineger mysql_affected_rows([MYSQL_POINTER mp])
	static int _mysql_fetch_lengths(SQVM * v); // array mysql_fetch_lengths(MYSQL_RESULT mr)
	static int _mysql_real_escape_string(SQVM * v); // string mysql_real_escape_string(string data)
	static int _mysql_escape_string(SQVM * v); // string mysql_escape_string(string data)
	static int _mysql_fetch_field(SQVM * v); // table mysql_field_field(MYSQL_RESULT mr [, integer offset])
	static int _mysql_field_name(SQVM * v); // string mysql_field_name(MYSQL_RESULT mr [, integer offset])
	static int _mysql_field_table(SQVM * v); // string mysql_field_table(MYSQL_RESULT mr [, integer offset])
	static int _mysql_field_len(SQVM * v); // integer mysql_field_len(MYSQL_RESULT mr [, integer offset])
	static int _mysql_field_type(SQVM * v); // string mysql_field_type(MYSQL_RESULT mr [, integer offset])
	static int _mysql_field_flags(SQVM * v); // table mysql_field_flags(MYSQL_RESULT mr [, integer offset])
};