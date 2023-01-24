/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Sep 17, 2021               	*/
/*              SWC              : DIO				*/
/*              Description	 : DIO Private                  */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_DIO_PRIVATE_H_
#define MCAL_DIO_PRIVATE_H_

/* Port_A DIO registers */
#define DDRA 	*((volatile u8*)0x3A)
#define PORTA 	*((volatile u8*)0x3B)
#define PINA	*((volatile u8*)0x39)
/* Port_B DIO registers */
#define DDRB	 *((volatile u8*)0x37)
#define PORTB	 *((volatile u8*)0x38)
#define PINB	 *((volatile u8*)0x36)
/* Port_C DIO registers */
#define DDRC	 *((volatile u8*)0x34)
#define PORTC	 *((volatile u8*)0x35)
#define PINC	 *((volatile u8*)0x33)
/* Port_D DIO registers */
#define DDRD	 *((volatile u8*)0x31)
#define PORTD	 *((volatile u8*)0x32)
#define PIND	 *((volatile u8*)0x30)


#endif /* MCAL_DIO_DIO_PRIVATE_H_ */
