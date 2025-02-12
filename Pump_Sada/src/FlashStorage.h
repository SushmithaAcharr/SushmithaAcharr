/*
 * FlashDriver.h
 *
 *  Created on: 04-Dec-2022
 *      Author: Sankalp
 */

#ifndef FLASHSTORAGE_H_
#define FLASHSTORAGE_H_

#include <IStorage.h>


class FlashStorage : public IStorage
{
private:
    uint32_t GetDataFlashBlockAddress(uint32_t block_num);
    bool EraseDataFlash(uint32_t address, uint32_t size);
    bool WriteToDataFlash(uint32_t address, uint8_t* data, uint32_t size);
    bool ReadFromDataFlash(uint32_t address, uint8_t* data, uint32_t size);
    uint32_t GetNumOfBlocksForSize(uint32_t size);

public:
    virtual bool WriteFactoryData(uint8_t* data, uint16_t size);
    virtual bool ReadFactoryData(uint8_t* data, uint16_t size);

    virtual bool WriteUserData(uint8_t* data, uint16_t size);
    virtual bool ReadUserData(uint8_t* data, uint16_t size);

    virtual bool WriteFaultDatabase(uint8_t* data, uint16_t size);
    virtual bool ReadFaultDatabase(uint8_t* data, uint16_t size);

};



#endif /* FLASHSTORAGE_H_ */
