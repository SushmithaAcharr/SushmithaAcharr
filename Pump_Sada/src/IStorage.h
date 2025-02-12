/*
 * IStorage.h
 *
 *  Created on: 04-Dec-2022
 *      Author: Sankalp
 */

#ifndef ISTORAGE_H_
#define ISTORAGE_H_

#include <stdint.h>

class IStorage
{
public:
    virtual ~IStorage(){}
    virtual bool WriteFactoryData(uint8_t* data, uint16_t size) = 0;
    virtual bool ReadFactoryData(uint8_t* data, uint16_t size) = 0;

    virtual bool WriteUserData(uint8_t* data, uint16_t size) = 0;
    virtual bool ReadUserData(uint8_t* data, uint16_t size) = 0;

    virtual bool WriteFaultDatabase(uint8_t* data, uint16_t size) = 0;
    virtual bool ReadFaultDatabase(uint8_t* data, uint16_t size) = 0;


};




#endif /* ISTORAGE_H_ */
