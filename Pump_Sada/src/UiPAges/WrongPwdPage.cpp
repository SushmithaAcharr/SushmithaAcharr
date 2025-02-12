/*
 * WrongPwdPage.cpp
 *
 *  Created on: 13-Mar-2024
 *      Author: Sankalp
 */



#include "WrongPwdPage.h"

static int wrongpwtimer = 0;
void WrongPwdPage::PageInit()
{
    wrongpwtimer = 0;
    UpdateStringField(PWD_MISMATCHED_INFO_TEXT, "Wrong Password    ", 18);
}
void WrongPwdPage::PageReadEventHandler(DisplayMsg_t * rsp)
{
    return;
}
void WrongPwdPage::PageReadEventHandlerTick()
{
    wrongpwtimer++;
    if(wrongpwtimer > 5){
        //ShowPage(DashBoardPageId);
    }
    return;
}
void WrongPwdPage::PageWriteAckedEventHandler()
{
    return;
}


