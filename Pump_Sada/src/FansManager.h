/*
 * FansManager.h
 *
 *  Created on: 12-Feb-2024
 *      Author: Sankalp
 */

#ifndef FANSMANAGER_H_
#define FANSMANAGER_H_
#include "FanControl.h"

extern Fan Fan1;
extern Fan Fan2;
extern Fan Fan3;
extern Fan Fan4;

void ScheduleChanged();
void TurnOnCurrentFan();
void TurnOffCurrentFan();
void TurnOnBackupFan();
void TurnOffBackupFan();
UserFanState_e GetCurrentFanState();

void RunAllFanSM();
void FanManagerInit();
void GetUpdatedTime(void);
#endif /* FANSMANAGER_H_ */
