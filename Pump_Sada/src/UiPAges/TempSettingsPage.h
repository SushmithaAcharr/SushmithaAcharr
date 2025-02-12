/*
 * TempSettingsPage.h
 *
 *  Created on: 13-Mar-2024
 *      Author: Sankalp
 */

#ifndef TEMPSETTINGSPAGE_H_
#define TEMPSETTINGSPAGE_H_


#include "UIPage.h"

class TempSettingsPage : public UIPage
{
public:
    virtual void PageInit();
    virtual void PageReadEventHandler(DisplayMsg_t *msg);
    virtual void PageReadEventHandlerTick();
    virtual void PageWriteAckedEventHandler();
};



#endif /* TEMPSETTINGSPAGE_H_ */
