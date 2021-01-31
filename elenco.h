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

    void setGrafico(QFile *csv);
    void setElenco();

private:
    Ui::Elenco *ui;

    struct utente{
        QString nome;
        QString cognome;
        QString telmail;
        QDate   dataNascita;
        QChar   genere;
        QString password;
    };

    QList<utente> listaUtenti;


};

#endif // ELENCO_H
