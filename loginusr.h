#ifndef LOGINUSR_H
#define LOGINUSR_H

#include <QDialog>

namespace Ui {
class Loginusr;
}

class Loginusr : public QDialog
{
    Q_OBJECT

public:
    explicit Loginusr(QWidget *parent = nullptr);
    ~Loginusr();

    //Metodi per personalizzazione pagina di login
    void setNome(QString n);
    void setCognome(QString c);

private:
    Ui::Loginusr *ui;
};

#endif // LOGINUSR_H
