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

    this->setFixedSize(330,340);    //Rendo immodificabili le dimensioni della finestra

    ui->btnaccedi->setHidden(true);         //Nascondo gli elementi non utili
    ui->btngotoiscriviti->setHidden(true);
    ui->lblgotoiscriviti->setHidden(true);
    ui->lblgotorecupero->setHidden(true);
    ui->btngotorecupero->setHidden(true);
    ui->btnrecupero->setHidden(true);

    QDate data = QDate::currentDate();  //Memorizzo la data odierna
    ui->datedata->setDate(data);        //Imposto la data del widget a quella odierna (solo scopo "estetico")
    ui->datedata->setMaximumDate(data); //Imposto la data odierna come massima data selezionabile, non è possibile inserire date nel futuro

    checkUsrDBFile();   //Metodo che verifica la presenza di percorso e file in cui scrivere/leggere info utenti
    insertAdmin();      //Metodo per caricare in memoria le informazioni dell'utente amministratore
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btniscriviti_clicked()
{
    QMessageBox msgIscrizione;      //Oggetto utile a mostrare dialog di errore

    switch (checkElements()){       //A seconda del char ritornato, mostro messaggio di errore
        case 'n': {
                    msgIscrizione.setText("Inserire nome, il nome non può contenere il carattere ',' <- virgola"); //Messaggio di errore
                    msgIscrizione.exec();   //Visualizzo
                    }
                    break;
        case 'c': {
                    msgIscrizione.setText("Inserire cognome, il cognome non può contenere il carattere ',' <- virgola");
                    msgIscrizione.exec();
                    }
                    break;
        case 'p': {
                    msgIscrizione.setText("Inserire password, la password non può contenere il carattere ',' <- virgola");
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
                      insertUtente();   //Scrivo su file il nuovo utente
                      swapPagine('i');  //Mostro pagina di benvenuto post iscrizione
                      clearForm();      //Svuoto tutti i campi inseriti dall'utente
                    }
        }break;
    };

}

void MainWindow::on_btngotoaccedi_clicked()
{
    //Rendo visibili solo elementi utili
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

    clearForm();    //Svuoto tutti i campi inseriti dall'utente


}

void MainWindow::on_btngotoiscriviti_clicked()
{
    //Rendo visibili solo elementi utili
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

    clearForm();    //Svuoto tutti i campi inseriti dall'utente
}

void MainWindow::on_btnaccedi_clicked()
{
    QMessageBox msgAccedi;      //Oggetto utile a mostrare dialog di errore

    switch (checkTelMailPswd()){    //A seconda del char ritornato, mostro messaggio di errore
        case 'm': {
                    msgAccedi.setText("Formato mail non valido");   //Messaggio di errore
                    msgAccedi.exec();   //Visualizzo
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
                    login();    //Se tutto ok, effettuo login
                    } break;
    };

}

char MainWindow::checkElements(){

    //Nome --> Non può essere vuoto e non può contenere ',' (creerebbe inconsistenza nel file). Accetto nomi contenenti caratteri di qualsiasi tipo
    if (ui->lnnome->text()=="" || ui->lnnome->text().contains(','))
        return 'n';

    //Cognome --> Non può essere vuoto e non può contenere ',' (creerebbe inconsistenza nel file). Accetto cognomi contenenti caratteri di qualsiasi tipo
    if (ui->lncognome->text()=="" || ui->lncognome->text().contains(','))
        return 'c';

    //Genere --> Uno dei due radio button deve essere selezionato
    if ((!ui->rdnbtndonna->isChecked()) && (!ui->rdnbtnuomo->isChecked()))
        return 'g';

    //Data --> Sommo 18 anni alla data inserita dall'utente, se maggiore della data odierna erroe
    QDate data = QDate::currentDate();
    QDate dataInserita = ui->datedata->date();

    if (dataInserita.addYears(18)>data)
        return 'd';

    //Tel | Mail, Password
    return checkTelMailPswd();


}

char MainWindow::checkTelMailPswd(){
    QString telmail = ui->lntelmail->text();

    //Variabili d'appoggio
    QString nomeutente, dominio= "";
    QStringList check;

    //Mail
    if (telmail.contains('@') && telmail.contains('.')){  //Controllo se '@' e '.' sono presenti

        check=telmail.split('@');   //Divido la stringa con la mail completa in 2 sottostringhe <nomeutente>@<dominio>
        nomeutente=check[0];
        dominio=check[1];

        //<nomeutente> non deve essere vuoto, il <dominio> deve essere almeno di 4 caratteri e deve contenere un '.' -> (d.it)
        if(nomeutente.length()!=0 && dominio.length()>=4 && dominio.contains('.')){
            for(int i=0;i<nomeutente.length();++i)  //Controllo che <nomeutente> contenga a-Z, 0-9, '.', '-', '_'
                if(!nomeutente[i].isLetter() && !nomeutente[i].isDigit() && nomeutente[i]!='.' && nomeutente[i]!='-' && nomeutente[i]!='_')
                    return 'm';

            check=dominio.split('.');   //Divido la stringa del <dominio> in 2 sottostringhe <dominio1>.<dominio2> riutilizzando le precedenti variabili
            nomeutente=check[0];    //nomeutente -> dominio1
            dominio=check[1];       //dominio -> dominio2

            //<dominio1> deve contenere almeno un carattere, <dominio2> deve contenerne almeno 2 (d.it)
            if(nomeutente.length()>=1 && dominio.length()>=2){
                for(int i=0;i<nomeutente.length();++i)  //Controllo che <dominio1> contenga solo a-Z, 0-9
                    if(!nomeutente[i].isLetter() && !nomeutente[i].isDigit())
                        return 'm';
                for(int i=0;i<dominio.length();++i) //Controllo che <dominio2> contenga solo a-Z
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
    //Pass --> Non può essere vuoto e non può contenere ',' (creerebbe inconsistenza nel file). Accetto password contenenti caratteri di qualsiasi tipo
    if (ui->lnpassword->text()=="" || ui->lnpassword->text().contains(','))
        return 'p';

    return 'o';
}

void MainWindow::checkUsrDBFile(){
    QString percorso = QApplication::applicationDirPath()+"/usrdb/"; //Il percorso che conterrà il file sarà <cartella_eseguibilie>/usrdb/
    QDir dir(percorso); //Creo una cartella con suddetto percorso in memoria

    if(!dir.exists()){  //Controllo l'effettiva esistenza in locale, se NON esiste
        dir.mkpath(percorso);   //Creo cartella
        csv.setFileName(percorso+"usr.csv");    //Creo un file chiamato usr.csv nel precedente percorso in memoria
        csv.open(QIODevice::ReadOnly);      //Creo il file in locale
        csv.close();                        //Chiudo il file
    }
    else
        if(!csv.exists()){  //Se il controllo del percorso da esito positivo, controllo l'esistenza del file, in caso NEGATIVO creo il file
            csv.setFileName(percorso + "usr.csv");
            csv.open(QIODevice::ReadOnly);
            csv.close();
        }
}

void MainWindow::insertAdmin(){

    //Memorizzo in memoria le info dell'utente admin
    admin.nome = "Super";
    admin.cognome = "User";
    admin.telmail = "admin@pas.com";
    admin.dataNascita = QDate::fromString("03101981","ddMMyyyy");
    admin.genere = 'M';
    admin.password = "admin";
}

bool MainWindow::checkIscritto(){

    bool iscritto=false;

    csv.open(QIODevice::ReadOnly);  //Apro il file in lettura
    QTextStream in(&csv);           //Creo stream di input

    while(!in.atEnd() && !iscritto){    //Fintanto che non sono alla fine del file E iscritto è false
        QStringList stringaUtente = in.readLine().split(',');   //Leggo riga del file
        if(ui->lntelmail->text() == stringaUtente[2]) //Controllo che mail/tel inserito dall'utente si uguale a mail/tel letto dal file
            iscritto = true;
    }

    in.flush();     //Svuoto stream di output
    csv.close();    //Chiudo il file

    return iscritto;
}

void MainWindow::insertUtente(){

    //Salvo in memoria tutto ciò che ha inserito l'utente nella form
    utente u;
    u.nome = ui->lnnome->text();
    u.cognome = ui->lncognome->text();
    u.telmail = ui->lntelmail->text().toLower(); //Per evitare problemi dovuti a caratteri min/MAIUSC rendo la mail tutta minuscola
    u.dataNascita = ui->datedata->date();
    if(ui->rdnbtndonna->isChecked())
        u.genere = 'F';
    else
        u.genere = 'M';
    u.password = ui->lnpassword->text();

    csv.open(QIODevice::Append); //Apro il file scrivendo in coda

    QTextStream out(&csv);      //Apro stream di output

    //Scrivo su file separando ogni campo con ','
    out << u.nome << "," << u.cognome << "," << u.telmail << "," << u.dataNascita.toString("ddMMyyyy") << "," << u.genere << "," << u.password << "\n";
    out.flush();    //Svuoto stream di output
    csv.close();    //Chiudo il file
}

void MainWindow::clearForm(){

    //Svuoto tutti i campi
    ui->lnnome->setText("");
    ui->lncognome->setText("");
    ui->lntelmail->setText("");
    ui->lnpassword->setText("");
    ui->datedata->setDate(QDate::currentDate()); //Imposto nuovamente la data a quella corrente

    //Deseleziono i radio button
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
    //Rendo visibili solo gli elementi necessari
    ui->btnrecupero->setHidden(false);
    ui->lnpassword->setHidden(true);
    ui->btnaccedi->setHidden(true);
    ui->lblgotorecupero->setHidden(true);
    ui->btngotorecupero->setHidden(true);

    clearForm();    //Svuoto tutti i campi

}

void MainWindow::on_btnrecupero_clicked()
{
    QMessageBox msgRecupero;    //Oggetto utile a mostrare dialog di errore

    switch(checkTelMailPswd()){ //A seconda del char ritornato mostro messaggio di errore
    case 'm':{
                msgRecupero.setText("Formato mail non valido"); //Messaggio di errore
                msgRecupero.exec(); //Visualizzo
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

    QMessageBox login;  //Oggetto utile a mostrare dialog di errore

        //Admin --> Confronto ciò che è stato inserito nella form con l'utente admin in memoria
        if(ui->lntelmail->text().toLower() == admin.telmail){
            if(ui->lnpassword->text() == admin.password){
                swapPagine('a',admin.nome,admin.cognome);   //Se il confronto è positivo, mostro la pagina dell'amministratore
                clearForm();    //Svuoto i campi inseriti dall'utente
            }
            else{
                login.setText("Password errata");
                login.exec();
            }
        }
        //Utenti --> Confronto ciò che è stato inserito nella form con gli utenti salvati nel file
        else{
            bool signin=false;              //Variabile d'appoggio
            csv.open(QIODevice::ReadOnly);  //Apro il file in sola lettura
            QTextStream in(&csv);           //Creo stream di input

            while(!in.atEnd() && !signin){  //Fintanto che non leggo tutto il file e signin è FALSE

                QStringList stringaUtente = in.readLine().split(',');   //Leggo riga dal file

                if(ui->lntelmail->text().toLower() == stringaUtente[2]){ //Confronto il campo telmail con ciò che è stato letto dal file
                    if (ui->lnpassword->text() == stringaUtente[5]){    //Confronto il campo password con ciò che è stato letto dal file
                        swapPagine('u',stringaUtente[0],stringaUtente[1]);  //Se tel/mail e password coincidono mostro pagina di benvenuto all'utente
                        clearForm();    //Svuoto i campi inseriti dall'utente
                    }
                    else{
                        login.setText("Password errata!");
                        login.exec();
                    }

                    signin = true;  //Se tel/mail e password coincidono signin = TRUE
                }

            }
            if(!signin){    //Se il login non è andato a buon fine mostro messaggio d'errore
                login.setText("Utente non presente a sistema");
                login.exec();
            }

            in.flush(); //Svuoto stream di input
            csv.close();    //Chiudo file
         }
    }

void MainWindow::swapPagine(char pagina){

    switch(pagina){
        case 'i':{  //Pagina iscrizione
            this->hide();   //Nascondo la pagina attuale
            Iscrizione ip(this);    //Creo oggetto di tipo Iscrizione per gestire l'omonima pagina
            ip.setModal(true);      //Rendo la finestra iscrizione modale, in modo da poter interagire solo con quella una volta visualizzata
            ip.setNome(ui->lnnome->text());     //Personalizzo pagina di benvenuto con nome utente
            ip.setCognome(ui->lncognome->text());   //Personalizzo pagina di benvenuto con cognome utente
            ip.exec();  //Visualizzo pagina iscrizione
            this->show();   //Una volta chiusa la pagina di iscrizione rimostro l'attuale
        }
        break;
        case 'r':{  //Pagina recupero password
            this->hide();       //Nascondo la pagina attuale
            Recupero rp(this);  //Creo oggetto di tipo Recupero per gestire l'omonima pagina
            rp.setModal(true);  //Rendo la finestra recupero modale, in modo da poter interagire solo con quella una volta visualizzata
            rp.exec();      //Visualizzo pagina recupero
            this->show();   //Una volta chiusa la pagina di recupero rimostro l'attuale
        }
        break;
    };
}

void MainWindow::swapPagine(char pagina, QString nome, QString cognome){    //Overloading del metodo precedente, qui passo nome e cognome in input al metodo

    switch(pagina){
        case 'u':{      //Pagina login utente
            this->hide();    //Nascondo la pagina attuale
            Loginusr lp(this);  //Creo oggetto di tipo Loginusr per gestire l'omonima pagina
            lp.setModal(true);  //Rendo la finestra loginusr modale, in modo da poter interagire solo con quella una volta visualizzata
            lp.setNome(nome);   //Utilizzo il metodo setter per il nome
            lp.setCognome(cognome); //Utilizzo il metodo setter per il cognome
            lp.exec();      //Visualizzo la pagina loginusr
            this->show();   //Una volta chiusa la pagina di loginusr rimostro l'attuale
        }
        break;

        case 'a':{      //Pagina login admin
            this->hide();   //Nascondo la pagina attuale
            Loginadmin ap(this);    //Creo oggetto di tipo Loginadmin per gestire l'omonima pagina
            ap.setModal(true);      //Rendo la finestra loginadmin modale, in modo da poter interagire solo con quella una volta visualizzata
            ap.setAdmin(nome,cognome);  //Utilizzo il metodo setter per nome e cognome dell'admin
            ap.brgFile(&csv);   //Passo il riferimento al file, verrà utilizzato dalle 2 pagine che mostreranno grafici ed elenco
            ap.exec();      //Visualizzo la pagina loginuadmin
            this->show();       //Una volta chiusa la pagina di loginadmin rimostro l'attuale
        }
        break;
    };
}
