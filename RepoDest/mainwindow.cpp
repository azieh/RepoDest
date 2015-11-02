#include "mainwindow.h"
#include "ui_mainwindow.h"






MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setIconAndConnection();
    guiSetup();
    guiConnection();
    threadManager();
}

MainWindow::~MainWindow()
{
    delete ui;
    thread1.quit();
    thread2.quit();
    thread3.quit();
    thread4.quit();
}

void MainWindow::on_lineEditTotal_textChanged(const QString &arg1)
{
    ui->lineEditTotal->setText(arg1);
}


void MainWindow::on_plainTextEditSt10_textChanged(const QString &arg1)
{
    ui->plainTextEditSt10->appendPlainText(arg1);
}
void MainWindow::on_plainTextEditSt20_textChanged(const QString &arg1)
{
    ui->plainTextEditSt20->appendPlainText(arg1);
}
void MainWindow::on_plainTextEditSt30_textChanged(const QString &arg1)
{
    ui->plainTextEditSt30->appendPlainText(arg1);
}
void MainWindow::on_plainTextEditSt40_textChanged(const QString &arg1)
{
    ui->plainTextEditSt40->appendPlainText(arg1);
}
void MainWindow::on_plainTextEditSt50_textChanged(const QString &arg1)
{
    ui->plainTextEditSt50->appendPlainText(arg1);
}
void MainWindow::on_plainTextEditSt60_textChanged(const QString &arg1)
{
    ui->plainTextEditSt60->appendPlainText(arg1);
}
void MainWindow::on_plainTextEditSt70_textChanged(const QString &arg1)
{
    ui->plainTextEditSt70->appendPlainText(arg1);
}
void MainWindow::on_plainTextEditSt80_textChanged(const QString &arg1)
{
    ui->plainTextEditSt80->appendPlainText(arg1);
}
void MainWindow::on_plainTextEditSt90_textChanged(const QString &arg1)
{
    ui->plainTextEditSt90->appendPlainText(arg1);
}
void MainWindow::on_plainTextEditSt100_textChanged(const QString &arg1)
{
    ui->plainTextEditSt100->appendPlainText(arg1);
}
void MainWindow::on_plainTextEditSt110_textChanged(const QString &arg1)
{
    ui->plainTextEditSt110->appendPlainText(arg1);
}
void MainWindow::on_plainTextEditSt120_textChanged(const QString &arg1)
{
    ui->plainTextEditSt120->appendPlainText(arg1);
}
void MainWindow::setIconAndConnection()
{
    QPixmap warningIcon = QPixmap(":/ico/Warning.ico");
    warningIcon = warningIcon.scaled(QSize(25, 25), Qt::KeepAspectRatio);

    ui->labelSt10Ico->setPixmap(warningIcon);
    ui->labelSt20Ico->setPixmap(warningIcon);
    ui->labelSt30Ico->setPixmap(warningIcon);
    ui->labelSt40Ico->setPixmap(warningIcon);
    ui->labelSt50Ico->setPixmap(warningIcon);
    ui->labelSt60Ico->setPixmap(warningIcon);
    ui->labelSt70Ico->setPixmap(warningIcon);
    ui->labelSt80Ico->setPixmap(warningIcon);
    ui->labelSt90Ico->setPixmap(warningIcon);
    ui->labelSt100Ico->setPixmap(warningIcon);
    ui->labelSt110Ico->setPixmap(warningIcon);
    ui->labelSt120Ico->setPixmap(warningIcon);
}

void MainWindow::guiConnection()
{
    connect(&st10,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt10_textChanged(QString)));
    connect(&st20,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt20_textChanged(QString)));
    connect(&st30,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt30_textChanged(QString)));
    connect(&st40,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt40_textChanged(QString)));
    connect(&st50,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt50_textChanged(QString)));
    connect(&st60,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt60_textChanged(QString)));
    connect(&st70,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt70_textChanged(QString)));
    connect(&st80,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt80_textChanged(QString)));
    connect(&st90,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt90_textChanged(QString)));
    connect(&st100,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt100_textChanged(QString)));
    connect(&st110,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt110_textChanged(QString)));
    connect(&st120,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt120_textChanged(QString)));
}

void MainWindow::guiSetup()
{
    ui->plainTextEditSt10->setMaximumBlockCount(10);
    ui->plainTextEditSt20->setMaximumBlockCount(10);
    ui->plainTextEditSt30->setMaximumBlockCount(10);
    ui->plainTextEditSt40->setMaximumBlockCount(10);
    ui->plainTextEditSt50->setMaximumBlockCount(10);
    ui->plainTextEditSt60->setMaximumBlockCount(10);
    ui->plainTextEditSt70->setMaximumBlockCount(10);
    ui->plainTextEditSt80->setMaximumBlockCount(10);
    ui->plainTextEditSt90->setMaximumBlockCount(10);
    ui->plainTextEditSt100->setMaximumBlockCount(10);
    ui->plainTextEditSt110->setMaximumBlockCount(10);
    ui->plainTextEditSt120->setMaximumBlockCount(10);
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
