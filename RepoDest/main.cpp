#include "mainwindow.h"
#include "client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    Client st10;
//    st10.address="192.168.1.1";
//    st10.dbNumber=999;
//    st10.startPlcCommunication();

    return a.exec();
}
