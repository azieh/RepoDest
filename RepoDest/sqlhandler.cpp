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
void SqlHandler::createTable(SqlDataStruct* data)
{
    if ( database->isOpen() ){
        if ( !database->tables().contains( data->stationName )){

            QString command;
            command = QString("create table %1 (id int primary key,"
                              "Date varchar(8), Hour varchar(5), Time_elapsed varchar(20), Fault_nr int)").arg( data->stationName );

            if ( query != nullptr ){
                delete query;
                query = nullptr;
            }
            query = new QSqlQuery;
            query->prepare( command );
            if ( !query->exec() ){
                emit messageText( "LogMsg",  "SQL error when Table was created for " + data->stationName + ": " + query->lastError().text() );
            } else {
                emit messageText( "LogMsg",  "SQL query: Correctly created table for " + data->stationName );
            }
            query->clear();
        }
    }
}
void SqlHandler::insertValue(SqlDataStruct* data)
{
    if ( query != nullptr ){
        delete query;
        query = nullptr;
    }
    query = new QSqlQuery;
}



