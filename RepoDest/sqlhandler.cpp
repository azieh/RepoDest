#include "sqlhandler.h"

SqlHandler::SqlHandler(QObject *parent) :
    QObject     (parent),
    database ( nullptr ),
    query    ( nullptr )
{
}
SqlHandler::~SqlHandler()
{
    database->close();
    delete database;
    database = nullptr;

    delete query;
    query = nullptr;
}
//------------------------------------------------------------------------------
// Open database
//------------------------------------------------------------------------------
bool SqlHandler::openDatabase()
{
    if ( !DATABASEPATH.exists() ){
        if ( DATABASEPATH.mkpath(".") ){
            emit messageText( "LogMsg", "Program create dir path for DB file: " + DATABASEPATH.path() );
        } else {
            emit messageText( "LogMsg", "Program has problem with creating path: " + DATABASEPATH.path() );
        }
    }
    if ( database != nullptr ){
        delete database;
        database = nullptr;
    }
    database = new QSqlDatabase( QSqlDatabase::addDatabase("QSQLITE") );
    database->setHostName ( "localhost" );
    database->setDatabaseName ( DATABASEPATH.path()+ "/" + DBFILENAME );

    if (database->isOpen ()){
        database->close ();
    }
    if (!database->open()){
        emit messageText( "LogMsg", "Cannot open Database | Error: " +database->lastError().text() );
    }else {
        emit messageText( "LogMsg",  "Database was loaded successfully" );
    }
    return database->isOpen ();
}
//------------------------------------------------------------------------------
// Create table
//------------------------------------------------------------------------------
void SqlHandler::createTable(SqlDataStruct* data)
{
    if ( database->isOpen() ){
        if ( !database->tables().contains( data->stationName )){

            QString command;
            command = QString("create table %1 ("
                              "Date date, Hour time, Time_in_fault double, Fault_number int)").arg( data->stationName );

            if ( query != nullptr ){
                delete query;
                query = nullptr;
            }
            query = new QSqlQuery;
            query->prepare( command );
            if ( !query->exec() ){
                emit messageText( "LogMsg",  "SQL error when Table was created for " + data->stationName + ": " + query->lastError().text() );
            } else {
                data->stationName.clear();
                data->date.clear();
                data->hour.clear();
                data->timeElapsed = 0.0;
                data->faultNumber = 0;

                emit messageText( "LogMsg",  "SQL query: Correctly created table for " + data->stationName );
            }
            query->clear();
        }
    }
}
//------------------------------------------------------------------------------
// Insert value
//------------------------------------------------------------------------------
void SqlHandler::insertValue(SqlDataStruct* data)
{
    if ( database->isOpen() ){
        if ( query != nullptr ){
            delete query;
            query = nullptr;
        }
        query = new QSqlQuery;
        QString command = QString( "INSERT INTO %1 (Date, Hour, Time_in_fault, Fault_number) "
                                   "VALUES ( %2, %3, %4, %5)" )
                .arg( data->stationName )
                .arg( "'" + data->date + "'" )
                .arg( "'" + data->hour + "'")
                .arg( data->timeElapsed )
                .arg( data->faultNumber );

        if ( !query->exec( command ) ){
            emit messageText( data->stationName,  "SQL error when Insert value for " + data->stationName + ": " + query->lastError().text() );
        } else {
            emit messageText( data->stationName,  "SQL query: Correctly inserted" );
        }
        query->clear();
    }
}



