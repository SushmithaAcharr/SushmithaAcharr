/*
 * FanControl.h
 *
 *  Created on: 30-Jan-2024
 *      Author: Sankalp
 */

#ifndef FANCONTROL_H_
#define FANCONTROL_H_

#include <stdint.h>
#include <stdbool.h>
#include "UserConfig.h"

#ifdef __cplusplus
    extern "C"{
        #include "hal_data.h"
    }
#endif

#define AUX_RELAY_TIME_DELAY (1000 * 60 * device_config.unit[fan_id].act_delay) // 2 min
#define SM_TICK_TIME_DURATION	(1000) // in ms

#define TIME_OUT_TO_TURN_ON_MAIN	(AUX_RELAY_TIME_DELAY/SM_TICK_TIME_DURATION)

typedef enum {
	FanStateOff,
	TurnAuxFanOn,
	AuxilaryFanOn,
	WaitForFanOn,
	MainFanOn,
	AtFault,
	ClearingFault,
	TurnOffFan
}FanStates_e;


typedef enum{
	UserFanOff,
	UserAuxOn,
	UserFanOn,
	UserFanAtFault,
	FanNotAvailable
}UserFanState_e;

typedef enum {
	FanOff,
	FanOn
}FanValue_e;

typedef enum{
	ACFeedbackUnknown,
	ACFeedbackHigh,
	ACFeedbackLow,
	ACFeedbackInTransittingToHigh,
	ACFeedbackInTransittingToLow,
}ACFeedback_e;

typedef enum{
    Scheduled,
    Backup
} FanMode_e;


class Fan
{
private:

    void SetAuxOn();
    void SetAuxOff();
    bool IsAuxOn();

    void SetMainOn();
    void SetMainOff();
    bool IsMainOn();
    void CheckFanFault();
    bool IsFanInFault();

    FanStates_e fan_state;
    int timer_cnt;
    ACFeedback_e fan_ac_fb_status;
    uint32_t in_low_time;
    uint32_t in_high_time;
    int fan_id;

    bsp_io_port_pin_t main_relay_pin;
    bsp_io_port_pin_t aux_relay_pin;
    bsp_io_port_pin_t feedback_pin;
    bsp_io_port_pin_t status_led_pin;

public:
    Fan(int fanid, bsp_io_port_pin_t relay, bsp_io_port_pin_t auxrelay, bsp_io_port_pin_t fb, bsp_io_port_pin_t status);
    void Init();
    void SetFanValue(FanValue_e state);
    FanValue_e GetFanValue();
    void SetAuxFanValue(FanValue_e state);
    FanValue_e GetAuxFanValue();
    UserFanState_e GetFanState();
    void RunFanSM();
    void ClearFaultSM();
    FanValue_e GetFanFBState();

    FanMode_e mode;

};


#endif /* FANCONTROL_H_ */
