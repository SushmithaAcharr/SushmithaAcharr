/*
 * FansManager.c
 *
 *  Created on: 12-Feb-2024
 *      Author: Sankalp
 */

#include "FansManager.h"
#include "FanControl.h"
#include "UserConfig.h"
#include <stdbool.h>
#include "FanSchedular.h"
#include "TempContol.h"

typedef enum{
	OnRequest,
	OffRequest
}FanRequest_e;


FanRequest_e fan_requests[NUM_OF_UNITS] = {OffRequest, OffRequest, OffRequest, OffRequest};

Fan Fan1(0, BSP_IO_PORT_01_PIN_06, BSP_IO_PORT_01_PIN_12, BSP_IO_PORT_00_PIN_00, BSP_IO_PORT_04_PIN_08);
Fan Fan2(1, BSP_IO_PORT_02_PIN_10, BSP_IO_PORT_01_PIN_09, BSP_IO_PORT_00_PIN_01, BSP_IO_PORT_04_PIN_09);
Fan Fan3(2, BSP_IO_PORT_00_PIN_14, BSP_IO_PORT_01_PIN_11, BSP_IO_PORT_00_PIN_02, BSP_IO_PORT_05_PIN_00);
Fan Fan4(3, BSP_IO_PORT_00_PIN_15, BSP_IO_PORT_01_PIN_10, BSP_IO_PORT_00_PIN_03, BSP_IO_PORT_05_PIN_01);

static Fan *Fans[NUM_OF_UNITS] = {&Fan1, &Fan2, &Fan3, &Fan4};

static int current_primary_fan = -1;
static int current_backup_to_primary_fan = -1;


void FanManagerInit()
{
    Fans[0]->Init();
    Fans[1]->Init();
    Fans[2]->Init();
    Fans[3]->Init();

    TempControlInit();
}

static void SetAllFansOff()
{
    for(int i = 0 ; i < NUM_OF_UNITS; i++){
        //Fans[i]->SetFanValueHandler(FanOff);
        fan_requests[i] = OffRequest;
    }
}

int next_backup = 0;

static void SetAllScheduledFansOn()
{
    for(int i = 0 ; i < NUM_OF_UNITS; i++){
        if(device_config.unit[i].status == 1 && IsFanScheduledToRunNow(i)){
            fan_requests[i] = OnRequest;
            Fans[i]->mode = Scheduled;
            next_backup = (i+1) % NUM_OF_UNITS;
        } else {
            Fans[i]->mode = Backup;
        }
    }
}

static void SetOnlyPrimaryOn()
{
    SetAllFansOff();
    SetAllScheduledFansOn();

    for(int i = 0; i < NUM_OF_UNITS; i++){
        if(fan_requests[i] == OnRequest){
            if(Fans[i]->GetFanState() == UserFanAtFault){
                fan_requests[i] = OffRequest;
                for( int j = 0; j < NUM_OF_UNITS; j++){
                    int fanid = (i+j)%NUM_OF_UNITS;
                    if(device_config.unit[fanid].status == 1 && Fans[fanid]->mode == Backup &&
                            Fans[fanid]->GetFanState() != UserFanAtFault){
                        Fans[fanid]->SetFanValue(FanOn);
                        fan_requests[fanid] = OnRequest;
                        break;
                    }
                }
            }
        }
    }

}

static void SetPrimaryAndOneBackupFan()
{
    SetAllFansOff();
    SetAllScheduledFansOn();
    for(int i = 0 ; i < NUM_OF_UNITS; i++){
        int fanidx = (next_backup + i) % NUM_OF_UNITS;
        if(device_config.unit[fanidx].status == 1 && Fans[fanidx]->mode == Backup){
            fan_requests[fanidx] = OnRequest;
            break;
        }
    }
}

static void SetPrimaryAndTwoBackupFan()
{
    if(NUM_OF_UNITS < 2){
        return;
    }
    int backcnt = 0;
    SetAllFansOff();
    SetAllScheduledFansOn();
    for(int i = 0 ; i < NUM_OF_UNITS; i++){
        int fanidx = (next_backup + i) % NUM_OF_UNITS;
        if(device_config.unit[fanidx].status == 1 && Fans[fanidx]->mode == Backup){
            fan_requests[fanidx] = OnRequest;
            backcnt++;
            if(backcnt == 2){
                break;
            }
        }
    }
}

static void SetAllFansOn()
{
    SetAllFansOff();
    for(int i = 0 ; i < NUM_OF_UNITS; i++){
        if(device_config.unit[i].status == 1){
            fan_requests[i] = OnRequest;
        }
    }
}

TemperatureControlStates_e current_temperature_state = UnknownLevel;

void RunAllFanSM()
{
    if(device_config.fan_control_mode == 1){
        TemperatureControlStates_e temperature_state = GetTemperatureState();
        switch(temperature_state)
        {
        case BelowLowTemp:
            SetAllFansOff();
            break;
        case AboveTemp:
            SetOnlyPrimaryOn();
            break;
        case CriticalLevel1:
            SetPrimaryAndOneBackupFan();
            break;
        case CriticalLevel2:
            SetPrimaryAndTwoBackupFan();
            break;
        case CriticalLevel3:
            SetAllFansOn();
            break;
        default:
            break;
        }
        current_temperature_state = temperature_state;
    } else {
        SetOnlyPrimaryOn();
    }
    for(int i = 0; i < NUM_OF_UNITS; i++){
        if(fan_requests[i] == OnRequest){
            Fans[i]->SetFanValue(FanOn);
        } else {
            Fans[i]->SetFanValue(FanOff);
        }
        Fans[i]->RunFanSM();
    }

}

