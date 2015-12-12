#include <QApplication>
#include <QMessageBox>
#include <QSharedMemory>
#include "workarea.h"
#include "mainwindow.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Adrian Wasielewski");
    QCoreApplication::setApplicationName("Raportowanie przestojów");


    QSharedMemory shared("62d60669-bb94-4a94-88bb-b964890a7e04");   //Creating shared memory to every single application

    if( !shared.create( 512, QSharedMemory::ReadWrite) )
    {
        //in case we have already one shared memory like above we should exit next app
        QMessageBox msgBox;
        msgBox.setText( QObject::tr( "Program został już uruchomiony. "
                                     "Sprawdź pasek zadań. Jeżeli problem występuje nadal sprawdź "
                                     "Menadżer zadań i zamknij proces RepoDest "));
        msgBox.setIcon( QMessageBox::Critical );
        msgBox.exec();
        exit(0);
    }

    MainWindow w;

    w.tm->start(); // start of main threads

    a.setQuitOnLastWindowClosed(false); // option to check what window was closed
    a.exec();


    return a.exec();
}
