/*
 * ConfigManager.c
 *
 *  Created on: 25-Dec-2023
 *      Author: Sankalp
 */

#include "ConfigManager.h"
#include "FlashStorage.h"

#include <stdint.h>
#include <string.h>

extern UserConfig_t device_config;
ManufacturingInfo_t mfg_config;
extern FlashStorage storage;

void ConfigMgrInit()
{
    ConfigMgrRead();
    ConfigMgrReadMfgData();

}

void ConfigSetToFactoryValues()
{
	device_config.fan_control_mode = 1;

	device_config.unit[0].status = 1;
	device_config.unit[0].act_delay = 2;
	device_config.unit[0].schedule.on_time.hr = 0 ;
	device_config.unit[0].schedule.on_time.min = 0;
	device_config.unit[0].schedule.on_time.sec = 0;
	device_config.unit[0].schedule.off_time.hr = 7;
	device_config.unit[0].schedule.off_time.min = 59;
	device_config.unit[0].schedule.off_time.sec = 59;

	device_config.unit[1].status = 1;
	device_config.unit[1].act_delay = 2;
	device_config.unit[1].schedule.on_time.hr = 8;
	device_config.unit[1].schedule.on_time.min = 0;
	device_config.unit[1].schedule.on_time.sec = 0;
	device_config.unit[1].schedule.off_time.hr = 15;
	device_config.unit[1].schedule.off_time.min = 59;
	device_config.unit[1].schedule.off_time.sec = 59;

	device_config.unit[2].status = 1;
	device_config.unit[2].act_delay = 2;
	device_config.unit[2].schedule.on_time.hr = 16;
	device_config.unit[2].schedule.on_time.min = 0;
	device_config.unit[2].schedule.on_time.sec = 0;
	device_config.unit[2].schedule.off_time.hr = 23;
	device_config.unit[2].schedule.off_time.min = 59;
	device_config.unit[2].schedule.off_time.sec = 59;

	device_config.unit[3].status = 0;
	device_config.unit[3].act_delay = 2;
	device_config.unit[3].schedule.on_time.hr = 18;
	device_config.unit[3].schedule.on_time.min = 0;
	device_config.unit[3].schedule.on_time.sec = 0;
	device_config.unit[3].schedule.off_time.hr = 23;
	device_config.unit[3].schedule.off_time.min = 59;
	device_config.unit[3].schedule.off_time.sec = 59;

	device_config.high_temp = 30;
	device_config.low_temp = 16;
	device_config.critical_temp1 = 22;
	device_config.critical_temp2 = 25;
	device_config.critical_temp3 = 28;
	device_config.act_buzzer_temp = 27;
	device_config.temp_tolerence = 3;

	device_config.buzzer_enable = 1;
	device_config.snooze_time = 1;
	device_config.backlight_mode = 100;
	device_config.device_id = 1;
	device_config.baud_rate = 4;
	device_config.parity = 1;
	device_config.stop_bits = 1;

	device_config.user_pwd[0] = 1;
	device_config.user_pwd[1] = 1;
	device_config.user_pwd[2] = 1;
	device_config.user_pwd[3] = 1;
	device_config.temp_offset = 0;
}

void ConfigMgrRead()
{
    storage.ReadUserData((uint8_t*)&device_config, sizeof(UserConfig_t));
    //device_config.magic_word = 0;
    if(device_config.magic_word != 0xA5A5 || device_config.version != 1){
        ConfigSetToFactoryValues();
        device_config.temp_offset = 0;
    }
}
void ConfigMgrWrite()
{
    device_config.magic_word = 0xA5A5;
    device_config.version = 1;
    device_config.temp_offset = 0;
    storage.WriteUserData((uint8_t*)&device_config, (uint16_t)sizeof(device_config));
}


void ConfigMgrReadMfgData()
{
    storage.ReadFactoryData((uint8_t*)&mfg_config, sizeof(ManufacturingInfo_t));
    //device_config.magic_word = 0;
    if(mfg_config.magic_word != 0xA5A5){
        mfg_config.hw_version = 0x010000;
        mfg_config.sw_version = 0x010000;
        memcpy(mfg_config.serial_num, "ASP12345", DEVICE_SERIAL_NUM_LEN+1);
    }
}
void ConfigMgrWriteMfgData()
{

}

