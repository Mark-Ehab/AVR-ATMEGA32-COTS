/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Jan 17, 2022               	*/
/*              Description	 : Service Functions Program    */
/* 	        Version          : V1.0                         */
/****************************************************************/

#include "STD_TYPES.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  PUBLIC FUNCTIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : This function is used to map a value in some input range to  */
/*		     its equivalent value in output range			  */
/* Input Arguments : s32 Copy_s32InputMin  , s32 Copy_s32InputMax, 	          */
/* 		     s32 Copy_u32OutputMin , s32 Copy_s32OutputMax, 		  */
/* 		     s32 Copy_s32InputVal			   		  */
/* Return          : s32                 	      			          */
/**********************************************************************************/
s32 SERV_s32Map(  s32 Copy_s32InputMin  , s32 Copy_s32InputMax
		, s32 Copy_s32OutputMin , s32 Copy_s32OutputMax
		, s32 Copy_s32InputVal )
{
	/* Local Variables Definitions */
	s32 Local_s32MappingResult; /* Holds the mapping result */
	f32 Local_f32Slope = (f32)(Copy_s32OutputMax - Copy_s32OutputMin)/(f32)(Copy_s32InputMax - Copy_s32InputMin); /* Slope */

	/* Get Mapping Result From the Following Straight-Line Equation */
	Local_s32MappingResult = (Local_f32Slope * (f32)Copy_s32InputVal) - (Local_f32Slope * (f32)Copy_s32InputMin) + (f32)Copy_s32OutputMin ;

	return Local_s32MappingResult;
}
/**********************************************************************************/
/* Description     : Function to get modulus of two numbers			  */
/* Input Arguments : f32 Copy_f32Num1 , f32 Copy_f32Num2		          */
/* Return          : f32						          */
/**********************************************************************************/
f32 SERV_f32Mod(f32 Copy_f32Num1 , f32 Copy_f32Num2)
{
	/* Local Variables Definitions */
	f32 Local_f32Result;  		 	/* A variable to hold the result */

	/* Calculate the modulus */
        f32 Local_f32Result = Copy_f32Num1 - ((u32)(Copy_f32Num1/Copy_f32Num2) * Copy_f32Num2);

	return Local_f32Result;
}
/**********************************************************************************/
/* Description     : Function to get ceil of the result of two dividend numbers   */
/* Input Arguments : f32 Copy_f32Num1 , f32 Copy_f32Num2		          */
/* Return          : u32  	        	      			          */
/**********************************************************************************/
u32 SERV_u32CeilDev(f32 Copy_f32Num1 , f32 Copy_f32Num2)
{
	/* Local Variables Definitions */
	u32 Local_u32Result;			/* A variable to hold result after ceiling */

	/* Calculate result then ceil it */
	Local_u32Result = (u32)(Copy_f32Num1/Copy_f32Num2) + (SERV_f32Mod(Copy_f32Num1,Copy_f32Num2)!= 0);

	return Local_u32Result;
}
/**********************************************************************************/
/* Description     : Function to get the power of a number		          */
/* Input Arguments : u32 Copy_u32Base , u32 Copy_u32Power		          */
/* Return          : u32  	        	      			          */
/**********************************************************************************/
u32 SERV_u32Pow(u32 Copy_u32Base , u32 Copy_u32Power)
{
	/* Local Variables Definitions */
	u32 Local_u32Result ;              /* A variable to hold result of power process of passed number */

	/* Initialize Local_u32Result to be equal to 1 */
	Local_u32Result = 1;

	/* Check if passed power value equal 0 or not */
	if(Copy_u32Power != 0)
	{
		/* Calculate the power of passed number */
		while(Copy_u32Power != 0)
		{
		    /* Decrease power value */
		    Copy_u32Power --;

		    /* Get the result */
		    Local_u32Result *= Copy_u32Base;
		}
	}

	return Local_u32Result;
}
