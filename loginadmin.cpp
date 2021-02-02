#include "loginadmin.h"
#include "ui_loginadmin.h"

Loginadmin::Loginadmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loginadmin)
{
    ui->setupUi(this);
    this->setFixedSize(500,200);        //Rendo immodificabili dimensioni finestra

}

Loginadmin::~Loginadmin()
{
    delete ui;
}

void Loginadmin::setAdmin(QString nome, QString cognome){
     ui->lbladmin->setText("ADMIN: "+nome+" "+cognome);     //Metodo setter per il contenuto della label Admin
}

void Loginadmin::brgFile(QFile *csv){
    usrdb=csv;      //Memorizzo il riferimento al file. Successivamente lo passerò ai metodi che genereranno i grafici
}

void Loginadmin::on_lblgotoelenco_clicked()
{
    Elenco ep(this);    //Creo oggetto di tipo Elenco per poter gestire l'omonima pagina
    ep.setModal(true);  //Rendo la finestra elenco modale, in modo da poter interagire solo con quella una volta visualizzata
    ep.setGrafico(usrdb); //Richiamo il metodo setGrafico() passando il riferimento al file
    ep.exec();          //Visualizzo la nouva pagina
}

void Loginadmin::on_btngotografici_clicked()
{
    Grafici gp(this);   //Creo oggetto di tipo Grafici per poter gestire l'omonima pagina
    gp.setModal(true);  //Rendo la finestra grafico modale, in modo da poter interagire solo con quella una volta visualizzata
    gp.setGrafico(usrdb);   //Richiamo il metodo setGrafico() passando il riferimento al file
    gp.exec();          //Visualizzo la nouva pagina
}
