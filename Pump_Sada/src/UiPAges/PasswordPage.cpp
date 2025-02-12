/*
 * PasswordPage.cpp
 *
 *  Created on: 13-Mar-2024
 *      Author: Sankalp
 */




/*
 * PasswordPage.cpp
 *
 *  Created on: 09-Mar-2024
 *      Author: Sankalp
 */
#include "PasswordPage.h"
#include "UserConfig.h"
#include "stdio.h"


void PasswordPage::PageInit()
{
    printf("PasswordPage::PageInit() called\n");
}
void PasswordPage::PageReadEventHandler(DisplayMsg_t *msg )
{
    uint8_t pwd[PWD_LENGTH];
    pwd[0] = (msg->data[0] >> 8) - 0x30;
    pwd[1] = (msg->data[0] & 0xFF ) - 0x30;
    pwd[2] = (msg->data[1] >> 8) - 0x30;
    pwd[3] = (msg->data[1] & 0xFF ) - 0x30;

    if(pwd[0] == device_config.user_pwd[0] &&
            pwd[1] == device_config.user_pwd[1] &&
            pwd[2] == device_config.user_pwd[2] &&
            pwd[3] == device_config.user_pwd[3] ){

        ShowPage(SettingsPageId);
        return;
    } else {
        //MoveToWrongPwdPage();
        ShowPage(WrongPasswordPageId);
        return;
    }
}
void PasswordPage::PageReadEventHandlerTick()
{
    return;
}
void PasswordPage::PageWriteAckedEventHandler()
{
    return;
}




