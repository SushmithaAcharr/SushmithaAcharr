/*
 * FaultHistPage.cpp
 *
 *  Created on: 20-Apr-2024
 *      Author: Sankalp
 */

#include "FaultHistPage.h"
#include "FaultCodeDatabase.h"
#include "UI.h"
#include "UIVPAddresses.h"
#include <stdio.h>

typedef enum{
    ReadFaultPageNum,
    ClearFirstEntry,
    ClearSecondEntry,
    ClearThirdEntry,
    SendingFirstEntry,
    SendingSecondEntry,
    SendingThirdEntry,
    FaultHistIdle,
}FaultHistState_e;

#define FAULT_EMPTY_STRING  ("                                    ")
char FaultString[FAULT_STRING_LEN + 1];
static FaultCodeDbEntry_t* entry = NULL;
static FaultHistState_e fault_hist_state = FaultHistIdle;
static uint8_t pagenum = 0;
static char* GetStringForFault(AlarmPopUp_e code)
{
    char * ret = "";
    switch (code){
        case FireActivatedAlarm:
            ret = "ExtFireAlarm    ";
            break;
        case Unit1FailedAlarm:
            ret = "Unit1Failed     ";
            break;
        case Unit2FailedAlarm:
            ret = "Unit2Failed     ";
            break;
        case Unit3FailedAlarm:
            ret = "Unit3Failed     ";
            break;
        case Unit4FailedAlarm:
            ret = "Unit4Failed     ";
            break;
        case UnitPowerFailedAlarm:
            ret = "UnitPowerFailed ";
            break;
        case HighTempAlarm:
            ret = "HighTemp        ";
            break;
        case LowTempAlarm:
            ret = "LowTemp         ";
            break;
        case TempSensosrFailedAlarm:
            ret = "TempSensorFailed";
            break;
        case RS485CommErrorAlarm:
            ret = "CommError      ";
            break;
    }
    return ret;
}

static char* GetFirstFieldString()
{
    entry = GetFirstEntry(pagenum);
    if(entry != NULL){
        snprintf(FaultString, sizeof(FaultString), "%02d/%02d/%02d - %02d:%02d:%02d %s", entry->day, entry->mon,
                                                 entry->year,entry->hr, entry->min, entry->sec,
                                                 GetStringForFault((AlarmPopUp_e)entry->fault_code));
    } else {
        strcpy(FaultString, FAULT_EMPTY_STRING);
    }

    return FaultString;
}

static char* GetSecondFieldString()
{
    entry = GetNextEntry();

    if(entry != NULL){
        snprintf(FaultString, sizeof(FaultString), "%02d/%02d/%02d - %02d:%02d:%02d %s", entry->day, entry->mon,
                                                 entry->year,entry->hr, entry->min, entry->sec,
                                                 GetStringForFault((AlarmPopUp_e)entry->fault_code));
    } else {
        strcpy(FaultString, FAULT_EMPTY_STRING);
    }
    return FaultString;
}

static char* GetThirdFieldString()
{
    entry = GetNextEntry();

    if(entry != NULL){
        snprintf(FaultString, sizeof(FaultString), "%02d/%02d/%02d - %02d:%02d:%02d %s", entry->day, entry->mon,
                                                 entry->year,entry->hr, entry->min, entry->sec,
                                                 GetStringForFault((AlarmPopUp_e)entry->fault_code));
    } else {
        strcpy(FaultString, FAULT_EMPTY_STRING);
    }
    return FaultString;
}

void FaultHistPage::PageInit()
{
    pagenum = 0;
    fault_hist_state = ReadFaultPageNum;
    ReadField(FAULT_PAGE_NUMBER);
}
void FaultHistPage::PageReadEventHandler(DisplayMsg_t * rsp)
{
    switch(rsp->address){
        case FAULT_PAGE_NUMBER:
            pagenum = (uint8_t)rsp->data[0];
            UpdateStringField(FAULT_FIRST_ENTRY, FAULT_EMPTY_STRING, FAULT_STRING_LEN);
            fault_hist_state = ClearFirstEntry;
            break;
        default:
            break;
    }

    return;
}
void FaultHistPage::PageReadEventHandlerTick()
{
    return;
}
void FaultHistPage::PageWriteAckedEventHandler()
{
    switch(fault_hist_state){
        case ReadFaultPageNum:
            //UpdateStringField(FAULT_FIRST_ENTRY, GetFirstFieldString(), FAULT_STRING_LEN);
            //fault_hist_state = SendingFirstEntry;
            break;
        case ClearFirstEntry:
            UpdateStringField(FAULT_SECOND_ENTRY, FAULT_EMPTY_STRING, FAULT_STRING_LEN);
            fault_hist_state = ClearSecondEntry;
            break;
        case ClearSecondEntry:
            UpdateStringField(FAULT_SECOND_ENTRY, FAULT_EMPTY_STRING, FAULT_STRING_LEN);
            fault_hist_state = ClearThirdEntry;
            break;
        case ClearThirdEntry:
            UpdateStringField(FAULT_FIRST_ENTRY, GetFirstFieldString(), FAULT_STRING_LEN);
            fault_hist_state = SendingFirstEntry;
            break;
        case SendingFirstEntry:
            UpdateStringField(FAULT_SECOND_ENTRY, GetSecondFieldString(), FAULT_STRING_LEN);
            fault_hist_state = SendingSecondEntry;
            break;
        case SendingSecondEntry:
            UpdateStringField(FAULT_THIRD_ENTRY, GetThirdFieldString(), FAULT_STRING_LEN);
            fault_hist_state = SendingThirdEntry;
            break;
        case SendingThirdEntry:
            fault_hist_state = FaultHistIdle;
            break;
        case FaultHistIdle:
            break;
    }
    return;
}

