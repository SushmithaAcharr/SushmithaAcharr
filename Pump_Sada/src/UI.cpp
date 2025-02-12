/*
 * UI.cpp
 *
 *  Created on: 28-Feb-2024
 *      Author: Sankalp
 */
#include "UI.h"
#include "UIPage.h"

#include "UiPAges/SplashPage.h"
#include "UiPAges/DashBoard.h"
#include "UiPAges/PasswordPage.h"
#include "UiPAges/SettingsPage.h"
#include "UiPAges/DateTimeSettingPage.h"
#include "UiPAges/TempSettingsPage.h"
#include "UiPAges/GsmSettingsPage.h"
#include "UiPAges/Rs485SettingsPage.h"
#include "UiPAges/WrongPwdPage.h"
#include "UiPAges/HeatWarningPage.h"
#include "UiPAges/UnitFailurePage.h"
#include "UiPAges/ExtFireSignalPage.h"
#include "UiPAges/TempSensorFailedPage.h"
#include "UiPAges/UnitSettingPage.h"
#include "UiPAges/BuzzerSettingPage.h"
#include "UiPAges/MiscSettingsPage.h"
#include "UiPAges/ChangePwdPage.h"
#include "UiPAges/AlertPage.h"
#include "UiPAges/FaultHistPage.h"
#include "UiPAges/AboutPage.h"
#include "UiPAges/FactoryResetPage.h"
#include "UiPAges/CalibrationPage.h"

#include "UIVPAddresses.h"


SplashPage splash;
DashBoard dashboard;
PasswordPage passwordpage;
SettingsPage settingpage;
DateTimeSettingPage timesettingspage;
TempSettingsPage tempsettingspage;
GsmSettingsPage gsmsettingspage;
Rs485SettingsPage rs485settingspage;
WrongPwdPage       wrongpwdpage;
HeatWarningPage heatwarningpage;
UnitFailurePage unitfailurepage;
ExtFireSignalPage extfiresignalpage;
TempSensorFailedPage tempsensorfailedpage;
UnitSettingPage unitSettingPage;
BuzzerSettingPage buzzerSettingPage;
MiscSettingsPage miscSettingsPage;
ChangePwdPage   changePwdPage;
AlertPage   alertPage;
FaultHistPage faultHistPage;
AboutPage aboutPage;
FactoryResetPage factorResetPage;
CalibrationPage calibrationPage;



uint16_t new_page_id;

UIPage* pages[MaxPages] ={
                          &splash, //0
                          &dashboard, //1
                          NULL,//2
                          &passwordpage, //3
                          NULL,//4
                          &settingpage, //5
                          NULL, //6
                          &unitSettingPage, //7
                          NULL, //8
                          &rs485settingspage, //9
                          NULL, //10
                          &timesettingspage, //11
                          NULL,//12
                          &buzzerSettingPage,//13
                          NULL,//14
                          &changePwdPage,//15
                          NULL,//16
                          &tempsettingspage,//17
                          NULL,//18
                          &gsmsettingspage,//119
                          NULL,//20
                          &miscSettingsPage,//21
                          NULL,//22
                          NULL,//23
                          &wrongpwdpage,//24
                          NULL,//25
                          &alertPage,//26
                          &faultHistPage, //27
                          &aboutPage, //28
                          &factorResetPage, //29
                          NULL, // 30
                          &calibrationPage, //31
};

DisplayMsg_t txmsg;
Page_e current_page = MaxPages;
uint16_t last_read_address = 0;

uint16_t ConvertNumToAscii(uint16_t num)
{
    uint16_t asciified = 0;
    asciified = (num%10) + 0x30;
    asciified |= (((num /10)+ 0x30) << 8);
    return asciified;
}

uint16_t ConvertAsciiToNum(uint16_t asciinum)
{
    uint16_t num = 0;
    num = (asciinum >> 8) - 0x30;
    num *= 10;
    num += (asciinum & 0xFF ) - 0x30;
    return num;
}

void RestartHMI()
{
    txmsg.cmd = WRITE_DATA_TO_ADDRES;
    txmsg.address = SystemResetField;
    txmsg.reg_cnt = 2;
    txmsg.data[0] = 0x55AA;
    txmsg.data[1] = 0x5AA5;
    current_page = SplashPageId;
    xQueueSend(display_tx_que, &txmsg, 0);

}

void SetLCDBrightness(uint16_t percentage)
{

}

Page_e GetCurrentPage()
{
    return current_page;
}

void HandleResponse(DisplayMsg_t* rsp)
{
    switch(rsp->address){
        case GetPageIdField:
        case PAGE_CHANGED_EVENT:
            if(rsp->data[0] != 0x1001){
                new_page_id = rsp->data[0];
            } else {
                new_page_id = DashBoardPageId;
            }
            InitPageIfChanged();
            break;
        default:
            if(current_page < MaxPages){

                pages[current_page]->PageReadEventHandler(rsp);

            }
            break;
    }

}


void PageHandlerTick()
{
    if(current_page < MaxPages){
       pages[current_page]->PageReadEventHandlerTick();
    }
}


void PageWriteAckedEventHandler(DisplayMsg_t* )
{
    if(current_page < MaxPages){
        pages[current_page]->PageWriteAckedEventHandler();
    }
    InitPageIfChanged();

}

void InitPageIfChanged()
{
    if(current_page != new_page_id){
        current_page = (Page_e) new_page_id;
        if(current_page < MaxPages){
            pages[current_page]->PageInit();
        }
    }
}


void UpdateField(uint16_t addr, uint16_t val)
{
    txmsg.cmd = WRITE_DATA_TO_ADDRES;
    txmsg.address = addr;
    txmsg.reg_cnt = 1;
    txmsg.data[0] = val;
    xQueueSend(display_tx_que, &txmsg, 0);
}

void ReadField(uint16_t addr)
{
    txmsg.cmd = READ_DATA_FROM_ADDRES;
    txmsg.address = addr;
    txmsg.reg_cnt = 1;
    xQueueSend(display_tx_que, &txmsg, 0);

}

void UpdateStringField(uint16_t addr, char* val, uint16_t len)
{
    txmsg.cmd = WRITE_DATA_TO_ADDRES;
    txmsg.address = addr;
    txmsg.reg_cnt = 0;
    for(int i = 0; i < len; i += 2){
        uint16_t reg = val[i];
        reg <<= 8;
        if((i + 1) < len){
            reg |= val[i+1];
        } else {
            reg |= 0;
        }
        txmsg.data[txmsg.reg_cnt] = reg;
        txmsg.reg_cnt++;
    }
    xQueueSend(display_tx_que, &txmsg, 0);
}

void UpdatePageId()
{
    txmsg.cmd = READ_DATA_FROM_ADDRES;
    txmsg.address = (uint16_t)GetPageIdField;
    txmsg.reg_cnt = 1;
    xQueueSend(display_tx_que, &txmsg, 0);
}
void ShowPage(uint16_t pageid)
{
    txmsg.cmd = WRITE_DATA_TO_ADDRES;
    txmsg.address = (uint16_t)SetPageIdField;
    txmsg.reg_cnt = 2;
    txmsg.data[0] = 0x5A01; //enble page setting
    txmsg.data[1] = pageid;
    new_page_id = pageid;
    xQueueSend(display_tx_que, &txmsg, 0);
}

void BuzzScreenBuzzer()
{
    txmsg.cmd = WRITE_DATA_TO_ADDRES;
    txmsg.address = (uint16_t)SetBuzzerField;
    txmsg.reg_cnt = 1;
    txmsg.data[0] = 0x007D; //enble page setting
    xQueueSend(display_tx_que, &txmsg, 0);
}


