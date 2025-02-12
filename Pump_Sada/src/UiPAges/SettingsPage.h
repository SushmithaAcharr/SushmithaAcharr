/*
 * SettingsPage.h
 *
 *  Created on: 13-Mar-2024
 *      Author: Sankalp
 */

#ifndef SETTINGSPAGE_H_
#define SETTINGSPAGE_H_

#include "UIPage.h"

class SettingsPage : public UIPage
{
public:
    virtual void PageInit();
    virtual void PageReadEventHandler(DisplayMsg_t *msg);
    virtual void PageReadEventHandlerTick();
    virtual void PageWriteAckedEventHandler();
};




#endif /* SETTINGSPAGE_H_ */
