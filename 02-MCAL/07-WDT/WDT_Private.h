/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Feb 27, 2023               	*/
/*              SWC              : WatchDog Timer		*/
/*              Description	 : WatchDog Timer Private       */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_WDT_PRIVATE_H_
#define MCAL_WDT_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            PORT REGISTERS DEFINITIONS		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

#define WDTCR							    *((volatile u8*)0x41) /* Watchdog Timer Control Register */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                              SOME BITS DEFINITIONS		 	             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Some Bit Definitions of Watchdog Timer Control Register (WDTCR) */
#define WDTCR_WDE						    3 /* Watchdog Enable */


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	   PRIVATE MACROS				     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Mask of WDT Prescaler Bits */
#define WDT_PRESCALER_MASK 					    0b11111000

/* Watchdog Timer Prescaler Values at Vcc = 5.0V */
#define WDT_PRESCALER_16K_16300us                                   0b00000000
#define WDT_PRESCALER_32K_32500us	                            0b00000001
#define WDT_PRESCALER_64K_65ms	                                    0b00000010
#define WDT_PRESCALER_128K_130ms                                    0b00000011
#define WDT_PRESCALER_256K_260ms                                    0b00000100
#define WDT_PRESCALER_512K_520ms                                    0b00000101
#define WDT_PRESCALER_1024K_1s                                      0b00000110
#define WDT_PRESCALER_2048K_2s                                      0b00000111

/* Watchdog Timer Disable Sequence Steps */
#define WDT_DISABLE_STEP1					    0b00011000
#define WDT_DISABLE_STEP2					    0b00000000

#endif /* MCAL_WDT_PRIVATE_H_ */
