/*
 * BuzzerSettingPage.cpp
 *
 *  Created on: 29-Mar-2024
 *      Author: Sankalp
 */

#include "BuzzerSettingPage.h"
#include "UI.h"
#include "ConfigManager.h"

typedef enum{
    BuzzerUpdatingEnable,
    BuzzerUpdatingSnooze,
    BuzzerIdle
}BuzzerSettingPageState_e;

static BuzzerSettingPageState_e buzzerpagestate = BuzzerIdle;



void BuzzerSettingPage::PageInit()
{
    UpdateField(BUZZER_ENABLE_FIELD, device_config.buzzer_enable );
    buzzerpagestate = BuzzerUpdatingEnable;
}

void BuzzerSettingPage::PageReadEventHandler(DisplayMsg_t * rsp)
{
    switch(rsp->address){
        case BUZZER_ENABLE_FIELD:
            device_config.buzzer_enable = rsp->data[0];
            break;
        case BUZZER_SNOOZE_FIELD:
            device_config.snooze_time = ConvertAsciiToNum(rsp->data[0]);
            break;
        case SAVE_SETTING_BUTTON:
            ShowPage(SettingsPageId);
            break;
    }

    return;
}
void BuzzerSettingPage::PageReadEventHandlerTick()
{
    return;
}


void BuzzerSettingPage::PageWriteAckedEventHandler()
{
    switch(buzzerpagestate){
        case BuzzerUpdatingEnable:
            UpdateField(BUZZER_SNOOZE_FIELD, ConvertNumToAscii(device_config.snooze_time));
            buzzerpagestate = BuzzerIdle;
            break;
        case BuzzerIdle:
            break;
    }
    return;
}



