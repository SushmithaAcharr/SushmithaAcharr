/*
 * ChangePwdPage.cpp
 *
 *  Created on: 29-Mar-2024
 *      Author: Sankalp
 */
#include "ChangePwdPage.h"
#include "ConfigManager.h"

typedef enum{
    UpdatingUserMessageFirst,
    ClearingStatusMessageFirst,
    WaitingForFirstPwd,
    UpdatingUserMessageSecond,
    ClearingStatusMessageSecond,
    WaitingForSecondPwd,
    UpdatingStatusMessageFinal,
    ChangePwdIdle,
}ChangePwdPageStates_e;

static ChangePwdPageStates_e pwdpagestate = ChangePwdIdle;
static uint8_t firstpwd[PWD_LENGTH];
static uint8_t secondpwd[PWD_LENGTH];
static int pwdtimer = 0;

void ChangePwdPage::PageInit()
{
    UpdateStringField((uint16_t)PWD_CHANGE_INSTRUCTION_FIELD, (char*)"Enter Password", (uint16_t)14);
    pwdpagestate = UpdatingUserMessageFirst;
}

void ChangePwdPage::PageReadEventHandler(DisplayMsg_t * rsp)
{
    switch(rsp->address){
        case PWD_CHANGE_ENTRY_FIELD:
            if(pwdpagestate == WaitingForFirstPwd){
                firstpwd[0] = (rsp->data[0] >> 8) - 0x30;
                firstpwd[1] = (rsp->data[0] & 0xFF ) - 0x30;
                firstpwd[2] = (rsp->data[1] >> 8) - 0x30;
                firstpwd[3] = (rsp->data[1] & 0xFF ) - 0x30;
                UpdateStringField((uint16_t)PWD_CHANGE_INSTRUCTION_FIELD, (char*)"Reenter Password", (uint16_t)16);
                pwdpagestate = UpdatingUserMessageSecond;
            } else {
                secondpwd[0] = (rsp->data[0] >> 8) - 0x30;
                secondpwd[1] = (rsp->data[0] & 0xFF ) - 0x30;
                secondpwd[2] = (rsp->data[1] >> 8) - 0x30;
                secondpwd[3] = (rsp->data[1] & 0xFF ) - 0x30;

                if(firstpwd[0] == secondpwd[0] &&
                   firstpwd[1] == secondpwd[1] &&
                   firstpwd[2] == secondpwd[2] /*&&
                   firstpwd[3] == secondpwd[3]*/ ){
                    UpdateStringField((uint16_t)PWD_CHANGE_RESULT_FIELD, (char*)"Password Changed", (uint16_t)16);
                    device_config.user_pwd[0] = firstpwd[0];
                    device_config.user_pwd[1] = firstpwd[1];
                    device_config.user_pwd[2] = firstpwd[2];
                    device_config.user_pwd[3] = firstpwd[3];

                } else {
                    UpdateStringField((uint16_t)PWD_CHANGE_RESULT_FIELD, (char*)"Password failed ", (uint16_t)16);
                }
                pwdpagestate = UpdatingStatusMessageFinal;
            }
            break;
        case SAVE_SETTING_BUTTON:
            ShowPage(SettingsPageId);
            break;
    }
    return;
}
void ChangePwdPage::PageReadEventHandlerTick()
{
    if(pwdpagestate == ChangePwdIdle){
        pwdtimer++;
        if(pwdtimer > 5){
            ShowPage(SettingsPageId);
        }
    }
    return;
}


void ChangePwdPage::PageWriteAckedEventHandler()
{
    switch(pwdpagestate){
        case UpdatingUserMessageFirst:
            UpdateStringField((uint16_t)PWD_CHANGE_RESULT_FIELD, (char*)"                ", (uint16_t)16);
            pwdpagestate = ClearingStatusMessageFirst;
            break;
        case ClearingStatusMessageFirst:
            pwdpagestate = WaitingForFirstPwd;
            break;
        case WaitingForFirstPwd:
            break;
        case UpdatingUserMessageSecond:
            UpdateStringField((uint16_t)PWD_CHANGE_RESULT_FIELD, (char*)"                ", (uint16_t)16);
            pwdpagestate = ClearingStatusMessageSecond;
            break;
        case ClearingStatusMessageSecond:
            pwdpagestate = WaitingForSecondPwd;
            break;
        case WaitingForSecondPwd:
            break;
        case UpdatingStatusMessageFinal:
            pwdpagestate = ChangePwdIdle;
            pwdtimer = 0;
            break;
        case ChangePwdIdle:
            break;
    }

    return;
}




