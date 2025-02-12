/*
 * AboutPage.cpp
 *
 *  Created on: 28-Apr-2024
 *      Author: Sankalp
 */



/*
 * AboutPage.cpp
 *
 *  Created on: 20-Apr-2024
 *      Author: Sankalp
 */

#include "AboutPage.h"
#include "UI.h"
#include "UIVPAddresses.h"

typedef enum{
    ClearingFirstString,
    ClearingSecondString,
    ClearingThirdString,
    UpdatingFirstString,
    UpdatingSecondString,
    UpdatingThirdString,
    AboutIdle,
}AboutState_e;

#define ABOUT_EMPTY_STRING  ("                                    ")
char AboutString[FAULT_STRING_LEN + 1];
static AboutState_e about_page_state = AboutIdle;

void AboutPage::PageInit()
{
    UpdateStringField(ABOUT_FIRST_ENTRY, ABOUT_EMPTY_STRING, ABOUT_STRING_LEN);
    about_page_state = ClearingFirstString;
}
void AboutPage::PageReadEventHandler(DisplayMsg_t * rsp)
{
    switch(rsp->address){
        default:
            break;
    }

    return;
}
void AboutPage::PageReadEventHandlerTick()
{
    return;
}
void AboutPage::PageWriteAckedEventHandler()
{
    switch(about_page_state){
        case ClearingFirstString:
            UpdateStringField(ABOUT_SECOND_ENTRY, ABOUT_EMPTY_STRING, ABOUT_STRING_LEN);
            about_page_state = ClearingSecondString;
            break;
        case ClearingSecondString:
            UpdateStringField(ABOUT_THIRD_ENTRY, ABOUT_EMPTY_STRING, FAULT_STRING_LEN);
            about_page_state = ClearingThirdString;
            break;
        case ClearingThirdString:
            UpdateStringField(ABOUT_FIRST_ENTRY, "Serial : 12345678", 17);
            about_page_state = UpdatingFirstString;
            break;
        case UpdatingFirstString:
            UpdateStringField(ABOUT_SECOND_ENTRY, "SW Ver: 1.0.0", 13);
            about_page_state = UpdatingSecondString;
            break;
        case UpdatingSecondString:
            UpdateStringField(ABOUT_THIRD_ENTRY, "Mfg Date: 28/04/2024", 20);
            about_page_state = UpdatingThirdString;
            break;
        case UpdatingThirdString:
            about_page_state = AboutIdle;
            break;
        case AboutIdle:
            break;
    }
    return;
}


