#include <QDebug>
#include <QTimer>

#include "workarea.h"


WorkArea::WorkArea(QObject *parent) :
    QObject(parent),
    _thread (nullptr),
    _client (nullptr)

{
    _repeatThreadTime = 1;

    _client = new Client;

}

WorkArea::~WorkArea()
{
    delete _thread;
    _thread = nullptr;

    delete _client;
    _client = nullptr;
}

void WorkArea::doSetup(QThread* cThread)
{
    if ( _thread != nullptr ){
        delete _thread;
        _thread = nullptr;
    }
    _thread = cThread;
    connect(_thread, SIGNAL( started() ), this, SLOT(mainOperation()));
    connect(_thread, SIGNAL( finished() ), _thread, SLOT(start()));
    connect(_client, SIGNAL( messageText( QString )), this, SLOT( on_MessageTextChanged( QString ) ));
    connect(_client, SIGNAL( connectionStatus( bool )), this, SLOT( labelStatus_Changed( bool ) ));
    connect(_client, SIGNAL( messageOk( int& )), this, SLOT( lineEditOk_Changed( int & ) ));
    connect(_client, SIGNAL( messageKo( int& )), this, SLOT( lineEditNok_Changed( int & ) ));
}
void WorkArea::setIpAddress(const char *arg1)
{
    _client->setIpAddress( arg1 );
}

void WorkArea::setDbNumber(const int &arg1)
{
    _client->setDbNumber( arg1 );
}

void WorkArea::setName(const char *arg1)
{
    _name = arg1;
}

void WorkArea::repeatThread()
{
    QTimer::singleShot(_repeatThreadTime, _thread, SLOT(quit()));
}
void WorkArea::on_MessageTextChanged(const QString &arg1)
{
    emit messageText(_name, arg1);
}
void WorkArea::labelStatus_Changed(bool arg1)
{
    emit connectionStatus(_name, arg1);
}

void WorkArea::lineEditOk_Changed(int &arg1)
{
    emit messageOk(_name, arg1);
}

void WorkArea::lineEditNok_Changed(int &arg1)
{
    emit messageKo(_name, arg1);
}


void WorkArea::mainOperation()
{
    _client->makeConnect();

    repeatThread();
}




//    for ( j=0; j<11; ++j){
//        text = name + ": Thread is working   :" +  QString::number(j) + "\n";
//        emit plainText( text );
//        thread->msleep( 100 );
//    }
//    if ( timerIsStarted == true){
//        text = name + ": One cycle time is: " + QString::number(time.elapsed()) + " ms \n";
//        emit plainText ( text );
//        timerIsStarted=false;
//    }
//    if ( timerIsStarted == false ){
//        time.start();
//        timerIsStarted = true;
//    }
