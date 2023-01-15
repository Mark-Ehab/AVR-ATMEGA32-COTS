/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Dec 19, 2022               	*/
/*              SWC              : SSD				*/
/*              Description	 : SSD Config                   */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef HAL_SSD_CONFIG_H_
#define HAL_SSD_CONFIG_H_

/***********************************************/
/* Configure the type of seven segment common: */
/*					       */
/* Options : 1) Common Cathode		       */
/* 	      2) Common Anode		       */
/***********************************************/
#define SSD_COMMON_TYPE 1 //Default: Common Cathode

/***********************************************/
/* Configure seven segment mode:               */
/*					       */
/* Options : 1) Single Mode		       */	
/* 	      2) Multiplexing Mode             */
/***********************************************/
#define SSD_MODE 2

/************************************************************************/
/* Configure the port of seven segment (could be used for multiplexing) */
/*                                                                      */
/* Options : 1) PORT_A                                                  */
/* 	      2) PORT_B                                         	*/
/* 	      3) PORT_C                                          	*/
/* 	      4) PORT_D                                                 */
/************************************************************************/
#define SSD_PORT_CFG PORT_A //Default: PORTA

/***********************************************/
/* Configure the port of seven segment common: */
/*					       */
/* Options : 1) PORT_A                         */
/* 	      2) PORT_B               	       */
/* 	      3) PORT_C               	       */
/* 	      4) PORT_D               	       */
/***********************************************/
#define SSD_PORT_COMMON_CFG PORT_B //Default: PORTB

/************************************************************************/
/* In case of one seven segment, Configure the pin of its common on the */
/* seven segment common port 						*/
/*                                                                      */
/* Options : 1) PIN_0                                                   */
/* 	      2) PIN_1                                                  */
/* 	      3) PIN_2                                                  */
/* 	      4) PIN_3                                                  */
/* 	      5) PIN_4                                                  */
/* 	      6) PIN_5                                                  */
/* 	      7) PIN_6                                                  */
/* 	      8) PIN_7                                                  */
/************************************************************************/
#define SSD_PIN_COMMON_CFG  PIN_0 //Default: PIN_0

/****************************************************/
/* In case of two multiplexing, Configure the two   */
/* pins of their common on the seven segment common */
/* port: 					    */      
/*                                                  */
/* Options : 1) PIN_0                               */
/* 	      2) PIN_1                  	    */
/* 	      3) PIN_2                  	    */
/* 	      4) PIN_3                  	    */
/* 	      5) PIN_4                  	    */
/* 	      6) PIN_5                  	    */
/* 	      7) PIN_6                  	    */
/* 	      8) PIN_7                  	    */
/****************************************************/
#define SSD_PIN_FIRST_COMMON_CFG  PIN_0
#define SSD_PIN_SECOND_COMMON_CFG PIN_1

#endif /* HAL_SSD_SSD_CONFIG_H_ */
