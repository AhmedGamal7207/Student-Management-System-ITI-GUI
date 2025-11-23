#include "Student.h"


// Constructors:
Student::Student(){
    id = 0;
    name = "";
    age = 0;
    department = "";
    gpa = 0;
}

Student::Student(int i, string n, int a, string d, float g){
    id = i;
    name = n;
    age = a;
    department = d;
    gpa = g;
}

Student::Student(string n, int a, string d, float g){
    id = 0;
    name = n;
    age = a;
    department = d;
    gpa = g;
}

// Setters:
int Student::get_id()
{
    return id;
}
int Student::get_age()
{
    return age;
}
string Student::get_name()
{
    return name;
}
string Student::get_department()
{
    return department;
}
float Student::get_gpa()
{
    return gpa;
}

// Getters:
void Student::set_id(int i)
{
    id = i;
}
void Student::set_age(int a)
{
    age = a;
}
void Student::set_name(string n)
{
    name = n;
}
void Student::set_department(int d)
{
    department = d;
}
void Student::set_gpa(float g)
{
    gpa = g;
}

void Student::print_student(){
    cout << "Student ID: " << id << endl;
    cout << "Student Name: " << name << endl;
    cout << "Student Age: " << age << endl;
    cout << "Student Department: " << department << endl;
    cout << "Student GPA: " << gpa << endl << endl;
}