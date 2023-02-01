/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Nov 7, 2021              	*/
/*              SWC              : GIE				*/
/*              Description	 : GIE Program	                */
/* 	        Version          : V1.0                         */
/****************************************************************/

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/STD_ERRORS.h"

#include "GIE_Interface.h"
#include "GIE_Private.h"
#include "GIE_Config.h"

/**********************************************************************************/
/* Description     : Enable/Disable Global Interrupt 	   			  */
/* Input Arguments : u8 Copy_u8Flag		  			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 GIE_u8EnableGlobalInterrupt(u8 Copy_u8Flag)
{
	u8 local_u8errStatus = RT_OK ;
	if(Copy_u8Flag == GIE_ENABLE || Copy_u8Flag == GIE_DISABLE)
	{
		switch(Copy_u8Flag)
		{
		case GIE_ENABLE:
			SREG |= Copy_u8Flag;
			break;
		case GIE_DISABLE:
			SREG &= Copy_u8Flag;
			break;
		}
	}
	else
	{
		local_u8errStatus = RT_NOK ;
	}
	return(local_u8errStatus);
}

