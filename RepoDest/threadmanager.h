#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <QObject>

#include "workarea.h"

class ThreadManager : public QObject
{
    Q_OBJECT
public:
    explicit ThreadManager(QObject *parent = 0);
    ~ThreadManager();

    QThread* thread1;
    QThread* thread2;
    QThread* thread3;
    QThread* thread4;
    WorkArea* st10;
    WorkArea* st20;
    WorkArea* st30;
    WorkArea* st40;
    WorkArea* st50;
    WorkArea* st60;
    WorkArea* st70;
    WorkArea* st80;
    WorkArea* st90;
    WorkArea* st100;
    WorkArea* st110;
    WorkArea* st120;
    WorkArea* st130;

    void createThreads();
    void createClientDeclaration();


signals:

public slots:
    void startThreads();
};

#endif // THREADMANAGER_H
