#include "iscrizione.h"
#include "ui_iscrizione.h"
#include <QTimer>

Iscrizione::Iscrizione(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Iscrizione)
{
    ui->setupUi(this);
    this->setFixedSize(370,220);

}

Iscrizione::~Iscrizione()
{
    delete ui;
}

void Iscrizione::setNome(QString n){
    ui->lblnome->setText(n);
}

void Iscrizione::setCognome(QString c){
    ui->lblcognome->setText(c);
}
