/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Mar 16, 2023               	*/
/*              SWC              : EEPROM			*/
/*              Description	 : EEPROM Interface             */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef HAL_EEPROM_INTERFACE_H_
#define HAL_EEPROM_INTERFACE_H_
        
/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 FUNCTIONS PROTOTYPES		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize EEPROM		                                  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void EEPROM_vidInit(void);
/**********************************************************************************/
/* Description     : Send data byte to be written on a specific byte of EEPROM    */
/* Input Arguments : u16 Copy_u16ByteAddress , u8 Copy_u8DataByteToBeSend	  */
/* Return          : void						          */
/**********************************************************************************/
void EEPROM_vidSendDataByte(u16 Copy_u16ByteAddress , u8 Copy_u8DataByteToBeSend);
/**********************************************************************************/
/* Description     : Read data byte from a specific byte of EEPROM                */
/* Input Arguments : u16 Copy_u16ByteAddress , u8* Copy_pu8DataByteToBeReceived	  */
/* Return          : void						          */
/**********************************************************************************/
void EEPROM_vidReadDataByte(u16 Copy_u16ByteAddress , u8* Copy_pu8DataByteToBeReceived);

#endif /* HAL_EEPROM_INTERFACE_H_ */