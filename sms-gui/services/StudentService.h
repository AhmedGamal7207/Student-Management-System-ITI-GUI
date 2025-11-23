#ifndef STUDENT_SERVICE_H
#define STUDENT_SERVICE_H

#include <iostream>
#include <string.h>
#include <vector>
#include <mysql/mysql.h>
#include <fstream> 
#include "../database_models/MyDatabase.h"
#include "../models/Student.h"

using namespace std;

class StudentService
{
    MyDatabase& db;

    public:
        StudentService(MyDatabase& d);
        void add_student(Student& s);
        void delete_student(int id);
        Student search_student_id(int id, int print = 0);
        vector<Student> search_student_name(string name, int print = 0);
        vector<Student> search_student_in_name(string name, int print = 0);
        void update_student(int id, string column_name, string new_value);
        vector<Student> get_all_students(int print = 0, int top = 0);
        void export_students_csv();
};

#endif
