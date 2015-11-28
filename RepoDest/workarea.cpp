#include <QDebug>
#include <QTimer>
#include <QMutex>

#include "workarea.h"

QMutex mutex;

WorkArea::WorkArea(SqlHandler* sqlHandler, QObject *parent) :
    QObject     (parent),
    dbStruct    (nullptr),
    _thread     (nullptr),
    _plcHandler  (nullptr),
    _sqlHandler (sqlHandler)
{
    _faultIsDetected        = false;
    _makeWritingPlc         = true;
    _makeWritingSql         = false;
    _repeatThreadTime       = 500;

    dbStruct = new RepoDestDbStruct;
    if ( dbStruct != nullptr ){
        dbStruct->fault         = false;
        dbStruct->fault_ack     = false;
        dbStruct->part_ok       = false;
        dbStruct->part_ok_ack   = false;
        dbStruct->fault_number  = 0;
        dbStruct->partsInLastMinute = 0;
    }

    sqlDataStruct = new SqlDataStruct;
    if (sqlDataStruct != nullptr ){
        // only intiger value have to be init with 0
        sqlDataStruct->faultNumber = 0;
        sqlDataStruct->timeElapsed = 0.0;
        sqlDataStruct->partsInLastMinute = 0;
    }
    _plcHandler = new PlcHandler;
}
WorkArea::~WorkArea()
{
    delete _thread;
    _thread = nullptr;

    delete _plcHandler;
    _plcHandler = nullptr;
}
//------------------------------------------------------------------------------
// Main work area
//------------------------------------------------------------------------------
void WorkArea::mainOperation()
{
    checkLoopTime();
    _date = _date.currentDate();
    _time = _time.currentTime();

    if ( _makeWritingPlc ) _makeWritingPlc = _plcHandler->makeMultiWrite( dbStruct );

    else {
        _plcHandler->makeMultiRead( dbStruct );
        checkDbStruct( dbStruct );
    }
    repeatThread();                                                         //method to make loop thread
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

    connect(_plcHandler, SIGNAL( messageText( const QString & )),   this, SLOT( messageTextChanged( const QString & ) ));
    connect(_plcHandler, SIGNAL( connectionStatus( bool )),         this, SLOT( labelStatus_Changed( bool ) ));
    connect(_plcHandler, SIGNAL( messageOk( int )),                 this, SLOT( lineEditOk_Changed( int ) ));
    connect(_plcHandler, SIGNAL( messageKo( int )),                 this, SLOT( lineEditNok_Changed( int ) ));

}
//------------------------------------------------------------------------------
// Repeat thread
//------------------------------------------------------------------------------
void WorkArea::repeatThread()
{
    QTimer::singleShot(_repeatThreadTime, _thread, SLOT(quit()));
}
//------------------------------------------------------------------------------
// Check loop time
//------------------------------------------------------------------------------
void WorkArea::checkLoopTime()
{
    if ( _loopTimer.isValid() ){
        emit loopTime ( _name, QString::number( _loopTimer.elapsed() ) + "ms"); // read elapsed time of one loop timer
    }
    _loopTimer.start(); // start one loop timer
}
//------------------------------------------------------------------------------
// SQL handler call for insert data into Parts in last minute
//------------------------------------------------------------------------------
void WorkArea::sqlHInsertDataPartsInLastMinute()
{
    mutex.lock();                              // need to lock this part of code | program can have only one connection to database in one time
    _sqlHandler->insertValueInTo_PartsInLastMinute( sqlDataStruct );
    mutex.unlock();
}
//------------------------------------------------------------------------------
// SQL handler call for insert data into Last fault information
//------------------------------------------------------------------------------
void WorkArea::sqlHInsertDataLastFaultInfo()
{
    mutex.lock();                              // need to lock this part of code | program can have only one connection to database in one time
    _sqlHandler->insertValueInTo_Breakes( sqlDataStruct );
    mutex.unlock();
}
//------------------------------------------------------------------------------
// Check DB structure
//------------------------------------------------------------------------------
void WorkArea::checkDbStruct(RepoDestDbStruct* dbStruct)
{
    checkDbForFault             ( dbStruct );
    checkDbForPartOk            ( dbStruct );
    checkDbForPartsInLastMinute ( dbStruct );
}
//------------------------------------------------------------------------------
// Signals and slot area
//------------------------------------------------------------------------------
void WorkArea::checkDbForFault( RepoDestDbStruct* dbStruct )
{
    if ( dbStruct->fault == true  && _faultIsDetected == false ){
        _faultTimer.start(); // if we have fault on mstation -> start timer

        sqlDataStruct->stationName  = _name;
        sqlDataStruct->date         = _date.toString("yy-MM-dd");   // get current date of fault
        sqlDataStruct->hour         = _time.toString("hh:mm");      // get current time of fault
        sqlDataStruct->faultNumber  = dbStruct->fault_number;       // coppy fault number
        sqlDataStruct->reference    = dbStruct->reference;          // coppy reference number

        emit messageText( _name,
                          "Fault on machine number " +
                          QString::number( sqlDataStruct->faultNumber )
                          );
        emit messageText( _name,
                          "On reference: " +
                          sqlDataStruct->reference
                          );

        // after read problem data, set ack bit for PLC
        dbStruct->fault         = false;
        dbStruct->fault_ack     = true;
        dbStruct->part_ok       = false;
        dbStruct->part_ok_ack   = false;
        dbStruct->fault_number  = 0;

        _faultIsDetected        = true;
        _makeWritingPlc         = true;

    }
}
//------------------------------------------------------------------------------
// Signals and slot area
//------------------------------------------------------------------------------
void WorkArea::checkDbForPartOk( RepoDestDbStruct* dbStruct )
{
    if ( _faultIsDetected == true && dbStruct->part_ok == true ){

        int _faultTimeElapsedMemory         =  _faultTimer.elapsed(); // if we have first good part after fault, read time since start timer

        /* IF WE WANT RESULT IN mm:ss we need to start this part of code */
//        int _faultTimeElapsedMemoryMinutes  =   _faultTimeElapsedMemory / 60000; // coppy time from ms to minute
//        int _faultTimeElapsedMemorySeconds  = ( _faultTimeElapsedMemory % 60000 ) / 1000; // coppy time from ms to seconds
//        // change prepared time value to double in format [min.ss]
//        sqlDataStruct->timeElapsed          = (double)_faultTimeElapsedMemoryMinutes + ( (double)_faultTimeElapsedMemorySeconds / 100.0 );
//        emit messageText( _name, "Fault time = " + ( QString::number( _faultTimeElapsedMemoryMinutes) + " min ") + ( QString::number ( _faultTimeElapsedMemorySeconds ) + " sec") );

        /* IF WE WANT RESULT IN seconds we need to start this part of code */
        int _faultTimeElapsedMemorySeconds  = ( _faultTimeElapsedMemory ) / 1000; // coppy time from ms to seconds
        // change prepared time value to double in format [ss.ms] but we use just seconds format in that moment
        sqlDataStruct->timeElapsed          =  (double)_faultTimeElapsedMemorySeconds;
        emit messageText( _name, "Fault time = " + ( QString::number ( _faultTimeElapsedMemorySeconds ) + " sec") );

        // after read ok product data, set ack bit for PLC
        dbStruct->fault         = false;
        dbStruct->fault_ack     = false;
        dbStruct->part_ok       = false;
        dbStruct->part_ok_ack   = true;
        dbStruct->fault_number  = 0;


        _makeWritingPlc  = true;

        sqlHInsertDataLastFaultInfo();

        _faultIsDetected = false;
    }
}
//------------------------------------------------------------------------------
// Signals and slot area
//------------------------------------------------------------------------------
void WorkArea::checkDbForPartsInLastMinute(RepoDestDbStruct* dbStruct)
{
    if ( _prepareDataForPartsInLastMinute == false ){
        if ( _time.second() == 0) _prepareDataForPartsInLastMinute = true;
    }
    if ( _prepareDataForPartsInLastMinute && _time.second() != 0 ){
        sqlDataStruct->stationName          = _name;
        sqlDataStruct->date                 = _date.toString("yy-MM-dd"); // get current date of fault
        sqlDataStruct->hour                 = _time.toString("hh:mm"); // get current time of fault
        sqlDataStruct->reference            = dbStruct->reference;    // coppy reference number
        sqlDataStruct->partsInLastMinute    = dbStruct->partsInLastMinute;

        dbStruct->partsInLastMinute = 0;

        _makeWritingPlc = true;

        sqlHInsertDataPartsInLastMinute();

        _prepareDataForPartsInLastMinute = false;
    }
}
//------------------------------------------------------------------------------
// Signals and slot area
//------------------------------------------------------------------------------
void WorkArea::setIpAddress(const char *arg1)
{
    _plcHandler->setIpAddress( arg1 );
}
void WorkArea::setDbNumber(const int &arg1)
{
    _plcHandler->setDbNumber( arg1 );
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
