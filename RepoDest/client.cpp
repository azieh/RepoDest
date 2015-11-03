/*|============================================================================|
|                                                                              |
|  S7Client Example                                                              |
|                                                                              |
|=============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "core/snap7.h"
#include "client.h"
#include <QtWidgets>

#ifdef OS_WINDOWS
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#endif


Client::Client() :
    S7Client            (nullptr),
    address             (nullptr),
    repoDestDbStruct    (nullptr)
{
    dbNumber = 0;

    ok = 0;
    ko = 0;
}

Client::~Client()
{
    disconnect();

    delete S7Client;
    S7Client = nullptr;

    delete address;
    address = nullptr;

    delete repoDestDbStruct;
    repoDestDbStruct = nullptr;
}
//------------------------------------------------------------------------------
// Unit Connection
//------------------------------------------------------------------------------
bool Client::connect()
{
    if ( S7Client != nullptr ){
        delete S7Client;
        S7Client = nullptr;
    }
    S7Client= new TS7Client();
    int res = S7Client->ConnectTo(address,PLCRACK,PLCSLOT);
    if (_check(res,"UNIT Connection")) {
        qWarning("  Connected to   : %s (Rack=%d, Slot=%d)",address,PLCRACK,PLCSLOT);
        qWarning("  PDU Requested  : %d bytes",S7Client->PDURequested());
        qWarning("  PDU Negotiated : %d bytes",S7Client->PDULength());
    };
    return res==0;
}
//------------------------------------------------------------------------------
// Unit Disconnection
//------------------------------------------------------------------------------
void Client::disconnect()
{
    S7Client->Disconnect();
}
//------------------------------------------------------------------------------
// Check error
//------------------------------------------------------------------------------
bool Client::_check(int result, const char * function)
{
    qWarning("+-----------------------------------------------------");
    qWarning("| %s",function);
    qWarning("+-----------------------------------------------------");
    if (result==0) {
        qWarning("| Result         : OK");
        qWarning("| Execution time : %d ms",S7Client->ExecTime());
        qWarning("+-----------------------------------------------------");
        ok++;
    }
    else {
        qWarning("| ERROR !!!");
        if (result<0)
            qWarning("| Library Error (-1)");
        else
            qWarning("| %s",CliErrorText(result).c_str());
        qWarning("+-----------------------------------------------------");
        ko++;
    }
    return result==0;
}
//------------------------------------------------------------------------------
// Multi Read
//------------------------------------------------------------------------------
void Client::multiRead(int& dbNumber, RepoDestDbStruct& dbStruct)
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

        qWarning("DBX0.0 : %d",Items[0].Result);
        if (Items[0].Result==0)
            _hexdump(&dbStruct.fault,1);
        qWarning("DBX0.1 : %d",Items[1].Result);
        if (Items[1].Result==0)
            _hexdump(&dbStruct.fault_ack,1);
        qWarning("DBX0.2 : %d",Items[2].Result);
        if (Items[2].Result==0)
            _hexdump(&dbStruct.part_ok,1);
        qWarning("DBX0.3 : %d",Items[3].Result);
        if (Items[3].Result==0)
            _hexdump(&dbStruct.part_ok_ack,1);
        qWarning("DBW2 : %d",Items[4].Result);
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
        qWarning("  Order Code : %s",Info.Code);
        qWarning("  Version    : %d.%d.%d",Info.V1,Info.V2,Info.V3);
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
        qWarning() <<  "  Module Type Name  : "+QString::fromStdString(Info.ModuleTypeName);
        qWarning() <<  "  Serial Number     : "+QString::fromStdString(Info.SerialNumber);
        qWarning() <<  "  AS Name           : "+QString::fromStdString(Info.ASName);
        qWarning() <<  "  Module Name       : "+QString::fromStdString(Info.ModuleName);
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
        case S7CpuStatusRun : qWarning("  RUN"); break;
        case S7CpuStatusStop: qWarning("  STOP"); break;
        default             : qWarning("  UNKNOWN"); break;
        }
    };
}
//------------------------------------------------------------------------------
// Tests Summary
//------------------------------------------------------------------------------
void Client::_summary()
{

    qWarning() << "+-----------------------------------------------------";
    qWarning() << "| Test Summary ";
    qWarning() << "+-----------------------------------------------------";
    qWarning() << "| Performed  : "+QString::number(ok+ko);
    qWarning() << "| Passed     : "+QString::number(ok);
    qWarning() << "| Failed     : "+QString::number(ko);
    qWarning() << "+-----------------------------------------------------";

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
            qWarning("0x%04x: ", i);
        }
        /* print hex data */
        if(i < len){
            qWarning("%02x ", 0xFF & ((char*)mem)[i]);
        }
        else /* end of block, just aligning for ASCII dump */{
            qWarning("   ");
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
//------------------------------------------------------------------------------
// Main S7Client area
//------------------------------------------------------------------------------
void Client::startPlcCommunication()
{
    connect();
}


