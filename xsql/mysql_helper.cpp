// mysql_helper.cpp.cpp created by xstudio 
//Wed Jul 02:19:09 2019

#include "mysql.h"


struct MysqlResultSet{
	MYSQL_RES * __h_result;
	MYSQL_ROW	__h_cur_row;
	unsigned int __fieldcount;
};


MysqlResultSet * create_rs(MYSQL_RES * res){
    MysqlResultSet rs = new MysqlResultSet();
    rs->__h_result = res;
    rs->__fieldcount = mysql_num_fields(__h_result);
    return rs;
}

void free_rs(MysqlResultSet * rs){
    if (rs->__h_result != nilptr){
        mysql_free_result(rs->__h_result);
        rs->__h_result = nilptr;
    }
    delete rs;
}
    
bool first(MysqlResultSet * rs){
    mysql_data_seek(rs->__h_result, 0);
    mysql_row_seek(rs->__h_result, mysql_row_tell(rs->__h_result));
    return next(rs);
}

int label2Index(MysqlResultSet * rs, const char* label){
    for (unsigned int i = 0; i < rs->__fieldcount; i++) {
        MYSQL_FIELD * field = mysql_fetch_field_direct(rs->__h_result, i);
        if (strncmp(field->name, label, field->name_length) == 0){
            return i;
        }
    }
    return -1;
}

bool last(MysqlResultSet * rs){
    mysql_data_seek(rs->__h_result, getRowCount());
    mysql_row_seek(rs->__h_result, mysql_row_tell(rs->__h_result));
    return next(rs);
}


bool next(MysqlResultSet * rs){
    rs->__h_cur_row = mysql_fetch_row(rs->__h_result);
    return rs->__h_cur_row != nilptr;
}

long long getRowCount(MysqlResultSet * rs){
    return mysql_num_rows(rs->__h_result);
}

bool isValid(MysqlResultSet * rs){
    return rs->__h_cur_row != nilptr;
}

const char * getValue(MysqlResultSet * rs, const char * key){
    int idx = label2Index(rs, key);
    if (idx != -1){
        return rs->__h_cur_row[idx];
    }
    return nilptr;
}
