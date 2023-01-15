/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Sep 17, 2021               	*/
/*              SWC              : DIO				*/
/*              Description	 : DIO Interface                */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_DIO_INTERFACE_H_
#define MCAL_DIO_INTERFACE_H_

						   /* Interface Macros */
/* DIO Ports */
#define PORT_A 			(u8)0
#define PORT_B 			(u8)1
#define PORT_C 			(u8)2
#define PORT_D 			(u8)3

/* DIO Pins */
#define PIN_0 			(u8)0
#define PIN_1 			(u8)1
#define PIN_2 			(u8)2
#define PIN_3 			(u8)3
#define PIN_4 			(u8)4
#define PIN_5 			(u8)5
#define PIN_6 			(u8)6
#define PIN_7 			(u8)7

/* Pin Level Signals */
#define INPUT 			(u8)0
#define OUTPUT			(u8)1
#define LOW 				(u8)0
#define HIGH 				(u8)1

/* Port Level Signals */
#define FULL_INPUT 			0x00
#define FULL_OUTPUT			0xff
#define FULL_LOW 			0x00
#define FULL_HIGH 			0xff

						/* Function prototypes */
/* Port Level */

/**********************************************************************************/
/* Description     : Set port direction (Input or Output)			  */
/* Input Arguments : u8 Copy_u8port , u8 Copy_u8dir			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8setPortDir(u8 Copy_u8port , u8 Copy_u8dir);
/**********************************************************************************/
/* Description     : Set port value (High  or Low)				  */
/* Input Arguments : u8 Copy_u8port , u8 Copy_u8dval			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8setPortVal(u8 Copy_u8port , u8 Copy_u8dval);
/**********************************************************************************/
/* Description     : Get the value on port 	     				  */
/* Input Arguments : u8 Copy_u8port , u8* Copy_u8pval			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8getPortVal(u8 Copy_u8port , u8* Copy_u8pval);

/* Pin Level */

/**********************************************************************************/
/* Description     : Set pin direction (Input  or Output)			  */
/* Input Arguments : u8 Copy_u8port , u8 Copy_u8pin , u8 Copy_u8dir		  */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8setPinDir(u8 Copy_u8port , u8 Copy_u8pin , u8 Copy_u8dir);
/**********************************************************************************/
/* Description     : Set pin value (High or Low)			          */
/* Input Arguments : u8 Copy_u8port , u8 Copy_u8pin , u8 Copy_u8val		  */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8setPinVal(u8 Copy_u8port , u8 Copy_u8pin , u8 Copy_u8val);
/**********************************************************************************/
/* Description     : Get pin value					          */
/* Input Arguments : u8 Copy_u8port , u8 Copy_u8pin , u8* Copy_u8pval		  */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8getPinVal(u8 Copy_u8port , u8 Copy_u8pin , u8* Copy_u8pval);
/**********************************************************************************/
/* Description     : Toggle current pin value					  */
/* Input Arguments : u8 Copy_u8port , u8 Copy_u8pin			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8togglePinVal(u8 Copy_u8port , u8 Copy_u8pin);

#endif /* MCAL_DIO_DIO_INTERFACE_H_  */
