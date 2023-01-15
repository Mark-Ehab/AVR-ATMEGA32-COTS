/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Dec 19, 2022               	*/
/*              SWC              : SSD				*/
/*              Description	 : SSD Program                  */
/* 	        Version          : V1.0                         */
/****************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "SSD_Interface.h"
#include "SSD_Config.h"
#include "SSD_Private.h"


/**********************************************************************************/
/* Description     : Initialize Seven Segment					  */
/* Input Arguments : void			    			          */
/* Return          : void                       				  */
/**********************************************************************************/
void SSD_vidSevenSegmentDisplayInit(void)
{
#if SSD_MODE == 1
	/* Single Mode */
	/* Set all pins of seven segment as output and its common pin as output too */
	DIO_u8setPortDir(SSD_PORT_CFG,FULL_OUTPUT);
	DIO_u8setPinDir(SSD_PORT_COMMON_CFG,SSD_PIN_COMMON_CFG,OUTPUT);
	#if SSD_COMMON_TYPE == 1
		/* Set the common as high in default (common cathode) */
		DIO_u8setPinVal(SSD_PORT_COMMON_CFG,SSD_PIN_COMMON_CFG,HIGH);
	#elif SSD_COMMON_TYPE == 2
		/* Set the common as low in default (common anode) */
		DIO_u8setPinVal(SSD_PORT_COMMON_CFG,SSD_PIN_COMMON_CFG,LOW);
	#else
		#error "Invalid Seven Segment Common Type Configuration!"
	#endif
#elif SSD_MODE == 2
	/* Multiplexing Mode */
	/* Set all pins of seven segments as output and their common pins as output too */
	DIO_u8setPortDir(SSD_PORT_CFG,FULL_OUTPUT);
	DIO_u8setPinDir(SSD_PORT_COMMON_CFG,SSD_PIN_FIRST_COMMON_CFG,OUTPUT);
	DIO_u8setPinDir(SSD_PORT_COMMON_CFG,SSD_PIN_SECOND_COMMON_CFG,OUTPUT);
	#if SSD_COMMON_TYPE == 1
		/* Set the commons as high in default (common cathode) */
		DIO_u8setPinVal(SSD_PORT_COMMON_CFG,SSD_PIN_FIRST_COMMON_CFG,HIGH);
		DIO_u8setPinVal(SSD_PORT_COMMON_CFG,SSD_PIN_SECOND_COMMON_CFG,HIGH);
	#elif SSD_COMMON_TYPE == 2
		/* Set the commons as low in default (common anode) */
		DIO_u8setPinVal(SSD_PORT_COMMON_CFG,SSD_PIN_FIRST_COMMON_CFG,LOW);
		DIO_u8setPinVal(SSD_PORT_COMMON_CFG,SSD_PIN_SECOND_COMMON_CFG,LOW);
	#else
		#error "Invalid Seven Segment Common Type Configuration!"
	#endif
#else
	#error "Invalid Mode Configuration!"
#endif
}

/**********************************************************************************/
/* Description     : Turn On Seven Segment					  */
/* Input Arguments : Copy_u8Common		    			          */
/* Return          : void                       			          */
/**********************************************************************************/
void SSD_vidTurnON(u8 Copy_u8Common)
{
#if SSD_COMMON_TYPE == 1
	/* Common Cathode */
	if(Copy_u8Common == SSD_FIRST_COMMON)
	{
		DIO_u8setPinVal(SSD_PORT_COMMON_CFG,SSD_PIN_FIRST_COMMON_CFG,LOW);
	}
	else
	{
		DIO_u8setPinVal(SSD_PORT_COMMON_CFG,SSD_PIN_SECOND_COMMON_CFG,LOW);
	}
#elif SSD_COMMON_TYPE == 2
	/* Common Anode */
	if(Copy_u8Common == SSD_FIRST_COMMON)
	{
		DIO_u8setPinVal(SSD_PORT_COMMON_CFG,SSD_PIN_FIRST_COMMON_CFG,HIGH);
	}
	else
	{
		DIO_u8setPinVal(SSD_PORT_COMMON_CFG,SSD_PIN_SECOND_COMMON_CFG,HIGH);
	}
#else
	#error "Invalid Seven Segment Common Type Configuration!"
#endif
}

/**********************************************************************************/
/* Description     : Turn Off Seven Segment					  */
/* Input Arguments : Copy_u8Common		         	                  */
/* Return          : void                       			          */
/**********************************************************************************/
void SSD_vidTurnOFF(u8 Copy_u8Common)
{
#if SSD_COMMON_TYPE == 1
	/* Common Cathode */
	if(Copy_u8Common == SSD_FIRST_COMMON)
	{
		DIO_u8setPinVal(SSD_PORT_COMMON_CFG,SSD_PIN_FIRST_COMMON_CFG,HIGH);
	}
	else
	{
		DIO_u8setPinVal(SSD_PORT_COMMON_CFG,SSD_PIN_SECOND_COMMON_CFG,HIGH);
	}
#elif SSD_COMMON_TYPE == 2
	/* Common Anode */
	if(Copy_u8Common == SSD_FIRST_COMMON)
	{
		DIO_u8setPinVal(SSD_PORT_COMMON_CFG,SSD_PIN_FIRST_COMMON_CFG,LOW);
	}
	else
	{
		DIO_u8setPinVal(SSD_PORT_COMMON_CFG,SSD_PIN_SECOND_COMMON_CFG,LOW);
	}
#else
	#error "Invalid Seven Segment Common Type Configuration!"
#endif
}

/**********************************************************************************/
/* Description     : Display a number on seven segment from 0 to 9		  */
/* Input Arguments : Copy_u8Num			    			          */
/* Return          : void                       				  */
/**********************************************************************************/
void SSD_vidDisplayNum(u8 Copy_u8Num)
{
	u8 Local_u8SevenDigits[10] = {ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE};
#if SSD_COMMON_TYPE == 1
	/* Common Cathode */
	DIO_u8setPortVal(SSD_PORT_CFG,Local_u8SevenDigits[Copy_u8Num]);
#elif SSD_COMMON_TYPE == 2
	/* Common Anode */
	DIO_u8setPortVal(SSD_PORT_CFG,~(Local_u8SevenDigits[Copy_u8Num]));
#else
	#error "Invalid Seven Segment Common Type Configuration!"
#endif
}
