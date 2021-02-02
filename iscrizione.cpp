#include "iscrizione.h"
#include "ui_iscrizione.h"
#include <QTimer>

Iscrizione::Iscrizione(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Iscrizione)
{
    ui->setupUi(this);
    this->setFixedSize(370,220);        //Rendo immodificabili dimensioni finestra

}

Iscrizione::~Iscrizione()
{
    delete ui;
}

void Iscrizione::setNome(QString n){
    ui->lblnome->setText(n);        //Metodo setter per il contenuto della label Nome
}

void Iscrizione::setCognome(QString c){
    ui->lblcognome->setText(c);     //Metodo setter per il contenuto della label Cognome
}
