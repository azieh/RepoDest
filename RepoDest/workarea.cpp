#include <QDebug>

#include "workarea.h"

WorkArea::WorkArea(QObject *parent) :
    QObject(parent)
{
    i = true;
}

void WorkArea::doSetup(QThread &cThread)
{
    thread = &cThread;
    connect(&cThread,SIGNAL(started()),this,SLOT(startReading()));
}


void WorkArea::startReading()
{
    int j;
    while( i == true ){
        qWarning() << "Thread is working" << j++;
        thread->msleep(100);
    }
}
