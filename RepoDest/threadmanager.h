#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <QObject>

#include "workarea.h"
#include "sqlhandler.h"

struct settingsStruct {
    QByteArray ipAddress;
    int dbNumber;
    QByteArray stationName;
};


class ThreadManager : public QObject
{
    Q_OBJECT
public:
    explicit ThreadManager(QObject *parent = 0);
    ~ThreadManager();
    SqlHandler* sqlH;
    QThread* thread1;
    WorkArea* st10;
    QSettings* settings;

    QList<settingsStruct> settingsList;

    void createThreads();
    void createClientDeclaration();
    void loadSettings();

private:

    QDir    _apuDbPath;
    QString _apuDbName;
    QDir    _pcsDbPath;
    QString _pcsDbName;

signals:

public slots:
    void start();
};

#endif // THREADMANAGER_H
