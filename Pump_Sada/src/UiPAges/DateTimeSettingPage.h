/*
 * DateTimeSettingPage.h
 *
 *  Created on: 29-Mar-2024
 *      Author: Sankalp
 */

#ifndef UIPAGES_DATETIMESETTINGPAGE_H_
#define UIPAGES_DATETIMESETTINGPAGE_H_



#include "UIPage.h"

class DateTimeSettingPage : public UIPage
{
public:
    virtual void PageInit();
    virtual void PageReadEventHandler(DisplayMsg_t *msg);
    virtual void PageReadEventHandlerTick();
    virtual void PageWriteAckedEventHandler();
};


#endif /* UIPAGES_DATETIMESETTINGPAGE_H_ */
