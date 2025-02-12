/*
 * ManufacturingInfo.h
 *
 *  Created on: 27-Apr-2023
 *      Author: Sankalp
 */

#ifndef MANUFACTURINGINFO_H_
#define MANUFACTURINGINFO_H_

#include <stdint.h>

#define DEVICE_SERIAL_NUM_LEN   (8)

typedef struct __attribute__((packed)){
    uint16_t magic_word;
    uint8_t serial_num[DEVICE_SERIAL_NUM_LEN + 1];
    uint32_t hw_version;
    uint32_t sw_version;
}ManufacturingInfo_t;


#endif /* MANUFACTURINGINFO_H_ */
