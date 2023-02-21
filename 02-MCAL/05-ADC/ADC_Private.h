/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Oct 15, 2021               	*/
/*              SWC              : ADC				*/
/*              Description	 : ADC Private                  */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_ADC_PRIVATE_H_
#define MCAL_ADC_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                              ADC REGISTERS DEFINITIONS		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

#define ADMUX	                             *((volatile u8*)0x27) /* ADC Multiplexer Selection Register */
#define ADCSRA	                             *((volatile u8*)0x26) /* ADC Control and Status Register A */
#define ADCH	                             *((volatile u8*)0x25) /* ADC Data High Register */
#define ADCL	                             *((volatile u8*)0x24) /* ADC Data Low Register */
#define SFIOR	                             *((volatile u8*)0x50) /* Special FunctionIO Register */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                              SOME BITS DEFINITIONS		 	             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Some bit definitions of ADC Multiplexer Selection Register (ADMUX) */
#define ADMUX_ADLAR                            5 /* ADC Left Adjust Result */


/* Some bit definitions of ADC Control and Status Register A (ADCSRA) */
#define ADCSRA_ADIE                             3 /* ADC Interrupt Enable */
#define ADCSRA_ADIF                             4 /* ADC Interrupt Flag */
#define ADCSRA_ADATE                            5 /* ADC Auto-Trigger Enable */
#define ADCSRA_ADSC                             6 /* ADC Start Conversion */
#define ADCSRA_ADEN                             7 /* ADC Enable */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	   PRIVATE MACROS				     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Definition of ADC Single Ended Channels Mask */
#define ADC_SINGLE_ENDED_CHANNELS_MASK       0b11100000


/* ADC Reference Voltage Modes */
#define ADC_AREF                             0b00000000 /* AREF, Internal Vref turned off */
#define ADC_AVCC                             0b01000000 /* AVCC with external capacitor at AREF pin */
#define ADC_INTERNAL_VOLT                    0b11000000 /* Internal 2.56V Voltage Reference with external capacitor at AREF pin */
#define ADC_REF_VOLT_MASK                    0b00111111 /* Mask of ADC Reference Voltage */


/* ADC CLK Pre-scaler Selections */
#define ADC_CLK_DIV_BY_2                     0b00000000 /* CLK/2 */
#define ADC_CLK_DIV_BY_4                     0b00000010 /* CLK/4 */
#define ADC_CLK_DIV_BY_8                     0b00000011 /* CLK/8 */
#define ADC_CLK_DIV_BY_16                    0b00000100 /* CLK/16 */
#define ADC_CLK_DIV_BY_32                    0b00000101 /* CLK/32 */
#define ADC_CLK_DIV_BY_64                    0b00000110 /* CLK/64 */
#define ADC_CLK_DIV_BY_128                   0b00000111 /* CLK/128 */
#define ADC_CLK_MASK 	                     0b11111000 /* Mask of ADC CLK */


/* ADC Auto-Trigger Source Selection */
#define ADC_FREE_RUNNING                     0b00000000 /* Free Running mode */
#define ADC_ANALOG_COMPARATOR                0b00100000 /* Analog Comparator */
#define ADC_EXTI0                            0b01000000 /* External Interrupt Request 0 */
#define ADC_TIMER0_COMPARE_MATCH             0b01100000 /* Timer/Counter0 Compare Match */
#define ADC_TIMER0_OVERFLOW                  0b10000000 /* Timer/Counter0 Overflow */
#define ADC_TIMER_COMPARE_MATCH_B            0b10100000 /* Timer/Counter Compare Match B */
#define ADC_TIMER1_OVERFLOW                  0b11000000 /* Timer/Counter1 Overflow */
#define ADC_TIMER1_CAPTURE_EVENT             0b11100000 /* Timer/Counter1 Capture Event */
#define ADC_AUTO_TRIGGER_SOURCE_MASK         0b00011111 /* Mask of Auto-Trigger Source */


/* ADC Status Options */
#define ADC_IDLE                             0 /* Status tells that ADC peripheral is available to start conversion */
#define ADC_BUSY                             1 /* Status tells that ADC peripheral is busy and not available to start conversion */


/* ADC Complete ISR Source */
#define ADC_SINGLE_CHANNEL_ASYNC             0 /* Tells that ADC Conversion Complete ISR source is from a single channel */
#define ADC_CHAIN_CHANNEL_ASYNC              1 /* Tells that ADC Conversion Complete ISR source is from a chain of channels */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           CONFIGURATION OPTIONS VALUES		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Reference Voltage Options */
#define AREF                                 1
#define AVCC                                 2
#define INTERNAL_VOLT                        3


/* ADC Result Adjustment Modes */
#define RIGHT_ADJUSTMENT                     1
#define LEFT_ADJUSTMENT                      2


/* Enable/Disable Auto-Trigger Options */
#define AUTO_TRIGGER_ENABLE                  1
#define AUTO_TRIGGER_DISABLE                 2


/* Auto-Trigger Source Options */
#define FREE_RUNNING                         1
#define ANALOG_COMPARATOR                    2
#define EXTERNAL_INTERRUPT_REQUEST0          3
#define TIMER0_COMPARE_MATCH                 4
#define TIMER0_OVERFLOW                      5
#define TIMER_COMPARE_MATCH_B                6
#define TIMER1_OVERFLOW                      7
#define TIMER1_CAPTURE_EVENT                 8


/* Auto-Trigger Channel Options */
#define CH_0                                 0
#define CH_1                                 1
#define CH_2                                 2
#define CH_3                                 3
#define CH_4                                 4
#define CH_5                                 5
#define CH_6                                 6
#define CH_7                                 7


/* ADC CLK Pre-scaler Options */
#define CLK_DIV_BY_2                         1
#define CLK_DIV_BY_4                         2
#define CLK_DIV_BY_8                         3
#define CLK_DIV_BY_16                        4
#define CLK_DIV_BY_32                        5
#define CLK_DIV_BY_64                        6
#define CLK_DIV_BY_128                       7


/* ADC Bit Resolution Options */
#define EIGHT_BIT_RESOLUTION                 1
#define TEN_BIT_RESOLUTION	             2

#endif /*MCAL_ADC_PRIVATE_H_*/
