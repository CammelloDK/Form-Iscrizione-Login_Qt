#include "grafici.h"
#include "ui_grafici.h"

Grafici::Grafici(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Grafici)
{
    ui->setupUi(this);
    this->setFixedSize(500,600);
}

Grafici::~Grafici()
{
    delete ui;
}

void Grafici::setGrafico(QFile *csv){

    usrdb=csv;

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

        if(u.genere=='M')
            m++;
        else
            f++;

        QDate data = QDate::currentDate();
        if (u.dataNascita.addYears(54)<=data)
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

    in.flush();
    csv->close();

    setGrGenere();
    setGrEta();


}

void Grafici::setGrGenere(){
    QPieSeries *generi=new QPieSeries();

    generi->append("Maschi",m);
    generi->append("Femmine",f);

    generi->slices().at(0)->setLabel("Maschi: "+QString::number(m));
    generi->slices().at(1)->setLabel("Femmine: "+QString::number(f));

    QChart *graficoGeneri=new QChart();
    graficoGeneri->addSeries(generi);
    graficoGeneri->setTitle("% uomini/donne iscritte al portale");

    ui->piMF->setFixedSize(480,258);
    QChartView *vistaGrafico=new QChartView(graficoGeneri);
    vistaGrafico->setParent(ui->piMF);

    vistaGrafico->setFixedSize(ui->piMF->width(),ui->piMF->height());
}

void Grafici::setGrEta(){
    QPieSeries *eta=new QPieSeries();

    eta->append("18-26",sotto26);
    eta->append("27-35",tra27_35);
    eta->append("36-44",tra36_44);
    eta->append("45-53",tra45_53);
    eta->append("54+",sopra54);

    eta->slices().at(0)->setLabel("18-26: "+QString::number(sotto26));
    eta->slices().at(1)->setLabel("27-35: "+QString::number(tra27_35));
    eta->slices().at(2)->setLabel("36-44: "+QString::number(tra36_44));
    eta->slices().at(3)->setLabel("45-53: "+QString::number(tra45_53));
    eta->slices().at(4)->setLabel("54+: "+QString::number(sopra54));

    QChart *graficoEta=new QChart();
    graficoEta->addSeries(eta);
    graficoEta->setTitle("% età iscritti al portale");

    ui->piNumero->setFixedSize(480,259);
    QChartView *vistaEta=new QChartView(graficoEta);
    vistaEta->setParent(ui->piNumero);

    vistaEta->setFixedSize(ui->piNumero->width(),ui->piNumero->height());
}
