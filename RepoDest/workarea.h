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

private:
    QThread* _thread;
    Client* _client;

    QString _name;
    int _repeatThreadTime;

    void repeatThread();

signals:
    bool done();
    void messageText(const QString &);
    void messageOk(int &);
    void messageKo(int &);
    void messageTotal(int &);
    void connectionStatus(bool);


private slots:
    void on_MessageTextChanged(const QString &arg1);
    void labelStatus_Changed(bool arg1);
    void lineEditOk_Changed(int &arg1);
    void lineEditNok_Changed(int &arg1);

public slots:
    void mainOperation();
};

#endif // WORKAREA_H
