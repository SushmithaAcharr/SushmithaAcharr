/*
 * MiscSettingsPage.cpp
 *
 *  Created on: 29-Mar-2024
 *      Author: Sankalp
 */

#include "MiscSettingsPage.h"
#include "UI.h"
#include "ConfigManager.h"
#include "TempContol.h"

typedef enum{
    UpdatingFanControlMode,
    UpdatingTempCalibration,
    UpdatingLCDBrightness,
    MiscIdle
}MiscSettingsPageState_e;

static MiscSettingsPageState_e miscpagestate = MiscIdle;
static char temp_offset_str[3+1];
#define TEMP_OFFSET_LOWER_LIMIT   (-99)
#define TEMP_OFFSET_UPPER_LIMIT   (99)
char* get_offset_string()
{
    int16_t val = device_config.temp_offset;
    if(device_config.temp_offset < TEMP_OFFSET_LOWER_LIMIT || device_config.temp_offset > TEMP_OFFSET_UPPER_LIMIT){
        temp_offset_str[0] = '-';
        temp_offset_str[1] = '-';
        temp_offset_str[2] = '-';
        temp_offset_str[3] = 0;
    }else{
        if(device_config.temp_offset < 0){
            temp_offset_str[0] = '-';
            val *= -1;
        } else {
            temp_offset_str[0] = ' ';
        }

        temp_offset_str[1] = (char)((val /10)+ 0x30);
        temp_offset_str[2] = (char)((val%10) + 0x30);
        temp_offset_str[3] = 0;
    }
    return temp_offset_str;
}



void MiscSettingsPage::PageInit()
{
    UpdateStringField(TEMP_CALIBRATION_FILELD, get_offset_string(), 3);
    miscpagestate = UpdatingTempCalibration;
}

void MiscSettingsPage::PageReadEventHandler(DisplayMsg_t * rsp)
{
    switch(rsp->address){
        case TEMP_CALIBRATION_FILELD:{
            uint16_t curtemp = GetCurrentTemp();
            device_config.temp_offset = (ConvertAsciiToNum(rsp->data[0])*10) - curtemp;
        }
            break;
        case FAN_CTRL_MODE_FIELD:
            device_config.fan_control_mode = rsp->data[0]-1;
            break;
        case LED_BRIGHTNESS_FIELD:
            device_config.backlight_mode = ((rsp->data[0] >> 8) & 0x00FF);
            break;
    }

    return;
}
void MiscSettingsPage::PageReadEventHandlerTick()
{
    return;
}


void MiscSettingsPage::PageWriteAckedEventHandler()
{
    switch(miscpagestate){
        case UpdatingTempCalibration:
            UpdateField(FAN_CTRL_MODE_FIELD, device_config.fan_control_mode+1);
            miscpagestate = UpdatingFanControlMode;
            break;
        case UpdatingFanControlMode:
            //UpdateField(LED_BRIGHTNESS_FIELD, device_config.backlight_mode);
            SetLCDBrightness(device_config.backlight_mode);
            miscpagestate = MiscIdle;
            break;
        case MiscIdle:
            break;
    }
    return;
}





