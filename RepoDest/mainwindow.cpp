#include "mainwindow.h"
#include "ui_mainwindow.h"






MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    thread1(nullptr),
    thread2(nullptr),
    thread3(nullptr),
    thread4(nullptr),
    st10(nullptr),
    st20(nullptr),
    st30(nullptr),
    st40(nullptr),
    st50(nullptr),
    st60(nullptr),
    st70(nullptr),
    st80(nullptr),
    st90(nullptr),
    st100(nullptr),
    st110(nullptr),
    st120(nullptr),
    st130(nullptr)

{
    ui->setupUi(this);
    threadManager(); //generete and manage every station program in direct thread
    setIconAndConnection(); //set default icon for connection status
    guiSetup(); //initial settings for GUI
    guiConnection(); //generete and manage connection between GUI and WorkArea stations

}

MainWindow::~MainWindow()
{
    delete ui;

    //Wait and clear every thread
    thread1->quit();
    delete thread1;
    thread1 = nullptr;

    thread2->quit();
    delete thread2;
    thread2 = nullptr;

    thread3->quit();
    delete thread3;
    thread3 = nullptr;

    thread4->quit();
    delete thread4;
    thread4 = nullptr;

    //Clear memory about every station instance
    delete st10;
    st10 = nullptr;
    delete st20;
    st20 = nullptr;
    delete st30;
    st30 = nullptr;
    delete st40;
    st40 = nullptr;
    delete st50;
    st50 = nullptr;
    delete st60;
    st60 = nullptr;
    delete st70;
    st70 = nullptr;
    delete st80;
    st80 = nullptr;
    delete st90;
    st90 = nullptr;
    delete st100;
    st100 = nullptr;
    delete st110;
    st110 = nullptr;
    delete st120;
    st120 = nullptr;
    delete st130;
    st130 = nullptr;
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
    connect(st10,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt10_textChanged(QString)));
    connect(st20,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt20_textChanged(QString)));
    connect(st30,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt30_textChanged(QString)));
    connect(st40,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt40_textChanged(QString)));
    connect(st50,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt50_textChanged(QString)));
    connect(st60,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt60_textChanged(QString)));
    connect(st70,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt70_textChanged(QString)));
    connect(st80,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt80_textChanged(QString)));
    connect(st90,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt90_textChanged(QString)));
    connect(st100,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt100_textChanged(QString)));
    connect(st110,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt110_textChanged(QString)));
    connect(st120,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt120_textChanged(QString)));
}

void MainWindow::guiSetup()
{
    // implement here every settings for GUI
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
    //first generete thread instance
    if ( thread1 != nullptr){
        thread1->quit();
        delete thread1;
        thread1 = nullptr;
    }
    thread1 = new QThread;

    if ( thread2 != nullptr){
        thread2->quit();
        delete thread2;
        thread2 = nullptr;
    }
    thread2 = new QThread;

    if ( thread3 != nullptr){
        thread3->quit();
        delete thread3;
        thread3 = nullptr;
    }
    thread3 = new QThread;

    if ( thread4 != nullptr){
        thread4->quit();
        delete thread4;
        thread4 = nullptr;
    }
    thread4 = new QThread;

    //end of genereting thread instance

    //genereting WorkArea class instance for each station on production line

    if ( st10 != nullptr){
        delete st10;
        st10 = nullptr;
    }
    st10 = new WorkArea;
    st10->doSetup(thread1);  // declarate thread for program
    st10->moveToThread(thread1); // declarate thread for program
    st10->name = "St10"; // not important

    if ( st20 != nullptr){
        delete st20;
        st20 = nullptr;
    }
    st20 = new WorkArea;
    st20->doSetup(thread1);
    st20->moveToThread(thread1);
    st20->name = "St20";

    if ( st30 != nullptr){
        delete st30;
        st30 = nullptr;
    }
    st30 = new WorkArea;
    st30->doSetup(thread1);
    st30->moveToThread(thread1);
    st30->name = "St30";

    if ( st40 != nullptr){
        delete st40;
        st40 = nullptr;
    }
    st40 = new WorkArea;
    st40->doSetup(thread2);
    st40->moveToThread(thread2);
    st40->name = "St40";

    if ( st50 != nullptr){
        delete st50;
        st50 = nullptr;
    }
    st50 = new WorkArea;
    st50->doSetup(thread2);
    st50->moveToThread(thread2);
    st50->name = "St50";

    if ( st60 != nullptr){
        delete st60;
        st60 = nullptr;
    }
    st60 = new WorkArea;
    st60->doSetup(thread2);
    st60->moveToThread(thread2);
    st60->name = "St60";

    if ( st70 != nullptr){
        delete st70;
        st70 = nullptr;
    }
    st70 = new WorkArea;
    st70->doSetup(thread3);
    st70->moveToThread(thread3);
    st70->name = "St70";

    if ( st80 != nullptr){
        delete st80;
        st80 = nullptr;
    }
    st80 = new WorkArea;
    st80->doSetup(thread3);
    st80->moveToThread(thread3);
    st80->name = "St80";

    if ( st90 != nullptr){
        delete st90;
        st90 = nullptr;
    }
    st90 = new WorkArea;
    st90->doSetup(thread3);
    st90->moveToThread(thread3);
    st90->name = "St90";

    if ( st100 != nullptr){
        delete st100;
        st100 = nullptr;
    }
    st100 = new WorkArea;
    st100->doSetup(thread4);
    st100->moveToThread(thread4);
    st100->name = "St100";

    if ( st110 != nullptr){
        delete st110;
        st110 = nullptr;
    }
    st110 = new WorkArea;
    st110->doSetup(thread4);
    st110->moveToThread(thread4);
    st110->name = "St110";

    if ( st120 != nullptr){
        delete st120;
        st120 = nullptr;
    }
    st120 = new WorkArea;
    st120->doSetup(thread4);
    st120->moveToThread(thread4);
    st120->name = "St120";

    //start threads
    thread1->start();
    thread2->start();
    thread3->start();
    thread4->start();
}
