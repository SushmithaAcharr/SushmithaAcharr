/*
 * PasswordPage.h
 *
 *  Created on: 13-Mar-2024
 *      Author: Sankalp
 */

#ifndef PASSWORDPAGE_H_
#define PASSWORDPAGE_H_


#include "UIPage.h"

class PasswordPage : public UIPage
{
public:
    virtual void PageInit();
    virtual void PageReadEventHandler(DisplayMsg_t *msg);
    virtual void PageReadEventHandlerTick();
    virtual void PageWriteAckedEventHandler();
};



#endif /* PASSWORDPAGE_H_ */
