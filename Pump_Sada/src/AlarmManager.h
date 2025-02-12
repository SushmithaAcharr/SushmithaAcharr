/*
 * AlarmManager.h
 *
 *  Created on: 27-Feb-2024
 *      Author: Sankalp
 */

#ifndef ALARMMANAGER_H_
#define ALARMMANAGER_H_

typedef enum{
    NoAlarm,
    FireActivatedAlarm,
    Unit1FailedAlarm,
    Unit2FailedAlarm,
    Unit3FailedAlarm,
    Unit4FailedAlarm,
    UnitPowerFailedAlarm,
    HighTempAlarm,
    LowTempAlarm,
    TempSensosrFailedAlarm,
    RS485CommErrorAlarm,
}AlarmPopUp_e;

void RunAlarmMaganagerStateMachine();
void AlarmManagernit();
void MuteBuzzer();

AlarmPopUp_e GetCurrnetAlarmState();

bool IsInAlarmState();



#endif /* ALARMMANAGER_H_ */
