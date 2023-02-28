/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Feb 27, 2023               	*/
/*              SWC              : WatchDog Timer		*/
/*              Description	 : WatchDog Timer Interface     */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_WDT_INTERFACE_H_
#define MCAL_WDT_INTERFACE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	   INTERFACE MACROS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Watchdog Timer Possible Prescaler Values at Vcc = 5.0V */
#define WDT_16K_16300us                                    1
#define WDT_32K_32500us	                                   2
#define WDT_64K_65ms	                                   3
#define WDT_128K_130ms                                     4
#define WDT_256K_260ms                                     5
#define WDT_512K_520ms                                     6
#define WDT_1024K_1s                                       7
#define WDT_2048K_2s                                       8


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 FUNCTIONS PROTOTYPES		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Enable WatchDog Timer					  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void WDT_vidEnable(void);
/**********************************************************************************/
/* Description     : Disable WatchDog Timer					  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void WDT_vidDisable(void);
/**********************************************************************************/
/* Description     : Set WatchDog Timer in sleep mode for a specific time	  */
/* Input Arguments : u8 Copy_u8SleepTime				          */
/* Return          : u8							          */
/**********************************************************************************/
u8 WDT_u8Sleep(u8 Copy_u8SleepTime);

#endif /* MCAL_WDT_INTERFACE_H_ */
