/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Jan 17, 2022               	*/
/*              SWC              : PORT				*/
/*              Description	 : PORT Config                  */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_PORT_CONFIG_H_
#define MCAL_PORT_CONFIG_H_

/*********************************************************/
/* Set the direction of each pin of AVR Atmega32 ports:- */
/* 		         	                         */
/* Options : - 0 for Input      	                 */
/*    	     - 1 for Output				 */
/* 	                          		 	 */
/*********************************************************/

/* Port A */
#define PORT_PORTA_PIN0_DIR                                 0
#define PORT_PORTA_PIN1_DIR                                 0
#define PORT_PORTA_PIN2_DIR                                 0
#define PORT_PORTA_PIN3_DIR                                 0
#define PORT_PORTA_PIN4_DIR                                 0
#define PORT_PORTA_PIN5_DIR                                 0
#define PORT_PORTA_PIN6_DIR                                 0
#define PORT_PORTA_PIN7_DIR                                 0

/* Port B */
#define PORT_PORTB_PIN0_DIR                                 0
#define PORT_PORTB_PIN1_DIR                                 0
#define PORT_PORTB_PIN2_DIR                                 0
#define PORT_PORTB_PIN3_DIR                                 0
#define PORT_PORTB_PIN4_DIR                                 0
#define PORT_PORTB_PIN5_DIR                                 0
#define PORT_PORTB_PIN6_DIR                                 0
#define PORT_PORTB_PIN7_DIR                                 0

/* Port C */
#define PORT_PORTC_PIN0_DIR                                 0
#define PORT_PORTC_PIN1_DIR                                 0
#define PORT_PORTC_PIN2_DIR                                 0
#define PORT_PORTC_PIN3_DIR                                 0
#define PORT_PORTC_PIN4_DIR                                 0
#define PORT_PORTC_PIN5_DIR                                 0
#define PORT_PORTC_PIN6_DIR                                 0
#define PORT_PORTC_PIN7_DIR                                 0

/* Port D */
#define PORT_PORTD_PIN0_DIR                                 0
#define PORT_PORTD_PIN1_DIR                                 0
#define PORT_PORTD_PIN2_DIR                                 0
#define PORT_PORTD_PIN3_DIR                                 0
#define PORT_PORTD_PIN4_DIR                                 0
#define PORT_PORTD_PIN5_DIR                                 0
#define PORT_PORTD_PIN6_DIR                                 0
#define PORT_PORTD_PIN7_DIR                                 0

/*********************************************************/
/* Set the Initial Value of each pin of AVR Atmega32  	 */
/* ports :- 					 	 */
/* 		         	                         */
/* Options : - 0 for Floating if Input , Low if Output   */
/*    	     - 1 for Pulledup if Input , High if Output  */
/* 	                          		  	 */
/*********************************************************/

/* Port A */
#define PORT_PORTA_PIN0_INITIAL_VALUE                       0
#define PORT_PORTA_PIN1_INITIAL_VALUE                       0
#define PORT_PORTA_PIN2_INITIAL_VALUE                       0
#define PORT_PORTA_PIN3_INITIAL_VALUE                       0
#define PORT_PORTA_PIN4_INITIAL_VALUE                       0
#define PORT_PORTA_PIN5_INITIAL_VALUE                       0
#define PORT_PORTA_PIN6_INITIAL_VALUE                       0
#define PORT_PORTA_PIN7_INITIAL_VALUE                       0

/* Port B */
#define PORT_PORTB_PIN0_INITIAL_VALUE                       0
#define PORT_PORTB_PIN1_INITIAL_VALUE                       0
#define PORT_PORTB_PIN2_INITIAL_VALUE                       0
#define PORT_PORTB_PIN3_INITIAL_VALUE                       0
#define PORT_PORTB_PIN4_INITIAL_VALUE                       0
#define PORT_PORTB_PIN5_INITIAL_VALUE                       0
#define PORT_PORTB_PIN6_INITIAL_VALUE                       0
#define PORT_PORTB_PIN7_INITIAL_VALUE                       0

/* Port C */
#define PORT_PORTC_PIN0_INITIAL_VALUE                       0
#define PORT_PORTC_PIN1_INITIAL_VALUE                       0
#define PORT_PORTC_PIN2_INITIAL_VALUE                       0
#define PORT_PORTC_PIN3_INITIAL_VALUE                       0
#define PORT_PORTC_PIN4_INITIAL_VALUE                       0
#define PORT_PORTC_PIN5_INITIAL_VALUE                       0
#define PORT_PORTC_PIN6_INITIAL_VALUE                       0
#define PORT_PORTC_PIN7_INITIAL_VALUE                       0

/* Port D */
#define PORT_PORTD_PIN0_INITIAL_VALUE                       0
#define PORT_PORTD_PIN1_INITIAL_VALUE                       0
#define PORT_PORTD_PIN2_INITIAL_VALUE                       0
#define PORT_PORTD_PIN3_INITIAL_VALUE                       0
#define PORT_PORTD_PIN4_INITIAL_VALUE                       0
#define PORT_PORTD_PIN5_INITIAL_VALUE                       0
#define PORT_PORTD_PIN6_INITIAL_VALUE                       0
#define PORT_PORTD_PIN7_INITIAL_VALUE                       0


#endif /* MCAL_PORT_CONFIG_H_ */
