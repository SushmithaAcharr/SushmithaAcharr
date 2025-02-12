/*
 * DashBoard.cpp
 *
 *  Created on: 09-Mar-2024
 *      Author: Sankalp
 */

#include "DashBoard.h"
#include "FansManager.h"
#include "AlarmManager.h"
#include "fan_control_thread.h"
#include "r_rtc_api.h"
#include "UIVPAddresses.h"
//#include "UI.h"

typedef enum{
    UpdateStatusToDB,
    UpdateDateToDB,
    UpdateTimeToDB,
    UpdateTemperatureToDB,
    DashboardIdle,
}DashboardStates_e;

#define UNIT1_STATUS_FLAG_MASK      (0x0001)
#define UNIT2_STATUS_FLAG_MASK      (0x0002)
#define UNIT3_STATUS_FLAG_MASK      (0x0004)
#define UNIT4_STATUS_FLAG_MASK      (0x0008)

//#define ACT1_STATUS_FLAG_MASK       (0x0010)
//#define ACT2_STATUS_FLAG_MASK       (0x0020)
//#define ACT3_STATUS_FLAG_MASK       (0x0040)
//#define ACT4_STATUS_FLAG_MASK       (0x0080)

#define BUZZ_STATUS_FLAG_MASK       (0x0100)
#define RS485_STATUS_FLAG_MASK      (0x0200)



static DashboardStates_e db_state = UpdateStatusToDB;
static int ticktimer = 0;

static void UpdateDashboardDate()
{
    const char date_str[] = "10-Feb-2025";  // Hardcoded date

    txmsg.cmd = WRITE_DATA_TO_ADDRES;
    txmsg.address = (uint16_t)DASHBOARD_DATE;
    txmsg.reg_cnt = 6;

    for (int i = 0; i < 6; i++)
    {
        txmsg.data[i] = (date_str[i * 2] << 8) | date_str[(i * 2) + 1];
    }

    xQueueSend(display_tx_que, &txmsg, 0);
}

static void UpdateDashboardTime()
{
    const char time_str[] = "12:56";

    txmsg.cmd = WRITE_DATA_TO_ADDRES;
    txmsg.address = (uint16_t)DASHBOARD_TIME;
    txmsg.reg_cnt = 3;


    for (int i = 0; i < 3; i++)
    {
        txmsg.data[i] = (time_str[i * 2] << 8) | time_str[(i * 2) + 1];
    }

    xQueueSend(display_tx_que, &txmsg, 0);
}


static void UpdateTemperature()
{
    txmsg.cmd = WRITE_DATA_TO_ADDRES;
    txmsg.address = (uint16_t)DASH_BOARD_TEMP_TEXT_FIELD;
    txmsg.reg_cnt = 2;
    int temp = GetCurrentTemp();

    txmsg.data[1] = 0x2E;
    txmsg.data[1] <<= 8;
    txmsg.data[1] |= (temp%10) + 0x30;

    temp /= 10;

    txmsg.data[0] = (temp%10) + 0x30;
    txmsg.data[0] |= (((temp /10)+ 0x30) << 8);


    xQueueSend(display_tx_que, &txmsg, 0);
}

static void UpdateDashBoardStatus()
{
    uint16_t val = 0;

    if(Fan1.GetFanState() == UserAuxOn || Fan1.GetFanState() == UserFanOn){
        val |=  UNIT1_STATUS_FLAG_MASK;
    }

//    if(Fan1.GetFanFBState() == FanOn){
//        val |= ACT1_STATUS_FLAG_MASK;
//    }

    if(Fan2.GetFanState() == UserAuxOn || Fan2.GetFanState() == UserFanOn){
        val |=  UNIT2_STATUS_FLAG_MASK;
    }

//    if(Fan2.GetFanFBState() == FanOn){
//        val |= ACT2_STATUS_FLAG_MASK;
//    }

    if(Fan3.GetFanState() == UserAuxOn || Fan3.GetFanState() == UserFanOn){
        val |=  UNIT3_STATUS_FLAG_MASK;
    }

//    if(Fan3.GetFanFBState() == FanOn){
//        val |= ACT3_STATUS_FLAG_MASK;
//    }

    if(Fan4.GetFanState() == UserAuxOn || Fan4.GetFanState() == UserFanOn){
        val |=  UNIT4_STATUS_FLAG_MASK;
    }

//    if(Fan4.GetFanFBState() == FanOn){
//        val |= ACT4_STATUS_FLAG_MASK;
//    }

    if(IsInAlarmState() == true){
        val |= BUZZ_STATUS_FLAG_MASK;
    }

    if(g_rs485Comm_status_on_display){
        val |= RS485_STATUS_FLAG_MASK;
    }
    txmsg.cmd = WRITE_DATA_TO_ADDRES;
    txmsg.address = (uint16_t)DASH_BOARD_BIT_FIELD;
    txmsg.reg_cnt = 1;
    txmsg.data[0] = val;
    xQueueSend(display_tx_que, &txmsg, 0);
}

void DashBoard::PageInit()
{
    UpdateDashBoardStatus();
    db_state = UpdateStatusToDB;
    ticktimer = 0;
}
void DashBoard::PageReadEventHandler(DisplayMsg_t * )
{
    return;
}
void DashBoard::PageReadEventHandlerTick()
{
    if(db_state == DashboardIdle){
        ticktimer++;
        if(ticktimer > 2){
            UpdateDashBoardStatus();
            db_state = UpdateStatusToDB;
        }
    }
    return;
}
void DashBoard::PageWriteAckedEventHandler()
{
    if(db_state == UpdateStatusToDB){
        UpdateTemperature();
        db_state = UpdateDateToDB;
    }else if(db_state == UpdateDateToDB){
        UpdateDashboardDate();
        db_state = UpdateTimeToDB;
    }else if(db_state == UpdateTimeToDB){
        UpdateDashboardTime();
        db_state = UpdateTemperatureToDB;
    }else if(db_state == UpdateTemperatureToDB){
        ticktimer = 0;
        db_state = DashboardIdle;
    }
    return;
}



