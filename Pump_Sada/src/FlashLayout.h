/*
 * FlashLayout.h
 *
 *  Created on: 04-Dec-2022
 *      Author: Sankalp
 */

#ifndef FLASHLAYOUT_H_
#define FLASHLAYOUT_H_

#include <stdint.h>

#define FLASH_HP_DF_BLOCK_SIZE            (64)
#define FLASH_HP_DF_BLOCK_0               (0x40100000U)

#define FLASH_BLOCK_START_ADDR_MASK         (0xFFFFFFC0)

#define FACTORY_DATA_START_BLOCK          (0)
#define FACTORY_DATA_BLOCK_COUNT          (8)

#define USER_DATA_START_BLOCK          (8)
#define USER_DATA_BLOCK_COUNT          (2)

#define FAULT_CODE_DATABASE_START_BLOCK     (10)
#define FAULT_CODE_DATABASE_BLOCK_COUNT     (4)


#endif /* FLASHLAYOUT_H_ */
