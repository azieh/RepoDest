#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui ( new Ui::MainWindow ),
    tm ( nullptr )

{
    ui->setupUi(this);

    createThreadManager();
    setIconAndConnectionTextStatus(); //set default icon for connection status
    setGuiSetup(); //initial settings for GUI
    setGuiConnection(); //generete and manage connection between GUI and WorkArea stations

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createThreadManager()
{
    if ( tm != nullptr ){
        delete tm;
        tm = nullptr;
    }
    tm = new ThreadManager;
    tm->createThreads();
    tm->createClientDeclaration();
    tm->startThreads();
}

void MainWindow::setIconAndConnectionTextStatus()
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

void MainWindow::setGuiConnection()
{
    connect(tm->st10,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt10_textChanged(QString)));
    //    connect(tm->st20,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt20_textChanged(QString)));
    //    connect(tm->st30,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt30_textChanged(QString)));
    //    connect(tm->st40,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt40_textChanged(QString)));
    //    connect(tm->st50,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt50_textChanged(QString)));
    //    connect(tm->st60,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt60_textChanged(QString)));
    //    connect(tm->st70,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt70_textChanged(QString)));
    //    connect(tm->st80,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt80_textChanged(QString)));
    //    connect(tm->st90,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt90_textChanged(QString)));
    //    connect(tm->st100,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt100_textChanged(QString)));
    //    connect(tm->st110,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt110_textChanged(QString)));
    //    connect(tm->st120,SIGNAL(plainText(QString)),this,SLOT(on_plainTextEditSt120_textChanged(QString)));
}

void MainWindow::setGuiSetup()
{
    int blockCount = 10; // number of lines in plainText window
    // implement here every settings for GUI


    ui->plainTextEditSt10->setMaximumBlockCount(blockCount);
    ui->plainTextEditSt20->setMaximumBlockCount(blockCount);
    ui->plainTextEditSt30->setMaximumBlockCount(blockCount);
    ui->plainTextEditSt40->setMaximumBlockCount(blockCount);
    ui->plainTextEditSt50->setMaximumBlockCount(blockCount);
    ui->plainTextEditSt60->setMaximumBlockCount(blockCount);
    ui->plainTextEditSt70->setMaximumBlockCount(blockCount);
    ui->plainTextEditSt80->setMaximumBlockCount(blockCount);
    ui->plainTextEditSt90->setMaximumBlockCount(blockCount);
    ui->plainTextEditSt100->setMaximumBlockCount(blockCount);
    ui->plainTextEditSt110->setMaximumBlockCount(blockCount);
    ui->plainTextEditSt120->setMaximumBlockCount(blockCount);
}

void MainWindow::outputMessage(QtMsgType type, const QString &msg)
{
    switch (type) {
    case QtDebugMsg:
        ui->plainTextEditSt10->appendPlainText(msg);
        break;

    case QtWarningMsg:
        ui->plainTextEditSt10->appendPlainText(tr("— WARNING: %1").arg(msg));
        break;

    case QtCriticalMsg:
        ui->plainTextEditSt10->appendPlainText(tr("— CRITICAL: %1").arg(msg));
        break;

    case QtFatalMsg:
        ui->plainTextEditSt10->appendPlainText(tr("— FATAL: %1").arg(msg));
        break;
    }
}

void MainWindow::on_lineEditTotal_textChanged(const QString &arg1)
{
    ui->lineEditTotal->setText(arg1);

}
void MainWindow::on_plainTextEditSt10_textChanged(const QString &arg1)
{
    ui->plainTextEditSt10->insertPlainText(arg1);
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


