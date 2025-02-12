/*
 * ExtFireSignalPage.h
 *
 *  Created on: 13-Mar-2024
 *      Author: Sankalp
 */

#ifndef EXTFIRESIGNALPAGE_H_
#define EXTFIRESIGNALPAGE_H_

#include "UIPage.h"

class ExtFireSignalPage : public UIPage
{
public:
    virtual void PageInit();
    virtual void PageReadEventHandler(DisplayMsg_t *msg);
    virtual void PageReadEventHandlerTick();
    virtual void PageWriteAckedEventHandler();
};



#endif /* EXTFIRESIGNALPAGE_H_ */
