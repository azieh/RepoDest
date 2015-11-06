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
    connect(tm->st10, SIGNAL( messageText( const QString &, const QString & )), this, SLOT( on_plainTextEdit_textChanged( const QString &, const QString & )));
    connect(tm->st10, SIGNAL( messageOk( const QString &, int )),               this, SLOT( on_lineEditOk_Changed( const QString &, int )));
    connect(tm->st10, SIGNAL( messageKo( const QString &, int )),               this, SLOT( on_lineEditNok_Changed( const QString &, int )));
    connect(tm->st10, SIGNAL( connectionStatus( const QString &, bool )),       this, SLOT( on_labelStatus_Changed( const QString &, bool )));
    connect(tm->st10, SIGNAL( loopTime( const QString &, const QString &)),     this, SLOT( on_lineEditTime_Changed( const QString &, const QString &)));

    connect(tm->st20, SIGNAL( messageText( const QString &, const QString & )), this, SLOT( on_plainTextEdit_textChanged( const QString &, const QString & )));
    connect(tm->st20, SIGNAL( messageOk( const QString &, int )),               this, SLOT( on_lineEditOk_Changed( const QString &, int )));
    connect(tm->st20, SIGNAL( messageKo( const QString &, int )),               this, SLOT( on_lineEditNok_Changed( const QString &, int )));
    connect(tm->st20, SIGNAL( connectionStatus( const QString &, bool )),       this, SLOT( on_labelStatus_Changed( const QString &, bool )));
    connect(tm->st20, SIGNAL( loopTime( const QString &, const QString &)),     this, SLOT( on_lineEditTime_Changed( const QString &, const QString &)));

    connect(tm->st30, SIGNAL( messageText( const QString &, const QString & )), this, SLOT( on_plainTextEdit_textChanged( const QString &, const QString & )));
    connect(tm->st30, SIGNAL( messageOk( const QString &, int )),               this, SLOT( on_lineEditOk_Changed( const QString &, int )));
    connect(tm->st30, SIGNAL( messageKo( const QString &, int )),               this, SLOT( on_lineEditNok_Changed( const QString &, int )));
    connect(tm->st30, SIGNAL( connectionStatus( const QString &, bool )),       this, SLOT( on_labelStatus_Changed( const QString &, bool )));
    connect(tm->st30, SIGNAL( loopTime( const QString &, const QString &)),     this, SLOT( on_lineEditTime_Changed( const QString &, const QString &)));

    connect(tm->st40, SIGNAL( messageText( const QString &, const QString & )), this, SLOT( on_plainTextEdit_textChanged( const QString &, const QString & )));
    connect(tm->st40, SIGNAL( messageOk( const QString &, int )),               this, SLOT( on_lineEditOk_Changed( const QString &, int )));
    connect(tm->st40, SIGNAL( messageKo( const QString &, int )),               this, SLOT( on_lineEditNok_Changed( const QString &, int )));
    connect(tm->st40, SIGNAL( connectionStatus( const QString &, bool )),       this, SLOT( on_labelStatus_Changed( const QString &, bool )));
    connect(tm->st40, SIGNAL( loopTime( const QString &, const QString &)),     this, SLOT( on_lineEditTime_Changed( const QString &, const QString &)));

    connect(tm->st50, SIGNAL( messageText( const QString &, const QString & )), this, SLOT( on_plainTextEdit_textChanged( const QString &, const QString & )));
    connect(tm->st50, SIGNAL( messageOk( const QString &, int )),               this, SLOT( on_lineEditOk_Changed( const QString &, int )));
    connect(tm->st50, SIGNAL( messageKo( const QString &, int )),               this, SLOT( on_lineEditNok_Changed( const QString &, int )));
    connect(tm->st50, SIGNAL( connectionStatus( const QString &, bool )),       this, SLOT( on_labelStatus_Changed( const QString &, bool )));
    connect(tm->st50, SIGNAL( loopTime( const QString &, const QString &)),     this, SLOT( on_lineEditTime_Changed( const QString &, const QString &)));

    connect(tm->st60, SIGNAL( messageText( const QString &, const QString & )), this, SLOT( on_plainTextEdit_textChanged( const QString &, const QString & )));
    connect(tm->st60, SIGNAL( messageOk( const QString &, int )),               this, SLOT( on_lineEditOk_Changed( const QString &, int )));
    connect(tm->st60, SIGNAL( messageKo( const QString &, int )),               this, SLOT( on_lineEditNok_Changed( const QString &, int )));
    connect(tm->st60, SIGNAL( connectionStatus( const QString &, bool )),       this, SLOT( on_labelStatus_Changed( const QString &, bool )));
    connect(tm->st60, SIGNAL( loopTime( const QString &, const QString &)),     this, SLOT( on_lineEditTime_Changed( const QString &, const QString &)));

    connect(tm->st70, SIGNAL( messageText( const QString &, const QString & )), this, SLOT( on_plainTextEdit_textChanged( const QString &, const QString & )));
    connect(tm->st70, SIGNAL( messageOk( const QString &, int )),               this, SLOT( on_lineEditOk_Changed( const QString &, int )));
    connect(tm->st70, SIGNAL( messageKo( const QString &, int )),               this, SLOT( on_lineEditNok_Changed( const QString &, int )));
    connect(tm->st70, SIGNAL( connectionStatus( const QString &, bool )),       this, SLOT( on_labelStatus_Changed( const QString &, bool )));
    connect(tm->st70, SIGNAL( loopTime( const QString &, const QString &)),     this, SLOT( on_lineEditTime_Changed( const QString &, const QString &)));

    connect(tm->st80, SIGNAL( messageText( const QString &, const QString & )), this, SLOT( on_plainTextEdit_textChanged( const QString &, const QString & )));
    connect(tm->st80, SIGNAL( messageOk( const QString &, int )),               this, SLOT( on_lineEditOk_Changed( const QString &, int )));
    connect(tm->st80, SIGNAL( messageKo( const QString &, int )),               this, SLOT( on_lineEditNok_Changed( const QString &, int )));
    connect(tm->st80, SIGNAL( connectionStatus( const QString &, bool )),       this, SLOT( on_labelStatus_Changed( const QString &, bool )));
    connect(tm->st80, SIGNAL( loopTime( const QString &, const QString &)),     this, SLOT( on_lineEditTime_Changed( const QString &, const QString &)));

    connect(tm->st90, SIGNAL( messageText( const QString &, const QString & )), this, SLOT( on_plainTextEdit_textChanged( const QString &, const QString & )));
    connect(tm->st90, SIGNAL( messageOk( const QString &, int )),               this, SLOT( on_lineEditOk_Changed( const QString &, int )));
    connect(tm->st90, SIGNAL( messageKo( const QString &, int )),               this, SLOT( on_lineEditNok_Changed( const QString &, int )));
    connect(tm->st90, SIGNAL( connectionStatus( const QString &, bool )),       this, SLOT( on_labelStatus_Changed( const QString &, bool )));
    connect(tm->st90, SIGNAL( loopTime( const QString &, const QString &)),     this, SLOT( on_lineEditTime_Changed( const QString &, const QString &)));

    connect(tm->st100, SIGNAL( messageText( const QString &, const QString & )), this, SLOT( on_plainTextEdit_textChanged( const QString &, const QString & )));
    connect(tm->st100, SIGNAL( messageOk( const QString &, int )),               this, SLOT( on_lineEditOk_Changed( const QString &, int )));
    connect(tm->st100, SIGNAL( messageKo( const QString &, int )),               this, SLOT( on_lineEditNok_Changed( const QString &, int )));
    connect(tm->st100, SIGNAL( connectionStatus( const QString &, bool )),       this, SLOT( on_labelStatus_Changed( const QString &, bool )));
    connect(tm->st100, SIGNAL( loopTime( const QString &, const QString &)),     this, SLOT( on_lineEditTime_Changed( const QString &, const QString &)));

    connect(tm->st110, SIGNAL( messageText( const QString &, const QString & )), this, SLOT( on_plainTextEdit_textChanged( const QString &, const QString & )));
    connect(tm->st110, SIGNAL( messageOk( const QString &, int )),               this, SLOT( on_lineEditOk_Changed( const QString &, int )));
    connect(tm->st110, SIGNAL( messageKo( const QString &, int )),               this, SLOT( on_lineEditNok_Changed( const QString &, int )));
    connect(tm->st110, SIGNAL( connectionStatus( const QString &, bool )),       this, SLOT( on_labelStatus_Changed( const QString &, bool )));
    connect(tm->st110, SIGNAL( loopTime( const QString &, const QString &)),     this, SLOT( on_lineEditTime_Changed( const QString &, const QString &)));

    connect(tm->st120, SIGNAL( messageText( const QString &, const QString & )), this, SLOT( on_plainTextEdit_textChanged( const QString &, const QString & )));
    connect(tm->st120, SIGNAL( messageOk( const QString &, int )),               this, SLOT( on_lineEditOk_Changed( const QString &, int )));
    connect(tm->st120, SIGNAL( messageKo( const QString &, int )),               this, SLOT( on_lineEditNok_Changed( const QString &, int )));
    connect(tm->st120, SIGNAL( connectionStatus( const QString &, bool )),       this, SLOT( on_labelStatus_Changed( const QString &, bool )));
    connect(tm->st120, SIGNAL( loopTime( const QString &, const QString &)),     this, SLOT( on_lineEditTime_Changed( const QString &, const QString &)));
}

void MainWindow::setGuiSetup()
{
    int blockCount = 50; // number of lines in plainText window
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
    if ( stName == "St30" ){
        ui->plainTextEditSt30->appendPlainText(arg1);
    }
    if ( stName == "St40" ){
        ui->plainTextEditSt40->appendPlainText(arg1);
    }
    if ( stName == "St50" ){
        ui->plainTextEditSt50->appendPlainText(arg1);
    }
    if ( stName == "St60" ){
        ui->plainTextEditSt60->appendPlainText(arg1);
    }
    if ( stName == "St70" ){
        ui->plainTextEditSt70->appendPlainText(arg1);
    }
    if ( stName == "St80" ){
        ui->plainTextEditSt80->appendPlainText(arg1);
    }
    if ( stName == "St90" ){
        ui->plainTextEditSt90->appendPlainText(arg1);
    }
    if ( stName == "St100" ){
        ui->plainTextEditSt100->appendPlainText(arg1);
    }
    if ( stName == "St110" ){
        ui->plainTextEditSt110->appendPlainText(arg1);
    }
    if ( stName == "St120" ){
        ui->plainTextEditSt120->appendPlainText(arg1);
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

    if ( stName == "St30" ){
        if ( arg1 == true ){
            ui->labelSt30Status->setText("Connected");
            ui->labelSt30Ico->setPixmap(_connectedIcon);
        } else {
            ui->labelSt30Status->setText("Dissconected");
            ui->labelSt30Ico->setPixmap(_warningIcon);
        }
    }

    if ( stName == "St40" ){
        if ( arg1 == true ){
            ui->labelSt40Status->setText("Connected");
            ui->labelSt40Ico->setPixmap(_connectedIcon);
        } else {
            ui->labelSt40Status->setText("Dissconected");
            ui->labelSt40Ico->setPixmap(_warningIcon);
        }
    }

    if ( stName == "St50" ){
        if ( arg1 == true ){
            ui->labelSt50Status->setText("Connected");
            ui->labelSt50Ico->setPixmap(_connectedIcon);
        } else {
            ui->labelSt50Status->setText("Dissconected");
            ui->labelSt50Ico->setPixmap(_warningIcon);
        }
    }

    if ( stName == "St60" ){
        if ( arg1 == true ){
            ui->labelSt60Status->setText("Connected");
            ui->labelSt60Ico->setPixmap(_connectedIcon);
        } else {
            ui->labelSt60Status->setText("Dissconected");
            ui->labelSt60Ico->setPixmap(_warningIcon);
        }
    }

    if ( stName == "St70" ){
        if ( arg1 == true ){
            ui->labelSt70Status->setText("Connected");
            ui->labelSt70Ico->setPixmap(_connectedIcon);
        } else {
            ui->labelSt70Status->setText("Dissconected");
            ui->labelSt70Ico->setPixmap(_warningIcon);
        }
    }

    if ( stName == "St80" ){
        if ( arg1 == true ){
            ui->labelSt80Status->setText("Connected");
            ui->labelSt80Ico->setPixmap(_connectedIcon);
        } else {
            ui->labelSt80Status->setText("Dissconected");
            ui->labelSt80Ico->setPixmap(_warningIcon);
        }
    }

    if ( stName == "St90" ){
        if ( arg1 == true ){
            ui->labelSt90Status->setText("Connected");
            ui->labelSt90Ico->setPixmap(_connectedIcon);
        } else {
            ui->labelSt90Status->setText("Dissconected");
            ui->labelSt90Ico->setPixmap(_warningIcon);
        }
    }

    if ( stName == "St100" ){
        if ( arg1 == true ){
            ui->labelSt100Status->setText("Connected");
            ui->labelSt100Ico->setPixmap(_connectedIcon);
        } else {
            ui->labelSt100Status->setText("Dissconected");
            ui->labelSt100Ico->setPixmap(_warningIcon);
        }
    }

    if ( stName == "St110" ){
        if ( arg1 == true ){
            ui->labelSt110Status->setText("Connected");
            ui->labelSt110Ico->setPixmap(_connectedIcon);
        } else {
            ui->labelSt110Status->setText("Dissconected");
            ui->labelSt110Ico->setPixmap(_warningIcon);
        }
    }

    if ( stName == "St120" ){
        if ( arg1 == true ){
            ui->labelSt120Status->setText("Connected");
            ui->labelSt120Ico->setPixmap(_connectedIcon);
        } else {
            ui->labelSt120Status->setText("Dissconected");
            ui->labelSt120Ico->setPixmap(_warningIcon);
        }
    }
}

void MainWindow::on_lineEditOk_Changed(const QString &stName, int arg1)
{
    if ( stName == "St10" ){
        ui->lineEditSt10Ok->setText(QString::number(arg1));
    }
    if ( stName == "St20" ){
        ui->lineEditSt20Ok->setText(QString::number(arg1));
    }
    if ( stName == "St30" ){
        ui->lineEditSt30Ok->setText(QString::number(arg1));
    }
    if ( stName == "St40" ){
        ui->lineEditSt40Ok->setText(QString::number(arg1));
    }
    if ( stName == "St50" ){
        ui->lineEditSt50Ok->setText(QString::number(arg1));
    }
    if ( stName == "St60" ){
        ui->lineEditSt60Ok->setText(QString::number(arg1));
    }
    if ( stName == "St70" ){
        ui->lineEditSt70Ok->setText(QString::number(arg1));
    }
    if ( stName == "St80" ){
        ui->lineEditSt80Ok->setText(QString::number(arg1));
    }
    if ( stName == "St90" ){
        ui->lineEditSt90Ok->setText(QString::number(arg1));
    }
    if ( stName == "St100" ){
        ui->lineEditSt100Ok->setText(QString::number(arg1));
    }
    if ( stName == "St110" ){
        ui->lineEditSt110Ok->setText(QString::number(arg1));
    }
    if ( stName == "St120" ){
        ui->lineEditSt120Ok->setText(QString::number(arg1));
    }


}

void MainWindow::on_lineEditNok_Changed(const QString &stName, int arg1)
{
    if ( stName == "St10" ){
        ui->lineEditSt10Nok->setText(QString::number(arg1));
    }
    if ( stName == "St20" ){
        ui->lineEditSt20Nok->setText(QString::number(arg1));
    }
    if ( stName == "St30" ){
        ui->lineEditSt30Nok->setText(QString::number(arg1));
    }
    if ( stName == "St40" ){
        ui->lineEditSt40Nok->setText(QString::number(arg1));
    }
    if ( stName == "St50" ){
        ui->lineEditSt50Nok->setText(QString::number(arg1));
    }
    if ( stName == "St60" ){
        ui->lineEditSt60Nok->setText(QString::number(arg1));
    }
    if ( stName == "St70" ){
        ui->lineEditSt70Nok->setText(QString::number(arg1));
    }
    if ( stName == "St80" ){
        ui->lineEditSt80Nok->setText(QString::number(arg1));
    }
    if ( stName == "St90" ){
        ui->lineEditSt90Nok->setText(QString::number(arg1));
    }
    if ( stName == "St100" ){
        ui->lineEditSt100Nok->setText(QString::number(arg1));
    }
    if ( stName == "St110" ){
        ui->lineEditSt110Nok->setText(QString::number(arg1));
    }
    if ( stName == "St120" ){
        ui->lineEditSt120Nok->setText(QString::number(arg1));
    }
}
void MainWindow::on_lineEditTime_Changed(const QString &stName, const QString &arg1)
{
    if ( stName == "St10" ){
        ui->lineEditSt10Time->setText(arg1);
    }
    if ( stName == "St20" ){
        ui->lineEditSt20Time->setText(arg1);
    }
    if ( stName == "St30" ){
        ui->lineEditSt30Time->setText(arg1);
    }
    if ( stName == "St40" ){
        ui->lineEditSt40Time->setText(arg1);
    }
    if ( stName == "St50" ){
        ui->lineEditSt50Time->setText(arg1);
    }
    if ( stName == "St60" ){
        ui->lineEditSt60Time->setText(arg1);
    }
    if ( stName == "St70" ){
        ui->lineEditSt70Time->setText(arg1);
    }
    if ( stName == "St80" ){
        ui->lineEditSt80Time->setText(arg1);
    }
    if ( stName == "St90" ){
        ui->lineEditSt90Time->setText(arg1);
    }
    if ( stName == "St100" ){
        ui->lineEditSt100Time->setText(arg1);
    }
    if ( stName == "St110" ){
        ui->lineEditSt110Time->setText(arg1);
    }
    if ( stName == "St120" ){
        ui->lineEditSt120Time->setText(arg1);
    }
}

