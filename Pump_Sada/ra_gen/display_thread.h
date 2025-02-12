/* generated thread header file - do not edit */
#ifndef DISPLAY_THREAD_H_
#define DISPLAY_THREAD_H_
#include "bsp_api.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void display_thread_entry(void * pvParameters);
                #else
extern void display_thread_entry(void *pvParameters);
#endif
#include "r_sci_uart.h"
#include "r_uart_api.h"
FSP_HEADER
/** UART on SCI Instance. */
extern const uart_instance_t g_uart1;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_uart_instance_ctrl_t g_uart1_ctrl;
extern const uart_cfg_t g_uart1_cfg;
extern const sci_uart_extended_cfg_t g_uart1_cfg_extend;

#ifndef display_comm_handle
void display_comm_handle(uart_callback_args_t *p_args);
#endif
FSP_FOOTER
#endif /* DISPLAY_THREAD_H_ */
