#ifndef MATRIXINVERSION_H
#define MATRIXINVERSION_H

#include <QDialog>
#include "matrix.h"

namespace Ui {
class MatrixInversion;
}

class MatrixInversion : public QDialog
{
    Q_OBJECT

public:
    explicit MatrixInversion(QWidget *parent = nullptr, QString w_method = "", matrix w_matrix = matrix(0,0));
    ~MatrixInversion();

private slots:
    void on_pushButton_done_clicked();

    void on_pushButton_inf_clicked();

    void on_pushButton_write_1_clicked();

private:
    Ui::MatrixInversion *ui;
    QString method;
    matrix _matrix;
    int _comp;
    matrix _reversed;
};

#endif // MATRIXINVERSION_H
