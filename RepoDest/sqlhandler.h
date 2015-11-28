#ifndef SQLHANDLER_H
#define SQLHANDLER_H
#include <QObject>
#include <QApplication>
#include <QDebug>
#include <QtSql>

const QDir    DATABASEPATH  ("C:/Baza_przestojow");
const QString DBFILENAME    ("/M1.mdb");

struct SqlDataStruct{    // Struct for SQL data
    QString     stationName;
    QString     date;
    QString     hour;
    QString     reference;
    double      timeElapsed;
    int         faultNumber;
    int         partsInLastMinute;
};

class SqlHandler : public QObject
{
    Q_OBJECT
public:
    explicit SqlHandler( QObject *parent = 0 );
    ~SqlHandler();

    QSqlDatabase* database;
    QSqlQuery* query;

    bool openDatabase();
    bool createTable_Breakes(SqlDataStruct* data);
    bool createTable_PartsInLastMinute(SqlDataStruct* data);
    bool insertValueInTo_Breakes(SqlDataStruct* data);
    bool insertValueInTo_PartsInLastMinute(SqlDataStruct* data);

signals:
    void messageText(const QString &, const QString &);
    void messageOk(const QString &, int );
    void messageKo(const QString &, int );

public slots:
};

#endif // SQLHANDLER_H
