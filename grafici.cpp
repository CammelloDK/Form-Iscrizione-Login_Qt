#include "grafici.h"
#include "ui_grafici.h"

Grafici::Grafici(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Grafici)
{
    ui->setupUi(this);
    this->setFixedSize(500,600);    //Rendo immodificabili dimensioni finestra
}

Grafici::~Grafici()
{
    delete ui;
}

void Grafici::setGrafico(QFile *csv){

    usrdb=csv;      //Riferimento al file dal leggere

    utente u;                       //Variabile di memorizzazione info utenti
    csv->open(QIODevice::ReadOnly); //Apro il file
    QTextStream in(csv);            //Creo stream di input

    while(!in.atEnd()){             //Fintanto che non ho letto tutto il file
        QStringList stringaUtente = in.readLine().split(',');   //Popolo lista con tutte le info lette dal file, separatore ','
        u.nome=stringaUtente[0];        //Nome è primo elemento della lista
        u.cognome=stringaUtente[1];     //Cognome secondo e così via
        u.telmail=stringaUtente[2];
        u.dataNascita=QDate::fromString(stringaUtente[3],"ddMMyyyy");   //Per memorizzare la data come tipo QDate da una stringa uso fromString(<stringa>,<formato>)
        u.genere=static_cast<QChar>(stringaUtente[4][0]);   //Effettuo il casting da stringa a char
        u.password=stringaUtente[5];

        if(u.genere=='M')   //A seconda del genere letto incremendo l'opportuna variabile
            m++;
        else
            f++;

        QDate data = QDate::currentDate();      //Memorizzo la data odierna
        if (u.dataNascita.addYears(54)<=data)   //Sommo 54 anni alla data letta dal file, se maggiore dell'odierna l'utente ha meno di 54 anni e così via
            sopra54++;
        else
            if(u.dataNascita.addYears(45)<=data)
                tra45_53++;
            else
                if(u.dataNascita.addYears(36)<=data)
                    tra36_44++;
                else
                    if(u.dataNascita.addYears(27)<=data)
                        tra27_35++;
                    else
                        sotto26++;

    }

    in.flush();     //Svuoto stream di input
    csv->close();   //Chiudo il file

    setGrGenere();  //Genero grafico genere
    setGrEta();     //Genero grafico età


}

void Grafici::setGrGenere(){
    QPieSeries *generi=new QPieSeries();    //Serie di dati che andrò ad inserire nel grafico

    generi->append("Maschi",m);     //Primo elemento della serie
    generi->append("Femmine",f);    //Secondo

    generi->slices().at(0)->setLabel("Maschi: "+QString::number(m));    //Personalizzo le label delle fette del grafico
    generi->slices().at(1)->setLabel("Femmine: "+QString::number(f));

    QChart *graficoGeneri=new QChart();     //Genero il grafico
    graficoGeneri->addSeries(generi);       //Aggiungendo la serie
    graficoGeneri->setTitle("% uomini/donne iscritte al portale");  //Personalizzo il titolo

    ui->piMF->setFixedSize(480,258);    //Stabilisco dimensioni del frame che conterrà il grafico
    QChartView *vistaGrafico=new QChartView(graficoGeneri);     //Gestisco la visualizzazione del grafico
    vistaGrafico->setParent(ui->piMF);      //Imposto il frame genitore

    vistaGrafico->setFixedSize(ui->piMF->width(),ui->piMF->height());   //Adatto la dimensione del grafico a quella del frame in cui è contenuto
}

void Grafici::setGrEta(){
    QPieSeries *eta=new QPieSeries();   //Serie di dati che andrò ad inserire nel grafico

    eta->append("18-26",sotto26);       //Primo elemento della serie
    eta->append("27-35",tra27_35);      //Secondo
    eta->append("36-44",tra36_44);      //E così via
    eta->append("45-53",tra45_53);
    eta->append("54+",sopra54);

    eta->slices().at(0)->setLabel("18-26: "+QString::number(sotto26));      //Personalizzo le label delle fette del grafico
    eta->slices().at(1)->setLabel("27-35: "+QString::number(tra27_35));
    eta->slices().at(2)->setLabel("36-44: "+QString::number(tra36_44));
    eta->slices().at(3)->setLabel("45-53: "+QString::number(tra45_53));
    eta->slices().at(4)->setLabel("54+: "+QString::number(sopra54));

    QChart *graficoEta=new QChart();    //Genero il grafico
    graficoEta->addSeries(eta);         //Aggiungendo le serie
    graficoEta->setTitle("% età iscritti al portale");  //Personalizzo il titolo

    ui->piNumero->setFixedSize(480,259);    //Stabilisco dimensioni del frame che conterrà il grafico
    QChartView *vistaEta=new QChartView(graficoEta);    //Gestisco la visualizzazione del grafico
    vistaEta->setParent(ui->piNumero);      //Imposto il frame genitore

    vistaEta->setFixedSize(ui->piNumero->width(),ui->piNumero->height());   //Adatto la dimensione del grafico a quella del frame in cui è contenuto
}
