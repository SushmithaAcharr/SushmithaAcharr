/*
 * AlarmManager.cpp
 *
 *  Created on: 27-Feb-2024
 *      Author: Sankalp
 */

#include "AlarmManager.h"
#include "FansManager.h"
#include "TempContol.h"
#include "ConfigManager.h"
#include "UI.h"
#include "UiPAges/AlertPage.h"
#include "TempHysterisis.h"
#include "FaultCodeDatabase.h"
#

#ifdef __cplusplus
    extern "C"{
        #include "hal_data.h"
    }
#endif


typedef enum{
    AlaemManagerInitialWait,
    AlarmManagerIdle,
    AlarmManagerInAlarm,
    AlarmManagerSnoozing
}AlarmState_e;

extern AlertPage   alertPage;

static AlarmState_e alarm_mgr_state = AlaemManagerInitialWait;
static AlarmPopUp_e current_alarm_screen = NoAlarm;
static TickType_t mute_start_time = 0;

static void ShowAlarmScreen(AlarmPopUp_e alm)
{
    switch(alm){
        case NoAlarm:
            break;
        case FireActivatedAlarm:
            alertPage.ShowAlert(ExtFireAlert);
            break;
        case Unit1FailedAlarm:
            alertPage.ShowAlert(Unit1FailedAlert);
            break;
        case Unit2FailedAlarm:
            alertPage.ShowAlert(Unit2FailedAlert);
            break;
        case Unit3FailedAlarm:
            alertPage.ShowAlert(Unit3FailedAlert);
            break;
        case Unit4FailedAlarm:
            alertPage.ShowAlert(Unit4FailedAlert);
            break;
        case UnitPowerFailedAlarm:
            alertPage.ShowAlert(UnitPowerFailAlert);
            break;
        case HighTempAlarm:
            alertPage.ShowAlert(HighTempAlert);
            break;
        case LowTempAlarm:
            alertPage.ShowAlert(LowTempAlert);
            break;
        case TempSensosrFailedAlarm:
            alertPage.ShowAlert(TempSensorAlert);
            break;
        case RS485CommErrorAlarm:
            alertPage.ShowAlert(RS485CommErrorAlert);
            break;
    }
}

void BuzzTheBuzzer()
{
    switch (current_alarm_screen){
        case NoAlarm:
        case LowTempAlarm:
            R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_02_PIN_05, BSP_IO_LEVEL_LOW);
            break;
        case FireActivatedAlarm:
        case Unit1FailedAlarm:
        case Unit2FailedAlarm:
        case Unit3FailedAlarm:
        case Unit4FailedAlarm:
        case UnitPowerFailedAlarm:
        case HighTempAlarm:
        case TempSensosrFailedAlarm:
        case RS485CommErrorAlarm:
            if(device_config.buzzer_enable == 1 && alarm_mgr_state != AlarmManagerSnoozing){
                R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_02_PIN_05, BSP_IO_LEVEL_HIGH);
            } else {
                R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_02_PIN_05, BSP_IO_LEVEL_LOW);
            }
            break;
    }
}

void MuteBuzzer()
{
    mute_start_time = xTaskGetTickCount();
    alarm_mgr_state = AlarmManagerSnoozing;
}

static AlarmPopUp_e CheckForAlarms();
int ticksfromstart = 0;

void AlarmManagernit()
{
    ticksfromstart = xTaskGetTickCount();
    alarm_mgr_state = AlaemManagerInitialWait;
}

bool IsInAlarmState()
{
    return (alarm_mgr_state == AlarmManagerInAlarm || alarm_mgr_state == AlarmManagerSnoozing);
}

void RunAlarmMaganagerStateMachine()
{
    AlarmPopUp_e alarm = CheckForAlarms();
    switch (alarm_mgr_state){
        case AlaemManagerInitialWait:
            {
                int currenttick = xTaskGetTickCount();
                if((currenttick - ticksfromstart) >= 30000){
                    alarm_mgr_state = AlarmManagerIdle;
                }
            }
            break;
        case AlarmManagerIdle:
            if(NoAlarm != alarm){
                current_alarm_screen = alarm;
                AddAlarmToDataBase(alarm);
                ShowAlarmScreen(alarm);
                alarm_mgr_state = AlarmManagerInAlarm;
            }
            break;
        case AlarmManagerInAlarm:
            {
                if(alarm == NoAlarm){
                    alertPage.ClearAlert();
                    ShowPage(DashBoardPageId);
                    alarm_mgr_state = AlarmManagerIdle;
                } else if(alarm != current_alarm_screen){
                    current_alarm_screen = alarm;
                    AddAlarmToDataBase(alarm);
                    ShowAlarmScreen(alarm);
                    alarm_mgr_state = AlarmManagerInAlarm;
                }
            }
            break;
        case AlarmManagerSnoozing:
            if(alarm == NoAlarm){
                alertPage.ClearAlert();
                ShowPage(DashBoardPageId);
                alarm_mgr_state = AlarmManagerIdle;
            } else if(alarm != current_alarm_screen){
                current_alarm_screen = alarm;
                AddAlarmToDataBase(alarm);
                ShowAlarmScreen(alarm);
                alarm_mgr_state = AlarmManagerInAlarm;
            }
            if((xTaskGetTickCount() - mute_start_time) > (device_config.snooze_time * 60 * 1000)){
                ShowAlarmScreen(alarm);
                alarm_mgr_state = AlarmManagerInAlarm;
            }
            break;
    }
    BuzzTheBuzzer();
}

AlarmPopUp_e CheckForAlarms()
{
    bsp_io_level_t level= BSP_IO_LEVEL_LOW;

    AlarmPopUp_e alarm = NoAlarm;

    TemperatureControlStates_e tempstate = GetTemperatureState();

    R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_02_PIN_06, &level);
    if(level == BSP_IO_LEVEL_LOW){
        alarm = FireActivatedAlarm;
    } else if(GetSensorState() == SensorAtFault){
        alarm = TempSensosrFailedAlarm;
    } else if(tempstate == CriticalLevel3){
        alarm = HighTempAlarm;
    } else if(Fan1.GetFanState() == UserFanAtFault){
        alarm = Unit1FailedAlarm;
    }else if(Fan2.GetFanState() == UserFanAtFault){
        alarm = Unit2FailedAlarm;
    }else if(Fan3.GetFanState() == UserFanAtFault){
        alarm = Unit3FailedAlarm;
    }else if(Fan4.GetFanState() == UserFanAtFault){
        alarm = Unit4FailedAlarm;
    } else if(tempstate == BelowLowTemp){
        alarm = LowTempAlarm;
    }

    return alarm;
}

AlarmPopUp_e GetCurrnetAlarmState()
{
    return current_alarm_screen;
}

