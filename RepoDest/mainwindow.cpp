#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui ( new Ui::MainWindow ),
    tm ( nullptr )

{
    ui->setupUi(this);

    createThreadManager();
    setGuiSetup(); //initial settings for GUI
    setGuiConnection(); //generete and manage connection between GUI and WorkArea stations
    setIconAndConnectionTextStatus(); //set default icon for connection status

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
    ui->labelSt10Ico->setPixmap(_warningIcon);
    ui->labelSt20Ico->setPixmap(_warningIcon);
    ui->labelSt30Ico->setPixmap(_warningIcon);
    ui->labelSt40Ico->setPixmap(_warningIcon);
    ui->labelSt50Ico->setPixmap(_warningIcon);
    ui->labelSt60Ico->setPixmap(_warningIcon);
    ui->labelSt70Ico->setPixmap(_warningIcon);
    ui->labelSt80Ico->setPixmap(_warningIcon);
    ui->labelSt90Ico->setPixmap(_warningIcon);
    ui->labelSt100Ico->setPixmap(_warningIcon);
    ui->labelSt110Ico->setPixmap(_warningIcon);
    ui->labelSt120Ico->setPixmap(_warningIcon);
}

void MainWindow::setGuiConnection()
{
    connect(tm->st10, SIGNAL( messageText(const QString &, const QString &) ), this, SLOT( on_plainTextEdit_textChanged(const QString &, const QString &) ) );
    connect(tm->st10, SIGNAL( connectionStatus(const QString &, bool ) ), this, SLOT( on_labelStatus_Changed(const QString &, bool ) ) );
    connect(tm->st20, SIGNAL( messageText(const QString &, const QString &) ), this, SLOT( on_plainTextEdit_textChanged(const QString &, const QString &) ) );
    connect(tm->st20, SIGNAL( connectionStatus(const QString &, bool ) ), this, SLOT( on_labelStatus_Changed(const QString &, bool ) ) );
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

    _connectedIcon = QPixmap(":/ico/Success.ico");
    _connectedIcon = _connectedIcon.scaled(QSize(25, 25), Qt::KeepAspectRatio);
    _warningIcon = QPixmap(":/ico/Warning.ico");
    _warningIcon = _warningIcon.scaled(QSize(25, 25), Qt::KeepAspectRatio);
}

void MainWindow::on_plainTextEdit_textChanged(const QString &stName, const QString &arg1)
{
    if ( stName == "St10" ){
        ui->plainTextEditSt10->appendPlainText(arg1);
    }
    if ( stName == "St20" ){
        ui->plainTextEditSt20->appendPlainText(arg1);
    }

}
void MainWindow::on_labelStatus_Changed(const QString &stName, bool arg1)
{
    if ( stName == "St10" ){
        if ( arg1 == true ){
            ui->labelSt10Status->setText("Connected");
            ui->labelSt10Ico->setPixmap(_connectedIcon);
        } else {
            ui->labelSt10Status->setText("Dissconected");
            ui->labelSt10Ico->setPixmap(_warningIcon);
        }
    }

    if ( stName == "St20" ){
        if ( arg1 == true ){
            ui->labelSt20Status->setText("Connected");
            ui->labelSt20Ico->setPixmap(_connectedIcon);
        } else {
            ui->labelSt20Status->setText("Dissconected");
            ui->labelSt20Ico->setPixmap(_warningIcon);
        }
    }
}

void MainWindow::on_lineEditOk_Changed(const QString &stName, int &arg1)
{

}

void MainWindow::on_lineEditNok_Changed(const QString &stName, int &arg1)
{

}

void MainWindow::on_lineEditTotal_Changed(const QString &stName, int &arg1)
{

}


