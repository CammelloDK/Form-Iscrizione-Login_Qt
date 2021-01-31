#include "recupero.h"
#include "ui_recupero.h"

Recupero::Recupero(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Recupero)
{
    ui->setupUi(this);
    this->setFixedSize(370,220);
}

Recupero::~Recupero()
{
    delete ui;
}
