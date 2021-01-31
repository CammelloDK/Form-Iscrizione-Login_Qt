#ifndef LOGINADMIN_H
#define LOGINADMIN_H

#include <QDialog>
#include <QtCharts>
#include <QPieSeries>
#include <QPieSlice>
#include "elenco.h"

namespace Ui {
class Loginadmin;
}

class Loginadmin : public QDialog
{
    Q_OBJECT

public:
    explicit Loginadmin(QWidget *parent = nullptr);
    ~Loginadmin();

    void setAdmin(QString nome, QString cognome);
    void setGrafico(QFile *csv);
    void setGrGenere();
    void setGrEta();

private slots:
    void on_lblgotoelenco_clicked();

private:
    Ui::Loginadmin *ui;

    struct utente{
        QString nome;
        QString cognome;
        QString telmail;
        QDate   dataNascita;
        QChar   genere;
        QString password;
    };

    QList<utente> listaUtenti;
    int m=0;
    int f=0;
    int sotto26=0;
    int sopra54=0;
    int tra27_35=0;
    int tra36_44=0;
    int tra45_53=0;
    QFile *usrdb;

};

#endif // LOGINADMIN_H
