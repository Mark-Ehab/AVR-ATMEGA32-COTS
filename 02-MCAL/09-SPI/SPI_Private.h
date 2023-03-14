/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Mar 10, 2023               	*/
/*              SWC              : SPI  	        	*/
/*              Description	 : SPI Private                  */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_SPI_PRIVATE_H_
#define MCAL_SPI_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                               SPI REGISTERS DEFINITIONS		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

#define SPDR	                                          *((volatile u8*)0x2F) /* SPI Data Register */
#define SPSR                                              *((volatile u8*)0x2E) /* SPI Status Register */
#define SPCR                                              *((volatile u8*)0x2D) /* SPI Control Register */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                               SOME BITS DEFINITIONS		 	             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Some Bits Definitions of SPI Control Register (SPCR) */
#define SPCR_SPIE					  7 /* SPI Interrupt Enable */
#define SPCR_SPE					  6 /* SPI Enable */
#define SPCR_DORD					  5 /* Data Order */
#define SPCR_MSTR					  4 /* Master/Slave Select */
#define SPCR_CPOL					  3 /* Clock Polarity */
#define SPCR_CPHA				       	  2 /* Clock Phase */
#define SPCR_SPR1				  	  1 /* SPI Clock Rate Select Bit 1 */
#define SPCR_SPR0					  0 /* SPI Clock Rate Select Bit 0 */


/* Some Bits Definitions of SPI Status Register (SPSR) */
#define SPSR_SPIF					  7 /* SPI Interrupt Flag */
#define SPSR_WCOL					  6 /* Write COLlision Flag */
#define SPSR_SPI2X					  0 /* Double SPI Speed Bit */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	     PRIVATE MACROS				     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* SPI Transmission Status Options */
#define SPI_CHARACTER_TRANSMISSION_IDLE                    0
#define SPI_CHARACTER_TRANSMISSION_BUSY                    1
#define SPI_STRING_TRANSMISSION_IDLE                       2
#define SPI_STRING_TRANSMISSION_BUSY                       3


/* SPI Reception Status Options */
#define SPI_CHARACTER_RECEPTION_IDLE                       0
#define SPI_CHARACTER_RECEPTION_BUSY                       1
#define SPI_STRING_RECEPTION_IDLE                          2
#define SPI_STRING_RECEPTION_BUSY                          3


/* Serial Transfer Complete ISR Source Options */
#define SPI_TRANSMISSION_SINGLE_CHARACTER_ASYNC            0
#define SPI_TRANSMISSION_STRING_ASYNC		           1
#define SPI_RECEPTION_SINGLE_CHARACTER_ASYNC	           2
#define SPI_RECEPTION_STRING_ASYNC		           3

/* Define A Dummy Value To Set in SPDR Register Before Receiving Data */
#define SPI_DUMMY_VALUE 				   0x00


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             CONFIGURATION OPTIONS VALUES		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* SPI Mode Possible Options */
#define SPI_SLAVE_MODE					  1
#define SPI_MASTER_MODE					  2


/* Data Order Options */
#define TRANSMIT_MSB_FIRST                                1
#define TRANSMIT_LSB_FIRST                                2


/* Clock Polarity Options */
#define RISING_LEADING_FALLING_TRAILING                   1
#define FALIING_LEADING_RISING_TRAILING                   2


/* Clock Phase Options */
#define SAMPLE_LEADING_SETUP_TRAILING                     1
#define SETUP_LEADING_SAMPLE_TRAILING                     2


/* SPI Clock Rate Options */
#define FOSC_DIV_BY_4                                     1
#define FOSC_DIV_BY_16					  2
#define FOSC_DIV_BY_64					  3
#define FOSC_DIV_BY_128					  4
#define FOSC_DOUBLE_DIV_BY_2				  5
#define FOSC_DOUBLE_DIV_BY_8				  6
#define FOSC_DOUBLE_DIV_BY_32				  7
#define FOSC_DOUBLE_DIV_BY_64				  8


/* Enable/Disable signals for Serial Transfer Complete Interrupt */
#define ENABLE						  1
#define DISABLE                                           2

#endif /* MCAL_SPI_PRIVATE_H_ */