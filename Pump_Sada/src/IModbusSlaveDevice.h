#pragma once
#include <stdint.h>

typedef enum {
   ValueAccepted = 0,
   ValueInvalid
} DataValueState_e;

class IModbusSlaveDevice
{
public:

   virtual uint16_t GetCoilCount() = 0;
   virtual uint16_t GetDescreteInputCount() = 0;
   virtual uint16_t GetHoldingRegisterCount() = 0;
   virtual uint16_t GetInputRegisterCountCount() = 0;

   virtual bool GetCoilValue(uint16_t offset) = 0;
   virtual bool GetDescreteInputValue(uint16_t offset) = 0;
   virtual uint16_t GetHoldingRegisterValue(uint16_t offset) = 0;
   virtual uint16_t GetInputRegisterValue(uint16_t offset) = 0;

   virtual DataValueState_e SetCoilValue(uint16_t offset, bool value) = 0;
   virtual DataValueState_e SetHoldingRegister(uint16_t offset, uint16_t value) = 0;
   virtual bool IsValidHoldingRegisterAddress(uint16_t addr) = 0;
   virtual bool IsValidInputRegisterAddress(uint16_t addr) = 0;
};
