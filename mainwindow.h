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
    QFile csv;

    struct utente{
        QString nome;
        QString cognome;
        QString telmail;
        QDate   dataNascita;
        QChar   genere;
        QString password;
    };

    utente admin;
    char checkElements();
    char checkTelMailPswd();
    void checkUsrDBFile();
    void insertAdmin();
    bool checkIscritto();
    void insertUtente();
    void clearForm();
    void login();
    void swapPagine(char pagina);
    void swapPagine(char pagina, QString nome, QString cognome);
};
#endif // MAINWINDOW_H
