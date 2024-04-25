#include "readfile.h"
#include "ui_readfile.h"

readfile::readfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::readfile)
{
    ui->setupUi(this);
}

readfile::~readfile()
{
    delete ui;
}

void readfile::on_pushButton_clicked()
{

}

