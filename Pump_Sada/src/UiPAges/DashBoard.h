/*
 * DashBoard.h
 *
 *  Created on: 09-Mar-2024
 *      Author: Sankalp
 */

#ifndef DASHBOARD_H_
#define DASHBOARD_H_

#include "UIPage.h"
extern bool g_rs485Comm_status_on_display;
class DashBoard : public UIPage
{
public:

    virtual void PageInit();
    virtual void PageReadEventHandler(DisplayMsg_t *msg);
    virtual void PageReadEventHandlerTick();
    virtual void PageWriteAckedEventHandler();
};

#endif /* DASHBOARD_H_ */
