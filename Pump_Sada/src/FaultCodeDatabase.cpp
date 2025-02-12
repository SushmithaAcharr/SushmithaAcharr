/*
 * FaultCodeDatabase.cpp
 *
 *  Created on: 31-Mar-2024
 *      Author: Sankalp
 */

#include <time.h>
#include "ConfigManager.h"
#include "r_rtc.h"
#include "FaultCodeDatabase.h"
#include "FlashStorage.h"

#define MAX_FAULT_CODE_CNT          (20)
#define FAULT_CODE_DB_MAGIC_WORD    (0xBAD0)



typedef struct{
    uint16_t db_magic_word;
    FaultCodeDbEntry_t entries[MAX_FAULT_CODE_CNT];
    uint8_t next_entry;
    uint8_t oldest_entry;
}FaultCodeDb_t;


static FaultCodeDb_t FaultDbRAMCopy;
static int current_index;
static int num_of_entries = 0;
extern FlashStorage storage;
extern rtc_instance_ctrl_t g_rtc0_ctrl;
static rtc_time_t rtc_time;
static void GetDateTime(AspTime_t *t, AspDate_t *d)
{
    R_RTC_CalendarTimeGet(&g_rtc0_ctrl, &rtc_time);
    t->hr = (int8_t)rtc_time.tm_hour;
    t->min = (int8_t)rtc_time.tm_min;
    t->sec = (int8_t)rtc_time.tm_sec;

    d->day = (int8_t)rtc_time.tm_mday;
    d->month = (int8_t)rtc_time.tm_mon;
    d->year = (int8_t)rtc_time.tm_year%100;

}
static void SetFaultDbToEmpty()
{
    FaultDbRAMCopy.next_entry = 0;
    FaultDbRAMCopy.oldest_entry = MAX_FAULT_CODE_CNT;
    for(int i = 0; i < MAX_FAULT_CODE_CNT; i++){
        FaultDbRAMCopy.entries[i].fault_code = NoAlarm;
    }

}

void AddAlarmToDataBase(AlarmPopUp_e alm)
{
    AspTime_t t;
    AspDate_t d;

    GetDateTime(&t, &d);
    FaultCodeDbEntry_t * entry = &FaultDbRAMCopy.entries[FaultDbRAMCopy.next_entry];
    entry->day = d.day;
    entry->mon = d.month;
    entry->year = d.year;
    entry->hr = t.hr;
    entry->min = t.min;
    entry->sec = t.sec;
    entry->fault_code = alm;

    if(FaultDbRAMCopy.oldest_entry == MAX_FAULT_CODE_CNT){
        FaultDbRAMCopy.oldest_entry = 0;
    } else if(FaultDbRAMCopy.oldest_entry == FaultDbRAMCopy.next_entry){
        FaultDbRAMCopy.oldest_entry++;
        if(FaultDbRAMCopy.oldest_entry >= MAX_FAULT_CODE_CNT){
            FaultDbRAMCopy.oldest_entry = 0;
        }
    }
    FaultDbRAMCopy.next_entry++;
    if(FaultDbRAMCopy.next_entry >= MAX_FAULT_CODE_CNT){
        FaultDbRAMCopy.next_entry = 0;
    }
    FaultDbRAMCopy.db_magic_word = FAULT_CODE_DB_MAGIC_WORD;
    storage.WriteFaultDatabase((uint8_t*)&FaultDbRAMCopy,  sizeof(FaultDbRAMCopy));
}

AlarmPopUp_e GetLastAlarm()
{
    uint8_t idx = FaultDbRAMCopy.next_entry -1;
    if(idx > MAX_FAULT_CODE_CNT){
        idx = MAX_FAULT_CODE_CNT - 1;
    }
    FaultDbRAMCopy.entries[idx].fault_code;
}

void EraseFaultDataBase()
{
    SetFaultDbToEmpty();
    FaultDbRAMCopy.db_magic_word = FAULT_CODE_DB_MAGIC_WORD;
    storage.WriteFaultDatabase((uint8_t*)&FaultDbRAMCopy,  sizeof(FaultDbRAMCopy));
}


void InitAlarmDataBase()
{
    storage.ReadFaultDatabase((uint8_t*)&FaultDbRAMCopy, sizeof(FaultDbRAMCopy));
    if(FaultDbRAMCopy.db_magic_word != FAULT_CODE_DB_MAGIC_WORD){
        SetFaultDbToEmpty();
    }

}
#define NUM_OF_FAULTS_PER_PAGE      (3)
FaultCodeDbEntry_t* GetFirstEntry(uint8_t startingpage)
{

    uint8_t entriestoskip = (startingpage-1) * NUM_OF_FAULTS_PER_PAGE;

    FaultCodeDbEntry_t* ret = NULL;
    uint8_t oldest = FaultDbRAMCopy.oldest_entry;
    uint8_t next = FaultDbRAMCopy.next_entry;
    current_index = (oldest == MAX_FAULT_CODE_CNT) ? 0 : oldest;

    num_of_entries =  (oldest < next) ? (next - oldest) : (MAX_FAULT_CODE_CNT - oldest + next);

    current_index += entriestoskip;
    num_of_entries -= entriestoskip;
    if(current_index > MAX_FAULT_CODE_CNT){
        current_index -= MAX_FAULT_CODE_CNT;
    }

    if(FaultDbRAMCopy.entries[current_index].fault_code != NoAlarm){
        ret = &FaultDbRAMCopy.entries[current_index];
        num_of_entries--;
    }
    return ret;
}

FaultCodeDbEntry_t* GetNextEntry()
{
    if(num_of_entries <= 0){
        return NULL;
    }
    num_of_entries--;
    current_index++;
    if(current_index >= MAX_FAULT_CODE_CNT){
        current_index = 0;
    }
    FaultCodeDbEntry_t* ret = NULL;
    if(current_index < MAX_FAULT_CODE_CNT && FaultDbRAMCopy.entries[current_index].fault_code != NoAlarm){
        ret = &FaultDbRAMCopy.entries[current_index];
    }
    return ret;
}




