/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Sep 17, 2021               	*/
/*              SWC              : DIO				*/
/*              Description	 : DIO Private                  */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_DIO_PRIVATE_H_
#define MCAL_DIO_PRIVATE_H_

/* DIO Registers Definitions */

/* Port_A DIO registers */
#define DDRA 	                                 *((volatile u8*)0x3A) /* Port A Data Direction Register */
#define PORTA 	                                 *((volatile u8*)0x3B) /* Port A Data Register */
#define PINA	                                 *((volatile u8*)0x39) /* Port A Input Pins Address Register*/
/* Port_B DIO registers */
#define DDRB	                                 *((volatile u8*)0x37) /* Port B Data Direction Register */
#define PORTB	                                 *((volatile u8*)0x38) /* Port B Data Register */
#define PINB	                                 *((volatile u8*)0x36) /* Port B Input Pins Address Register*/
/* Port_C DIO registers */
#define DDRC	                                 *((volatile u8*)0x34) /* Port C Data Direction Register */
#define PORTC	                                 *((volatile u8*)0x35) /* Port C Data Register */
#define PINC	                                 *((volatile u8*)0x33) /* Port C Input Pins Address Register*/
/* Port_D DIO registers */
#define DDRD	                                 *((volatile u8*)0x31) /* Port D Data Direction Register */
#define PORTD	                                 *((volatile u8*)0x32) /* Port D Data Register */
#define PIND	                                 *((volatile u8*)0x30) /* Port D Input Pins Address Register*/


#endif /* MCAL_DIO_DIO_PRIVATE_H_ */
