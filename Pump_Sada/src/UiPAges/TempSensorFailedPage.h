/*
 * TempSensorFailedPage.h
 *
 *  Created on: 13-Mar-2024
 *      Author: Sankalp
 */

#ifndef TEMPSENSORFAILEDPAGE_H_
#define TEMPSENSORFAILEDPAGE_H_

#include "UIPage.h"

class TempSensorFailedPage : public UIPage
{
public:
    virtual void PageInit();
    virtual void PageReadEventHandler(DisplayMsg_t *msg);
    virtual void PageReadEventHandlerTick();
    virtual void PageWriteAckedEventHandler();
};



#endif /* TEMPSENSORFAILEDPAGE_H_ */
