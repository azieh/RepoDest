#include <QApplication>

#include "mainwindow.h"
#include "client.h"
#include "crossclass.h"


void workArea(MainWindow* w)
{

    w->on_lineEditTotal_textChanged("100");

    Client st10;
    st10.address="192.168.1.1";
    st10.dbNumber=999;
    st10.startPlcCommunication();

}

