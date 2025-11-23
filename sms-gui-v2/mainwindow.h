#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

#include "database_models/MyDatabase.h"
#include "services/StudentService.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void update_dashboard();
    void update_view_students();
    void search_student();
    void load_students_table(QTableWidget *table, vector<Student> students);

private slots:
    void on_listWidget_currentRowChanged(int currentRow);

    void on_stackedWidget_currentChanged(int arg1);

    void on_btn_search_s_clicked();

    void on_btn_add_clicked();

    void on_btn_search_d_clicked();

    void on_btn_new_s_clicked();

    void on_btn_delete_clicked();

    void on_btn_search_u_clicked();

    void on_btn_new_u_clicked();

    void on_btn_update_clicked();

private:
    Ui::MainWindow *ui;
    MyDatabase db;
    StudentService* ss;
    int id_to_delete;
    int id_to_update;
};
#endif // MAINWINDOW_H
