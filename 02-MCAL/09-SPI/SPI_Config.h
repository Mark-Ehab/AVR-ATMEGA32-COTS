/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Mar 10, 2023               	*/
/*              SWC              : SPI  	        	*/
/*              Description	 : SPI Config                   */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_SPI_CONFIG_H_
#define MCAL_SPI_CONFIG_H_

/*********************************************************/
/* Set TimeOut Value:-					 */
/*********************************************************/
#define SPI_TIMEOUT 5000000
/*********************************************************/
/* Select SPI Mode for this Node :-            		 */
/* 		         	                         */
/* Options : - SPI_SLAVE_MODE                            */
/*    	     - SPI_MASTER_MODE             	  	 */
/* 	                          		 	 */
/*********************************************************/
#define SPI_MODE SPI_SLAVE_MODE /* Default: SPI_SLAVE_MODE */
/*********************************************************/
/* Select Data Order for this SPI Node :-            	 */
/* 		         	                         */
/* Options : - TRANSMIT_MSB_FIRST                        */
/*    	     - TRANSMIT_LSB_FIRST             	  	 */
/* 	                          		 	 */
/*********************************************************/
#define SPI_DATA_ORDER TRANSMIT_LSB_FIRST /* Default: TRANSMIT_LSB_FIRST */
/*********************************************************/
/* Select Clock Polarity for this SPI Node :-            */
/* 		         	                         */
/* Options : - RISING_LEADING_FALLING_TRAILING           */
/*    	     - FALIING_LEADING_RISING_TRAILING           */
/* 	                          		 	 */
/*********************************************************/
#define SPI_CLOCK_POLARITY RISING_LEADING_FALLING_TRAILING /* Default: RISING_LEADING_FALLING_TRAILING */
/*********************************************************/
/* Select Clock Phase for this SPI Node :-            	 */
/* 		         	                         */
/* Options : - SAMPLE_LEADING_SETUP_TRAILING             */
/*    	     - SETUP_LEADING_SAMPLE_TRAILING             */
/* 	                          		 	 */
/*********************************************************/
#define SPI_CLOCK_PHASE SAMPLE_LEADING_SETUP_TRAILING /* Default: SAMPLE_LEADING_SETUP_TRAILING */
/*********************************************************/
/* Select SPI Clock Rate :-           	 	         */
/* 		         	                         */
/* Options : - FOSC_DIV_BY_4                             */
/*    	     - FOSC_DIV_BY_16                            */
/*    	     - FOSC_DIV_BY_64                            */
/*    	     - FOSC_DIV_BY_128                           */
/*    	     - FOSC_DOUBLE_DIV_BY_2                      */
/*	     - FOSC_DOUBLE_DIV_BY_8		         */
/*	     - FOSC_DOUBLE_DIV_BY_32		         */
/*	     - FOSC_DOUBLE_DIV_BY_64			 */
/*		 		                         */
/* Note    : Only selected when SPI node is a master   	 */
/* 	                          		 	 */
/*********************************************************/
#define SPI_CLOCK_RATE FOSC_DIV_BY_16 /* Default: FOSC_DIV_BY_16 */
/*********************************************************/
/* Enable/Disable Serial Transfer Complete Interrupt :-	 */
/* 		         	                         */
/* Options : - ENABLE    	    	                 */
/*    	     - DISABLE      				 */
/*							 */
/*********************************************************/
#define SPI_SERIAL_TRANSFER_COMPLETE_INTERRUPT_ENABLE DISABLE /* Default: DISABLE */

#endif /* MCAL_SPI_CONFIG_H_ */