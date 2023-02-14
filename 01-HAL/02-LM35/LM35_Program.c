/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : JAN 23, 2023               	*/
/*              SWC              : LM35				*/
/*              Description	 : LM35 Program                 */
/* 	        Version          : V1.0                         */
/****************************************************************/

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/STD_ERRORS.h"

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/ADC/ADC_Interface.h"

#include "LM35_Interface.h"
#include "LM35_Private.h"
#include "LM35_Config.h"

#define VREF_MV 			5000UL
#define TWO_POWER_RESOLUTION		1024UL

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  PUBLIC FUNCTIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize LM35			        		  */
/* Input Arguments : void			    			          */
/* Return          : void                       			          */
/**********************************************************************************/
void LM35_vidLM35Init(void)
{
	/* Set the pin to which LM35 is connected as input */
	DIO_u8setPinDir(LM35_PORT,LM35_PIN,INPUT);

	/* Initialize ADC */
	ADC_vidInit();
}
/**********************************************************************************/
/* Description     : Get the temperature reading in celsius sensed by LM35        */
/*		     Temperature Sensor	synchronously			  	  */
/* Input Arguments : Copy_u8LM35ChannelNum	    			          */
/* Return          : u16	                      			          */
/**********************************************************************************/
u16 LM35_u16GetLM35ReadingSync(u8 Copy_u8LM35ChannelNum)
{
	/* Initialize local variables */
	u16 Local_u16LM35Reading;         /* Holds LM35 Physical Temperature Reading in Celsius */
	u16* Local_pu16ADCDigitalReading; /* Holds Address of ADC Digital Reading of Temperature */
	u16 Local_u16AnalogReading_mv;    /* Holds Analog Reading equivalent for ADC Digital Reading of Temperature in milli-volts */

	/* Get ADC Digital Reading Synchronously */
	ADC_u8GetAdcReadingSyncSingleConversion(Copy_u8LM35ChannelNum,Local_pu16ADCDigitalReading);

	/* Convert ADC Digital Reading to its equivalent Analog Reading in milli-volts */
	Local_u16AnalogReading_mv = (u16)(((u32)(*Local_pu16ADCDigitalReading) * VREF_MV)/TWO_POWER_RESOLUTION);

	/* Get Equivalent Analog Physical Value of Temperature Sensed by LM35 in Celsius */
	Local_u16LM35Reading = Local_u16AnalogReading_mv/10;

	return Local_u16LM35Reading;
}
/**********************************************************************************/
/* Description     : Get the temperature reading in celsius sensed by LM35        */
/*		     Temperature Sensor	asynchronously			          */
/* Input Arguments : Copy_u8LM35ChannelNum , Copy_pu16LM35Reading,  		  */
/* 		     void(*Copy_pvLM35Func)(void)			    	  */
/* Return          : void	                      			          */
/**********************************************************************************/
void LM35_u16GetLM35ReadingAsync(u8 Copy_u8LM35ChannelNum , u16* Copy_pu16LM35Reading, void(*Copy_pvLM35Func)(void))
{
	/* Get ADC Digital Reading Asynchronously */
	ADC_u8GetAdcReadingAsyncSingleConversion(Copy_u8LM35ChannelNum , Copy_pu16LM35Reading , Copy_pvLM35Func);
}
