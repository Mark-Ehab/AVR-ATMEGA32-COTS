/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Feb 27, 2023               	*/
/*              SWC              : WatchDog Timer		*/
/*              Description	 : WatchDog Timer Program       */
/* 	        Version          : V1.0                         */
/****************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_ERRORS.h"
#include "../../LIB/SERVICE_FUNCTIONS.h"

#include "WDT_Interface.h"
#include "WDT_Private.h"
#include "WDT_Config.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  PUBLIC FUNCTIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Enable WatchDog Timer					  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void WDT_vidEnable(void)
{
	/* Set WDE Bit in WDTCR Register */
	SET_BIT(WDTCR,WDTCR_WDE);
}
/**********************************************************************************/
/* Description     : Disable WatchDog Timer					  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void WDT_vidDisable(void)
{
	/* Perform Watchdog Disable Sequence */

	/* Step1 : In the same operation, write a logic one to WDTOE and WDE bits in WDTCR Register */
	WDTCR |= WDT_DISABLE_STEP1;

	/* Step2 : Write a logic 0 to WDE Bit in WDTCR Register */
	WDTCR = WDT_DISABLE_STEP2;
}
/**********************************************************************************/
/* Description     : Set WatchDog Timer in sleep mode for a specific time	  */
/* Input Arguments : u8 Copy_u8SleepTime				          */
/* Return          : u8							          */
/**********************************************************************************/
u8 WDT_u8Sleep(u8 Copy_u8SleepTime)
{
	/* Local Variables Definitions */
	u8 Local_u8ErrorStatus = RT_OK;		/* A variable to hold function error status */

	/* Clear WDT Prescaler Bits */
	WDTCR &= WDT_PRESCALER_MASK;

	/* Check if passed sleep time is valid or not */
	switch(Copy_u8SleepTime)
	{
		case WDT_16K_16300us:
			/* Set WDT to sleep for 16.3ms */
			WDTCR |= WDT_PRESCALER_16K_16300us;
			break;
		case WDT_32K_32500us:
			/* Set WDT to sleep for 32.5ms */
			WDTCR |= WDT_PRESCALER_32K_32500us;
			break;
		case WDT_64K_65ms:
			/* Set WDT to sleep for 65ms */
			WDTCR |= WDT_PRESCALER_64K_65ms;
			break;
		case WDT_128K_130ms:
			/* Set WDT to sleep for 0.13s */
			WDTCR |= WDT_PRESCALER_128K_130ms;
			break;
		case WDT_256K_260ms:
			/* Set WDT to sleep for 0.26s */
			WDTCR |= WDT_PRESCALER_256K_260ms;
			break;
		case WDT_512K_520ms:
			/* Set WDT to sleep for 0.52s */
			WDTCR |= WDT_PRESCALER_512K_520ms;
			break;
		case WDT_1024K_1s:
			/* Set WDT to sleep for 1.0s */
			WDTCR |= WDT_PRESCALER_1024K_1s;
			break;
		case WDT_2048K_2s:
			/* Set WDT to sleep for 2.1s */
			WDTCR |= WDT_PRESCALER_2048K_2s;
			break;
		default:
			/* Function is not working as expected */
			Local_u8ErrorStatus = RT_NOK;
	}

	return Local_u8ErrorStatus;

}
