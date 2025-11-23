#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string.h>

using namespace std;

class Student{
    int id;
    int age;
    string name;
    string department;
    float gpa;
    
    public:
        Student();
        Student(int i, string n, int a, string d, float g);
        Student(string n, int a, string d, float g);

        int get_id();
        int get_age();
        string get_name();
        string get_department();
        float get_gpa();

        void set_id(int i);
        void set_age(int a);
        void set_name(string n);
        void set_department(int d);
        void set_gpa(float g);

        void print_student();
};

#endif