/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Mar 1, 2023               	*/
/*              SWC              : USART	        	*/
/*              Description	 : USART Interface              */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_USART_INTERFACE_H_
#define MCAL_USART_INTERFACE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 NEW TYPES DEFINITIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Define a new enum for USART Frame Errors */
typedef enum
{
	NO_ERROR      =    0,
	FRAME_ERROR   =    1,
	DATA_OVERRUN  =    2,
	PARITY_ERROR  =    3

}USART_FrameError_e;

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 FUNCTIONS PROTOTYPES		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize USART Communication Protocol		          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void USART_vidInit(void);
/**********************************************************************************/
/* Description     : Enable USART Rx Complete Interrupt 		          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void USART_vidEnableRxCompleteInterrupt(void);
/**********************************************************************************/
/* Description     : Disable USART Rx Complete Interrupt 		          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void USART_vidDisableRxCompleteInterrupt(void);
/**********************************************************************************/
/* Description     : Enable USART Data Register Empty Interrupt 	          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void USART_vidEnableDataRegisterEmptyInterrupt(void);
/**********************************************************************************/
/* Description     : Disable USART Data Register Empty Interrupt 	          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void USART_vidDisableDataRegisterEmptyInterrupt(void);
/**********************************************************************************/
/* Description     : Enable USART Tx Complete Interrupt 		          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void USART_vidEnableTxCompleteInterrupt(void);
/**********************************************************************************/
/* Description     : Disable USART Tx Complete Interrupt 		          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void USART_vidDisableTxCompleteInterrupt(void);
/**********************************************************************************/
/* Description     : Send one byte or 9-bit data through USART synchronously      */
/* 		     through busy-waiting over USART Data Register Empty (UDRE)   */
/*		     bit to check if data transmission buffer (TXB) is empty or   */
/*		     not and once is empty begin sending data			  */
/* Input Arguments : u16 Copy_u16Data				                  */
/* Return          : u8 						          */
/**********************************************************************************/
u8 USART_u8SendDataSync(u16 Copy_u16Data);
/**********************************************************************************/
/* Description     : Send one byte or 9-bit data through USART asynchronously     */
/* 		     when hardware generates an interrupt once data transmission  */
/*		     buffer (TXB) is empty				          */
/* Input Arguments : u16 Copy_u16Data , 					  */
/* 		     void(*Copy_pvDataRegisterEmptyNotificationFunc)(void) ,	  */
/*		     void(*Copy_pvTxCompleteNotificationFunc)(void)		  */
/* Return          : u8 						          */
/**********************************************************************************/
u8 USART_u8SendDataAsync(u16 Copy_u16Data , void(*Copy_pvDataRegisterEmptyNotificationFunc)(void) , void(*Copy_pvTxCompleteNotificationFunc)(void));
/**********************************************************************************/
/* Description     : Send string through USART synchronously			  */
/* Input Arguments : u8* Copy_pu8StringToBeSend					  */
/* Return          : u8 						          */
/**********************************************************************************/
u8 USART_u8SendStringSync(u8* Copy_pu8StringToBeSend);
/**********************************************************************************/
/* Description     : Send string through USART asynchronously			  */
/* Input Arguments : u8* Copy_pu8StringToBeSend , 				  */
/* 		     void(*Copy_pvDataRegisterEmptyNotificationFunc)(void) , 	  */
/*      	     void(*Copy_pvTxCompleteNotificationFunc)(void)		  */
/* Return          : u8 						          */
/**********************************************************************************/
u8 USART_u8SendStringAsync(u8* Copy_pu8StringToBeSend , void(*Copy_pvDataRegisterEmptyNotificationFunc)(void) , void(*Copy_pvTxCompleteNotificationFunc)(void));
/**********************************************************************************/
/* Description     : Receive one byte or 9-bit data through USART synchronously	  */
/*		     through busy-waiting over USART Receive Complete (RXC) bit   */
/*		     to check if USART reception process is completed and once	  */
/*		     is done begin reading data			        	  */
/* Input Arguments : u16* Copy_pu16DataToBeReceived,				  */
/*		     USART_FrameError_e* Copy_ErrorType_pe		          */
/* Return          : u8							          */
/**********************************************************************************/
u8 USART_u8ReceiveDataSync(u16* Copy_pu16DataToBeReceived , USART_FrameError_e* Copy_ErrorType_pe);
/**********************************************************************************/
/* Description     : Receive one byte or 9-bit data through USART asynchronously  */
/*		     when hardware generates an interrupt once USART reception    */
/*		     process is completed					  */
/* Input Arguments : u16* Copy_pu16DataToBeReceived,				  */
/*		     USART_FrameError_e* Copy_ErrorType_pe,			  */
/*		     void(*Copy_pvNotificationFunc)(void)			  */
/* Return          : u8							          */
/**********************************************************************************/
u8 USART_u8ReceiveDataAsync(u16* Copy_pu16DataToBeReceived , USART_FrameError_e* Copy_ErrorType_pe , void(*Copy_pvNotificationFunc)(void));
/**********************************************************************************/
/* Description     : Receive string through USART synchronously		 	  */
/* Input Arguments : u8* Copy_pu8StringToBeReceived,			          */
/* 		     USART_FrameError_e* Copy_ErrorType_pe,			  */
/* Return          : u8 						          */
/**********************************************************************************/
u8 USART_u8ReceiveStringSync(u8* Copy_pu8StringToBeReceived , USART_FrameError_e* Copy_ErrorType_pe);
/**********************************************************************************/
/* Description     : Receive string through USART asynchronously		  */
/* Input Arguments : u8* Copy_pu8StringToBeReceived,			          */
/* 		     USART_FrameError_e* Copy_ErrorType_pe,			  */
/* 		     void(*Copy_pvNotificationFunc)(void)			  */
/* Return          : u8 						          */
/**********************************************************************************/
u8 USART_u8ReceiveStringAsync(u8* Copy_pu8StringToBeReceived , USART_FrameError_e* Copy_ErrorType_pe , void(*Copy_pvNotificationFunc)(void));

#endif /* MCAL_USART_INTERFACE_H_ */