#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private slots:
    void on_btn_clicked();

    void on_btn_top_clicked();

    void on_btn_csv_clicked();

    void on_btn_all_students_clicked();

private:
    Ui::MainWindow *ui;
    MyDatabase db;
    StudentService* ss;
};
#endif // MAINWINDOW_H
