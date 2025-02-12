
#include <math.h>
#include "max31865.h"
#include "fan_control_thread.h"

//#########################################################################################################################
#define MAX31856_CONFIG_REG             0x00
#define MAX31856_CONFIG_BIAS            0x80
#define MAX31856_CONFIG_MODEAUTO        0x40
#define MAX31856_CONFIG_MODEOFF         0x00
#define MAX31856_CONFIG_1SHOT           0x20
#define MAX31856_CONFIG_3WIRE           0x10
#define MAX31856_CONFIG_24WIRE          0x00
#define MAX31856_CONFIG_FAULTSTAT       0x02
#define MAX31856_CONFIG_FILT50HZ        0x01
#define MAX31856_CONFIG_FILT60HZ        0x00

#define MAX31856_RTDMSB_REG             0x01
#define MAX31856_RTDLSB_REG             0x02
#define MAX31856_HFAULTMSB_REG          0x03
#define MAX31856_HFAULTLSB_REG          0x04
#define MAX31856_LFAULTMSB_REG          0x05
#define MAX31856_LFAULTLSB_REG          0x06
#define MAX31856_FAULTSTAT_REG          0x07


#define MAX31865_FAULT_HIGHTHRESH       0x80
#define MAX31865_FAULT_LOWTHRESH        0x40
#define MAX31865_FAULT_REFINLOW         0x20
#define MAX31865_FAULT_REFINHIGH        0x10
#define MAX31865_FAULT_RTDINLOW         0x08
#define MAX31865_FAULT_OVUV             0x04


#define RTD_A (3.9083e-3f)
#define RTD_B (-5.775e-7f)

static volatile bool g_transfer_complete = false;
//#########################################################################################################################
static void  Max31865_delay(uint32_t delay_ms)
{
    vTaskDelay(delay_ms);
}

static void Exchange1Byte(uint8_t* txbyte, uint8_t*rxbyte)
{
    uint8_t dummy = 0xFF;
    g_transfer_complete = false;
    if(txbyte == NULL){
        txbyte = &dummy;
    } else if(rxbyte == NULL){
        rxbyte = &dummy;
        R_SPI_Write(&g_spi0_ctrl, txbyte, 1, SPI_BIT_WIDTH_8_BITS);
    } else {
        R_SPI_WriteRead(&g_spi0_ctrl, txbyte, rxbyte, 1, SPI_BIT_WIDTH_8_BITS);
    }
    while(g_transfer_complete == false);
}

//#########################################################################################################################
static void Max31865_readRegisterN(uint8_t addr, uint8_t *buffer, uint8_t n)
{
    uint8_t tmp = 0xFF;
    addr &= 0x7F;
    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_03, BSP_IO_LEVEL_LOW);

    //R_SPI_Write(&g_spi0_ctrl, &addr, 1, SPI_BIT_WIDTH_8_BITS);
    Exchange1Byte(&addr, NULL);

    while (n--)
    {
        //R_SPI_WriteRead(&g_spi0_ctrl, &tmp, buffer, 1, SPI_BIT_WIDTH_8_BITS);
        Exchange1Byte(&tmp, buffer);
        buffer++;
    }
    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_03, BSP_IO_LEVEL_HIGH);
}
//#########################################################################################################################
static uint8_t Max31865_readRegister8(uint8_t addr)
{
    uint8_t ret = 0;
    Max31865_readRegisterN(addr, &ret, 1);
    return ret;
}
//#########################################################################################################################
static uint16_t Max31865_readRegister16(uint8_t addr)
{
    uint8_t buffer[2] = {0, 0};
    Max31865_readRegisterN(addr, buffer, 2);
    uint16_t ret = buffer[0];
    ret <<= 8;
    ret =  ((uint16_t)ret | buffer[1]);
    return ret;
}
//#########################################################################################################################
static void Max31865_writeRegister8(uint8_t addr, uint8_t data)
{
    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_03, BSP_IO_LEVEL_LOW);
    addr |= 0x80;
    //R_SPI_Write(&g_spi0_ctrl, &addr, 1, SPI_BIT_WIDTH_8_BITS);
    Exchange1Byte(&addr, NULL);
    //R_SPI_Write(&g_spi0_ctrl, &data, 1, SPI_BIT_WIDTH_8_BITS);
    Exchange1Byte(&data, NULL);
    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_03, BSP_IO_LEVEL_HIGH);
}
//#########################################################################################################################
static uint8_t Max31865_readFault()
{
  return Max31865_readRegister8(MAX31856_FAULTSTAT_REG);
}
//#########################################################################################################################
static void Max31865_clearFault()
{
    uint8_t t = Max31865_readRegister8(MAX31856_CONFIG_REG);
    t &= (uint8_t)~0x2C;
    t |= MAX31856_CONFIG_FAULTSTAT;
    Max31865_writeRegister8( MAX31856_CONFIG_REG, t);
}
//#########################################################################################################################
static void Max31865_enableBias(uint8_t enable)
{
    uint8_t t = Max31865_readRegister8( MAX31856_CONFIG_REG);
    if (enable)
        t |= MAX31856_CONFIG_BIAS;
    else
        t &= (uint8_t) ~MAX31856_CONFIG_BIAS;
    Max31865_writeRegister8( MAX31856_CONFIG_REG, t);
}
//#########################################################################################################################
static void Max31865_autoConvert(uint8_t enable)
{
    uint8_t t = Max31865_readRegister8( MAX31856_CONFIG_REG);
    if (enable)
        t |= MAX31856_CONFIG_MODEAUTO;
    else
        t &= (uint8_t)~MAX31856_CONFIG_MODEAUTO;
    Max31865_writeRegister8( MAX31856_CONFIG_REG, t);
}
//#########################################################################################################################
static void Max31865_setWires(uint8_t numWires)
{
    uint8_t t = Max31865_readRegister8(MAX31856_CONFIG_REG);
    if (numWires == 3)
        t |= MAX31856_CONFIG_3WIRE;
    else
        t &= (uint8_t) ~MAX31856_CONFIG_3WIRE;
    Max31865_writeRegister8(MAX31856_CONFIG_REG, t);
}
//#########################################################################################################################
static void Max31865_setFilter(uint8_t filterHz)
{
    uint8_t t = Max31865_readRegister8( MAX31856_CONFIG_REG);
    if (filterHz == 50)
        t |= MAX31856_CONFIG_FILT50HZ;
    else
        t &= (uint8_t)~MAX31856_CONFIG_FILT50HZ;
    Max31865_writeRegister8(MAX31856_CONFIG_REG, t);
}
//#########################################################################################################################
static uint16_t Max31865_readRTD ()
{
    Max31865_clearFault();
    Max31865_enableBias(1);
    Max31865_delay(10);
    uint8_t t = Max31865_readRegister8(MAX31856_CONFIG_REG);
    t |= MAX31856_CONFIG_1SHOT;
    Max31865_writeRegister8(MAX31856_CONFIG_REG, t);
    Max31865_delay(65);
    uint16_t rtd = Max31865_readRegister16(MAX31856_RTDMSB_REG);
    rtd >>= 1;
    return rtd;
}
//#########################################################################################################################
//#########################################################################################################################
//#########################################################################################################################
void  Max31865_init(uint8_t  numwires, uint8_t filterHz)
{
  Max31865_delay(1);

  R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_03, BSP_IO_LEVEL_HIGH);
  Max31865_delay(100);
  Max31865_setWires(numwires);
  Max31865_enableBias(0);
  Max31865_autoConvert(0);
  Max31865_clearFault();
  Max31865_setFilter(filterHz);
}
//#########################################################################################################################
bool Max31865_readTempC(float *readTemp)
{
    Max31865_delay(1);
    bool isOk = false;
    float Z1, Z2, Z3, Z4, Rt, temp;
    Rt = Max31865_readRTD();
    Rt /= 32768;
    Rt *= _MAX31865_RREF;
    Z1 = -RTD_A;
    Z2 = RTD_A * RTD_A - (4 * RTD_B);
    Z3 = (4 * RTD_B) / _MAX31865_RNOMINAL;
    Z4 = 2 * RTD_B;
    temp = Z2 + (Z3 * Rt);
    temp = (sqrtf(temp) + Z1) / Z4;

    if (temp >= 0)
  {
    *readTemp = temp;
    if(Max31865_readFault() == 0)
      isOk = true;
    return isOk;
  }
    Rt /= _MAX31865_RNOMINAL;
    Rt *= 100;
    float rpoly = Rt;
    temp = -242.02f;
    temp += 2.2228f * rpoly;
    rpoly *= Rt;  // square
    temp += 2.5859e-3f * rpoly;
    rpoly *= Rt;  // ^3
    temp -= 4.8260e-6f * rpoly;
    rpoly *= Rt;  // ^4
    temp -= 2.8183e-8f * rpoly;
    rpoly *= Rt;  // ^5
    temp += 1.5243e-10f * rpoly;

  *readTemp = temp;
  if(Max31865_readFault() == 0)
    isOk = true;
  return isOk;
}
//#########################################################################################################################
bool  Max31865_readTempF(float *readTemp)
{
  bool isOk = Max31865_readTempC(readTemp);
  *readTemp = (*readTemp * 9.0f / 5.0f) + 32.0f;
  return isOk;
}
//#########################################################################################################################
float Max31865_Filter(float newInput, float lastOutput, float efectiveFactor)
{
    return ((float)lastOutput*(1.0f-efectiveFactor)) + ((float)newInput*efectiveFactor) ;
}
//#########################################################################################################################

/* Callback function */
void spi_callback(spi_callback_args_t *p_args)
{
    /* TODO: add your own code here */
    if (SPI_EVENT_TRANSFER_COMPLETE == p_args->event)
    {
        g_transfer_complete = true;
    }
}

