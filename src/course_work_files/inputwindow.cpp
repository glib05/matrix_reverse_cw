#include "inputwindow.h"
#include "ui_inputwindow.h"
#include <QStatusBar>
#include <QFileDialog>

InputWindow::InputWindow(QWidget *parent, QString w_method, int w_size) :
    QDialog(parent), ui(new Ui::InputWindow), method(w_method), size(w_size)
{
    ui->setupUi(this);

    this ->setFixedSize(180 + size * 45, 180 + size * 35);

    ui->label->move(20 + size * 20, 0);

    ui->matrixWidget->setGeometry(68, 40, 35 + size * 45, 35 + size * 35);
    ui->matrixWidget->setColumnCount(size);
    ui->matrixWidget->setRowCount(size);
    ui->matrixWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->matrixWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->clearButton->setFixedSize(80, 30);
    ui->clearButton->move(26 + size * 7, 80 + size * 35);

    ui->submitButton->setFixedSize(80, 30);
    ui->submitButton->move(82 + size * 35, 80 + size * 35);

    ui->statusBar->move(0, 120 + size * 35);
    ui->statusBar->setFixedSize(180 + size * 45, 30);
    ui->statusBar->setStyleSheet("color: red;");

    connect(ui->submitButton, &QPushButton::clicked, this, &InputWindow::handleInput);
    connect(ui->clearButton, &QPushButton::clicked, this, &InputWindow::clearInput);
}

InputWindow::~InputWindow()
{
    delete ui;
}




void InputWindow::handleInput()
{
    matrix_.clear();
    matrix_.resize(size);

    matrix* new_matrix;

    try{
        for (int row = 0; row < size; row++)
        {
            matrix_[row].resize(size);

            for (int column = 0; column < size; column++)
            {
                QTableWidgetItem* item = ui->matrixWidget->item(row, column);
                bool isValueNumber = false;
                double value = item ? item->text().toDouble(&isValueNumber) : 0.0;

                if (isValueNumber)
                {
                    string valueString = item->text().toStdString();
                    size_t decimalPos = valueString.find('.');
                    int precision = valueString.length() - decimalPos - 1;

                    if (abs(value) > MAX_VALUE)
                    {
                        throw QString("Введено занадто велике число");
                        return;
                    }
                    else if (precision > MAX_PRECISION)
                    {
                        throw QString("Введено забагато знаків після коми");
                        return;
                    }

                    matrix_[row][column] = value;
                }
                else
                {
                    throw QString("Будь-ласка введіть ЧИСЛА");
                    return;
                }
            }
        }

        new_matrix = new matrix(size, size, matrix_);
        double determinant;
        if (method == "okaimlennya"){
            determinant = gause_det(*new_matrix);
            if (isnan(determinant)) // close to zero
                throw QString("Методом окаймлення\n не можна обернути цю матрицю");
        }
        if (method == "schulz")
            determinant = det(*new_matrix);

        if (fabs(determinant) < 1e-7) // close to zero
            throw QString("Оберненої матриці не існує");
    }
    catch(const QString& err){
        ui->statusBar->setText(err);
        return;
    }

    hide();
    MatrixInversion window(this, method, *new_matrix);
    window.setWindowTitle("Обернення матриць");
    window.setModal(true);
    window.exec();
    delete new_matrix;
}

void InputWindow::clearInput()
{
    ui->matrixWidget->clear();
    matrix_.clear();
}

void InputWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Text Files (*.txt)");
    //QString fileName = "Для курсової.txt";
    QFile file(fileName);
    int size;
    matrix *new_matrix;


    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        stream>>size;
        new_matrix = new matrix(size, size);
        double value;

        for (int i = 0; i<size; i++)
            for (int j = 0; j<size; j++){
                stream>>(*new_matrix)[i][j];

            }
    }

    hide();
    MatrixInversion window(this, method, *new_matrix);
    window.setWindowTitle("Обернення матриць");
    window.setModal(true);
    window.exec();
    delete new_matrix;
    file.close();
}

