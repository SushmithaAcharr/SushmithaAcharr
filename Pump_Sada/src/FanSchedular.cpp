/*
 * FanSchedular.c
 *
 *  Created on: 13-Feb-2024
 *      Author: Sankalp
 */
#include "FanControl.h"
#include "UserConfig.h"
#include "fan_control_thread.h"
#include <stdbool.h>
#include "FanSchedular.h"

static int ConvertAspTimeToSecondsFromMidnight(AspTime_t *time)
{
	return ((time->hr*60*60) + (time->min * 60) + time->sec);
}

static bool IsTimeOutOfRange(AspTime_t *time, UnitSchedule_t *range)
{
	int ontime = ConvertAspTimeToSecondsFromMidnight(&range->on_time);
	int offtime = ConvertAspTimeToSecondsFromMidnight(&range->off_time);
	int current = ConvertAspTimeToSecondsFromMidnight(time);
	//int currentLoopback = 0;

	//over flow at midnight
	if(range->off_time.hr < range->on_time.hr){
		if( time->hr < range->on_time.hr){ //we crossed midnight
			if(current <= offtime){
				return false;
			}
		}
	} else {
		if(ontime <= current && offtime >= current){
			return false;
		}
	}
	return true;
}


rtc_time_t rtc_time;

static void GetTime(AspTime_t *t)
{
    R_RTC_CalendarTimeGet(&g_rtc0_ctrl, &rtc_time);
    t->hr = (int8_t)rtc_time.tm_hour;
    t->min = (int8_t)rtc_time.tm_min;
    t->sec = (int8_t)rtc_time.tm_sec;
}

int GetCurrentScheduleId()
{
	int ret = -1;
	AspTime_t currentTime;
	GetTime(&currentTime);

	for(int i = 0; i < NUM_OF_UNITS; i++){
		if(IsTimeOutOfRange(&currentTime, &device_config.unit[i].schedule) == false){
			ret = i;
			break;
		}
	}
	return ret;
}

bool out;
bool IsFanScheduledToRunNow(int fanid)
{
    AspTime_t currentTime;
    GetTime(&currentTime);
    out = IsTimeOutOfRange(&currentTime, &device_config.unit[fanid].schedule);
    return ( out == false);
}

/*void RunSchedule()
{
	int sched_id = GetCurrentScheduleId();
	if(sched_id != current_schedule){
		ScheduleChanged();
		current_schedule = sched_id;
	}
}*/

