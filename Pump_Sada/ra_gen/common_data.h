/* generated common header file - do not edit */
#ifndef COMMON_DATA_H_
#define COMMON_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "r_ioport.h"
#include "bsp_pin_cfg.h"
FSP_HEADER
/* IOPORT Instance */
extern const ioport_instance_t g_ioport;

/* IOPORT control structure. */
extern ioport_instance_ctrl_t g_ioport_ctrl;
extern QueueHandle_t display_tx_que;
extern TimerHandle_t RS485T35Timer;
void vRS485TimerCallbackT35(TimerHandle_t xTimer);
extern QueueHandle_t g_configQue;
void g_common_init(void);
FSP_FOOTER
#endif /* COMMON_DATA_H_ */
