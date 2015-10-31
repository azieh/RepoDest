#include "mainwindow.h"
#include "ui_mainwindow.h"






MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    st10.doSetup(thread1);
    st10.moveToThread(&thread1);
    st10.name = "St10";

    st20.doSetup(thread1);
    st20.moveToThread(&thread1);
    st20.name = "St20";

    st30.doSetup(thread2);
    st30.moveToThread(&thread2);
    st30.name = "St30";

    st40.doSetup(thread2);
    st40.moveToThread(&thread2);
    st40.name = "St40";

    st50.doSetup(thread3);
    st50.moveToThread(&thread3);
    st50.name = "St50";

    st60.doSetup(thread4);
    st60.moveToThread(&thread4);
    st60.name = "St60";

   // firstThread.msleep(1);
    thread1.start();
    thread2.start();
    thread3.start();
    thread4.start();







}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEditTotal_textChanged(const QString &arg1)
{
 ui->lineEditTotal->setText(arg1);
}
