#ifndef ELENCO_H
#define ELENCO_H

#include <QDialog>
#include <QDate>
#include <QFile>
#include <QTextStream>

namespace Ui {
class Elenco;
}

class Elenco : public QDialog
{
    Q_OBJECT

public:
    explicit Elenco(QWidget *parent = nullptr);
    ~Elenco();

    void setGrafico(QFile *csv);    //Funzione che predispone le info utili alla creazione dell'elenco
    void setElenco();               //Funzione che realizza l'elenco

private:
    Ui::Elenco *ui;

    struct utente{                  //Struttura in cui verranno memorizzate le informazioni di ogni utente
        QString nome;
        QString cognome;
        QString telmail;
        QDate   dataNascita;
        QChar   genere;
        QString password;
    };

    QList<utente> listaUtenti;      //Lista di tutti gli utenti


};

#endif // ELENCO_H
