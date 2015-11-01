#include "mainwindow.h"
#include "ui_mainwindow.h"






MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    threadManager();
    setIconAndConnection();
    connect(&st10,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt10_textChanged(QString)));

    ui->plainTextEditSt10->setMaximumBlockCount(10);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEditTotal_textChanged(const QString &arg1)
{
    ui->lineEditTotal->setText(arg1);
}


void MainWindow::on_plainTextEditSt10_textChanged(const QString &arg1)
{
    ui->plainTextEditSt10->appendPlainText(arg1);
}

void MainWindow::setIconAndConnection()
{
    QPixmap warningIcon = QPixmap(":/ico/Warning.ico");
    warningIcon = warningIcon.scaled(QSize(25, 25), Qt::KeepAspectRatio);

    ui->labelSt10Ico->setPixmap(warningIcon);
    ui->labelSt20Ico->setPixmap(warningIcon);
    ui->labelSt30Ico->setPixmap(warningIcon);
}

void MainWindow::threadManager()
{
    st10.doSetup(thread1);
    st10.moveToThread(&thread1);
    st10.name = "St10";

    st20.doSetup(thread1);
    st20.moveToThread(&thread1);
    st20.name = "St20";

    st30.doSetup(thread1);
    st30.moveToThread(&thread1);
    st30.name = "St30";

    st40.doSetup(thread2);
    st40.moveToThread(&thread2);
    st40.name = "St40";

    st50.doSetup(thread2);
    st50.moveToThread(&thread2);
    st50.name = "St50";

    st60.doSetup(thread2);
    st60.moveToThread(&thread2);
    st60.name = "St60";

    st70.doSetup(thread3);
    st70.moveToThread(&thread3);
    st70.name = "St70";

    st80.doSetup(thread3);
    st80.moveToThread(&thread3);
    st80.name = "St80";

    st90.doSetup(thread3);
    st90.moveToThread(&thread3);
    st90.name = "St90";

    st100.doSetup(thread4);
    st100.moveToThread(&thread4);
    st100.name = "St100";

    st110.doSetup(thread4);
    st110.moveToThread(&thread4);
    st110.name = "St110";

    st120.doSetup(thread4);
    st120.moveToThread(&thread4);
    st120.name = "St120";

    thread1.start();
    thread2.start();
    thread3.start();
    thread4.start();
}
