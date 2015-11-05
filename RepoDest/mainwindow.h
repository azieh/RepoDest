#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "threadmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_lineEditTotal_textChanged(const QString &arg1);

private slots:
    void on_plainTextEditSt10_textChanged(const QString &arg1);
    void on_labelSt10Status_Changed(bool arg1);
    void on_lineEditSt10Ok_Changed(int &arg1);
    void on_lineEditSt10Nok_Changed(int &arg1);
    void on_lineEditSt10Total_Changed(int &arg1);

    void on_plainTextEditSt20_textChanged(const QString &arg1);
    void on_plainTextEditSt30_textChanged(const QString &arg1);
    void on_plainTextEditSt40_textChanged(const QString &arg1);
    void on_plainTextEditSt50_textChanged(const QString &arg1);
    void on_plainTextEditSt60_textChanged(const QString &arg1);
    void on_plainTextEditSt70_textChanged(const QString &arg1);
    void on_plainTextEditSt80_textChanged(const QString &arg1);
    void on_plainTextEditSt90_textChanged(const QString &arg1);
    void on_plainTextEditSt100_textChanged(const QString &arg1);
    void on_plainTextEditSt110_textChanged(const QString &arg1);
    void on_plainTextEditSt120_textChanged(const QString &arg1);

private:
    Ui::MainWindow* ui;
    ThreadManager* tm;

    QPixmap _connectedIcon;
    QPixmap _warningIcon;

    void createThreadManager();
    void setIconAndConnectionTextStatus();
    void setGuiConnection();
    void setGuiSetup();

};

#endif // MAINWINDOW_H
