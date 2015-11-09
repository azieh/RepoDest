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

public slots:

private slots:
    void on_plainTextEdit_textChanged(const QString &stName, const QString &arg1);
    void on_labelStatus_Changed(const QString &stName, bool arg1);
    void on_lineEditOk_Changed(const QString &stName, int arg1);
    void on_lineEditNok_Changed(const QString &stName, int arg1);
    void on_lineEditTime_Changed(const QString &stName, const QString &arg1);

    void on_pushButtonQuit_clicked();

signals:
    void startThread();

};

#endif // MAINWINDOW_H
