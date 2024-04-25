#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "matrixinversion.h"
#include "inputwindow.h"
#include "matrix.h"

//#include <QMessageBox>
//#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButtonCreate_clicked()
{
    QString method;
    if(ui->rbFirstMethod->isChecked())
        method = "okaimlennya";
    else
        method = "schulz";

    if(ui->rbGenerateInput->isChecked())
    {
        int size = ui->spinBox->value();
        matrix m(size, size);
        while (!det(m.randomise()));
        MatrixInversion window(this, method, m);
        window.setWindowTitle("Обернення матриць");
        window.setModal(true);
        window.exec();
    }
    else
    {
        InputWindow window(this, method, ui->spinBox->value());
        window.setWindowTitle("Заповнення матриць");
        window.setModal(true);
        window.exec();
    }

}

