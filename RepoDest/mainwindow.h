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

    QThread firstThread;
    WorkArea st10;



public slots:
    void on_lineEditTotal_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
