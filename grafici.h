#ifndef GRAFICI_H
#define GRAFICI_H

#include <QDialog>
#include <QDate>
#include <QFile>
#include <QtCharts>
#include <QPieSeries>
#include <QPieSlice>

namespace Ui {
class Grafici;
}

class Grafici : public QDialog
{
    Q_OBJECT

public:
    explicit Grafici(QWidget *parent = nullptr);
    ~Grafici();

    void setGrafico(QFile *csv);    //Metodo che predispone le info utili alla creazione dei grafici
    void setGrGenere();             //Metodo che realizza il grafico dei generi
    void setGrEta();                //Metodo che realizza il grafico delle età

private:
    Ui::Grafici *ui;

    struct utente{                  //Struttura in cui verranno memorizzate le informazioni di ogni utente
        QString nome;
        QString cognome;
        QString telmail;
        QDate   dataNascita;
        QChar   genere;
        QString password;
    };

    QList<utente> listaUtenti;      //Lista di tutti gli utenti
    QFile *usrdb;                   //Puntatore al file

    //Variabili utili alla memorizzazione delle informazioni da visualizzare attraverso i grafici
    int m=0;
    int f=0;
    int sotto26=0;
    int sopra54=0;
    int tra27_35=0;
    int tra36_44=0;
    int tra45_53=0;
};

#endif // GRAFICI_H
