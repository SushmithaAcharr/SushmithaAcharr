/* generated common source file - do not edit */
#include "common_data.h"
ioport_instance_ctrl_t g_ioport_ctrl;
const ioport_instance_t g_ioport =
{ .p_api = &g_ioport_on_ioport, .p_ctrl = &g_ioport_ctrl, .p_cfg = &g_bsp_pin_cfg, };
QueueHandle_t display_tx_que;
#if 1
StaticQueue_t display_tx_que_memory;
uint8_t display_tx_que_queue_memory[256 * 2];
#endif
void rtos_startup_err_callback(void *p_instance, void *p_data);
TimerHandle_t RS485T35Timer;
#if 1
StaticTimer_t RS485T35Timer_memory;
#endif
void rtos_startup_err_callback(void *p_instance, void *p_data);
QueueHandle_t g_configQue;
#if 1
StaticQueue_t g_configQue_memory;
uint8_t g_configQue_queue_memory[1 * 64];
#endif
void rtos_startup_err_callback(void *p_instance, void *p_data);
void g_common_init(void)
{
    display_tx_que =
#if 1
            xQueueCreateStatic (
#else
                xQueueCreate(
                #endif
                                2,
                                256
#if 1
                                ,
                                &display_tx_que_queue_memory[0], &display_tx_que_memory
#endif
                                );
    if (NULL == display_tx_que)
    {
        rtos_startup_err_callback (display_tx_que, 0);
    }
    RS485T35Timer =
#if 1
            xTimerCreateStatic (
#else
                xTimerCreate(
                #endif
                                "T35 Timer",
                                11, pdFALSE, NULL, vRS485TimerCallbackT35
#if 1
                                ,
                                &RS485T35Timer_memory
#endif
                                );
    if (NULL == RS485T35Timer)
    {
        rtos_startup_err_callback (RS485T35Timer, 0);
    }
    g_configQue =
#if 1
            xQueueCreateStatic (
#else
                xQueueCreate(
                #endif
                                64,
                                1
#if 1
                                ,
                                &g_configQue_queue_memory[0], &g_configQue_memory
#endif
                                );
    if (NULL == g_configQue)
    {
        rtos_startup_err_callback (g_configQue, 0);
    }
}
