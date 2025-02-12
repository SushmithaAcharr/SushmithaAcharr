/*
 * ChangePwdPage.h
 *
 *  Created on: 29-Mar-2024
 *      Author: Sankalp
 */

#ifndef UIPAGES_CHANGEPWDPAGE_H_
#define UIPAGES_CHANGEPWDPAGE_H_

#include "UIPage.h"

class ChangePwdPage : public UIPage
{
public:
    virtual void PageInit();
    virtual void PageReadEventHandler(DisplayMsg_t *msg);
    virtual void PageReadEventHandlerTick();
    virtual void PageWriteAckedEventHandler();
};



#endif /* UIPAGES_CHANGEPWDPAGE_H_ */
