#ifndef ISCRIZIONE_H
#define ISCRIZIONE_H

#include <QDialog>

namespace Ui {
class Iscrizione;
}

class Iscrizione : public QDialog
{
    Q_OBJECT

public:
    explicit Iscrizione(QWidget *parent = nullptr);
    ~Iscrizione();

    //Metodi per personalizzazione pagina di benvenuto
    void setNome(QString n);
    void setCognome(QString c);

private:
    Ui::Iscrizione *ui;
};

#endif // ISCRIZIONE_H
