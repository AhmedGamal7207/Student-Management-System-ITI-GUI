#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <iostream>
#include <mysql/mysql.h>
#include <string.h>
#include <vector>

using namespace std;

class MyDatabase{
    MYSQL* conn = nullptr;
    MYSQL_RES* result = nullptr;
    public:
        MyDatabase();
        ~MyDatabase();
        
        void connect_to_db();
        int execute_query(const char* query, int print = 0);
        vector<string> get_columns_names(string table_name, int print = 0);
        void print_query_result();
        my_ulonglong get_last_insert_id();

        MYSQL_RES* get_result();
        
};

#endif