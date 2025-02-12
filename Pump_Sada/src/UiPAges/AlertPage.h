/*
 * AlaertPage.h
 *
 *  Created on: 31-Mar-2024
 *      Author: Sankalp
 */

#ifndef UIPAGES_ALERTPAGE_H_
#define UIPAGES_ALERTPAGE_H_

#include "UIPage.h"

typedef enum{
    ExtFireAlert,
    TempSensorAlert,
    HighTempAlert,
    Unit1FailedAlert,
    Unit2FailedAlert,
    Unit3FailedAlert,
    Unit4FailedAlert,
    UnitPowerFailAlert,
    LowTempAlert,
    RS485CommErrorAlert,
    NoAlert,
}Alert_e;

typedef enum{
    RegularAlertIcon = 0,
    FireAlertIcon = 1,
    UnitAlertIcon = 2,
    TempAlertIcon = 3,
}IcondId_e;

class AlertPage : public UIPage
{
public:
    virtual void PageInit();
    virtual void PageReadEventHandler(DisplayMsg_t *msg);
    virtual void PageReadEventHandlerTick();
    virtual void PageWriteAckedEventHandler();

    void ShowAlert(Alert_e alert);
    void ClearAlert();
};




#endif /* UIPAGES_ALERTPAGE_H_ */
