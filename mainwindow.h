#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    char checkElements();
    char checkTelMailPswd();
};
#endif // MAINWINDOW_H
