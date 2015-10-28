#ifndef CLIENT_H
#define CLIENT_H


#include "core/snap7.h"
#include "client.h"
#include <QApplication>



class Client : public TS7Client
{
public:
    Client();
    ~Client();


    TS7Client* S7Client;

    int DBNum;// default value = 1050;
    char *Address;     // PLC IP Address
    int Rack,Slot; // Default Rack and Slot

    void mainFunction();
    bool cliConnect();
    void cliDisconnect();
    void multiRead();

    struct CommunicationStruct
    {
        bool    fault;
        bool    fault_ack;
        bool    part_ok;
        bool    part_ok_ack;
        int     fault_nr;
    };

private:

    int _ok;// = 0; // Number of test pass
    int _ko;// = 0; // Number of test failure

//    bool _jobdone;//=false;
//    int _jobresult;//=0;


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
