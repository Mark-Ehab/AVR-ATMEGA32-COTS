/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Mar 15, 2023               	*/
/*              SWC              : TWI  	        	*/
/*              Description	 : TWI Interface                */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_TWI_INTERFACE_H_
#define MCAL_TWI_INTERFACE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 NEW TYPES DEFINITIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Define a new enum for TWI possible error status during transmission */
typedef enum
{
	NO_ERROR       			=    0,
        TIMEOUT        			=    1,
        StartConditionError     	=    2,
        RepeatedStartConditionError     =    3,
        SlaveAddressWithWriteAckError   =    4,
        SlaveAddressWithReadAckError    =    5,
        MasterWriteDataByteAckError     =    6,
	MasterReadDataByteAckError      =    7

}TWI_ErrorStatus_e;

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 FUNCTIONS PROTOTYPES		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize this node as TWI master                           */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void TWI_vidMasterInit(void);
/**********************************************************************************/
/* Description     : Initialize this node as TWI slave                            */
/* Input Arguments : u8 Copy_u8SlaveAddress				          */
/* Return          : void						          */
/**********************************************************************************/
void TWI_vidSlaveInit(u8 Copy_u8SlaveAddress);
/**********************************************************************************/
/* Description     : Enable TWI Interrupt                                         */
/* Input Arguments : void 						          */
/* Return          : void						          */
/**********************************************************************************/
void TWI_vidEnableInterrupt(void);
/**********************************************************************************/
/* Description     : Disable TWI Interrupt                                        */
/* Input Arguments : void 						          */
/* Return          : void						          */
/**********************************************************************************/
void TWI_vidDisableInterrupt(void);
/**********************************************************************************/
/* Description     : Send Start Condition on the bus to start communication while */
/*		     SCL is in high state					  */
/* Input Arguments : void						          */
/* Return          : TWI_ErrorStatus_e			             	          */
/**********************************************************************************/
TWI_ErrorStatus_e TWI_SendStartCondition(void);
/**********************************************************************************/
/* Description     : Send Repeated Start Condition on the bus while SCL is in	  */
/*		     high state to address either the same slave or another one   */
/*		     with either read or write options without having to stop  	  */
/*		     current communication and initiating new one	          */
/* Input Arguments : void						          */
/* Return          : TWI_ErrorStatus_e			             	          */
/**********************************************************************************/
TWI_ErrorStatus_e TWI_SendRepeatedStartCondition(void);
/**********************************************************************************/
/* Description     : Send desired slave address on the bus with write option	  */
/* Input Arguments : u8 Copy_u8SlaveAddress				          */
/* Return          : TWI_ErrorStatus_e			             	          */
/**********************************************************************************/
TWI_ErrorStatus_e TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);
/**********************************************************************************/
/* Description     : Send desired slave address on the bus with read option	  */
/* Input Arguments : u8 Copy_u8SlaveAddress				          */
/* Return          : TWI_ErrorStatus_e			             	          */
/**********************************************************************************/
TWI_ErrorStatus_e TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress);
/**********************************************************************************/
/* Description     : Function used by master node to send a data byte to desired  */
/*		     slave node on the bus					  */
/* Input Arguments : u8 Copy_u8DataByteToBeSend				          */
/* Return          : TWI_ErrorStatus_e			             	          */
/**********************************************************************************/
TWI_ErrorStatus_e TWI_MasterSendDataByte(u8 Copy_u8DataByteToBeSend);
/**********************************************************************************/
/* Description     : Function used by master node to read a data byte from   	  */
/*		     desired slave node on the bus				  */
/* Input Arguments : u8* Copy_pu8DataByteToBeReceived				  */
/* Return          : TWI_ErrorStatus_e			             	          */
/**********************************************************************************/
TWI_ErrorStatus_e TWI_MasterReadDataByte(u8* Copy_pu8DataByteToBeReceived);
/**********************************************************************************/
/* Description     : Send Stop Condition on the bus to stop communication while   */
/*		     SCL is in high state					  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void TWI_SendStopCondition(void);

#endif /* MCAL_TWI_INTERFACE_H_ */