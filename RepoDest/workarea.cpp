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
    for ( j=0; j<5; ++j){
        qWarning()<< name << "Thread is working" << j;
        text = name + QString::number(j) + "/n";
        emit plainText(text);
    }
    QTimer::singleShot(100, thread, SLOT(quit()));
}
