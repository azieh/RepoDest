#include "threadmanager.h"

ThreadManager::ThreadManager(QObject *parent) :
    QObject(parent),
    sqlH (nullptr),
    thread1(nullptr),
    thread2(nullptr),
    thread3(nullptr),
    thread4(nullptr),
    st10(nullptr),
    st30(nullptr),
    st40(nullptr),
    st50(nullptr),
    st60(nullptr),
    st70(nullptr),
    st80(nullptr),
    st90(nullptr),
    st100(nullptr),
    st110(nullptr),
    st120(nullptr),
    st130(nullptr)
{

}
ThreadManager::~ThreadManager()
{
    delete sqlH;
    sqlH = nullptr;

    //Quit and clear every thread
    thread1->quit();
    delete thread1;
    thread1 = nullptr;

    thread2->quit();
    delete thread2;
    thread2 = nullptr;

    thread3->quit();
    delete thread3;
    thread3 = nullptr;

    thread4->quit();
    delete thread4;
    thread4 = nullptr;

    //Clear memory about every station instance
    delete st10;
    st10 = nullptr;
    delete st30;
    st30 = nullptr;
    delete st40;
    st40 = nullptr;
    delete st50;
    st50 = nullptr;
    delete st60;
    st60 = nullptr;
    delete st70;
    st70 = nullptr;
    delete st80;
    st80 = nullptr;
    delete st90;
    st90 = nullptr;
    delete st100;
    st100 = nullptr;
    delete st110;
    st110 = nullptr;
    delete st120;
    st120 = nullptr;
    delete st130;
    st130 = nullptr;
}
//------------------------------------------------------------------------------
// Create threads
//------------------------------------------------------------------------------
void ThreadManager::createThreads()
{
    if ( sqlH != nullptr ){
        delete sqlH;
        sqlH = nullptr;
    }
    sqlH = new SqlHandler;

    //first generete thread instance
    if ( thread1 != nullptr){
        thread1->quit();
        delete thread1;
        thread1 = nullptr;
    }
    thread1 = new QThread;

    if ( thread2 != nullptr){
        thread2->quit();
        delete thread2;
        thread2 = nullptr;
    }
    thread2 = new QThread;

    if ( thread3 != nullptr){
        thread3->quit();
        delete thread3;
        thread3 = nullptr;
    }
    thread3 = new QThread;

    if ( thread4 != nullptr){
        thread4->quit();
        delete thread4;
        thread4 = nullptr;
    }
    thread4 = new QThread;
}
//------------------------------------------------------------------------------
// Create client objects and give them settings
//------------------------------------------------------------------------------
void ThreadManager::createClientDeclaration()
{
    //genereting WorkArea class instance for each station on production line

    if ( st10 != nullptr){
        delete st10;
        st10 = nullptr;
    }
    st10 = new WorkArea(sqlH);
    st10->doSetup       ( thread1 );  // declarate thread for program
    st10->moveToThread  ( thread1 ); // declarate thread for program
    st10->setIpAddress  ( "10.10.190.1" );
    st10->setDbNumber   ( 193 );
    st10->setName       ( "St10_St20" );


    if ( st30 != nullptr){
        delete st30;
        st30 = nullptr;
    }
    st30 = new WorkArea(sqlH);
    st30->doSetup       ( thread1 );
    st30->moveToThread  ( thread1 );
    st30->setIpAddress  ( "10.10.190.1" );
    st30->setDbNumber   ( 293 );
    st30->setName       ( "St30" );

    if ( st40 != nullptr){
        delete st40;
        st40 = nullptr;
    }
    st40 = new WorkArea(sqlH);
    st40->doSetup       ( thread1 );
    st40->moveToThread  ( thread1 );
    st40->setIpAddress  ( "10.10.190.1" );
    st40->setDbNumber   ( 393 );
    st40->setName       ( "St40" );

    if ( st50 != nullptr){
        delete st50;
        st50 = nullptr;
    }
    st50 = new WorkArea(sqlH);
    st50->doSetup       ( thread2 );
    st50->moveToThread  ( thread2 );
    st50->setIpAddress  ( "10.10.190.1" );
    st50->setDbNumber   ( 493 );
    st50->setName       ( "St50" );

    if ( st60 != nullptr){
        delete st60;
        st60 = nullptr;
    }
    st60 = new WorkArea(sqlH);
    st60->doSetup       ( thread2 );
    st60->moveToThread  ( thread2 );
    st60->setIpAddress  ( "10.10.190.1" );
    st60->setDbNumber   ( 593 );
    st60->setName       ( "St60" );

    if ( st70 != nullptr){
        delete st70;
        st70 = nullptr;
    }
    st70 = new WorkArea(sqlH);
    st70->doSetup       ( thread2 );
    st70->moveToThread  ( thread2 );
    st70->setIpAddress  ( "10.10.191.1" );
    st70->setDbNumber   ( 193 );
    st70->setName       ( "St70" );

    if ( st80 != nullptr){
        delete st80;
        st80 = nullptr;
    }
    st80 = new WorkArea(sqlH);
    st80->doSetup       ( thread3 );
    st80->moveToThread  ( thread3 );
    st80->setIpAddress  ( "10.10.191.1" );
    st80->setDbNumber   ( 293 );
    st80->setName       ( "St80" );

    if ( st90 != nullptr){
        delete st90;
        st90 = nullptr;
    }
    st90 = new WorkArea(sqlH);
    st90->doSetup       ( thread3 );
    st90->moveToThread  ( thread3 );
    st90->setIpAddress  ( "10.10.191.1" );
    st90->setDbNumber   ( 393 );
    st90->setName       ( "St90" );

    if ( st100 != nullptr){
        delete st100;
        st100 = nullptr;
    }
    st100 = new WorkArea(sqlH);
    st100->doSetup       ( thread3 );
    st100->moveToThread  ( thread3 );
    st100->setIpAddress  ( "10.10.192.1" );
    st100->setDbNumber   ( 193 );
    st100->setName       ( "St100" );

    if ( st110 != nullptr){
        delete st110;
        st110 = nullptr;
    }
    st110 = new WorkArea(sqlH);
    st110->doSetup       ( thread4 );
    st110->moveToThread  ( thread4 );
    st110->setIpAddress  ( "10.10.192.1" );
    st110->setDbNumber   ( 293 );
    st110->setName       ( "St110" );

    if ( st120 != nullptr){
        delete st120;
        st120 = nullptr;
    }
    st120 = new WorkArea(sqlH);
    st120->doSetup       ( thread4 );
    st120->moveToThread  ( thread4 );
    st120->setIpAddress  ( "10.10.192.1" );
    st120->setDbNumber   ( 393 );
    st120->setName       ( "St120" );

    if ( st130 != nullptr){
        delete st130;
        st130 = nullptr;
    }
    st130 = new WorkArea(sqlH);
    st130->doSetup       ( thread4 );
    st130->moveToThread  ( thread4 );
    st130->setIpAddress  ( "10.10.193.1" );
    st130->setDbNumber   ( 193 );
    st130->setName       ( "St130" );
}
//------------------------------------------------------------------------------
// Start threads
//------------------------------------------------------------------------------
void ThreadManager::start()
{
    //start threads
    sqlH->openDatabase();
    thread1->start();
    thread2->start();
    thread3->start();
    thread4->start();
}
