#include "ui_task.h"
/* UI Task entry function */
/* pvParameters contains TaskHandle_t */
#include "UI.h"


QueueHandle_t g_ui_que;
StaticQueue_t g_ui_task_que;
uint8_t g_ui_task_que_memory[sizeof(DisplayMsg_t) * 2];

static DisplayMsg_t rxmsg;
static DisplayMsg_t txmsg;
static bool sent = false;

DisplayCommState_e ui_state = RestartHMIState;
static int tasktick = 0;
void ui_task_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);

    g_ui_que =xQueueCreateStatic (
                                    2,
                                    sizeof(DisplayMsg_t),
                                    &g_ui_task_que_memory[0], &g_ui_task_que
                                    );

    //InitPageIfChanged();
    /* TODO: add your own code here */
    while (1)
    {
        BaseType_t ret = xQueueReceive(g_ui_que, &rxmsg, 100);
        if(ret == pdTRUE){
            switch(rxmsg.cmd){
                case WRITE_DATA_TO_ADDRES:
                {
                    PageWriteAckedEventHandler(&rxmsg);
                }
                break;
                case READ_DATA_FROM_ADDRES:
                {
                    HandleResponse(&rxmsg);
                }
                break;
                default:
                    break;
            }

        } else {
            switch(ui_state){
                case RestartHMIState:
                    RestartHMI();
                    ui_state = Idle;
                    tasktick = 0;
                    break;
                case Idle:
                    tasktick++;
                    if(tasktick > 1){
                        UpdatePageId();
                        tasktick = 0;
                    }
                default:
                    PageHandlerTick();
                    break;
            }
        }
        //vTaskDelay(100);
    }
}

DisplayCommState_e GetUIState()
{
    return ui_state;
}
