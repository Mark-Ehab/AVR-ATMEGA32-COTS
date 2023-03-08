/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Mar 1, 2023               	*/
/*              SWC              : USART	        	*/
/*              Description	 : USART Private                */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_USART_PRIVATE_H_
#define MCAL_USART_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             USART REGISTERS DEFINITIONS		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*******************************************************************************************/
/* Note	: UCSRC and UBRRH registers have the same address in I/O memory so when doing      */
/*	  a write access of this I/O location, the USART register select (URSEL) bit,      */
/*	  controls which one of the two registers that will be written. If URSEL is zero   */
/*	  during a write operation, the UBRRH value will be updated. If URSEL is one, the  */
/*	  UCSRC setting will be updated. 			       	                   */
/*******************************************************************************************/

#define UDR 			                        *((volatile u8*)0x2C) /* USART I/O Data Register */
#define UCSRA			                        *((volatile u8*)0x2B) /* USART Control and Status Register A */
#define UCSRB			                        *((volatile u8*)0x2A) /* USART Control and Status Register B */
#define UCSRC			                        *((volatile u8*)0x40) /* USART Control and Status Register C */
#define UBRRH			                        *((volatile u8*)0x40) /* USART Baud Rate High Register */
#define UBRRL			                        *((volatile u8*)0x29) /* USART Baud Rate Low Register */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                              SOME BITS DEFINITIONS		 	             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Some Bits Definitions of USART Control and Status Register A (UCSRA) */
#define UCSRA_RXC 		                        7 /* USART Receive Complete */
#define UCSRA_TXC 		                        6 /* USART Transmit Complete */
#define UCSRA_UDRE		                        5 /* USART Data Register Empty */
#define UCSRA_FE		                        4 /* Frame Error */
#define UCSRA_DOR		                        3 /* Data OverRun */
#define UCSRA_PE		                        2 /* Parity Error */
#define UCSRA_U2X		                        1 /* Double the USART Transmission Speed */
#define UCSRA_MPCM		                        0 /* Multi-processor Communication Mode */


/* Some Bits Definitions of USART Control and Status Register B (UCSRB) */
#define UCSRB_RXCIE                                     7 /* RX Complete Interrupt Enable */
#define UCSRB_TXCIE                                     6 /* TX Complete Interrupt Enable */
#define UCSRB_UDRIE                                     5 /* USART Data Register Empty Interrupt Enable */
#define UCSRB_RXEN                                      4 /* Receiver Enable */
#define UCSRB_TXEN                                      3 /* Transmitter Enable */
#define UCSRB_UCSZ2                                     2 /* USART Character Size Bit 2 */
#define UCSRB_RXB8                                      1 /* Receive Data Bit 8 */
#define UCSRB_TXB8                                      0 /* Transmit Data Bit 8 */


/* Some Bits Definitions of USART Control and Status Register C (UCSRC) */
#define UCSRC_URSEL                                     7 /* Register Select */
#define UCSRC_UMSEL                                     6 /* USART Mode Select */
#define UCSRC_UPM1                                      5 /* USART Parity Mode Selection Bit 1 */
#define UCSRC_UPM0                                      4 /* USART Parity Mode Selection Bit 0 */
#define UCSRC_USBS                                      3 /* USART Stop Bit Select */
#define UCSRC_UCSZ1                                     2 /* USART Character Size Bit 1 */
#define UCSRC_UCSZ0                                     1 /* USART Character Size Bit 0 */
#define UCSRC_UCPOL                                     0 /* USART Clock Polarity */


/* Some Bits Definitions of USART Baud Rate High Register (UBRRH) */
#define UBRRH_URSEL                                     7 /* Register Select */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	   PRIVATE MACROS				     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* USART Transmission Status Options */
#define USART_CHARACTER_TRANSMISSION_IDLE               0
#define USART_CHARACTER_TRANSMISSION_BUSY               1
#define USART_STRING_TRANSMISSION_IDLE                  2
#define USART_STRING_TRANSMISSION_BUSY                  3


/* USART Reception Status Options */
#define USART_CHARACTER_RECEPTION_IDLE                  0
#define USART_CHARACTER_RECEPTION_BUSY                  1
#define USART_STRING_RECEPTION_IDLE                     2
#define USART_STRING_RECEPTION_BUSY                     3


/* Data Register Empty ISR Source Options */
#define USART_TRANSMISSION_SINGLE_CHARACTER_ASYNC       0
#define USART_TRANSMISSION_STRING_ASYNC		        1


/* Rx Complete ISR Source Options */
#define USART_RECEPTION_SINGLE_CHARACTER_ASYNC	        0
#define USART_RECEPTION_STRING_ASYNC		        1


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           CONFIGURATION OPTIONS VALUES		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* USART Mode Possible Options */
#define SYNCHRONOUS_MODE    	                        1
#define ASYNCHRONOUS_MODE   	                        2


/* USART Communication Mode Possible Options */
#define SINGLE_PROCESSOR_MODE                           1
#define MULTI_PROCESSOR_MODE                            2


/* USART Transmission Speed Mode Possible Options */
#define NORMAL_SPEED_MODE 	                        1
#define DOUBLE_SPEED_MODE 	                        2


/* USART Data Direction Possible Options */
#define SIMPLEX_TX                                      1
#define SIMPLIX_RX                                      2
#define FULL_DUPLEX_TX_RX                               3


/* USART Parity Mode Possible Options */
#define DISABLED                                        1
#define EVEN_PARITY                                     2
#define ODD_PARITY                                      3


/* USART Stop Bits Possible Options */
#define ONE_STOP_BIT		                        1
#define TWO_STOP_BITS		                        2


/* USART Character Size Possible Options */
#define FIVE_BITS                                       1
#define SIX_BITS                                        2
#define SEVEN_BITS                                      3
#define EIGHT_BITS                                      4
#define NINE_BITS                                       5


/* USART Clock Polarity Possible Options */
#define TX_RISING_XCK_EDGE_RX_FALLING_XCK_EDGE		1
#define TX_FALLING_XCK_EDGE_RX_RISING_XCK_EDGE		2


/* Enable/Disable Signals for Rx Complete , Data Register Empty and Tx Complete Interrupts */
#define ENABLE                                          1
#define DISABLE                                         2


/* Baud Rate Possible Values */
#define BAUDRATE_2400_bps				2400UL
#define BAUDRATE_4800_bps				4800UL
#define BAUDRATE_9600_bps				9600UL
#define BAUDRATE_14400_bps				14400UL
#define BAUDRATE_19200_bps				19200UL
#define BAUDRATE_28800_bps				28800UL
#define BAUDRATE_38400_bps				38400UL
#define BAUDRATE_57600_bps				57600UL
#define BAUDRATE_76800_bps				76800UL
#define BAUDRATE_115200_bps				115200UL
#define BAUDRATE_230400_bps				230400UL
#define BAUDRATE_250000_bps				250000UL
#define BAUDRATE_500000_bps				500000UL

#endif /* MCAL_USART_PRIVATE_H_ */