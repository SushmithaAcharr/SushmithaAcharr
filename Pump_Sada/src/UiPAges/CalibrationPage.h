/*
 * CalibrationPage.h
 *
 *  Created on: 28-Apr-2024
 *      Author: Sankalp
 */

#ifndef UIPAGES_CALIBRATIONPAGE_H_
#define UIPAGES_CALIBRATIONPAGE_H_


#include "UIPage.h"


class CalibrationPage : public UIPage
{
public:
    virtual void PageInit();
    virtual void PageReadEventHandler(DisplayMsg_t *msg);
    virtual void PageReadEventHandlerTick();
    virtual void PageWriteAckedEventHandler();
};



#endif /* UIPAGES_CALIBRATIONPAGE_H_ */
