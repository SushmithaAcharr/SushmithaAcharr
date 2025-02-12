/*
 * Event.h
 *
 *  Created on: Sep 26, 2022
 *      Author: Sankalp
 */

#ifndef APP_INC_EVENT_H_
#define APP_INC_EVENT_H_

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

#define MAX_BUFFER_SIZE	(256)

typedef enum{
	MODBUS_RS485_MESSAGE_RXED,
	MODBUS_RS485_RESPONSE_TIMEDOUT,
	MODBUS_RS232_MESSAGE_RXED,
	MODBUS_RS232_RESPONSE_TIMEDOUT,
	CANBUS_MESSAGE_RXED,
	UNKNOWN_EVENT
}EventType_e;

typedef struct{
	EventType_e evt;
	uint8_t buffer[MAX_BUFFER_SIZE];
	uint16_t size;
}Event_t;

typedef struct{
	EventType_e evt;
	uint16_t id;
	uint8_t buffer[MAX_BUFFER_SIZE];
}PSMsg_t;

#ifdef __cplusplus
}
#endif


#endif /* APP_INC_EVENT_H_ */
