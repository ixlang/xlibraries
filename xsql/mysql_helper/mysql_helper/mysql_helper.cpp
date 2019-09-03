// mysql_helper.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "string.h"
#include <stdio.h>
// mysql_helper.cpp.cpp created by xstudio 
//Wed Jul 02:19:09 2019

#ifdef WIN32
#define XCDECL __cdecl
#else
#define XCDECL __attribute__((__cdecl__))
#endif

#define STDC extern "C"

struct MysqlResultSet{
	MYSQL_RES * __h_result;
	MYSQL_ROW	__h_cur_row;
	unsigned int __fieldcount;
};

STDC MysqlResultSet * XCDECL rs_create(MYSQL_RES * res){
	MysqlResultSet * rs = new MysqlResultSet();
	rs->__h_result = res;
	rs->__fieldcount = mysql_num_fields(rs->__h_result);
	return rs;
}

STDC void XCDECL rs_free(MysqlResultSet * rs){
	if (rs->__h_result != 0){
		mysql_free_result(rs->__h_result);
		rs->__h_result = 0;
	}
	delete rs;
}

STDC bool XCDECL rs_next(MysqlResultSet * rs){
	rs->__h_cur_row = mysql_fetch_row(rs->__h_result);
	return rs->__h_cur_row != 0;
}

STDC bool XCDECL rs_first(MysqlResultSet * rs){
	mysql_data_seek(rs->__h_result, 0);
	mysql_row_seek(rs->__h_result, mysql_row_tell(rs->__h_result));
	return rs_next(rs);
}

STDC int XCDECL rs_label2Index(MysqlResultSet * rs, const char* label){
	for (unsigned int i = 0; i < rs->__fieldcount; i++) {
		MYSQL_FIELD * field = mysql_fetch_field_direct(rs->__h_result, i);
		if (strncmp(field->name, label, field->name_length) == 0){
			return i;
		}
	}
	return -1;
}

STDC long long XCDECL rs_getRowCount(MysqlResultSet * rs){
	return mysql_num_rows(rs->__h_result);
}

STDC bool XCDECL rs_last(MysqlResultSet * rs){
	mysql_data_seek(rs->__h_result, rs_getRowCount(rs));
	mysql_row_seek(rs->__h_result, mysql_row_tell(rs->__h_result));
	return rs_next(rs);
}

STDC bool XCDECL rs_isValid(MysqlResultSet * rs){
	return rs->__h_cur_row != 0;
}

STDC bool XCDECL rs_isLast(MysqlResultSet * rs){
	return mysql_eof(rs->__h_result) != 0;
}

STDC const char * XCDECL rs_getValue(MysqlResultSet * rs, const char * key){
	int idx = rs_label2Index(rs, key);
	if (idx != -1){
		return rs->__h_cur_row[idx];
	}
	return 0;
}

STDC int XCDECL rs_getValueI(MysqlResultSet * rs, const char * key){
	int idx = rs_label2Index(rs, key);
	if (idx != -1){
		return atoi(rs->__h_cur_row[idx]);
	}
	return 0;
}

STDC long long XCDECL rs_getValueL(MysqlResultSet * rs, const char * key){
	int idx = rs_label2Index(rs, key);
	if (idx != -1){
#ifdef WIN32
		return _atoi64(rs->__h_cur_row[idx]);
#else
		return atoll(rs->__h_cur_row[idx]);
#endif
	}
	return 0;
}

STDC double XCDECL rs_getValueD(MysqlResultSet * rs, const char * key){
	int idx = rs_label2Index(rs, key);
	if (idx != -1){
		return atof(rs->__h_cur_row[idx]);
	}
	return 0;
}




STDC const char * XCDECL rs_getIValue(MysqlResultSet * rs, int idx){
	if (idx != -1 && idx < rs->__fieldcount){
		return rs->__h_cur_row[idx];
	}
	return 0;
}

STDC int XCDECL rs_getIValueI(MysqlResultSet * rs, int idx){
	if (idx != -1 && idx < rs->__fieldcount){
		return atoi(rs->__h_cur_row[idx]);
	}
	return 0;
}

STDC long long XCDECL rs_getIValueL(MysqlResultSet * rs, int idx){
	if (idx != -1 && idx < rs->__fieldcount){
#ifdef WIN32
		return _atoi64(rs->__h_cur_row[idx]);
#else
		return atoll(rs->__h_cur_row[idx]);
#endif
	}
	return 0;
}

STDC double XCDECL rs_getIValueD(MysqlResultSet * rs, int idx){
	if (idx != -1 && idx < rs->__fieldcount){
		return atof(rs->__h_cur_row[idx]);
	}
	return 0;
}

STDC MYSQL * XCDECL x_mysql_init(MYSQL *mysql){
	return mysql_init(mysql);
}

STDC int XCDECL x_mysql_options(MYSQL *mysql, enum mysql_option option,
	const void *arg){
	return mysql_options(mysql, option, arg);
}

STDC MYSQL *		XCDECL x_mysql_real_connect(MYSQL *mysql, const char *host,
	const char *user,
	const char *passwd,
	const char *db,
	unsigned int port,
	const char *unix_socket,
	unsigned long clientflag)
{
	return mysql_real_connect(mysql, host, user, passwd, db, port, unix_socket, clientflag);
}


STDC int  XCDECL x_mysql_set_character_set(MYSQL *mysql, const char *csname){
	return mysql_set_character_set(mysql, csname);
}

STDC int	XCDECL x_mysql_select_db(MYSQL * p, const char * db){
	return mysql_select_db(p, db);
}

STDC int XCDECL x_mysql_errno(MYSQL * p){
	return mysql_errno(p);
}

STDC const char * XCDECL x_mysql_error(MYSQL * p){
	return mysql_error(p);
}

STDC const char * XCDECL x_mysql_state(MYSQL * p){
	return mysql_sqlstate(p);
}

STDC const char * XCDECL x_mysql_info(MYSQL * p){
	return mysql_info(p);
}

STDC int XCDECL x_mysql_query(MYSQL * p, const char * db){
	return mysql_query(p, db);
}

STDC void XCDECL x_mysql_close(MYSQL * p){
	mysql_close(p);
}

STDC MYSQL_RES  *   XCDECL x_mysql_store_result(MYSQL * mysql){
	return mysql_store_result(mysql);
}

STDC void XCDECL x_mysql_data_seek(MYSQL_RES *result,
	my_ulonglong offset)
{
	mysql_data_seek(result, offset);
}

STDC MYSQL_ROW_OFFSET XCDECL x_mysql_row_seek(MYSQL_RES *result,
	MYSQL_ROW_OFFSET offset){

	return mysql_row_seek(result, offset);
}

STDC MYSQL_ROW_OFFSET XCDECL x_mysql_row_tell(MYSQL_RES *res){

	return mysql_row_tell(res);
}

STDC MYSQL_ROW	XCDECL x_mysql_fetch_row(MYSQL_RES *result) {
	return mysql_fetch_row(result);
}

STDC my_ulonglong XCDECL x_mysql_num_rows(MYSQL_RES *res){
	return mysql_num_rows(res);
}

STDC void		XCDECL x_mysql_free_result(MYSQL_RES *result){
	return mysql_free_result(result);
}

STDC unsigned int XCDECL x_mysql_num_fields(MYSQL_RES *res){
	return mysql_num_fields(res);
}