/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Oct 11, 2021               	*/
/*              SWC              : EXTI				*/
/*              Description	 : EXTI Program                 */
/* 	        Version          : V1.0                         */
/****************************************************************/

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/STD_ERRORS.h"

#include "EXTI_Interface.h"
#include "EXTI_Private.h"
#include "EXTI_Config.h"

/* Define Some Global Variables */
static void(*EXTI_pvEXTI0Func)(void) = NULL; /* Global Pointer To Function That Holds Address of EXTI0 ISR Application Specific Function */
static void(*EXTI_pvEXTI1Func)(void) = NULL; /* Global Pointer To Function That Holds Address of EXTI1 ISR Application Specific Function */
static void(*EXTI_pvEXTI2Func)(void) = NULL; /* Global Pointer To Function That Holds Address of EXTI2 ISR Application Specific Function */

/**********************************************************************************/
/* Description     : Initialize External Interrupt 0				  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void EXTI_vidEXTI0Init(void)
{
	/* Define Some Local Variables */
	u8 Local_u8MCUCRTemp; /* Temporary Variable to Hold Current MCUCR Register Value */

	/* Read Current Value of MCUCR Register then Assign it to Local_u8MCUCRTemp */
	Local_u8MCUCRTemp = MCUCR;

	/* Check EXTI0 Interrupt Sense Control Action Based on Configurations from Config File */
	#if   EXTI_EXTI0_SENSE_CONTROL == LOW_LEVEL
	      /* Clear EXTI0 Interrupt Sense Control Bits in MCUCR Register Value Assigned to Local_u8MCUCRTemp */
	      Local_u8MCUCRTemp &= EXTI_EXTI0_SENSE_CONTROL_MASK;
	      /* Modify EXTI0 Interrupt Sense Control Bits of MCUCR Register Value Assigned to Local_u8MCUCRTemp to be Low Level */
	      Local_u8MCUCRTemp |= EXTI_EXTI0_LOW_LEVEL;
	#elif EXTI_EXTI0_SENSE_CONTROL == ANY_LOGICAL_CHANGE
	      /* Clear EXTI0 Interrupt Sense Control Bits in MCUCR Register Value Assigned to Local_u8MCUCRTemp */
	      Local_u8MCUCRTemp &= EXTI_EXTI0_SENSE_CONTROL_MASK;
	      /* Modify EXTI0 Interrupt Sense Control Bits of MCUCR Register Value Assigned to Local_u8MCUCRTemp to be Any Logical Change */
	      Local_u8MCUCRTemp |= EXTI_EXTI0_ANY_LOGICAL_CHANGE;
	#elif EXTI_EXTI0_SENSE_CONTROL == FALLING_EDGE
	      /* Clear EXTI0 Interrupt Sense Control Bits in MCUCR Register Value Assigned to Local_u8MCUCRTemp */
	      Local_u8MCUCRTemp &= EXTI_EXTI0_SENSE_CONTROL_MASK;
	      /* Modify EXTI0 Interrupt Sense Control Bits of MCUCR Register Value Assigned to Local_u8MCUCRTemp to be Falling Edge */
	      Local_u8MCUCRTemp |= EXTI_EXTI0_FALLING_EDGE;
	#elif EXTI_EXTI0_SENSE_CONTROL == RISING_EDGE
	      /* Clear EXTI0 Interrupt Sense Control Bits in MCUCR Register Value Assigned to Local_u8MCUCRTemp */
	      Local_u8MCUCRTemp &= EXTI_EXTI0_SENSE_CONTROL_MASK;
	      /* Modify EXTI0 Interrupt Sense Control Bits of MCUCR Register Value Assigned to Local_u8MCUCRTemp to be Rising Edge */
	      Local_u8MCUCRTemp |= EXTI_EXTI0_RISING_EDGE;
	#else
		#error " Wrong External Interrupt 0 Interrupt Sense Control Action Configuration "
	#endif

	/* Write Modified Value of Local_u8MCUCRTemp Back Again to MCUCR Register */
	MCUCR = Local_u8MCUCRTemp;


	/* Check EXTI0 Enable Signal Whether its Enable or Disable */
	#if   EXTI_EXTI0_ENABLE == ENABLE
	      /* Enable EXTI0 */
	      SET_BIT(GICR,EXTI_INT0);
	#elif EXTI_EXTI0_ENABLE == DISABLE
	      /* Disable EXTI0 */
	      CLR_BIT(GICR,EXTI_INT0);
	#else
		#error " Wrong External Interrupt 0 Enable Signal Configuration"
	#endif
}
/**********************************************************************************/
/* Description     : Initialize External Interrupt 1				  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void EXTI_vidEXTI1Init(void)
{
	/* Define Some Local Variables */
        u8 Local_u8MCUCRTemp; /* Temporary Variable to Hold Current MCUCR Register Value */

        /* Read Current Value of MCUCR Register then Assign it to Local_u8MCUCRTemp */
        Local_u8MCUCRTemp = MCUCR;

        /* Check EXTI1 Interrupt Sense Control Action Based on Configurations from Config File */
        #if   EXTI_EXTI1_SENSE_CONTROL == LOW_LEVEL
              /* Clear EXTI1 Interrupt Sense Control Bits in MCUCR Register Value Assigned to Local_u8MCUCRTemp */
              Local_u8MCUCRTemp &= EXTI_EXTI1_SENSE_CONTROL_MASK;
              /* Modify EXTI1 Interrupt Sense Control Bits of MCUCR Register Value Assigned to Local_u8MCUCRTemp to be Low Level */
              Local_u8MCUCRTemp |= EXTI_EXTI1_LOW_LEVEL;
        #elif EXTI_EXTI1_SENSE_CONTROL == ANY_LOGICAL_CHANGE
              /* Clear EXTI1 Interrupt Sense Control Bits in MCUCR Register Value Assigned to Local_u8MCUCRTemp */
              Local_u8MCUCRTemp &= EXTI_EXTI1_SENSE_CONTROL_MASK;
              /* Modify EXTI1 Interrupt Sense Control Bits of MCUCR Register Value Assigned to Local_u8MCUCRTemp to be Any Logical Change */
              Local_u8MCUCRTemp |= EXTI_EXTI1_ANY_LOGICAL_CHANGE;
        #elif EXTI_EXTI1_SENSE_CONTROL == FALLING_EDGE
              /* Clear EXTI1 Interrupt Sense Control Bits in MCUCR Register Value Assigned to Local_u8MCUCRTemp */
              Local_u8MCUCRTemp &= EXTI_EXTI1_SENSE_CONTROL_MASK;
              /* Modify EXTI1 Interrupt Sense Control Bits of MCUCR Register Value Assigned to Local_u8MCUCRTemp to be Falling Edge */
              Local_u8MCUCRTemp |= EXTI_EXTI1_FALLING_EDGE;
        #elif EXTI_EXTI1_SENSE_CONTROL == RISING_EDGE
              /* Clear EXTI1 Interrupt Sense Control Bits in MCUCR Register Value Assigned to Local_u8MCUCRTemp */
              Local_u8MCUCRTemp &= EXTI_EXTI1_SENSE_CONTROL_MASK;
              /* Modify EXTI1 Interrupt Sense Control Bits of MCUCR Register Value Assigned to Local_u8MCUCRTemp to be Rising Edge */
              Local_u8MCUCRTemp |= EXTI_EXTI1_RISING_EDGE;
        #else
        	#error " Wrong External Interrupt 1 Interrupt Sense Control Action Configuration "
        #endif

        /* Write Modified Value of Local_u8MCUCRTemp Back Again to MCUCR Register */
        MCUCR = Local_u8MCUCRTemp;


        /* Check EXTI1 Enable Signal Whether its Enable or Disable */
        #if   EXTI_EXTI1_ENABLE == ENABLE
              /* Enable EXTI1 */
              SET_BIT(GICR,EXTI_INT1);
        #elif EXTI_EXTI1_ENABLE == DISABLE
              /* Disable EXTI1 */
              CLR_BIT(GICR,EXTI_INT1);
        #else
        	#error " Wrong External Interrupt 1 Enable Signal Configuration"
        #endif
}
/**********************************************************************************/
/* Description     : Initialize External Interrupt 2				  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void EXTI_vidEXTI2Init(void)
{
	/* Define Some Local Variables */
        u8 Local_u8MCUCRTemp; /* Temporary Variable to Hold Current MCUCR Register Value */

        /* Read Current Value of MCUCR Register then Assign it to Local_u8MCUCRTemp */
        Local_u8MCUCRTemp = MCUCR;

        /* Check EXTI2 Interrupt Sense Control Action Based on Configurations from Config File */
        #if EXTI_EXTI2_SENSE_CONTROL == FALLING_EDGE
              /* Clear EXTI2 Interrupt Sense Control Bits in MCUCR Register Value Assigned to Local_u8MCUCRTemp */
              Local_u8MCUCRTemp &= EXTI_EXTI2_SENSE_CONTROL_MASK;
              /* Modify EXTI2 Interrupt Sense Control Bits of MCUCR Register Value Assigned to Local_u8MCUCRTemp to be Falling Edge */
              Local_u8MCUCRTemp |= EXTI_EXTI2_FALLING_EDGE;
        #elif EXTI_EXTI2_SENSE_CONTROL == RISING_EDGE
              /* Clear EXTI2 Interrupt Sense Control Bits in MCUCR Register Value Assigned to Local_u8MCUCRTemp */
              Local_u8MCUCRTemp &= EXTI_EXTI2_SENSE_CONTROL_MASK;
              /* Modify EXTI2 Interrupt Sense Control Bits of MCUCR Register Value Assigned to Local_u8MCUCRTemp to be Rising Edge */
              Local_u8MCUCRTemp |= EXTI_EXTI2_RISING_EDGE;
        #else
        	#error " Wrong External Interrupt 2 Interrupt Sense Control Action Configuration "
        #endif

        /* Write Modified Value of Local_u8MCUCRTemp Back Again to MCUCR Register */
        MCUCR = Local_u8MCUCRTemp;


        /* Check EXTI2 Enable Signal Whether its Enable or Disable */
        #if   EXTI_EXTI2_ENABLE == ENABLE
              /* Enable EXTI2 */
              SET_BIT(GICR,EXTI_INT2);
        #elif EXTI_EXTI2_ENABLE == DISABLE
              /* Disable EXTI2 */
              CLR_BIT(GICR,EXTI_INT2);
        #else
        	#error " Wrong External Interrupt 2 Enable Signal Configuration"
        #endif
}
/**********************************************************************************/
/* Description     : Enable External Interrupt 0				  */
/* Input Arguments : void						          */
/* Return          : void        					          */
/**********************************************************************************/
void EXTI_vidEXTI0Enable(void)
{
	/* Enable EXTI0 */
	SET_BIT(GICR,EXTI_INT0);
}
/**********************************************************************************/
/* Description     : Enable External Interrupt 1				  */
/* Input Arguments : void						          */
/* Return          : void        					          */
/**********************************************************************************/
void EXTI_vidEXTI1Enable(void)
{
	/* Enable EXTI1 */
	SET_BIT(GICR,EXTI_INT1);
}
/**********************************************************************************/
/* Description     : Enable External Interrupt 2				  */
/* Input Arguments : void						          */
/* Return          : void        					          */
/**********************************************************************************/
void EXTI_vidEXTI2Enable(void)
{
	/* Enable EXTI2 */
	SET_BIT(GICR,EXTI_INT2);
}
/**********************************************************************************/
/* Description     : Disable External Interrupt 0				  */
/* Input Arguments : void						          */
/* Return          : void      						          */
/**********************************************************************************/
void EXTI_vidEXTI0Disable(void)
{
	/* Disable EXTI0 */
	CLR_BIT(GICR,EXTI_INT0);
}
/**********************************************************************************/
/* Description     : Disable External Interrupt 1				  */
/* Input Arguments : void						          */
/* Return          : void      						          */
/**********************************************************************************/
void EXTI_vidEXTI1Disable(void)
{
	/* Disable EXTI1 */
	CLR_BIT(GICR,EXTI_INT1);
}
/**********************************************************************************/
/* Description     : Disable External Interrupt 2				  */
/* Input Arguments : void						          */
/* Return          : void      						          */
/**********************************************************************************/
void EXTI_vidEXTI2Disable(void)
{
	/* Disable EXTI2 */
        CLR_BIT(GICR,EXTI_INT2);
}
/**********************************************************************************/
/* Description     : Set sense control action based on which EXTI0 will be 	  */
/* 		     generated 						          */
/* Input Arguments : EXTI_EXTI0SenseControl_e Copy_SenseControl_e	          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 EXTI_u8SetEXTI0SenseControl(EXTI_EXTI0SenseControl_e Copy_SenseControl_e)
{
	/* Define Some Local Variables */
	u8 Local_u8ErrorStatus = RT_OK; 	/* Variable to hold the function status whether it's ok or not ok */
	u8 Local_u8MCUCRTemp; 			/* Temporary Variable to Hold Current MCUCR Register Value */

	/* Check if passed EXTI0 interrupt sense control action is valid or not */
	if(Copy_SenseControl_e == EXTI0_LOW_LEVEL || Copy_SenseControl_e == EXTI0_ANY_LOGICAL_CHANGE ||
	   Copy_SenseControl_e == EXTI0_FALLING_EDGE || Copy_SenseControl_e == EXTI0_RISING_EDGE)
	{
		/* Read Current Value of MCUCR Register then Assign it to Local_u8MCUCRTemp */
		Local_u8MCUCRTemp = MCUCR;

		/* Clear EXTI0 Interrupt Sense Control Bits in MCUCR Register Value Assigned to Local_u8MCUCRTemp */
		Local_u8MCUCRTemp &= EXTI_EXTI0_SENSE_CONTROL_MASK;

		/* Modify EXTI0 Interrupt Sense Control Bits of MCUCR Register Value Assigned to Local_u8MCUCRTemp to be as Passed Sense Control Action */
		Local_u8MCUCRTemp |= Copy_SenseControl_e;

		/* Write Modified Value of Local_u8MCUCRTemp Back Again to MCUCR Register */
	        MCUCR = Local_u8MCUCRTemp;
	}
	else
	{
		/* Function is not working as expected */
		Local_u8ErrorStatus = RT_NOK;
	}
	return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Set sense control action based on which EXTI1 will be 	  */
/* 		     generated 						          */
/* Input Arguments : EXTI_EXTI1SenseControl_e Copy_SenseControl_e	          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 EXTI_u8SetEXTI1SenseControl(EXTI_EXTI1SenseControl_e Copy_SenseControl_e)
{
	/* Define Some Local Variables */
        u8 Local_u8ErrorStatus = RT_OK; 	/* Variable to hold the function status whether it's ok or not ok */
        u8 Local_u8MCUCRTemp; 			/* Temporary Variable to Hold Current MCUCR Register Value */

        /* Check if passed EXTI1 interrupt sense control action is valid or not */
        if(Copy_SenseControl_e == EXTI1_LOW_LEVEL || Copy_SenseControl_e == EXTI1_ANY_LOGICAL_CHANGE ||
           Copy_SenseControl_e == EXTI1_FALLING_EDGE || Copy_SenseControl_e == EXTI1_RISING_EDGE)
        {
        	/* Read Current Value of MCUCR Register then Assign it to Local_u8MCUCRTemp */
        	Local_u8MCUCRTemp = MCUCR;

        	/* Clear EXTI1 Interrupt Sense Control Bits in MCUCR Register Value Assigned to Local_u8MCUCRTemp */
        	Local_u8MCUCRTemp &= EXTI_EXTI1_SENSE_CONTROL_MASK;

        	/* Modify EXTI1 Interrupt Sense Control Bits of MCUCR Register Value Assigned to Local_u8MCUCRTemp to be as Passed Sense Control Action */
        	Local_u8MCUCRTemp |= Copy_SenseControl_e;

        	/* Write Modified Value of Local_u8MCUCRTemp Back Again to MCUCR Register */
                MCUCR = Local_u8MCUCRTemp;
        }
        else
        {
        	/* Function is not working as expected */
        	Local_u8ErrorStatus = RT_NOK;
        }
        return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Set sense control action based on which EXTI2 will be 	  */
/* 		     generated 						          */
/* Input Arguments : EXTI_EXTI2SenseControl_e Copy_SenseControl_e	          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 EXTI_u8SetEXTI2SenseControl(EXTI_EXTI2SenseControl_e Copy_SenseControl_e)
{
	/* Define Some Local Variables */
        u8 Local_u8ErrorStatus = RT_OK; 	/* Variable to hold the function status whether it's ok or not ok */
        u8 Local_u8MCUCRTemp; 			/* Temporary Variable to Hold Current MCUCR Register Value */

        /* Check if passed EXTI2 interrupt sense control action is valid or not */
        if(Copy_SenseControl_e == EXTI2_FALLING_EDGE || Copy_SenseControl_e == EXTI2_RISING_EDGE)
        {
        	/* Read Current Value of MCUCR Register then Assign it to Local_u8MCUCRTemp */
        	Local_u8MCUCRTemp = MCUCR;

        	/* Clear EXTI2 Interrupt Sense Control Bits in MCUCR Register Value Assigned to Local_u8MCUCRTemp */
        	Local_u8MCUCRTemp &= EXTI_EXTI2_SENSE_CONTROL_MASK;

        	/* Modify EXTI2 Interrupt Sense Control Bits of MCUCR Register Value Assigned to Local_u8MCUCRTemp to be as Passed Sense Control Action */
        	Local_u8MCUCRTemp |= Copy_SenseControl_e;

        	/* Write Modified Value of Local_u8MCUCRTemp Back Again to MCUCR Register */
                MCUCR = Local_u8MCUCRTemp;
        }
        else
        {
        	/* Function is not working as expected */
        	Local_u8ErrorStatus = RT_NOK;
        }
        return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Register application callback function that will be executed */
/*		     immediately once EXTI0 ISR is triggered			  */
/* Input Arguments : void(*Copy_pvEXTI0Func)(void)			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 EXTI_u8EXTI0SetCallback(void(*Copy_pvEXTI0Func)(void))
{
	u8 Local_u8ErrorStatus = RT_OK;
	if(Copy_pvEXTI0Func == NULL)
	{
		/* Passed Pointer is NULL Pointer */
		Local_u8ErrorStatus = NULL_POINTER;
	}
	else
	{
		/* Register EXTI0 Application Callback Function */
		EXTI_pvEXTI0Func = Copy_pvEXTI0Func;
	}
	return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Register application callback function that will be executed */
/*		     immediately once EXTI1 ISR is triggered			  */
/* Input Arguments : void(*Copy_pvEXTI1Func)(void)			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 EXTI_u8EXTI1SetCallback(void(*Copy_pvEXTI1Func)(void))
{
	u8 Local_u8ErrorStatus = RT_OK;
	if(Copy_pvEXTI1Func == NULL)
	{
		/* Passed Pointer is NULL Pointer */
		Local_u8ErrorStatus = NULL_POINTER;
	}
	else
	{
		/* Register EXTI1 Application Callback Function */
		EXTI_pvEXTI1Func = Copy_pvEXTI1Func;
	}
	return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Register application callback function that will be executed */
/*		     immediately once EXTI2 ISR is triggered			  */
/* Input Arguments : void(*Copy_pvEXTI2Func)(void)			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 EXTI_u8EXTI2SetCallback(void(*Copy_pvEXTI2Func)(void))
{
	u8 Local_u8ErrorStatus = RT_OK;
	if(Copy_pvEXTI2Func == NULL)
	{
		/* Passed Pointer is NULL Pointer */
		Local_u8ErrorStatus = NULL_POINTER;
	}
	else
	{
		/* Register EXTI2 Application Callback Function */
		EXTI_pvEXTI2Func = Copy_pvEXTI2Func;
	}
	return Local_u8ErrorStatus;
}

/******************************************** Interrupt Handlers ********************************************/

/************************************************/
/* 	External Interrupt Request 0		*/
/************************************************/
void __vector_1 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_1 (void)
{
	/* Check If EXTI0 Callback Function is Registered or Not */
	if(EXTI_pvEXTI0Func != NULL)
	{
		/* Invoke EXTI0 Callback Function */
		EXTI_pvEXTI0Func();
	}
}

/************************************************/
/* 	External Interrupt Request 1		*/
/************************************************/
void __vector_2 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_2 (void)
{
	/* Check If EXTI1 Callback Function is Registered or Not */
	if(EXTI_pvEXTI1Func != NULL)
	{
		/* Invoke EXTI1 Callback Function */
		EXTI_pvEXTI1Func();
	}
}

/************************************************/
/* 	External Interrupt Request 2		*/
/************************************************/
void __vector_3 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_3 (void)
{
	/* Check If EXTI2 Callback Function is Registered or Not */
	if(EXTI_pvEXTI2Func != NULL)
	{
		/* Invoke EXTI2 Callback Function */
		EXTI_pvEXTI2Func();
	}
}
