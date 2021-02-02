#include "loginusr.h"
#include "ui_loginusr.h"

Loginusr::Loginusr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loginusr)
{
    ui->setupUi(this);
    this->setFixedSize(370,220);    //Rendo immodificabili le dimensioni della finestra
}

Loginusr::~Loginusr()
{
    delete ui;
}

void Loginusr::setNome(QString n){
    ui->lblnome->setText(n);        //Metodo setter per il contenuto della label Nome
}

void Loginusr::setCognome(QString c){
    ui->lblcognome->setText(c);     //Metodo setter per il contenuto della label Cognome
}
