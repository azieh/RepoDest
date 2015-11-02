#include <QDebug>
#include <QTimer>
#include "workarea.h"

WorkArea::WorkArea(QObject *parent) :
    QObject(parent)
{
    i = true;
    j = 0;

}

void WorkArea::doSetup(QThread &cThread)
{
    thread = &cThread;
    connect(&cThread,SIGNAL(started()),this,SLOT(startReading()));
    connect(&cThread,SIGNAL(finished()), &cThread, SLOT(start()));
}


void WorkArea::startReading()
{
    for ( j=0; j<11; ++j){
        text = name + ": Thread is working   :" +  QString::number(j);
        emit plainText(text);
        thread->msleep(100);
    }
    QTimer::singleShot(100, thread, SLOT(quit()));
}
