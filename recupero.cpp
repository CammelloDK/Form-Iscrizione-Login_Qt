#include "recupero.h"
#include "ui_recupero.h"

Recupero::Recupero(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Recupero)
{
    ui->setupUi(this);
    this->setFixedSize(370,220);    //Rendo immodificabili le dimensioni della finestra
}

Recupero::~Recupero()
{
    delete ui;
}
