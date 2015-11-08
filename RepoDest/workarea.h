#ifndef WORKAREA_H
#define WORKAREA_H

#include <QObject>
#include <QThread>
#include <QApplication>
#include <QElapsedTimer>

#include "client.h"


class WorkArea : public QObject
{
    Q_OBJECT
public:
    explicit WorkArea(QObject *parent = 0);
    ~WorkArea();

    void doSetup        (QThread* cThread);
    void setIpAddress   (const char* arg1);
    void setDbNumber    (const int &arg1);
    void setName        (const char* arg1);
    RepoDestDbStruct*    dbStruct;

private:
    QThread* _thread;
    Client* _client;


    QString _name;
    QElapsedTimer loopTimer;
    QElapsedTimer faultTimer;
    int _repeatThreadTime;
    int _faultNumberMemory;
    int _faultTimeElapsedMemory;

    void repeatThread();
    void initOperation();
    void checkDbStruct(RepoDestDbStruct* dbStruct);

signals:
    void messageText(const QString &, const QString &);
    void messageOk(const QString &, int );
    void messageKo(const QString &, int );
    void messageTotal(const QString &, int &);
    void connectionStatus(const QString &, bool);
    void loopTime(const QString &, const QString &);


private slots:
    void messageTextChanged(const QString &arg1);
    void labelStatus_Changed(bool arg1);
    void lineEditOk_Changed(int arg1);
    void lineEditNok_Changed(int arg1);

public slots:
    void mainOperation();
};

#endif // WORKAREA_H
