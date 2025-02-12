/*
 * GsmSettingsPage.h
 *
 *  Created on: 13-Mar-2024
 *      Author: Sankalp
 */

#ifndef GSMSETTINGSPAGE_H_
#define GSMSETTINGSPAGE_H_

#include "UIPage.h"

class GsmSettingsPage : public UIPage
{
public:
    virtual void PageInit();
    virtual void PageReadEventHandler(DisplayMsg_t *msg);
    virtual void PageReadEventHandlerTick();
    virtual void PageWriteAckedEventHandler();
};





#endif /* GSMSETTINGSPAGE_H_ */
