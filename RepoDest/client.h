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


    TS7Client *S7Client;

    byte Buffer[65536]; // 64 K buffer
    int SampleDBNum;// = 1000;

    char *Address;     // PLC IP Address
    int Rack,Slot; // Default Rack and Slot

    int ok;// = 0; // Number of test pass
    int ko;// = 0; // Number of test failure

    bool JobDone;//=false;
    int JobResult;//=0;

    void mainFunction();

private:

    void S7API CliCompletion(void *usrPtr, int opCode, int opResult);
    void SysSleep(longword Delay_ms);
    void Usage();
    bool Check(int Result, const char * function);
    void hexdump(void *mem, unsigned int len);
    void MultiRead();
    void ListBlocks();
    void OrderCode();
    void CpuInfo();
    void CpInfo();
    void UnitStatus();
    void UploadDB0();
    void AsCBUploadDB0();
    void AsEWUploadDB0();
    void AsPOUploadDB0();
    void ReadSzl_0011_0000();
    bool CliConnect();
    void CliDisconnect();
    void PerformTests();
    void Summary();




    //signals:

    //public slots:
};



#endif // CLIENT_H
