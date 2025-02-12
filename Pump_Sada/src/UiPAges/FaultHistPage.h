/*
 * FaultHistPage.h
 *
 *  Created on: 20-Apr-2024
 *      Author: Sankalp
 */

#ifndef UIPAGES_FAULTHISTPAGE_H_
#define UIPAGES_FAULTHISTPAGE_H_

#include "UIPage.h"

class FaultHistPage : public UIPage
{
public:
    virtual void PageInit();
    virtual void PageReadEventHandler(DisplayMsg_t *msg);
    virtual void PageReadEventHandlerTick();
    virtual void PageWriteAckedEventHandler();
};



#endif /* UIPAGES_FAULTHISTPAGE_H_ */
