/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Oct 15, 2021               	*/
/*              SWC              : ADC				*/
/*              Description	 : ADC Interface                */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_ADC_INTERFACE_H_
#define MCAL_ADC_INTERFACE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                       DEFINING NEW TYPES FOR INTERFACING		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*
 * Define a new type for Chain ADC to define variables that holds chain parameters like :-
 * 1) Chain ID
 * 2) Chain Size
 * 3) Result Array
 * 4) Pointer to Chain ADC Complete Notification Function
 */
typedef struct
{
	u8*  ADC_pu8ChainID;
	u8   ADC_u8Size;
	u16* ADC_pu16ChainResult;
	void (*ADC_pvChainNotificationFunc)(void);
}ADC_Chain_s;

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	   INTERFACE MACROS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Single Ended ADC channels */
#define ADC_CH0            0    /* ADC Single-Ended Channel 0 */
#define ADC_CH1            1    /* ADC Single-Ended Channel 1 */
#define ADC_CH2            2    /* ADC Single-Ended Channel 2 */
#define ADC_CH3            3    /* ADC Single-Ended Channel 3 */
#define ADC_CH4            4    /* ADC Single-Ended Channel 4 */
#define ADC_CH5            5    /* ADC Single-Ended Channel 5 */
#define ADC_CH6            6    /* ADC Single-Ended Channel 6 */
#define ADC_CH7            7    /* ADC Single-Ended Channel 7 */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 FUNCTIONS PROTOTYPES		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize ADC peripheral with the pre-bulid configurations  */
/*                   stated in config file                                        */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void ADC_vidInit(void);
/**********************************************************************************/
/* Description     : This function starts ADC conversion through polling (busy-   */
/*                   waiting) on ADIF flag in ADCSRA register and performs only	  */
/* 		     a single conversion					  */
/* Input Arguments : u8 Copy_u8ChannelNum , u16* Copy_pu16Reading		  */
/* Return          : u8							          */
/* Note            : This function used for both 8-bit and 10-bit ADC resolutions */
/**********************************************************************************/
u8 ADC_u8GetAdcReadingSyncSingleConversion(u8 Copy_u8ChannelNum , u16* Copy_pu16Reading);
/**********************************************************************************/
/* Description     : This function starts ADC conversion and when conversion      */
/*                   completes, the hardware generates an interrupt to get the    */
/*                   ADC reading without busy-waiting the processor and performs  */
/* 		     a single conversion				  	  */
/* Input Arguments : u8 Copy_u8ChanelNum , u16 * Copy_pu16Reading,		  */
/*                   void(*Copy_pvAdcNotificationFunc)(void)			  */
/* Return          : u8								  */
/* Note            : This function used for both 8-bit and 10-bit ADC resolutions */
/**********************************************************************************/
u8 ADC_u8GetAdcReadingAsyncSingleConversion(u8 Copy_u8ChannelNum , u16* Copy_pu16Reading, void(*Copy_pvAdcNotificationFunc)(void));
/**********************************************************************************/
/* Description     : This function gets ADC conversion reading synchronously in   */
/*                   Free Running mode						  */
/* Input Arguments : u16* Copy_pu16Reading				          */
/* Return          : u8							          */
/* Note            : This function used for both 8-bit and 10-bit ADC resolutions */
/**********************************************************************************/
u8 ADC_u8GetAdcReadingSyncFreeRunning(u16* Copy_pu16Reading);
/**********************************************************************************/
/* Description     : This function gets ADC conversion reading asynchronously in  */
/*                   Free Running mode						  */
/* Input Arguments : u16 * Copy_pu16Reading,					  */
/* 		     void(*Copy_pvAdcNotificationFunc)(void)		  	  */
/* Return          : u8								  */
/* Note            : This function used for both 8-bit and 10-bit ADC resolutions */
/**********************************************************************************/
u8 ADC_u8GetAdcReadingAsyncFreeRunning(u16* Copy_pu16Reading, void(*Copy_pvAdcNotificationFunc)(void));
/**********************************************************************************/
/* Description     : This function gets ADC conversion chain reading in single    */
/* 		     conversion mode asynchronously  				  */
/* Input Arguments : ADC_Chain_s* Copy_Chain_ps					  */
/* Return          : u8								  */
/* Note            : This function used for both 8-bit and 10-bit ADC resolutions */
/**********************************************************************************/
u8 ADC_u8GetAdcReadingChainAsyncSingleConversion(ADC_Chain_s* Copy_Chain_ps);

#endif /*MCAL_ADC_INTERFACE_H_*/
