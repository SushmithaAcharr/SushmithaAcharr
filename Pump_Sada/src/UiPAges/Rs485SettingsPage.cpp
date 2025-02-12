/*
 * Rs485SettingsPage.cpp
 *
 *  Created on: 13-Mar-2024
 *      Author: Sankalp
 */

#include "Rs485SettingsPage.h"
#include "fan_control_thread.h"
#include "ConfigManager.h"
#include "UI.h"

typedef enum{
    UpdatingSlaveId,
    UpdatingBaudRate,
    UpdatingParity,
    UpdatingStopbit,
    UpdatingModbusWriteEnable,
    ModbusIdle
}Rs485SettingsPageState_e;

static Rs485SettingsPageState_e modbusstate = ModbusIdle;
static rtc_time_t rtctime;


void Rs485SettingsPage::PageInit()
{
    txmsg.data[0] = 0xFFFF;
    txmsg.data[1] = 0xFFFF;

    uint8_t id = device_config.device_id;
    uint16_t asciified = 0;
    if(id < 10){
        asciified = (id%10) + 0x30;
        txmsg.data[0] = (asciified << 8) | 0xFF;
    } else if(id < 100){
        asciified = (id%10) + 0x30;
        asciified |= (((id /10)+ 0x30) << 8);
        txmsg.data[0] = asciified;
    } else {
        asciified = (id%10) + 0x30;
        txmsg.data[1] = (asciified << 8) | 0xFF;
        id /= 10;
        asciified = (id%10) + 0x30;
        asciified |= (((id /10)+ 0x30) << 8);
        txmsg.data[0] = asciified;
    }

    txmsg.cmd = WRITE_DATA_TO_ADDRES;
    txmsg.address = MODBUS_SLAVE_ID_FIELD;
    txmsg.reg_cnt = 2;
    xQueueSend(display_tx_que, &txmsg, 0);

    modbusstate = UpdatingSlaveId;
}

void Rs485SettingsPage::PageReadEventHandler(DisplayMsg_t * rsp)
{
    switch(rsp->address){
        case MODBUS_WRITE_ENABLE_FIELD:
            device_config.modbus_write = rsp->data[0];
            break;
        case MODBUS_SLAVE_ID_FIELD:
        {
            uint8_t id = 0;
            id = (rsp->data[0] >> 8) - 0x30;
            if((rsp->data[0] & 0xFF ) != 0xFF){
                id *= 10;
                id += (rsp->data[0] & 0xFF ) - 0x30;
            }

            if(((rsp->data[1] >> 8) & 0xFF ) != 0xFF){
                id *= 10;
                id += ((rsp->data[1] >> 8) & 0xFF ) - 0x30;
            }


            device_config.device_id = id;
        }
            break;
        case MODBUS_BAUD_SELECT_FIELD:
            device_config.baud_rate = rsp->data[0];
            break;
        case MODBUS_PARITY_SELECT_FIELD:
            device_config.parity = rsp->data[0];
            break;
        case MODBUS_STOPBIT_SELECT_FIELD:
            device_config.stop_bits = rsp->data[0];
            break;
        case SAVE_SETTING_BUTTON:
            if(rsp->data[0] == ModbusSaveButton){
            }
            ShowPage(SettingsPageId);
            break;
    }

    return;
}
void Rs485SettingsPage::PageReadEventHandlerTick()
{
    return;
}

void Rs485SettingsPage::PageWriteAckedEventHandler()
{
    switch(modbusstate){
        case UpdatingSlaveId:
            UpdateField(MODBUS_WRITE_ENABLE_FIELD, device_config.modbus_write);
            modbusstate = UpdatingModbusWriteEnable;
            break;
        case UpdatingModbusWriteEnable:
            UpdateField(MODBUS_BAUD_SELECT_FIELD, device_config.baud_rate);
            modbusstate = UpdatingBaudRate;
            break;
        case UpdatingBaudRate:
            UpdateField(MODBUS_PARITY_SELECT_FIELD, device_config.parity);
            modbusstate = UpdatingParity;
            break;
            break;
        case UpdatingParity:
            UpdateField(MODBUS_STOPBIT_SELECT_FIELD, device_config.stop_bits);
            modbusstate = ModbusIdle;
            break;
        default:
            break;
    }
    return;
}



