/*
 * HeatWarningPage.h
 *
 *  Created on: 13-Mar-2024
 *      Author: Sankalp
 */

#ifndef HEATWARNINGPAGE_H_
#define HEATWARNINGPAGE_H_

#include "UIPage.h"

class HeatWarningPage : public UIPage
{
public:
    virtual void PageInit();
    virtual void PageReadEventHandler(DisplayMsg_t *msg);
    virtual void PageReadEventHandlerTick();
    virtual void PageWriteAckedEventHandler();
};




#endif /* HEATWARNINGPAGE_H_ */
