/*
 * AlertPage.cpp
 *
 *  Created on: 31-Mar-2024
 *      Author: Sankalp
 */
#include "AlertPage.h"
#include "UIVPAddresses.h"
#include "stdio.h"
#include "AlarmManager.h"

typedef struct{
    char *Title;
    char *SubText;
    char *Button;
    IcondId_e icon;
}AlertScreenText_t;

typedef enum{
    ClearingTitleText,
    ClearingSubText,
    ClearingButtonText,
    UpdatingTitleText,
    UpdatingSubText,
    UpdatingButtonText,
    UpdatingIcon,
    AlertScreenIdle
}AlaertScreenState_e;

Page_e fallback_screen = DashBoardPageId;
AlaertScreenState_e screenstate = AlertScreenIdle;
Alert_e AlertState = NoAlert;
uint16_t AlertParam = 0;

AlertScreenText_t screenText[NoAlert] = {
                                  {
                                       (char*)" Ext. Fire Detected  ",
                                       (char*)" External Fire!!  ",
                                       (char*)" Dismiss  ",
                                       FireAlertIcon
                                  },
                                  {
                                       (char*)" Temp. Sensor Failed ",
                                       (char*)"Temperature Sensor",
                                       (char*)" Dismiss  ",
                                       TempAlertIcon
                                  },
                                  {
                                       (char*)" Temp. Out of Range  ",
                                       (char*)" High Temperature!",
                                       (char*)" Dismiss  ",
                                       TempAlertIcon
                                  },
                                  {
                                       (char*)"    Unit 1 Failed    ",
                                       (char*)" Unit Failed!!   ",
                                       (char*)" Dismiss  ",
                                       UnitAlertIcon
                                  },
                                  {
                                       (char*)"    Unit 2 Failed    ",
                                       (char*)" Unit Failed!!   ",
                                       (char*)" Dismiss  ",
                                       UnitAlertIcon
                                  },
                                  {
                                       (char*)"    Unit 3 Failed    ",
                                       (char*)" Unit Failed!!   ",
                                       (char*)" Dismiss  ",
                                       UnitAlertIcon
                                  },
                                  {
                                       (char*)"    Unit 4 Failed    ",
                                       (char*)" Unit Failed!!   ",
                                       (char*)" Dismiss  ",
                                       UnitAlertIcon
                                  },
                                  {
                                       (char*)"  Unit Power Failed  ",
                                       (char*)"Unit Power Failed!",
                                       (char*)" Dismiss  ",
                                       UnitAlertIcon
                                  },
                                  {
                                       (char*)" Temp. Out of Range  ",
                                       (char*)" Low Temperature!!",
                                       (char*)" Dismiss  ",
                                       TempAlertIcon
                                  },
                                  {
                                       (char*)" Modbus Comm Failed  ",
                                       (char*)"  Comm. Failed!!  ",
                                       (char*)" Dismiss  ",
                                       UnitAlertIcon
                                  }
};

char UnitFailureSubText[64];
#define EMPTY_STRING    "                     "
#define SUB_TEXT_LEN        (18)
#define HEADER_TEXT_LEN     (21)
#define BUTTON_TEXT_LEN     (10)

void AlertPage::PageInit()
{
    UpdateStringField(ALERT_TITLE_TEXT, (char*)EMPTY_STRING, HEADER_TEXT_LEN);
    screenstate = ClearingTitleText;
}

static void HandleAlarmDismiss()
{
    MuteBuzzer();
    if(fallback_screen != AlertPagesId){
        ShowPage(fallback_screen);
    } else {
        ShowPage(DashBoardPageId);
    }

}

void AlertPage::PageReadEventHandler(DisplayMsg_t * rsp)
{
    if(rsp->address == ALERT_DISMISS_BUTTON){
        HandleAlarmDismiss();
    }

    return;
}



void AlertPage::PageReadEventHandlerTick()
{
    bsp_io_level_t level= BSP_IO_LEVEL_LOW;
    R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_02_PIN_00, &level);
    if(level== BSP_IO_LEVEL_HIGH){
        HandleAlarmDismiss();
    }

    return;
}
void AlertPage::PageWriteAckedEventHandler()
{
    switch(screenstate){
        case ClearingTitleText:
            UpdateStringField(ALERT_SUB_TEXT, (char*)EMPTY_STRING, SUB_TEXT_LEN);
            screenstate = ClearingSubText;
            break;
        case ClearingSubText:
            UpdateStringField(ALERT_BUTTON_TEXT, (char*)EMPTY_STRING, BUTTON_TEXT_LEN);
            screenstate = ClearingButtonText;
            break;
        case ClearingButtonText:
            UpdateStringField(ALERT_TITLE_TEXT, screenText[AlertState].Title, strlen(screenText[AlertState].Title));
            screenstate = UpdatingTitleText;
            break;
        case UpdatingTitleText:
            UpdateStringField(ALERT_SUB_TEXT, screenText[AlertState].SubText, strlen(screenText[AlertState].SubText));
            screenstate = UpdatingSubText;
            break;
        case UpdatingSubText:
            UpdateStringField(ALERT_BUTTON_TEXT, screenText[AlertState].Button, strlen(screenText[AlertState].Button));
            screenstate = UpdatingButtonText;
            break;
        case UpdatingButtonText:
            UpdateField(ALERT_ICON_FIELD, screenText[AlertState].icon);
            screenstate = UpdatingIcon;
            break;
        case UpdatingIcon:
            screenstate = AlertScreenIdle;
            break;
        case AlertScreenIdle:
            break;
    }
    return;
}

void AlertPage::ClearAlert()
{
    AlertState = NoAlert;
}

void AlertPage::ShowAlert(Alert_e alert)
{
    fallback_screen = GetCurrentPage();
    AlertState = alert;
    ShowPage(AlertPagesId);
}
