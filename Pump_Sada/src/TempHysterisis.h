/*
 * TempHysterisis.h
 *
 *  Created on: 12-Mar-2024
 *      Author: Sankalp
 */

#ifndef TEMPHYSTERISIS_H_
#define TEMPHYSTERISIS_H_


class TempHysterisis
{
    int Setpoint;
    int Threshold;
    bool IsAboveHigherThreshold;
public:
    void Init(int setpoint, int threshold);
    bool GetActionToDo(int temp);
};


#endif /* TEMPHYSTERISIS_H_ */
