/*
 * UnitSettingPage.cpp
 *
 *  Created on: 29-Mar-2024
 *      Author: Sankalp
 */
#include "UnitSettingPage.h"
#include "ConfigManager.h"

typedef enum{
    ReadingSelectedUnit,
    UpdatingSelectedUnitStatus,
    UpdatingSelectedUnitOnTimeHr,
    UpdatingSelectedUnitOnTimeMin,
    UpdatingSelectedUnitOnTimeSec,
    UpdatingSelectedUnitOffTimeHr,
    UpdatingSelectedUnitOffTimeMin,
    UpdatingSelectedUnitOffTimeSec,
    UpdatingActDelay,
    UnitSettingIdle
}UnitSettingPageState_e;

uint16_t unit_selected = 0;
UnitSettingPageState_e unitcfgstate = UnitSettingIdle;

void SendGetSelectedUnitNum()
{
    txmsg.cmd = READ_DATA_FROM_ADDRES;
    txmsg.address = UNIT_SELECTED_FIELD;
    txmsg.reg_cnt = 1;
    unitcfgstate = ReadingSelectedUnit;
    xQueueSend(display_tx_que, &txmsg, 0);
}

void SendUnitStatus()
{
    UpdateField(UNIT_ENABLED_RADIO_FIELD, device_config.unit[unit_selected].status);
}

void UpdateUnitInfo()
{
    unitcfgstate = UpdatingSelectedUnitStatus;
    SendUnitStatus();
}

void UnitSettingPage::PageInit()
{
    SendGetSelectedUnitNum();
}
void UnitSettingPage::PageReadEventHandler(DisplayMsg_t * rsp)
{
    switch(rsp->address){
        case UNIT_SELECTED_FIELD:
            unit_selected = rsp->data[0];
            UpdateUnitInfo();
            break;
        case UNIT_ENABLED_RADIO_FIELD:
            device_config.unit[unit_selected].status = rsp->data[0];
            break;
        case UNIT_ON_HH_CHANGED:
            device_config.unit[unit_selected].schedule.on_time.hr = rsp->data[0];
            break;
        case UNIT_ON_MM_CHANGED:
            device_config.unit[unit_selected].schedule.on_time.min = rsp->data[0];
            break;
        case UNIT_ON_SS_CHANGED:
            device_config.unit[unit_selected].schedule.on_time.sec = rsp->data[0];
            break;
        case UNIT_OFF_HH_CHANGED:
            device_config.unit[unit_selected].schedule.off_time.hr = rsp->data[0];
            break;
        case UNIT_OFF_MM_CHANGED:
            device_config.unit[unit_selected].schedule.off_time.min = rsp->data[0];
            break;
        case UNIT_OFF_SS_CHANGED:
            device_config.unit[unit_selected].schedule.off_time.sec = rsp->data[0];
            break;
        case UNIT_ACT_DELAY_FIELD:
            device_config.unit[unit_selected].act_delay = rsp->data[0];
            break;
    }

    return;
}
void UnitSettingPage::PageReadEventHandlerTick()
{
    return;
}


void UnitSettingPage::PageWriteAckedEventHandler()
{
    switch(unitcfgstate){
        case UpdatingSelectedUnitStatus:
            UpdateField(UNIT_ON_HH_CHANGED, device_config.unit[unit_selected].schedule.on_time.hr);
            unitcfgstate = UpdatingSelectedUnitOnTimeHr;
            break;
        case UpdatingSelectedUnitOnTimeHr:
            UpdateField(UNIT_ON_MM_CHANGED, device_config.unit[unit_selected].schedule.on_time.min);
            unitcfgstate = UpdatingSelectedUnitOnTimeMin;
            break;
        case UpdatingSelectedUnitOnTimeMin:
            UpdateField(UNIT_ON_SS_CHANGED, device_config.unit[unit_selected].schedule.on_time.min);
            unitcfgstate = UpdatingSelectedUnitOnTimeSec;
            break;
        case UpdatingSelectedUnitOnTimeSec:
            UpdateField(UNIT_OFF_HH_CHANGED, device_config.unit[unit_selected].schedule.off_time.hr);
            unitcfgstate = UpdatingSelectedUnitOffTimeHr;
            break;
            break;
        case UpdatingSelectedUnitOffTimeHr:
            UpdateField(UNIT_OFF_MM_CHANGED, device_config.unit[unit_selected].schedule.off_time.min);
            unitcfgstate = UpdatingSelectedUnitOffTimeMin;
            break;
        case UpdatingSelectedUnitOffTimeMin:
            UpdateField(UNIT_OFF_SS_CHANGED, device_config.unit[unit_selected].schedule.off_time.sec);
            unitcfgstate = UpdatingSelectedUnitOffTimeSec;
            break;
        case UpdatingSelectedUnitOffTimeSec:
            UpdateField(UNIT_ACT_DELAY_FIELD, device_config.unit[unit_selected].act_delay);
            unitcfgstate = UpdatingActDelay;
            break;

        case UpdatingActDelay:
            unitcfgstate = UnitSettingIdle;
            break;
        default:
            break;
    }

    return;
}



