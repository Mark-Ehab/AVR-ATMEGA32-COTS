/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Sep 17, 2021               	*/
/*              SWC              : DIO				*/
/*              Description	 : DIO Interface                */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_DIO_INTERFACE_H_
#define MCAL_DIO_INTERFACE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	   INTERFACE MACROS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* DIO Ports */
#define DIO_PORT_A 			0U
#define DIO_PORT_B 			1U
#define DIO_PORT_C 			2U
#define DIO_PORT_D 			3U


/* DIO Pins */
#define DIO_PIN_0 			0U
#define DIO_PIN_1 			1U
#define DIO_PIN_2 			2U
#define DIO_PIN_3 			3U
#define DIO_PIN_4 			4U
#define DIO_PIN_5 			5U
#define DIO_PIN_6 			6U
#define DIO_PIN_7 			7U


/* Pin Level Signals */
#define DIO_PIN_INPUT 			0U
#define DIO_PIN_OUTPUT			1U

#define DIO_PIN_LOW 			0U
#define DIO_PIN_HIGH 			1U


/* Port Level Signals */
#define DIO_PORT_INPUT 		        0x00
#define DIO_PORT_OUTPUT		        0xff

#define DIO_PORT_LOW 		        0x00
#define DIO_PORT_HIGH 		        0xff


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 FUNCTIONS PROTOTYPES		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Port Level */

/**********************************************************************************/
/* Description     : Set port direction (Input or Output)			  */
/* Input Arguments : u8 Copy_u8Port , u8 Copy_u8Dir			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8setPortDir(u8 Copy_u8Port , u8 Copy_u8Dir);
/**********************************************************************************/
/* Description     : Set port value (High  or Low)				  */
/* Input Arguments : u8 Copy_u8Port , u8 Copy_u8Val			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8setPortVal(u8 Copy_u8Port , u8 Copy_u8Val);
/**********************************************************************************/
/* Description     : Get the value on port 	     				  */
/* Input Arguments : u8 Copy_u8Port , u8* Copy_pu8Val			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8getPortVal(u8 Copy_u8Port , u8* Copy_pu8Val);

/* Pin Level */

/**********************************************************************************/
/* Description     : Set pin direction (Input  or Output)			  */
/* Input Arguments : u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Dir		  */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8setPinDir(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Dir);
/**********************************************************************************/
/* Description     : Set pin value (High or Low)			          */
/* Input Arguments : u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Val		  */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8setPinVal(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Val);
/**********************************************************************************/
/* Description     : Get pin value					          */
/* Input Arguments : u8 Copy_u8Port , u8 Copy_u8Pin , u8* Copy_pu8Val		  */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8getPinVal(u8 Copy_u8Port , u8 Copy_u8Pin , u8* Copy_pu8Val);
/**********************************************************************************/
/* Description     : Toggle current pin value					  */
/* Input Arguments : u8 Copy_u8Port , u8 Copy_u8Pin			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8togglePinVal(u8 Copy_u8Port , u8 Copy_u8Pin);

#endif /* MCAL_DIO_DIO_INTERFACE_H_  */
