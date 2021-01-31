#ifndef LOGINADMIN_H
#define LOGINADMIN_H

#include <QDialog>
#include "elenco.h"
#include "grafici.h"

namespace Ui {
class Loginadmin;
}

class Loginadmin : public QDialog
{
    Q_OBJECT

public:
    explicit Loginadmin(QWidget *parent = nullptr);
    ~Loginadmin();

    void setAdmin(QString nome, QString cognome);   //Funzione per personalizzazione pagina di benvenuto
    void brgFile(QFile *csv);                       //Funzione "ponte" utile per portare il riferimento del file alle classi che generanno i grafici

private slots:
    void on_lblgotoelenco_clicked();

    void on_btngotografici_clicked();

private:
    Ui::Loginadmin *ui;

    QFile *usrdb;                                   //Puntatore al file usato in brgFile()

};

#endif // LOGINADMIN_H
