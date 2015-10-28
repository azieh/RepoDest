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
    S7Client (nullptr)
{

}

Client::~Client()
{

    cliDisconnect();
    delete S7Client;

}

//------------------------------------------------------------------------------
// Unit Connection
//------------------------------------------------------------------------------
bool Client::cliConnect()
{
    if (S7Client!=nullptr){
        delete S7Client;
        S7Client = nullptr;
    }
    S7Client= new TS7Client();
    int res = S7Client->ConnectTo(Address,Rack,Slot);
    if (_check(res,"UNIT Connection")) {
        qWarning("  Connected to   : %s (Rack=%d, Slot=%d)\n",Address,Rack,Slot);
        qWarning("  PDU Requested  : %d bytes\n",S7Client->PDURequested());
        qWarning("  PDU Negotiated : %d bytes\n",S7Client->PDULength());
    };
    return res==0;
}
//------------------------------------------------------------------------------
// Unit Disconnection
//------------------------------------------------------------------------------
void Client::cliDisconnect()
{
    S7Client->Disconnect();
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

    for(i = 0; i < len + ((len % HEXDUMP_COLS) ? (HEXDUMP_COLS - len % HEXDUMP_COLS) : 0); i++)
    {
        /* print offset */
        if(i % HEXDUMP_COLS == 0)
        {
            qWarning("0x%04x: ", i);
        }

        /* print hex data */
        if(i < len)
        {
            qWarning("%02x ", 0xFF & ((char*)mem)[i]);
        }
        else /* end of block, just aligning for ASCII dump */
        {
            qWarning("   ");
        }

        /* print ASCII dump */
        if(i % HEXDUMP_COLS == (HEXDUMP_COLS - 1))
        {
            for(j = i - (HEXDUMP_COLS - 1); j <= i; j++)
            {
                if(j >= len) /* end of block, not really printing */
                {
                    putchar(' ');
                }
                else if(isprint((((char*)mem)[j] & 0x7F))) /* printable char */
                {
                    putchar(0xFF & ((char*)mem)[j]);
                }
                else /* other char */
                {
                    putchar('.');
                }
            }
            putchar('\n');
        }
    }
}
//------------------------------------------------------------------------------
// Check error
//------------------------------------------------------------------------------
bool Client::_check(int result, const char * function)
{
    qWarning("\n");
    qWarning("+-----------------------------------------------------\n");
    qWarning("| %s\n",function);
    qWarning("+-----------------------------------------------------\n");
    if (result==0) {
        qWarning("| Result         : OK\n");
        qWarning("| Execution time : %d ms\n",S7Client->ExecTime());
        qWarning("+-----------------------------------------------------\n");
        _ok++;
    }
    else {
        qWarning("| ERROR !!! \n");
        if (result<0)
            qWarning("| Library Error (-1)\n");
        else
            qWarning("| %s\n",CliErrorText(result).c_str());
        qWarning("+-----------------------------------------------------\n");
        _ko++;
    }
    return result==0;
}
//------------------------------------------------------------------------------
// Multi Read
//------------------------------------------------------------------------------
void Client::multiRead()
{
    // Multiread buffers
    bool fault;
    bool fault_ack;
    bool part_ok;
    bool part_ok_ack;
    byte fault_nr[2];

    // Prepare struct
    TS7DataItem Items[5];

    // NOTE : *AMOUNT IS NOT SIZE* , it's the number of items

    // Merkers
    Items[0].Area     =S7AreaDB;
    Items[0].WordLen  =S7WLBit;
    Items[0].DBNumber =998;        // Don't need DB
    Items[0].Start    =0;        // Starting from 0
    Items[0].Amount   =1;       // 16 Items (bytes)
    Items[0].pdata    =&fault;
    // Digital Input bytes
    Items[1].Area     =S7AreaDB;
    Items[1].WordLen  =S7WLBit;
    Items[1].DBNumber =998;        // Don't need DB
    Items[1].Start    =1;        // Starting from 0
    Items[1].Amount   =1;       // 16 Items (bytes)
    Items[1].pdata    =&fault_ack;
    // Digital Output bytes
    Items[2].Area     =S7AreaDB;
    Items[2].WordLen  =S7WLBit;
    Items[2].DBNumber =998;        // Don't need DB
    Items[2].Start    =2;        // Starting from 0
    Items[2].Amount   =1;       // 16 Items (bytes)
    Items[2].pdata    =&part_ok;
    // Timers
    Items[3].Area     =S7AreaDB;
    Items[3].WordLen  =S7WLBit;
    Items[3].DBNumber =998;        // Don't need DB
    Items[3].Start    =3;        // Starting from 0
    Items[3].Amount   =1;        // 8 Timers
    Items[3].pdata    =&part_ok_ack;
    // Counters
    Items[4].Area     =S7AreaDB;
    Items[4].WordLen  =S7WLByte;
    Items[4].DBNumber =998;        // Don't need DB
    Items[4].Start    =2;        // Starting from 0
    Items[4].Amount   =2;        // 8 Counters
    Items[4].pdata    =&fault_nr;

    int res=S7Client->ReadMultiVars(&Items[0],5);
    if (_check(res,"Multiread Vars"))
    {
        // Result of S7Client->ReadMultivars is the "global result" of
        // the function, it's OK if something was exchanged.

        // But we need to check single Var results.
        // Let shall suppose that we ask for 5 vars, 4 of them are ok but
        // the 5th is inexistent, we will have 4 results ok and 1 not ok.

        qWarning("DBX0.0 : %d\n",Items[0].Result);
        if (Items[0].Result==0)
            _hexdump(&fault,1);
        qWarning("DBX0.1 : %d\n",Items[1].Result);
        if (Items[1].Result==0)
            _hexdump(&fault_ack,1);
        qWarning("DBX0.2 : %d\n",Items[2].Result);
        if (Items[2].Result==0)
            _hexdump(&part_ok,1);
        qWarning("DBX0.3 : %d\n",Items[3].Result);
        if (Items[3].Result==0)
            _hexdump(&part_ok_ack,1);         // 8 Timers -> 16 bytes
        qWarning("DBW2 : %d\n",Items[4].Result);
        if (Items[4].Result==0)
            _hexdump(&fault_nr,2);         // 8 Counters -> 16 bytes
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
        qWarning("  Order Code : %s\n",Info.Code);
        qWarning("  Version    : %d.%d.%d\n",Info.V1,Info.V2,Info.V3);
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
        qWarning() <<  "  Nazwa modułu   : "+QString::fromStdString(Info.ModuleTypeName);
        qWarning() <<  "  Numer seryjny  : "+QString::fromStdString(Info.SerialNumber);
        qWarning() <<  "  Nazwa AS       : "+QString::fromStdString(Info.ASName);
        qWarning() <<  "  Nazwa modułu   : "+QString::fromStdString(Info.ModuleName);
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
        case S7CpuStatusRun : qWarning("  RUN\n"); break;
        case S7CpuStatusStop: qWarning("  STOP\n"); break;
        default             : qWarning("  UNKNOWN\n"); break;
        }
    };
}
//------------------------------------------------------------------------------
// Tests Summary
//------------------------------------------------------------------------------
void Client::_summary()
{

    //w->on_appenedMessage_textChanged("+-----------------------------------------------------");
    //w->on_appenedMessage_textChanged("| Test wykonanych operacji");
    //w->on_appenedMessage_textChanged("+-----------------------------------------------------");
    //w->on_appenedMessage_textChanged("| Wykonano  : "+QString::number(ok+ko));
    //w->on_appenedMessage_textChanged("| Pomyślnie : "+QString::number(ok));
    //w->on_appenedMessage_textChanged("| Błędnie   : "+QString::number(ko));
    //w->on_appenedMessage_textChanged("+-----------------------------------------------------");

}
//------------------------------------------------------------------------------
// Main S7Client area
//------------------------------------------------------------------------------



void Client::mainFunction()
{




    _cpuInfo();
    multiRead();


}


