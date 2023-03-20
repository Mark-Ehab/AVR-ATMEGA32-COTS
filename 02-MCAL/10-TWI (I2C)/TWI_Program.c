/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Mar 15, 2023               	*/
/*              SWC              : TWI  	        	*/
/*              Description	 : TWI Program                  */
/* 	        Version          : V1.0                         */
/****************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_ERRORS.h"
#include "../../LIB/SERVICE_FUNCTIONS.h"

#include "TWI_Interface.h"
#include "TWI_Private.h"
#include "TWI_Config.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  PUBLIC FUNCTIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize this node as TWI master                           */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void TWI_vidMasterInit(void)
{
	/******************************************Calculate Bit Rate Based on Selected TWI Prescaler from Config File*****************************************/
	/* Check Selected TWI Prescaler from Config File */
	#if   TWI_Prescaler_VAL == _1_PRESCALER

		/* Set Selected TWI Prescaler */
		CLR_BIT(TWSR,TWSR_TWPS0);
		CLR_BIT(TWSR,TWSR_TWPS1);

		/* Calculate Bit Rate to be set in TWBR register */
		TWBR = (u8)((TWI_FCPU - (16UL * TWI_SCL)) / (2UL * SERV_u32Pow(4,TWI_Prescaler_VAL) * TWI_SCL));

	#elif TWI_Prescaler_VAL == _4_PRESCALER

		/* Set Selected TWI Prescaler */
		SET_BIT(TWSR,TWSR_TWPS0);
		CLR_BIT(TWSR,TWSR_TWPS1);

		/* Calculate Bit Rate to be set in TWBR register */
		TWBR = (u8)((TWI_FCPU - (16UL * TWI_SCL)) / (2UL * SERV_u32Pow(4,TWI_Prescaler_VAL) * TWI_SCL));

	#elif TWI_Prescaler_VAL == _16_PRESCALER

		/* Set Selected TWI Prescaler */
		CLR_BIT(TWSR,TWSR_TWPS0);
		SET_BIT(TWSR,TWSR_TWPS1);

		/* Calculate Bit Rate to be set in TWBR register */
		TWBR = (u8)((TWI_FCPU - (16UL * TWI_SCL)) / (2UL * SERV_u32Pow(4,TWI_Prescaler_VAL) * TWI_SCL));

	#elif TWI_Prescaler_VAL == _64_PRESCALER

		/* Set Selected TWI Prescaler */
		SET_BIT(TWSR,TWSR_TWPS0);
		SET_BIT(TWSR,TWSR_TWPS1);

		/* Calculate Bit Rate to be set in TWBR register */
		TWBR = (u8)((TWI_FCPU - (16UL * TWI_SCL)) / (2UL * SERV_u32Pow(4,TWI_Prescaler_VAL) * TWI_SCL));

	#else
		#error " Wrong TWI Prescaler Configuration ! "
	#endif


	/******************************************Enable/Disable TWI Acknowledge Bit for this Node Based on Config File*****************************************/
	/* Check if TWI Acknowledge Bit is Enabled or Not for this Node from Config File */
	#if   TWI_ACK_BIT_ENABLE == ENABLE

		/* Enable Acknowledge Bit */
		SET_BIT(TWCR,TWCR_TWEA);

	#elif TWI_ACK_BIT_ENABLE == DISABLE

		/* Disable Acknowledge Bit */
		CLR_BIT(TWCR,TWCR_TWEA);

	#else
		#error " Wrong TWI Acknowledge Bit Enable Signal Configuration ! "
	#endif


	/******************************************Enable/Disable TWI Interrupt*****************************************/
	/* Check if TWI Interrupt is Enabled or Not for this Node from Config File */
	#if   TWI_INTERRUPT_ENABLE == ENABLE

		/* Enable TWI Interrupt */
		SET_BIT(TWCR,TWCR_TWIE);

	#elif TWI_INTERRUPT_ENABLE == DISABLE

		/* Disable TWI Interrupt */
		CLR_BIT(TWCR,TWCR_TWIE);

	#else
		#error " Wrong TWI Interrupt Enable Signal Configuration ! "
	#endif


	/******************************************Enable/Disable TWI General Call Recognition*****************************************/
	/* Check if TWI General Call Recognition is Enabled or Not for this Node from Config File */
	#if   TWI_GENERAL_CALL_RECOGNITION_ENABLE == ENABLE

		/* Enable TWI General Call Recognition */
		SET_BIT(TWAR,TWAR_TWGCE);

	#elif TWI_GENERAL_CALL_RECOGNITION_ENABLE == DISABLE

		/* Disable TWI General Call Recognition */
		CLR_BIT(TWAR,TWAR_TWGCE);

	#else
		#error " Wrong TWI Interrupt Enable Signal Configuration ! "
	#endif


	/******************************************Enable TWI*****************************************/
	SET_BIT(TWCR,TWCR_TWEN);
}
/**********************************************************************************/
/* Description     : Initialize this node as TWI slave                            */
/* Input Arguments : u8 Copy_u8SlaveAddress				          */
/* Return          : void						          */
/**********************************************************************************/
void TWI_vidSlaveInit(u8 Copy_u8SlaveAddress)
{
	/******************************************Set Passed Slave Address to Be the Own Address of this Node*****************************************/
	/* Load Passed Slave Address to the Most Significant 7 Bits of TWAR Register */
	TWAR |= (Copy_u8SlaveAddress << 1);


	/******************************************Enable/Disable TWI Acknowledge Bit for this Node Based on Config File*****************************************/
	/* Check if TWI Acknowledge Bit is Enabled or Not for this Node from Config File */
	#if   TWI_ACK_BIT_ENABLE == ENABLE

		/* Enable Acknowledge Bit */
		SET_BIT(TWCR,TWCR_TWEA);

	#elif TWI_ACK_BIT_ENABLE == DISABLE

		/* Disable Acknowledge Bit */
		CLR_BIT(TWCR,TWCR_TWEA);

	#else
		#error " Wrong TWI Acknowledge Bit Enable Signal Configuration ! "
	#endif


	/******************************************Enable/Disable TWI Interrupt*****************************************/
	/* Check if TWI Interrupt is Enabled or Not for this Node from Config File */
	#if   TWI_INTERRUPT_ENABLE == ENABLE

		/* Enable TWI Interrupt */
		SET_BIT(TWCR,TWCR_TWIE);

	#elif TWI_INTERRUPT_ENABLE == DISABLE

		/* Disable TWI Interrupt */
		CLR_BIT(TWCR,TWCR_TWIE);

	#else
		#error " Wrong TWI Interrupt Enable Signal Configuration ! "
	#endif


	/******************************************Enable/Disable TWI General Call Recognition*****************************************/
	/* Check if TWI General Call Recognition is Enabled or Not for this Node from Config File */
	#if   TWI_GENERAL_CALL_RECOGNITION_ENABLE == ENABLE

		/* Enable TWI General Call Recognition */
		SET_BIT(TWAR,TWAR_TWGCE);

	#elif TWI_GENERAL_CALL_RECOGNITION_ENABLE == DISABLE

		/* Disable TWI General Call Recognition */
		CLR_BIT(TWAR,TWAR_TWGCE);

	#else
		#error " Wrong TWI Interrupt Enable Signal Configuration ! "
	#endif


	/******************************************Enable TWI*****************************************/
	SET_BIT(TWCR,TWCR_TWEN);
}
/**********************************************************************************/
/* Description     : Enable TWI Interrupt                                         */
/* Input Arguments : void 						          */
/* Return          : void						          */
/**********************************************************************************/
void TWI_vidEnableInterrupt(void)
{
	/* Enable TWI Interrupt */
	SET_BIT(TWCR,TWCR_TWIE);
}
/**********************************************************************************/
/* Description     : Disable TWI Interrupt                                        */
/* Input Arguments : void 						          */
/* Return          : void						          */
/**********************************************************************************/
void TWI_vidDisableInterrupt(void)
{
	/* Disable TWI Interrupt */
	CLR_BIT(TWCR,TWCR_TWIE);
}
/**********************************************************************************/
/* Description     : Send Start Condition on the bus to start communication while */
/*		     SCL is in high state					  */
/* Input Arguments : void						          */
/* Return          : TWI_ErrorStatus_e			             	          */
/**********************************************************************************/
TWI_ErrorStatus_e TWI_SendStartCondition(void)
{
	/* Local Variables Definitions */
	TWI_ErrorStatus_e Local_ErrorStatus = NO_ERROR;   /* A variable to hold TWI error status */
	u32 Local_u32TimeOutCounter = 0;  		  /* A variable to hold TWI Timeout count */

	/* Send start condition on the bus to initiate the communication */
	SET_BIT(TWCR,TWCR_TWSTA);

	/* Clear TWI interrupt flag through setting TWINT bit in TWCR register to start the previous operation */
	SET_BIT(TWCR,TWCR_TWINT);

	/* Wait until TWI Interrupt Flag is raised again indicating that previous operation is completed through busy-waiting over TWI interrupt flag (TWINT) bit in TWCR register */
	while((GET_BIT(TWCR,TWCR_TWINT) == 0) && (Local_u32TimeOutCounter < TWI_TIMEOUT))
	{
		/* Increment TWI Timeout Counter */
		Local_u32TimeOutCounter ++;
	}

	/* Check if TWI Reached Timeout or Not */
	if(Local_u32TimeOutCounter == TWI_TIMEOUT)
	{
		Local_ErrorStatus = TIMEOUT;
	}
	else
	{
		/* Check if TWI Start Condition is Sent on the Bus or Not */
		if ((TWSR & TWI_STATUS_MASK) != TWI_MASTER_START_CONDITION_STATUS)
		{
			/* Return Error */
			Local_ErrorStatus = StartConditionError;
		}
		else
		{
			/* Clear TWI Start Condition (TWSTA) bit in TWCR register after Start Condition has been transmitted */
			CLR_BIT(TWCR,TWCR_TWSTA);
		}
	}

	return Local_ErrorStatus;
}
/**********************************************************************************/
/* Description     : Send Repeated Start Condition on the bus while SCL is in	  */
/*		     high state to address either the same slave or another one   */
/*		     with either read or write options without having to stop  	  */
/*		     current communication and initiating new one	          */
/* Input Arguments : void						          */
/* Return          : TWI_ErrorStatus_e			             	          */
/**********************************************************************************/
TWI_ErrorStatus_e TWI_SendRepeatedStartCondition(void)
{
	/* Local Variables Definitions */
	TWI_ErrorStatus_e Local_ErrorStatus = NO_ERROR;   /* A variable to hold TWI error status */
	u32 Local_u32TimeOutCounter = 0;  		  /* A variable to hold TWI Timeout count */

	/* Send start condition on the bus to initiate the communication */
	SET_BIT(TWCR,TWCR_TWSTA);

	/* Clear TWI interrupt flag through setting TWINT bit in TWCR register to start the previous operation */
	SET_BIT(TWCR,TWCR_TWINT);

	/* Wait until TWI Interrupt Flag is raised again indicating that previous operation is completed through busy-waiting over TWI interrupt flag (TWINT) bit in TWCR register */
	while((GET_BIT(TWCR,TWCR_TWINT) == 0) && (Local_u32TimeOutCounter < TWI_TIMEOUT))
	{
		/* Increment TWI Timeout Counter */
		Local_u32TimeOutCounter ++;
	}

	/* Check if TWI Reached Timeout or Not */
	if(Local_u32TimeOutCounter == TWI_TIMEOUT)
	{
		Local_ErrorStatus = TIMEOUT;
	}
	else
	{
		/* Check if TWI Repeated Start Condition is Sent on the Bus or Not */
		if ((TWSR & TWI_STATUS_MASK) != TWI_MASTER_REPEATED_START_CONDITION_STATUS)
		{
			/* Return Error */
			Local_ErrorStatus = RepeatedStartConditionError;
		}
		else
		{
			/* Clear TWI Start Condition (TWSTA) bit in TWCR register after Repeated Start Condition has been transmitted */
			CLR_BIT(TWCR,TWCR_TWSTA);
		}
	}

	return Local_ErrorStatus;
}
/**********************************************************************************/
/* Description     : Send desired slave address on the bus with write option	  */
/* Input Arguments : u8 Copy_u8SlaveAddress				          */
/* Return          : TWI_ErrorStatus_e			             	          */
/**********************************************************************************/
TWI_ErrorStatus_e TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress)
{
	/* Local Variables Definitions */
	TWI_ErrorStatus_e Local_ErrorStatus = NO_ERROR;   /* A variable to hold TWI error status */
	u32 Local_u32TimeOutCounter = 0;  		  /* A variable to hold TWI Timeout count */

	/* Write passed slave address on the bus through setting it in the most significant 7 bits of TWDR register */
	TWDR = Copy_u8SlaveAddress << 1;

	/* Clear LSB of TWDR register to send write option on the bus */
	CLR_BIT(TWDR,TWDR_TWD0);

	/* Clear TWI interrupt flag through setting TWINT bit in TWCR register to start the previous operation */
	SET_BIT(TWCR,TWCR_TWINT);

	/* Wait until TWI Interrupt Flag is raised again indicating that previous operation is completed through busy-waiting over TWI interrupt flag (TWINT) bit in TWCR register */
	while((GET_BIT(TWCR,TWCR_TWINT) == 0) && (Local_u32TimeOutCounter < TWI_TIMEOUT))
	{
		/* Increment TWI Timeout Counter */
		Local_u32TimeOutCounter ++;
	}

	/* Check if TWI Reached Timeout or Not */
	if(Local_u32TimeOutCounter == TWI_TIMEOUT)
	{
		Local_ErrorStatus = TIMEOUT;
	}
	else
	{
		/* Check if Sent TWI Slave Address Plus Write With ACK Received Packet is Sent on the Bus or Not */
		if ((TWSR & TWI_STATUS_MASK) != TWI_TMASTER_SLAVE_ADDRESS_PLUS_WRITE_ACK_STATUS)
		{
			/* Return Error */
			Local_ErrorStatus = SlaveAddressWithWriteAckError;
		}
	}

	return Local_ErrorStatus;
}
/**********************************************************************************/
/* Description     : Send desired slave address on the bus with read option	  */
/* Input Arguments : u8 Copy_u8SlaveAddress				          */
/* Return          : TWI_ErrorStatus_e			             	          */
/**********************************************************************************/
TWI_ErrorStatus_e TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress)
{
	/* Local Variables Definitions */
	TWI_ErrorStatus_e Local_ErrorStatus = NO_ERROR;   /* A variable to hold TWI error status */
	u32 Local_u32TimeOutCounter = 0;  		  /* A variable to hold TWI Timeout count */

	/* Write passed slave address on the bus through setting it in the most significant 7 bits of TWDR register */
	TWDR = Copy_u8SlaveAddress << 1;

	/* Set LSB of TWDR register to send read option on the bus */
	SET_BIT(TWDR,TWDR_TWD0);

	/* Clear TWI interrupt flag through setting TWINT bit in TWCR register to start the previous operation */
	SET_BIT(TWCR,TWCR_TWINT);

	/* Wait until TWI Interrupt Flag is raised again indicating that previous operation is completed through busy-waiting over TWI interrupt flag (TWINT) bit in TWCR register */
	while((GET_BIT(TWCR,TWCR_TWINT) == 0) && (Local_u32TimeOutCounter < TWI_TIMEOUT))
	{
		/* Increment TWI Timeout Counter */
		Local_u32TimeOutCounter ++;
	}

	/* Check if TWI Reached Timeout or Not */
	if(Local_u32TimeOutCounter == TWI_TIMEOUT)
	{
		Local_ErrorStatus = TIMEOUT;
	}
	else
	{
		/* Check if Sent TWI Slave Address Plus Read With ACK Received Packet is Sent on the Bus or Not */
		if ((TWSR & TWI_STATUS_MASK) != TWI_RMASTER_SLAVE_ADDRESS_PLUS_READ_ACK_STATUS)
		{
			/* Return Error */
			Local_ErrorStatus = SlaveAddressWithReadAckError;
		}
	}

	return Local_ErrorStatus;
}
/**********************************************************************************/
/* Description     : Function used by master node to send a data byte to desired  */
/*		     slave node on the bus					  */
/* Input Arguments : u8 Copy_u8DataByteToBeSend				          */
/* Return          : TWI_ErrorStatus_e			             	          */
/**********************************************************************************/
TWI_ErrorStatus_e TWI_MasterSendDataByte(u8 Copy_u8DataByteToBeSend)
{
	/* Local Variables Definitions */
	TWI_ErrorStatus_e Local_ErrorStatus = NO_ERROR;   /* A variable to hold TWI error status */
	u32 Local_u32TimeOutCounter = 0;  		  /* A variable to hold TWI Timeout count */

	/* Write data byte to be sent in TWDR register */
	TWDR = Copy_u8DataByteToBeSend;

	/* Clear TWI interrupt flag through setting TWINT bit in TWCR register to start the previous operation */
	SET_BIT(TWCR,TWCR_TWINT);

	/* Wait until TWI Interrupt Flag is raised again indicating that previous operation is completed through busy-waiting over TWI interrupt flag (TWINT) bit in TWCR register */
	while((GET_BIT(TWCR,TWCR_TWINT) == 0) && (Local_u32TimeOutCounter < TWI_TIMEOUT))
	{
		/* Increment TWI Timeout Counter */
		Local_u32TimeOutCounter ++;
	}

	/* Check if TWI Reached Timeout or Not */
	if(Local_u32TimeOutCounter == TWI_TIMEOUT)
	{
		Local_ErrorStatus = TIMEOUT;
	}
	else
	{
		/* Check if Sent TWI Data Byte With ACK Received Packet is Sent on the Bus or Not */
		if ((TWSR & TWI_STATUS_MASK) != TWI_TMASTER_DATA_BYTE_ACK_STATUS)
		{
			/* Return Error */
			Local_ErrorStatus = MasterWriteDataByteAckError;
		}
	}

	return Local_ErrorStatus;
}
/**********************************************************************************/
/* Description     : Function used by master node to read a data byte from   	  */
/*		     desired slave node on the bus				  */
/* Input Arguments : u8* Copy_pu8DataByteToBeReceived				  */
/* Return          : TWI_ErrorStatus_e			             	          */
/**********************************************************************************/
TWI_ErrorStatus_e TWI_MasterReadDataByte(u8* Copy_pu8DataByteToBeReceived)
{
	/* Local Variables Definitions */
	TWI_ErrorStatus_e Local_ErrorStatus = NO_ERROR;   /* A variable to hold TWI error status */
	u32 Local_u32TimeOutCounter = 0;  		  /* A variable to hold TWI Timeout count */

	/* Clear TWI interrupt flag through setting TWINT bit in TWCR register to start receiving data from addressed slave node */
	SET_BIT(TWCR,TWCR_TWINT);

	/* Wait until TWI Interrupt Flag is raised again indicating that previous operation is completed through busy-waiting over TWI interrupt flag (TWINT) bit in TWCR register */
	while((GET_BIT(TWCR,TWCR_TWINT) == 0) && (Local_u32TimeOutCounter < TWI_TIMEOUT))
	{
		/* Increment TWI Timeout Counter */
		Local_u32TimeOutCounter ++;
	}

	/* Check if TWI Reached Timeout or Not */
	if(Local_u32TimeOutCounter == TWI_TIMEOUT)
	{
		Local_ErrorStatus = TIMEOUT;
	}
	else
	{
		/* Check if Received TWI Data Byte With ACK Returned Packet is Sent on the Bus or Not */
		if ((TWSR & TWI_STATUS_MASK) != TWI_RMASTER_DATA_BYTE_ACK_STATUS)
		{
			/* Return Error */
			Local_ErrorStatus = MasterReadDataByteAckError;
		}
		else
		{
			/* Receive Data Sent By Slave Node Through Reading TWDR Register */
			*Copy_pu8DataByteToBeReceived = TWDR;
		}
	}

	return Local_ErrorStatus;
}
/**********************************************************************************/
/* Description     : Send Stop Condition on the bus to stop communication while   */
/*		     SCL is in high state					  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void TWI_SendStopCondition(void)
{
	/* Send stop condition on the bus to finish the communication */
	SET_BIT(TWCR,TWCR_TWSTO);

	/* Clear TWI interrupt flag through setting TWINT bit in TWCR register to start the previous operation */
	SET_BIT(TWCR,TWCR_TWINT);
}