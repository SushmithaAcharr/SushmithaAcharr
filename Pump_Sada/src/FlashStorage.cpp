#include "FlashStorage.h"
#include "FlashLayout.h"
#include "r_flash_hp.h"
#include "r_flash_api.h"
#include <stdio.h>

extern flash_hp_instance_ctrl_t g_flash0_ctrl;
extern const flash_cfg_t g_flash0_cfg;

uint32_t FlashStorage::GetNumOfBlocksForSize(uint32_t size)
{
    uint32_t ret = size / FLASH_HP_DF_BLOCK_SIZE;
    if(size % FLASH_HP_DF_BLOCK_SIZE){
        ret++;
    }
    return ret;
}
uint32_t FlashStorage::GetDataFlashBlockAddress(uint32_t block_num)
{
    return (FLASH_HP_DF_BLOCK_0 + (FLASH_HP_DF_BLOCK_SIZE * block_num));
}
bool FlashStorage::EraseDataFlash(uint32_t address, uint32_t size)
{
    fsp_err_t err = R_FLASH_HP_Erase(&g_flash0_ctrl, address, GetNumOfBlocksForSize(size));
    return (err == FSP_SUCCESS);
}
bool FlashStorage::WriteToDataFlash(uint32_t address, uint8_t* data, uint32_t size)
{
    fsp_err_t err = R_FLASH_HP_Write(&g_flash0_ctrl, (uint32_t) data, address, size);
    return (err == FSP_SUCCESS);
}
bool FlashStorage::ReadFromDataFlash(uint32_t address, uint8_t* data, uint32_t size)
{
    if(data == NULL){
        return false;
    }
    uint8_t* addr = (uint8_t*)address;
    memcpy(data, addr, size);
    return true;
}
bool FlashStorage::WriteFactoryData(uint8_t* data, uint16_t size)
{
    bool ret  = EraseDataFlash(GetDataFlashBlockAddress(FACTORY_DATA_START_BLOCK), size);
    if(ret == true){
        ret = WriteToDataFlash(GetDataFlashBlockAddress(FACTORY_DATA_START_BLOCK), data, size);
    }
    return ret;
}
bool FlashStorage::ReadFactoryData(uint8_t* data, uint16_t size)
{
    ReadFromDataFlash(GetDataFlashBlockAddress(FACTORY_DATA_START_BLOCK), data, size);
    return true;
}

bool FlashStorage::WriteUserData(uint8_t* data, uint16_t size)
{
    bool ret  = EraseDataFlash(GetDataFlashBlockAddress(USER_DATA_START_BLOCK), size);
    if(ret == true){
        ret = WriteToDataFlash(GetDataFlashBlockAddress(USER_DATA_START_BLOCK), data, size);
    }
    return ret;
}
bool FlashStorage::ReadUserData(uint8_t* data, uint16_t size)
{
    ReadFromDataFlash(GetDataFlashBlockAddress(USER_DATA_START_BLOCK), data, size);
    return true;
}

bool FlashStorage::WriteFaultDatabase(uint8_t* data, uint16_t size)
{
    bool ret  = EraseDataFlash(GetDataFlashBlockAddress(FAULT_CODE_DATABASE_START_BLOCK), size);
    if(ret == true){
        ret = WriteToDataFlash(GetDataFlashBlockAddress(FAULT_CODE_DATABASE_START_BLOCK), data, size);
    }
    return ret;
}
bool FlashStorage::ReadFaultDatabase(uint8_t* data, uint16_t size)
{
    ReadFromDataFlash(GetDataFlashBlockAddress(FAULT_CODE_DATABASE_START_BLOCK), data, size);
    return true;
}


