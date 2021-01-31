#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDate>

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

    char checkElements();
    char checkTelMailPswd();
    void checkUsrDBFile();
    void insertAdmin();
    bool checkIscritto();
    void insertUtente();
};
#endif // MAINWINDOW_H
