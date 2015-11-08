#include <QApplication>
#include <QDebug>
#include "workarea.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;
    w.showFullScreen();
    w.tm->startThreads();

    a.exec();

    return 0;
}
