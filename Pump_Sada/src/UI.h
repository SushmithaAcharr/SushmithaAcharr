/*
 * UI.h
 *
 *  Created on: 28-Feb-2024
 *      Author: Sankalp
 */

#ifndef UI_H_
#define UI_H_

#include "display_comm.h"

typedef enum{
    RestartHMIState,
    WaitingForHMIRestart,
    Idle,
}DisplayCommState_e;


typedef enum{
    SplashPageId = 0,
    DashBoardPageId = 1,
    PasswordPageId = 3,
    SettingsPageId = 5,
    UnitConfigPageId = 7,
    ModbusConfigPageId = 9,
    TimeSettingsId = 11,
    BuzzerSettingPageId = 13,
    ChangePasswordPageId = 15,
    TempSettingsId = 17,
    GsmSettingsId = 19,
    MiscSettingPageId = 21,
    CorrentPasswordPageId = 23,
    WrongPasswordPageId = 24,
    AlertPagesId = 26,
    FaultHistPageId = 27,
    AboutPageId = 28,
    FactorResetPageId = 29,
    CalibrationPageId = 31,
    MaxPages
}Page_e;

void RestartHMI();
void HandleResponse(DisplayMsg_t* rsp);

void PageEventHandler(DisplayMsg_t *msg);
void PageHandlerTick();
void PageWriteAckedEventHandler(DisplayMsg_t *msg);
void InitPageIfChanged();
void ShowPage(uint16_t pageid);
void BuzzScreenBuzzer();
void UpdateField(uint16_t addr, uint16_t val);
void ReadField(uint16_t addr);
uint16_t ConvertAsciiToNum(uint16_t asciinum);
uint16_t ConvertNumToAscii(uint16_t num);
void SetLCDBrightness(uint16_t percentage);
void UpdateStringField(uint16_t addr, char* val, uint16_t len);
void UpdatePageId();

DisplayCommState_e GetUIState();
Page_e GetCurrentPage();

#endif /* UI_H_ */
