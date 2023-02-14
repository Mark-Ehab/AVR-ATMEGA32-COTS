/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Jan 17, 2022               	*/
/*              SWC              : PORT				*/
/*              Description	 : PORT Interface               */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_PORT_INTERFACE_H_
#define MCAL_PORT_INTERFACE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 FUNCTIONS PROTOTYPES		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize each pin of AVR Atmega32 ports			  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void PORT_vidInit(void);

#endif /* MCAL_PORT_INTERFACE_H_ */
