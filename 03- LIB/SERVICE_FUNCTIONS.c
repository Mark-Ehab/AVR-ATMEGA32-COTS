/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Jan 17, 2022               	*/
/*              Description	 : Service Functions Program    */
/* 	        Version          : V1.0                         */
/****************************************************************/

#include "STD_TYPES.h"

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
	/* Define Some Local Variables */
	s32 Local_s32MappingResult; /* Holds the mapping result */
	f32 Local_f32Slope = (f32)(Copy_s32OutputMax - Copy_s32OutputMin)/(f32)(Copy_s32InputMax - Copy_s32InputMin); /* Slope */

	/* Get Mapping Result From the Following Straight-Line Equation */
	Local_s32MappingResult = (Local_f32Slope * (f32)Copy_s32InputVal) - (Local_f32Slope * (f32)Copy_s32InputMin) + (f32)Copy_s32OutputMin ;

	return Local_s32MappingResult;
}
