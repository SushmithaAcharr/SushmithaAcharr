/*
 * TempSettingsPage.cpp
 *
 *  Created on: 13-Mar-2024
 *      Author: Sankalp
 */

#include "TempSettingsPage.h"
#include "UserConfig.h"

typedef enum{
    UpdatingLowTempState,
    UpdatingBuzzTempState,
    UpdatingDifferentTempState,
    UpdatingCrit1TempState,
    UpdatingCrit2TempState,
    UpdatingCrit3TempState,
    MaxTempState
}DashboardStates_e;

static DashboardStates_e state = MaxTempState;

static void UpdateTemperature(uint16_t addr, uint16_t val)
{
    txmsg.cmd = WRITE_DATA_TO_ADDRES;
    txmsg.address = (uint16_t)addr;
    txmsg.reg_cnt = 1;
    txmsg.data[0] = val;

    xQueueSend(display_tx_que, &txmsg, 0);
}

void TempSettingsPage::PageInit()
{
    UpdateTemperature(LOW_TEMP_FIELD, device_config.low_temp);
    state = UpdatingLowTempState;
}
void TempSettingsPage::PageReadEventHandler(DisplayMsg_t * rsp)
{
    uint16_t val = rsp->data[0];
    switch(rsp->address)
    {
        case LOW_TEMP_FIELD:
            device_config.low_temp = val;
            break;
        case BUZZ_TEMP_FIELD:
            device_config.act_buzzer_temp = val;
            break;
        case TEMP_THRESHOLD_FIELD:
            device_config.temp_tolerence = val;
            break;
        case CT1_TEMP_FIELD:
            device_config.critical_temp1 = val;
            break;
        case CT2_TEMP_FIELD:
            device_config.critical_temp2 = val;
            break;
        case CT3_TEMP_FIELD:
            device_config.critical_temp3 = val;
            break;
        case SAVE_SETTING_BUTTON:
            ShowPage(SettingsPageId);
            break;
        default:
            break;
    }
    return;
}
void TempSettingsPage::PageReadEventHandlerTick()
{
    return;
}
void TempSettingsPage::PageWriteAckedEventHandler()
{
    switch(state){
        case UpdatingLowTempState:
            UpdateTemperature((uint16_t)BUZZ_TEMP_FIELD, device_config.act_buzzer_temp);
            state = UpdatingBuzzTempState;
            break;
        case UpdatingBuzzTempState:
            UpdateTemperature((uint16_t)TEMP_THRESHOLD_FIELD, device_config.temp_tolerence);
            state = UpdatingDifferentTempState;
            break;
        case UpdatingDifferentTempState:
            UpdateTemperature((uint16_t)CT1_TEMP_FIELD, device_config.critical_temp1);
            state = UpdatingCrit1TempState;
            break;
        case UpdatingCrit1TempState:
            UpdateTemperature((uint16_t)CT2_TEMP_FIELD, device_config.critical_temp2);
            state = UpdatingCrit2TempState;
            break;
        case UpdatingCrit2TempState:
            UpdateTemperature((uint16_t)CT3_TEMP_FIELD, device_config.critical_temp3);
            state = UpdatingCrit3TempState;
            break;
        case UpdatingCrit3TempState:
            state = MaxTempState;
            break;
        default:
            break;
    }
    return;
}
