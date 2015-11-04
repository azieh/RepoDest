#ifndef CLIENT_H
#define CLIENT_H

#include <QApplication>

#include "core/snap7.h"


// Default value for
const int PLCRACK  = 0; // Rack and
const int PLCSLOT  = 2; // Slot

class Client : private TS7Client
{
public:
    Client();
    ~Client();


    TS7Client* S7Client;


    struct RepoDestDbStruct{    // Struct of RepoDest DB
        bool    fault;          // DBX0.0
        bool    fault_ack;      // DBX0.1
        bool    part_ok;        // DBX0.2
        bool    part_ok_ack;    // DBX0.3
        int     fault_number;   // DBW2
    };
    RepoDestDbStruct* repoDestDbStruct; // RepoDest DB buffer

    bool connected;
    int ok;// = 0; // Number of test pass
    int ko;// = 0; // Number of test failure
    QString logText;

    void setIpAddress(const char* arg1);
    void setDbNumber(const int &arg1);
    bool makeConnect();
    void makeDisconnect();
    void makeMultiRead(int& dbNumber, RepoDestDbStruct& dbStruct);
    void startPlcCommunication();

private:

    const char* _address;              // PLC IP Address
    int  _dbNumber;             // Number of RepoDest DB


    bool _check(int result, const char * function);
    void _hexdump(void *mem, unsigned int len);
    void _orderCode();
    void _cpuInfo();
    void _unitStatus();
    void _summary();


};



#endif // CLIENT_H
