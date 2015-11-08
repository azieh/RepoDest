#include <QDebug>
#include <QTimer>

#include "workarea.h"


WorkArea::WorkArea(QObject *parent) :
    QObject     (parent),
    dbStruct    (nullptr),
    _thread     (nullptr),
    _client     (nullptr)
{
    _repeatThreadTime = 100;

    if ( _client != nullptr ){
        delete _client;
        _client = nullptr;
    }
    _client = new Client;

    if ( dbStruct != nullptr ){
        delete dbStruct;
        dbStruct = nullptr;
    }
    dbStruct = new RepoDestDbStruct;
    if ( dbStruct != nullptr ){
        dbStruct->fault = false;
        dbStruct->fault_ack = false;
        dbStruct->part_ok = false;
        dbStruct->part_ok_ack = false;
        dbStruct->fault_number = 0;
    }
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

    connect(_client, SIGNAL( messageText( const QString & )),   this, SLOT( messageTextChanged( const QString & ) ));
    connect(_client, SIGNAL( connectionStatus( bool )),         this, SLOT( labelStatus_Changed( bool ) ));
    connect(_client, SIGNAL( messageOk( int )),                 this, SLOT( lineEditOk_Changed( int ) ));
    connect(_client, SIGNAL( messageKo( int )),                 this, SLOT( lineEditNok_Changed( int ) ));

}

void WorkArea::initOperation()
{
    loopTimer.start();
//    _client->makeConnect();
//    if ( _client->isConnected == false ){
//        emit messageText( _name, "    I will try once again :)" );
//    }
}
void WorkArea::repeatThread()
{
    emit loopTime ( _name, QString::number( loopTimer.elapsed() ) + " ms");
    QTimer::singleShot(_repeatThreadTime, _thread, SLOT(quit()));
}

void WorkArea::checkDbStruct(RepoDestDbStruct* dbStruct)
{
    if ( dbStruct->fault == true ){
        faultTimer.start();
        _faultNumberMemory = dbStruct->fault_number;
        emit messageText( _name, "Fault on machine number " + QString::number( _faultNumberMemory ) );
        dbStruct->fault = false;
    }
    if ( dbStruct->part_ok == true ){
        _faultTimeElapsedMemory = faultTimer.elapsed();
        emit messageText( _name, "Fault time = " + ( QString::number( _faultTimeElapsedMemory / 60000 ) + " min ") + ( QString::number( ( _faultTimeElapsedMemory % 60000) / 1000 ) + " sec") );
        dbStruct->part_ok = false;
    }
}

void WorkArea::mainOperation()
{
    initOperation();
    _client->testRead( dbStruct );
    checkDbStruct( dbStruct );
    if ( _client->isConnected == true ){
        _client->makeMultiRead( dbStruct );


        _client->makeDisconnect();
    }
    repeatThread();               //method to make loop thread
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
void WorkArea::messageTextChanged(const QString &arg1)
{
    emit messageText(_name, arg1);
}
void WorkArea::labelStatus_Changed(bool arg1)
{
    emit connectionStatus(_name, arg1);
}
void WorkArea::lineEditOk_Changed(int arg1)
{
    emit messageOk(_name, arg1);
}
void WorkArea::lineEditNok_Changed(int arg1)
{
    emit messageKo(_name, arg1);
}
