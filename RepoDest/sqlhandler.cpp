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
            emit messageText( "LogMsg",
                              "Program create dir path for DB file: " +
                              DATABASEPATH.path()
                              );
        } else {
            emit messageText( "LogMsg",
                              "Program has problem with creating path: " +
                              DATABASEPATH.path()
                              );
        }
    }
    if ( database != nullptr ){
        delete database;
        database = nullptr;
    }
    database = new QSqlDatabase( QSqlDatabase::addDatabase("QODBC3") );
    database->setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};"
                              "FIL={MS Access};"
                              "DBQ="+DATABASEPATH.path()+DBFILENAME
                              );
    database->setConnectOptions("SQL_ATTR_ODBC_VERSION=SQL_OV_ODBC3");
    database->setHostName ( "PLC" );


    if (!database->open()){
        emit messageText( "LogMsg",
                          "Cannot open Database " +
                          DATABASEPATH.path() + DBFILENAME +
                          "| Error: " +database->lastError().text()
                          );
    }else {
        emit messageText( "LogMsg",
                          "Database was loaded successfully"
                          );
    }
    return database->isOpen ();
}
//------------------------------------------------------------------------------
// Create table breakes
//------------------------------------------------------------------------------
bool SqlHandler::createTable_Breakes(SqlDataStruct* data)
{
    bool tableExist = false;
    if ( database->isOpen() ){
        QString command;
        tableExist = database->tables().contains( QString( data->stationName + "_PRZESTOJE" ) );
        if ( !tableExist ){
            command = QString("CREATE TABLE %1_PRZESTOJE "
                              "(ID AUTOINCREMENT, Data DATE, Godzina TIME, Referencja TEXT, [Czas przestoju] DOUBLE, [Kod bledu] INTEGER, [Opis bledu] TEXT)"
                              ).arg( data->stationName );

            if ( query != nullptr ){
                delete query;
                query = nullptr;
            }
            query = new QSqlQuery;
            query->prepare( command );

            if ( !query->exec() ){
                emit messageText( "LogMsg",
                                  "SQL error when Table was created for " +
                                  data->stationName + "_PRZESTOJE" ": " +
                                  query->lastError().text()
                                  );
            } else {
                emit messageText( "LogMsg",
                                  "SQL query: Correctly created table for " +
                                  data->stationName + "_PRZESTOJE"
                                  );
                tableExist = true;
            }
            query->clear();
        }
    }
    return tableExist;
}
//------------------------------------------------------------------------------
// Create table parts in last minute
//------------------------------------------------------------------------------
bool SqlHandler::createTable_PartsInLastMinute(SqlDataStruct* data)
{
    bool tableExist = false;
    if ( database->isOpen() ){
        QString command;
        tableExist = database->tables().contains( QString( data->stationName + "_LICZNIK_SZTUK" ) );
        if ( !tableExist ){
            command = QString("CREATE TABLE %1_LICZNIK_SZTUK "
                              "(ID AUTOINCREMENT, Data DATE, Godzina TIME, Referencja TEXT, [Ilosc sztuk] INTEGER)"
                              ).arg( data->stationName );

            if ( query != nullptr ){
                delete query;
                query = nullptr;
            }
            query = new QSqlQuery;
            query->prepare( command );

            if ( !query->exec() ){
                emit messageText( "LogMsg",
                                  "SQL error when Table was created for " +
                                  data->stationName + "_LICZNIK_SZTUK" +
                                  ": " + query->lastError().text()
                                  );
            } else {
                emit messageText( "LogMsg",
                                  "SQL query: Correctly created table for " +
                                  data->stationName + "_LICZNIK_SZTUK"
                                  );
                tableExist = true;
            }
            query->clear();
        }
    }
    return tableExist;
}
//------------------------------------------------------------------------------
// Insert value into breakes
//------------------------------------------------------------------------------
bool SqlHandler::insertValueInTo_Breakes(SqlDataStruct* data)
{   
    bool done = false;

    if ( openDatabase() ){
        if ( createTable_Breakes( data ) ){
            QString command;
            command = QString( "INSERT INTO %1_PRZESTOJE (Data, Godzina, Referencja, [Czas przestoju], [Kod bledu]) "
                               "VALUES ( %2, %3, %4, %5, %6)" )
                    .arg( data->stationName )
                    .arg( "'" + data->date + "'" )
                    .arg( "'" + data->hour + "'" )
                    .arg( "'" + data->reference + "'")
                    .arg( data->timeElapsed )
                    .arg( data->faultNumber );
            if ( query != nullptr ){
                delete query;
                query = nullptr;
            }
            query = new QSqlQuery();
            query->prepare( command );

            if ( !query->exec( ) ){
                emit messageText( "LogMsg",
                                  "SQL error when Insert value for " +
                                  data->stationName + "_PRZESTOJE" +
                                  ": " + query->lastError().text()
                                  );
            } else {
                emit messageText( "LogMsg",
                                  "SQL query: Correctly inserted value for " +
                                  data->stationName + "_PRZESTOJE"
                                  );
                done = true;
            }
            query->clear();
            database->close();
        }
    }
    return done != 0;
}
//------------------------------------------------------------------------------
// Insert value into parts in last minute
//------------------------------------------------------------------------------
bool SqlHandler::insertValueInTo_PartsInLastMinute(SqlDataStruct* data)
{
    bool done = false;

    if ( openDatabase() ){
        if ( createTable_PartsInLastMinute( data ) ){
            QString command;
            command = QString( "INSERT INTO %1_LICZNIK_SZTUK (Data, Godzina, Referencja, [Ilosc sztuk]) "
                               "VALUES ( %2, %3, %4, %5)" )
                    .arg( data->stationName )
                    .arg( "'" + data->date + "'" )
                    .arg( "'" + data->hour + "'" )
                    .arg( "'" + data->reference + "'")
                    .arg( data->partsInLastMinute );
            if ( query != nullptr ){
                delete query;
                query = nullptr;
            }
            query = new QSqlQuery();
            query->prepare( command );

            if ( !query->exec( ) ){
                emit messageText( "LogMsg",
                                  "SQL error when Insert value for " +
                                  data->stationName + "_LICZNIK_SZTUK" +
                                  ": " + query->lastError().text()
                                  );
            } else {
                emit messageText( "LogMsg",
                                  "SQL query: Correctly inserted value for " +
                                  data->stationName + "_LICZNIK_SZTUK"
                                  );
                done = true;
            }
            query->clear();
            database->close();
        }
    }
    return done != 0;
}




