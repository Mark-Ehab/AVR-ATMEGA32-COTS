/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Feb 20, 2023               	*/
/*              SWC              : SERVO			*/
/*              Description	 : SERVO Program                */
/* 	        Version          : V1.0                         */
/****************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_ERRORS.h"
#include "../../LIB/SERVICE_FUNCTIONS.h"

#include "../../MCAL/TIMERs/TIMER1/TIMER1_Interface.h"

#include "SERVO_Interface.h"
#include "SERVO_Private.h"
#include "SERVO_Config.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 FUNCTIONS PROTOTYPES		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize servo motor					  */
/* Input Arguments : void					                  */
/* Return          : void	                      			          */
/**********************************************************************************/
void SERVO_vidInit(void)
{
	/* Initialize Timer1 */
	TIMER1_vidInit();

	/* Set Timer1 Top as Input Capture Value */
	TIMER1_vidSetInputCaptureValue(20000);

	/* Start Timer1 */
	TIMER1_vidStart();
}
/**********************************************************************************/
/* Description     : Function that takes desired angle to rotate servo motor in	  */
/*                   addition to desired Timer1 output compare match channel on   */
/*                   which servo motor will operate                               */
/* Input Arguments : u8 Copy_u8ChannelNum , u8 Copy_u8AngleVal	                  */
/* Return          : u8		                      			          */
/* Note            : This servo motor is limited servo motor which is angle       */
/*                   controlled and can rotate to angles in range (0 ==> 180)     */
/*                   degrees                                                      */
/**********************************************************************************/
u8 SERVO_vidRotateServo(u8 Copy_u8ChannelNum , u8 Copy_u8AngleVal)
{
	/* Local Variable Definitions */
	u8 Local_u8ErrorState = RT_OK;    /* A variable to hold function status */

	if(Copy_u8AngleVal > 180)
	{
		/* Function is not working as expected */
		Local_u8ErrorState = RT_NOK;
	}
	else
	{
		u16 Local_u16MappingResult; /* Variable to Hold Mapping Result */

		/* Get the compare match value equivalent to passed angle value */
		Local_u16MappingResult = (u16)SERV_s32Map(0,180,750,2500,Copy_u8AngleVal);

		/* Check Timer1 Channel on Which Servo will Operate */
		switch (Copy_u8ChannelNum) {
			case SERVO_CHANNELA:
				/* Set Compare Match Value for Timer1 Channel A */
				TIMER1_vidSetCompareMatchAValue(Local_u16MappingResult);
				break;
			case SERVO_CHANNELB:
				/* Set Compare Match Value for Timer1 Channel B */
				TIMER1_vidSetCompareMatchBValue(Local_u16MappingResult);
				break;
			default:
				/* Function is not working as expected */
				Local_u8ErrorState = RT_NOK;
		}
	}
	return Local_u8ErrorState;
}
