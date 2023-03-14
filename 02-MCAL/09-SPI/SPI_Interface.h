/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Mar 10, 2023               	*/
/*              SWC              : SPI  	        	*/
/*              Description	 : SPI Interface                */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef MCAL_SPI_INTERFACE_H_
#define MCAL_SPI_INTERFACE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 NEW TYPES DEFINITIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Define a new enum for SPI Transmission Errors */
typedef enum
{
	NO_ERROR      	  =    0,
	WRITE_COLLISION   =    1

}SPI_TransmissionError_e;

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 FUNCTIONS PROTOTYPES		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize Serial Peripheral Interface Communication	  */
/*		     Protocol (SPI) Based on Whether the Node is Master or Slave  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void SPI_vidInit(void);
/**********************************************************************************/
/* Description     : Enable Serial Transfer Complete Interrupt			  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void SPI_vidEnableSerialTransferCompleteInterrupt(void);
/**********************************************************************************/
/* Description     : Disable Serial Transfer Complete Interrupt			  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void SPI_vidDisableSerialTransferCompleteInterrupt(void);
/**********************************************************************************/
/* Description     : Send data over SPI synchronously through writing the data to */
/*		     be sent to start transmitting then busy-waiting over SPI 	  */
/* 		     Interrupt Flag (SPIF) bit to check if serial transfer is     */
/*		     completed or not						  */
/* Input Arguments : u8 Copy_u8DataToBeSend , 					  */
/* 		     SPI_TransmissionError_e* Copy_ErrorType_pe		          */
/* Return          : u8	 						          */
/**********************************************************************************/
u8 SPI_u8SendDataSync(u8 Copy_u8DataToBeSend , SPI_TransmissionError_e* Copy_ErrorType_pe);
/**********************************************************************************/
/* Description     : Send data over SPI asynchronously through writing the data   */
/* 		     to be sent to start transmitting then hardware generates an  */
/*		     interrupt once serial transfer is completed                  */
/* Input Arguments : u8 Copy_u8DataToBeSend ,                                     */
/* 		     SPI_TransmissionError_e* Copy_ErrorType_pe ,                 */
/*                   void (*Copy_pvNotificationFunc)(void)		          */
/* Return          : u8							          */
/**********************************************************************************/
u8 SPI_u8SendDataAsync(u8 Copy_u8DataToBeSend , SPI_TransmissionError_e* Copy_ErrorType_pe , void (*Copy_pvNotificationFunc)(void));
/**********************************************************************************/
/* Description     : Send string through SPI synchronously                        */
/* Input Arguments : u8* Copy_pu8StringToBeSend ,				  */
/* 		     SPI_TransmissionError_e* Copy_ErrorType_pe	                  */
/* Return          : u8 						          */
/**********************************************************************************/
u8 SPI_u8SendStringSync(u8* Copy_pu8StringToBeSend , SPI_TransmissionError_e* Copy_ErrorType_pe);
/**********************************************************************************/
/* Description     : Send string through SPI asynchronously                       */
/* Input Arguments : u8* Copy_pu8StringToBeSend ,  		                  */
/*		     SPI_TransmissionError_e* Copy_ErrorType_pe ,		  */
/*		     void (*Copy_pvNotificationFunc)(void))			  */
/* Return          : u8							          */
/**********************************************************************************/
u8 SPI_u8SendStringAsync(u8* Copy_pu8StringToBeSend , SPI_TransmissionError_e* Copy_ErrorType_pe , void (*Copy_pvNotificationFunc)(void));
/**********************************************************************************/
/* Description     : Receive data over SPI synchronously through busy-waiting     */
/*		     over SPI Interrupt Flag (SPIF) bit to check if serial        */
/*		     transfer is completed or not then read the received data 	  */
/*		     once data transfer is completed				  */
/* Input Arguments : u8* Copy_pu8DataToBeReceived , 				  */
/* 		     SPI_TransmissionError_e* Copy_ErrorType_pe   		  */
/* Return          : u8 						          */
/**********************************************************************************/
u8 SPI_u8ReceiveDataSync(u8* Copy_pu8DataToBeReceived , SPI_TransmissionError_e* Copy_ErrorType_pe);
/**********************************************************************************/
/* Description     : Receive data over SPI asynchronously through reading data    */
/*		     received when hardware generates an interrupt once serial	  */
/*		     transfer is completed				          */
/* Input Arguments : u8* Copy_pu8DataToBeReceived ,   		                  */
/*		     SPI_TransmissionError_e* Copy_ErrorType_pe	,		  */
/*		     void (*Copy_pvNotificationFunc)(void)                        */
/* Return          : u8 						          */
/**********************************************************************************/
u8 SPI_u8ReceiveDataAsync(u8* Copy_pu8DataToBeReceived , SPI_TransmissionError_e* Copy_ErrorType_pe , void (*Copy_pvNotificationFunc)(void));
/**********************************************************************************/
/* Description     : Receive string through SPI synchronously                     */
/* Input Arguments : u8* Copy_pu8StringToBeReceived ,			          */
/*		     SPI_TransmissionError_e* Copy_ErrorType_pe		          */
/* Return          : u8 						          */
/**********************************************************************************/
u8 SPI_u8ReceiveStringSync(u8* Copy_pu8StringToBeReceived , SPI_TransmissionError_e* Copy_ErrorType_pe);
/**********************************************************************************/
/* Description     : Receive string through SPI asynchronously                    */
/* Input Arguments : u8* Copy_pu8StringToBeReceived ,				  */
/*		     SPI_TransmissionError_e* Copy_ErrorType_pe	,		  */
/* 		     void (*Copy_pvNotificationFunc)(void)		          */
/* Return          : u8 						          */
/**********************************************************************************/
u8 SPI_u8ReceiveStringAsync(u8* Copy_pu8StringToBeReceived , SPI_TransmissionError_e* Copy_ErrorType_pe , void (*Copy_pvNotificationFunc)(void));


#endif /* MCAL_SPI_INTERFACE_H_ */