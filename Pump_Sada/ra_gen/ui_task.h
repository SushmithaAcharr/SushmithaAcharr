/* generated thread header file - do not edit */
#ifndef UI_TASK_H_
#define UI_TASK_H_
#include "bsp_api.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void ui_task_entry(void * pvParameters);
                #else
extern void ui_task_entry(void *pvParameters);
#endif
FSP_HEADER
FSP_FOOTER
#endif /* UI_TASK_H_ */
