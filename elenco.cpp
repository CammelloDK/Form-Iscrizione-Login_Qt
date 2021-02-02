#include "elenco.h"
#include "ui_elenco.h"

Elenco::Elenco(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Elenco)
{
    ui->setupUi(this);
    this->setFixedSize(639,300);    //Rendo immodificabili le dimensioni della finestra
}

Elenco::~Elenco()
{
    delete ui;
}

void Elenco::setGrafico(QFile *csv){

    utente u;                       //Variabile di memorizzazione info utenti
    csv->open(QIODevice::ReadOnly); //Apro file in sola lettura
    QTextStream in(csv);            //Creo stream di input per leggere in file

    while(!in.atEnd()){             //Fintanto che non ho letto tutto il file
        QStringList stringaUtente = in.readLine().split(',');   //Popolo lista con tutte le info lette dal file, separatore ','
        u.nome=stringaUtente[0];    //Nome è primo elemento della lista
        u.cognome=stringaUtente[1]; //Cognome secondo e così via
        u.telmail=stringaUtente[2];
        u.dataNascita=QDate::fromString(stringaUtente[3],"ddMMyyyy"); //Per memorizzare la data come tipo QDate da una stringa uso fromString(<stringa>,<formato>)
        u.genere=static_cast<QChar>(stringaUtente[4][0]); //Effettuo il casting da stringa a char
        u.password=stringaUtente[5];

        listaUtenti.append(u);  //Aggiungo in coda alla lista utenti l'utente appena letto da file

    }

    in.flush();     //Svuoto lo stream di input
    csv->close();   //Chiudo il file

    setElenco();    //Genero l'elenco


}

void Elenco::setElenco(){
    ui->tbElenco=new QTableWidget(listaUtenti.count(),6,this);  //Costruttore richiede (<Numero righe>,<Numero colonne>,<Widget padre>)
    ui->tbElenco->setFixedSize(639,300);    //Dimensione fissa dell'elenco
    ui->tbElenco->setEditTriggers(QAbstractItemView::NoEditTriggers);   //Rimuovo possibilità di modificare i valori all'interno dell'elenco

    QStringList titoli;     //Lista di stringhe che andranno a comporre gli header di ogni colonna
    titoli.append("Nome");
    titoli.append("Cognome");
    titoli.append("Tel/Mail");
    titoli.append("Data di nascita");
    titoli.append("Genere");
    titoli.append("Password");

    QTableWidgetItem *cella;    //Puntatore a cella dell'elenco

    ui->tbElenco->setHorizontalHeaderLabels(titoli);    //Imposto i titoli

    for(int i=0;i<listaUtenti.count();++i){ //Per ogni utente
        for(int j=0;j<6;++j){   //Per ogni informazione memorizzata
            switch(j){  //Popolo ogni cella di una riga
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
            ui->tbElenco->setItem(i,j,cella); //Aggiungo la cella precedentemente popolata all'elenco
        }
    }
}
