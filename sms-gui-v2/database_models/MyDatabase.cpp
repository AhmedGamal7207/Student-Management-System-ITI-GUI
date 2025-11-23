#include "MyDatabase.h"

#define host "127.0.0.1"
#define user "python_user"
#define password "Ahmedgamal619"
#define database "iti_first_proj"
#define port 3306

MyDatabase::MyDatabase() {
    conn = mysql_init(nullptr);
    if (conn == nullptr) {
        cerr << "Couldn't initialize MySQL connection";
        return;
    }

    connect_to_db();
    //cout << "Connected to MySQL Database successfully!" << endl << endl;
    result = nullptr;
}

void MyDatabase::connect_to_db() {
    if (mysql_real_connect(conn, host, user, password, database, port, nullptr, 0) == nullptr) {
        cerr << "Error while connecting to MySQL: " << mysql_error(conn) << endl;
        mysql_close(conn);
        conn = nullptr;
    }
}

int MyDatabase::execute_query(const char* query,int print) 
{
    if (result) {
        mysql_free_result(result);
        result = nullptr;
    }

    if (mysql_query(conn, query)) {
        cerr << "Error while running this query: " << query << endl
             << "Error is: " << mysql_error(conn);
        return 1;
    }

    result = mysql_store_result(conn);

    if (print) {
        print_query_result();
    }

    return 0;
}

vector<string> MyDatabase::get_columns_names(string table_name, int print)
{
    vector<string> columns;
    string query = "SHOW COLUMNS FROM ";
    query += table_name;
    query += ";";

    if (mysql_query(conn, query.c_str())) {
        cerr << "Error while running this query: " << query << endl
             << "Error is: " << mysql_error(conn);
        return columns;
    }
    result = mysql_store_result(conn);

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        columns.push_back(row[0]);
    }

    if(print)
    {
        for (string col : columns){
            cout << col << endl;
        }
    }

    return columns;
}

void MyDatabase::print_query_result() {
    int num_fields = mysql_num_fields(result);
    
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < num_fields; ++i) {
            cout << (row[i] ? row[i] : "NULL") << " | ";
        }
        cout << endl;
    }
}

MYSQL_RES* MyDatabase::get_result()
{
    return result;
}

my_ulonglong MyDatabase::get_last_insert_id()
{
    return mysql_insert_id(conn);
}

MyDatabase::~MyDatabase() {
    if (result){
        mysql_free_result(result);
    }
    if (conn)
    {
        mysql_close(conn);
    }       
}
