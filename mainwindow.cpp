#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
//#include <QDateTime>
#include <QDir>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btniscriviti_clicked()
{
    QMessageBox msgIscrizione;

    switch (checkElements()){
        case 'n': {
                    msgIscrizione.setText("Inserire nome");
                    msgIscrizione.exec();
                    }
                    break;
        case 'c': {
                    msgIscrizione.setText("Inserire cognome");
                    msgIscrizione.exec();
                    }
                    break;
        case 'p': {
                    msgIscrizione.setText("Inserire password");
                    msgIscrizione.exec();
                    }
                    break;
        case 'g': {
                    msgIscrizione.setText("Selezionare il genere");
                    msgIscrizione.exec();
                    }
                    break;
        case 'd': {
                    msgIscrizione.setText("Necessaria la maggiore età");
                    msgIscrizione.exec();
                    }
                    break;
        case 'm': {
                    msgIscrizione.setText("Formato mail non valido");
                    msgIscrizione.exec();
                    }
                    break;
        case 't': {
                    msgIscrizione.setText("Formato numero telefonico non valido");
                    msgIscrizione.exec();
                    }
                    break;
        case 'o': {/*Tutto ok*/} break;
    };

    /*
    QString percorso = QApplication::applicationDirPath()+"/usrdb/";
    QDir dir(percorso);
    QFile csv;

    if(!dir.exists()){
        dir.mkpath(percorso);
        csv.setFileName(percorso+"usr.csv");
        csv.open(QIODevice::WriteOnly);
        csv.close();
    }
    else
        if(!csv.exists()){
            csv.setFileName(percorso + "usr.csv");
            csv.open(QIODevice::WriteOnly);
            csv.close();
        }*/

}

void MainWindow::on_btngotoaccedi_clicked()
{
    ui->btniscriviti->setHidden(true);
    ui->btngotoaccedi->setHidden(true);
    ui->lblgotoaccedi->setHidden(true);
    ui->lnnome->setHidden(true);
    ui->lncognome->setHidden(true);
    ui->datedata->setHidden(true);
    ui->rdnbtndonna->setHidden(true);
    ui->rdnbtnuomo->setHidden(true);

    ui->btnaccedi->setHidden(false);
    ui->btngotoiscriviti->setHidden(false);
    ui->lblgotoiscriviti->setHidden(false);


}

void MainWindow::on_btngotoiscriviti_clicked()
{

    ui->btniscriviti->setHidden(false);
    ui->btngotoaccedi->setHidden(false);
    ui->lblgotoaccedi->setHidden(false);
    ui->lnnome->setHidden(false);
    ui->lncognome->setHidden(false);
    ui->datedata->setHidden(false);
    ui->rdnbtndonna->setHidden(false);
    ui->rdnbtnuomo->setHidden(false);

    ui->btnaccedi->setHidden(true);
    ui->btngotoiscriviti->setHidden(true);
    ui->lblgotoiscriviti->setHidden(true);
}

void MainWindow::on_btnaccedi_clicked()
{
    QMessageBox msgAccedi;

    switch (checkTelMailPswd()){
        case 'm': {
                    msgAccedi.setText("Formato mail non valido");
                    msgAccedi.exec();
                    }
                    break;
        case 't': {
                    msgAccedi.setText("Formato numero telefonico non valido");
                    msgAccedi.exec();
                    }
                    break;
        case 'p': {
                    msgAccedi.setText("Inserire password");
                    msgAccedi.exec();
                    }
                    break;
        case 'o': { /*tutto ok*/} break;
    };

}

char MainWindow::checkElements(){

    //Nome
    if (ui->lnnome->text()=="")
        return 'n';

    //Cognome
    if (ui->lncognome->text()=="")
        return 'c';

    //Genere
    if ((!ui->rdnbtndonna->isChecked()) && (!ui->rdnbtnuomo->isChecked()))
        return 'g';

    //Data
    /*QDate data = QDate::currentDate();
    QDate dataInserita = ui->datedata->date();

    qint64 diffdata = data.toJulianDay() - dataInserita.toJulianDay();
    QDate diffdata2 = QDate::fromJulianDay(diffdata);
    QDate primoJulian = QDate::fromJulianDay(0);

    int anno = diffdata2.year() - primoJulian.year();

    if (anno<18)
        return 'd'; */

    //Data --> Sommo 18 anni alla data inserita dall'utente, se maggiore della data odierna erroe
    QDate data = QDate::currentDate();
    QDate dataInserita = ui->datedata->date();

    if (dataInserita.addYears(18)>data)
        return 'd';

    //Tel | Mail, PAssword
    return checkTelMailPswd();


}

char MainWindow::checkTelMailPswd(){
    QString telmail = ui->lntelmail->text();

    //Mail
    if (telmail.contains('@')){
        qint16 chiocind = telmail.indexOf('@');
        qint16 puntind = telmail.lastIndexOf('.');
        if(chiocind<1 || puntind<chiocind+2 || puntind+2>=telmail.length())
            return 'm';
    }
    else{
    //Tel  --> Controllo della lunghezza del numero di cellulare, poi controllo se tutte cifre
        if (telmail.length()==10){
            for (int i=0;i<telmail.length();++i)
                if (!telmail[i].isDigit())
                    return 't';
        }
        else
            return 't';

     }
    //Pass
    if (ui->lnpassword->text()=="")
        return 'p';

    return 'o';
}


