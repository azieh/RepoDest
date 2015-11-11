#include "sqlhandler.h"

SqlHandler::SqlHandler() :
    database ( nullptr ),
    query    ( nullptr )
{
    if ( database != nullptr ){
        delete database;
        database = nullptr;
    }
    database = new QSqlDatabase( QSqlDatabase::addDatabase("QSQLITE") );
    database->setHostName ( "localhost" );
    database->setDatabaseName ( DATABASEPATH );

    if (database->isOpen ()){
        database->close ();
    }
    if (!database->open()){
        qWarning() << "Cannot open DB | Error: "
                +database->lastError().text();
    }else {
        qWarning() << "DB was loaded successfully";
    }
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
    if (database->isOpen ()){
        database->close ();
    }
    if (!database->open()){
        qWarning() << "Cannot open DB | Error: "
                +database->lastError().text();
    }else {
        qWarning() << "DB was loaded successfully";
    }
    return database->isOpen ();
}
void SqlHandler::createTable()
{
    if ( !database->tables().contains( name )){
        if ( query != nullptr ){
            delete query;
            query = nullptr;
        }
        QString command;
        command = QString("create table %1 (id int primary key,"
                  "Date varchar(20), Hour varchar(20), Time_elapsed varchar(20), Fault_nr int)").arg( name );

        query = new QSqlQuery;
        query->prepare( command );
        query->exec();
        query->clear();
    }
}
void SqlHandler::insertValue()
{
    if ( query != nullptr ){
        delete query;
        query = nullptr;
    }
    query = new QSqlQuery;
}

bool SqlHandler::executeQuery()
{

}

