#include "config_thread0.h"
#include "pcdc_freertos.h"
#include "FlashStorage.h"
#include "UserConfig.h"
#include "fan_control_thread.h"
#include "r_rtc_api.h"
#include "TempContol.h"
#include "ConfigManager.h"
#include "FaultCodeDatabase.h"
#include "version.h"

#define RESET_VALUE             (0x00)
/* Error status flag */
static volatile bool g_err_flag = false;
/* Variable to store baud rate */
uint32_t g_baud_rate = RESET_VALUE ;
/* Buffer to store user data */
uint8_t user_data_buf[DATA_LEN] = {RESET_VALUE};
/* Variable to store size of data received from tera term */
volatile uint32_t g_terminal_data_size = RESET_VALUE ;

/* Pointers to store USB descriptors */
extern uint8_t g_apl_device[];
extern uint8_t g_apl_configuration[];
extern uint8_t g_apl_hs_configuration[];
extern uint8_t g_apl_qualifier_descriptor[];
extern uint8_t * g_apl_string_table[];

const usb_descriptor_t g_usb_pcdc_descriptor =
{
 g_apl_device,                   /* Pointer to the device descriptor */
 g_apl_configuration,            /* Pointer to the configuration descriptor for Full-speed */
 g_apl_hs_configuration,         /* Pointer to the configuration descriptor for Hi-speed */
 g_apl_qualifier_descriptor,     /* Pointer to the qualifier descriptor */
 g_apl_string_table,             /* Pointer to the string descriptor table */
 NUM_STRING_DESCRIPTOR           /* Num entry String Descriptor */
};


FlashStorage storage;
#define READ_BUF_SIZE               (64)
uint8_t g_buf[READ_BUF_SIZE]            = {0};
uint8_t msg[READ_BUF_SIZE]            = {0};

typedef enum{

    ReadUserConfig = 1,
    SaveUserConfig = 2,
    ReadMfgConfig = 3,
    SaveMfgConfig = 4,
    SetTime = 5,
    GetTime = 6,
    ReadFirstFaultCode = 7,
    ReadNextFaultCode = 8,
    EraseFaultDb = 9,
}ConfigCommands_e;



Simulate_t simulate_setup {0, 17, 0, 0, 0, 0};


volatile bool msgsent = false;


static void  writeData(uint8_t* data, uint16_t)
{
    volatile fsp_err_t err;
    msgsent= false;
    err = R_USB_Write (&g_basic0_ctrl, (uint8_t*)data, 16, USB_CLASS_PCDC);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        __NOP();
    }
    while(!msgsent);
    err = R_USB_Write (&g_basic0_ctrl, (uint8_t*)&data[16], 16, USB_CLASS_PCDC);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        __NOP();
    }
    while(!msgsent);
    err = R_USB_Write (&g_basic0_ctrl, (uint8_t*)&data[32], 16, USB_CLASS_PCDC);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        __NOP();
    }
    while(!msgsent);

    err = R_USB_Write (&g_basic0_ctrl, (uint8_t*)&data[48], 16, USB_CLASS_PCDC);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        __NOP();
    }
    while(!msgsent);

}
/* We have not woken a task at the start of the ISR. */
BaseType_t xHigherPriorityTaskWoken = pdFALSE;
uint8_t lastcmd [4]= {0};
uint16_t cmdidx = 0;
uint16_t msgcnt = 0;
extern uint16_t current_temp;
/* Config Thread entry function */
/* pvParameters contains TaskHandle_t */
void config_thread0_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);
    R_USB_Open (&g_basic0_ctrl, &g_basic0_cfg);
    uint8_t msg[READ_BUF_SIZE];
    fsp_err_t err;
    InitAlarmDataBase();

    /*rtc_time_t time1;
    time1.tm_sec = 19;
    time1.tm_min = 40;
    time1.tm_hour =  15;
    time1.tm_mday = 6;
    time1.tm_mon = 1;
    time1.tm_year =  125;
    R_RTC_ClockSourceSet(&g_rtc0_ctrl);
    R_RTC_CalendarTimeSet(&g_rtc0_ctrl, &time1);*/

    while (1)
    {
        BaseType_t ret = xQueueReceive(g_configQue, msg, 1000);
        if(ret == pdTRUE){
            msgcnt++;
            lastcmd[cmdidx++] = msg[0];
            if(cmdidx >= 4){
                cmdidx = 0;
            }
            switch(msg[0]){
                case ReadUserConfig:

                    msg[0] = ReadUserConfig;
                    msg[1] = sizeof(device_config);
                    memcpy(&msg[2], &device_config, sizeof(device_config));
                    if(err != FSP_SUCCESS){
                        //while(1);
                    }
                    writeData(&msg[0], 64);
                    break;
                case SaveUserConfig:
                {
                    memcpy(&device_config, &msg[2], sizeof(device_config));
                    device_config.magic_word = 0xA5A5;
                    device_config.version = 1;
                    ConfigMgrWrite();
                    writeData(&msg[0], 64);
                    break;
                }
                case ReadMfgConfig:
                    ConfigMgrReadMfgData();
                    msg[0] = ReadMfgConfig;
                    msg[1] = sizeof(mfg_config);
                    mfg_config.sw_version = SW_VERSION;
                    memcpy(&msg[2], &mfg_config, sizeof(mfg_config));
                    writeData(&msg[0], 64);
                    break;
                case SaveMfgConfig:
                    memcpy(&mfg_config, &msg[2], sizeof(mfg_config));
                    mfg_config.magic_word = 0xA5A5;
                    ConfigMgrWriteMfgData();
                    writeData(&msg[0], 64);
                    break;
                case SetTime:
                {
                    rtc_time_t time;
                    time.tm_sec = msg[1];
                    time.tm_min = msg[2];
                    time.tm_hour =  msg[3];
                    time.tm_mday = msg[4];
                    time.tm_mon = msg[5];
                    time.tm_year =  msg[6];
                    R_RTC_ClockSourceSet(&g_rtc0_ctrl);
                    R_RTC_CalendarTimeSet(&g_rtc0_ctrl, &time);
                    writeData(&msg[0], 64);
                    break;
                }
                case GetTime:
                {
                    rtc_time_t time;
                    R_RTC_CalendarTimeGet(&g_rtc0_ctrl, &time);
                    msg[0] = (uint8_t)GetTime;
                    msg[1] = (uint8_t)time.tm_sec;
                    msg[2] = (uint8_t)time.tm_min;
                    msg[3] = (uint8_t)time.tm_hour;
                    msg[4] = (uint8_t)time.tm_mday;
                    msg[5] = (uint8_t)time.tm_mon;
                    msg[6] = (uint8_t)time.tm_year;
                    writeData(&msg[0], 64);
                    break;
                }

                case ReadFirstFaultCode:
                {
                    FaultCodeDbEntry_t* e = GetFirstEntry(0);
                    msg[0] = (uint8_t)ReadFirstFaultCode;
                    if(e != NULL){
                        msg[1] = (uint8_t)e->sec;
                        msg[2] = (uint8_t)e->min;
                        msg[3] = (uint8_t)e->hr;
                        msg[4] = (uint8_t)e->day;
                        msg[5] = (uint8_t)e->mon;
                        msg[6] = (uint8_t)e->year;
                        msg[7] = (uint8_t)e->fault_code;
                    } else {
                        msg[7] = NoAlarm;
                    }
                    writeData(&msg[0], 64);
                }
                    break;
                case ReadNextFaultCode:
                {
                    FaultCodeDbEntry_t* e = GetNextEntry();
                    msg[0] = (uint8_t)ReadNextFaultCode;
                    if(e != NULL){
                        msg[1] = (uint8_t)e->sec;
                        msg[2] = (uint8_t)e->min;
                        msg[3] = (uint8_t)e->hr;
                        msg[4] = (uint8_t)e->day;
                        msg[5] = (uint8_t)e->mon;
                        msg[6] = (uint8_t)e->year;
                        msg[7] = (uint8_t)e->fault_code;
                    } else {
                        msg[7] = NoAlarm;
                    }
                    writeData(&msg[0], 64);                }
                    break;
                case EraseFaultDb:
                    EraseFaultDataBase();
                    writeData(&msg[0], 64);
                    break;
                default:

                    break;

            }
        }
    }
}

volatile usb_pcdc_linecoding_t g_line_coding;
usb_pcdc_ctrllinestate_t g_control_line_state =
{
 .bdtr = 0,
 .brts = 0,
 .rsv = 0
};

void usb_pcdc_callback(usb_event_info_t * p_pcdc_event , usb_hdl_t task, usb_onoff_t state)
{
    FSP_PARAMETER_NOT_USED (task);
    FSP_PARAMETER_NOT_USED (state);
    switch (p_pcdc_event->event)
    {
        /* USB Read complete Class Request */
        case USB_STATUS_READ_COMPLETE:
        {
            R_USB_Read (&g_basic0_ctrl, g_buf, READ_BUF_SIZE, USB_CLASS_PCDC);
            xHigherPriorityTaskWoken = pdFALSE;
            xQueueSendFromISR(g_configQue, g_buf, 0);
            portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
        }
        break;

        /*  Write Complete Class Request */

        /* Configured state class request */
        case USB_STATUS_CONFIGURED:
        {
            R_USB_Read (&g_basic0_ctrl, g_buf, READ_BUF_SIZE, USB_CLASS_PCDC);
        }
        break;

        /* Receive Class Request */
        case USB_STATUS_REQUEST:
        {
            /* Check for the specific CDC class request IDs */
            if (USB_PCDC_SET_LINE_CODING == (p_pcdc_event->setup.request_type & USB_BREQUEST))
            {
                /* Get the class request.*/
                fsp_err_t err = R_USB_PeriControlDataGet (&g_basic0_ctrl, (uint8_t*) &g_line_coding, LINE_CODING_LENGTH);
                if(FSP_SUCCESS == err)
                {
                    /* Calculate the baud rate*/
                    g_baud_rate = g_line_coding.dw_dte_rate;
                }
            }

            else if (USB_PCDC_GET_LINE_CODING == (p_pcdc_event->setup.request_type & USB_BREQUEST))
            {
                /* Set the class request.*/
                R_USB_PeriControlDataSet (&g_basic0_ctrl, (uint8_t*) &g_line_coding, LINE_CODING_LENGTH);
            }
            else if (USB_PCDC_SET_CONTROL_LINE_STATE == (p_pcdc_event->setup.request_type & USB_BREQUEST))
            {
                /* Get the status of the control signals */
                fsp_err_t err = R_USB_PeriControlDataGet(&g_basic0_ctrl,
                                                         (uint8_t*) &g_control_line_state,
                                                         sizeof(usb_pcdc_ctrllinestate_t));
                if (FSP_SUCCESS == err)
                {
                    if (FSP_SUCCESS == err)
                    {
                        g_control_line_state.bdtr = (unsigned char)((p_pcdc_event->setup.request_value >> 0) & 0x01);
                        g_control_line_state.brts = (unsigned char)((p_pcdc_event->setup.request_value >> 1) & 0x01);
                    }
                }

                /* Set the usb status as ACK response.*/
                err = R_USB_PeriControlStatusSet (&g_basic0_ctrl, USB_SETUP_STATUS_ACK);
            }
            else
            {
                ;
            }
            return;


        }
        break;

        case USB_STATUS_WRITE_COMPLETE:
        {
            msgsent = true;
            __NOP();
        }
        break;
        /* Complete Class Request */
        case USB_STATUS_REQUEST_COMPLETE:
        {
            //R_USB_Read (&g_basic0_ctrl, g_buf, READ_BUF_SIZE, USB_CLASS_PCDC);
        }
        break;

        /* Detach, Suspend State Class requests */
        case USB_STATUS_DETACH:
            /* Stop all read/write transactions using R_USB_Stop */
        case USB_STATUS_SUSPEND:
        {
        }
        break;
        /* Resume state */
        case USB_STATUS_RESUME:
        {
        }
        break;

        default:
            return;
            break;
    }
}

void bgo_callback(flash_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED (p_args);
}
