/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Oct 11, 2021               	*/
/*              SWC              : EXTI				*/
/*              Description	 : EXTI Private                 */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_EXTI_PRIVATE_H_
#define MCAL_EXTI_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             EXTI REGISTERS DEFINITIONS		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

#define GICR 	                                   *((volatile u8*)0x5B) /* General Interrupt Control Register */
#define GIFR 	                                   *((volatile u8*)0x5A) /* General Interrupt Flag Register */
#define MCUCR 	                                   *((volatile u8*)0x55) /* MCU Control Register */
#define MCUCSR	                                   *((volatile u8*)0x54) /* MCU Control and Status Register */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                              SOME BITS DEFINITIONS		 	             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Bit Definitions of General Interrupt Control Register (GICR) */
#define GICR_INT2			       	   5 /* External Interrupt Request 2 Enable */
#define GICR_INT0			           6 /* External Interrupt Request 0 Enable */
#define GICR_INT1				   7 /* External Interrupt Request 1 Enable */


/* Bit Definitions of General Interrupt Flag Register (GIFR) */
#define GIFR_INTF2			       	   5 /* External Interrupt Flag 2 */
#define GIFR_INTF0			           6 /* External Interrupt Flag 0 */
#define GIFR_INTF1				   7 /* External Interrupt Flag 1 */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	   PRIVATE MACROS				     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* EXTI0 Sense Controls Values */
#define EXTI_EXTI0_SENSE_CONTROL_MASK		   0b11111100 /*  Mask of EXTI0 Sense Control Bits  */
#define EXTI_EXTI0_LOW_LEVEL                       0b00000000 /* Generate EXTI0 request on Low Level of INT0 */
#define EXTI_EXTI0_ANY_LOGICAL_CHANGE              0b00000001 /* Generate EXTI0 request on Any Logical Change of INT0 */
#define EXTI_EXTI0_FALLING_EDGE                    0b00000010 /* Generate EXTI0 request on The Falling Edge of INT0 */
#define EXTI_EXTI0_RISING_EDGE                     0b00000011 /* Generate EXTI0 request on The Rising Edge of INT0 */


/* EXTI1 Sense Controls Values */
#define EXTI_EXTI1_SENSE_CONTROL_MASK	           0b11110011 /*  Mask of EXTI1 Sense Control Bits  */
#define EXTI_EXTI1_LOW_LEVEL                       0b00000000 /* Generate EXTI1 request on Low Level of INT1 */
#define EXTI_EXTI1_ANY_LOGICAL_CHANGE              0b00000100 /* Generate EXTI1 request on Any Logical Change of INT1 */
#define EXTI_EXTI1_FALLING_EDGE                    0b00001000 /* Generate EXTI1 request on The Falling Edge of INT1 */
#define EXTI_EXTI1_RISING_EDGE                     0b00001100 /* Generate EXTI1 request on The Rising Edge of INT1 */


/* EXTI2 Sense Controls Values */
#define EXTI_EXTI2_SENSE_CONTROL_MASK		   0b10111111 /*  Mask of EXTI2 Sense Control Bits  */
#define EXTI_EXTI2_FALLING_EDGE			   0b00000000 /* Generate EXTI2 request on The Falling Edge of INT2 */
#define EXTI_EXTI2_RISING_EDGE 			   0b01000000 /* Generate EXTI2 request on The Rising Edge of INT2 */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           CONFIGURATION OPTIONS VALUES		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* EXTI Interrupt Sense Control Actions Options */
#define LOW_LEVEL                                  0
#define ANY_LOGICAL_CHANGE	                   1
#define FALLING_EDGE		                   2
#define RISING_EDGE		                   3


/* EXTI Enable Signals */
#define ENABLE					   0
#define DISABLE					   1

#endif /* MCAL_EXTI_PRIVATE_H_ */
