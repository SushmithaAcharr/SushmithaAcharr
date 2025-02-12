/*
 * TempContol.h
 *
 *  Created on: 13-Feb-2024
 *      Author: Sankalp
 */

#ifndef TEMPCONTOL_H_
#define TEMPCONTOL_H_

#include <stdint.h>

typedef enum {
	BelowLowTemp,
	AboveTemp,
	CriticalLevel1,
	CriticalLevel2,
	CriticalLevel3,
	SensorFailed,
	UnknownLevel
}TemperatureControlStates_e;

typedef enum{
    SensorStateGood,
    SensorAtFault
}TempSensorState_e;

TemperatureControlStates_e GetTemperatureState();

uint16_t GetCurrentTemp();
TempSensorState_e GetSensorState();
void ReadTemperature();
void TempControlInit();


#endif /* TEMPCONTOL_H_ */
