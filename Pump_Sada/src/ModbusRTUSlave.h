#pragma once

#include <stdint.h>
#include "IModbusSlaveDevice.h"


typedef enum {
   ReadCoils = 1,
   ReadDescretes = 2,
   ReadHolding = 3,
   ReadInput = 4,
   WriteCoil = 5,
   WriteHolding = 6,
   WriteMultipleCoils = 15,
   WriteMultipleHolding = 16
}FunctionCode_e;

typedef enum {
   SlaveId,
   FuncId,
   AddrHi,
   AddrLo,
   NumHi,
   NumLo
}Offsets_e;

typedef enum {
   IllegalFunction = 1,
   IllelgalDataAddress,
   IllegalDataValue,
   SlaveDeviceFailure,
   Acknowledge,
   SlaveDeviceBusy,
   MemoryParityError,
   GatewayPathNotAvailable,
   GatewayTargetDeviceFailedToRespond
}ModbusExceptionCodes_e;


class ModbusRTUSlave
{
    uint16_t ProcessException(ModbusExceptionCodes_e exc, uint8_t Func, uint8_t* response);
   void ProcessWriteCoil(uint16_t addr, uint16_t value);
   DataValueState_e ProcessWriteHolding(uint16_t addr, uint16_t value);
   uint16_t ProcessReadInput(uint16_t addr, uint16_t count, uint8_t* response);
   uint16_t ProcessReadHolding(uint16_t addr, uint16_t count, uint8_t* response);
   uint16_t ProcessReadDescretes(uint16_t addr, uint16_t count, uint8_t* response);
   uint16_t ProcessReadCoils(uint16_t addr, uint16_t count, uint8_t* response);
   uint16_t ModRTU_CRC(uint8_t* buf, int len);

   uint8_t m_MyId = 0;
   IModbusSlaveDevice* m_SlaveDevice;

public:

   ModbusRTUSlave(uint8_t slaveid, IModbusSlaveDevice* slave);
   void ProcessMessage(uint8_t* msg, uint16_t len, uint8_t* response, uint16_t* rsplen);
   void SetModbusSlaveId(uint8_t id);
};
