#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDir>
#include <QMessageBox>
#include <string>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ss = new StudentService(db);
    update_dashboard();

    QPixmap pix(":/images/images/logo.png");
    ui->logoLabel->setPixmap(pix);
    ui->logoLabel->setScaledContents(true);

    ui->stackedWidget->setCurrentIndex(0);

    ui->table_search->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->btn_update->setEnabled(false);
    ui->btn_delete->setEnabled(false);

    ui->field_name_u->setEnabled(false);
    ui->field_age_u->setEnabled(false);
    ui->field_dept_u->setEnabled(false);
    ui->field_gpa_u->setEnabled(false);
    ui->field_name_d->setEnabled(false);
    ui->field_age_d->setEnabled(false);
    ui->field_dept_d->setEnabled(false);
    ui->field_gpa_d->setEnabled(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    ui->stackedWidget->setCurrentIndex(currentRow);
}


void MainWindow::on_stackedWidget_currentChanged(int index)
{
    if (index == 0) { // Dashboard
        update_dashboard();
    }
    else if (index == 1) { // Add Student

    }
    else if (index == 2) { // View Students
        update_view_students();
    }
    else if (index == 3) { // Search Students

    }
    else if (index == 4) { // Update Students

    }
    else if (index == 5) { // Delete Students

    }
}

void MainWindow::update_dashboard(){
    ui->label_students->setText(ss->get_students_count().c_str());
    ui->label_highest->setText(ss->get_highest_gpa().c_str());
    ui->label_lowest->setText(ss->get_lowest_gpa().c_str());

    vector<Student> top_students = ss->get_all_students(0,1);
    load_students_table(ui->table_top, top_students);
}

void MainWindow::update_view_students(){
    vector<Student> students = ss->get_all_students(0,0);
    load_students_table(ui->table_view, students);
}

void MainWindow::load_students_table(QTableWidget *table, vector<Student> students)
{
    table->clear();
    table->setColumnCount(5);
    QStringList headers;
    headers << "ID"
            << "Name"
            << "Age"
            << "Department"
            << "GPA";

    table->setHorizontalHeaderLabels(headers);

    table->setRowCount(students.size());
    for (int r = 0; r < students.size(); r++)
    {
        Student& s = students[r];

        QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(s.get_id()));
        idItem->setTextAlignment(Qt::AlignCenter);
        table->setItem(r, 0, idItem);

        QTableWidgetItem *nameItem = new QTableWidgetItem(QString::fromStdString(s.get_name()));
        nameItem->setTextAlignment(Qt::AlignCenter);
        table->setItem(r, 1, nameItem);

        QTableWidgetItem *ageItem = new QTableWidgetItem(QString::number(s.get_age()));
        ageItem->setTextAlignment(Qt::AlignCenter);
        table->setItem(r, 2, ageItem);

        QTableWidgetItem *depItem = new QTableWidgetItem(QString::fromStdString(s.get_department()));
        depItem->setTextAlignment(Qt::AlignCenter);
        table->setItem(r, 3, depItem);

        QTableWidgetItem *gpaItem = new QTableWidgetItem(QString::number(s.get_gpa(), 'f', 2));
        gpaItem->setTextAlignment(Qt::AlignCenter);
        table->setItem(r, 4, gpaItem);
    }
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::search_student(){
    QAbstractButton *checked = ui->buttonGroup->checkedButton();
    QString column_name = checked->text();

    column_name = column_name.replace(" ","_");
    column_name = column_name.toLower();

    QString search_value = ui->field_search_s->text();

    if (search_value.isEmpty()) {
        QMessageBox::warning(
            this,
            "Missing Input",
            "Please provide a search value before searching."
            );
        return;
    }

    vector<Student> students = ss->search_student_in_field(column_name.toStdString(), search_value.toStdString());
    load_students_table(ui->table_search,students);
}

void MainWindow::on_btn_search_s_clicked()
{
    search_student();
}


void MainWindow::on_btn_add_clicked()
{
    QString name = ui->field_name->text();
    QString age = ui->field_age->text();
    QString department = ui->field_dept->text();
    QString gpa = ui->field_gpa->text();
    if (name.isEmpty()) {
        QMessageBox::warning(
            this,
            "Missing Input",
            "Please enter student name."
            );
        return;
    }
    if (age.isEmpty()) {
        QMessageBox::warning(
            this,
            "Missing Input",
            "Please enter student age."
            );
        return;
    }
    if (department.isEmpty()) {
        QMessageBox::warning(
            this,
            "Missing Input",
            "Please enter student department."
            );
        return;
    }
    if (gpa.isEmpty()) {
        QMessageBox::warning(
            this,
            "Missing Input",
            "Please enter student gpa."
            );
        return;
    }

    bool age_validation;
    int age_int = age.toInt(&age_validation);
    if (!age_validation) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid Age.");
        return;
    }

    bool gpa_validation;
    float gpa_float = gpa.toFloat(&gpa_validation);
    if (!gpa_validation) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid GPA.");
        return;
    }

    Student s(name.toStdString(), age_int, department.toStdString(), gpa_float);
    ss->add_student(s);
    int inserted_id = db.get_last_insert_id();
    string message = "Student " + name.toStdString() + " has been added successfully with id = " + to_string(inserted_id);
    QString qmessage = QString::fromStdString(message);
    QMessageBox::information(this, "Student Added", qmessage);

    ui->field_name->clear();
    ui->field_age->clear();
    ui->field_dept->clear();
    ui->field_gpa->clear();
}


void MainWindow::on_btn_search_d_clicked()
{
    QString search_value = ui->field_search_d->text();

    if (search_value.isEmpty()) {
        QMessageBox::warning(
            this,
            "Missing Input",
            "Please provide student id you want to delete."
            );
        return;
    }

    Student s = ss->search_student_id(search_value.toInt());
    ui->field_name_d->setText(QString::fromStdString(s.get_name()));
    ui->field_age_d->setText(QString::fromStdString(to_string(s.get_age())));
    ui->field_dept_d->setText(QString::fromStdString(s.get_department()));
    ui->field_gpa_d->setText(QString::fromStdString(to_string(s.get_gpa())));

    id_to_delete = s.get_id();

    ui->btn_delete->setEnabled(true);
    ui->btn_search_d->setEnabled(false);
    ui->field_search_d->setEnabled(false);
}


void MainWindow::on_btn_new_s_clicked()
{
    ui->field_name_d->clear();
    ui->field_age_d->clear();
    ui->field_dept_d->clear();
    ui->field_gpa_d->clear();
    ui->field_search_d->clear();

    ui->btn_delete->setEnabled(false);
    ui->btn_search_d->setEnabled(true);
    ui->field_search_d->setEnabled(true);
}


void MainWindow::on_btn_delete_clicked()
{
    QString name = ui->field_name_d->text();
    QMessageBox::StandardButton answer;
    answer = QMessageBox::question(
        this,
        "Confirm Action",
        "Are you sure you want to delete "+name+" from database?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (answer == QMessageBox::Yes) {
        ss->delete_student(id_to_delete);
        QMessageBox::information(this, "Student Deleted", "Student "+name+" has been deleted from database successfully");
        on_btn_new_s_clicked();
    }
    else {

    }
}

void MainWindow::on_btn_search_u_clicked()
{
    QString search_value = ui->field_search_u->text();

    if (search_value.isEmpty()) {
        QMessageBox::warning(
            this,
            "Missing Input",
            "Please provide student id you want to update."
            );
        return;
    }

    Student s = ss->search_student_id(search_value.toInt());
    ui->field_name_u->setText(QString::fromStdString(s.get_name()));
    ui->field_age_u->setText(QString::fromStdString(to_string(s.get_age())));
    ui->field_dept_u->setText(QString::fromStdString(s.get_department()));
    ui->field_gpa_u->setText(QString::fromStdString(to_string(s.get_gpa())));

    ui->field_name_u->setEnabled(true);
    ui->field_age_u->setEnabled(true);
    ui->field_dept_u->setEnabled(true);
    ui->field_gpa_u->setEnabled(true);

    id_to_update = s.get_id();

    ui->btn_update->setEnabled(true);
    ui->btn_search_u->setEnabled(false);
    ui->field_search_u->setEnabled(false);
}


void MainWindow::on_btn_new_u_clicked()
{
    ui->field_name_u->clear();
    ui->field_age_u->clear();
    ui->field_dept_u->clear();
    ui->field_gpa_u->clear();
    ui->field_search_u->clear();

    ui->field_name_u->setEnabled(false);
    ui->field_age_u->setEnabled(false);
    ui->field_dept_u->setEnabled(false);
    ui->field_gpa_u->setEnabled(false);

    ui->btn_update->setEnabled(false);
    ui->btn_search_u->setEnabled(true);
    ui->field_search_u->setEnabled(true);

    id_to_update = 0;
}


void MainWindow::on_btn_update_clicked()
{
    QString name = ui->field_name_u->text();
    QString age = ui->field_age_u->text();
    QString department = ui->field_dept_u->text();
    QString gpa = ui->field_gpa_u->text();
    if (name.isEmpty()) {
        QMessageBox::warning(
            this,
            "Missing Input",
            "Please enter student name."
            );
        return;
    }
    if (age.isEmpty()) {
        QMessageBox::warning(
            this,
            "Missing Input",
            "Please enter student age."
            );
        return;
    }
    if (department.isEmpty()) {
        QMessageBox::warning(
            this,
            "Missing Input",
            "Please enter student department."
            );
        return;
    }
    if (gpa.isEmpty()) {
        QMessageBox::warning(
            this,
            "Missing Input",
            "Please enter student gpa."
            );
        return;
    }

    bool age_validation;
    int age_int = age.toInt(&age_validation);
    if (!age_validation) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid Age.");
        return;
    }

    bool gpa_validation;
    float gpa_float = gpa.toFloat(&gpa_validation);
    if (!gpa_validation) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid GPA.");
        return;
    }

    QMessageBox::StandardButton answer;
    answer = QMessageBox::question(
        this,
        "Confirm Action",
        "Are you sure you want to update "+name+" in database?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (answer == QMessageBox::Yes) {
        ss->full_update_student(id_to_update,name.toStdString(),age_int,department.toStdString(),gpa_float);
        QMessageBox::information(this, "Student Updated", "Student "+name+" has been updated in database successfully");
        on_btn_new_u_clicked();
    }
    else {

    }
}
