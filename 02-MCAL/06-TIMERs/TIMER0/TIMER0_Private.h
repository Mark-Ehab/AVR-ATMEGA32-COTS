/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Feb 4, 2022               	*/
/*              SWC              : TIMER0			*/
/*              Description	 : TIMER0 Private               */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_TIMER0_PRIVATE_H_
#define MCAL_TIMER0_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           TIMER0 REGISTERS DEFINITIONS		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

#define TIMSK                                                        *((volatile u8*)0x59) /* Timer/Counter Interrupt Mask Register */
#define TIFR                                                         *((volatile u8*)0x58) /* Timer/Counter Interrupt Flag Register */
#define TCCR0                                                        *((volatile u8*)0x53) /* Timer/Counter Control Register 0 */
#define TCNT0                                                        *((volatile u8*)0x52) /* Timer/Counter Register 0 */
#define OCR0                                                         *((volatile u8*)0x5C) /* Output Compare Register 0 */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	   PRIVATE MACROS				     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Define Timer0 Overflow Ticks */
#define TIMER0_OVERFLOW_TICKS		                             255 /* Maximum Number of Timer Ticks to Reach Overflow and Calculated Based on Timer Resolution (8 bits in case of Timer0) */


/* Mask of Timer0 Waveform Generation Bits */
#define TIMER0_WAVEFORM_GENERATION_MASK                              0b10110111


/* Define Timer0 Operating Modes */
#define TIMER0_OVERFLOW_MODE				             0b00000000 /* Normal (Overflow) Mode */
#define TIMER0_PHASE_CORRECT_PWM_MODE                                0b01000000 /* PWM, Phase Correct Mode */
#define TIMER0_CTC_MODE		                                     0b00001000 /* CTC (Clear Timer on Compare Match) Mode */
#define TIMER0_FAST_PWM_MODE                                         0b01001000 /* Fast PWM Mode */


/* Mask of Timer0 Output Compare Match Pin Mode Bits */
#define TIMER0_OUTPUT_COMPARE_PIN_MODE_MASK                          0b11001111


/* Define Timer0 Output Compare Match Pin Modes (Non PWM)  */
#define TIMER0_NON_PWM_OUTPUT_COMPARE_PIN_DISCONNECTED               0b00000000 /* Timer0 Output Compare Match Pin is Disconnect */
#define TIMER0_NON_PWM_OUTPUT_COMPARE_PIN_TOGGLE                     0b00010000 /* Timer0 Output Compare Match Pin is Toggled */
#define TIMER0_NON_PWM_OUTPUT_COMPARE_PIN_CLEAR                      0b00100000 /* Timer0 Output Compare Match Pin is Cleared */
#define TIMER0_NON_PWM_OUTPUT_COMPARE_PIN_SET                        0b00110000 /* Timer0 Output Compare Match Pin is Set */


/* Define Timer0 Output Compare Match Pin Modes (Fast PWM)  */
#define TIMER0_FAST_PWM_OUTPUT_COMPARE_PIN_DISCONNECTED		     0b00000000 /* Timer0 Output Compare Match Pin is Disconnect */
#define TIMER0_FAST_PWM_OUTPUT_COMPARE_PIN_NON_INVERTED_MODE         0b00100000 /* Clear OC0 on compare match, set OC0 at TOP */
#define TIMER0_FAST_PWM_OUTPUT_COMPARE_PIN_INVERTED_MODE             0b00110000 /* Set OC0 on compare match, clear OC0 at TOP */


/* Define Timer0 Output Compare Match Pin Modes (Phase-Correct PWM)  */
#define TIMER0_PHASE_CORRECT_PWM_OUTPUT_COMPARE_DISCONNECTED         0b00000000 /* Timer0 Output Compare Match Pin is Disconnect */
#define TIMER0_PHASE_CORRECT_PWM_OUTPUT_COMPARE_NON_INVERTED_MODE    0b00100000 /* Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting */
#define TIMER0_PHASE_CORRECT_PWM_OUTPUT_COMPARE_INVERTED_MODE        0b00110000 /* Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting */


/* Some Bits Definitions of Timer/Counter Interrupt Mask Register (TIMSK) */
#define TIMER0_TOIE0 						     0 /* Timer/Counter0 Overflow Interrupt Enable */
#define TIMER0_OCIE0						     1 /* Timer/Counter0 Output Compare Match Interrupt Enable */


/* Some Bits Definitions of Timer/Counter Interrupt Flag Register (TIFR) */
#define TIMER0_TOV0 						     0 /* Timer/Counter0 Overflow Flag */
#define TIMER0_OCF0						     1 /* Output Compare Flag 0 */


/* Mask of Timer0 Clock Selection Bits */
#define TIMER0_CLK_MASK						     0b11111000


/* Timer0 Prescaler Selections */
#define TIMER0_CLK_DIV_BY_NO_PRESCALER				     0b00000001 /* clkI/O/(No prescaling) */
#define TIMER0_CLK_DIV_BY_8					     0b00000010 /* clkI/O/8 (From prescaler) */
#define TIMER0_CLK_DIV_BY_64					     0b00000011 /* clkI/O/64 (From prescaler) */
#define TIMER0_CLK_DIV_BY_256					     0b00000100 /* clkI/O/256 (From prescaler) */
#define TIMER0_CLK_DIV_BY_1024					     0b00000101 /* clkI/O/1024 (From prescaler) */
#define TIMER0_EXT_CLK_FALLING_EDGE				     0b00000110 /* External clock source on T0 pin. Clock on falling edge */
#define TIMER0_EXT_CLK_RISING_EDGE			       	     0b00000111 /* External clock source on T0 pin. Clock on rising edge */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           CONFIGURATION OPTIONS VALUES		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Timer0 Operating Modes Options */
#define OVERFLOW_MODE		                                     1
#define PHASE_CORRECT_PWM_MODE                                       2
#define CTC_MODE		                                     3
#define FAST_PWM_MODE                                                4


/* Output Compare Match Pin Modes Options (Non PWM) */
#define DISCONNECTED					             0
#define TOGGLE	                                                     1
#define CLEAR	                                                     2
#define SET	                                                     3


/* Output Compare Match Pin Modes Options (Phase Correct & Fast PWM) */
#define NON_INVERTED_MODE                                            1
#define INVERTED_MODE                                                2


/* Enable/Disable signals for both Overflow and Compare Match Interrupts of Timer0 */
#define ENABLE                                                       1
#define DISABLE                                                      2


/* Timer0 Pre-scaler Options */
#define CLK_DIV_BY_NO_PRESCALER	                                     1
#define CLK_DIV_BY_8	                                             8
#define CLK_DIV_BY_64		                                     64
#define CLK_DIV_BY_256      	                                     256
#define CLK_DIV_BY_1024                                              1024
#define EXT_CLK_FALLING_EDGE	                                     2
#define EXT_CLK_RISING_EDGE				             3

#endif /* MCAL_TIMER0_PRIVATE_H_ */
