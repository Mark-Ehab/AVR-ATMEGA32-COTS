/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Feb 4, 2022               	*/
/*              SWC              : TIMER0			*/
/*              Description	 : TIMER0 Program               */
/* 	        Version          : V1.0                         */
/****************************************************************/

#include "../../../LIB/BIT_MATH.h"
#include "../../../LIB/STD_TYPES.h"
#include "../../../LIB/STD_ERRORS.h"
#include "../../../LIB/SERVICE_FUNCTIONS.h"

#include "TIMER0_Interface.h"
#include "TIMER0_Private.h"
#include "TIMER0_Config.h"


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            GLOBAL VARIABLES DEFINITIONS	                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

static f32 Global_f32Timer0OverflowTime = ((f32)TIMER0_PRESCALER/(f32)TIMER0_MCU_CLK_FREQ) * (f32)TIMER0_OVERFLOW_TICKS;	/* Global Variable to Hold Timer0 Overflow Time */
static void (*TIMER0_pvOverflowCallbakFunc)(void);										/* Pointer to Function to Hold Address of Overflow Function to Be Called Once Timer0 Overflow ISR is Triggered */
static void (*TIMER0_pvComapareMatchCallbakFunc)(void);										/* Pointer to Function to Hold Address of Compare Match Function to Be Called Once Timer0 Compare Match ISR is Triggered */

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  PRIVATE FUNCTIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Calculate Timer0 preload value     			  */
/* Input Arguments : f32 Copy_f32Delay_s , u32 Copy_u32OverflowNum	          */
/* Return          : u8							          */
/**********************************************************************************/
static u8 TIMER0_u8CalculateTimer0PreloadVal(f32 Copy_f32Delay_s , u32 Copy_u32OverflowNum)
{
	/* Define Some Local Variables */
	u8 Local_u8PreloadValue; 	/* Variable to hold preload value to be put in TCNT0 register before Timer0 starts */

	/* Check if passed delay is greater, less or equal to overflow time  */
	if(Copy_f32Delay_s > Global_f32Timer0OverflowTime)
	{
		Local_u8PreloadValue = TIMER0_OVERFLOW_TICKS * ((f32)Copy_u32OverflowNum-(Copy_f32Delay_s/Global_f32Timer0OverflowTime));
	}
	else if(Copy_f32Delay_s < Global_f32Timer0OverflowTime)
	{
		Local_u8PreloadValue = TIMER0_OVERFLOW_TICKS * (1.0f-(Copy_f32Delay_s/Global_f32Timer0OverflowTime));
	}
	else
	{
		Local_u8PreloadValue = 0;
	}

	return Local_u8PreloadValue;
}
/**********************************************************************************/
/* Description     : Set duty cycle value of PWM to be generated by Timer0        */
/* Input Arguments : u8 Copy_u8DutyCycle			 	          */
/* Return          : u8						                  */
/**********************************************************************************/
static u8 TIMER0_u8SetDutyCycle(u8 Copy_u8DutyCycle)
{
	/* Define Some Local Variables */
	u8 Local_u8ErrorState = RT_OK;     		/* A variable to hold function error status */

	if(Copy_u8DutyCycle <= 100)
	{
		u8 Local_u8CompareMatchValue;		/* A variable to hold compare match value to be calculated */

		#if   TIMER0_MODE == FAST_PWM_MODE

			#if   TIMER0_FAST_PWM_OUTPUT_COMPARE_PIN_MODE == NON_INVERTED_MODE

			Local_u8CompareMatchValue = TIMER0_OVERFLOW_TICKS * ((f32)Copy_u8DutyCycle * 0.01f);

			#elif TIMER0_FAST_PWM_OUTPUT_COMPARE_PIN_MODE == INVERTED_MODE

			Local_u8CompareMatchValue = TIMER0_OVERFLOW_TICKS - (TIMER0_OVERFLOW_TICKS * ((f32)Copy_u8DutyCycle * 0.01f));

			#endif
		#elif TIMER0_MODE == PHASE_CORRECT_PWM_MODE

			#if   TIMER0_PHASE_CORRECT_PWM_OUTPUT_COMPARE_PIN_MODE == NON_INVERTED_MODE

			Local_u8CompareMatchValue = TIMER0_OVERFLOW_TICKS * ((f32)Copy_u8DutyCycle * 0.01f);

			#elif TIMER0_PHASE_CORRECT_PWM_OUTPUT_COMPARE_PIN_MODE == INVERTED_MODE

			Local_u8CompareMatchValue = TIMER0_OVERFLOW_TICKS - (TIMER0_OVERFLOW_TICKS * ((f32)Copy_u8DutyCycle * 0.01f));

			#endif
		#endif

		/* Set Calculated Compare Match Value in OC0 Register */
		TIMER0_vidSetCompareMatchValue(Local_u8CompareMatchValue);
	}
	else
	{
		/* Function is not working as expected */
		Local_u8ErrorState = RT_NOK;
	}

	return Local_u8ErrorState;
}

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  PUBLIC FUNCTIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize Timer0 based on selected configurations from      */
/* 		     config file						  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void TIMER0_vidInit(void)
{
	/******************************************Set TIMER0 Operating Mode*****************************************/
	/* Clear waveform generation bits */
	TCCR0 &= TIMER0_WAVEFORM_GENERATION_MASK;
	/* Check selected operating mode For Timer0 From config file */
	#if   TIMER0_MODE == OVERFLOW_MODE
		/* Set Timer0 to work in overflow mode */
		TCCR0 |= TIMER0_OVERFLOW_MODE;
	#elif TIMER0_MODE == CTC_MODE
		/* Set Timer0 to work in ctc mode */
		TCCR0 |= TIMER0_CTC_MODE;
        #elif TIMER0_MODE == FAST_PWM_MODE
		/* Set Timer0 to work in fast PWM mode */
		TCCR0 |= TIMER0_FAST_PWM_MODE;
        #elif TIMER0_MODE == PHASE_CORRECT_PWM_MODE
		/* Set Timer0 to work in phase correct PWM mode */
		TCCR0 |= TIMER0_PHASE_CORRECT_PWM_MODE;
	#else
		#error "Wrong Timer0 Mode Configuration !"
	#endif


	/******************************************Set Timer0 Output Compare Match Pin Mode*****************************************/
        /* Clear Timer0 Output Compare Match Pin Mode Bits */
	TCCR0 &= TIMER0_OUTPUT_COMPARE_PIN_MODE_MASK;
	/* Check selected operating mode For Timer0 From config file */
	#if   TIMER0_MODE == OVERFLOW_MODE || TIMER0_MODE == CTC_MODE
	      /* Check mode of Timer0 output compare match pin (Non PWM) */
              #if   TIMER0_NON_PWM_OUTPUT_COMPARE_PIN_MODE == DISCONNECTED
		    /* Disconnect Timer0 output compare match pin */
		    TCCR0 |= TIMER0_NON_PWM_OUTPUT_COMPARE_PIN_DISCONNECTED;
              #elif TIMER0_NON_PWM_OUTPUT_COMPARE_PIN_MODE == TOGGLE
		    /* Toggle Timer0 output compare match pin */
		    TCCR0 |= TIMER0_NON_PWM_OUTPUT_COMPARE_PIN_TOGGLE;
              #elif TIMER0_NON_PWM_OUTPUT_COMPARE_PIN_MODE == CLEAR
		    /* Clear Timer0 output compare match pin */
		    TCCR0 |= TIMER0_NON_PWM_OUTPUT_COMPARE_PIN_CLEAR;
              #elif TIMER0_NON_PWM_OUTPUT_COMPARE_PIN_MODE == SET
		    /* Set Timer0 output compare match pin */
		    TCCR0 |= TIMER0_NON_PWM_OUTPUT_COMPARE_PIN_SET;
              #else
              	      #error "Wrong Timer0 Output Compare Match Pin (Non PWM) Configuration !"
              #endif
        #elif TIMER0_MODE == FAST_PWM_MODE
	      /* Check mode of Timer0 output compare match pin (Fast PWM) */
	      #if   TIMER0_FAST_PWM_OUTPUT_COMPARE_PIN_MODE == DISCONNECTED
		    /* Disconnect Timer0 output compare match pin */
		    TCCR0 |= TIMER0_FAST_PWM_OUTPUT_COMPARE_PIN_DISCONNECTED;
	      #elif TIMER0_FAST_PWM_OUTPUT_COMPARE_PIN_MODE == NON_INVERTED_MODE
		    /* Set Timer0 Fast PWM to Operate in Non Inverted Mode */
		    TCCR0 |= TIMER0_FAST_PWM_OUTPUT_COMPARE_PIN_NON_INVERTED_MODE;
	      #elif TIMER0_FAST_PWM_OUTPUT_COMPARE_PIN_MODE == INVERTED_MODE
		    /* Set Timer0 Fast PWM to Operate in Inverted Mode */
		    TCCR0 |= TIMER0_FAST_PWM_OUTPUT_COMPARE_PIN_INVERTED_MODE;
	      #else
	      	      #error "Wrong Timer0 Output Compare Match Pin (Fast PWM) Configuration !"
	      #endif
        #elif TIMER0_MODE == PHASE_CORRECT_PWM_MODE
	      /* Check mode of Timer0 output compare match pin (Phase-Correct PWM) */
	      #if   TIMER0_PHASE_CORRECT_PWM_OUTPUT_COMPARE_PIN_MODE == DISCONNECTED
		    /* Disconnect Timer0 output compare match pin */
		    TCCR0 |= TIMER0_PHASE_CORRECT_PWM_OUTPUT_COMPARE_DISCONNECTED;
	      #elif TIMER0_PHASE_CORRECT_PWM_OUTPUT_COMPARE_PIN_MODE == NON_INVERTED_MODE
		    /* Set Timer0 Phase Correct PWM to Operate in Non Inverted Mode */
		    TCCR0 |= TIMER0_PHASE_CORRECT_PWM_OUTPUT_COMPARE_NON_INVERTED_MODE;
	      #elif TIMER0_PHASE_CORRECT_PWM_OUTPUT_COMPARE_PIN_MODE == INVERTED_MODE
		    /* Set Timer0 Phase Correct PWM to Operate in Inverted Mode */
		    TCCR0 |= TIMER0_PHASE_CORRECT_PWM_OUTPUT_COMPARE_INVERTED_MODE;
	      #else
		      #error "Wrong Timer0 Output Compare Match Pin (Phase-Correct PWM) Configuration !"
	      #endif
	#else
		#error "Wrong Timer0 Mode Configuration !"
	#endif


       /******************************************Enable/Disable Timer0 Overflow and Compare Match Interrupts*****************************************/
       /* Check if Timer0 overflow interrupt is enabled or not from config file */
       #if   TIMER0_OVERFLOW_INTERRUPT_ENABLE == ENABLE
		    /* Enable Timer0 Overflow Interrupt */
		    SET_BIT(TIMSK,TIMSK_TOIE0);
       #elif TIMER0_OVERFLOW_INTERRUPT_ENABLE == DISABLE
		    /* Disable Timer0 Overflow Interrupt */
		    CLR_BIT(TIMSK,TIMSK_TOIE0);
       #else
       	       #error "Wrong Timer0 Overflow Interrupt Enable Signal Configuration !"
       #endif

       /* Check if Timer0 compare match interrupt is enabled or not from config file */
       #if   TIMER0_COMPARE_MATCH_INTERRUPT_ENABLE == ENABLE
		    /* Enable Timer0 Compare Match Interrupt */
		    SET_BIT(TIMSK,TIMSK_OCIE0);
       #elif TIMER0_COMPARE_MATCH_INTERRUPT_ENABLE == DISABLE
		    /* Disable Timer0 Compare Match Interrupt */
		    CLR_BIT(TIMSK,TIMSK_OCIE0);
       #else
       	       #error "Wrong Timer0 Compare Match Interrupt Enable Signal Configuration !"
       #endif
}
/**********************************************************************************/
/* Description     : Start Timer0 by setting Timer0 prescaler selected from       */
/* 		     config file					          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void TIMER0_vidStart(void)
{
	/* Clear Timer0 Clock Selection Bits */
	TCCR0 &= TIMER0_CLK_MASK;
	/* Check Selected Prescaler Value from Config File to Start Timer0 */
	#if   TIMER0_PRESCALER == CLK_DIV_BY_NO_PRESCALER
	        /* Set Timer0 clock to be the same as system clock without division by any prescalers */
		TCCR0 |= TIMER0_CLK_DIV_BY_NO_PRESCALER;
	#elif TIMER0_PRESCALER == CLK_DIV_BY_8
	        /* Set Timer0 clock to be system clock but divided by 8 prescaler */
		TCCR0 |= TIMER0_CLK_DIV_BY_8;
	#elif TIMER0_PRESCALER == CLK_DIV_BY_64
	        /* Set Timer0 clock to be system clock but divided by 64 prescaler */
		TCCR0 |= TIMER0_CLK_DIV_BY_64;
	#elif TIMER0_PRESCALER == CLK_DIV_BY_256
	        /* Set Timer0 clock to be system clock but divided by 256 prescaler */
		TCCR0 |= TIMER0_CLK_DIV_BY_256;
	#elif TIMER0_PRESCALER == CLK_DIV_BY_1024
	        /* Set Timer0 clock to be system clock but divided by 1024 prescaler */
		TCCR0 |= TIMER0_CLK_DIV_BY_1024;
	#elif TIMER0_PRESCALER == EXT_CLK_FALLING_EDGE
	        /* Set Timer0 to work on external clock source on T0 pin (clock on falling edge) */
		TCCR0 |= TIMER0_EXT_CLK_FALLING_EDGE;
	#elif TIMER0_PRESCALER == EXT_CLK_RISING_EDGE
	      	/* Set Timer0 to work on external clock source on T0 pin (clock on rising edge) */
		TCCR0 |= TIMER0_EXT_CLK_RISING_EDGE;
	#else
        	#error
	#endif
}
/**********************************************************************************/
/* Description     : Stop Timer0  					          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void TIMER0_vidStop(void)
{
	/* Clear Timer0 Clock Selection Bits (Stop Timer0) */
	TCCR0 &= TIMER0_CLK_MASK;
}
/**********************************************************************************/
/* Description     : Set preload value					          */
/* Input Arguments : u8 Copy_u8PreloadValue                                       */
/* Return          : void                                		          */
/**********************************************************************************/
void TIMER0_vidSetPreloadValue(u8 Copy_u8PreloadValue)
{
	/* Set Timer0 Preload Value in TCNT0 Register */
	TCNT0 = Copy_u8PreloadValue;
}
/**********************************************************************************/
/* Description     : Set compare match value				          */
/* Input Arguments : u8 Copy_u8CompareMatchValue                                  */
/* Return          : void                                		          */
/**********************************************************************************/
void TIMER0_vidSetCompareMatchValue(u8 Copy_u8CompareMatchValue)
{
	/* Set Compare Match Value in OCR0 Register */
	OCR0 = Copy_u8CompareMatchValue;
}
/**********************************************************************************/
/* Description     : Enable Timer0 Overflow Interrupt			          */
/* Input Arguments : void                                                         */
/* Return          : void                                		          */
/**********************************************************************************/
void TIMER0_vidEnableOverflowInterrupt(void)
{
	/* Enable Timer0 Overflow Interrupt */
	SET_BIT(TIMSK,TIMSK_TOIE0);
}
/**********************************************************************************/
/* Description     : Disable Timer0 Overflow Interrupt			          */
/* Input Arguments : void                        			          */
/* Return          : void                               	                  */
/**********************************************************************************/
void TIMER0_vidDisableOverflowInterrupt(void)
{
	/* Disable Timer0 Overflow Interrupt */
	CLR_BIT(TIMSK,TIMSK_TOIE0);
}
/**********************************************************************************/
/* Description     : Enable Timer0 Compare Match Interrupt		          */
/* Input Arguments : void                            		    	          */
/* Return          : void                       		                  */
/**********************************************************************************/
void TIMER0_vidEnableCompareMatchInterrupt(void)
{
	/* Enable Timer0 Compare Match Interrupt */
	SET_BIT(TIMSK,TIMSK_OCIE0);
}
/**********************************************************************************/
/* Description     : Disable Timer0 Compare Match Interrupt		          */
/* Input Arguments : void                       				  */
/* Return          : void                    			                  */
/**********************************************************************************/
void TIMER0_vidDisableCompareMatchInterrupt(void)
{
	/* Disable Timer0 Compare Match Interrupt */
	CLR_BIT(TIMSK,TIMSK_OCIE0);
}
/**********************************************************************************/
/* Description     : Register application callback function that will be called   */
/*		     immediately once Timer0 overflow ISR is triggered		  */
/* Input Arguments : void(*Copy_pvTIMER0OverflowFunc)(void)		          */
/* Return          : u8						                  */
/**********************************************************************************/
u8 TIMER0_u8SetOverflowCallback(void(*Copy_pvTIMER0OverflowFunc)(void))
{
	/* Define Some Local Variables */
	u8 Local_u8ErrorState = RT_OK;     /* A variable to hold function error status */

	/* Check if passed pointer to function is null pointer or not */
	if(Copy_pvTIMER0OverflowFunc == NULL)
	{
		/* Passed Pointer is NULL Pointer */
		Local_u8ErrorState = NULL_POINTER;
	}
	else
	{
		/* Register Timer0 Overflow Callback Function */
		TIMER0_pvOverflowCallbakFunc = Copy_pvTIMER0OverflowFunc;
	}

	return Local_u8ErrorState;
}
/**********************************************************************************/
/* Description     : Register application callback function that will be called   */
/*		     immediately once Timer0 compare match ISR is triggered	  */
/* Input Arguments : void(*Copy_pvTIMER0CompareMatchFunc)(void)		          */
/* Return          : u8						                  */
/**********************************************************************************/
u8 TIMER0_u8SetCompareMatchCallback(void(*Copy_pvTIMER0CompareMatchFunc)(void))
{
	/* Define Some Local Variables */
	u8 Local_u8ErrorState = RT_OK;     /* A variable to hold function error status */

	/* Check if passed pointer to function is null pointer or not */
	if(Copy_pvTIMER0CompareMatchFunc == NULL)
	{
		/* Passed Pointer is NULL Pointer */
		Local_u8ErrorState = NULL_POINTER;
	}
	else
	{
		/* Register Timer0 Overflow Callback Function */
		TIMER0_pvComapareMatchCallbakFunc = Copy_pvTIMER0CompareMatchFunc;
	}

	return Local_u8ErrorState;
}
/**********************************************************************************/
/* Description     : A function used to delay the processor for some time in      */
/*		     milli-second based on passed value of time in milli-second   */
/* Input Arguments : u32 Copy_u32DelayTime_ms				          */
/* Return          : u8                                                	          */
/**********************************************************************************/
u8 TIMER0_u8SetBusyWait_ms(u32 Copy_u32DelayTime_ms)
{
	/* Define Some Local Variables */
	u8 Local_u8ErrorState = RT_OK;     		/* A variable to hold function error status */

	if(Copy_u32DelayTime_ms < 4294967296)
	{
		f32 Local_f32DelayTime_s;               /* A variable to hold passed delay time in seconds */

		u32 Local_u32OverflowNum;		/* A variable to hold number of overflows required for Timer0 to achieve passed delay */

		u32 Local_u32OverflowCounter = 0;	/* A variable to count the number of overflows */

		u8 Local_u8PreloadValue ;		/* A variable to hold preload value to be calculated */

		/* Convert passed delay from milli-second to second */
		Local_f32DelayTime_s = (f32)Copy_u32DelayTime_ms * 0.001f;

		/* Get number of overflows required for Timer0 to reach passed delay */
		Local_u32OverflowNum = SERV_u32CeilDev(Local_f32DelayTime_s,Global_f32Timer0OverflowTime);

		/* Get Preload Value */
		Local_u8PreloadValue = TIMER0_u8CalculateTimer0PreloadVal(Local_f32DelayTime_s,Local_u32OverflowNum);

		/* Set Timer0 Preload Value Before Timer0 Starts */
		TIMER0_vidSetPreloadValue(Local_u8PreloadValue);

		/* Start Timer0 */
		TIMER0_vidStart();

		/* Wait until the delay is finished */
		while(Local_u32OverflowCounter < Local_u32OverflowNum)
		{
			/* Wait until TOV0 Flag is set by hardware */
			while(GET_BIT(TIFR,TIFR_TOV0) != 1);

			/* Clear TOV0 Flag by writing 1 to its bit in TIFR Register */
			SET_BIT(TIFR,TIFR_TOV0);

			/* Increment Overflow Counter */
			Local_u32OverflowCounter++;
		}

		/* Stop Timer0 */
		TIMER0_vidStop();
	}
	else
	{
		/* Function is not working as expected */
		Local_u8ErrorState = RT_NOK;
	}

	return Local_u8ErrorState;
}
/**********************************************************************************/
/* Description     : Start to generate PWM from Timer0			          */
/* Input Arguments : uu8 Copy_u8DutyCyclePercentage			          */
/* Return          : void						          */
/**********************************************************************************/
u8 TIMER0_u8StartPWM(u8 Copy_u8DutyCyclePercentage)
{
	/* Define Some Local Variables */
	u8 Local_u8ErrorState = RT_OK;     		/* A variable to hold function error status */

	if(Copy_u8DutyCyclePercentage <= 100)
	{
		/* Set Duty Cycle Percentage */
		TIMER0_u8SetDutyCycle(Copy_u8DutyCyclePercentage);

		/* Start Timer */
		TIMER0_vidStart();
	}
	else
	{
		/* Function is not working as expected */
		Local_u8ErrorState = RT_NOK;
	}

	return Local_u8ErrorState;
}

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            	  INTERRUPT HANDLERS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/************************************************/
/* 	Timer/Counter0 Overflow Interrupt	*/
/************************************************/
void __vector_11 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_11 (void)
{
	/* Check if Timer0 overflow function is registered or not */
	if(TIMER0_pvOverflowCallbakFunc != NULL)
	{
		/* Invoke Timer0 overflow function */
		TIMER0_pvOverflowCallbakFunc();
	}
}

/************************************************/
/*    Timer/Counter0 Compare Match Interrupt	*/
/************************************************/
void __vector_10 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_10 (void)
{
	/* Check if Timer0 compare match function is registered or not */
	if(TIMER0_pvComapareMatchCallbakFunc != NULL)
	{
		/* Invoke Timer0 compare match function */
		TIMER0_pvComapareMatchCallbakFunc();
	}
}
