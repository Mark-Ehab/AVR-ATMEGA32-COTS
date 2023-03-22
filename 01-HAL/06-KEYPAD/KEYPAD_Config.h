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
/* Options : - PORT_A                                    */
/*    	     - PORT_B	                                 */
/*           - PORT_C	                                 */
/*	     - PORT_D	                                 */
/* 	                          		 	 */
/*********************************************************/
#define KEYPAD_PORT PORT_B /* Default: PORT_B */
/*********************************************************/
/* Select the Four Pins of Keypad Rows  :-       	 */
/* 		         	                         */
/* Options : - PIN_0                                     */
/*    	     - PIN_1	                                 */
/*           - PIN_2	                                 */
/*	     - PIN_3	                                 */
/*	     - PIN_4                                     */
/*           - PIN_5                                     */
/*           - PIN_6                                     */
/*           - PIN_7			                 */
/* 	                          		 	 */
/*********************************************************/
#define KEYPAD_ROW_0 PIN_0
#define KEYPAD_ROW_1 PIN_1
#define KEYPAD_ROW_2 PIN_2
#define KEYPAD_ROW_3 PIN_3
/*********************************************************/
/* Select the Four Pins of Keypad Columns  :-       	 */
/* 		         	                         */
/* Options : - PIN_0                                     */
/*    	     - PIN_1	                                 */
/*           - PIN_2	                                 */
/*	     - PIN_3	                                 */
/*	     - PIN_4                                     */
/*           - PIN_5                                     */
/*           - PIN_6                                     */
/*           - PIN_7			                 */
/* 	                          		 	 */
/*********************************************************/
#define KEYPAD_COLUMN_0 PIN_4
#define KEYPAD_COLUMN_1 PIN_5
#define KEYPAD_COLUMN_2 PIN_6
#define KEYPAD_COLUMN_3 PIN_7

#endif /* HAL_KEYPAD_CONFIG_H_ */