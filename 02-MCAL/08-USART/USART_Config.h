/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Mar 1, 2023               	*/
/*              SWC              : USART	        	*/
/*              Description	 : USART Config                 */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_USART_CONFIG_H_
#define MCAL_USART_CONFIG_H_

/*********************************************************/
/* Set Clock Frequency on Which MCU Operates:-		 */
/*********************************************************/
#define USART_FCPU 8000000UL
/*********************************************************/
/* Set TimeOut Value:-					 */
/*********************************************************/
#define USART_TIMEOUT 5000000
/*********************************************************/
/* Select USART Mode:-					 */
/* 		         	                         */
/* Options : - SYNCHRONOUS_MODE      	                 */
/*    	     - ASYNCHRONOUS_MODE			 */
/* 	                          		 	 */
/*********************************************************/
#define USART_MODE ASYNCHRONOUS_MODE /* Default: ASYNCHRONOUS_MODE */
/*********************************************************/
/* Select USART Communication Mode:-			 */
/* 		         	                         */
/* Options : - SINGLE_PROCESSOR_MODE      	         */
/*    	     - MULTI_PROCESSOR_MODE			 */
/* 	                          		 	 */
/*********************************************************/
#define USART_COMMUNICATION_MODE SINGLE_PROCESSOR_MODE /* Default: SINGLE_PROCESSOR_MODE */
/*********************************************************/
/* Select USART Transmission Speed Mode:-		 */
/* 		         	                         */
/* Options : - NORMAL_SPEED_MODE      	  	         */
/*    	     - DOUBLE_SPEED_MODE			 */
/* 	                          		 	 */
/*********************************************************/
#define USART_TRANSMISSION_SPEED_MODE NORMAL_SPEED_MODE /* Default: NORMAL_SPEED_MODE */
/*********************************************************/
/* Select USART Data Direction:-			 */
/* 		         	                         */
/* Options : - SIMPLEX_TX	      	  	         */
/*    	     - SIMPLIX_RX				 */
/*	     - FULL_DUPLEX_TX_RX 			 */
/* 	                          		 	 */
/*********************************************************/
#define USART_DATA_DIRECTION FULL_DUPLEX_TX_RX /* Default: FULL_DUPLEX_TX_RX */
/*********************************************************/
/* Select USART Parity Mode:-				 */
/* 		         	                         */
/* Options : - DISABLED         	                 */
/*    	     - EVEN_PARITY      			 */
/* 	     - ODD_PARITY         		 	 */
/*							 */
/*********************************************************/
#define USART_PARITY_MODE DISABLED /* Default: DISABLED */
/*********************************************************/
/* Select USART Stop Bits:-				 */
/* 		         	                         */
/* Options : - ONE_STOP_BIT         	                 */
/*    	     - TWO_STOP_BITS      			 */
/*							 */
/*********************************************************/
#define USART_STOP_BITS ONE_STOP_BIT /* Default: ONE_STOP_BIT */
/*********************************************************/
/* Select USART Character Size:-			 */
/* 		         	                         */
/* Options : - FIVE_BITS                     	         */
/*    	     - SIX_BITS                             	 */
/*	     - SEVEN_BITS		           	 */
/*	     - EIGHT_BITS	                 	 */
/*	     - NINE_BITS	                 	 */
/*							 */
/*********************************************************/
#define USART_CHARACTER_SIZE EIGHT_BITS /* Default: EIGHT_BITS */
/*********************************************************/
/* Select USART Clock Polarity:-			 */
/* 		         	                         */
/* Options : - TX_RISING_XCK_EDGE_RX_FALLING_XCK_EDGE    */
/*    	     - TX_FALLING_XCK_EDGE_RX_RISING_XCK_EDGE    */
/*							 */
/* Note	   : Only Selected When USART Mode is in	 */
/* 	     Synchronous Mode				 */
/*							 */
/*********************************************************/
#define USART_CLOCK_POLARITY TX_RISING_XCK_EDGE_RX_FALLING_XCK_EDGE /* Default: TX_RISING_XCK_EDGE_RX_FALLING_XCK_EDGE */
/*********************************************************/
/* Enable/Disable USART Rx Complete Interrupt :-	 */
/* 		         	                         */
/* Options : - ENABLE    	    	                 */
/*    	     - DISABLE      				 */
/*							 */
/*********************************************************/
#define USART_RX_COMPLETE_INTERRUPT_ENABLE DISABLE /* Default: DISABLE */
/*********************************************************/
/* Enable/Disable USART Data Register Empty Interrupt :- */
/* 		         	                         */
/* Options : - ENABLE    	    	                 */
/*    	     - DISABLE      				 */
/*							 */
/*********************************************************/
#define USART_DATA_REGISTER_EMPTY_INTERRUPT_ENABLE DISABLE /* Default: DISABLE */
/*********************************************************/
/* Enable/Disable USART Tx Complete Interrupt :-	 */
/* 		         	                         */
/* Options : - ENABLE    	    	                 */
/*    	     - DISABLE      				 */
/*							 */
/*********************************************************/
#define USART_TX_COMPLETE_INTERRUPT_ENABLE DISABLE /* Default: DISABLE */
/*********************************************************/
/* Select Baud Rate Value on Which USART will Operate :- */
/* 		         	                         */
/* Options : - BAUDRATE_2400_bps                         */
/*    	     - BAUDRATE_4800_bps                   	 */
/*	     - BAUDRATE_9600_bps           	 	 */
/*	     - BAUDRATE_14400_bps                	 */
/*	     - BAUDRATE_19200_bps                	 */
/*    	     - BAUDRATE_28800_bps                   	 */
/*	     - BAUDRATE_38400_bps           	 	 */
/*	     - BAUDRATE_57600_bps                	 */
/*	     - BAUDRATE_76800_bps                	 */
/*    	     - BAUDRATE_115200_bps                   	 */
/*	     - BAUDRATE_230400_bps           	 	 */
/*	     - BAUDRATE_250000_bps                	 */
/*	     - BAUDRATE_500000_bps                       */
/*							 */
/* Note    : These options are for 8.0 MHZ MCU CLK Setup */
/*	     (fosc = 8.0000 MHz)			 */
/*							 */
/*********************************************************/
#define USART_BAUDRATE_VAL BAUDRATE_9600_bps /* Default: BAUDRATE_9600_bps */

#endif /* MCAL_USART_CONFIG_H_ */