/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Feb 10, 2022               	*/
/*              SWC              : TIMER1			*/
/*              Description	 : TIMER1 Interface             */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_TIMER1_INTERFACE_H_
#define MCAL_TIMER1_INTERFACE_H_
        
/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                       DEFINING NEW TYPES FOR INTERFACING		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*
 * Define new enum type for Timer1 Input Capture Event Trigger Edges which are :
 * 1) Generate Input Capture Event request on The Falling Edge
 * 2) Generate Input Capture Event request on The Rising Edge
 */
typedef enum
{
	TIMER1_ICU_FALLING_EDGE   = 1,
	TIMER1_ICU_RISING_EDGE    = 2
}TIMER1_ICUTriggerEdge_e;


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 FUNCTIONS PROTOTYPES		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize Timer1 based on selected configurations from      */
/* 		     config file						  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void TIMER1_vidInit(void);
/**********************************************************************************/
/* Description     : Start Timer1 by setting Timer1 prescaler selected from       */
/* 		     config file					          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void TIMER1_vidStart(void);
/**********************************************************************************/
/* Description     : Stop Timer1  					          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void TIMER1_vidStop(void);
/**********************************************************************************/
/* Description     : Set preload value					          */
/* Input Arguments : u16 Copy_u16PreloadValue                                     */
/* Return          : void                                		          */
/**********************************************************************************/
void TIMER1_vidSetPreloadValue(u16 Copy_u16PreloadValue);
/**********************************************************************************/
/* Description     : Set compare match A value				          */
/* Input Arguments : u16 Copy_u16CompareMatchAValue                               */
/* Return          : void                                		          */
/**********************************************************************************/
void TIMER1_vidSetCompareMatchAValue(u16 Copy_u16CompareMatchAValue);
/**********************************************************************************/
/* Description     : Set compare match B value				          */
/* Input Arguments : u16 Copy_u16CompareMatchBValue                               */
/* Return          : void                                		          */
/**********************************************************************************/
void TIMER1_vidSetCompareMatchBValue(u16 Copy_u16CompareMatchBValue);
/**********************************************************************************/
/* Description     : Set input capture value				          */
/* Input Arguments : u16 Copy_u16InputCaptureValue                                */
/* Return          : void                                		          */
/**********************************************************************************/
void TIMER1_vidSetInputCaptureValue(u16 Copy_u16InputCaptureValue);
/**********************************************************************************/
/* Description     : Read Timer/Counter1 Value				          */
/* Input Arguments : void                                                         */
/* Return          : u16                                		          */
/**********************************************************************************/
u16 TIMER1_u16ReadTimerValue(void);
/**********************************************************************************/
/* Description     : Read Timer1 Input Capture Value			          */
/* Input Arguments : void                                                         */
/* Return          : void                                		          */
/**********************************************************************************/
u16 TIMER1_u16ReadInputCaptureValue(void);
/**********************************************************************************/
/* Description     : Enable Timer1 Overflow Interrupt			          */
/* Input Arguments : void                                                         */
/* Return          : void                                		          */
/**********************************************************************************/
void TIMER1_vidEnableOverflowInterrupt(void);
/**********************************************************************************/
/* Description     : Disable Timer1 Overflow Interrupt			          */
/* Input Arguments : void                        			          */
/* Return          : void                               	                  */
/**********************************************************************************/
void TIMER1_vidDisableOverflowInterrupt(void);
/**********************************************************************************/
/* Description     : Enable Timer1 Compare Match A Interrupt		          */
/* Input Arguments : void                            		    	          */
/* Return          : void                       		                  */
/**********************************************************************************/
void TIMER1_vidEnableCompareMatchAInterrupt(void);
/**********************************************************************************/
/* Description     : Disable Timer1 Compare Match A Interrupt		          */
/* Input Arguments : void                       				  */
/* Return          : void                    			                  */
/**********************************************************************************/
void TIMER1_vidDisableCompareMatchAInterrupt(void);
/**********************************************************************************/
/* Description     : Enable Timer1 Compare Match B Interrupt		          */
/* Input Arguments : void                            		    	          */
/* Return          : void                       		                  */
/**********************************************************************************/
void TIMER1_vidEnableCompareMatchBInterrupt(void);
/**********************************************************************************/
/* Description     : Disable Timer1 Compare Match B Interrupt		          */
/* Input Arguments : void                       				  */
/* Return          : void                    			                  */
/**********************************************************************************/
void TIMER1_vidDisableCompareMatchBInterrupt(void);
/**********************************************************************************/
/* Description     : Enable Timer1 Capture Event Interrupt		          */
/* Input Arguments : void                            		    	          */
/* Return          : void                       		                  */
/**********************************************************************************/
void TIMER1_vidEnableCaptureEventInterrupt(void);
/**********************************************************************************/
/* Description     : Disable Timer1 Capture Event Interrupt		          */
/* Input Arguments : void                       				  */
/* Return          : void                    			                  */
/**********************************************************************************/
void TIMER1_vidDisableCaptureEventInterrupt(void);
/**********************************************************************************/
/* Description     : Set Timer1 Input Capture Event Trigger Edge 		  */
/* 		     (Rising or Falling) Edge				          */
/* Input Arguments : TIMER1_ICUTriggerEdge_e Copy_EdgeType_e         		  */
/* Return          : u8                   			                  */
/**********************************************************************************/
u8 TIMER1_u8SetInputCaptureEventEdge(TIMER1_ICUTriggerEdge_e Copy_EdgeType_e);
/**********************************************************************************/
/* Description     : Register application callback function that will be called   */
/*		     immediately once Timer1 overflow ISR is triggered		  */
/* Input Arguments : void(*Copy_pvTIMER1OverflowFunc)(void)		          */
/* Return          : u8						                  */
/**********************************************************************************/
u8 TIMER1_u8SetOverflowCallback(void(*Copy_pvTIMER1OverflowFunc)(void));
/**********************************************************************************/
/* Description     : Register application callback function that will be called   */
/*		     immediately once Timer1 compare match A ISR is triggered	  */
/* Input Arguments : void(*Copy_pvTIMER1CompareMatchAFunc)(void)		  */
/* Return          : u8						                  */
/**********************************************************************************/
u8 TIMER1_u8SetCompareMatchACallback(void(*Copy_pvTIMER1CompareMatchAFunc)(void));
/**********************************************************************************/
/* Description     : Register application callback function that will be called   */
/*		     immediately once Timer1 compare match B ISR is triggered	  */
/* Input Arguments : void(*Copy_pvTIMER1CompareMatchBFunc)(void)		  */
/* Return          : u8						                  */
/**********************************************************************************/
u8 TIMER1_u8SetCompareMatchBCallback(void(*Copy_pvTIMER1CompareMatchBFunc)(void));
/**********************************************************************************/
/* Description     : Register application callback function that will be called   */
/*		     immediately once Timer1 capture event ISR is triggered	  */
/* Input Arguments : void(*Copy_pvTIMER1CaptureEventFunc)(void)		 	  */
/* Return          : u8						                  */
/**********************************************************************************/
u8 TIMER1_u8SetCaptureEventCallback(void(*Copy_pvTIMER1CaptureEventFunc)(void));
/**********************************************************************************/
/* Description     : A function used to delay the processor for some time in      */
/*		     milli-second based on passed value of time in milli-second   */
/* Input Arguments : u32 Copy_u32DelayTime_ms				          */
/* Return          : u8                                                	          */
/**********************************************************************************/
u8 TIMER1_u8SetBusyWait_ms(u32 Copy_u32DelayTime_ms);
/**********************************************************************************/
/* Description     : Start to generate PWM from Timer1 Output Compare Match 	  */
/*		     Channel A						          */
/* Input Arguments : u8 Copy_u8DutyCyclePercentage				  */
/* Return          : void						          */
/**********************************************************************************/
u8 TIMER1_u8StartPWMChannelA(u8 Copy_u8DutyCyclePercentage);
/**********************************************************************************/
/* Description     : Start to generate PWM from Timer1 Output Compare Match 	  */
/*		     Channel B						          */
/* Input Arguments : u8 Copy_u8DutyCyclePercentage				  */
/* Return          : void						          */
/**********************************************************************************/
u8 TIMER1_u8StartPWMChannelB(u8 Copy_u8DutyCyclePercentage);
        
#endif /* MCAL_TIMER1_INTERFACE_H_ */
