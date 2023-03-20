/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Mar 15, 2023               	*/
/*              SWC              : TWI  	        	*/
/*              Description	 : TWI Config                   */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_TWI_CONFIG_H_
#define MCAL_TWI_CONFIG_H_

/*********************************************************/
/* Set AVR ATmega32 Clock Frequency			 */
/*********************************************************/
#define TWI_FCPU 8000000UL /* Default: 8000000UL */
/*********************************************************/
/* Set TimeOut Value:-					 */
/*********************************************************/
#define TWI_TIMEOUT 5000000
/*********************************************************/
/* Set TWI Serial Clock Value:-				 */
/*********************************************************/
#define TWI_SCL 400000UL
/*********************************************************/
/* Enable/Disable Acknowledge bit for this TWI node :-	 */
/* 		         	                         */
/* Options : - ENABLE                                    */
/*    	     - DISABLE                               	 */
/*                                                       */
/*********************************************************/
#define TWI_ACK_BIT_ENABLE DISABLE /* Default: DISABLE */
/*********************************************************/
/* Enable/Disable TWI Interrupt :-			 */
/* 		         	                         */
/* Options : - ENABLE                                    */
/*    	     - DISABLE                               	 */
/*                                                       */
/*********************************************************/
#define TWI_INTERRUPT_ENABLE DISABLE /* Default: DISABLE */
/*********************************************************/
/* Enable/Disable TWI General Call Recognition for this  */
/* node :-						 */
/* 		         	                         */
/* Options : - ENABLE                                    */
/*    	     - DISABLE                               	 */
/*                                                       */
/*********************************************************/
#define TWI_GENERAL_CALL_RECOGNITION_ENABLE DISABLE /* Default: DISABLE */
/*********************************************************/
/* Select TWI prescaler to control the bit rate 	 */
/* prescaler :-			  	 		 */
/* 		         	                         */
/* Options : - _1_PRESCALER                              */
/*    	     - _4_PRESCALER                         	 */
/*    	     - _16_PRESCALER                         	 */
/*    	     - _64_PRESCALER                         	 */
/*							 */
/* Note    : Selected only when node is operating as	 */
/*	     master					 */
/* 	                          		 	 */
/*********************************************************/
#define TWI_Prescaler_VAL _1_PRESCALER /* Default: _1_PRESCALER */

#endif /* MCAL_TWI_CONFIG_H_ */