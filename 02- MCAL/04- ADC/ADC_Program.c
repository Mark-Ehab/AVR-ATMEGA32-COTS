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

/********************************* Defining Global Variables *********************************/

#if   ADC_BIT_RESOLUTION == EIGHT_BIT_RESOLUTION
	/* Global Pointer to u8 to Hold Memory Address of ADC Reading After Conversion Completes */
	static u8* Global_pu8Reading = NULL; /* Used in 8-bit Resolution */
#else
	/* Global Pointer to u16 to Hold Memory Address of ADC Reading After Conversion Completes */
	static u16* Global_pu16Reading = NULL; /* Used in 10-bit Resolution */
#endif


/********************************* Defining Pointer to Function for Callback *********************************/
static void(*ADC_pvConversionCompleteFunc)(void) = NULL;


/******************************************** Private Functions ********************************************/

/**********************************************************************************/
/* Description     : Start ADC conversion 			              	  */
/* Input Arguments : void							  */
/* Return          : void							  */
/**********************************************************************************/
static void ADC_vidStartConversion(void)
{
	SET_BIT(ADCSRA,ADC_ADSC);
}
/**********************************************************************************/
/* Description     : Enable ADC conversion complete interrupt                 	  */
/* Input Arguments : void							  */
/* Return          : void							  */
/**********************************************************************************/
static void ADC_vidEnableInterrupt(void)
{
	SET_BIT(ADCSRA,ADC_ADIE);
}
/**********************************************************************************/
/* Description     : Disable ADC conversion complete interrupt                 	  */
/* Input Arguments : void							  */
/* Return          : void							  */
/**********************************************************************************/
static void ADC_vidDisableInterrupt(void)
{
	CLR_BIT(ADCSRA,ADC_ADIE);
}

/******************************************** Public Functions ********************************************/

/**********************************************************************************/
/* Description     : Initialize ADC peripheral with the pre-bulid configurations  */
/*                   stated in config file                                        */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/  
void ADC_vidInit()
{
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


   /* Check if ADC result in ADC data registers (ADCH,ADCL) is left adjusted or not */
   #if   ADC_RESULT_ADJUSTMENT == RIGHT_ADJUSTMENT
	CLR_BIT(ADMUX,ADC_ADLAR);
   #elif ADC_RESULT_ADJUSTMENT == LEFT_ADJUSTMENT
	SET_BIT(ADMUX,ADC_ADLAR);
   #else
	#error "Wrong ADC Result Adjustment Configuration"
   #endif


   /* Check if ADC auto-trigger is enabled or not */
   #if   ADC_AUTO_TRIGGER == AUTO_TRIGGER_ENABLE

	/* Clear Auto-Trigger Source Selection Bits */
	SFIOR &= ADC_AUTO_TRIGGER_SOURCE_MASK

	/* Check Selected Auto Trigger Source */
	#if   ADC_AUTO_TRIGGER_SOURCE == FREE_RUNNING
		SFIOR |= ADC_FREE_RUNNING;
	#elif ADC_AUTO_TRIGGER_SOURCE == ANALOG_COMPARATOR
		SFIOR |= ADC_ANALOG_COMPARATOR;
	#elif ADC_AUTO_TRIGGER_SOURCE == EXTERNAL_INTERRUPT_REQUEST0
		SFIOR |= ADC_EXTI0;
	#elif ADC_AUTO_TRIGGER_SOURCE == TIMER0_COMPARE_MATCH
		SFIOR |= ADC_TIMER0_COMPARE_MATCH;
	#elif ADC_AUTO_TRIGGER_SOURCE == TIMER0_OVERFLOW
		SFIOR |= ADC_TIMER0_OVERFLOW;
	#elif ADC_AUTO_TRIGGER_SOURCE == TIMER_COMPARE_MATCH_B
		SFIOR |= ADC_TIMER_COMPARE_MATCH_B;
	#elif ADC_AUTO_TRIGGER_SOURCE == TIMER1_OVERFLOW
		SFIOR |= ADC_TIMER1_OVERFLOW;
	#elif ADC_AUTO_TRIGGER_SOURCE == TIMER1_CAPTURE_EVENT
		SFIOR |= ADC_TIMER1_CAPTURE_EVENT;
	#else
		#error "Wrong ADC Auto-Trigger Source Configuration"
	#endif
   #elif ADC_AUTO_TRIGGER == AUTO_TRIGGER_DISABLE
	/* Disable Auto-Trigger and Select ADC Single Conversion Mode */
	CLR_BIT(ADCSRA,ADC_ADATE);
   #else
	#error "Wrong ADC Auto-Trigger Configuration"
   #endif


   /* Clear ADC CLK Pre-Scaler Selection Bits*/
   ADCSRA &= ADC_CLK_MASK;
   /* Check selected ADC pre-scaler for CLK fed to ADC */
   #if   ADC_CLK == CLK_DIV_BY_2
   	   ADCSRA |= ADC_CLK_DIV_BY_2;
   #elif ADC_CLK == CLK_DIV_BY_4
   	   ADCSRA |= ADC_CLK_DIV_BY_4;
   #elif ADC_CLK == CLK_DIV_BY_8
   	   ADCSRA |= ADC_CLK_DIV_BY_8;
   #elif ADC_CLK == CLK_DIV_BY_16
   	   ADCSRA |= ADC_CLK_DIV_BY_16;
   #elif ADC_CLK == CLK_DIV_BY_32
   	   ADCSRA |= ADC_CLK_DIV_BY_32;
   #elif ADC_CLK == CLK_DIV_BY_64
   	   ADCSRA |= ADC_CLK_DIV_BY_64;
   #elif ADC_CLK == CLK_DIV_BY_128
   	   ADCSRA |= ADC_CLK_DIV_BY_128;
   #else
	#error "Wrong ADC Clock Pre-Scaler Configuration"
   #endif


   /* Disable ADC Conversion Complete Interrupt */
   ADC_vidDisableInterrupt();


   /* Enable ADC */
   SET_BIT(ADCSRA,ADC_ADEN);

}

/* Check ADC bit resolution based on configuration to build its functions */

#if  ADC_BIT_RESOLUTION == EIGHT_BIT_RESOLUTION

	/**********************************************************************************/
	/* Description     : This function starts ADC conversion through polling (busy-   */
	/*                   waiting) on ADIF flag in ADCSRA register			  */
	/* Input Arguments : u8 Copy_u8ChannelNum				          */
	/* Return          : u8 						          */
	/* Note            : This function used for 8-bit ADC resolution 		  */
	/**********************************************************************************/
	u8 ADC_u8GetAdcReadingSyncEightBit(u8 Copy_u8ChannelNum)
	{
	   /* Define local variable that holds the result of ADC reading */
	   u8 Local_u8Result ;

	   /* Clear ADC Single Ended Channels Bits in ADMUX Register */
	   ADMUX &= ADC_SINGLE_ENDED_CHANNELS_MASK;

	   /* Select the ADC channel to read from */
	   ADMUX |= Copy_u8ChannelNum;

	   /* Start ADC Conversion */
	   ADC_vidStartConversion();

	   /* Polling (busy waiting) over ADC Conversion Complete Interrupt Flag untill it's set to 1 */
	   while(GET_BIT(ADCSRA,ADC_ADIF) == 0);

	   /* Clear ADC Conversion Complete Interrupt Flag By Writing 1 to ADIF Bit */
	   SET_BIT(ADCSRA,ADC_ADIF);

	   /* Check ADC Result Adjustment */
	   #if ADC_RESULT_ADJUSTMENT == LEFT_ADJUSTMENT
		   /* Get ADC Reading */
		   Local_u8Result = ADCH;
	   #else
		   /* Get ADC Reading */
		   Local_u8Result = ((u8)(ADCL>>2)|(u8)(ADCH<<6));
	   #endif

	   return Local_u8Result;
	}
	/**********************************************************************************/
	/* Description     : This function starts ADC conversion and when conversion      */
	/*                   completes, the hardware generates an interrupt to get the    */
	/*                   ADC reading without busy-waiting the processor               */
	/* Input Arguments : u8 Copy_u8ChannelNum , u8 * Copy_pu8Reading,		  */
	/*                   void(*Copy_pvAdcFunc)(void)				  */
	/* Return          : void							  */
	/* Note            : This function used for 8-bit ADC resolution 		  */
	/**********************************************************************************/
	void ADC_vidGetAdcReadingAsyncEightBit(u8 Copy_u8ChannelNum , u8* Copy_pu8Reading , void(*Copy_pvAdcFunc)(void))
	{
	  /* Initialize the global ADC reading pointer that will hold the address of ADC reading after conversion completes */
	  Global_pu8Reading = Copy_pu8Reading;

	  /* Register the callback function to be called in ISR after ADC conversion completes */
	  ADC_pvConversionCompleteFunc = Copy_pvAdcFunc;

	  /* Clear ADC Single Ended Channels Bits in ADMUX Register */
	  ADMUX &= ADC_SINGLE_ENDED_CHANNELS_MASK;

	  /* Select the ADC channel to read from */
	  ADMUX |= Copy_u8ChannelNum;

	  /* Enable ADC Conversion Complete Interrupt */
	  ADC_vidEnableInterrupt();

	  /* Start ADC Conversion */
	  ADC_vidStartConversion();

	}
#else
	/**********************************************************************************/
	/* Description     : This function starts ADC conversion through polling (busy-   */
	/*                   waiting) on ADIF flag in ADCSRA register			  */
	/* Input Arguments : u8 Copy_u8ChannelNum				          */
	/* Return          : u16						          */
	/* Note            : This function used for 10-bit ADC resolution 		  */
	/**********************************************************************************/
	u16 ADC_u16GetAdcReadingSyncTenBit(u8 Copy_u8ChannelNum)
	{
	  /* Define local variable that holds the result of ADC reading */
	  u8 Local_u16Result ;

	  /* Clear ADC Single Ended Channels Bits in ADMUX Register */
	  ADMUX &= ADC_SINGLE_ENDED_CHANNELS_MASK;

	  /* Select the ADC channel to read from */
	  ADMUX |= Copy_u8ChannelNum;

	  /* Start ADC Conversion */
	  ADC_vidStartConversion();

	  /* Polling (busy waiting) over ADC Conversion Complete Interrupt Flag untill it's set to 1 */
	  while(GET_BIT(ADCSRA,ADC_ADIF) == 0);

	  /* Clear ADC Conversion Complete Interrupt Flag By Writing 1 to ADIF Bit */
	  SET_BIT(ADCSRA,ADC_ADIF);

	  /* Check ADC Result Adjustment */
	  #if ADC_RESULT_ADJUSTMENT == LEFT_ADJUSTMENT
	 	   /* Get ADC Reading */
	 	   Local_u16Result = ((u16)(ADCH<<2)|(u16)(ADCL>>6));
	  #else
	 	   /* Get ADC Reading */
	 	   Local_u16Result = ((u16)(ADCH<<8)|(u16)ADCL);
	  #endif

	  return Local_u16Result;
	}
	/**********************************************************************************/
	/* Description     : This function starts ADC conversion and when conversion      */
	/*                   completes, the hardware generates an interrupt to get the    */
	/*                   ADC reading without busy-waiting the processor               */
	/* Input Arguments : u8 Copy_u8ChannelNum , u16 * Copy_pu16Reading,		  */
	/*                   void(*Copy_pvAdcFunc)(void)				  */
	/* Return          : void							  */
	/* Note            : This function used for 10-bit ADC resolution 		  */
	/**********************************************************************************/
	void ADC_vidGetAdcReadingAsyncTenBit(u8 Copy_u8ChannelNum , u16* Copy_pu16Reading, void(*Copy_pvAdcFunc)(void))
	{
	  /* Initialize the global ADC reading pointer that will hold the address of ADC reading after conversion completes */
	  Global_pu16Reading = Copy_pu16Reading;

	  /* Register the callback function to be called in ISR after ADC conversion completes */
	  ADC_pvConversionCompleteFunc = Copy_pvAdcFunc;

	  /* Clear ADC Single Ended Channels Bits in ADMUX Register */
	  ADMUX &= ADC_SINGLE_ENDED_CHANNELS_MASK;

	  /* Select the ADC channel to read from */
	  ADMUX |= Copy_u8ChannelNum;

	  /* Enable ADC Conversion Complete Interrupt */
	  ADC_vidEnableInterrupt();

	  /* Start ADC Conversion */
	  ADC_vidStartConversion();
	}

#endif

/******************************************** Interrupt Handlers ********************************************/

/* ADC Conversion Complete Interrupt */
void __vector_16 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_16 (void)
{
	#if   ADC_BIT_RESOLUTION == EIGHT_BIT_RESOLUTION
		#if ADC_RESULT_ADJUSTMENT == LEFT_ADJUSTMENT
			/* Get ADC Reading */
			*Global_pu8Reading = ADCH;
		#else
			  /* Get ADC Reading */
			*Global_pu8Reading = ((u8)(ADCL>>2)|(u8)(ADCH<<6));
		#endif
	#else
		#if ADC_RESULT_ADJUSTMENT == LEFT_ADJUSTMENT
			/* Get ADC Reading */
			*Global_pu16Reading = ((u16)(ADCH<<2)|(u16)(ADCL>>6));
		#else
		        /* Get ADC Reading */
			*Global_pu16Reading = ((u16)(ADCH<<8)|(u16)ADCL);
		#endif
	#endif

	/* Check if callback function is registered or not */
	if(ADC_pvConversionCompleteFunc != NULL)
	{
		ADC_pvConversionCompleteFunc();
	}

	/* Disable ADC Conversion Complete Interrupt */
	ADC_vidDisableInterrupt();
}
