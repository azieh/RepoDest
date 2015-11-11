#ifndef SQLHANDLER_H
#define SQLHANDLER_H
#include <QDebug>
#include <QtSql>

const QString DATABASEPATH = "D:/Baza_przestojow/M1.sqlite";

class SqlHandler
{
public:
    SqlHandler();
    ~SqlHandler();

    QSqlDatabase* database;
    QSqlQuery* query;

    bool openDatabase();
    bool executeQuery();
    void createTable();
    void insertValue();
    QString name;

    QString actualstatus;

signals:

public slots:
};

#endif // SQLHANDLER_H
