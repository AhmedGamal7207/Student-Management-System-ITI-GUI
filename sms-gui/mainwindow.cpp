#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "models/Student.h"

#include <vector>
#include <sstream>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ss = new StudentService(db);
    ui->lbl->setText("Database Connected Successfully.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_clicked()
{
    ui->lbl->setText("Here are all students data.");
    vector<Student> students = ss->get_all_students();
    string print_all = "student_id,name,age,department,gpa,\n";
    for (Student& s : students){
        std::ostringstream gpa_stream;
        gpa_stream << std::fixed << std::setprecision(2) << s.get_gpa();
        string gpa_str = gpa_stream.str();
        print_all += to_string(s.get_id()) + ","
                      + s.get_name() + ","
                     + to_string(s.get_age()) + ","
                      + s.get_department() + ","
                     + gpa_str + "\n";
    }
    ui->long_lbl->setText(print_all.c_str());
}

void MainWindow::on_btn_top_clicked()
{
    ui->lbl->setText("Here are data of top 5 students.");
    vector<Student> top_students = ss->get_all_students(1,1);
    string print_all = "student_id,name,age,department,gpa,\n";
    for (Student& s : top_students){
        std::ostringstream gpa_stream;
        gpa_stream << std::fixed << std::setprecision(2) << s.get_gpa();
        string gpa_str = gpa_stream.str();
        print_all += to_string(s.get_id()) + ","
                     + s.get_name() + ","
                     + to_string(s.get_age()) + ","
                     + s.get_department() + ","
                     + gpa_str + "\n";
    }
    ui->long_lbl->setText(print_all.c_str());
}

void MainWindow::on_btn_csv_clicked()
{
    ui->long_lbl->setText("");
    ui->lbl->setText("Exporting students data to CSV.");
    ss->export_students_csv();
    ui->lbl->setText("Students data has been exported to students.csv successfully");
}

