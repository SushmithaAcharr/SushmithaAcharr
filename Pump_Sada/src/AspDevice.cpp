/*
 * AspDevice.cpp
 *
 *  Created on: 25-Feb-2024
 *      Author: Sankalp
 */

#include "AspDevice.h"
#include "string.h"
#include "UserConfig.h"
#include "FansManager.h"
#include "TempContol.h"

void AspDevice::ResetAllRegisters(void)
{
}


AspDevice::AspDevice()
{
}

uint16_t AspDevice::GetCoilCount()
{
    return 0;
}
uint16_t AspDevice::GetDescreteInputCount()
{
    return 0;
}
uint16_t AspDevice::GetHoldingRegisterCount()
{
    return MAX_REGISTERS;
}
uint16_t AspDevice::GetInputRegisterCountCount()
{
    return 0;
}

bool AspDevice::GetCoilValue(uint16_t )
{
    return false;
}
bool AspDevice::GetDescreteInputValue(uint16_t )
{
    return false;
}

bool AspDevice::IsValidInputRegisterAddress(uint16_t)
{
    bool ret = false;
    return ret;
}

bool AspDevice::IsValidHoldingRegisterAddress(uint16_t addr)
{
    bool ret = false;
    switch(addr){
        case UNIT1_ENABLED_REG :
        case UNIT2_ENABLED_REG :
        case UNIT3_ENABLED_REG :
        case UNIT4_ENABLED_REG :
        case FAN_CONTROL_MODE_REG :
        case HIGH_TEMP_SP_REG   :
        case LOW_TEMP_SP_REG    :
        case CT1_TEMP_SP_REG    :
        case CT2_TEMP_SP_REG    :
        case CT3_TEMP_SP_REG    :
        case ACT_BUZZ_TEMP_SP_REG   :
        case TEMP_TOLERENCE_REG :
        case BUZZER_ENABLED_REG :
        case BUZZER_SNOOZE_TIME_REG :
        case BACKLIGHT_TIME_REG :
        case MODBUS_SLAVE_ID_REG :
        case MODBUS_BAUD_REG :
        case MODBUS_PARITY_REG :
        case MODBUS_STOP_BIT_REG :
        case TEMPERATURE_REG :
        case LOW_TEMPERATURE_REG :
        case HIGH_TEMPERATURE_REG :
        case UNIT1_STATUS :
        case UNIT2_STATUS :
        case UNIT3_STATUS :
        case UNIT4_STATUS :
        /*case UNIT1_PWR_STATUS :
            break;
        case UNIT2_PWR_STATUS :
            break;
        case UNIT3_PWR_STATUS :
            break;
        case UNIT4_PWR_STATUS :
            break;*/
        case BUZZER_ALARM_FAULT_CODE :
        case CT0_FAULT_CODE :
        case CT1_FAULT_CODE :
        case CT2_FAULT_CODE :
        case CT3_FAULT_CODE :
        case LT_FAULT_CODE :
        case SF_FAULT_CODE :
        case UT1_FAULT_CODE :
        case UT2_FAULT_CODE :
        case UT3_FAULT_CODE :
        case UT4_FAULT_CODE :
            ret = true;
            break;
        default:
            ret = true;
            break;
    }
    return ret;
}
uint16_t AspDevice::GetInputRegisterValue(uint16_t )
{
    uint16_t ret = 0;
    return ret;
}

DataValueState_e AspDevice::SetCoilValue(uint16_t , bool )
{
    return ValueAccepted;
}

DataValueState_e AspDevice::SetHoldingRegister(uint16_t offset, uint16_t value)
{
    DataValueState_e retval = ValueInvalid;
    if(device_config.modbus_write == 1){
        retval = ValueAccepted;
        switch(offset){
            case UNIT1_ENABLED_REG :
                device_config.unit[0].status = value;
                break;
            case UNIT2_ENABLED_REG :
                device_config.unit[1].status = value;
                break;
            case UNIT3_ENABLED_REG :
                device_config.unit[2].status = value;
                break;
            case UNIT4_ENABLED_REG :
                device_config.unit[3].status = value;
                break;
            case FAN_CONTROL_MODE_REG :
                device_config.fan_control_mode = value;
                break;
            case HIGH_TEMP_SP_REG   :
                device_config.high_temp = value;
                break;
            case LOW_TEMP_SP_REG    :
                device_config.low_temp = value;
                break;
            case CT1_TEMP_SP_REG    :
                device_config.critical_temp1 = value;
                break;
            case CT2_TEMP_SP_REG    :
                device_config.critical_temp2 = value;
                break;
            case CT3_TEMP_SP_REG    :
                device_config.critical_temp3 = value;
                break;
            case ACT_BUZZ_TEMP_SP_REG   :
                device_config.act_buzzer_temp = value;
                break;
            case TEMP_TOLERENCE_REG :
                device_config.temp_tolerence = value;
                break;
            case BUZZER_ENABLED_REG :
                device_config.buzzer_enable = value;
                break;
            case BUZZER_SNOOZE_TIME_REG :
                device_config.snooze_time = value;
                break;
            case BACKLIGHT_TIME_REG :
                device_config.backlight_mode = value;
                break;
            case MODBUS_SLAVE_ID_REG :
                device_config.device_id = value;
                break;
            case MODBUS_BAUD_REG :
                device_config.baud_rate = value;
                break;
            case MODBUS_PARITY_REG :
                device_config.parity = value;
                break;
            case MODBUS_STOP_BIT_REG :
                device_config.stop_bits = value;
                break;

            case TEMPERATURE_REG :
                break;
            case LOW_TEMPERATURE_REG :
                break;
            case HIGH_TEMPERATURE_REG :
                break;
            case UNIT1_STATUS :
                break;
            case UNIT2_STATUS :
                break;
            case UNIT3_STATUS :
                break;
            case UNIT4_STATUS :
                break;
            /*case UNIT1_PWR_STATUS :
                break;
            case UNIT2_PWR_STATUS :
                break;
            case UNIT3_PWR_STATUS :
                break;
            case UNIT4_PWR_STATUS :
                break;*/
            case BUZZER_ALARM_FAULT_CODE :
                break;
            case CT0_FAULT_CODE :
                break;
            case CT1_FAULT_CODE :
                break;
            case CT2_FAULT_CODE :
                break;
            case CT3_FAULT_CODE :
                break;
            case LT_FAULT_CODE :
                break;
            case SF_FAULT_CODE :
                break;
            case UT1_FAULT_CODE :
                break;
            case UT2_FAULT_CODE :
                break;
            case UT3_FAULT_CODE :
                break;
            case UT4_FAULT_CODE :
                break;
            default:
                break;
        }

    }

    return retval;
}

uint16_t AspDevice::GetHoldingRegisterValue(uint16_t offset)
{
    uint16_t retval = 0;
    uint16_t temp = GetCurrentTemp();

    switch(offset){
        case UNIT1_ENABLED_REG :
            retval = device_config.unit[0].status;
            break;
        case UNIT2_ENABLED_REG :
            retval = device_config.unit[1].status;
            break;
        case UNIT3_ENABLED_REG :
            retval = device_config.unit[2].status;
            break;
        case UNIT4_ENABLED_REG :
            retval = device_config.unit[3].status;
            break;
        case FAN_CONTROL_MODE_REG :
            retval = device_config.fan_control_mode;
            break;
        case HIGH_TEMP_SP_REG   :
            retval = device_config.high_temp;
            break;
        case LOW_TEMP_SP_REG    :
            retval = device_config.low_temp;
            break;
        case CT1_TEMP_SP_REG    :
            retval = device_config.critical_temp1;
            break;
        case CT2_TEMP_SP_REG    :
            retval = device_config.critical_temp2;
            break;
        case CT3_TEMP_SP_REG    :
            retval = device_config.critical_temp3;
            break;
        case ACT_BUZZ_TEMP_SP_REG   :
            retval = device_config.act_buzzer_temp;
            break;
        case TEMP_TOLERENCE_REG :
            retval = device_config.temp_tolerence;
            break;
        case BUZZER_ENABLED_REG :
            retval = device_config.buzzer_enable;
            break;
        case BUZZER_SNOOZE_TIME_REG :
            retval = device_config.snooze_time;
            break;
        case BACKLIGHT_TIME_REG :
            retval = device_config.backlight_mode;
            break;
        case MODBUS_SLAVE_ID_REG :
            retval = device_config.device_id;
            break;
        case MODBUS_BAUD_REG :
            retval = device_config.baud_rate;
            break;
        case MODBUS_PARITY_REG :
            retval = device_config.parity;
            break;
        case MODBUS_STOP_BIT_REG :
            retval = device_config.stop_bits;
            break;

        case TEMPERATURE_REG :
            retval = temp;
            break;
        case LOW_TEMPERATURE_REG :
            retval = device_config.low_temp;
            break;
        case HIGH_TEMPERATURE_REG :
            retval = device_config.high_temp;
            break;
        case UNIT1_STATUS :
            retval = (uint16_t) Fan1.GetFanState();
            break;
        case UNIT2_STATUS :
            retval = (uint16_t) Fan2.GetFanState();
            break;
        case UNIT3_STATUS :
            retval = (uint16_t) Fan3.GetFanState();
            break;
        case UNIT4_STATUS :
            retval = (uint16_t) Fan4.GetFanState();
            break;
        /*case UNIT1_PWR_STATUS :
            break;
        case UNIT2_PWR_STATUS :
            break;
        case UNIT3_PWR_STATUS :
            break;
        case UNIT4_PWR_STATUS :
            break;*/
        case BUZZER_ALARM_FAULT_CODE :
            retval = 0; //TODO: fille the right value rom alarm manager later
            break;
        case CT0_FAULT_CODE :
            if(temp >= device_config.critical_temp1){
                retval = 1;
            } else {
                retval = 0;
            }
            break;
        case CT1_FAULT_CODE :
            if(temp >= device_config.critical_temp2){
                retval = 1;
            } else {
                retval = 0;
            }
            break;
        case CT2_FAULT_CODE :
            if(temp >= device_config.critical_temp3){
                retval = 1;
            } else {
                retval = 0;
            }
            break;
        case CT3_FAULT_CODE :
            retval = 0;
            break;
        case LT_FAULT_CODE :
            retval = 0;
            break;
        case SF_FAULT_CODE :
            retval = 0;
            break;
        case UT1_FAULT_CODE :
            retval = 0;
            break;
        case UT2_FAULT_CODE :
            retval = 0;
            break;
        case UT3_FAULT_CODE :
            retval = 0;
            break;
        case UT4_FAULT_CODE :
            retval = 0;
            break;
        default:
            retval = 0;
            break;
    }
    return retval;
}





