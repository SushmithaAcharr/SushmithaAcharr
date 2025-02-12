/*
 * display_comm.h
 *
 *  Created on: 28-Feb-2024
 *      Author: Sankalp
 */

#ifndef DISPLAY_COMM_H_
#define DISPLAY_COMM_H_
#include <stdint.h>

#define MAX_WORDS_PER_MSG   (0x7C)
typedef enum{
    WRITE_COMMAND_ACKED = 0x01,
    WRITE_STRING_TO_ADDRESS = 0x80,
    READ_STRING_FROM_ADDRESS = 0x81,
    WRITE_DATA_TO_ADDRES    = 0x82,
    READ_DATA_FROM_ADDRES    = 0x83,
    WRITE_CURVE_DATA_TO_ADDRES    = 0x84,
}DWINCommands_e;

typedef struct{
    DWINCommands_e cmd;
    uint8_t reg_cnt;
    uint16_t address;
    uint16_t num_of_words;
    uint16_t data[MAX_WORDS_PER_MSG];
}DisplayMsg_t;


#endif /* DISPLAY_COMM_H_ */
