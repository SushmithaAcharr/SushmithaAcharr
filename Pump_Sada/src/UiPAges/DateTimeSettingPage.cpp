/*
 * DateTimeSettingPage.cpp
 *
 *  Created on: 29-Mar-2024
 *      Author: Sankalp
 */
#include "DateTimeSettingPage.h"
#include "fan_control_thread.h"
#include "r_rtc_api.h"
#include "UI.h"

typedef enum{
    UpdatingTimeday,
    UpdatingTimeMon,
    UpdatingTimeYear,
    UpdatingTimeHr,
    UpdatingTimeMin,
    UpdatingTimeSec,
    DateTimeIdle
}DateTimeSettingPageState_e;

static DateTimeSettingPageState_e datetimestate = DateTimeIdle;
static rtc_time_t rtctime;


void DateTimeSettingPage::PageInit()
{

    R_RTC_CalendarTimeGet(&g_rtc0_ctrl, &rtctime);
    UpdateField(DATETIME_DATE_FIELD, rtctime.tm_mday);
    datetimestate = UpdatingTimeday;
}

void DateTimeSettingPage::PageReadEventHandler(DisplayMsg_t * rsp)
{
    switch(rsp->address){
        case DATETIME_DATE_FIELD:
            rtctime.tm_mday = rsp->data[0];
            break;
        case DATETIME_MONTH_FIELD:
            rtctime.tm_mon = rsp->data[0];
            break;
        case DATETIME_YEAR_FIELD:
            rtctime.tm_year = rsp->data[0];
            break;
        case DATETIME_HR_FIELD:
            rtctime.tm_hour = rsp->data[0];
            break;
        case DATETIME_MIN_FIELD:
            rtctime.tm_min = rsp->data[0];
            break;
        case DATETIME_SEC_FIELD:
            rtctime.tm_sec = rsp->data[0];
            break;
        case SAVE_SETTING_BUTTON:
            if(rsp->data[0] == DateTimeSaveButton){
                R_RTC_ClockSourceSet(&g_rtc0_ctrl);
                R_RTC_CalendarTimeSet(&g_rtc0_ctrl, &rtctime);
            }
            ShowPage(SettingsPageId);

            break;
    }

    return;
}
void DateTimeSettingPage::PageReadEventHandlerTick()
{
   /* R_RTC_CalendarTimeGet(&g_rtc0_ctrl, &rtctime);
    UpdateField(DATETIME_DATE_FIELD, rtctime.tm_mday);
    datetimestate = UpdatingTimeday;*/
    return;
}


void DateTimeSettingPage::PageWriteAckedEventHandler()
{
    switch(datetimestate){
        case UpdatingTimeday:
            UpdateField(DATETIME_MONTH_FIELD, rtctime.tm_mon);
            datetimestate = UpdatingTimeMon;
            break;
        case UpdatingTimeMon:
            UpdateField(DATETIME_YEAR_FIELD, rtctime.tm_year % 100);
            datetimestate = UpdatingTimeYear;
            break;
        case UpdatingTimeYear:
            UpdateField(DATETIME_HR_FIELD, rtctime.tm_hour);
            datetimestate = UpdatingTimeHr;
            break;
            break;
        case UpdatingTimeHr:
            UpdateField(DATETIME_MIN_FIELD, rtctime.tm_min);
            datetimestate = UpdatingTimeMin;
            break;
        case UpdatingTimeMin:
            UpdateField(DATETIME_SEC_FIELD, rtctime.tm_sec);
            datetimestate = UpdatingTimeSec;
            break;
        case UpdatingTimeSec:
            datetimestate = DateTimeIdle;
            break;
        default:
            break;
    }
    return;
}







