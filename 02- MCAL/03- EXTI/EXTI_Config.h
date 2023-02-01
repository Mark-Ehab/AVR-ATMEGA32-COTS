/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Oct 11, 2021               	*/
/*              SWC              : EXTI				*/
/*              Description	 : EXTI Config                  */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_EXTI_CONFIG_H_
#define MCAL_EXTI_CONFIG_H_

/*********************************** External Interrupt 0 ***********************************/

/*********************************************************/
/* Select EXTI0 Interrupt Sense Control Action :-        */
/* 		         	                         */
/* Options : - LOW_LEVEL                                 */
/*    	     - ANY_LOGICAL_CHANGE			 */
/*           - FALLING_EDGE				 */
/*	     - RISING_EDGE				 */
/* 	                          		 	 */
/*********************************************************/
#define EXTI_EXTI0_SENSE_CONTROL LOW_LEVEL /* Default: LOW_LEVEL */
/*********************************************************/
/* Enable/Disable EXTI0 :-         		         */
/* 		         	                         */
/* Options : - ENABLE                                    */
/*    	     - DISABLE					 */
/* 	                          		 	 */
/*********************************************************/
#define EXTI_EXTI0_ENABLE ENABLE /* Default: ENABLE */

/*********************************** External Interrupt 1 ***********************************/

/*********************************************************/
/* Select EXTI1 Interrupt Sense Control Action :-        */
/* 		         	                         */
/* Options : - LOW_LEVEL                                 */
/*    	     - ANY_LOGICAL_CHANGE			 */
/*           - FALLING_EDGE				 */
/*	     - RISING_EDGE				 */
/* 	                          		 	 */
/*********************************************************/
#define EXTI_EXTI1_SENSE_CONTROL LOW_LEVEL /* Default: LOW_LEVEL */
/*********************************************************/
/* Enable/Disable EXTI1 :-         		         */
/* 		         	                         */
/* Options : - ENABLE                                    */
/*    	     - DISABLE					 */
/* 	                          		 	 */
/*********************************************************/
#define EXTI_EXTI1_ENABLE ENABLE /* Default: ENABLE */

/*********************************** External Interrupt 2 ***********************************/

/*********************************************************/
/* Select EXTI2 Interrupt Sense Control Action :-        */
/* 		         	                         */
/* Options : - FALLING_EDGE	                         */
/*    	     - RISING_EDGE				 */
/*           						 */
/*********************************************************/
#define EXTI_EXTI2_SENSE_CONTROL FALLING_EDGE /* Default: FALLING_EDGE */
/*********************************************************/
/* Enable/Disable EXTI2 :-         		         */
/* 		         	                         */
/* Options : - ENABLE                                    */
/*    	     - DISABLE					 */
/* 	                          		 	 */
/*********************************************************/
#define EXTI_EXTI2_ENABLE ENABLE /* Default: ENABLE */

#endif /* MCAL_EXTI_CONFIG_H_ */
