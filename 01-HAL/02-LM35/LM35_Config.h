/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : JAN 23, 2023               	*/
/*              SWC              : LM35				*/
/*              Description	 : LM35 Config                  */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef HAL_LM35_CONFIG_H_
#define HAL_LM35_CONFIG_H_

/************************************************************************/
/* Select the port for LM35 to operate on:- 				*/
/*					       				*/
/* Options :  - PORT_A                         				*/
/* 	      - PORT_B               	       				*/
/* 	      - PORT_C               	       				*/
/* 	      - PORT_D               	       				*/
/*								        */
/* Note    : In case of AVR ATmega32 the only valid port to receive     */
/* 	     analog signal as input from sensors is PORT_A (Mandatory)  */
/* 					       				*/
/************************************************************************/
#define LM35_PORT PORT_A /* Default: PORT_A */

/************************************************************************/
/* Select the pin for LM35 to operate on:- 				*/
/*                                                                      */
/* Options :  - PIN_0                                                   */
/* 	      - PIN_1                                                   */
/* 	      - PIN_2                                                   */
/* 	      - PIN_3                                                   */
/* 	      - PIN_4                                                   */
/* 	      - PIN_5                                                   */
/* 	      - PIN_6                                                   */
/* 	      - PIN_7                                                   */
/*									*/
/************************************************************************/
#define LM35_PIN  PIN_0 /* Default: PIN_0 */


#endif /* HAL_LM35_CONFIG_H_ */
