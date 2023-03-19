/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Jan 17, 2022               	*/
/*              Description	 : Service Functions Interface  */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef LIB_SERVICE_FUNCTIONS_H
#define LIB_SERVICE_FUNCTIONS_H

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 FUNCTIONS PROTOTYPES		                     */
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
		, s32 Copy_s32InputVal );
/**********************************************************************************/
/* Description     : Function to get modulus of two numbers			  */
/* Input Arguments : f32 Copy_f32Num1 , f32 Copy_f32Num2		          */
/* Return          : f32						          */
/**********************************************************************************/
f32 SERV_f32Mod(f32 Copy_f32Num1 , f32 Copy_f32Num2);
/**********************************************************************************/
/* Description     : Function to get ceil of the result of two dividend numbers   */
/* Input Arguments : f32 Copy_f32Num1 , f32 Copy_f32Num2		          */
/* Return          : u32  	        	      			          */
/**********************************************************************************/
u32 SERV_u32CeilDev(f32 Copy_f32Num1 , f32 Copy_f32Num2);
/**********************************************************************************/
/* Description     : Function to get the power of a number		          */
/* Input Arguments : u32 Copy_u32Base , u32 Copy_u32Power		          */
/* Return          : u32  	        	      			          */
/**********************************************************************************/
u32 SERV_u32Pow(u32 Copy_u32Base , u32 Copy_u32Power);

#endif /* LIB_SERVICE_FUNCTIONS_H */
