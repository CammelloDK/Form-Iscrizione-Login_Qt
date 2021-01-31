#ifndef LOGINADMIN_H
#define LOGINADMIN_H

#include <QDialog>

namespace Ui {
class Loginadmin;
}

class Loginadmin : public QDialog
{
    Q_OBJECT

public:
    explicit Loginadmin(QWidget *parent = nullptr);
    ~Loginadmin();

    void setNome(QString n);
    void setCognome(QString c);

private:
    Ui::Loginadmin *ui;
};

#endif // LOGINADMIN_H
