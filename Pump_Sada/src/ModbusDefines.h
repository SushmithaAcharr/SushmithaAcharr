/*
 * ModbusDefines.h
 *
 *  Created on: Oct 2, 2022
 *      Author: Sankalp
 */

#ifndef APP_INC_MODBUSDEFINES_H_
#define APP_INC_MODBUSDEFINES_H_

typedef enum
{
    RS232_HW = 1,
    RS485_HW = 2,
    TCP_HW = 3,
}ModbusHardware_t ;

typedef enum
{
    MB_FC_READ_COILS               = 1,	 /*read coils or digital outputs */
    MB_FC_READ_DISCRETE_INPUT      = 2,	 /*read digital inputs */
    MB_FC_READ_REGISTERS           = 3,	 /*read registers or analog outputs */
    MB_FC_READ_INPUT_REGISTER      = 4,	 /*read analog inputs */
    MB_FC_WRITE_COIL               = 5,	 /*write single coil or output */
    MB_FC_WRITE_REGISTER           = 6,	 /*write single register */
    MB_FC_WRITE_MULTIPLE_COILS     = 15, /*write multiple coils or outputs */
    MB_FC_WRITE_MULTIPLE_REGISTERS = 16	 /*write multiple registers */
}ModbusFunctionCode_e;

typedef enum
{
    ID                             = 0, //!< ID field
    FUNC, //!< Function code position
    ADD_HI, //!< Address high byte
    ADD_LO, //!< Address low byte
    NB_HI, //!< Number of coils or registers high byte
    NB_LO, //!< Number of coils or registers low byte
    BYTE_CNT  //!< byte counter
}ModbusMessageOffsets_e;

typedef enum
{
    ERR_NOT_MASTER                = -1,
    ERR_POLLING                   = -2,
    ERR_BUFF_OVERFLOW             = -3,
    ERR_BAD_CRC                   = -4,
    ERR_EXCEPTION                 = -5,
    ERR_BAD_SIZE                  = -6,
    ERR_BAD_ADDRESS               = -7,
    ERR_TIME_OUT		          = -8,
    ERR_BAD_SLAVE_ID		      = -9,
	ERR_BAD_TCP_ID		          = -10,
	ERR_OK_QUERY				  = -11,
	ERR_WRONGID					  = -12

}ModbusErrot_t;

typedef enum{
	MasterDevice,
	RS232RTU,
	RS485RTU,
	TCPModbus
}SlaveType_e;

typedef enum{
	BigEndian,
	LittleEndian,
}SlaveEndianness_e;


#endif /* APP_INC_MODBUSDEFINES_H_ */
