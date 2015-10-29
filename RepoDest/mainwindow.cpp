#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_lineEditTotal_textChanged("asdaaa");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEditTotal_textChanged(const QString &arg1)
{
 ui->lineEditTotal->setText(arg1);
}
