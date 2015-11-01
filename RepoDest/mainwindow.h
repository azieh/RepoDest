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

    QThread thread1, thread2, thread3, thread4;
    WorkArea st10, st20, st30, st40, st50, st60, st70, st80, st90, st100, st110, st120;

public slots:
    void on_lineEditTotal_textChanged(const QString &arg1);
    void on_plainTextEditSt10_textChanged(const QString &arg1);

private slots:

private:
    Ui::MainWindow *ui;

    void setIconAndConnection();
    void threadManager();
};

#endif // MAINWINDOW_H
