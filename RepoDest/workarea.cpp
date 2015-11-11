#include <QDebug>
#include <QTimer>
#include <QMutex>

#include "workarea.h"

QMutex mutex;

WorkArea::WorkArea(SqlHandler* sqlHandler, QObject *parent) :
    QObject     (parent),
    dbStruct    (nullptr),
    _thread     (nullptr),
    _client     (nullptr),
    _sqlHandler (sqlHandler)
{
    _makeWriting            = false;
    _repeatThreadTime       = 0;
    _faultTimeElapsedMemory = 0;
    _faultNumberMemory      = 0;

    dbStruct = new RepoDestDbStruct;
    if ( dbStruct != nullptr ){
        dbStruct->fault         = false;
        dbStruct->fault_ack     = false;
        dbStruct->part_ok       = false;
        dbStruct->part_ok_ack   = false;
        dbStruct->fault_number  = 0;
    }

    sqlDataStruct = new SqlDataStruct;
    if (sqlDataStruct != nullptr ){
        // only intiger value have to be init with 0
        sqlDataStruct->faultNumber = 0;
    }
    _client = new Client;
}
WorkArea::~WorkArea()
{
    delete _thread;
    _thread = nullptr;

    delete _client;
    _client = nullptr;
}
//------------------------------------------------------------------------------
// Do setup for object
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
// Repeat thread
//------------------------------------------------------------------------------
void WorkArea::repeatThread()
{  
    QTimer::singleShot(_repeatThreadTime, _thread, SLOT(quit()));
}
//------------------------------------------------------------------------------
// Check DB structure
//------------------------------------------------------------------------------
void WorkArea::checkDbStruct(RepoDestDbStruct* dbStruct)
{


    if ( dbStruct->fault == true ){
        _faultTimer.start(); // if we have fault on mstation -> start timer
        QDate date;
        date.currentDate();

        sqlDataStruct->date = date.toString("yyMMdd");
        sqlDataStruct->faultNumber = dbStruct->fault_number; // coppy fault number

        emit messageText( _name, "Fault on machine number " + QString::number( sqlDataStruct->faultNumber ) );

        // after read problem data, set ack bit for PLC
        dbStruct->fault = false;
        dbStruct->fault_number = 0;
        dbStruct->fault_ack = true;

        _makeWriting = true;
    }
    if ( dbStruct->part_ok == true ){
        _faultTimeElapsedMemory =  _faultTimer.elapsed(); // if we have first good part after fault, read time since start timer
        _faultTimeElapsedMemoryMinutes =   _faultTimeElapsedMemory / 60000; // coppy time from ms to minute
        _faultTimeElapsedMemorySeconds = ( _faultTimeElapsedMemory % 60000 ) / 1000; // coppy time from ms to seconds
        _faultTimeElapsedMemoryD = (double)_faultTimeElapsedMemoryMinutes + ( (double)_faultTimeElapsedMemorySeconds / 100 );

        emit messageText( _name, "Fault time = " + ( QString::number( _faultTimeElapsedMemoryMinutes) + " min ") + ( QString::number ( _faultTimeElapsedMemorySeconds ) + " sec") );

        // after read ok product data, set ack bit for PLC
        dbStruct->part_ok = false;
        dbStruct->part_ok_ack = true;

        _makeWriting = true;
    }

}
//------------------------------------------------------------------------------
// PLC work area
//------------------------------------------------------------------------------
void WorkArea::plcArea()
{
    QDate date;
    date.currentDate();

    sqlDataStruct->date = date.toString("yyMMdd");
    if ( _client->makeConnect() == true ){                      // check connection
        if          ( _makeWriting == false ){                  // check statement to Read or Write data
            if ( _client->makeMultiRead ( dbStruct ) == true ){ // read data from PLC and coppy them to dbStruct
                checkDbStruct( dbStruct );                      // check condition of already read data
            }
        }else if    ( _makeWriting == true ){
            if ( _client->makeMultiWrite ( dbStruct ) == true ){
                _makeWriting = false;
            }
        }
        _client->makeDisconnect();                              // disconnect after every work
    }
}
void WorkArea::prepareSqlData()
{



}

//------------------------------------------------------------------------------
// Main work area
//------------------------------------------------------------------------------
void WorkArea::mainOperation()
{
    _loopTimer.start(); // start one loop timer

    plcArea();

    if ( _faultTimeElapsedMemoryD != 0 ){
         prepareSqlData();
    }

    mutex.lock();
    sqlDataStruct->stationName = _name;
    _sqlHandler->createTable(sqlDataStruct);
    mutex.unlock();

    emit loopTime ( _name, QString::number( _loopTimer.elapsed() ) + " ms"); // read elapsed time of one loop timer
    repeatThread();                                                         //method to make loop thread
}
//------------------------------------------------------------------------------
// Signals and slot area
//------------------------------------------------------------------------------
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
