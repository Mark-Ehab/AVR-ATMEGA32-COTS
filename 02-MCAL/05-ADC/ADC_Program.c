/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Oct 15, 2021               	*/
/*              SWC              : ADC				*/
/*              Description	 : ADC Program                  */
/* 	        Version          : V1.0                         */
/****************************************************************/

#include "../../LIB/STD_ERRORS.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "ADC_Config.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            GLOBAL VARIABLES DEFINITIONS	                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Global Pointer to u16 to Hold Memory Address of ADC Reading After Conversion Completes */
static u16* Global_pu16Reading = NULL; 						/* Used for both 10-bit and 8-bit Resolutions */

/* Define a global variable to tell the status of ADC whether it's busy or idle */
static u8 Global_u8AdcStatus = ADC_IDLE ; 					/* Initialize ADC status as idle */

/* Define a global variable to specify ADC Conversion Complete ISR Source whether form ChainAsync or not */
static u8 Global_u8ADCISRSource;

/* Define Chain ADC related global variables */
static u8*  Global_pu8ADCChainId = NULL;  					/* Variable to hold chain address (ID) */
static u8   Global_u8ADCChainSize;	  					/* Variable to hold chain size (numbers of chain channels) */
static u16* Global_pu16ADCChainResult = NULL;					/* Variable to hold chain result array address */
static u8   Global_u8ADCChainIndex = 0;						/* Variable to hold current chain index */
static void(*ADC_pvChainConversionCompleteNotificationFunc)(void) = NULL;	/* A pointer to function for chain channel async callback */

/* Define a pointer to function for single channel async callback */
static void(*ADC_pvConversionCompleteNotificationFunc)(void) = NULL;

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  PRIVATE FUNCTIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Start ADC conversion 			              	  */
/* Input Arguments : void							  */
/* Return          : void							  */
/**********************************************************************************/
static void ADC_vidStartConversion(void)
{
	SET_BIT(ADCSRA,ADCSRA_ADSC);
}
/**********************************************************************************/
/* Description     : Enable ADC conversion complete interrupt                 	  */
/* Input Arguments : void							  */
/* Return          : void							  */
/**********************************************************************************/
static void ADC_vidEnableInterrupt(void)
{
	SET_BIT(ADCSRA,ADCSRA_ADIE);
}
/**********************************************************************************/
/* Description     : Disable ADC conversion complete interrupt                 	  */
/* Input Arguments : void							  */
/* Return          : void							  */
/**********************************************************************************/
static void ADC_vidDisableInterrupt(void)
{
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
}

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  PUBLIC FUNCTIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize ADC peripheral with the pre-bulid configurations  */
/*                   stated in config file                                        */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/  
void ADC_vidInit(void)
{
   /******************************************Set ADC Reference Voltage*****************************************/
   /* Clear ADC reference voltage selection bits */
   ADMUX &= ADC_REF_VOLT_MASK;
   /* Check the reference voltage mode for ADC */
   #if   ADC_REF_VOLT == AREF
	ADMUX |= ADC_AREF;
   #elif ADC_REF_VOLT == AVCC
	ADMUX |= ADC_AVCC;
   #elif ADC_REF_VOLT == INTERNAL_VOLT
	ADMUX |= ADC_INTERNAL_VOLT;
   #else
	#error "Wrong ADC Reference Voltage Configuration"
   #endif


   /******************************************Set ADC Result Adjustment*****************************************/
   /* Check if ADC result in ADC data registers (ADCH,ADCL) is left adjusted or not */
   #if   ADC_RESULT_ADJUSTMENT == RIGHT_ADJUSTMENT
	CLR_BIT(ADMUX,ADMUX_ADLAR);
   #elif ADC_RESULT_ADJUSTMENT == LEFT_ADJUSTMENT
	SET_BIT(ADMUX,ADMUX_ADLAR);
   #else
	#error "Wrong ADC Result Adjustment Configuration"
   #endif


   /******************************************Set ADC Auto-Trigger*****************************************/
   /* Check if ADC auto-trigger is enabled or not */
   #if   ADC_AUTO_TRIGGER == AUTO_TRIGGER_ENABLE
	/* Enable Auto-Trigger */
	SET_BIT(ADCSRA,ADCSRA_ADATE);
	/* Clear Auto-Trigger Source Selection Bits */
	SFIOR &= ADC_AUTO_TRIGGER_SOURCE_MASK;
	/* Check Selected Auto Trigger Source */
	#if   ADC_AUTO_TRIGGER_SOURCE == FREE_RUNNING
		/* Enable Free Running Mode */
		SFIOR |= ADC_FREE_RUNNING;
		/* Clear ADC Single Ended Channels Bits in ADMUX Register */
		ADMUX &= ADC_SINGLE_ENDED_CHANNELS_MASK;
		/* Select the ADC channel to read from */
		ADMUX |= ADC_AUTO_TRIGGER_CHANNEL;
	#elif ADC_AUTO_TRIGGER_SOURCE == ANALOG_COMPARATOR
		/* Enable Analog Comparator */
		SFIOR |= ADC_ANALOG_COMPARATOR;
	#elif ADC_AUTO_TRIGGER_SOURCE == EXTERNAL_INTERRUPT_REQUEST0
		/* Enable External Interrupt Request 0 */
		SFIOR |= ADC_EXTI0;
	#elif ADC_AUTO_TRIGGER_SOURCE == TIMER0_COMPARE_MATCH
		/* Enable Timer0 Compare Match */
		SFIOR |= ADC_TIMER0_COMPARE_MATCH;
	#elif ADC_AUTO_TRIGGER_SOURCE == TIMER0_OVERFLOW
		/* Enable Timer0 OverFlow */
		SFIOR |= ADC_TIMER0_OVERFLOW;
	#elif ADC_AUTO_TRIGGER_SOURCE == TIMER_COMPARE_MATCH_B
		/* Enable Timer Compare Match B */
		SFIOR |= ADC_TIMER_COMPARE_MATCH_B;
	#elif ADC_AUTO_TRIGGER_SOURCE == TIMER1_OVERFLOW
		/* Timer1 OverFlow */
		SFIOR |= ADC_TIMER1_OVERFLOW;
	#elif ADC_AUTO_TRIGGER_SOURCE == TIMER1_CAPTURE_EVENT
		/* Timer1 Capture Event */
		SFIOR |= ADC_TIMER1_CAPTURE_EVENT;
	#else
		#error "Wrong ADC Auto-Trigger Source Configuration"
	#endif
   #elif ADC_AUTO_TRIGGER == AUTO_TRIGGER_DISABLE
	/* Disable Auto-Trigger and Select ADC Single Conversion Mode */
	CLR_BIT(ADCSRA,ADCSRA_ADATE);
   #else
	#error "Wrong ADC Auto-Trigger Configuration"
   #endif


   /******************************************Set ADC Clock Pre-Scaler*****************************************/
   /* Clear ADC CLK Pre-Scaler Selection Bits*/
   ADCSRA &= ADC_CLK_MASK;
   /* Check selected ADC pre-scaler for CLK fed to ADC */
   #if   ADC_CLK == CLK_DIV_BY_2
   	   /* Select 2 as CLK Division Pre-Scaler */
   	   ADCSRA |= ADC_CLK_DIV_BY_2;
   #elif ADC_CLK == CLK_DIV_BY_4
   	   /* Select 4 as CLK Division Pre-Scaler */
   	   ADCSRA |= ADC_CLK_DIV_BY_4;
   #elif ADC_CLK == CLK_DIV_BY_8
   	   /* Select 8 as CLK Division Pre-Scaler */
   	   ADCSRA |= ADC_CLK_DIV_BY_8;
   #elif ADC_CLK == CLK_DIV_BY_16
   	   /* Select 16 as CLK Division Pre-Scaler */
   	   ADCSRA |= ADC_CLK_DIV_BY_16;
   #elif ADC_CLK == CLK_DIV_BY_32
   	   /* Select 32 as CLK Division Pre-Scaler */
   	   ADCSRA |= ADC_CLK_DIV_BY_32;
   #elif ADC_CLK == CLK_DIV_BY_64
   	   /* Select 64 as CLK Division Pre-Scaler */
   	   ADCSRA |= ADC_CLK_DIV_BY_64;
   #elif ADC_CLK == CLK_DIV_BY_128
   	   /* Select 128 as CLK Division Pre-Scaler */
   	   ADCSRA |= ADC_CLK_DIV_BY_128;
   #else
	#error "Wrong ADC Clock Pre-Scaler Configuration"
   #endif


   /* Disable ADC Conversion Complete Interrupt */
   ADC_vidDisableInterrupt();


   /* Enable ADC */
   SET_BIT(ADCSRA,ADCSRA_ADEN);


   /* Check if Free Running Mode is Enabled or Not to Start Conversion */
   #if(ADC_AUTO_TRIGGER == AUTO_TRIGGER_ENABLE && ADC_AUTO_TRIGGER_SOURCE == FREE_RUNNING)
	   /* Start ADC Conversion */
	   ADC_vidStartConversion();
   #endif

}
/**********************************************************************************/
/* Description     : This function starts ADC conversion through polling (busy-   */
/*                   waiting) on ADIF flag in ADCSRA register and performs only	  */
/* 		     a single conversion					  */
/* Input Arguments : u8 Copy_u8ChannelNum , u16* Copy_pu16Reading		  */
/* Return          : u8							          */
/* Note            : This function used for both 8-bit and 10-bit ADC resolutions */
/**********************************************************************************/
u8 ADC_u8GetAdcReadingSyncSingleConversion(u8 Copy_u8ChannelNum , u16* Copy_pu16Reading)
{
   /* Defining Some Local Variables */
   u8 Local_u8ErrorStatus = RT_OK;    /* A variable to hold function error status */
   u8 Local_u32AdcTimeOutCounter = 0; /* A variable to hold ADC Timeout count */

   /* Check if ADC is idle or busy */
   if(Global_u8AdcStatus == ADC_IDLE)
   {
  	  /* Check if passed pointer is NULL pointer or not */
  	  if(Copy_pu16Reading == NULL)
  	  {
  		  Local_u8ErrorStatus = NULL_POINTER;
  	  }
  	  else
  	  {
  		  /* Set ADC Status as Busy */
  		  Global_u8AdcStatus = ADC_BUSY;

  		  /* Clear ADC Single Ended Channels Bits in ADMUX Register */
  		  ADMUX &= ADC_SINGLE_ENDED_CHANNELS_MASK;

  		  /* Select the ADC channel to read from */
  		  ADMUX |= Copy_u8ChannelNum;

  		  /* Start ADC Conversion */
  		  ADC_vidStartConversion();

  		  /* Polling (busy waiting) over ADC Conversion Complete Interrupt Flag untill it's set to 1 or when ADC reaches Timeout */
  		  while((GET_BIT(ADCSRA,ADCSRA_ADIF) == 0) && (Local_u32AdcTimeOutCounter < ADC_TIMEOUT))
  		  {
  			  Local_u32AdcTimeOutCounter++;
  		  }

  		  /* Check if ADC reached Timeout or not */
  		  if(Local_u32AdcTimeOutCounter == ADC_TIMEOUT)
  		  {
  			  Local_u8ErrorStatus = RT_NOK;
  		  }
  		  else
  		  {
  			  /* Clear ADC Conversion Complete Interrupt Flag By Writing 1 to ADIF Bit */
  			  SET_BIT(ADCSRA,ADCSRA_ADIF);

  			  /* Check ADC bit resolution based on configuration to build its functions */
  			  #if    ADC_BIT_RESOLUTION == EIGHT_BIT_RESOLUTION
  				/* Check if ADC result in ADC data registers (ADCH,ADCL) is left adjusted or not */
  				#if   ADC_RESULT_ADJUSTMENT == RIGHT_ADJUSTMENT
  					 /* Get ADC Reading */
  					 *Copy_pu16Reading = ((u8)(ADCL>>2)|(u8)(ADCH<<6));
  				#elif ADC_RESULT_ADJUSTMENT == LEFT_ADJUSTMENT
  					 /* Get ADC Reading */
  					 *Copy_pu16Reading = ADCH;
  				#else
  					#error "Wrong ADC Result Adjustment Configuration"
  				#endif
  			  #elif  ADC_BIT_RESOLUTION == TEN_BIT_RESOLUTION
  				/* Check if ADC result in ADC data registers (ADCH,ADCL) is left adjusted or not */
  				#if   ADC_RESULT_ADJUSTMENT == RIGHT_ADJUSTMENT
  					/* Get ADC Reading */
  					*Copy_pu16Reading = ((u16)ADCL|(u16)(ADCH<<8));
  				#elif ADC_RESULT_ADJUSTMENT == LEFT_ADJUSTMENT
  					/* Get ADC Reading */
  					*Copy_pu16Reading = ((u16)(ADCL>>6)|(u16)(ADCH<<2));
  				#else
  					#error "Wrong ADC Result Adjustment Configuration"
  				#endif
  			  #else
  				#error "Wrong Bit Resolution Configuration"
  			  #endif

  			  /* Set ADC Status as Idle */
  			  Global_u8AdcStatus = ADC_IDLE;
  		  }
  	  }
   }
   else
   {
  	  Local_u8ErrorStatus = BUSY_FUNC;
   }
   return Local_u8ErrorStatus ;
}
/**********************************************************************************/
/* Description     : This function starts ADC conversion and when conversion      */
/*                   completes, the hardware generates an interrupt to get the    */
/*                   ADC reading without busy-waiting the processor and performs  */
/* 		     a single conversion				  	  */
/* Input Arguments : u8 Copy_u8ChanelNum , u16 * Copy_pu16Reading,		  */
/*                   void(*Copy_pvAdcNotificationFunc)(void)			  */
/* Return          : u8								  */
/* Note            : This function used for both 8-bit and 10-bit ADC resolutions */
/**********************************************************************************/
u8 ADC_u8GetAdcReadingAsyncSingleConversion(u8 Copy_u8ChannelNum , u16* Copy_pu16Reading, void(*Copy_pvAdcNotificationFunc)(void))
{
   /* Defining Some Local Variables */
   u8 Local_u8ErrorStatus = RT_OK;    /* A variable to hold function error status */

   /* Check if ADC is idle or busy */
   if(Global_u8AdcStatus == ADC_IDLE)
   {
	   /* Check if passed pointer is NULL pointer or not */
	   if(Copy_pu16Reading == NULL)
	   {
		   Local_u8ErrorStatus = NULL_POINTER;
	   }
	   else
	   {
		   /* Set ADC Status as Busy */
		   Global_u8AdcStatus = ADC_BUSY;

		   /* Initialize the global ADC reading pointer that will hold the address of ADC reading after conversion completes */
		   Global_pu16Reading = Copy_pu16Reading;

		   /* Register the callback function to be called in ISR after ADC conversion completes */
		   ADC_pvConversionCompleteNotificationFunc = Copy_pvAdcNotificationFunc;

		   /* Clear ADC Single Ended Channels Bits in ADMUX Register */
		   ADMUX &= ADC_SINGLE_ENDED_CHANNELS_MASK;

		   /* Select the ADC channel to read from */
		   ADMUX |= Copy_u8ChannelNum;

		   /* Set ADC Conversion Complete ISR Source As ADC_SINGLE_CHANNEL_ASYNC */
		   Global_u8ADCISRSource = ADC_SINGLE_CHANNEL_ASYNC;

		   /* Enable ADC Conversion Complete Interrupt */
		   ADC_vidEnableInterrupt();

		   /* Start ADC Conversion */
		   ADC_vidStartConversion();
	   }
   }
   else
   {
	     Local_u8ErrorStatus = BUSY_FUNC;
   }
   return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : This function gets ADC conversion reading synchronously in   */
/*                   Free Running mode						  */
/* Input Arguments : u16* Copy_pu16Reading				          */
/* Return          : u8							          */
/* Note            : This function used for both 8-bit and 10-bit ADC resolutions */
/**********************************************************************************/
u8 ADC_u8GetAdcReadingSyncFreeRunning(u16* Copy_pu16Reading)
{
   /* Defining Some Local Variables */
   u8 Local_u8ErrorStatus = RT_OK;    /* A variable to hold function error status */
   u8 Local_u32AdcTimeOutCounter = 0; /* A variable to hold ADC Timeout count */

   /* Check if passed pointer is NULL pointer or not */
   if(Copy_pu16Reading == NULL)
   {
	   Local_u8ErrorStatus = NULL_POINTER;
   }
   else
   {
	   /* Polling (busy waiting) over ADC Conversion Complete Interrupt Flag untill it's set to 1 or when ADC reaches Timeout */
	   while((GET_BIT(ADCSRA,ADCSRA_ADIF) == 0) && (Local_u32AdcTimeOutCounter < ADC_TIMEOUT))
	   {
	 	   Local_u32AdcTimeOutCounter++;
	   }

	   /* Check if ADC reached Timeout or not */
	   if(Local_u32AdcTimeOutCounter == ADC_TIMEOUT)
	   {
	 	   Local_u8ErrorStatus = RT_NOK;
	   }
	   else
	   {
		   /* Clear ADC Conversion Complete Interrupt Flag By Writing 1 to ADIF Bit */
		   SET_BIT(ADCSRA,ADCSRA_ADIF);

		   /* Check ADC bit resolution based on configuration to build its functions */
		   #if    ADC_BIT_RESOLUTION == EIGHT_BIT_RESOLUTION
			/* Check if ADC result in ADC data registers (ADCH,ADCL) is left adjusted or not */
			#if   ADC_RESULT_ADJUSTMENT == RIGHT_ADJUSTMENT
				 /* Get ADC Reading */
				  *Copy_pu16Reading  = ((u8)(ADCL>>2)|(u8)(ADCH<<6));
			#elif ADC_RESULT_ADJUSTMENT == LEFT_ADJUSTMENT
				 /* Get ADC Reading */
				  *Copy_pu16Reading = ADCH;
			#else
				#error "Wrong ADC Result Adjustment Configuration"
			#endif
		   #elif  ADC_BIT_RESOLUTION == TEN_BIT_RESOLUTION
			/* Check if ADC result in ADC data registers (ADCH,ADCL) is left adjusted or not */
			#if   ADC_RESULT_ADJUSTMENT == RIGHT_ADJUSTMENT
				/* Get ADC Reading */
				*Copy_pu16Reading  = ((u16)ADCL|(u16)(ADCH<<8));
			#elif ADC_RESULT_ADJUSTMENT == LEFT_ADJUSTMENT
				/* Get ADC Reading */
				*Copy_pu16Reading  = ((u16)(ADCL>>6)|(u16)(ADCH<<2));
			#else
				#error "Wrong ADC Result Adjustment Configuration"
			#endif
		   #else
			#error "Wrong Bit Resolution Configuration"
		   #endif
	   }
   }
   return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : This function gets ADC conversion reading asynchronously in  */
/*                   Free Running mode						  */
/* Input Arguments : u16 * Copy_pu16Reading,					  */
/* 		     void(*Copy_pvAdcNotificationFunc)(void)		  	  */
/* Return          : u8								  */
/* Note            : This function used for both 8-bit and 10-bit ADC resolutions */
/**********************************************************************************/
u8 ADC_u8GetAdcReadingAsyncFreeRunning(u16* Copy_pu16Reading, void(*Copy_pvAdcNotificationFunc)(void))
{
   /* Defining Some Local Variables */
   u8 Local_u8ErrorStatus = RT_OK;    /* A variable to hold function error status */

   /* Check if passed pointer is NULL pointer or not */
   if(Copy_pu16Reading == NULL)
   {
	   Local_u8ErrorStatus = NULL_POINTER;
   }
   else
   {
	   /* Initialize the global ADC reading pointer that will hold the address of ADC reading after conversion completes */
	   Global_pu16Reading = Copy_pu16Reading;

	   /* Register the callback function to be called in ISR after ADC conversion completes */
	   ADC_pvConversionCompleteNotificationFunc = Copy_pvAdcNotificationFunc;

	   /* Enable ADC Conversion Complete Interrupt */
	   ADC_vidEnableInterrupt();
   }
   return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : This function gets ADC conversion chain reading in single    */
/* 		     conversion mode asynchronously  				  */
/* Input Arguments : ADC_Chain_s* Copy_Chain_ps					  */
/* Return          : u8								  */
/* Note            : This function used for both 8-bit and 10-bit ADC resolutions */
/**********************************************************************************/
u8 ADC_u8GetAdcReadingChainAsyncSingleConversion(ADC_Chain_s* Copy_Chain_ps)
{
	/* Define Some Local Variables */
	u8 Local_u8ErrorStatus = RT_OK;

	/* Check if ADC is idle or busy */
	if(Global_u8AdcStatus == ADC_IDLE)
	{
		if(Copy_Chain_ps == NULL)
		{
			Local_u8ErrorStatus = NULL_POINTER;
		}
		else
		{
			/* Set ADC Status as Busy */
			Global_u8AdcStatus = ADC_BUSY;

			/* Initialize Global Variable That Will Hold Chain Id */
			Global_pu8ADCChainId = Copy_Chain_ps -> ADC_pu8ChainID;

			/* Initialize Global Variable That Will Hold Chain Size */
			Global_u8ADCChainSize = Copy_Chain_ps -> ADC_u8Size;

			/* Initialize Global Variable That Will Hold Chain Result */
			Global_pu16ADCChainResult = Copy_Chain_ps -> ADC_pu16ChainResult;

			/* Register ADC Chain Conversion Complete Callback Function */
			ADC_pvChainConversionCompleteNotificationFunc = Copy_Chain_ps -> ADC_pvChainNotificationFunc;

			/* Clear ADC Single Ended Channels Bits in ADMUX Register */
			ADMUX &= ADC_SINGLE_ENDED_CHANNELS_MASK;

			/* Select the ADC channel to read from */
			ADMUX |= Global_pu8ADCChainId[Global_u8ADCChainIndex];

			/* Set ADC Conversion Complete ISR Source As ADC_CHAIN_CHANNEL_ASYNC */
			Global_u8ADCISRSource = ADC_CHAIN_CHANNEL_ASYNC;

			/* Enable ADC Conversion Complete Interrupt */
			ADC_vidEnableInterrupt();

			/* Start ADC Conversion */
			ADC_vidStartConversion();
		}
	}
	else
	{
		Local_u8ErrorStatus = BUSY_FUNC;
	}
	return Local_u8ErrorStatus;
}

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            	  INTERRUPT HANDLERS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/************************************************/
/* 	ADC Conversion Complete Interrupt	*/
/************************************************/
void __vector_16 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_16 (void)
{
	/* Check if Single Conversion Mode is Enabled */
	#if ADC_AUTO_TRIGGER == AUTO_TRIGGER_DISABLE
		/* Check ADC Conversion Complete ISR Source */
		if(Global_u8ADCISRSource == ADC_SINGLE_CHANNEL_ASYNC)
		{
			/* Check ADC bit resolution based on configuration to build its functions */
			#if    ADC_BIT_RESOLUTION == EIGHT_BIT_RESOLUTION
				/* Check if ADC result in ADC data registers (ADCH,ADCL) is left adjusted or not */
				#if   ADC_RESULT_ADJUSTMENT == RIGHT_ADJUSTMENT
					/* Get ADC Reading */
					*Global_pu16Reading = ((u8)(ADCL>>2)|(u8)(ADCH<<6));
				#elif ADC_RESULT_ADJUSTMENT == LEFT_ADJUSTMENT
					/* Get ADC Reading */
					*Global_pu16Reading = ADCH;
				#else
					#error "Wrong ADC Result Adjustment Configuration"
				#endif
			#elif  ADC_BIT_RESOLUTION == TEN_BIT_RESOLUTION
				/* Check if ADC result in ADC data registers (ADCH,ADCL) is left adjusted or not */
				#if   ADC_RESULT_ADJUSTMENT == RIGHT_ADJUSTMENT
					/* Get ADC Reading */
					*Global_pu16Reading = ((u16)ADCL|(u16)(ADCH<<8));
				#elif ADC_RESULT_ADJUSTMENT == LEFT_ADJUSTMENT
					/* Get ADC Reading */
					*Global_pu16Reading = ((u16)(ADCL>>6)|(u16)(ADCH<<2));
				#else
					#error "Wrong ADC Result Adjustment Configuration"
				#endif
			#else
				#error "Wrong Bit Resolution Configuration"
			#endif
			/* Set ADC as Idle */
			Global_u8AdcStatus = ADC_IDLE;

			/* Check if ADC conversion complete notification callback function is registered or not */
			if(ADC_pvConversionCompleteNotificationFunc != NULL)
			{
				/* Invoke ADC conversion complete notification callback function */
				ADC_pvConversionCompleteNotificationFunc();
			}

			/* Disable ADC Conversion Complete Interrupt */
			ADC_vidDisableInterrupt();
		}
		else if(Global_u8ADCISRSource == ADC_CHAIN_CHANNEL_ASYNC)
		{
			/* Check ADC bit resolution based on configuration to build its functions */
			#if    ADC_BIT_RESOLUTION == EIGHT_BIT_RESOLUTION
				/* Check if ADC result in ADC data registers (ADCH,ADCL) is left adjusted or not */
				#if   ADC_RESULT_ADJUSTMENT == RIGHT_ADJUSTMENT
				 	/* Get ADC Chain Reading */
					Global_pu16ADCChainResult[Global_u8ADCChainIndex] = ((u8)(ADCL>>2)|(u8)(ADCH<<6));
				#elif ADC_RESULT_ADJUSTMENT == LEFT_ADJUSTMENT
					/* Get ADC Chain Reading */
					Global_pu16ADCChainResult[Global_u8ADCChainIndex] = ADCH;
				#else
					#error "Wrong ADC Result Adjustment Configuration"
				#endif
			#elif  ADC_BIT_RESOLUTION == TEN_BIT_RESOLUTION
				/* Check if ADC result in ADC data registers (ADCH,ADCL) is left adjusted or not */
				#if   ADC_RESULT_ADJUSTMENT == RIGHT_ADJUSTMENT
					/* Get ADC Chain Reading */
					Global_pu16ADCChainResult[Global_u8ADCChainIndex] = ((u16)ADCL|(u16)(ADCH<<8));
				#elif ADC_RESULT_ADJUSTMENT == LEFT_ADJUSTMENT
					/* Get ADC Chain Reading */
					Global_pu16ADCChainResult[Global_u8ADCChainIndex] = ((u16)(ADCL>>6)|(u16)(ADCH<<2));
				#else
					#error "Wrong ADC Result Adjustment Configuration"
				#endif
			#else
				#error "Wrong Bit Resolution Configuration"
			#endif

			/* Increment Chain Index */
			Global_u8ADCChainIndex++;

			/* Check if Chain is finished or not */
			if(Global_u8ADCChainIndex == Global_u8ADCChainSize)
			{
				/* Chain is finished */

				/* Set ADC as Idle */
				Global_u8AdcStatus = ADC_IDLE;

				/* Check if ADC chain conversion complete notification callback function is registered or not */
				if(ADC_pvChainConversionCompleteNotificationFunc != NULL)
				{
					/* Invoke ADC chain conversion complete notification callback function*/
					ADC_pvChainConversionCompleteNotificationFunc();
				}

				/* Disable ADC Conversion Complete Interrupt */
				ADC_vidDisableInterrupt();

				/* Set Global_u8ADCChainIndex to 0 */
				Global_u8ADCChainIndex = 0;
			}
			else
			{
				/* Chain is not finished */

				/* Clear ADC Single Ended Channels Bits in ADMUX Register */
				ADMUX &= ADC_SINGLE_ENDED_CHANNELS_MASK;

				/* Select the ADC channel to read from */
				ADMUX |= Global_pu8ADCChainId[Global_u8ADCChainIndex];

				/* Start ADC Conversion */
				ADC_vidStartConversion();
			}
		}
	#elif (ADC_AUTO_TRIGGER == AUTO_TRIGGER_ENABLE && ADC_AUTO_TRIGGER_SOURCE == FREE_RUNNING)
		/* Check ADC bit resolution based on configuration to build its functions */
		#if    ADC_BIT_RESOLUTION == EIGHT_BIT_RESOLUTION
			/* Check if ADC result in ADC data registers (ADCH,ADCL) is left adjusted or not */
			#if   ADC_RESULT_ADJUSTMENT == RIGHT_ADJUSTMENT
				 /* Get ADC Reading */
				 *Global_pu16Reading = ((u8)(ADCL>>2)|(u8)(ADCH<<6));
			#elif ADC_RESULT_ADJUSTMENT == LEFT_ADJUSTMENT
				 /* Get ADC Reading */
				 *Global_pu16Reading = ADCH;
			#else
				#error "Wrong ADC Result Adjustment Configuration"
			#endif
		#elif  ADC_BIT_RESOLUTION == TEN_BIT_RESOLUTION
			/* Check if ADC result in ADC data registers (ADCH,ADCL) is left adjusted or not */
			#if   ADC_RESULT_ADJUSTMENT == RIGHT_ADJUSTMENT
				/* Get ADC Reading */
				*Global_pu16Reading = ((u16)ADCL|(u16)(ADCH<<8));
			#elif ADC_RESULT_ADJUSTMENT == LEFT_ADJUSTMENT
				/* Get ADC Reading */
				*Global_pu16Reading = ((u16)(ADCL>>6)|(u16)(ADCH<<2));
			#else
				#error "Wrong ADC Result Adjustment Configuration"
			#endif
		#else
			#error "Wrong Bit Resolution Configuration"
		#endif
		/* Check if ADC conversion complete notification callback function is registered or not */
		if(ADC_pvConversionCompleteNotificationFunc != NULL)
		{
			/* Invoke ADC conversion complete notification callback function */
			ADC_pvConversionCompleteNotificationFunc();
		}

		/* Disable ADC Conversion Complete Interrupt */
		ADC_vidDisableInterrupt();
	#endif
}
