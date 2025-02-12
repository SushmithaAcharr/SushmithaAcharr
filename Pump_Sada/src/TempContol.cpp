/*
 * TempContol.c
 *
 *  Created on: 13-Feb-2024
 *      Author: Sankalp
 */
#include "FanControl.h"
#include "UserConfig.h"
#include <stdbool.h>
#include <FansManager.h>
#include "MAX31865.h"
#include "TempContol.h"
#include <cmath>
#include "TempHysterisis.h"


uint16_t current_temp = 0;
static TempSensorState_e current_state = SensorStateGood;
TemperatureControlStates_e temperature_state = BelowLowTemp;

TempHysterisis low;
TempHysterisis crit1;
TempHysterisis crit2;
TempHysterisis crit3;

static int ticks;

void TempControlInit()
{
    low.Init(device_config.low_temp, device_config.temp_tolerence);
    crit1.Init(device_config.critical_temp1, device_config.temp_tolerence);
    crit2.Init(device_config.critical_temp2, device_config.temp_tolerence);
    crit3.Init(device_config.critical_temp3, device_config.temp_tolerence);

    ticks = xTaskGetTickCount();
}

void ReadTemperature()
{
    float tempf;
    if(Max31865_readTempC(&tempf) == true){
        tempf *= 10;
        int temp = (int)round(tempf);
        current_temp = (uint16_t) temp;
        current_state = SensorStateGood;
    }else {
        current_temp = 0;
        current_state = SensorAtFault;
    }
}




TemperatureControlStates_e GetTemperatureState()
{
    uint16_t temp = GetCurrentTemp();
	TemperatureControlStates_e ret = BelowLowTemp;
	if(current_state != SensorAtFault){
        if(crit3.GetActionToDo(temp)){
            ret = CriticalLevel3;
        }else if(crit2.GetActionToDo(temp)){
            ret = CriticalLevel2;
        }else if(crit1.GetActionToDo(temp)){
            ret = CriticalLevel1;
        }else if(low.GetActionToDo(temp)){
            ret = AboveTemp;
        } else {
            ret = BelowLowTemp;
        }
	}else {
        current_state = SensorAtFault;
        ret = SensorFailed;
    }
	return ret;

}


uint16_t GetCurrentTemp()
{

    if(simulate_setup.simulate == 0){
        return current_temp  + device_config.temp_offset;
    } else {
        return (simulate_setup.simtemp*10);
    }
}

TempSensorState_e GetSensorState()
{
    return current_state;
}
