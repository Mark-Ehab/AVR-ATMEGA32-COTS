/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Mar 16, 2023               	*/
/*              SWC              : EEPROM			*/
/*              Description	 : EEPROM Private               */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef HAL_EEPROM_PRIVATE_H_
#define HAL_EEPROM_PRIVATE_H_
        
/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	     PRIVATE MACROS				     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Define EEPROM address fixed sequence which is in the 4 most significant bits of the address */
#define EEPROM_ADDRESS_FIXED_SEQENCE		 0b1010

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             CONFIGURATION OPTIONS VALUES		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Possible 8 Kbyte EEPROM Numbers */
#define EEPROM_1                                 0
#define EEPROM_2                                 1
        
#endif /* HAL_EEPROM_PRIVATE_H_ */