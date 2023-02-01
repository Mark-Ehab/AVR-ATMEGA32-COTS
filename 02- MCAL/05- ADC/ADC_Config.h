/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Oct 15, 2021               	*/
/*              SWC              : ADC				*/
/*              Description	 : ADC Config                   */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_ADC_CONFIG_H_
#define MCAL_ADC_CONFIG_H_

/*********************************************************/
/* Select ADC reference voltage mode :-                  */
/* 		         	                         */
/* Options : - AREF                                      */
/*    	     - AVCC					 */
/*           - INTERNAL_VOLT				 */
/* 	                          		 	 */
/*********************************************************/
#define ADC_REF_VOLT AVCC /* Default: AVCC */

/*********************************************************/
/* Select ADC result adjustment mode :-                  */
/* 		         	                         */
/* Options : - RIGHT_ADJUSTMENT                          */
/*    	     - LEFT_ADJUSTMENT 			         */
/* 	                        		 	 */
/*********************************************************/
#define ADC_RESULT_ADJUSTMENT LEFT_ADJUSTMENT /* Default: LEFT_ADJUSTMENT */

/*********************************************************/
/* Enable/Disable ADC auto-trigger :-                    */
/* 		         	                         */
/* Options : - AUTO_TRIGGER_ENABLE                       */
/*    	     - AUTO_TRIGGER_DISABLE		         */
/* 	                        		 	 */
/*********************************************************/
#define ADC_AUTO_TRIGGER AUTO_TRIGGER_DISABLE /* Default: AUTO_TRIGGER_DISABLE */

/*********************************************************/
/* Select ADC Auto-Trigger Source :-                     */
/* 		         	                         */
/* Options : - FREE_RUNNING 	                         */
/*    	     - ANALOG_COMPARATOR		         */
/* 	     - EXTERNAL_INTERRUPT_REQUEST0		 */
/* 	     - TIMER0_COMPARE_MATCH              	 */
/* 	     - TIMER0_OVERFLOW                    	 */
/* 	     - TIMER_COMPARE_MATCH_B             	 */
/* 	     - TIMER1_OVERFLOW                    	 */
/* 	     - TIMER1_CAPTURE_EVENT              	 */
/* 	                          		 	 */
/* Note    : Only Selected When ADC Auto-Trigger is 	 */
/*	     Enabled					 */
/*							 */
/*********************************************************/
#define ADC_AUTO_TRIGGER_SOURCE FREE_RUNNING /* Default: FREE_RUNNING */

/*********************************************************/
/* Select ADC Channel in Case Auto-Trigger Mode is 	 */
/* Enabled  :-           			         */
/* 		         	                         */
/* Options : - CH_0               			 */
/*    	     - CH_1	         			 */
/* 	     - CH_2		  			 */
/* 	     - CH_3       	 			 */
/* 	     - CH_4        	 			 */
/* 	     - CH_5       	 			 */
/* 	     - CH_6       	 			 */
/* 	     - CH_7       	 			 */
/* 	                          		 	 */
/* Note    : Only Selected When ADC Auto-Trigger is 	 */
/*	     Enabled					 */
/*							 */
/*********************************************************/
#define ADC_AUTO_TRIGGER_CHANNEL CH_0 /* Default: CH_0 */

/*********************************************************/
/* Select ADC CLK Pre-scaler :-                          */
/* 		         	                         */
/* Options : - CLK_DIV_BY_2                	         */
/*    	     - CLK_DIV_BY_4     	                 */
/*    	     - CLK_DIV_BY_8     	                 */
/*    	     - CLK_DIV_BY_16  	      	                 */
/*    	     - CLK_DIV_BY_32 	      	                 */
/*    	     - CLK_DIV_BY_64 	      	                 */
/*    	     - CLK_DIV_BY_128      	                 */
/*    	     		         			 */
/*********************************************************/
#define ADC_CLK CLK_DIV_BY_128 /* Default: CLK_DIV_BY_128  */

/*********************************************************/
/* Select ADC Bit Resolution  :-             	         */
/* 		         	                         */
/* Options : - EIGHT_BIT_RESOLUTION                      */
/*    	     - TEN_BIT_RESOLUTION		         */
/* 	                        		 	 */
/*********************************************************/
#define ADC_BIT_RESOLUTION EIGHT_BIT_RESOLUTION /* Default: Eight_BIT_RESOLUTION */

/*********************************************************/
/*							 */
/* Set ADC Timeout Value             	         	 */
/* 		         	                         */
/*********************************************************/
#define ADC_TIMEOUT	50000

#endif /*MCAL_ADC_CONFIG_H_*/
