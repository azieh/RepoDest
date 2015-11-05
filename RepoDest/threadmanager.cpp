#include "threadmanager.h"

ThreadManager::ThreadManager(QObject *parent) :
    QObject(parent),
    thread1(nullptr),
    thread2(nullptr),
    thread3(nullptr),
    thread4(nullptr),
    st10(nullptr),
    st20(nullptr),
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
    delete st20;
    st20 = nullptr;
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

void ThreadManager::createThreads()
{
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

void ThreadManager::createClientDeclaration()
{
    //genereting WorkArea class instance for each station on production line

    if ( st10 != nullptr){
        delete st10;
        st10 = nullptr;
    }
    st10 = new WorkArea;
    st10->doSetup       ( thread1 );  // declarate thread for program
    st10->moveToThread  ( thread1 ); // declarate thread for program
    st10->setIpAddress  ( "192.168.10.20" );
    st10->setDbNumber   ( 998 );
    st10->setName       ( "St10" ); // not important

    if ( st20 != nullptr){
        delete st20;
        st20 = nullptr;
    }
    st20 = new WorkArea;
    st20->doSetup       ( thread1 );
    st20->moveToThread  ( thread1 );
    st20->setIpAddress  ( "192.168.10.10" );
    st20->setName       ( "St20" );

//    if ( st30 != nullptr){
//        delete st30;
//        st30 = nullptr;
//    }
//    st30 = new WorkArea;
//    st30->doSetup(thread1);
//    st30->moveToThread(thread1);
//    st30->name = "St30";

//    if ( st40 != nullptr){
//        delete st40;
//        st40 = nullptr;
//    }
//    st40 = new WorkArea;
//    st40->doSetup(thread2);
//    st40->moveToThread(thread2);
//    st40->name = "St40";

//    if ( st50 != nullptr){
//        delete st50;
//        st50 = nullptr;
//    }
//    st50 = new WorkArea;
//    st50->doSetup(thread2);
//    st50->moveToThread(thread2);
//    st50->name = "St50";

//    if ( st60 != nullptr){
//        delete st60;
//        st60 = nullptr;
//    }
//    st60 = new WorkArea;
//    st60->doSetup(thread2);
//    st60->moveToThread(thread2);
//    st60->name = "St60";

//    if ( st70 != nullptr){
//        delete st70;
//        st70 = nullptr;
//    }
//    st70 = new WorkArea;
//    st70->doSetup(thread3);
//    st70->moveToThread(thread3);
//    st70->name = "St70";

//    if ( st80 != nullptr){
//        delete st80;
//        st80 = nullptr;
//    }
//    st80 = new WorkArea;
//    st80->doSetup(thread3);
//    st80->moveToThread(thread3);
//    st80->name = "St80";

//    if ( st90 != nullptr){
//        delete st90;
//        st90 = nullptr;
//    }
//    st90 = new WorkArea;
//    st90->doSetup(thread3);
//    st90->moveToThread(thread3);
//    st90->name = "St90";

//    if ( st100 != nullptr){
//        delete st100;
//        st100 = nullptr;
//    }
//    st100 = new WorkArea;
//    st100->doSetup(thread4);
//    st100->moveToThread(thread4);
//    st100->name = "St100";

//    if ( st110 != nullptr){
//        delete st110;
//        st110 = nullptr;
//    }
//    st110 = new WorkArea;
//    st110->doSetup(thread4);
//    st110->moveToThread(thread4);
//    st110->name = "St110";

//    if ( st120 != nullptr){
//        delete st120;
//        st120 = nullptr;
//    }
//    st120 = new WorkArea;
//    st120->doSetup(thread4);
//    st120->moveToThread(thread4);
//    st120->name = "St120";
}

void ThreadManager::startThreads()
{
    //start threads
    thread1->start();
//    thread2->start();
//    thread3->start();
//    thread4->start();
}
