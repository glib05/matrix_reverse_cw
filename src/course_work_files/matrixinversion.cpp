#include "matrixinversion.h"
#include "ui_matrixinversion.h"
#include <QTableWidget>
#include "matrix.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

MatrixInversion::MatrixInversion(QWidget *parent, QString w_method, matrix w_matrix) :
    QDialog(parent), method(w_method), _matrix(w_matrix), _reversed(w_matrix),
    ui(new Ui::MatrixInversion)
{
    ui->setupUi(this);

    this ->setFixedSize(160+_matrix.get_m()*120, 155+_matrix.get_m()*35);

    ui->source_matrix_widget->setGeometry(10, 20, 60+_matrix.get_m()*60, 40+_matrix.get_m()*35);
    ui->source_matrix_widget->setColumnCount(_matrix.get_m());
    ui->source_matrix_widget->setRowCount(_matrix.get_m());
    for (int i = 0; i < _matrix.get_m(); i++) {
        for (int j = 0; j < _matrix.get_m(); j++) {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(_matrix[i][j]));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Вимкнення флага редагованості
            ui->source_matrix_widget->setItem(i, j, item);
            //delete item;
        }
    }
    ui->source_matrix_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->source_matrix_widget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    _comp = 0;
    _reversed = _matrix.reverse(w_method, _comp);

    ui->reversed_matrix_widget->setGeometry(90+_matrix.get_m()*60, 20, 60+_matrix.get_m()*60, 40+_matrix.get_m()*35);
    ui->reversed_matrix_widget->setColumnCount(_matrix.get_m());
    ui->reversed_matrix_widget->setRowCount(_matrix.get_m());
    for (int i = 0; i < _matrix.get_m(); i++) {
        for (int j = 0; j < _matrix.get_m(); j++) {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(_reversed[i][j]));
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->reversed_matrix_widget->setItem(i, j, item);
        }
    }
    ui->reversed_matrix_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->reversed_matrix_widget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->label_source->move(20, 0);
    ui->label_reversed->move(90+_matrix.get_m()*60, 0);

    ui->pushButton_write_1->move(10, 65+_matrix.get_m()*35);
    ui->pushButton_write_1->setFixedWidth(60+_matrix.get_m()*120+80);

    ui->pushButton_inf->move(10, 110+_matrix.get_m()*35);
    ui->pushButton_inf->setFixedWidth(210+(_matrix.get_m()-1)*45);

    ui->pushButton_done->move(145+_matrix.get_m()*80, 110+_matrix.get_m()*35);
    ui->pushButton_done->setFixedWidth(5+_matrix.get_m()*40);

    ui->statusBar->move(10, 65+_matrix.get_m()*35);
    ui->statusBar->setFixedWidth(60+_matrix.get_m()*120+80);
    ui->statusBar->setStyleSheet("color: green;");
}

MatrixInversion::~MatrixInversion()
{
    delete ui;
}

void MatrixInversion::on_pushButton_done_clicked()
{
    ui->~MatrixInversion();
    MatrixInversion::close();
}


void MatrixInversion::on_pushButton_inf_clicked()
{
    if (method == "schulz")
        QMessageBox::information(this, "Інформація про метод Шульца", "Метод Шульца, також відомий як ітеративний метод "
                                                                      "обернення матриці.\n"
                                                                      "Для початку береться матриця, яка, ймовірно, є "
                                                                      "оберненою до початкової (у нашому випадку обирається "
                                                                      "одинична матриця), і певними операціями"
                                                                      "\"підганяється\" під справжню обернену матрицю,"
                                                                      "поки точність не буде задовільною.\n"
                                                                      "Оскільки це ітеративний метод, визначити "
                                                                      "його теоретичну складність неможливо.\n\n"
                                                                      "Практична складність (кількість ітерацій): "+QString(to_string(_comp).c_str()));
    else if (method == "okaimlennya")
        QMessageBox::information(this, "Інформація про метод окаймлення", "Метод окаймлення - метод обернення матриці, "
                                                                          "який отримує обернену матрицю із попередньої "
                                                                          "матриці меншої розмірності, шляхом \"окаймлення\" "
                                                                          "її стовпцем та рядком.\n "
                                                                          "Загалом, метод повторюється рекурсивно, поки "
                                                                          "розмірність матриці не дорівнюватиме 1, адже для "
                                                                          "такої матриці можна легко обчислити обернену, просто "
                                                                          "обернувши її перший і єдиний елемент.\n"
                                                                          "Теоретична складність О(n^4)\n"                                                                          ""
                                                                          "Практична складність: "+QString(to_string(_comp).c_str()));
}


void MatrixInversion::on_pushButton_write_1_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "Text Files (*.txt)"); // Діалогове вікно вибору файлу для збереження
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << "Вхідна матриця\n" << _matrix;
        stream << "         Визначник матриці: " + QString(std::to_string(det(_matrix)).c_str());

        stream << "Обернена матриця\n" << _reversed;
        stream << "\nЧасова складінсть методу " + method+ ": " + QString(std::to_string(_comp).c_str());

        file.close();
        //QMessageBox::information(this, "Успіх", "Матрицю успішно записано у файл.");
        ui->statusBar->setText("Інформацію успішно записано у файл");

        ui->pushButton_write_1->hide();
    }
}


