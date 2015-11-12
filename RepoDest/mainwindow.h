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
    ThreadManager* tm;

private:
    Ui::MainWindow* ui;

    QPixmap _connectedIcon;
    QPixmap _warningIcon;

    void createThreadManager();
    void setIconAndConnectionTextStatus();
    void setGuiConnection();
    void setGuiSetup();

private slots:
    void plainTextEdit_textChanged(const QString &stName, const QString &arg1);
    void labelStatus_Changed(const QString &stName, bool arg1);
    void lineEditOk_Changed(const QString &stName, int arg1);
    void lineEditNok_Changed(const QString &stName, int arg1);
    void lineEditTime_Changed(const QString &stName, const QString &arg1);

    void on_pushButtonQuit_clicked();

signals:
    void startThread();

};

#endif // MAINWINDOW_H
