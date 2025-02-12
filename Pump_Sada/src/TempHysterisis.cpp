/*

 * TempHysterisis.cpp
 *
 *  Created on: 12-Mar-2024
 *      Author: Sankalp
 */

#include "TempHysterisis.h"



void TempHysterisis::Init(int setpoint, int threshold)
{
    Setpoint = setpoint*10;
    Threshold = threshold;
    IsAboveHigherThreshold = false;
}
bool TempHysterisis::GetActionToDo(int temp)
{
    bool ret = false;

    if(temp > (Setpoint + Threshold)){
        ret = true;
        IsAboveHigherThreshold = true;
    } else if(IsAboveHigherThreshold && temp > (Setpoint - Threshold)){
        ret = true;
    } else if(IsAboveHigherThreshold && temp < (Setpoint - Threshold)){
        ret = false;
        IsAboveHigherThreshold = false;
    }

    return ret;
}
