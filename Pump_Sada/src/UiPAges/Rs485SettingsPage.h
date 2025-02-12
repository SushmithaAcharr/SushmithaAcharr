/*
 * Rs485SettingsPage.h
 *
 *  Created on: 13-Mar-2024
 *      Author: Sankalp
 */

#ifndef RS485SETTINGSPAGE_H_
#define RS485SETTINGSPAGE_H_


#include "UIPage.h"

class Rs485SettingsPage : public UIPage
{
public:
    virtual void PageInit();
    virtual void PageReadEventHandler(DisplayMsg_t *msg);
    virtual void PageReadEventHandlerTick();
    virtual void PageWriteAckedEventHandler();
};


#endif /* RS485SETTINGSPAGE_H_ */
