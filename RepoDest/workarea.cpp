#include <QDebug>
#include <QTimer>
#include "workarea.h"

WorkArea::WorkArea(QObject *parent) :
    QObject(parent)
{
    i = true;
    j = 0;
    timerIsStarted = false;
}

void WorkArea::doSetup(QThread* cThread)
{
    thread = cThread;
    connect(cThread,SIGNAL(started()),this,SLOT(startReading()));
    connect(cThread,SIGNAL(finished()), cThread, SLOT(start()));
}


void WorkArea::startReading()
{
    for ( j=0; j<11; ++j){
        text = name + ": Thread is working   :" +  QString::number(j);
        emit plainText( text );
        thread->msleep( 1000 );
    }
    if ( timerIsStarted == true){
        text = name + ": One cycle time is: " + QString::number(time.elapsed()) + " ms";
        emit plainText ( text );
        timerIsStarted=false;
    }
    if ( timerIsStarted == false ){
        time.start();
        timerIsStarted = true;
    }


    QTimer::singleShot(100, thread, SLOT(quit()));
}
