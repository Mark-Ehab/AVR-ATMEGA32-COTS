/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Dec 19, 2021               	*/
/*              SWC              : BUTTON			*/
/*              Description	 : BUTTON Program               */
/* 	        Version          : V1.0                         */
/****************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_ERRORS.h"
#include "../../LIB/SERVICE_FUNCTIONS.h"

#include "../../MCAL/DIO/DIO_Interface.h"

#include <util/delay.h>

#include "BUTTON_Interface.h"
#include "BUTTON_Private.h"
#include "BUTTON_Config.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 FUNCTIONS PROTOTYPES		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : This function checks if a specific button is pressed or not  */
/* Input Arguments : u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8ConnectionType ,  */
/* 		     u8* Copy_pu8ButtonStatus    				  */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 BUTTON_u8IsPressed(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8ConnectionType , u8* Copy_pu8ButtonStatus)
{
	/* Local Variables Definitions */
	u8 Local_u8ErrorStatus = RT_OK;			/* A variable to hold function status */

	/* Check if passed pointer is null or not */
	if(Copy_pu8ButtonStatus != NULL)
	{
		u8* Local_pu8PtrVar;			/* A pointer to char that holds address of variable that holds pin status to be updated by hardware */

		/* Initialize Button Status As Not Pressed */
		*Copy_pu8ButtonStatus = BUTTON_NOT_PRESSED;

		/* Get Pin Value */
		DIO_u8getPinVal(Copy_u8Port,Copy_u8Pin,Local_pu8PtrVar);

		/* Check Passed Button Connection Type */
		switch(Copy_u8ConnectionType)
		{
			case BUTTON_PULLED_UP:

				/* Check if button is pressed */
				if(*Local_pu8PtrVar == 0)
				{
					/* Set button status as pressed */
					*Copy_pu8ButtonStatus = BUTTON_PRESSED;
				}

				break;

			case BUTTON_PULLED_DOWN:

				/* Check if button is pressed */
				if(*Local_pu8PtrVar == 1)
				{
					/* Set button status as pressed */
					*Copy_pu8ButtonStatus = BUTTON_PRESSED;
				}

				break;

			default:
				/* Function is not working as expected */
				Local_u8ErrorStatus = RT_NOK;
		}
	}
	else
	{
		/* Passed pointer is a NULL pointer */
		Local_u8ErrorStatus = NULL_POINTER;
	}
	return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : This function checks if a specific button is pressed or not  */
/*		     with handling bouncing behavior				  */
/* Input Arguments : u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8ConnectionType ,  */
/* 		     u8* Copy_pu8ButtonStatus    				  */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 BUTTON_u8IsPressedDebounced(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8ConnectionType , u8* Copy_pu8ButtonStatus)
{
	/* Local Variables Definitions */
	u8 Local_u8ErrorStatus = RT_OK;		/* A variable to hold function status */

	/* Check if passed pointer is null or not */
	if(Copy_pu8ButtonStatus != NULL)
	{
		u8* Local_pu8PtrVar;			/* A pointer to char that holds address of variable that holds pin status to be updated by hardware */

		/* Initialize Button Status As Not Pressed */
		*Copy_pu8ButtonStatus = BUTTON_NOT_PRESSED;

		/* Get Pin Value */
		DIO_u8getPinVal(Copy_u8Port,Copy_u8Pin,Local_pu8PtrVar);

		/* Check Passed Button Connection Type */
		switch(Copy_u8ConnectionType)
		{
			case BUTTON_PULLED_UP:

				/* Check if button is pressed */
				if(*Local_pu8PtrVar == 0)
				{
					/* Wait for bounce time */
					_delay_ms(5);

					/* Get Pin Value */
					DIO_u8getPinVal(Copy_u8Port,Copy_u8Pin,Local_pu8PtrVar);

					/* Check Button Status After Debouncing */
					if(*Local_pu8PtrVar == 0)
					{
						/* Set button status as pressed */
						*Copy_pu8ButtonStatus = BUTTON_PRESSED;
					}

					/* Check if button is still pressed */
					while(*Local_pu8PtrVar == 0)
					{
						/* Get Pin Value */
						DIO_u8getPinVal(Copy_u8Port,Copy_u8Pin,Local_pu8PtrVar);
					}

					/* Wait for bounce time */
					_delay_ms(5);
				}

				break;

			case BUTTON_PULLED_DOWN:

				/* Check if button is pressed */
				if(*Local_pu8PtrVar == 1)
				{
					/* Wait for bounce time */
					_delay_ms(5);

					/* Get Pin Value */
					DIO_u8getPinVal(Copy_u8Port,Copy_u8Pin,Local_pu8PtrVar);

					/* Check Button Status After Debouncing */
					if(*Local_pu8PtrVar == 1)
					{
						/* Set button status as pressed */
						*Copy_pu8ButtonStatus = BUTTON_PRESSED;
					}

					/* Check if button is still pressed */
					while(*Local_pu8PtrVar == 1)
					{
						/* Get Pin Value */
						DIO_u8getPinVal(Copy_u8Port,Copy_u8Pin,Local_pu8PtrVar);
					}

					/* Wait for bounce time */
					_delay_ms(5);
				}
				break;

			default:
				/* Function is not working as expected */
				Local_u8ErrorStatus = RT_NOK;
		}
	}
	else
	{
		/* Passed pointer is a NULL pointer */
		Local_u8ErrorStatus = NULL_POINTER;
	}
	return Local_u8ErrorStatus;
}
