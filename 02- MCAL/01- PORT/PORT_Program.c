/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Jan 17, 2022               	*/
/*              SWC              : PORT				*/
/*              Description	 : PORT Program                 */
/* 	        Version          : V1.0                         */
/****************************************************************/

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/STD_ERRORS.h"

#include "PORT_Interface.h"
#include "PORT_Config.h"
#include "PORT_Private.h"

/**********************************************************************************/
/* Description     : Initialize each pin of AVR Atmega32 ports			  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void PORT_vidInit(void)
{
	/* Set Ports Directions */
	DDRA =  PORT_PORTA_DIR; 		/* Direction of port A pins */
	DDRB =  PORT_PORTB_DIR; 		/* Direction of port B pins */
	DDRC =  PORT_PORTC_DIR; 		/* Direction of port C pins */
	DDRD =  PORT_PORTD_DIR;			/* Direction of port D pins */

	/* Set Ports Initial Values */
	PORTA =  PORT_PORTA_INITIAL_VALUE; 	/* Initial Values of port A pins */
	PORTB =  PORT_PORTB_INITIAL_VALUE; 	/* Initial Values of port B pins */
	PORTC =  PORT_PORTC_INITIAL_VALUE;      /* Initial Values of port C pins */
	PORTD =  PORT_PORTD_INITIAL_VALUE;	/* Initial Values of port D pins */



}
