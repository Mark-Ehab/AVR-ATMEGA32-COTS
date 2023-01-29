/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Jan 17, 2022               	*/
/*              Description	 : Service Functions Interface  */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef LIB_SERVICE_FUNCTIONS_H
#define LIB_SERVICE_FUNCTIONS_H

                                                        /* Functions Prototypes */

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
		, s32 Copy_s32InputVal );

#endif /* LIB_SERVICE_FUNCTIONS_H */
