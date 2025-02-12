/*
 * FactoryResetPage.cpp
 *
 *  Created on: 28-Apr-2024
 *      Author: Sankalp
 */



#include "FactoryResetPage.h"
#include "UI.h"
#include "UIVPAddresses.h"
#include "ConfigManager.h"

void FactoryResetPage::PageInit()
{
}
void FactoryResetPage::PageReadEventHandler(DisplayMsg_t * rsp)
{
    switch(rsp->address){
        case SAVE_SETTING_BUTTON:
            if(rsp->data[0] == FACTORY_RESET_CONFIRM_ID){
                ConfigSetToFactoryValues();
                ConfigMgrWrite();
                NVIC_SystemReset();
            } else if(rsp->data[0] == FACTORY_RESET_CANCE_ID){
                // don nothing UI will exit
            }
            break;
        default:
            break;
    }

    return;
}
void FactoryResetPage::PageReadEventHandlerTick()
{
    return;
}
void FactoryResetPage::PageWriteAckedEventHandler()
{
    return;
}

