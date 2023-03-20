/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Mar 15, 2023               	*/
/*              SWC              : TWI  	        	*/
/*              Description	 : TWI Private                  */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_TWI_PRIVATE_H_
#define MCAL_TWI_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                               TWI REGISTERS DEFINITIONS		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

#define TWCR						             *((volatile u8*)0x56) /* TWI Control Register */
#define TWDR                                                         *((volatile u8*)0x23) /* TWI Data Register */
#define TWAR                                                         *((volatile u8*)0x22) /* TWI (Slave) Address Register */
#define TWSR                                                         *((volatile u8*)0x21) /* TWI Status Register */
#define TWBR                                                         *((volatile u8*)0x20) /* TWI Bit Rate Register */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                               SOME BITS DEFINITIONS		 	             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Some Bits Definitions of TWI Control Register (TWCR) */
#define TWCR_TWINT                                                   7 /* TWI Interrupt Flag */
#define TWCR_TWEA                                                    6 /* TWI Enable Acknowledge Bit */
#define TWCR_TWSTA                                                   5 /* TWI START Condition Bit */
#define TWCR_TWSTO                                                   4 /* TWI STOP Condition Bit */
#define TWCR_TWWC                                                    3 /* TWI Write Collision Flag */
#define TWCR_TWEN                                                    2 /* TWI Enable Bit */
#define TWCR_TWIE                                                    0 /* TWI Interrupt Enable */


/* Some Bits Definitions of TWI Data Register (TWDR) */
#define TWDR_TWD7                                                    7 /* TWI Data Register Bit 7 */
#define TWDR_TWD6                                                    6 /* TWI Data Register Bit 6 */
#define TWDR_TWD5                                                    5 /* TWI Data Register Bit 5 */
#define TWDR_TWD4                                                    4 /* TWI Data Register Bit 4 */
#define TWDR_TWD3                                                    3 /* TWI Data Register Bit 3 */
#define TWDR_TWD2                                                    2 /* TWI Data Register Bit 2 */
#define TWDR_TWD1                                                    1 /* TWI Data Register Bit 1 */
#define TWDR_TWD0                                                    0 /* TWI Data Register Bit 0 */


/* Some Bits Definitions of TWI Status Register (TWSR) */
#define TWSR_TWPS0						     0 /* TWI Prescaler Bit 0 */
#define TWSR_TWPS1						     1 /* TWI Prescaler Bit 1 */


/* Some Bits Definitions of TWI (Slave) Address Register (TWAR) */
#define TWAR_TWGCE					             0 /* TWI General Call Recognition Enable Bit */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	     PRIVATE MACROS				     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Define TWI Status Mask */
#define TWI_STATUS_MASK						     0xF8


/* TWI Status Codes */
/******************************Master Status Codes******************************/
/* General Master Status Codes */
#define TWI_MASTER_START_CONDITION_STATUS	      		     0x08 /* Start Condition has been transmitted */
#define TWI_MASTER_REPEATED_START_CONDITION_STATUS 		     0x10 /* Repeated Start Condition has been transmitted */
#define TWI_MASTER_ARBITRATION_LOST_STATUS			     0x38 /* Arbitration lost in SLA+W or data bytes */

/* Master Transmitter Mode Status Codes */
#define TWI_TMASTER_SLAVE_ADDRESS_PLUS_WRITE_ACK_STATUS 	     0x18 /* SLA+W has been transmitted and ACK has been received */
#define TWI_TMASTER_SLAVE_ADDRESS_PLUS_WRITE_NACK_STATUS             0x20 /* SLA+W has been transmitted and NOT ACK has been received */
#define TWI_TMASTER_DATA_BYTE_ACK_STATUS 	  		     0x28 /* Data byte has been transmitted and ACK has been received */
#define TWI_TMASTER_DATA_BYTE_NACK_STATUS 	                     0x30 /* Data byte has been transmitted and NOT ACK has been received */

/* Master Receiver Mode Status Codes */
#define TWI_RMASTER_SLAVE_ADDRESS_PLUS_READ_ACK_STATUS		     0x40 /* SLA+R has been transmitted and ACK has been received */
#define TWI_RMASTER_SLAVE_ADDRESS_PLUS_WRITE_NACK_STATUS	     0x48 /* SLA+R has been transmitted and NOT ACK has been received */
#define TWI_RMASTER_DATA_BYTE_ACK_STATUS 	  		     0x50 /* Data byte has been received and ACK has been received */
#define TWI_RMASTER_DATA_BYTE_NACK_STATUS 	                     0x58 /* Data byte has been received and NOT ACK has been received */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             CONFIGURATION OPTIONS VALUES		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Enable/Disable signals for TWI interrupt , Acknowledge bit and general call recognition */
#define ENABLE                                                       1
#define DISABLE                                                      2


/* TWI prescaler Possible Options */
#define _1_PRESCALER                                                 0
#define _4_PRESCALER                                                 1
#define _16_PRESCALER                                                2
#define _64_PRESCALER                                                3

#endif /* MCAL_TWI_PRIVATE_H_ */