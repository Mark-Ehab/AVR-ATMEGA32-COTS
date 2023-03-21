/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Mar 16, 2023               	*/
/*              SWC              : EEPROM			*/
/*              Description	 : EEPROM Program               */
/* 	        Version          : V1.0                         */
/****************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_ERRORS.h"
#include "../../LIB/SERVICE_FUNCTIONS.h"

#include "../../MCAL/TWI/TWI_Interface.h"

#include "EEPROM_Interface.h"
#include "EEPROM_Private.h"
#include "EEPROM_Config.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  PUBLIC FUNCTIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize EEPROM		                                  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void EEPROM_vidInit(void)
{
	/* Initialize this Node as Master Node in the Network to Communicate with EEPROM (Slave Node) */
	TWI_vidMasterInit();
}
/**********************************************************************************/
/* Description     : Send data byte to be written on a specific byte of EEPROM    */
/* Input Arguments : u16 Copy_u16ByteAddress , u8 Copy_u8DataByteToBeSend	  */
/* Return          : void						          */
/**********************************************************************************/
void EEPROM_vidSendDataByte(u16 Copy_u16ByteAddress , u8 Copy_u8DataByteToBeSend)
{
	/* Local Variables Definitions */
	u8 Local_u8Address;

	/* Send Start Condition on the Bus to Begin Communication with EEPROM */
	TWI_SendStartCondition();

	/* Check EEPROM Number */
	#if   EEPROM_NUM == EEPROM_1

		/* Calculate Address */
		Local_u8Address = ((EEPROM_ADDRESS_FIXED_SEQENCE << 3) | (EEPROM_NUM << 2) | (Copy_u16ByteAddress >> 8));

		/* Send EEPROM Address (Slave Address) Plus Write Option On the bus (TWI Address Packet) */
		TWI_SendSlaveAddressWithWrite(Local_u8Address);

	#elif EEPROM_NUM == EEPROM_2

		/* Calculate Address */
		Local_u8Address = ((EEPROM_ADDRESS_FIXED_SEQENCE << 3) | (EEPROM_NUM << 2) | (Copy_u16ByteAddress >> 8));

		/* Send EEPROM Address (Slave Address) Plus Write Option On the bus (TWI Address Packet) */
		TWI_SendSlaveAddressWithWrite(Local_u8Address);

	#else
		#error " Wrong EEPROM Number Configuration ! "
	#endif

	/* Send On the Bus EEPROM Byte (Page) Address Desired to Write Data On (TWI Data Packet) */
	TWI_MasterSendDataByte((u8)Copy_u16ByteAddress);

	/* Send Desired Data To Be Written On Addressed Byte of EEPROM (TWI Data Packet) */
	TWI_MasterSendDataByte(Copy_u8DataByteToBeSend);

	/* Send Stop Condition on the Bus to End Communication with EEPROM */
	TWI_SendStopCondition();
}
/**********************************************************************************/
/* Description     : Read data byte from a specific byte of EEPROM                */
/* Input Arguments : u16 Copy_u16ByteAddress , u8* Copy_pu8DataByteToBeReceived	  */
/* Return          : void						          */
/**********************************************************************************/
void EEPROM_vidReadDataByte(u16 Copy_u16ByteAddress , u8* Copy_pu8DataByteToBeReceived)
{
	/* Local Variables Definitions */
	u8 Local_u8Address;

	/* Send Start Condition on the Bus to Begin Communication with EEPROM */
	TWI_SendStartCondition();

	/* Check EEPROM Number */
	#if   EEPROM_NUM == EEPROM_1

		/* Calculate Address */
		Local_u8Address = ((EEPROM_ADDRESS_FIXED_SEQENCE << 3) | (EEPROM_NUM << 2) | (Copy_u16ByteAddress >> 8));

		/* Send EEPROM Address (Slave Address) Plus Write Option On the bus (TWI Address Packet) */
		TWI_SendSlaveAddressWithWrite(Local_u8Address);

	#elif EEPROM_NUM == EEPROM_2

		/* Calculate Address */
		Local_u8Address = ((EEPROM_ADDRESS_FIXED_SEQENCE << 3) | (EEPROM_NUM << 2) | (Copy_u16ByteAddress >> 8));

		/* Send EEPROM Address (Slave Address) Plus Write Option On the bus (TWI Address Packet) */
		TWI_SendSlaveAddressWithWrite(Local_u8Address);

	#else
		#error " Wrong EEPROM Number Configuration ! "
	#endif

	/* Send On the Bus EEPROM Byte (Page) Address Desired to Read Data From (TWI Data Packet) */
	TWI_MasterSendDataByte((u8)Copy_u16ByteAddress);

	/* Send Repeated Start Condition on the Bus to Start Receiving Data From Addressed EEPROM Byte  */
	TWI_SendRepeatedStartCondition();

	/* Check EEPROM Number */
	#if   EEPROM_NUM == EEPROM_1

		/* Calculate Address */
		Local_u8Address = ((EEPROM_ADDRESS_FIXED_SEQENCE << 3) | (EEPROM_NUM << 2) | (Copy_u16ByteAddress >> 8));

		/* Send EEPROM Address (Slave Address) Plus Read Option On the bus (TWI Address Packet) */
		TWI_SendSlaveAddressWithRead(Local_u8Address);

	#elif EEPROM_NUM == EEPROM_2

		/* Calculate Address */
		Local_u8Address = ((EEPROM_ADDRESS_FIXED_SEQENCE << 3) | (EEPROM_NUM << 2) | (Copy_u16ByteAddress >> 8));

		/* Send EEPROM Address (Slave Address) Plus Read Option On the bus (TWI Address Packet) */
		TWI_SendSlaveAddressWithRead(Local_u8Address);

	#else
		#error " Wrong EEPROM Number Configuration ! "
	#endif

	/* Read Desired Data Byte From Addressed Byte of EEPROM (TWI Data Packet)*/
	TWI_MasterReadDataByte(Copy_pu8DataByteToBeReceived);

	/* Send Stop Condition on the Bus to End Communication with EEPROM */
	TWI_SendStopCondition();
}