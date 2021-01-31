#ifndef RECUPERO_H
#define RECUPERO_H

#include <QDialog>

namespace Ui {
class Recupero;
}

class Recupero : public QDialog
{
    Q_OBJECT

public:
    explicit Recupero(QWidget *parent = nullptr);
    ~Recupero();

private:
    Ui::Recupero *ui;
};

#endif // RECUPERO_H
