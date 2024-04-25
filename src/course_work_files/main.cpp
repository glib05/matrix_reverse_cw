#include "mainwindow.h"
#include <QApplication>
#include<QLabel>
#include <QWidget>
#include <QTableWidget>
#include <QApplication>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Створення");
    w.show();
    return a.exec();
}
