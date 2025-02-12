/*
 * AboutPage.h
 *
 *  Created on: 28-Apr-2024
 *      Author: Sankalp
 */

#ifndef UIPAGES_ABOUTPAGE_H_
#define UIPAGES_ABOUTPAGE_H_

#include "UIPage.h"


class AboutPage : public UIPage
{
public:
    virtual void PageInit();
    virtual void PageReadEventHandler(DisplayMsg_t *msg);
    virtual void PageReadEventHandlerTick();
    virtual void PageWriteAckedEventHandler();
};




#endif /* UIPAGES_ABOUTPAGE_H_ */
