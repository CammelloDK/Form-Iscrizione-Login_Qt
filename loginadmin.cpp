#include "loginadmin.h"
#include "ui_loginadmin.h"

Loginadmin::Loginadmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loginadmin)
{
    ui->setupUi(this);
    this->setFixedSize(500,200);

}

Loginadmin::~Loginadmin()
{
    delete ui;
}

void Loginadmin::setAdmin(QString nome, QString cognome){
     ui->lbladmin->setText("ADMIN: "+nome+" "+cognome);
}

void Loginadmin::brgFile(QFile *csv){
    usrdb=csv;
}

void Loginadmin::on_lblgotoelenco_clicked()
{
    Elenco ep(this);
    ep.setModal(true);
    ep.setGrafico(usrdb);
    ep.exec();
}

void Loginadmin::on_btngotografici_clicked()
{
    Grafici gp(this);
    gp.setModal(true);
    gp.setGrafico(usrdb);
    gp.exec();
}
