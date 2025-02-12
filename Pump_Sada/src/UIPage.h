/*
 * UIPage.h
 *
 *  Created on: 09-Mar-2024
 *      Author: Sankalp
 */

#ifndef UIPAGE_H_
#define UIPAGE_H_

#include "TempContol.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "hal_data.h"
#include "UI.h"
#include "display_comm.h"
#include "UIVPAddresses.h"

typedef enum{
    SystemResetField = 0x04,
    GetPageIdField = 0x14,
    SetPageIdField = 0x84,
    SetBuzzerField = 0xA0,
}DisplayFieldAddress_e;

extern DisplayMsg_t txmsg;
extern QueueHandle_t display_tx_que;

class UIPage
{
public:
    virtual void PageInit() = 0;
    virtual void PageReadEventHandler(DisplayMsg_t *msg) = 0;
    virtual void PageReadEventHandlerTick() = 0;
    virtual void PageWriteAckedEventHandler() = 0;
};

#endif /* UIPAGE_H_ */
