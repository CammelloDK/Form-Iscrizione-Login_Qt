#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDate>
#include "iscrizione.h"
#include "loginusr.h"
#include "recupero.h"
#include "loginadmin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btniscriviti_clicked();

    void on_btngotoaccedi_clicked();

    void on_btngotoiscriviti_clicked();

    void on_btnaccedi_clicked();

    void on_btngotorecupero_clicked();

    void on_btnrecupero_clicked();

private:
    Ui::MainWindow *ui;
    QFile csv;                      //File in cui scriveremo gli utenti

    struct utente{                  //Struttura di memorizzazione degli utenti
        QString nome;
        QString cognome;
        QString telmail;
        QDate   dataNascita;
        QChar   genere;
        QString password;
    };

    utente admin;                   //Creiamo una variabile admin di tipo utente
    char checkElements();           //Metodo per verificare la correttezza dei dati inseriti tramite form
    char checkTelMailPswd();        //Metodo per verificare la correttezza dei dati telefono/mail e password inseriti tramite form
    void checkUsrDBFile();          //Metodo per verificare la presenza del percorso del file di memorizzazione degli utenti, in caso negativo crea
    void insertAdmin();             //Metodo per caricare in memoria le informazioni relative all'utente admin
    bool checkIscritto();           //Metodo per verificare l'iscrizione di un utente
    void insertUtente();            //Metodo per scrivere su file un nuovo utente
    void clearForm();               //Metodo per svuotare tutti i campi della form
    void login();                   //Metodo di login
    void swapPagine(char pagina);                                   //Metodo per visualizzare nuove pagine
    void swapPagine(char pagina, QString nome, QString cognome);    //Metodo per visualizzare pagine personalizzate
};
#endif // MAINWINDOW_H
