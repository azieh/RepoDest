#ifndef CLIENT_H
#define CLIENT_H


#include "core/snap7.h"
#include "client.h"
#include <QApplication>

                        // Default value for
const int PLCRACK  = 0; // Rack and
const int PLCSLOT  = 2; // Slot

class Client : public TS7Client
{
public:
    Client();
    ~Client();


    TS7Client* S7Client;

    const char* address;              // PLC IP Address
    int  dbNumber;             // Number of RepoDest DB
    struct RepoDestDbStruct{    // Struct of RepoDest DB
        bool    fault;          // DBX0.0
        bool    fault_ack;      // DBX0.1
        bool    part_ok;        // DBX0.2
        bool    part_ok_ack;    // DBX0.3
        int     fault_number;   // DBW2
    };
    RepoDestDbStruct* repoDestDbStruct; // RepoDest DB buffer

    int ok;// = 0; // Number of test pass
    int ko;// = 0; // Number of test failure

    void startPlcCommunication();
    bool connect();
    void disconnect();
    void multiRead(int& dbNumber, RepoDestDbStruct& dbStruct);

private:



    bool _check(int result, const char * function);
    void _hexdump(void *mem, unsigned int len);
    void _orderCode();
    void _cpuInfo();
    void _unitStatus();
    void _summary();


    //signals:

    //public slots:
};



#endif // CLIENT_H
