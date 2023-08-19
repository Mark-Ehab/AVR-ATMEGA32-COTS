/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Sep 20, 2021               	*/
/*              SWC              : KEYPAD		        */
/*              Description	 : KEYPAD Config                */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef HAL_KEYPAD_CONFIG_H_
#define HAL_KEYPAD_CONFIG_H_

/*********************************************************/
/* Select 4X4 Keypad Type :-       			 */
/* 		         	                         */
/* Options : - NORMAL_KEYPAD                             */
/*    	     - CALCULATOR_KEYPAD	                 */
/* 	                          		 	 */
/*********************************************************/
#define KEYPAD_TYPE NORMAL_KEYPAD /* Default: NORMAL_KEYPAD */
/*********************************************************/
/* Select Keypad Port :-       				 */
/* 		         	                         */
/* Options : - DIO_PORT_A                                */
/*    	     - DIO_PORT_B	                         */
/*           - DIO_PORT_C	                         */
/*	     - DIO_PORT_D	                         */
/* 	                          		 	 */
/*********************************************************/
#define KEYPAD_PORT DIO_PORT_B /* Default: DIO_PORT_B */
/*********************************************************/
/* Select the Four Pins of Keypad Rows  :-       	 */
/* 		         	                         */
/* Options : - DIO_PIN_0                                 */
/*    	     - DIO_PIN_1	                         */
/*           - DIO_PIN_2	                         */
/*	     - DIO_PIN_3	                         */
/*	     - DIO_PIN_4                                 */
/*           - DIO_PIN_5                                 */
/*           - DIO_PIN_6                                 */
/*           - DIO_PIN_7			         */
/* 	                          		 	 */
/*********************************************************/
#define KEYPAD_ROW_0 DIO_PIN_0
#define KEYPAD_ROW_1 DIO_PIN_1
#define KEYPAD_ROW_2 DIO_PIN_2
#define KEYPAD_ROW_3 DIO_PIN_3
/*********************************************************/
/* Select the Four Pins of Keypad Columns  :-       	 */
/* 		         	                         */
/* Options : - DIO_PIN_0                                 */
/*    	     - DIO_PIN_1	                         */
/*           - DIO_PIN_2	                         */
/*	     - DIO_PIN_3	                         */
/*	     - DIO_PIN_4                                 */
/*           - DIO_PIN_5                                 */
/*           - DIO_PIN_6                                 */
/*           - DIO_PIN_7			         */
/* 	                          		 	 */
/*********************************************************/
#define KEYPAD_COLUMN_0 DIO_PIN_4
#define KEYPAD_COLUMN_1 DIO_PIN_5
#define KEYPAD_COLUMN_2 DIO_PIN_6
#define KEYPAD_COLUMN_3 DIO_PIN_7

#endif /* HAL_KEYPAD_CONFIG_H_ */