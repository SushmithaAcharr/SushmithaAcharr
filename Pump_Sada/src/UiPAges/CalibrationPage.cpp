/*
 * CalibrationPage.cpp
 *
 *  Created on: 28-Apr-2024
 *      Author: Sankalp
 */




#include "CalibrationPage.h"
#include "UI.h"
#include "UIVPAddresses.h"
#include "ConfigManager.h"
#include "TempContol.h"

extern char* get_offset_string();
static volatile int ref_temp;
bool need_to_reread = true;

void CalibrationPage::PageInit()
{
    UpdateStringField(TEMP_CALIBRATION_FILELD, get_offset_string(), 3);
}
void CalibrationPage::PageReadEventHandler(DisplayMsg_t * rsp)
{
    switch(rsp->address){
        case REFERNECE_TEMP_VALUE:
            {
                if(need_to_reread == false){
                    ref_temp = (rsp->data[0] >> 8) - 0x30;
                    ref_temp *= 10;
                    ref_temp += ((rsp->data[0] & 0xFF ) - 0x30);
                    ref_temp *= 10;
                    ref_temp += (rsp->data[1] >> 8) - 0x30;
                } else {
                    need_to_reread = false;
                    ReadField(REFERNECE_TEMP_VALUE);
                }
            }
            break;
        case SAVE_SETTING_BUTTON:
            if(rsp->data[0] == CALC_TEMP_OFFSET){
                device_config.temp_offset = 0; // reset current offset
                device_config.temp_offset = ref_temp - GetCurrentTemp();
                UpdateStringField(TEMP_CALIBRATION_FILELD, get_offset_string(), 3);
            }
            break;
        default:
            break;
    }

    return;
}
void CalibrationPage::PageReadEventHandlerTick()
{
    return;
}
void CalibrationPage::PageWriteAckedEventHandler()
{
    return;
}




