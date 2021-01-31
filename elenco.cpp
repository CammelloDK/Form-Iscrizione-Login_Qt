#include "elenco.h"
#include "ui_elenco.h"

Elenco::Elenco(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Elenco)
{
    ui->setupUi(this);
    this->setFixedSize(639,300);
}

Elenco::~Elenco()
{
    delete ui;
}

void Elenco::setGrafico(QFile *csv){

    utente u;
    csv->open(QIODevice::ReadOnly);
    QTextStream in(csv);

    while(!in.atEnd()){
        QStringList stringaUtente = in.readLine().split(',');
        u.nome=stringaUtente[0];
        u.cognome=stringaUtente[1];
        u.telmail=stringaUtente[2];
        u.dataNascita=QDate::fromString(stringaUtente[3],"ddMMyyyy");
        u.genere=static_cast<QChar>(stringaUtente[4][0]);
        u.password=stringaUtente[5];

        listaUtenti.append(u);

    }

    in.flush();
    csv->close();

    setElenco();


}

void Elenco::setElenco(){
    ui->tbElenco=new QTableWidget(listaUtenti.count(),6,this);
    ui->tbElenco->setFixedSize(639,300);
    ui->tbElenco->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList titoli;
    titoli.append("Nome");
    titoli.append("Cognome");
    titoli.append("Tel/Mail");
    titoli.append("Data di nascita");
    titoli.append("Genere");
    titoli.append("Password");

    QTableWidgetItem *cella;

    ui->tbElenco->setHorizontalHeaderLabels(titoli);

    for(int i=0;i<listaUtenti.count();++i){
        for(int j=0;j<6;++j){
            switch(j){
            case 0: cella=new QTableWidgetItem(listaUtenti[i].nome);
                break;
            case 1: cella=new QTableWidgetItem(listaUtenti[i].cognome);
                break;
            case 2: cella=new QTableWidgetItem(listaUtenti[i].telmail);
                break;
            case 3: cella=new QTableWidgetItem(listaUtenti[i].dataNascita.toString("dd/MM/yyyy"));
                break;
            case 4: cella=new QTableWidgetItem(listaUtenti[i].genere);
                break;
            case 5: cella=new QTableWidgetItem(listaUtenti[i].password);
                break;
            }
            ui->tbElenco->setItem(i,j,cella);
        }
    }
}
