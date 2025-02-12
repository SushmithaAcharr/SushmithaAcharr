/*
 * HeatWarningPage.cpp
 *
 *  Created on: 13-Mar-2024
 *      Author: Sankalp
 */



#include "HeatWarningPage.h"

extern void MuteBuzzer();

void HeatWarningPage::PageInit()
{
}
void HeatWarningPage::PageReadEventHandler(DisplayMsg_t * rsp)
{
    if(rsp->address == 0x2070){
        MuteBuzzer();
    }
    return;
}
void HeatWarningPage::PageReadEventHandlerTick()
{
    BuzzScreenBuzzer();
    return;
}
void HeatWarningPage::PageWriteAckedEventHandler()
{
    return;
}

