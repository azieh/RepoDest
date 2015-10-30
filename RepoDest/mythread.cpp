#include "mythread.h"
#include <QtCore>

MyThread::MyThread(QObject *parent) :
    QThread(parent)
{
go = true;
i = 0;
}

void MyThread::run()
{
 while( go = true ){
    qWarning() << " THREAD IS WORKING "<< ++i;
    //this->msleep(100);
 }
}

