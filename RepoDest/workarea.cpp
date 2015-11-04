#include <QDebug>
#include <QTimer>
#include "qapplication.h"
#include "workarea.h"

WorkArea::WorkArea(QObject *parent) :
    QObject(parent)
{
    i = true;
    j = 0;
    timerIsStarted = false;
    qRegisterMetaType<QtMsgType>("QtMsgType");
}

void WorkArea::doSetup(QThread* cThread)
{
    thread = cThread;
    connect(cThread,SIGNAL(started()),this,SLOT(mainOperation()));
    connect(cThread,SIGNAL(finished()), cThread, SLOT(start()));
    qInstallMessageHandler(myMessageOutput);

}
void WorkArea::myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
 outputMessage( type, msg );
}
void WorkArea::outputMessage(QtMsgType type, const QString &msg)
{
 emit sendMessage( type, msg );
}

void WorkArea::mainOperation()
{

    if ( connected == false ){
        makeConnect();
        emit plainText( logText );
    }


    QTimer::singleShot(10000, thread, SLOT(quit()));
}





//    for ( j=0; j<11; ++j){
//        text = name + ": Thread is working   :" +  QString::number(j) + "\n";
//        emit plainText( text );
//        thread->msleep( 100 );
//    }
//    if ( timerIsStarted == true){
//        text = name + ": One cycle time is: " + QString::number(time.elapsed()) + " ms \n";
//        emit plainText ( text );
//        timerIsStarted=false;
//    }
//    if ( timerIsStarted == false ){
//        time.start();
//        timerIsStarted = true;
//    }
