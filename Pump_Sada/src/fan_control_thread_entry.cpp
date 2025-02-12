#include "fan_control_thread.h"
#include "r_rtc_api.h"
#include "MAX31865.h"
#include "FansManager.h"
#include "TempContol.h"
#include "AlarmManager.h"

/* Fan Control entry function */
/* pvParameters contains TaskHandle_t */
rtc_time_t g_rtc_current_time;

//rtc_time_t set_time;
//rtc_time_t get_time;
//float  temp = 0.0f;

void GetUpdatedTime(void)
{
    R_RTC_CalendarTimeGet(&g_rtc0_ctrl, &g_rtc_current_time);
}

void fan_control_thread_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);
    rtc_info_t info;

    R_RTC_InfoGet(&g_rtc0_ctrl, &info);
    if(info.status == RTC_STATUS_STOPPED){
        R_RTC_Open(&g_rtc0_ctrl, &g_rtc0_cfg);
    }

    R_SPI_Open(&g_spi0_ctrl, &g_spi0_cfg);

    /*set_time.tm_sec  = 00;
    set_time.tm_min  = 11;
    set_time.tm_hour  = 13;
    set_time.tm_mday  = 26;
    set_time.tm_mon  = 02;
    set_time.tm_year  = 124;*/
    //set_time.tm_year  = 3;

    AlarmManagernit();
    Max31865_init(3, 50);
    FanManagerInit();

    /* TODO: add your own code here */
    while (1)
    {



        /*R_RTC_CalendarTimeGet(&g_rtc0_ctrl, &get_time);
        if(Max31865_readTempC(&temp) != true)
        {
            while(1);
        }*/
        GetUpdatedTime();
        ReadTemperature();
        RunAllFanSM();
        RunAlarmMaganagerStateMachine();
        vTaskDelay (1000);
    }
}


