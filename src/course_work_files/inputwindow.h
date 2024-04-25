#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QMessageBox>
#include "matrixinversion.h"
#include "ui_inputwindow.h"
#include <QStatusBar>

#define MAX_PRECISION 10
#define MAX_VALUE 1e5

#define MIN_LINE_EDIT_WIDTH 50 // Minimum width for the QLineEdit widgets
#define MIN_LINE_EDIT_HEIGHT 30

namespace Ui {
class InputWindow;
}

class InputWindow : public QDialog
{
    Q_OBJECT

public:
    InputWindow(QWidget*, QString, int);
    ~InputWindow();

private slots:
    void handleInput(); // submitButton clicked
    void clearInput(); // clearButton clicked

    void on_pushButton_clicked();

private:
    Ui::InputWindow *ui;
    QVector<QVector<double>> matrix_;
    QString method;
    int size;

};

#endif // InputWindow_H
