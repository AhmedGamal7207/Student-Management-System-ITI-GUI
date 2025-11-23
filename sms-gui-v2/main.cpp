#include "mainwindow.h"

#include <QApplication>
#include <QFontDatabase>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/Lexend/static/Lexend-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Lexend/static/Lexend-Medium.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Lexend/static/Lexend-Bold.ttf");

    // Set default application font
    QFont font("Lexend");
    font.setPointSize(11);   // Adjust as needed
    QApplication::setFont(font);

    MainWindow w;
    w.show();
    return a.exec();
}
