#include "display_thread.h"
#include "display_comm.h"
//#include "UI.h"
/* Display entry function */

typedef enum{
    WaitForStartOfPacket,
    DispWaitingForHeader2,
    DispWaitingForLength,
    DisplayWaitingForPayload,
}disp_rx_state_e;

/* pvParameters contains TaskHandle_t */
#define MAX_DISPLAY_COMM_RX_BUFFER      (512)
#define MAX_DISPLAY_COMM_TX_BUFFER      (256)
#define MAX_PAYLOAD                     (256)

#define DWIN_HEADER_PAT1    (0x5A)
#define DWIN_HEADER_PAT2    (0xA5)

#define WRITE_ACK_START     ('O')
#define WRITE_ACK_END       ('K')

extern QueueHandle_t g_ui_que;

static uint8_t disp_rx_buf[MAX_DISPLAY_COMM_RX_BUFFER];
static int disp_read_idx = 0;
static int disp_write_idx = 0;
static disp_rx_state_e disp_rx_state = WaitForStartOfPacket;

static uint8_t disp_tx_buf[MAX_DISPLAY_COMM_TX_BUFFER];

static int payload_length;
static uint8_t disp_payload[MAX_PAYLOAD];

static DisplayMsg_t msg;
DisplayMsg_t rxmsg;
static void ParsePayload()
{
    rxmsg.cmd = (DWINCommands_e)disp_payload[0];
    rxmsg.address = disp_payload[1];
    rxmsg.address <<= 8;
    rxmsg.address = (rxmsg.address | (uint16_t)disp_payload[2]);
    rxmsg.num_of_words = disp_payload[3];
    int idx = 4;
    for(int i = 0 ; i < disp_payload[3]; i++){
        rxmsg.data[i] = disp_payload[idx++];
        rxmsg.data[i] <<= 8;
        rxmsg.data[i] |= disp_payload[idx++];
    }

    xQueueSend(g_ui_que, &rxmsg, 0);

}
extern QueueHandle_t display_tx_que;
int x = 0;
void display_thread_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);
    R_SCI_UART_Open (&g_uart1_ctrl, &g_uart1_cfg);
    int payloadidx = 0;
    /* TODO: add your own code here */
    while (1)
    {
        BaseType_t ret = xQueueReceive(display_tx_que, &msg, 0);
        if(ret == pdTRUE){
            disp_tx_buf[0] = DWIN_HEADER_PAT1;
            disp_tx_buf[1] = DWIN_HEADER_PAT2;
            disp_tx_buf[3] = (uint8_t)msg.cmd;
            disp_tx_buf[4] = (uint8_t)((msg.address >> 8) & 0xFF) ;
            disp_tx_buf[5] = (uint8_t)((msg.address) & 0xFF) ;
            int idx = 6;
            if(msg.cmd == READ_DATA_FROM_ADDRES){
                disp_tx_buf[2] = (uint8_t)(msg.reg_cnt*2 + 2); //cmd + reg cnt
                disp_tx_buf[idx++] = msg.reg_cnt;
            } else if(msg.cmd == WRITE_DATA_TO_ADDRES){
                disp_tx_buf[2] = (uint8_t)(msg.reg_cnt*2 + 2) + 1; //cmd + reg cnt
                for(int i = 0 ; i < msg.reg_cnt; i++){
                    disp_tx_buf[idx++] = (uint8_t)((msg.data[i] >> 8) & 0xFF) ;
                    disp_tx_buf[idx++] = (uint8_t)((msg.data[i]) & 0xFF) ;
                }
            }
            R_SCI_UART_Write(&g_uart1_ctrl, disp_tx_buf, idx);
        } else {
            while(disp_read_idx != disp_write_idx){
                switch(disp_rx_state){
                    case WaitForStartOfPacket:
                        if(disp_rx_buf[disp_read_idx] == DWIN_HEADER_PAT1){
                            disp_rx_state = DispWaitingForHeader2;
                        }
                        break;
                    case DispWaitingForHeader2:
                        if(disp_rx_buf[disp_read_idx] == DWIN_HEADER_PAT2){
                            disp_rx_state = DispWaitingForLength;
                        }
                        break;
                    case DispWaitingForLength:
                        payload_length = disp_rx_buf[disp_read_idx];
                        disp_rx_state = DisplayWaitingForPayload;
                        payloadidx = 0;
                        break;
                    case DisplayWaitingForPayload:
                        disp_payload[payloadidx++] = disp_rx_buf[disp_read_idx];
                        if(payloadidx >= payload_length){
                            ParsePayload();
                            disp_rx_state = WaitForStartOfPacket;
                        }
                        break;
                }
                disp_read_idx++;
                if(disp_read_idx >= MAX_DISPLAY_COMM_RX_BUFFER){
                    disp_read_idx = 0;
                }
            }
        }
        vTaskDelay (1);
    }
}
/* Callback function */
void display_comm_handle(uart_callback_args_t *p_args)
{
    /* Logged the event in global variable */
    if(UART_EVENT_RX_CHAR == p_args->event)
    {
        disp_rx_buf[disp_write_idx++] = (uint8_t ) p_args->data;
        if(disp_write_idx >= MAX_DISPLAY_COMM_RX_BUFFER){
            disp_write_idx = 0;
        }
    }
    if(UART_EVENT_TX_COMPLETE == p_args->event)
    {
    }
}
