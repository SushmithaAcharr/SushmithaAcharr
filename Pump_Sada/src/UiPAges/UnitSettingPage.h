/*
 * UnitSettingPage.h
 *
 *  Created on: 29-Mar-2024
 *      Author: Sankalp
 */

#ifndef UIPAGES_UNITSETTINGPAGE_H_
#define UIPAGES_UNITSETTINGPAGE_H_

#include "UIPage.h"

class UnitSettingPage : public UIPage
{
public:
    virtual void PageInit();
    virtual void PageReadEventHandler(DisplayMsg_t *msg);
    virtual void PageReadEventHandlerTick();
    virtual void PageWriteAckedEventHandler();
};




#endif /* UIPAGES_UNITSETTINGPAGE_H_ */
