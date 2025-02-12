/*
 * WrongPwdPage.h
 *
 *  Created on: 13-Mar-2024
 *      Author: Sankalp
 */

#ifndef WRONGPWDPAGE_H_
#define WRONGPWDPAGE_H_


#include "UIPage.h"

class WrongPwdPage : public UIPage
{
public:
    virtual void PageInit();
    virtual void PageReadEventHandler(DisplayMsg_t *msg);
    virtual void PageReadEventHandlerTick();
    virtual void PageWriteAckedEventHandler();
};


#endif /* WRONGPWDPAGE_H_ */
