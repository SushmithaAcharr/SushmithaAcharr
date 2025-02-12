/*
 * FanControle.c
 *
 *  Created on: 30-Jan-2024
 *      Author: Sankalp
 */
#include "FanControl.h"
#include "UserConfig.h"
#include "FreeRTOS.h"
#include "task.h"

#define FAN_ON_HYSERISYS_TIME   (2)
#define FAN_FB_DEBOUNCE_TIME    (1)


Fan::Fan(int fanid, bsp_io_port_pin_t relay, bsp_io_port_pin_t auxrelay, bsp_io_port_pin_t fb, bsp_io_port_pin_t status)
{
    main_relay_pin = relay;
    aux_relay_pin = auxrelay;
    feedback_pin = fb;
    status_led_pin = status;
    fan_id = fanid;

    fan_state = FanStateOff;
    timer_cnt = 0;
    fan_ac_fb_status = ACFeedbackUnknown;
    in_low_time = 0;
    in_high_time = 0;
    mode = Backup;
}

static int fan_start_time = 0;

void Fan::Init()
{
    SetMainOff();
    SetAuxFanValue(FanOff);
}

UserFanState_e Fan::GetFanState()
{
	UserFanState_e usr_state = FanNotAvailable;

	if(NUM_OF_UNITS > 1){
		switch (fan_state)
		{
			case FanStateOff:
				usr_state = UserFanOff;
				break;
			case TurnAuxFanOn:
				usr_state = UserAuxOn;
				break;
			case AuxilaryFanOn:
				usr_state = UserAuxOn;
				break;
			case MainFanOn:
				usr_state = UserFanOn;
				break;
			case AtFault:
			case ClearingFault:
				usr_state = UserFanAtFault;
				break;
			case TurnOffFan:
				usr_state = UserFanOff;
				break;
			case WaitForFanOn:
			    usr_state = UserFanOn;
			    break;
		}
	}
	return usr_state;
}


void Fan::SetFanValue(FanValue_e value)
{
    if(device_config.unit[fan_id].status == 0){
        return;
    }
	switch(fan_state)
	{
	case FanStateOff:
		if((value == FanOn)){
		    fan_start_time = xTaskGetTickCount();
			fan_state =  TurnAuxFanOn;
		}
		break;
	case AuxilaryFanOn:
	case MainFanOn:
		if((value == FanOff)){
			fan_state =  TurnOffFan;
		}
		break;
	case WaitForFanOn:
	case AtFault:
	case TurnAuxFanOn:
	case TurnOffFan:
	case ClearingFault:
		break;
	}
}
FanValue_e Fan::GetFanValue()
{
	if(IsMainOn()){
		return FanOn;
	} else {
		return FanOff;
	}
}
void Fan::SetAuxFanValue(FanValue_e value)
{
	if(value == FanOn){
		SetAuxOn();
	} else {
		SetAuxOff();
	}
}
FanValue_e Fan::GetAuxFanValue()
{
	if(IsAuxOn()){
		return FanOn;
	} else {
		return FanOff;
	}
}

FanValue_e Fan::GetFanFBState()
{
    bsp_io_level_t level= BSP_IO_LEVEL_LOW;
    R_IOPORT_PinRead(&g_ioport_ctrl, feedback_pin, &level);

	if(level == BSP_IO_LEVEL_HIGH){
		return FanOff;
	} else {
		return FanOn;
	}
}

void Fan::SetAuxOff()
{
    R_IOPORT_PinWrite(&g_ioport_ctrl, aux_relay_pin, BSP_IO_LEVEL_HIGH);
	//UC_SIG_AUX_RL1 = 1;
}

void Fan::SetAuxOn()
{
	//UC_SIG_AUX_RL1 = 0;
    R_IOPORT_PinWrite(&g_ioport_ctrl, aux_relay_pin, BSP_IO_LEVEL_LOW);
	//UNIT_LED1 = 1;
    R_IOPORT_PinWrite(&g_ioport_ctrl, status_led_pin, BSP_IO_LEVEL_LOW);
}

bool Fan::IsAuxOn()
{
    bsp_io_level_t level= BSP_IO_LEVEL_LOW;
    R_IOPORT_PinRead(&g_ioport_ctrl, aux_relay_pin, &level);
	return level == BSP_IO_LEVEL_LOW;
}

void Fan::SetMainOff()
{
	//UC_SIG_RL1 = 1;
    R_IOPORT_PinWrite(&g_ioport_ctrl, main_relay_pin, BSP_IO_LEVEL_HIGH);
	//UNIT_LED1 = 0;
    R_IOPORT_PinWrite(&g_ioport_ctrl, status_led_pin, BSP_IO_LEVEL_HIGH);
}

void Fan::SetMainOn()
{
	//UC_SIG_RL1 = 0;

	R_IOPORT_PinWrite(&g_ioport_ctrl, main_relay_pin, BSP_IO_LEVEL_LOW);
}

bool Fan::IsMainOn()
{
    bsp_io_level_t level= BSP_IO_LEVEL_LOW;
    R_IOPORT_PinRead(&g_ioport_ctrl, main_relay_pin, &level);
    return level == BSP_IO_LEVEL_LOW;
	//return UC_SIG_RL1 == 0;
}

typedef enum{
    FaultFanStateOff,
    FaultTurnAuxFanOn,
    FaultAuxilaryFanOn,
    FaultWaitForFanOn,
    FaultMainFanOn,
}FaultFanState_e;

FaultFanState_e fault_state = FaultFanStateOff;

void Fan::ClearFaultSM()
{
    CheckFanFault();
    switch (fault_state)
    {
        case FaultFanStateOff:
            break;
        case FaultTurnAuxFanOn:
            SetAuxFanValue(FanOn);
            fault_state = FaultAuxilaryFanOn;
            break;
        case FaultAuxilaryFanOn:
            timer_cnt++;
            if(timer_cnt >= TIME_OUT_TO_TURN_ON_MAIN){
                SetMainOn();
                fault_state = FaultWaitForFanOn;
                timer_cnt = 0;
            }
            break;
        case FaultWaitForFanOn:
            timer_cnt++;
            if(timer_cnt >= FAN_ON_HYSERISYS_TIME){
                fault_state = FaultMainFanOn;
                timer_cnt = 0;
            }
            break;
        case FaultMainFanOn:
            if(IsFanInFault()){
                fan_state = AtFault;
            } else {
                fan_state = FanStateOff;
                fault_state = FaultFanStateOff;
                SetMainOff();
                SetAuxOff();
            }
            break;
     }

}

void Fan::RunFanSM()
{
	CheckFanFault();
	switch (fan_state)
	{
	case FanStateOff:
		break;
	case TurnAuxFanOn:
		SetAuxFanValue(FanOn);
		fan_state = AuxilaryFanOn;
		break;
	case AuxilaryFanOn:
		timer_cnt++;
		if(timer_cnt >= TIME_OUT_TO_TURN_ON_MAIN){
			SetMainOn();
			fan_state = WaitForFanOn;
			timer_cnt = 0;
		}
		break;
	case WaitForFanOn:
		timer_cnt++;
		if(timer_cnt >= FAN_ON_HYSERISYS_TIME){
			fan_state = MainFanOn;
			timer_cnt = 0;
		}
		break;
	case MainFanOn:
		if(IsFanInFault()){
			fan_state = AtFault;
			timer_cnt = 0;
		}
		break;
	case AtFault:
	    timer_cnt++;
	    if(timer_cnt > 30 && fault_state != FaultFanStateOff){
	        fan_state = ClearingFault;
	    } else {
	        fault_state = FaultTurnAuxFanOn;
            SetMainOff();
            SetAuxFanValue(FanOff);
	    }
		break;
	case ClearingFault:
	    if(fault_state != FaultFanStateOff){
	        ClearFaultSM();
	    } else {
	        fan_state = FanStateOff;
	    }
	    break;
	case TurnOffFan:
		SetMainOff();
		SetAuxFanValue(FanOff);
		fan_state = FanStateOff;
		break;
	}
}




bool Fan::IsFanInFault()
{
    if(simulate_setup.simulate == 1){
        switch (fan_id){
            case 0:
                return simulate_setup.makeunit1fail;
            case 1:
                return simulate_setup.makeunit2fail;
            case 2:
                return simulate_setup.makeunit3fail;
            case 3:
                return simulate_setup.makeunit4fail;
        }

    }
	return (fan_ac_fb_status == ACFeedbackHigh);
}



//AC_FBIN1
void Fan::CheckFanFault()
{
    bsp_io_level_t feedback_value= BSP_IO_LEVEL_LOW;
    R_IOPORT_PinRead(&g_ioport_ctrl, main_relay_pin, &feedback_value);

	switch(fan_ac_fb_status){
		case ACFeedbackUnknown:
			if(feedback_value == 1){
				in_high_time = xTaskGetTickCount();
				fan_ac_fb_status = ACFeedbackInTransittingToHigh;
			} else {
				in_low_time = xTaskGetTickCount();
				fan_ac_fb_status = ACFeedbackInTransittingToLow;
			}
			break;
		case ACFeedbackInTransittingToHigh:
			if(feedback_value == 1){
				if((xTaskGetTickCount() - in_high_time)>= FAN_FB_DEBOUNCE_TIME){
					fan_ac_fb_status = ACFeedbackHigh;
				} else {
					fan_ac_fb_status = ACFeedbackInTransittingToHigh;
				}
			} else {
				fan_ac_fb_status = ACFeedbackLow;
			}
			break;
		case ACFeedbackHigh:
			if(feedback_value == 0){
				in_low_time = xTaskGetTickCount();
				fan_ac_fb_status = ACFeedbackInTransittingToLow;
			}
			break;
		case ACFeedbackInTransittingToLow:
			if(feedback_value == 0){
				if((xTaskGetTickCount() - in_low_time)>= FAN_FB_DEBOUNCE_TIME){
					fan_ac_fb_status = ACFeedbackLow;
				} else {
					fan_ac_fb_status = ACFeedbackInTransittingToLow;
				}
			} else {
				fan_ac_fb_status = ACFeedbackHigh;
			}
			break;
		case ACFeedbackLow:
			if(feedback_value == 1){
				in_high_time = xTaskGetTickCount();
				fan_ac_fb_status = ACFeedbackInTransittingToHigh;
			}
			break;
	}

}
