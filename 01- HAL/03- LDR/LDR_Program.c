/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : JAN 23, 2023               	*/
/*              SWC              : LDR  			*/
/*              Description	 : LDR Program                  */
/* 	        Version          : V1.0                         */
/****************************************************************/

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/STD_ERRORS.h"

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/ADC/ADC_Interface.h"

#include "LDR_Interface.h"
#include "LDR_Private.h"
#include "LDR_Config.h"

#define VREF_MV 			5000UL
#define TWO_POWER_RESOLUTION		256UL

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  PUBLIC FUNCTIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize LDR			        		  */
/* Input Arguments : void			    			          */
/* Return          : void                       			          */
/**********************************************************************************/
void LDR_vidLDRInit(void)
{
	/* Set the pin to which LDR is connected as input */
	DIO_u8setPinDir(LDR_PORT,LDR_PIN,INPUT);

	/* Initialize ADC */
	ADC_vidInit();
}
/**********************************************************************************/
/* Description     : Get the digital reading equivalent to analog reading sensed  */
/*		     by LDR Sensor synchronously		        	  */
/* Input Arguments : Copy_u8LDRChannelNum	    			          */
/* Return          : u16	                      			          */
/**********************************************************************************/
u16 LDR_u16GetLDRReadingSync(u8 Copy_u8LDRChannelNum)
{
	/* Define Some Local Variables */
	u16 Local_u16LDRReading_mv;       /* Holds LDR Analog Reading in milli-volts */
	u16* Local_pu16ADCDigitalReading; /* Holds Address of ADC Digital Reading Equivalent to Analog Reading Sensed by LDR */

	/* Get ADC Digital Reading Equivalent to Analog Reading Sensed by LDR */
	ADC_u8GetAdcReadingSyncSingleConversion(Copy_u8LDRChannelNum,Local_pu16ADCDigitalReading);

	/* Get Analog Reading Sensed by LDR */
	Local_u16LDRReading_mv = ((u32)(*Local_pu16ADCDigitalReading) * VREF_MV)/TWO_POWER_RESOLUTION;

	return Local_u16LDRReading_mv;
}
/**********************************************************************************/
/* Description     : Get the digital reading equivalent to analog reading sensed  */
/*		     by LDR Sensor asynchronously	        		  */
/* Input Arguments : Copy_u8LDRChannelNum , Copy_pu16LDRReading,  		  */
/* 		     void(*Copy_pvLDRFunc)(void)			    	  */
/* Return          : void	                      			          */
/**********************************************************************************/
void LDR_u16GetLDRReadingAsync(u8 Copy_u8LDRChannelNum , u16* Copy_pu16LDRReading, void(*Copy_pvLDRFunc)(void))
{
	/* Get ADC Digital Reading Asynchronously */
	ADC_u8GetAdcReadingAsyncSingleConversion(Copy_u8LDRChannelNum , Copy_pu16LDRReading , Copy_pvLDRFunc);
}
