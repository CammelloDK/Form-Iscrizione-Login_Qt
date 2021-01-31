#include "loginusr.h"
#include "ui_loginusr.h"

Loginusr::Loginusr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loginusr)
{
    ui->setupUi(this);
    this->setFixedSize(370,220);
}

Loginusr::~Loginusr()
{
    delete ui;
}

void Loginusr::setNome(QString n){
    ui->lblnome->setText(n);
}

void Loginusr::setCognome(QString c){
    ui->lblcognome->setText(c);
}
