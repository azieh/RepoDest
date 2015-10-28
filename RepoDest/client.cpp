/*|============================================================================|
|                                                                              |
|  S7Client Example                                                              |
|                                                                              |
|=============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "core/snap7.h"
#include "client.h"
#include <QApplication>
#include <QtWidgets>
#include <QtCore/qstate.h>

#ifdef OS_WINDOWS
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#endif



Client::Client()
{
   S7Client= new TS7Client();
}

Client::~Client()
{

    CliDisconnect();
    delete S7Client;

}




//------------------------------------------------------------------------------
//  Async completion callback
//------------------------------------------------------------------------------
// This is a simply text demo, we use callback only to set an internal flag...
//void S7API Client::CliCompletion(void *usrPtr, int opCode, int opResult)
//{
//JobResult=opResult;
//JobDone = true;
//}
//------------------------------------------------------------------------------
// SysSleep (copied from snap_sysutils.cpp) multiplatform millisec sleep
//------------------------------------------------------------------------------
void Client::SysSleep(longword Delay_ms)
{
#ifdef OS_WINDOWS
Sleep(Delay_ms);
#else
struct timespec ts;
ts.tv_sec = (time_t)(Delay_ms / 1000);
ts.tv_nsec =(long)((Delay_ms - ts.tv_sec) * 1000000);
nanosleep(&ts, (struct timespec *)0);
#endif
}
//------------------------------------------------------------------------------
//  Usage Syntax
//------------------------------------------------------------------------------
void Client::Usage()
{
qWarning("Usage\n");
qWarning("  S7Client <IP> [Rack=0 Slot=2]\n");
qWarning("Example\n");
qWarning("  S7Client 192.168.1.101 0 2\n");
qWarning("or\n");
qWarning("  S7Client 192.168.1.101\n");

}
//------------------------------------------------------------------------------
// hexdump, a very nice function, it's not mine.
// I found it on the net somewhere some time ago... thanks to the author ;-)
//------------------------------------------------------------------------------
#ifndef HEXDUMP_COLS
#define HEXDUMP_COLS 16
#endif
void Client::hexdump(void *mem, unsigned int len)
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
bool Client::Check(int Result, const char * function)
{
qWarning("\n");
qWarning("+-----------------------------------------------------\n");
qWarning("| %s\n",function);
qWarning("+-----------------------------------------------------\n");
if (Result==0) {
   qWarning("| Result         : OK\n");
   qWarning("| Execution time : %d ms\n",S7Client->ExecTime());
   qWarning("+-----------------------------------------------------\n");
   ok++;
}
else {
   qWarning("| ERROR !!! \n");
   if (Result<0)
       qWarning("| Library Error (-1)\n");
   else
       qWarning("| %s\n",CliErrorText(Result).c_str());
   qWarning("+-----------------------------------------------------\n");
   ko++;
}
return Result==0;
}
//------------------------------------------------------------------------------
// Multi Read
//------------------------------------------------------------------------------
void Client::MultiRead()
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
if (Check(res,"Multiread Vars"))
{
   // Result of S7Client->ReadMultivars is the "global result" of
   // the function, it's OK if something was exchanged.

   // But we need to check single Var results.
   // Let shall suppose that we ask for 5 vars, 4 of them are ok but
   // the 5th is inexistent, we will have 4 results ok and 1 not ok.

   qWarning("DBX0.0 : %d\n",Items[0].Result);
   if (Items[0].Result==0)
       hexdump(&fault,1);
   qWarning("DBX0.1 : %d\n",Items[1].Result);
   if (Items[1].Result==0)
       hexdump(&fault_ack,1);
   qWarning("DBX0.2 : %d\n",Items[2].Result);
   if (Items[2].Result==0)
       hexdump(&part_ok,1);
   qWarning("DBX0.3 : %d\n",Items[3].Result);
   if (Items[3].Result==0)
       hexdump(&part_ok_ack,1);         // 8 Timers -> 16 bytes
   qWarning("DBW2 : %d\n",Items[4].Result);
   if (Items[4].Result==0)
       hexdump(&fault_nr,2);         // 8 Counters -> 16 bytes
};
}
//------------------------------------------------------------------------------
// List blocks in AG
//------------------------------------------------------------------------------
void Client::ListBlocks()
{
TS7BlocksList List;
int res=S7Client->ListBlocks(&List);
if (Check(res,"List Blocks in AG"))
{
   qWarning("  OBCount  : %d\n",List.OBCount);
   qWarning("  FBCount  : %d\n",List.FBCount);
   qWarning("  FCCount  : %d\n",List.FCCount);
   qWarning("  SFBCount : %d\n",List.SFBCount);
   qWarning("  SFCCount : %d\n",List.SFCCount);
   qWarning("  DBCount  : %d\n",List.DBCount);
   qWarning("  SDBCount : %d\n",List.SDBCount);
};
}
//------------------------------------------------------------------------------
// CPU Info : catalog
//------------------------------------------------------------------------------
void Client::OrderCode()
{
TS7OrderCode Info;
int res=S7Client->GetOrderCode(&Info);
if (Check(res,"Catalog"))
{
     qWarning("  Order Code : %s\n",Info.Code);
     qWarning("  Version    : %d.%d.%d\n",Info.V1,Info.V2,Info.V3);
};
}
//------------------------------------------------------------------------------
// CPU Info : unit info
//------------------------------------------------------------------------------
void Client::CpuInfo()
{
TS7CpuInfo Info;
int res=S7Client->GetCpuInfo(&Info);
if (Check(res,"Unit Info"))
{
qWarning() <<  "  Nazwa modułu   : "+QString::fromStdString(Info.ModuleTypeName);
qWarning() <<  "  Numer seryjny  : "+QString::fromStdString(Info.SerialNumber);
qWarning() <<  "  Nazwa AS       : "+QString::fromStdString(Info.ASName);
qWarning() <<  "  Nazwa modułu   : "+QString::fromStdString(Info.ModuleName);
};
}
//------------------------------------------------------------------------------
// CP Info
//------------------------------------------------------------------------------
void Client::CpInfo()
{
TS7CpInfo Info;
int res=S7Client->GetCpInfo(&Info);
if (Check(res,"Communication processor Info"))
{
     qWarning("  Max PDU Length   : %d bytes\n",Info.MaxPduLengt);
     qWarning("  Max Connections  : %d \n",Info.MaxConnections);
     qWarning("  Max MPI Rate     : %d bps\n",Info.MaxMpiRate);
     qWarning("  Max Bus Rate     : %d bps\n",Info.MaxBusRate);
};
}
//------------------------------------------------------------------------------
// PLC Status
//------------------------------------------------------------------------------
void Client::UnitStatus()
{
int res=0;
int Status=S7Client->PlcStatus();
if (Check(res,"CPU Status"))
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
// Upload DB0 (surely exists in AG)
//------------------------------------------------------------------------------
void Client::UploadDB0()
{
int Size = sizeof(Buffer); // Size is IN/OUT par
                           // In input it tells the S7Client the size available
                           // In output it tells us how many bytes were uploaded.
int res=S7Client->Upload(Block_SDB, 0, &Buffer, &Size);
if (Check(res,"Block Upload (SDB 0)"))
{
     qWarning("Dump (%d bytes) :\n",Size);
     hexdump(&Buffer,Size);
}
}

//------------------------------------------------------------------------------
// Async Upload DB0 (using callback as completion trigger)
//------------------------------------------------------------------------------
void Client::AsCBUploadDB0()
{
int Size = sizeof(Buffer); // Size is IN/OUT par
                           // In input it tells the S7Client the size available
                           // In output it tells us how many bytes were uploaded.
JobDone=false;
int res=S7Client->AsUpload(Block_SDB, 0, &Buffer, &Size);

if (res==0)
{
    while (!JobDone)
    {
        SysSleep(100);
    }
    res=JobResult;
}

if (Check(res,"Async (callback) Block Upload (SDB 0)"))
{
     qWarning("Dump (%d bytes) :\n",Size);
     hexdump(&Buffer,Size);
}
}
//------------------------------------------------------------------------------
// Async Upload DB0 (using event wait as completion trigger)
//------------------------------------------------------------------------------
void Client::AsEWUploadDB0()
{
int Size = sizeof(Buffer); // Size is IN/OUT par
                           // In input it tells the S7Client the size available
                           // In output it tells us how many bytes were uploaded.
JobDone=false;
int res=S7Client->AsUpload(Block_SDB, 0, &Buffer, &Size);

if (res==0)
{
    res=S7Client->WaitAsCompletion(3000);
}

if (Check(res,"Async (Wait event) Block Upload (SDB 0)"))
{
     qWarning("Dump (%d bytes) :\n",Size);
     hexdump(&Buffer,Size);
}
}
//------------------------------------------------------------------------------
// Async Upload DB0 (using polling as completion trigger)
//------------------------------------------------------------------------------
void Client::AsPOUploadDB0()
{
int Size = sizeof(Buffer); // Size is IN/OUT par
                           // In input it tells the S7Client the size available
                           // In output it tells us how many bytes were uploaded.
JobDone=false;
int res=S7Client->AsUpload(Block_SDB, 0, &Buffer, &Size);

if (res==0)
{
    while (!S7Client->CheckAsCompletion(&res))
    {
        SysSleep(100);
    };
}

if (Check(res,"Async (polling) Block Upload (SDB 0)"))
{
     qWarning("Dump (%d bytes) :\n",Size);
     hexdump(&Buffer,Size);
}
}
//------------------------------------------------------------------------------
// Read a sample SZL Block
//------------------------------------------------------------------------------
void Client::ReadSzl_0011_0000()
{
PS7SZL SZL = PS7SZL(&Buffer);  // use our buffer casted as TS7SZL
int Size = sizeof(Buffer);
// Block ID 0x0011 IDX 0x0000 normally exists in every CPU
int res=S7Client->ReadSZL(0x0011, 0x0000, SZL, &Size);
if (Check(res,"Read SZL - ID : 0x0011, IDX 0x0000"))
{
   qWarning("  LENTHDR : %d\n",SZL->Header.LENTHDR);
   qWarning("  N_DR    : %d\n",SZL->Header.N_DR);
   qWarning("Dump (%d bytes) :\n",Size);
   hexdump(&Buffer,Size);
}
}
//------------------------------------------------------------------------------
// Unit Connection
//------------------------------------------------------------------------------
bool Client::CliConnect()
{
int res = S7Client->ConnectTo(Address,Rack,Slot);
if (Check(res,"UNIT Connection")) {
     qWarning("  Connected to   : %s (Rack=%d, Slot=%d)\n",Address,Rack,Slot);
     qWarning("  PDU Requested  : %d bytes\n",S7Client->PDURequested());
     qWarning("  PDU Negotiated : %d bytes\n",S7Client->PDULength());
};
return res==0;
}
//------------------------------------------------------------------------------
// Unit Disconnection
//------------------------------------------------------------------------------
void Client::CliDisconnect()
{
S7Client->Disconnect();
}
//------------------------------------------------------------------------------
// Perform readonly tests, no cpu status modification
//------------------------------------------------------------------------------
void Client::PerformTests()
{
OrderCode();
CpuInfo();
CpInfo();
UnitStatus();
ReadSzl_0011_0000();
UploadDB0();
AsCBUploadDB0();
AsEWUploadDB0();
AsPOUploadDB0();
MultiRead();
}
//------------------------------------------------------------------------------
// Tests Summary
//------------------------------------------------------------------------------
void Client::Summary()
{

//w->on_appenedMessage_textChanged("+-----------------------------------------------------");
//w->on_appenedMessage_textChanged("| Test wykonanych operacji");
//w->on_appenedMessage_textChanged("+-----------------------------------------------------");
//w->on_appenedMessage_textChanged("| Wykonano  : "+QString::number(ok+ko));
//w->on_appenedMessage_textChanged("| Pomyślnie : "+QString::number(ok));
//w->on_appenedMessage_textChanged("| Błędnie   : "+QString::number(ko));
//w->on_appenedMessage_textChanged("+-----------------------------------------------------");

}

void Client::ReadDbArea()
{


  CpuInfo();






}



//------------------------------------------------------------------------------
// Main S7Client area
//------------------------------------------------------------------------------



void Client::mainFunction()
{

    S7Client->ConnectTo("192.168.10.20", 0, 2);
    CpuInfo();
    MultiRead();


}


