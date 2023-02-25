/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Dec 19, 2021               	*/
/*              SWC              : BUTTON			*/
/*              Description	 : BUTTON Interface             */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef HAL_BUTTON_INTERFACE_H_
#define HAL_BUTTON_INTERFACE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	   INTERFACE MACROS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Types of button connections */
#define BUTTON_PULLED_UP		1
#define BUTTON_PULLED_DOWN		2


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
u8 BUTTON_u8IsPressed(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8ConnectionType , u8* Copy_pu8ButtonStatus);
/**********************************************************************************/
/* Description     : This function checks if a specific button is pressed or not  */
/*		     with handling bouncing behavior				  */
/* Input Arguments : u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8ConnectionType ,  */
/* 		     u8* Copy_pu8ButtonStatus    				  */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 BUTTON_u8IsPressedDebounced(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8ConnectionType , u8* Copy_pu8ButtonStatus);

#endif /* HAL_BUTTON_INTERFACE_H_ */
