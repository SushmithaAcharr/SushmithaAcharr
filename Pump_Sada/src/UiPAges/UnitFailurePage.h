/*
 * UnitFailurePage.h
 *
 *  Created on: 13-Mar-2024
 *      Author: Sankalp
 */

#ifndef UNITFAILUREPAGE_H_
#define UNITFAILUREPAGE_H_

#include "UIPage.h"

class UnitFailurePage : public UIPage
{
public:
    virtual void PageInit();
    virtual void PageReadEventHandler(DisplayMsg_t *msg);
    virtual void PageReadEventHandlerTick();
    virtual void PageWriteAckedEventHandler();
};




#endif /* UNITFAILUREPAGE_H_ */
