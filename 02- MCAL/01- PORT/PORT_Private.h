/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Jan 17, 2022               	*/
/*              SWC              : PORT				*/
/*              Description	 : PORT Private                 */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_PORT_PRIVATE_H_
#define MCAL_PORT_PRIVATE_H_

/* Registers Definitions */

/* Port_A DIO registers */
#define DDRA 	                             *((volatile u8*)0x3A) /* Port A Data Direction Register */
#define PORTA 	                             *((volatile u8*)0x3B) /* Port A Data Register */
/* Port_B DIO registers */
#define DDRB	                             *((volatile u8*)0x37) /* Port B Data Direction Register */
#define PORTB	                             *((volatile u8*)0x38) /* Port B Data Register */
/* Port_C DIO registers */
#define DDRC	                             *((volatile u8*)0x34) /* Port C Data Direction Register */
#define PORTC	                             *((volatile u8*)0x35) /* Port C Data Register */
/* Port_D DIO registers */
#define DDRD	                             *((volatile u8*)0x31) /* Port D Data Direction Register */
#define PORTD	                             *((volatile u8*)0x32) /* Port D Data Register */


/* Define a function-like macro called CONC to help us in concatenation of registers bits from config file */
#define CONC(b7,b6,b5,b4,b3,b2,b1,b0)        CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)
#define CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)   0b##b7##b6##b5##b4##b3##b2##b1##b0


/* Set AVR ATmega32 Ports Directions Based on Config File */
#define PORT_PORTA_DIR			     CONC(PORT_PORTA_PIN7_DIR,PORT_PORTA_PIN6_DIR,PORT_PORTA_PIN5_DIR,PORT_PORTA_PIN4_DIR,PORT_PORTA_PIN3_DIR,PORT_PORTA_PIN2_DIR,PORT_PORTA_PIN1_DIR,PORT_PORTA_PIN0_DIR)
#define PORT_PORTB_DIR			     CONC(PORT_PORTB_PIN7_DIR,PORT_PORTB_PIN6_DIR,PORT_PORTB_PIN5_DIR,PORT_PORTB_PIN4_DIR,PORT_PORTB_PIN3_DIR,PORT_PORTB_PIN2_DIR,PORT_PORTB_PIN1_DIR,PORT_PORTB_PIN0_DIR)
#define PORT_PORTC_DIR			     CONC(PORT_PORTC_PIN7_DIR,PORT_PORTC_PIN6_DIR,PORT_PORTC_PIN5_DIR,PORT_PORTC_PIN4_DIR,PORT_PORTC_PIN3_DIR,PORT_PORTC_PIN2_DIR,PORT_PORTC_PIN1_DIR,PORT_PORTC_PIN0_DIR)
#define PORT_PORTD_DIR			     CONC(PORT_PORTD_PIN7_DIR,PORT_PORTD_PIN6_DIR,PORT_PORTD_PIN5_DIR,PORT_PORTD_PIN4_DIR,PORT_PORTD_PIN3_DIR,PORT_PORTD_PIN2_DIR,PORT_PORTD_PIN1_DIR,PORT_PORTD_PIN0_DIR)


/* Set AVR ATmega32 Ports Directions Based on Config File */
#define PORT_PORTA_INITIAL_VALUE	     CONC(PORT_PORTA_PIN7_INITIAL_VALUE,PORT_PORTA_PIN6_INITIAL_VALUE,PORT_PORTA_PIN5_INITIAL_VALUE,PORT_PORTA_PIN4_INITIAL_VALUE,PORT_PORTA_PIN3_INITIAL_VALUE,PORT_PORTA_PIN2_INITIAL_VALUE,PORT_PORTA_PIN1_INITIAL_VALUE,PORT_PORTA_PIN0_INITIAL_VALUE)
#define PORT_PORTB_INITIAL_VALUE	     CONC(PORT_PORTB_PIN7_INITIAL_VALUE,PORT_PORTB_PIN6_INITIAL_VALUE,PORT_PORTB_PIN5_INITIAL_VALUE,PORT_PORTB_PIN4_INITIAL_VALUE,PORT_PORTB_PIN3_INITIAL_VALUE,PORT_PORTB_PIN2_INITIAL_VALUE,PORT_PORTB_PIN1_INITIAL_VALUE,PORT_PORTB_PIN0_INITIAL_VALUE)
#define PORT_PORTC_INITIAL_VALUE	     CONC(PORT_PORTC_PIN7_INITIAL_VALUE,PORT_PORTC_PIN6_INITIAL_VALUE,PORT_PORTC_PIN5_INITIAL_VALUE,PORT_PORTC_PIN4_INITIAL_VALUE,PORT_PORTC_PIN3_INITIAL_VALUE,PORT_PORTC_PIN2_INITIAL_VALUE,PORT_PORTC_PIN1_INITIAL_VALUE,PORT_PORTC_PIN0_INITIAL_VALUE)
#define PORT_PORTD_INITIAL_VALUE	     CONC(PORT_PORTD_PIN7_INITIAL_VALUE,PORT_PORTD_PIN6_INITIAL_VALUE,PORT_PORTD_PIN5_INITIAL_VALUE,PORT_PORTD_PIN4_INITIAL_VALUE,PORT_PORTD_PIN3_INITIAL_VALUE,PORT_PORTD_PIN2_INITIAL_VALUE,PORT_PORTD_PIN1_INITIAL_VALUE,PORT_PORTD_PIN0_INITIAL_VALUE)

#endif /* MCAL_PORT_PRIVATE_H_ */
