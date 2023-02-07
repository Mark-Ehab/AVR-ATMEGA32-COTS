/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Dec 19, 2022               	*/
/*              SWC              : SSD				*/
/*              Description	 : SSD Private                  */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef HAL_SSD_PRIVATE_H_
#define HAL_SSD_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	   PRIVATE MACROS				     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Encoding of digits that can be displayed on seven segment */
#define ZERO  					    0b00111111
#define ONE   					    0b00000110
#define TWO   					    0b01011011
#define THREE 					    0b01001111
#define FOUR  					    0b01100110
#define FIVE                                        0b01101101
#define SIX                                         0b01111101
#define SEVEN                                       0b00000111
#define EIGHT                                       0b01111111
#define NINE                                        0b01101111
#define DOT                                         0b10000000


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           CONFIGURATION OPTIONS VALUES		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* SSD Common Pin Type Options */
#define COMMON_CATHODE				    0
#define COMMON_ANODE				    1


/* SSD Mode Options */
#define SINGLE_MODE		                    0
#define MULTIPLEXING_MODE                           1

#endif /* HAL_SSD_PRIVATE_H_ */
