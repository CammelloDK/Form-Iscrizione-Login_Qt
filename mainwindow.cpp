#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(330,340);

    ui->btnaccedi->setHidden(true);
    ui->btngotoiscriviti->setHidden(true);
    ui->lblgotoiscriviti->setHidden(true);
    ui->lblgotorecupero->setHidden(true);
    ui->btngotorecupero->setHidden(true);
    ui->btnrecupero->setHidden(true);

    QDate data = QDate::currentDate();
    ui->datedata->setDate(data);
    ui->datedata->setMaximumDate(data);

    checkUsrDBFile();
    insertAdmin();
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
        case 'x': {
                    msgIscrizione.setText("Inserire un indirizzo mail o un numero telefonico valido");
                    msgIscrizione.exec();
                    }
                    break;
        case 'o': {if(checkIscritto()){
                    msgIscrizione.setText("Utente già presente a sistema");
                    msgIscrizione.exec();
                    }
                      else {
                      insertUtente();
                      /*msgIscrizione.setText("Utente inserito a sistema");
                      msgIscrizione.exec();*/
                      swapPagine('i');
                      clearForm();
                    }
        }break;
    };

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

    ui->lblgotorecupero->setHidden(false);
    ui->btngotorecupero->setHidden(false);

    ui->btnaccedi->setHidden(false);
    ui->btngotoiscriviti->setHidden(false);
    ui->lblgotoiscriviti->setHidden(false);

    clearForm();


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

    ui->lblgotorecupero->setHidden(true);
    ui->btngotorecupero->setHidden(true);
    ui->btnrecupero->setHidden(true);

    ui->btnaccedi->setHidden(true);
    ui->btngotoiscriviti->setHidden(true);
    ui->lblgotoiscriviti->setHidden(true);

    if(ui->lnpassword->isHidden())
        ui->lnpassword->setHidden(false);

    clearForm();
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
        case 'x': {
                    msgAccedi.setText("Inserire un indirizzo mail o un numero telefonico valido");
                    msgAccedi.exec();
                    }
                    break;
        case 'p': {
                    msgAccedi.setText("Inserire password");
                    msgAccedi.exec();
                    }
                    break;
        case 'o': {
                    login();
                    } break;
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
    QString nomeutente, dominio= "";
    QStringList check;

    //Mail
    if (telmail.contains('@') && telmail.contains('.')){

        check=telmail.split('@');
        nomeutente=check[0];
        dominio=check[1];

        if(nomeutente.length()!=0 && dominio.length()>=4 && dominio.contains('.')){
            for(int i=0;i<nomeutente.length();++i)
                if(!nomeutente[i].isLetter() && !nomeutente[i].isDigit() && nomeutente[i]!='.' && nomeutente[i]!='-' && nomeutente[i]!='_')
                    return 'm';

            check=dominio.split('.');
            nomeutente=check[0];
            dominio=check[1];

            if(nomeutente.length()>=1 && dominio.length()>=2){
                for(int i=0;i<nomeutente.length();++i)
                    if(!nomeutente[i].isLetter() && !nomeutente[i].isDigit())
                        return 'm';
                for(int i=0;i<dominio.length();++i)
                    if(!dominio[i].isLetter())
                        return 'm';
            }
            else
                return 'm';

        }
        else
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
            return 'x';

     }
    //Pass
    if (ui->lnpassword->text()=="")
        return 'p';

    return 'o';
}

void MainWindow::checkUsrDBFile(){
    QString percorso = QApplication::applicationDirPath()+"/usrdb/";
    QDir dir(percorso);

    if(!dir.exists()){
        dir.mkpath(percorso);
        csv.setFileName(percorso+"usr.csv");
        csv.open(QIODevice::ReadOnly);
        csv.close();
    }
    else
        if(!csv.exists()){
            csv.setFileName(percorso + "usr.csv");
            csv.open(QIODevice::ReadOnly);
            csv.close();
        }
}

void MainWindow::insertAdmin(){

    admin.nome = "Zlatan";
    admin.cognome = "Ibrahimovic";
    admin.telmail = "admin@pas.com";
    admin.dataNascita = QDate::fromString("03101981","ddMMyyyy");
    admin.genere = 'M';
    admin.password = "admin";
}

bool MainWindow::checkIscritto(){

    bool iscritto=false;

    csv.open(QIODevice::ReadOnly);
    QTextStream in(&csv);

    while(!in.atEnd() && !iscritto){
        QStringList stringaUtente = in.readLine().split(',');
        if(ui->lntelmail->text() == stringaUtente[2]) //Terzo parametro
            iscritto = true;
    }

    in.flush();
    csv.close();

    return iscritto;
}

void MainWindow::insertUtente(){
    utente u;
    u.nome = ui->lnnome->text();
    u.cognome = ui->lncognome->text();
    u.telmail = ui->lntelmail->text().toLower();
    u.dataNascita = ui->datedata->date();
    if(ui->rdnbtndonna->isChecked())
        u.genere = 'F';
    else
        u.genere = 'M';
    u.password = ui->lnpassword->text();

    csv.open(QIODevice::Append); //Scrive in coda

    QTextStream out(&csv);
    out << u.nome << "," << u.cognome << "," << u.telmail << "," << u.dataNascita.toString("ddMMyyyy") << "," << u.genere << "," << u.password << "\n";
    out.flush();
    csv.close();
}

void MainWindow::clearForm(){
    ui->lnnome->setText("");
    ui->lncognome->setText("");
    ui->lntelmail->setText("");
    ui->lnpassword->setText("");
    ui->datedata->setDate(QDate::currentDate());

    if(ui->rdnbtndonna->isChecked()){
        this->ui->rdnbtndonna->setAutoExclusive(false);
        ui->rdnbtndonna->setChecked(false);
        this->ui->rdnbtndonna->setAutoExclusive(true);
    }
    else{
        this->ui->rdnbtnuomo->setAutoExclusive(false);
        ui->rdnbtnuomo->setChecked(false);
        this->ui->rdnbtnuomo->setAutoExclusive(true);
    }
}

void MainWindow::on_btngotorecupero_clicked()
{
    ui->btnrecupero->setHidden(false);
    ui->lnpassword->setHidden(true);
    ui->btnaccedi->setHidden(true);
    ui->lblgotorecupero->setHidden(true);
    ui->btngotorecupero->setHidden(true);

    clearForm();

}

void MainWindow::on_btnrecupero_clicked()
{
    QMessageBox msgRecupero;

    switch(checkTelMailPswd()){
    case 'm':{
                msgRecupero.setText("Formato mail non valido");
                msgRecupero.exec();
            }
            break;
    case 't':{
                msgRecupero.setText("Formato numero telefonico non valido");
                msgRecupero.exec();
            }
            break;
    case 'p':
    case 'o':{
                if(checkIscritto()){
                    swapPagine('r');
                    //msgRecupero.setText("e-mail e/o SMS con procedura di ripristino inviata");
                    //msgRecupero.exec();
                    clearForm();
                }
                else{
                    msgRecupero.setText("Utente non presente a sistema");
                    msgRecupero.exec();
                }
            }
            break;
    };
}

void MainWindow::login(){

    QMessageBox login;


        if(ui->lntelmail->text().toLower() == admin.telmail){
            if(ui->lnpassword->text() == admin.password){
                //login.setText("Benvenuto superuser " + admin.nome + " " + admin.cognome);
                swapPagine('a',admin.nome,admin.cognome);
                clearForm();
                //Apri grafico
            }
            else{
                login.setText("Password errata");
                login.exec();
            }
        }

        else{
            bool signin=false;
            csv.open(QIODevice::ReadOnly);
            QTextStream in(&csv);

            while(!in.atEnd() && !signin){

                QStringList stringaUtente = in.readLine().split(',');

                if(ui->lntelmail->text().toLower() == stringaUtente[2]){ //Terzo parametro
                    if (ui->lnpassword->text() == stringaUtente[5]){
                        //login.setText("Benvenuto " + stringaUtente[0] + " " + stringaUtente[1]);
                        swapPagine('u',stringaUtente[0],stringaUtente[1]);
                        clearForm();
                    }
                    else{
                        login.setText("Password errata!");
                        login.exec();
                    }

                    signin = true;
                }

            }
            if(!signin){
                login.setText("Utente non presente a sistema");
                login.exec();
            }

            in.flush();
            csv.close();
         }
    }

void MainWindow::swapPagine(char pagina){

    switch(pagina){
        case 'i':{
            this->hide();
            Iscrizione ip(this);
            ip.setModal(true);
            ip.setNome(ui->lnnome->text());
            ip.setCognome(ui->lncognome->text());
            ip.exec();
            this->show();
        }
        break;
        case 'r':{
            this->hide();
            Recupero rp(this);
            rp.setModal(true);
            rp.exec();
            this->show();
        }
        break;
    };
}

void MainWindow::swapPagine(char pagina, QString nome, QString cognome){

    switch(pagina){
        case 'u':{
            this->hide();
            Loginusr lp(this);
            lp.setModal(true);
            lp.setNome(nome);
            lp.setCognome(cognome);
            lp.exec();
            this->show();
        }
        break;

        case 'a':{
            this->hide();
            Loginadmin ap(this);
            ap.setModal(true);
            ap.setAdmin(nome,cognome);
            ap.setGrafico(&csv);
            ap.exec();
            this->show();
        }
        break;
    };
}
