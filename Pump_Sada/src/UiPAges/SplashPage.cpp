/*
 * SplashPage.cpp
 *
 *  Created on: 09-Mar-2024
 *      Author: Sankalp
 */
#include "SplashPage.h"

static int time_cnt = 0;

static void MoveToDashBoard()
{
    ShowPage(DashBoardPageId);
}

void SplashPage::PageInit()
{
    time_cnt = 0;
}
void SplashPage::PageReadEventHandler(DisplayMsg_t * )
{
    return;
}
void SplashPage::PageReadEventHandlerTick()
{
    time_cnt++;
    if(time_cnt >= 50){
        time_cnt = 0;
        MoveToDashBoard();
        return ;
    }

    return;
}
void SplashPage::PageWriteAckedEventHandler()
{
    InitPageIfChanged();
}




