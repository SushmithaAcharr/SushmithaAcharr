/*
 * ConfigManager.h
 *
 *  Created on: 25-Dec-2023
 *      Author: Sankalp
 */

#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#include "UserConfig.h"
#include "ManufacturingInfo.h"

extern UserConfig_t device_config;
extern ManufacturingInfo_t mfg_config;

void ConfigMgrInit();
void ConfigSetToFactoryValues();
void ConfigMgrRead();
void ConfigMgrWrite();

void ConfigMgrReadMfgData();
void ConfigMgrWriteMfgData();



#endif /* CONFIGMANAGER_H_ */
