#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QApplication>

#include "core/snap7.h"


// Default value for
const int PLCRACK  = 0; // Rack and
const int PLCSLOT  = 2; // Slot

struct RepoDestDbStruct{    // Struct of RepoDest DB
    bool    fault;          // DBX0.0
    bool    fault_ack;      // DBX0.1
    bool    part_ok;        // DBX0.2
    bool    part_ok_ack;    // DBX0.3
    int     fault_number;   // DBW2
};

class Client : public QObject, private TS7Client
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    ~Client();

    TS7Client* S7Client;

    bool isConnected;
    bool isDisconnected;

    int ok;// = 0; // Number of test pass
    int ko;// = 0; // Number of test failure

    void setIpAddress(const char* arg1);
    void setDbNumber(const int &arg1);
    bool makeConnect();
    void makeDisconnect();
    bool makeMultiRead(RepoDestDbStruct* dbStruct);
    bool makeMultiWrite(RepoDestDbStruct* dbStruct);

private:

    const char* _address;              // PLC IP Address
    int  _dbNumber;             // Number of RepoDest DB


    bool _check(int result, const char * function);
    void _orderCode();
    void _cpuInfo();
    void _unitStatus();
    void _summary();
    void _checkOkKo();

signals:

    void messageText( const QString & );
    void messageOk( int );
    void messageKo( int );
    void connectionStatus( bool );

};
#endif // CLIENT_H
