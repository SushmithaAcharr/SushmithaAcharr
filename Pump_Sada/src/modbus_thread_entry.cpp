#include "modbus_thread.h"
/* Modbus Thread entry function */
#include "ModbusRTUSlave.h"
#include "AspDevice.h"
#include "Event.h"
#include "r_flash_hp.h"
#include "r_flash_api.h"
#include "FlashStorage.h"
#include "UserConfig.h"
#include "ConfigManager.h"
#include "display_comm.h"
#include "UiPAges/DashBoard.h"

#define MAX_BUFER_SIZE  (256)
#define MAX_RS485_FAIL_COUNT  (5)
bool g_rs485Comm_status_on_display = false;
extern flash_hp_instance_ctrl_t g_flash0_ctrl;
extern const flash_cfg_t g_flash0_cfg;
UserConfig_t device_config;
AspDevice aspdevice;
static ModbusRTUSlave slave(0x34, &aspdevice);
static volatile uint8_t g_uart_event = 0;
QueueHandle_t g_modbus_que;
static uint8_t RS485RxData[MAX_BUFER_SIZE];
static uint16_t RS485RxIdx = 0;

StaticQueue_t g_modbus_que_memory;
uint8_t g_modbus_que_queue_memory[300 * 2];


static Event_t cmd;
static uint8_t response[256];
static uint16_t rsplen;
static uint8_t rs485_fail_count = 0;
/* pvParameters contains TaskHandle_t */
void modbus_thread_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);
    RS485RxIdx = 0;

    g_modbus_que =xQueueCreateStatic (
                                    2,
                                    sizeof(Event_t),
                                    &g_modbus_que_queue_memory[0], &g_modbus_que_memory
                                    );
    //set to rx message
    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_07, BSP_IO_LEVEL_LOW);

    R_FLASH_HP_Open(&g_flash0_ctrl, &g_flash0_cfg);
    ConfigMgrInit();

    uart_cfg_t cfg;
    memcpy(&cfg, &g_uart0_cfg, sizeof(g_uart0_cfg));
    cfg.data_bits = UART_DATA_BITS_8;

    if(device_config.parity == 3){
        cfg.parity = UART_PARITY_EVEN;
    } else if(device_config.parity == 2){
        cfg.parity = UART_PARITY_ODD;
    } else {
        cfg.parity = UART_PARITY_OFF;
    }
    if(device_config.stop_bits == 2){
        cfg.stop_bits = UART_STOP_BITS_2;
    } else {
        cfg.stop_bits = UART_STOP_BITS_1;
    }
    /* Initialize UART channel with baud rate */
    R_SCI_UART_Open (&g_uart0_ctrl, &cfg);
    baud_setting_t baud;
    uint32_t rate = 0;
    switch(device_config.baud_rate)
    {
        case 1:
            rate = 1200;
            break;
        case 2:
            rate = 2400;
            break;
        case 3:
            rate = 4800;
            break;
        case 4:
            rate = 9600;
            break;
        case 5:
            rate = 19200;
            break;
        case 6:
            rate = 38400;
            break;
        case 7:
            rate = 115200;
            break;
    }
    R_SCI_UART_BaudCalculate(rate, false, 0, &baud);
    R_SCI_UART_BaudSet(&g_uart0_ctrl, &baud);
    slave.SetModbusSlaveId(device_config.device_id);
    while(1){
        if(xQueueReceive(g_modbus_que, &cmd, 1000) == pdTRUE){
            rs485_fail_count = 0;
            if (cmd.evt == MODBUS_RS485_MESSAGE_RXED){
                slave.ProcessMessage(cmd.buffer, cmd.size, response, &rsplen);
                if(rsplen > 0){
                    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_07, BSP_IO_LEVEL_HIGH);
                    vTaskDelay(2);
                    R_SCI_UART_Write(&g_uart0_ctrl, response, rsplen);
                }
            }
            g_rs485Comm_status_on_display = true;
        }
        else{
            rs485_fail_count++;
            if(rs485_fail_count >= MAX_RS485_FAIL_COUNT){
                g_rs485Comm_status_on_display = false;
            }
        }
    }
}

void uart_callback(uart_callback_args_t * p_args)
{
    /* Logged the event in global variable */
    g_uart_event = (uint8_t)p_args->event;

    if(UART_EVENT_RX_CHAR == p_args->event)
    {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        RS485RxData[RS485RxIdx++] = (uint8_t ) p_args->data;
        xTimerResetFromISR(RS485T35Timer, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    }
    if(UART_EVENT_TX_COMPLETE == p_args->event)
    {
        R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_07, BSP_IO_LEVEL_LOW);
    }
}

void vRS485TimerCallbackT35(TimerHandle_t)
{
    Event_t e;
    e.evt = MODBUS_RS485_MESSAGE_RXED;
    e.size = RS485RxIdx;
    memcpy(e.buffer, RS485RxData, e.size);
    RS485RxIdx = 0;
    xQueueSend(g_modbus_que, &e, 0);

}
