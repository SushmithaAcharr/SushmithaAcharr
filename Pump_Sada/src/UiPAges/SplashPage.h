/*
 * SplashPage.h
 *
 *  Created on: 09-Mar-2024
 *      Author: Sankalp
 */

#ifndef SPLASHPAGE_H_
#define SPLASHPAGE_H_

#include "UIPage.h"

class SplashPage : public UIPage
{
public:
    virtual void PageInit();
    virtual void PageReadEventHandler(DisplayMsg_t *msg);
    virtual void PageReadEventHandlerTick();
    virtual void PageWriteAckedEventHandler();
};



#endif /* SPLASHPAGE_H_ */
