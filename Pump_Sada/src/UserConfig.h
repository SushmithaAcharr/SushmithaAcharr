/*
 * UserConfig.h
 *
 *  Created on: 04-Dec-2022
 *      Author: Sankalp
 */

#ifndef USERCONFIG_H_
#define USERCONFIG_H_

#include <stdint.h>


#include <stdint.h>

#define PWD_LENGTH  (4)
#define NUM_OF_UNITS    (4)

typedef struct __attribute__((packed)){
    int8_t day;
    int8_t month;
    int8_t year;
}AspDate_t;

typedef struct __attribute__((packed)){
    int8_t sec;
    int8_t min;
    int8_t hr;
}AspTime_t;

typedef struct{
    AspTime_t on_time;
    AspTime_t off_time;
}UnitSchedule_t;

typedef struct __attribute__((packed)) {
    uint8_t status;
    uint8_t act_delay;
    UnitSchedule_t schedule;
}Unit_t;


typedef struct __attribute__((packed)){
    uint16_t magic_word;
    uint8_t version;
    uint8_t fan_control_mode;
    uint8_t temp_setpoint;
    uint8_t user_pwd[PWD_LENGTH];
    Unit_t unit[NUM_OF_UNITS];
    uint8_t high_temp;
    uint8_t low_temp;
    uint8_t critical_temp1;
    uint8_t critical_temp2;
    uint8_t critical_temp3;
    uint8_t act_buzzer_temp;
    uint8_t temp_tolerence;
    uint8_t buzzer_enable;
    uint8_t snooze_time;
    uint16_t backlight_mode;
    uint8_t device_id;
    uint8_t baud_rate;
    uint8_t parity;
    uint8_t stop_bits;
    uint8_t modbus_write;
    int16_t temp_offset;
}UserConfig_t;

extern UserConfig_t device_config;


typedef struct __attribute__((packed)){
    uint8_t simulate;
    uint8_t simtemp;
    uint8_t makeunit1fail;
    uint8_t makeunit2fail;
    uint8_t makeunit3fail;
    uint8_t makeunit4fail;
} Simulate_t;

extern Simulate_t simulate_setup;

#endif /* USERCONFIG_H_ */
