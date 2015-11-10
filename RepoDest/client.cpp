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
    _address            (nullptr)
{
    isConnected = false;
    isDisconnected = false;
    _dbNumber = 0;
    ok = 0;
    ko = 0;
}

Client::~Client()
{
    makeDisconnect();

    delete S7Client;
    S7Client = nullptr;

    delete _address;
    _address = nullptr;
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
    _checkOkKo();
    int result;
    if ( _address != nullptr ){ // checking if Ip address is correctly set
        if ( S7Client != nullptr ){
            delete S7Client;
            S7Client = nullptr;
        }
        S7Client= new TS7Client();

        result = S7Client->ConnectTo(_address,PLCRACK,PLCSLOT);
        if ( isConnected == false ){
            if ( result == 0 ) {
                emit messageText( "Connected to " + QString::fromStdString(_address) + " (Rack=" + QString::number(PLCRACK) + ", Slot=" + QString::number(PLCSLOT) + ")" );
                emit messageText( "Execution time : " + QString::number(S7Client->ExecTime()) + "ms");
                isConnected = true;
                isDisconnected = false;
                ok++;
                emit messageKo( ok );
            } else if ( isDisconnected == false && result != 0){
                emit messageText( "Connection NOK" );
                emit messageText( "Problem is :" + QString::fromStdString(CliErrorText(result).c_str()) );
                isConnected = false;
                isDisconnected = true;
                ko++;
                emit messageKo( ko );
            } else {
                ko++;
                emit messageKo( ko );
            }
            isConnected = S7Client->Connected();
            emit connectionStatus( isConnected );
        } else {
            emit messageText( "Ip address of client is not set" );
            ko++;
            emit messageKo(ko);
        }
    }
    return result==0;
}
//------------------------------------------------------------------------------
// Unit Disconnection
//------------------------------------------------------------------------------
void Client::makeDisconnect()
{
    S7Client->Disconnect();
}
//------------------------------------------------------------------------------
// Multi Read
//------------------------------------------------------------------------------
bool Client::makeMultiRead(RepoDestDbStruct* dbStruct)
{
    int result;
    if ( _dbNumber != 0 ){
        // Prepare struct
        TS7DataItem Items[5];

        // NOTE : *AMOUNT IS NOT SIZE* , it's the number of items

        // DBX0.0 - fault
        Items[0].Area     = S7AreaDB;
        Items[0].WordLen  = S7WLBit;
        Items[0].DBNumber = _dbNumber;
        Items[0].Start    = 0;
        Items[0].Amount   = 1;
        Items[0].pdata    = &dbStruct->fault;
        // DBX0.1 - fault_ack
        Items[1].Area     = S7AreaDB;
        Items[1].WordLen  = S7WLBit;
        Items[1].DBNumber = _dbNumber;
        Items[1].Start    = 1;
        Items[1].Amount   = 1;
        Items[1].pdata    = &dbStruct->fault_ack;
        // DBX0.2 - product_ok
        Items[2].Area     = S7AreaDB;
        Items[2].WordLen  = S7WLBit;
        Items[2].DBNumber = _dbNumber;
        Items[2].Start    = 2;
        Items[2].Amount   = 1;
        Items[2].pdata    = &dbStruct->part_ok;
        // DBX0.3 - product_ok_ack
        Items[3].Area     = S7AreaDB;
        Items[3].WordLen  = S7WLBit;
        Items[3].DBNumber = _dbNumber;
        Items[3].Start    = 3;
        Items[3].Amount   = 1;
        Items[3].pdata    = &dbStruct->part_ok_ack;
        // DBW2 - fault_number
        Items[4].Area     = S7AreaDB;
        Items[4].WordLen  = S7WLByte;
        Items[4].DBNumber = _dbNumber;
        Items[4].Start    = 1;
        Items[4].Amount   = 1;
        Items[4].pdata    = &dbStruct->fault_number;

        result = S7Client->ReadMultiVars(&Items[0],5);
        if ( result == 0 )
        {
            // Result of S7Client->ReadMultivars is the "global result" of
            // the function, it's OK if something was exchanged.

            // But we need to check single Var results.
            // Let shall suppose that we ask for 5 vars, 4 of them are ok but
            // the 5th is inexistent, we will have 4 results ok and 1 not ok.

            if (Items[0].Result != 0){
                emit messageText( "Problem with reading data from DB" + QString::number( _dbNumber ) + ".DBX0.0" );
                result = 99;
            }
            if (Items[1].Result != 0){
                emit messageText( "Problem with reading data from DB" + QString::number( _dbNumber ) + ".DBX0.1" );
                result = 98;
            }
            if (Items[2].Result != 0){
                emit messageText( "Problem with reading data from DB" + QString::number( _dbNumber ) + ".DBX0.2" );
                result = 97;
            }
            if (Items[3].Result != 0){
                emit messageText( "Problem with reading data from DB" + QString::number( _dbNumber ) + ".DBX0.3" );
                result = 96;
            }
            if (Items[4].Result != 0){
                emit messageText( "Problem with reading data from DB" + QString::number( _dbNumber ) + ".DBB1" );
                result = 95;
            }
            _check(result,"Multiread Vars"); // check result of reading
        };
    } else {
        result = 99;
        emit messageText( "Number of client DB is not set" );
        ko++;
        emit messageKo(ko);
    }
    return result == 0;
}
//------------------------------------------------------------------------------
// Multi Write
//------------------------------------------------------------------------------
bool Client::makeMultiWrite(RepoDestDbStruct* dbStruct)
{
    int result;
    if ( _dbNumber != 0 ){
        // Prepare struct
        TS7DataItem Items[5];

        // NOTE : *AMOUNT IS NOT SIZE* , it's the number of items

        // DBX0.0 - fault
        Items[0].Area     = S7AreaDB;
        Items[0].WordLen  = S7WLBit;
        Items[0].DBNumber = _dbNumber;
        Items[0].Start    = 0;
        Items[0].Amount   = 1;
        Items[0].pdata    = &dbStruct->fault;
        // DBX0.1 - fault_ack
        Items[1].Area     = S7AreaDB;
        Items[1].WordLen  = S7WLBit;
        Items[1].DBNumber = _dbNumber;
        Items[1].Start    = 1;
        Items[1].Amount   = 1;
        Items[1].pdata    = &dbStruct->fault_ack;
        // DBX0.2 - product_ok
        Items[2].Area     = S7AreaDB;
        Items[2].WordLen  = S7WLBit;
        Items[2].DBNumber = _dbNumber;
        Items[2].Start    = 2;
        Items[2].Amount   = 1;
        Items[2].pdata    = &dbStruct->part_ok;
        // DBX0.3 - product_ok_ack
        Items[3].Area     = S7AreaDB;
        Items[3].WordLen  = S7WLBit;
        Items[3].DBNumber = _dbNumber;
        Items[3].Start    = 3;
        Items[3].Amount   = 1;
        Items[3].pdata    = &dbStruct->part_ok_ack;
        // DBW2 - fault_number
        Items[4].Area     = S7AreaDB;
        Items[4].WordLen  = S7WLByte;
        Items[4].DBNumber = _dbNumber;
        Items[4].Start    = 1;
        Items[4].Amount   = 1;
        Items[4].pdata    = &dbStruct->fault_number;

        result=S7Client->WriteMultiVars(&Items[0],5);
        _check(result,"Multiwrite Vars");

    } else {
        result = 99;
        emit messageText( "Number of client DB is not set" );
    }
    return result == 0;
}
//------------------------------------------------------------------------------
// Check error
//------------------------------------------------------------------------------
bool Client::_check(int result, const char * function)
{
    if (result==0) {
        ok++;
        emit messageOk(ok);
    } else {
        emit messageText( "Something goes wrong with " + QString::fromStdString( function ));
        ko++;
        emit messageKo(ko);
    }
    return result==0;
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
// Check OK and KO value
//------------------------------------------------------------------------------
void Client::_checkOkKo()
{
    int okAndKo = ok + ko;
    if ( okAndKo >= 1000 ){
        ok = 0;
        ko = 0;
    }
}

