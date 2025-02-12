/*
 * AspDevice.h
 *
 *  Created on: 25-Feb-2024
 *      Author: Sankalp
 */

#ifndef ASPDEVICE_H_
#define ASPDEVICE_H_

#include <stdint.h>
#include "IModbusSlaveDevice.h"

// Register Maps for modbus slave

typedef enum{
    Baud1200 = 0,
    Baud2400 = 1,
    Baud4800 = 2,
    Baud9600 = 3,
    Baud19200 = 4,
    Baud38400 = 5,
    Baud115200 = 6
}Baudrates_e;

typedef enum{
    UNIT1_ENABLED_REG = 0x201,
    UNIT2_ENABLED_REG = 0x202,
    UNIT3_ENABLED_REG = 0x203,
    UNIT4_ENABLED_REG = 0x204,
    FAN_CONTROL_MODE_REG = 0x205,
    HIGH_TEMP_SP_REG    = 0x206,
    LOW_TEMP_SP_REG = 0x207,
    CT1_TEMP_SP_REG = 0x208,
    CT2_TEMP_SP_REG = 0x209,
    CT3_TEMP_SP_REG = 0x20A,
    ACT_BUZZ_TEMP_SP_REG    = 0x20B,
    TEMP_TOLERENCE_REG  = 0x20C,
    BUZZER_ENABLED_REG  = 0x20D,
    BUZZER_SNOOZE_TIME_REG  = 0x20E,
    BACKLIGHT_TIME_REG  = 0x20F,
    MODBUS_SLAVE_ID_REG = 0x210,
    MODBUS_BAUD_REG = 0x211,
    MODBUS_PARITY_REG = 0x212,
    MODBUS_STOP_BIT_REG = 0x213,

    TEMPERATURE_REG = 0x301,
    LOW_TEMPERATURE_REG = 0x302,
    HIGH_TEMPERATURE_REG = 0x303,
    UNIT1_STATUS = 0x304,
    UNIT2_STATUS = 0x305,
    UNIT3_STATUS = 0x306,
    UNIT4_STATUS = 0x307,
    /*UNIT1_PWR_STATUS = 0x308,
    UNIT2_PWR_STATUS = 0x309,
    UNIT3_PWR_STATUS = 0x30A,
    UNIT4_PWR_STATUS = 0x30B,*/

    BUZZER_ALARM_FAULT_CODE = 0x401,
    CT0_FAULT_CODE = 0x402,
    CT1_FAULT_CODE = 0x403,
    CT2_FAULT_CODE = 0x404,
    CT3_FAULT_CODE = 0x405,
    LT_FAULT_CODE = 0x406,
    SF_FAULT_CODE = 0x407,
    UT1_FAULT_CODE = 0x408,
    UT2_FAULT_CODE = 0x409,
    UT3_FAULT_CODE = 0x40A,
    UT4_FAULT_CODE = 0x40B,

    MAX_REGISTERS
}HoldingRegisterOffsets_e;


typedef enum{
    InputRegisterCount = 0
}InputRegisterOffsets_e;


class AspDevice : public IModbusSlaveDevice
{

public:
   AspDevice();

   void ResetAllRegisters(void);

   // modbus slave interface
    uint16_t GetCoilCount();
    uint16_t GetDescreteInputCount();
    uint16_t GetHoldingRegisterCount();
    uint16_t GetInputRegisterCountCount();

    bool GetCoilValue(uint16_t offset);
    bool GetDescreteInputValue(uint16_t offset);
    uint16_t GetHoldingRegisterValue(uint16_t offset);
    uint16_t GetInputRegisterValue(uint16_t offset);
    virtual bool IsValidHoldingRegisterAddress(uint16_t addr);
    virtual bool IsValidInputRegisterAddress(uint16_t addr);
    DataValueState_e SetCoilValue(uint16_t offset, bool value);
    DataValueState_e SetHoldingRegister(uint16_t offset, uint16_t value);
 };



#endif /* ASPDEVICE_H_ */
