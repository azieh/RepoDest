#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "workarea.h"



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
    Ui::MainWindow *ui;

    QThread* thread1;
    QThread* thread2;
    QThread* thread3;
    QThread* thread4;
    WorkArea* st10;
    WorkArea* st20;
    WorkArea* st30;
    WorkArea* st40;
    WorkArea* st50;
    WorkArea* st60;
    WorkArea* st70;
    WorkArea* st80;
    WorkArea* st90;
    WorkArea* st100;
    WorkArea* st110;
    WorkArea* st120;
    WorkArea* st130;

    void setIconAndConnection();
    void threadManager();
    void guiConnection();
    void guiSetup();
};

#endif // MAINWINDOW_H
