#include <QApplication>
#include <QDebug>
#include "workarea.h"
#include "mainwindow.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();

    w.tm->start();

    a.exec();

    return 0;
}
