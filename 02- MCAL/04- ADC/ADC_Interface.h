/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Oct 15, 2021               	*/
/*              SWC              : ADC				*/
/*              Description	 : ADC Interface                */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_ADC_INTERFACE_H_
#define MCAL_ADC_INTERFACE_H_

                                /* Interface Macros */

/* Single Ended ADC channels */
#define ADC_CH0            0
#define ADC_CH1            1
#define ADC_CH2            2
#define ADC_CH3            3
#define ADC_CH4            4
#define ADC_CH5            5
#define ADC_CH6            6
#define ADC_CH7            7

                                /* Function Prototypes */

/**********************************************************************************/
/* Description     : Initialize ADC peripheral with the pre-bulid configurations  */
/*                   stated in config file                                        */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void ADC_vidInit(void);
/**********************************************************************************/
/* Description     : This function starts ADC conversion through polling (busy-   */
/*                   waiting) on ADIF flag in ADCSRA register			  */
/* Input Arguments : u8 Copy_u8ChanelNum				          */
/* Return          : u16						          */
/* Note            : This function used for both 8-bit and 10-bit ADC resolutions */
/**********************************************************************************/
u16 ADC_u16GetAdcReadingSync(u8 Copy_u8ChannelNum);
/**********************************************************************************/
/* Description     : This function starts ADC conversion and when conversion      */
/*                   completes, the hardware generates an interrupt to get the    */
/*                   ADC reading without busy-waiting the processor               */
/* Input Arguments : u8 Copy_u8ChanelNum , u16 * Copy_pu16Reading,		  */
/*                   void(*Copy_pvAdcFunc)(void)				  */
/* Return          : void							  */
/* Note            : This function used for both 8-bit and 10-bit ADC resolutions */
/**********************************************************************************/
void ADC_vidGetAdcReadingAsync(u8 Copy_u8ChannelNum , u16* Copy_pu16Reading, void(*Copy_pvAdcFunc)(void));
                          
#endif /*MCAL_ADC_INTERFACE_H_*/
