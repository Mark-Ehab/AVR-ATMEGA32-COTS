/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Oct 11, 2021               	*/
/*              SWC              : EXTI				*/
/*              Description	 : EXTI Interface               */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_EXTI_INTERFACE_H_
#define MCAL_EXTI_INTERFACE_H_

				/* Interface Macros */
/*
 * Define new enum type for EXTI0 sense control signals which are :
 * 1) Generate EXTI0 request on Low Level of INT0
 * 2) Generate EXTI0 request on Any Logical Change of INT0
 * 3) Generate EXTI0 request on The Falling Edge of INT0
 * 4) Generate EXTI0 request on The Rising Edge of INT0
 */
typedef enum
{
	EXTI0_LOW_LEVEL   		= 0,
	EXTI0_ANY_LOGICAL_CHANGE  	= 1,
	EXTI0_FALLING_EDGE   		= 2,
	EXTI0_RISING_EDGE   		= 3
}EXTI_EXTI0SenseControl_e;


/*
 * Define new enum type for EXTI1 sense control signals which are :
 * 1) Generate EXTI1 request on Low Level of INT1
 * 2) Generate EXTI1 request on Any Logical Change of INT1
 * 3) Generate EXTI1 request on The Falling Edge of INT1
 * 4) Generate EXTI1 request on The Rising Edge of INT1
 */
typedef enum
{
	EXTI1_LOW_LEVEL   		= 0,
	EXTI1_ANY_LOGICAL_CHANGE  	= 1,
	EXTI1_FALLING_EDGE   		= 2,
	EXTI1_RISING_EDGE   		= 3
}EXTI_EXTI1SenseControl_e;


/*
 * Define new enum type for EXTI2 sense control signals which are :
 * 1) Generate EXTI2 request on The Falling Edge of INT2
 * 2) Generate EXTI2 request on The Rising Edge of INT2
 */
typedef enum
{
	EXTI2_FALLING_EDGE   		= 0,
	EXTI2_RISING_EDGE   		= 1
}EXTI_EXTI2SenseControl_e;


				/* Functions Prototypes */

/**********************************************************************************/
/* Description     : Initialize External Interrupt 0				  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void EXTI_vidEXTI0Init(void);
/**********************************************************************************/
/* Description     : Initialize External Interrupt 1				  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void EXTI_vidEXTI1Init(void);
/**********************************************************************************/
/* Description     : Initialize External Interrupt 2				  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void EXTI_vidEXTI2Init(void);
/**********************************************************************************/
/* Description     : Enable External Interrupt 0				  */
/* Input Arguments : void						          */
/* Return          : void        					          */
/**********************************************************************************/
void EXTI_vidEXTI0Enable(void);
/**********************************************************************************/
/* Description     : Enable External Interrupt 1				  */
/* Input Arguments : void						          */
/* Return          : void        					          */
/**********************************************************************************/
void EXTI_vidEXTI1Enable(void);
/**********************************************************************************/
/* Description     : Enable External Interrupt 2				  */
/* Input Arguments : void						          */
/* Return          : void        					          */
/**********************************************************************************/
void EXTI_vidEXTI2Enable(void);
/**********************************************************************************/
/* Description     : Disable External Interrupt 0				  */
/* Input Arguments : void						          */
/* Return          : void      						          */
/**********************************************************************************/
void EXTI_vidEXTI0Disable(void);
/**********************************************************************************/
/* Description     : Disable External Interrupt 1				  */
/* Input Arguments : void						          */
/* Return          : void      						          */
/**********************************************************************************/
void EXTI_vidEXTI1Disable(void);
/**********************************************************************************/
/* Description     : Disable External Interrupt 2				  */
/* Input Arguments : void						          */
/* Return          : void      						          */
/**********************************************************************************/
void EXTI_vidEXTI2Disable(void);
/**********************************************************************************/
/* Description     : Set sense control action based on which EXTI0 will be 	  */
/* 		     generated 						          */
/* Input Arguments : EXTI_EXTI0SenseControl_e Copy_SenseControl_e	          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 EXTI_u8SetEXTI0SenseControl(EXTI_EXTI0SenseControl_e Copy_SenseControl_e);
/**********************************************************************************/
/* Description     : Set sense control action based on which EXTI1 will be 	  */
/* 		     generated 						          */
/* Input Arguments : EXTI_EXTI1SenseControl_e Copy_SenseControl_e	          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 EXTI_u8SetEXTI1SenseControl(EXTI_EXTI1SenseControl_e Copy_SenseControl_e);
/**********************************************************************************/
/* Description     : Set sense control action based on which EXTI2 will be 	  */
/* 		     generated 						          */
/* Input Arguments : EXTI_EXTI2SenseControl_e Copy_SenseControl_e	          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 EXTI_u8SetEXTI2SenseControl(EXTI_EXTI2SenseControl_e Copy_SenseControl_e);
/**********************************************************************************/
/* Description     : Register application callback function that will be executed */
/*		     immediately once EXTI0 ISR is triggered			  */
/* Input Arguments : void(*Copy_pvEXTI0Func)(void)			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 EXTI_u8EXTI0SetCallback(void(*Copy_pvEXTI0Func)(void));
/**********************************************************************************/
/* Description     : Register application callback function that will be executed */
/*		     immediately once EXTI1 ISR is triggered			  */
/* Input Arguments : void(*Copy_pvEXTI1Func)(void)			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 EXTI_u8EXTI1SetCallback(void(*Copy_pvEXTI1Func)(void));
/**********************************************************************************/
/* Description     : Register application callback function that will be executed */
/*		     immediately once EXTI2 ISR is triggered			  */
/* Input Arguments : void(*Copy_pvEXTI2Func)(void)			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 EXTI_u8EXTI2SetCallback(void(*Copy_pvEXTI2Func)(void));

#endif /* MCAL_EXTI_INTERFACE_H_ */
