/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Feb 4, 2022               	*/
/*              SWC              : TIMER0			*/
/*              Description	 : TIMER0 Interface             */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_TIMER0_INTERFACE_H_
#define MCAL_TIMER0_INTERFACE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 FUNCTIONS PROTOTYPES		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize Timer0 based on selected configurations from      */
/* 		     config file						  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void TIMER0_vidInit(void);
/**********************************************************************************/
/* Description     : Start Timer0 by setting Timer0 prescaler selected from       */
/* 		     config file					          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void TIMER0_vidStart(void);
/**********************************************************************************/
/* Description     : Stop Timer0  					          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void TIMER0_vidStop(void);
/**********************************************************************************/
/* Description     : Set preload value					          */
/* Input Arguments : u8 Copy_u8PreloadValue                                       */
/* Return          : void                                		          */
/**********************************************************************************/
void TIMER0_vidSetPreloadValue(u8 Copy_u8PreloadValue);
/**********************************************************************************/
/* Description     : Set compare match value				          */
/* Input Arguments : u8 Copy_u8CompareMatchValue                                  */
/* Return          : void                                		          */
/**********************************************************************************/
void TIMER0_vidSetCompareMatchValue(u8 Copy_u8CompareMatchValue);
/**********************************************************************************/
/* Description     : Enable Timer0 Overflow Interrupt			          */
/* Input Arguments : void                                                         */
/* Return          : void                                		          */
/**********************************************************************************/
void TIMER0_vidEnableOverflowInterrupt(void);
/**********************************************************************************/
/* Description     : Disable Timer0 Overflow Interrupt			          */
/* Input Arguments : void                        			          */
/* Return          : void                               	                  */
/**********************************************************************************/
void TIMER0_vidDisableOverflowInterrupt(void);
/**********************************************************************************/
/* Description     : Enable Timer0 Compare Match Interrupt		          */
/* Input Arguments : void                            		    	          */
/* Return          : void                       		                  */
/**********************************************************************************/
void TIMER0_vidEnableCompareMatchInterrupt(void);
/**********************************************************************************/
/* Description     : Disable Timer0 Compare Match Interrupt		          */
/* Input Arguments : void                       				  */
/* Return          : void                    			                  */
/**********************************************************************************/
void TIMER0_vidDisableCompareMatchInterrupt(void);
/**********************************************************************************/
/* Description     : Register application callback function that will be called   */
/*		     immediately once Timer0 overflow ISR is triggered		  */
/* Input Arguments : void(*Copy_pvTIMER0OverflowFunc)(void)		          */
/* Return          : u8						                  */
/**********************************************************************************/
u8 TIMER0_u8SetOverflowCallback(void(*Copy_pvTIMER0OverflowFunc)(void));
/**********************************************************************************/
/* Description     : Register application callback function that will be called   */
/*		     immediately once Timer0 compare match ISR is triggered	  */
/* Input Arguments : void(*Copy_pvTIMER0CompareMatchFunc)(void)		          */
/* Return          : u8						                  */
/**********************************************************************************/
u8 TIMER0_u8SetCompareMatchCallback(void(*Copy_pvTIMER0CompareMatchFunc)(void));
/**********************************************************************************/
/* Description     : A function used to delay the processor for some time in      */
/*		     milli-second based on passed value of time in milli-second   */
/* Input Arguments : u32 Copy_u32DelayTime_ms				          */
/* Return          : u8                                                	          */
/**********************************************************************************/
u8 TIMER0_u8SetBusyWait_ms(u32 Copy_u32DelayTime_ms);
/**********************************************************************************/
/* Description     : Start to generate PWM from Timer0			          */
/* Input Arguments : u8 Copy_u8DutyCyclePercentage				  */
/* Return          : void						          */
/**********************************************************************************/
u8 TIMER0_u8StartPWM(u8 Copy_u8DutyCyclePercentage);

#endif /* MCAL_TIMER0_INTERFACE_H_ */
