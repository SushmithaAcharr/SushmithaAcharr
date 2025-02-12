/*
 * UIVPAddresses.h
 *
 *  Created on: 29-Mar-2024
 *      Author: Sankalp
 */

#ifndef UIVPADDRESSES_H_
#define UIVPADDRESSES_H_

#define PAGE_CHANGED_EVENT          (0x1000)
#define SAVE_SETTING_BUTTON         (0x3050)
// Dash board
#define DASH_BOARD_BIT_FIELD        (0x1010)
#define DASH_BOARD_TEMP_TEXT_FIELD  (0x1020)

#define DASHBOARD_DATE              (0x1230)
#define DASHBOARD_TIME              (0x1280)

// PWD entery
#define PASSWORD_TEXT_INPUT_FIELD   (0x2050)

//Buzzer Setting
#define BUZZER_ENABLE_FIELD         (0x1040)
#define BUZZER_SNOOZE_FIELD         (0x1150)

// Unit setting
#define UNIT_SELECTED_FIELD         (0x1030)
#define UNIT_ENABLED_RADIO_FIELD    (0x1040)
#define UNIT_ACT_DELAY_FIELD        (0x1049)
#define UNIT_ON_HH_CHANGED          (0x1050)
#define UNIT_ON_MM_CHANGED          (0x1051)
#define UNIT_ON_SS_CHANGED          (0x1052)
#define UNIT_OFF_HH_CHANGED         (0x1060)
#define UNIT_OFF_MM_CHANGED         (0x1061)
#define UNIT_OFF_SS_CHANGED         (0x1062)

//Modbus Setting
#define MODBUS_WRITE_ENABLE_FIELD   (0x1100)
#define MODBUS_SLAVE_ID_FIELD       (0x1110)
#define MODBUS_BAUD_SELECT_FIELD    (0x1120)
#define MODBUS_PARITY_SELECT_FIELD  (0x1130)
#define MODBUS_STOPBIT_SELECT_FIELD (0x1140)

//Datetime Setting
#define DATETIME_DATE_FIELD         (0x1210)
#define DATETIME_MONTH_FIELD        (0x1211)
#define DATETIME_YEAR_FIELD         (0x1212)
#define DATETIME_HR_FIELD           (0x1220)
#define DATETIME_MIN_FIELD          (0x1221)
#define DATETIME_SEC_FIELD          (0x1222)

// change PWD
#define PWD_CHANGE_INSTRUCTION_FIELD    (0x3050)
#define PWD_CHANGE_RESULT_FIELD         (0x3060)
#define PWD_CHANGE_ENTRY_FIELD          (0x1160)

//Temp Settings
#define LOW_TEMP_FIELD          (0x1310)
#define BUZZ_TEMP_FIELD         (0x1311)
#define TEMP_THRESHOLD_FIELD    (0x1312)
#define CT1_TEMP_FIELD          (0x1320)
#define CT2_TEMP_FIELD          (0x1321)
#define CT3_TEMP_FIELD          (0x1322)

//GSM Settings
#define GSM_ENABLE_FIELD        (0x1400)
#define PHONE1_TEXT_FIELD       (0x1410)
#define PHONE2_TEXT_FIELD       (0x1420)
#define PHONE3_TEXT_FIELD       (0x1430)
#define PHONE4_TEXT_FIELD       (0x1440)
#define PHONE5_TEXT_FIELD       (0x1450)

//Misc Settings
#define TEMP_CALIBRATION_FILELD (0x1500)
#define FAN_CTRL_MODE_FIELD     (0x1510)
#define LED_BRIGHTNESS_FIELD    (0x82)

//Password Matched
#define PWD_MATCHED_INFO_TEXT   (0x1600)

//Password Mismatch
#define PWD_MISMATCHED_INFO_TEXT   (0x1700)

//Alert
#define ALERT_SUB_TEXT          (0x1800)
#define ALERT_TITLE_TEXT        (0x1900)
#define ALERT_BUTTON_TEXT       (0x1980)
#define ALERT_DISMISS_BUTTON    (0x1990)
#define ALERT_ICON_FIELD        (0x3300)

//Fault history

#define FAULT_FIRST_ENTRY       (0x3800)
#define FAULT_SECOND_ENTRY      (0x3900)
#define FAULT_THIRD_ENTRY       (0x3A00)
#define FAULT_PAGE_NUMBER       (0x3500)
#define FAULT_STRING_LEN        (36)
////About page
#define ABOUT_FIRST_ENTRY       (0x3800)
#define ABOUT_SECOND_ENTRY      (0x3900)
#define ABOUT_THIRD_ENTRY       (0x3A00)
#define ABOUT_STRING_LEN        (36)

// Factory Reset Page

#define FACTORY_RESET_CONFIRM_ID    (0x2002)
#define FACTORY_RESET_CANCE_ID      (0x2001)

// Calibrtion page
#define REFERNECE_TEMP_VALUE        (0x1505)
#define CALC_TEMP_OFFSET            (0x50)

typedef enum{
    SystemSettingScreenSave = 0x1,
    ModbusResetButton = 0x2,
    ModbusSaveButton = 0x3,
    DateTimeResetButton = 0x5,
    DateTimeSaveButton = 0x6,
    BuzzerResetButton = 0x8,
    BuzzerSaveButton = 0x9,
    ChangePwdSaveButton = 0x11,
    TempSettingSaveButton = 0x12,
    GSMSettingsSaveButton = 0x20,
    TempCalibrationSetButton = 0x50,
    PasswordMatchedDismissButton = 0x1001,
}SettingButtonValues;


#endif /* UIVPADDRESSES_H_ */
