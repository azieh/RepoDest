/*|============================================================================|
|                                                                              |
|  S7Client Communication class                                                |
|                                                                              |
|=============================================================================*/
#include <QDebug>

#include "core/snap7.h"
#include "client.h"


#ifdef OS_WINDOWS
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#endif


Client::Client(QObject *parent) :
    QObject             (parent),
    S7Client            (nullptr),
    repoDestDbStruct    (nullptr),
    _address            (nullptr)
{
    _dbNumber = 0;
    ok = 0;
    ko = 0;
    cosik = true;
}

Client::~Client()
{
    makeDisconnect();

    delete S7Client;
    S7Client = nullptr;

    delete _address;
    _address = nullptr;

    delete repoDestDbStruct;
    repoDestDbStruct = nullptr;
}
void Client::setIpAddress(const char* arg1)
{
    if ( _address != nullptr){
        delete _address;
        _address = nullptr;
    }
    _address = arg1;
}
void Client::setDbNumber(const int &arg1)
{
    _dbNumber = arg1;
}

//------------------------------------------------------------------------------
// Unit Connection
//------------------------------------------------------------------------------
bool Client::makeConnect()
{
    if ( S7Client != nullptr ){
        delete S7Client;
        S7Client = nullptr;
    }
    S7Client= new TS7Client();

    int res = S7Client->ConnectTo(_address,PLCRACK,PLCSLOT);
    if (_check(res,"UNIT Connection")) {
        qDebug("  Connected to   : %s (Rack=%d, Slot=%d)",_address,PLCRACK,PLCSLOT);
        qDebug("  PDU Requested  : %d bytes",S7Client->PDURequested());
        qDebug("  PDU Negotiated : %d bytes",S7Client->PDULength());
        emit messageText( "UNIT Connection" );
        emit messageText( "Connected to " + QString::fromStdString(_address) );
    };
    return res==0;
}
//------------------------------------------------------------------------------
// Unit Disconnection
//------------------------------------------------------------------------------
void Client::makeDisconnect()
{
    S7Client->Disconnect();
}
//------------------------------------------------------------------------------
// Check error
//------------------------------------------------------------------------------
bool Client::_check(int result, const char * function)
{
    qDebug("+-----------------------------------------------------");
    qDebug("| %s",function);
    qDebug("+-----------------------------------------------------");
    emit messageText("+-----------------------------------------------------");
    emit messageText("| " + QString::fromStdString(function));
    emit messageText("+-----------------------------------------------------");
    if (result==0) {
        qDebug("| Result         : OK");
        qDebug("| Execution time : %d ms",S7Client->ExecTime());
        qDebug("+-----------------------------------------------------");
        emit messageText("| Result         : OK");
        emit messageText("| Execution time : " + QString::number(S7Client->ExecTime()) + "ms");
        emit messageText("+-----------------------------------------------------");

        ok++;
        emit messageOk(ok);
    }
    else {
        qDebug("| ERROR !!!");
        emit messageText("| ERROR !!!");
        if (result<0){
            qDebug("| Library Error (-1)");
            emit messageText("| Library Error (-1)");
        }
        else {
            qDebug("| %s",CliErrorText(result).c_str());
            emit messageText("| " + QString::fromStdString(CliErrorText(result).c_str()));
        }
        qDebug("+-----------------------------------------------------");
        emit messageText("+-----------------------------------------------------");
        ko++;
        emit messageKo(ko);
    }
    return result==0;
}
//------------------------------------------------------------------------------
// Multi Read
//------------------------------------------------------------------------------
void Client::makeMultiRead(int& dbNumber, RepoDestDbStruct& dbStruct)
{
    // Prepare struct
    TS7DataItem Items[5];

    // NOTE : *AMOUNT IS NOT SIZE* , it's the number of items

    // DBX0.0 - fault
    Items[0].Area     = S7AreaDB;
    Items[0].WordLen  = S7WLBit;
    Items[0].DBNumber = dbNumber;
    Items[0].Start    = 0;
    Items[0].Amount   = 1;
    Items[0].pdata    = &dbStruct.fault;
    // DBX0.1 - fault_ack
    Items[1].Area     = S7AreaDB;
    Items[1].WordLen  = S7WLBit;
    Items[1].DBNumber = dbNumber;
    Items[1].Start    = 1;
    Items[1].Amount   = 1;
    Items[1].pdata    = &dbStruct.fault_ack;
    // DBX0.2 - product_ok
    Items[2].Area     = S7AreaDB;
    Items[2].WordLen  = S7WLBit;
    Items[2].DBNumber = dbNumber;
    Items[2].Start    = 2;
    Items[2].Amount   = 1;
    Items[2].pdata    = &dbStruct.part_ok;
    // DBX0.3 - product_ok_ack
    Items[3].Area     = S7AreaDB;
    Items[3].WordLen  = S7WLBit;
    Items[3].DBNumber = dbNumber;
    Items[3].Start    = 3;
    Items[3].Amount   = 1;
    Items[3].pdata    = &dbStruct.part_ok_ack;
    // DBW2 - fault_number
    Items[4].Area     = S7AreaDB;
    Items[4].WordLen  = S7WLByte;
    Items[4].DBNumber = dbNumber;
    Items[4].Start    = 2;
    Items[4].Amount   = 2;
    Items[4].pdata    = &dbStruct.fault_number;

    int res=S7Client->ReadMultiVars(&Items[0],5);
    if (_check(res,"Multiread Vars"))
    {
        // Result of S7Client->ReadMultivars is the "global result" of
        // the function, it's OK if something was exchanged.

        // But we need to check single Var results.
        // Let shall suppose that we ask for 5 vars, 4 of them are ok but
        // the 5th is inexistent, we will have 4 results ok and 1 not ok.

        qDebug("DBX0.0 : %d",Items[0].Result);
        if (Items[0].Result==0)
            _hexdump(&dbStruct.fault,1);
        qDebug("DBX0.1 : %d",Items[1].Result);
        if (Items[1].Result==0)
            _hexdump(&dbStruct.fault_ack,1);
        qDebug("DBX0.2 : %d",Items[2].Result);
        if (Items[2].Result==0)
            _hexdump(&dbStruct.part_ok,1);
        qDebug("DBX0.3 : %d",Items[3].Result);
        if (Items[3].Result==0)
            _hexdump(&dbStruct.part_ok_ack,1);
        qDebug("DBW2 : %d",Items[4].Result);
        if (Items[4].Result==0)
            _hexdump(&dbStruct.fault_number,2);
    };
}
//------------------------------------------------------------------------------
// CPU Info : catalog
//------------------------------------------------------------------------------
void Client::_orderCode()
{
    TS7OrderCode Info;
    int res=S7Client->GetOrderCode(&Info);
    if (_check(res,"Catalog"))
    {
        qDebug("  Order Code : %s",Info.Code);
        qDebug("  Version    : %d.%d.%d",Info.V1,Info.V2,Info.V3);
    };
}
//------------------------------------------------------------------------------
// CPU Info : unit info
//------------------------------------------------------------------------------
void Client::_cpuInfo()
{
    TS7CpuInfo Info;
    int res=S7Client->GetCpuInfo(&Info);
    if (_check(res,"Unit Info"))
    {
        qDebug() <<  "  Module Type Name  : "+QString::fromStdString(Info.ModuleTypeName);
        qDebug() <<  "  Serial Number     : "+QString::fromStdString(Info.SerialNumber);
        qDebug() <<  "  AS Name           : "+QString::fromStdString(Info.ASName);
        qDebug() <<  "  Module Name       : "+QString::fromStdString(Info.ModuleName);
    };
}
//------------------------------------------------------------------------------
// PLC Status
//------------------------------------------------------------------------------
void Client::_unitStatus()
{
    int res=0;
    int Status=S7Client->PlcStatus();
    if (_check(res,"CPU Status"))
    {
        switch (Status)
        {
        case S7CpuStatusRun : qDebug("  RUN"); break;
        case S7CpuStatusStop: qDebug("  STOP"); break;
        default             : qDebug("  UNKNOWN"); break;
        }
    };
}
//------------------------------------------------------------------------------
// Tests Summary
//------------------------------------------------------------------------------
void Client::_summary()
{

    qDebug() << "+-----------------------------------------------------";
    qDebug() << "| Test Summary ";
    qDebug() << "+-----------------------------------------------------";
    qDebug() << "| Performed  : "+QString::number( ok + ko );
    qDebug() << "| Passed     : "+QString::number( ok );
    qDebug() << "| Failed     : "+QString::number( ko );
    qDebug() << "+-----------------------------------------------------";

}
//------------------------------------------------------------------------------
// hexdump, a very nice function, it's not mine.
// I found it on the net somewhere some time ago... thanks to the author ;-)
//------------------------------------------------------------------------------
#ifndef HEXDUMP_COLS
#define HEXDUMP_COLS 16
#endif
void Client::_hexdump(void *mem, unsigned int len)
{
    unsigned int i, j;

    for(i = 0; i < len + ((len % HEXDUMP_COLS) ? (HEXDUMP_COLS - len % HEXDUMP_COLS) : 0); i++){
        /* print offset */
        if(i % HEXDUMP_COLS == 0){
            qDebug("0x%04x: ", i);
        }
        /* print hex data */
        if(i < len){
            qDebug("%02x ", 0xFF & ((char*)mem)[i]);
        }
        else /* end of block, just aligning for ASCII dump */{
            qDebug("   ");
        }
        /* print ASCII dump */
        if(i % HEXDUMP_COLS == (HEXDUMP_COLS - 1)){
            for(j = i - (HEXDUMP_COLS - 1); j <= i; j++){
                if(j >= len) /* end of block, not really printing */{
                    putchar(' ');
                }
                else if(isprint((((char*)mem)[j] & 0x7F))) /* printable char */{
                    putchar(0xFF & ((char*)mem)[j]);
                }
                else /* other char */{
                    putchar('.');
                }
            }
            putchar('\n');
        }
    }
}



