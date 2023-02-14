/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Dec 19, 2022               	*/
/*              SWC              : SSD				*/
/*              Description	 : SSD Config                   */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef HAL_SSD_CONFIG_H_
#define HAL_SSD_CONFIG_H_

/************************************************************************/
/* Configure the type of seven segment common:- 			*/
/*					        			*/
/* Options :  - COMMON_CATHODE		       				*/
/* 	      -	COMMON_ANODE		       				*/
/* 					       				*/
/************************************************************************/
#define SSD_COMMON_TYPE COMMON_CATHODE /* Default: COMMON_CATHODE */

/************************************************************************/
/* Configure seven segment mode:-              				*/
/*					       				*/
/* Options :  - SINGLE_MODE		       				*/
/* 	      - MULTIPLEXING_MODE              				*/
/* 					      			        */
/************************************************************************/
#define SSD_MODE MULTIPLEXING_MODE /* Default: SINGLE_MODE */

/************************************************************************/
/* Configure the port of seven segment:-				*/
/*                                                                      */
/* Options :  - PORT_A                                                  */
/* 	      - PORT_B                                         	        */
/* 	      - PORT_C                                          	*/
/* 	      - PORT_D                                                  */
/*									*/
/* Note    : This port could be used either for a single SSD 		*/
/* 	     or for two multiplexing SSDs    			        */
/*                                                                      */
/************************************************************************/
#define SSD_PORT_CFG PORT_A /* Default: PORTA */

/************************************************************************/
/* Configure the port of seven segment common:- 			*/
/*					       				*/
/* Options :  - PORT_A                         				*/
/* 	      - PORT_B               	       				*/
/* 	      - PORT_C               	       				*/
/* 	      - PORT_D               	       				*/
/* 					       				*/
/************************************************************************/
#define SSD_PORT_COMMON_CFG PORT_B /* Default: PORTB */

/************************************************************************/
/* In case of one seven segment, Configure the pin of its common on the */
/* seven segment common port:- 						*/
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
#define SSD_PIN_COMMON_CFG  PIN_0 /* Default: PIN_0 */

/************************************************************************/
/* In case of two multiplexing, Configure the two pins of their common 	*/
/* on the seven segment common port:- 					*/
/*                                                  			*/
/* Options :  - PIN_0                               			*/
/* 	      - PIN_1                  	            			*/
/* 	      - PIN_2                  	           		   	*/
/* 	      - PIN_3                  	            			*/
/* 	      - PIN_4                  	            			*/
/* 	      - PIN_5                  	            			*/
/* 	      - PIN_6                  	            			*/
/* 	      - PIN_7                  	            			*/
/*						    			*/
/* Note    : Only Selected in SSD Multiplexing Mode 			*/
/* 									*/
/************************************************************************/
#define SSD_PIN_FIRST_COMMON_CFG  PIN_0 /* Default: PIN_0 */
#define SSD_PIN_SECOND_COMMON_CFG PIN_1 /* Default: PIN_1 */

#endif /* HAL_SSD_CONFIG_H_ */
