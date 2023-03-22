/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Sep 20, 2021               	*/
/*              SWC              : KEYPAD		        */
/*              Description	 : KEYPAD Private               */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef HAL_KEYPAD_PRIVATE_H_
#define HAL_KEYPAD_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	   PRIVATE MACROS				     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Define Number of Keypad Rows and Columns */
#define KEYPAD_ROWS_NUM 		       4
#define KEYPAD_COLUMNS_NUM 		       4

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           CONFIGURATION OPTIONS VALUES		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Possible 4X4 Keypad Types */
#define NORMAL_KEYPAD                          1
#define CALCULATOR_KEYPAD                      2

#endif /* HAL_KEYPAD_PRIVATE_H_ */