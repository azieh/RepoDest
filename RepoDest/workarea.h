#ifndef WORKAREA_H
#define WORKAREA_H

#include <QObject>
#include <QThread>
#include <QElapsedTimer>

#include "client.h"


class WorkArea : public QObject, public Client
{
    Q_OBJECT
public:
    explicit WorkArea(QObject *parent = 0);
    void doSetup(QThread* cThread);
    bool i;
    bool timerIsStarted;
    int j;
    QString name;
    QString text;
    QElapsedTimer time;
    void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

private:
    QThread* thread;

signals:
    bool done();
    void plainText(const QString &);
    void sendMessage( QtMsgType type, const QString &msg );

public slots:
    void mainOperation();
    void outputMessage( QtMsgType type, const QString &msg );
};

#endif // WORKAREA_H
