#include "StudentService.h"

StudentService::StudentService(MyDatabase& d) :db(d){}

void StudentService::add_student(Student& s)
{
    string query = "INSERT INTO students(name, age, department, gpa) VALUES(";

    query += "'" + s.get_name() + "', ";
    query += to_string(s.get_age()) + ", ";
    query += "'" + s.get_department() + "', ";
    query += to_string(s.get_gpa());

    query += ");";

    if(db.execute_query(query.c_str()))
    {
        cout << endl << "Couldn't add student: " << s.get_id() << " to database" << endl;
        cout << endl;
        return;
    }

    s.set_id(db.get_last_insert_id());
    
    cout << "Student " << s.get_id() << " was successfully added to the database" << endl;
    cout << endl;
}

void StudentService::delete_student(int id)
{
    Student s = search_student_id(id);
    if(!s.get_id()){
        return;
    }

    string query = "DELETE FROM students WHERE student_id = " + to_string(id) + ";";
    if(db.execute_query(query.c_str()))
    {
        cout << endl << "Couldn't delete student: " << id << " from database" << endl;
        cout << endl;
        return;
    }
    
    cout << "Student " << id << " was successfully deleted from the database" << endl;
    cout << endl;
}

void StudentService::update_student(int id, string column_name, string new_value)
{
    string query = "UPDATE students SET ";

    query +=  column_name + " = '" + new_value + "' WHERE student_id = ";
    query += to_string(id);
    query += ";";

    if(db.execute_query(query.c_str()))
    {
        cout << endl << "Couldn't update student: " << id << " with " << column_name << " = " << new_value << endl;
        cout << endl;
        return;
    }

    cout << "Student " << id << " was successfully updated with " << column_name << " = " << new_value << endl;
    cout << endl;
}

Student StudentService::search_student_id(int id, int print)
{
    string query = "SELECT * FROM students WHERE student_id = " + to_string(id) + ";";

    if(db.execute_query(query.c_str()))
    {
        cout << endl << "Couldn't search for student: " << id << " in database" << endl;
        cout << endl;
        return Student();  
    }
    
    MYSQL_RES* result = db.get_result();

    MYSQL_ROW row = mysql_fetch_row(result);
    if(row != NULL)
    {
        Student s(stoi(row[0]), string(row[1]), stoi(row[2]), string(row[3]), stof(row[4]));
        if(print)
        {
            cout << "Student " << id << " data was retrieved from the database" << endl;
            s.print_student();
        }
        cout << endl;
        return s;
    }
    else
    {
        cout << "Couldn't find any students with id = " << id << endl;
        cout << endl;
        return Student();
    }
    
}

vector<Student> StudentService::get_all_students(int print, int top)
{
    vector<Student> students;
    string query;
    if(top)
    {
        query = "SELECT * FROM students ORDER BY gpa DESC LIMIT 5;";
    }
    else
    {
        query = "SELECT * FROM students;";
    }
    

    if(db.execute_query(query.c_str()))
    {
        cout << endl << "Couldn't get all students from database" << endl;
        cout << endl;
        return students;  
    }
    
    MYSQL_RES* result = db.get_result();

    MYSQL_ROW row;
    while((row = mysql_fetch_row(result)))
    {
        Student s(stoi(row[0]), string(row[1]), stoi(row[2]), string(row[3]), stof(row[4]));
        students.push_back(s);
    }
    
    if(students.empty())
    {
        cout << "There are no students currently stored in the database" << endl;
    }
    else
    {
        if(print){
            for(Student& s : students){
                s.print_student();
            }
        }
    }
    cout << endl;
    return students;
}

vector<Student> StudentService::search_student_name(string name, int print)
{
    vector<Student> students;
    string query = "SELECT * FROM students WHERE name = '" + name + "';";

    if(db.execute_query(query.c_str()))
    {
        cout << endl << "Couldn't search for students with name: " << name << " in database" << endl;
        cout << endl;
        return students;  
    }
    
    MYSQL_RES* result = db.get_result();

    MYSQL_ROW row;
    while((row = mysql_fetch_row(result)))
    {
        Student s(stoi(row[0]), string(row[1]), stoi(row[2]), string(row[3]), stof(row[4]));
        students.push_back(s);
    }
    
    if(students.empty())
    {
        cout << "There are no students in the database with this name: " << name << endl;
    }
    else
    {
        if(print){
            for(Student& s : students){
                s.print_student();
            }
        }
    }
    cout << endl;
    return students;
}

vector<Student> StudentService::search_student_in_name(string name, int print)
{
    vector<Student> students;
    string query = "SELECT * FROM students WHERE name like '" + name + "%';";

    if(db.execute_query(query.c_str()))
    {
        cout << endl << "Couldn't search for students with name: " << name << " in database" << endl;
        cout << endl;
        return students;  
    }
    
    MYSQL_RES* result = db.get_result();

    MYSQL_ROW row;
    while((row = mysql_fetch_row(result)))
    {
        Student s(stoi(row[0]), string(row[1]), stoi(row[2]), string(row[3]), stof(row[4]));
        students.push_back(s);
    }
    
    if(students.empty())
    {
        cout << "There are no students in the database with this name: " << name << endl;
    }
    else
    {
        if(print){
            for(Student& s : students){
                s.print_student();
            }
        }
    }
    cout << endl;
    return students;
}

void StudentService::export_students_csv()
{
    ofstream students_file("students.csv");

    if (!students_file.is_open()) {
        cout << endl << "Error: Could not open file " << "students.csv" << endl << endl;
        return;
    }

    vector<Student> students = get_all_students();

    int students_count = students.size();
    students_file << "student_id,name,age,department,gpa" << "\n";
    
    for (int i=0; i<students_count; i++)
    {
        students_file << students[i].get_id() << ","
        << students[i].get_name() << ","
        << students[i].get_age() << ","
        << students[i].get_department() << ","
        << students[i].get_gpa() << "\n";
    }
    students_file.close();

    cout << endl << "Students have been exported successfully to students.csv file" << endl << endl;

}