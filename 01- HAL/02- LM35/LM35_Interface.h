/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : JAN 23, 2023               	*/
/*              SWC              : LM35				*/
/*              Description	 : LM35 Interface               */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef HAL_LM35_INTERFACE_H_
#define HAL_LM35_INTERFACE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	   INTERFACE MACROS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Possible Analog Single Ended Channels to Which LM35 Can Connect */
#define LM35_CH0            0
#define LM35_CH1            1
#define LM35_CH2            2
#define LM35_CH3            3
#define LM35_CH4            4
#define LM35_CH5            5
#define LM35_CH6            6
#define LM35_CH7            7


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 FUNCTIONS PROTOTYPES		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize LM35			        		  */
/* Input Arguments : void			    			          */
/* Return          : void                       			          */
/**********************************************************************************/
void LM35_vidLM35Init(void);
/**********************************************************************************/
/* Description     : Get the temperature reading in celsius sensed by LM35        */
/*		     Temperature Sensor	synchronously			  	  */
/* Input Arguments : Copy_u8LM35ChannelNum	    			          */
/* Return          : u16	                      			          */
/**********************************************************************************/
u16 LM35_u16GetLM35ReadingSync(u8 Copy_u8LM35ChannelNum);
/**********************************************************************************/
/* Description     : Get the temperature reading in celsius sensed by LM35        */
/*		     Temperature Sensor	asynchronously			          */
/* Input Arguments : Copy_u8LM35ChannelNum , Copy_pu16LM35Reading,  		  */
/* 		     void(*Copy_pvLM35Func)(void)			    	  */
/* Return          : void	                      			          */
/**********************************************************************************/
void LM35_u16GetLM35ReadingAsync(u8 Copy_u8LM35ChannelNum , u16* Copy_pu16LM35Reading, void(*Copy_pvLM35Func)(void));

#endif /* HAL_LM35_INTERFACE_H_ */
