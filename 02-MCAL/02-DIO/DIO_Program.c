/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Sep 17, 2021               	*/
/*              SWC              : DIO				*/
/*              Description	 : DIO Program                  */
/* 	        Version          : V1.0                         */
/****************************************************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/STD_ERRORS.h"

#include "DIO_Interface.h"
#include "DIO_Private.h"
#include "DIO_Config.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  PUBLIC FUNCTIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*Port level*/

/**********************************************************************************/
/* Description     : Set port direction (Input or Output)			  */
/* Input Arguments : u8 Copy_u8Port , u8 Copy_u8Dir			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8setPortDir(u8 Copy_u8Port , u8 Copy_u8Dir)
{
	u8 local_u8errStatus = RT_OK ;
	switch(Copy_u8Port)
	{
	case DIO_PORT_A:
		DDRA=Copy_u8Dir;
		break;
	case DIO_PORT_B:
		DDRB=Copy_u8Dir;
		break;
	case DIO_PORT_C:
		DDRC=Copy_u8Dir;
		break;
	case DIO_PORT_D:
		DDRD=Copy_u8Dir;
		break;
	default:
		local_u8errStatus = RT_NOK ;
	}
	return local_u8errStatus ;
}
/**********************************************************************************/
/* Description     : Set port value (High  or Low)				  */
/* Input Arguments : u8 Copy_u8Port , u8 Copy_u8Val			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8setPortVal(u8 Copy_u8Port , u8 Copy_u8Val)
{
	u8 local_u8errStatus = RT_OK ;
	switch(Copy_u8Port)
	{
	case DIO_PORT_A:
		PORTA=Copy_u8Val;
		break;
	case DIO_PORT_B:
		PORTB=Copy_u8Val;
		break;
	case DIO_PORT_C:
		PORTC=Copy_u8Val;
		break;
	case DIO_PORT_D:
		PORTD=Copy_u8Val;
		break;
	default:
		local_u8errStatus = RT_NOK ;
	}
	return local_u8errStatus ;
}
/**********************************************************************************/
/* Description     : Get the value on port 	     				  */
/* Input Arguments : u8 Copy_u8Port , u8* Copy_pu8Val			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8getPortVal(u8 Copy_u8Port , u8* Copy_pu8Val)
{
	u8 local_u8errStatus = RT_OK ;
	switch(Copy_u8Port)
	{
	case DIO_PORT_A:
		*Copy_pu8Val=PINA;
		break;
	case DIO_PORT_B:
		*Copy_pu8Val=PINB;
		break;
	case DIO_PORT_C:
		*Copy_pu8Val=PINC;
		break;
	case DIO_PORT_D:
		*Copy_pu8Val=PIND;
		break;
	default:
		local_u8errStatus = RT_NOK ;
	}
	return local_u8errStatus ;
}

/*Pin level*/

/**********************************************************************************/
/* Description     : Set pin direction (Input  or Output)			  */
/* Input Arguments : u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Dir		  */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8setPinDir(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Dir)
{
	u8 local_u8errStatus = RT_OK ;
	if(Copy_u8Pin >= DIO_PIN_0 && Copy_u8Pin <= DIO_PIN_7 )
	{
		if(Copy_u8Dir == DIO_PIN_INPUT)
		{
			switch(Copy_u8Port)
			{
			case DIO_PORT_A:
				CLR_BIT(DDRA,Copy_u8Pin);
				break;
			case DIO_PORT_B:
				CLR_BIT(DDRB,Copy_u8Pin);
				break;
			case DIO_PORT_C:
				CLR_BIT(DDRC,Copy_u8Pin);
				break;
			case DIO_PORT_D:
				CLR_BIT(DDRD,Copy_u8Pin);
				break;
			default:
				local_u8errStatus = RT_NOK ;
			}
		}
		else if(Copy_u8Dir == DIO_PIN_OUTPUT)
		{
			switch(Copy_u8Port)
			{
			case DIO_PORT_A:
				SET_BIT(DDRA,Copy_u8Pin);
				break;
			case DIO_PORT_B:
				SET_BIT(DDRB,Copy_u8Pin);
				break;
			case DIO_PORT_C:
				SET_BIT(DDRC,Copy_u8Pin);
				break;
			case DIO_PORT_D:
				SET_BIT(DDRD,Copy_u8Pin);
				break;
			default:
				local_u8errStatus = RT_NOK ;
			}
		}
		else
		{
			local_u8errStatus = RT_NOK ;
		}
	}
	else
	{
		local_u8errStatus = RT_NOK ;
	}
	return local_u8errStatus ;
}
/**********************************************************************************/
/* Description     : Set pin value (High or Low)			          */
/* Input Arguments : u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Val		  */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8setPinVal(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Val)
{
	u8 local_u8errStatus = RT_OK ;
	if(Copy_u8Pin >= DIO_PIN_0 && Copy_u8Pin <= DIO_PIN_7 )
	{
		if(Copy_u8Val == DIO_PIN_LOW)
		{
			switch(Copy_u8Port)
			{
			case DIO_PORT_A:
				CLR_BIT(PORTA,Copy_u8Pin);
				break;
			case DIO_PORT_B:
				CLR_BIT(PORTB,Copy_u8Pin);
				break;
			case DIO_PORT_C:
				CLR_BIT(PORTC,Copy_u8Pin);
				break;
			case DIO_PORT_D:
				CLR_BIT(PORTD,Copy_u8Pin);
				break;
			default:
				local_u8errStatus = RT_NOK ;
			}
		}
		else if(Copy_u8Val == DIO_PIN_HIGH)
		{
			switch(Copy_u8Port)
			{
			case DIO_PORT_A:
				SET_BIT(PORTA,Copy_u8Pin);
				break;
			case DIO_PORT_B:
				SET_BIT(PORTB,Copy_u8Pin);
				break;
			case DIO_PORT_C:
				SET_BIT(PORTC,Copy_u8Pin);
				break;
			case DIO_PORT_D:
				SET_BIT(PORTD,Copy_u8Pin);
				break;
			default:
				local_u8errStatus = RT_NOK ;
			}
		}
		else
		{
			local_u8errStatus = RT_NOK ;
		}
	}
	else
	{
		local_u8errStatus = RT_NOK ;
	}
	return local_u8errStatus ;
}
/**********************************************************************************/
/* Description     : Get pin value					          */
/* Input Arguments : u8 Copy_u8Port , u8 Copy_u8Pin , u8* Copy_pu8Val		  */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8getPinVal(u8 Copy_u8Port , u8 Copy_u8Pin , u8* Copy_pu8Val)
{
	u8 local_u8errStatus = RT_OK ;
	if(Copy_u8Pin >= DIO_PIN_0 && Copy_u8Pin <= DIO_PIN_7 )
	{
		switch(Copy_u8Port)
		{
		case DIO_PORT_A:
			*Copy_pu8Val=GET_BIT(PINA,Copy_u8Pin);
			break;
		case DIO_PORT_B:
			*Copy_pu8Val=GET_BIT(PINB,Copy_u8Pin);
			break;
		case DIO_PORT_C:
			*Copy_pu8Val=GET_BIT(PINC,Copy_u8Pin);
			break;
		case DIO_PORT_D:
			*Copy_pu8Val=GET_BIT(PIND,Copy_u8Pin);
			break;
		default:
			local_u8errStatus = RT_NOK ;
		}
	}
	else
	{
		local_u8errStatus = RT_NOK ;
	}
	return local_u8errStatus ;
}
/**********************************************************************************/
/* Description     : Toggle current pin value					  */
/* Input Arguments : u8 Copy_u8Port , u8 Copy_u8Pin			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 DIO_u8togglePinVal(u8 Copy_u8Port , u8 Copy_u8Pin)
{
	u8 local_u8errStatus = RT_OK;
	if(Copy_u8Pin >= DIO_PIN_0 && Copy_u8Pin <= DIO_PIN_7 )
	{
		switch(Copy_u8Port)
		{
		case DIO_PORT_A:
			TOGGLE_BIT(PORTA,Copy_u8Pin);
			break;
		case DIO_PORT_B:
			TOGGLE_BIT(PORTB,Copy_u8Pin);
			break;
		case DIO_PORT_C:
			TOGGLE_BIT(PORTC,Copy_u8Pin);
			break;
		case DIO_PORT_D:
			TOGGLE_BIT(PORTD,Copy_u8Pin);
			break;
		default:
			local_u8errStatus = RT_NOK ;
		}
	}
	else
	{
		local_u8errStatus = RT_NOK ;
	}
	return local_u8errStatus ;
}
