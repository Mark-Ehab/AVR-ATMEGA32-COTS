/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Feb 20, 2023               	*/
/*              SWC              : SERVO			*/
/*              Description	 : SERVO Interface              */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef HAL_SERVO_INTERFACE_H_
#define HAL_SERVO_INTERFACE_H_
        
/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	   INTERFACE MACROS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/ 

/* Possible Timer1 Channels To Rotate Servo */
#define SERVO_CHANNELA                          1
#define SERVO_CHANNELB                          2


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
void SERVO_vidInit(void);
/**********************************************************************************/
/* Description     : Function that takes desired angle to rotate servo motor in	  */
/*                   addition to desired Timer1 output compare match channel on   */
/*                   which servo motor will operate                               */
/* Input Arguments : u8 Copy_u8ChannelNum , u8 Copy_u8AngleVal	                  */
/* Return          : u8                       			          */
/* Note            : This servo motor is limited servo motor which is angle       */
/*                   controlled and can rotate to angles in range (0 ==> 180)     */
/*                   degrees                                                      */
/**********************************************************************************/
u8 SERVO_vidRotateServo(u8 Copy_u8ChannelNum , u8 Copy_u8AngleVal);
   
#endif /* HAL_SERVO_INTERFACE_H_ */
