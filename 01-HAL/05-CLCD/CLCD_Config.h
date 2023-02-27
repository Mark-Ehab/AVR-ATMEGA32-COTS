/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Sep 18, 2021               	*/
/*              SWC              : CLCD		        	*/
/*              Description	 : CLCD Config                  */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef HAL_CLCD_CONFIG_H_
#define HAL_CLCD_CONFIG_H_

/*********************************************************/
/* Select Character LCD Data Port :-       		 */
/* 		         	                         */
/* Options : - PORT_A                                    */
/*    	     - PORT_B	                                 */
/*           - PORT_C	                                 */
/*	     - PORT_D	                                 */
/* 	                          		 	 */
/*********************************************************/
#define CLCD_DATA_PORT 	   	PORT_C /* Default: PORT_C */
/*********************************************************/
/* Select Character LCD Control Pins Port :-       	 */
/* 		         	                         */
/* Options : - PORT_A                                    */
/*    	     - PORT_B	                                 */
/*           - PORT_C	                                 */
/*	     - PORT_D	                                 */
/* 	                          		 	 */
/*********************************************************/
#define CLCD_CTRL_PINS_PORT 	PORT_D /* Default: PORT_D */
/*********************************************************/
/* Select Character LCD RS Control Pin :-       	 */
/* 		         	                         */
/* Options : - PIN_0                                     */
/*    	     - PIN_1	                                 */
/*           - PIN_2	                                 */
/*	     - PIN_3	                                 */
/*	     - PIN_4                                     */
/*	     - PIN_5                                     */
/*	     - PIN_6                                     */
/*           - PIN_7                                     */
/* 	                          		 	 */
/*********************************************************/
#define CLCD_RS_PIN    		PIN_2 /* Default : PIN_2 */
/*********************************************************/
/* Select Character LCD RW Control Pin :-       	 */
/* 		         	                         */
/* Options : - PIN_0                                     */
/*    	     - PIN_1	                                 */
/*           - PIN_2	                                 */
/*	     - PIN_3	                                 */
/*	     - PIN_4                                     */
/*	     - PIN_5                                     */
/*	     - PIN_6                                     */
/*           - PIN_7                                     */
/* 	                          		 	 */
/*********************************************************/
#define CLCD_RW_PIN    		PIN_1 /* Default : PIN_1 */
/*********************************************************/
/* Select Character LCD E Control Pin :-       		 */
/* 		         	                         */
/* Options : - PIN_0                                     */
/*    	     - PIN_1	                                 */
/*           - PIN_2	                                 */
/*	     - PIN_3	                                 */
/*	     - PIN_4                                     */
/*	     - PIN_5                                     */
/*	     - PIN_6                                     */
/*           - PIN_7                                     */
/* 	                          		 	 */
/*********************************************************/
#define CLCD_E_PIN   	        PIN_0 /* Default : PIN_0 */

#endif /* HAL_CLCD_CONFIG_H_ */
