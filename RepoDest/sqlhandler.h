#ifndef SQLHANDLER_H
#define SQLHANDLER_H
#include <QObject>
#include <QApplication>
#include <QDebug>
#include <QtSql>

const QDir    DATABASEPATH  ("D:/Baza_przestojow");
const QString DBFILENAME    ("M1.sqlite");

struct SqlDataStruct{    // Struct for SQL data
    QString     stationName;
    QString     date;
    QString     hour;
    int         faultNumber;
    double      timeElapsed;
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
    void createTable(SqlDataStruct* data);
    void insertValue(SqlDataStruct* data);

signals:
    void messageText(const QString &, const QString &);
    void messageOk(const QString &, int );
    void messageKo(const QString &, int );

public slots:
};

#endif // SQLHANDLER_H
