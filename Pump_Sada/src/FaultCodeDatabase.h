/*
 * FaultCodeDatabase.h
 *
 *  Created on: 31-Mar-2024
 *      Author: Sankalp
 */

#ifndef FAULTCODEDATABASE_H_
#define FAULTCODEDATABASE_H_

#include <stdint.h>
#include "AlarmManager.h"

typedef struct{
    uint8_t day;
    uint8_t mon;
    uint8_t year;
    uint8_t hr;
    uint8_t min;
    uint8_t sec;
    uint16_t fault_code;
}FaultCodeDbEntry_t;

void AddAlarmToDataBase(AlarmPopUp_e alm);
void InitAlarmDataBase();
FaultCodeDbEntry_t* GetFirstEntry(uint8_t startingpage);
FaultCodeDbEntry_t* GetNextEntry();

AlarmPopUp_e GetLastAlarm();
void EraseFaultDataBase();

#endif /* FAULTCODEDATABASE_H_ */
