#ifndef READFILE_H
#define READFILE_H

#include <QWidget>

namespace Ui {
class readfile;
}

class readfile : public QWidget
{
    Q_OBJECT

public:
    explicit readfile(QWidget *parent = nullptr);
    ~readfile();

private slots:
    void on_pushButton_clicked();

private:
    Ui::readfile *ui;
};

#endif // READFILE_H
