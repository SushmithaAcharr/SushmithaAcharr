/*
 * SettingsPage.cpp
 *
 *  Created on: 13-Mar-2024
 *      Author: Sankalp
 */


#include "SettingsPage.h"
#include "ConfigManager.h"


void SettingsPage::PageInit()
{
}
void SettingsPage::PageReadEventHandler(DisplayMsg_t *rsp )
{
    if(rsp->address == SAVE_SETTING_BUTTON){
        ConfigMgrWrite();
        ShowPage(DashBoardPageId);
    }
    NVIC_SystemReset();
    return;
}
void SettingsPage::PageReadEventHandlerTick()
{

    return;
}
void SettingsPage::PageWriteAckedEventHandler()
{
    return;
}




