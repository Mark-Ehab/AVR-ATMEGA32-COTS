/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Mar 10, 2023               	*/
/*              SWC              : SPI  	        	*/
/*              Description	 : SPI Program                  */
/* 	        Version          : V1.0                         */
/****************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_ERRORS.h"
#include "../../LIB/SERVICE_FUNCTIONS.h"

#include "SPI_Interface.h"
#include "SPI_Private.h"
#include "SPI_Config.h"

#define ENTER_KEY_ASCII 13

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            GLOBAL VARIABLES DEFINITIONS	                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

static u8  Global_u8SPI_CharacterTransmission_Status = SPI_CHARACTER_TRANSMISSION_IDLE;        	/* Initialize SPI character transmission status as idle */
static u8  Global_u8SPI_CharacterReception_Status = SPI_CHARACTER_RECEPTION_IDLE;  	       	/* Initialize SPI character reception status as idle */
static u8  Global_u8SPI_StringTransmission_Status = SPI_STRING_TRANSMISSION_IDLE;              	/* Initialize SPI string transmission status as idle */
static u8  Global_u8SPI_StringReception_Status = SPI_STRING_RECEPTION_IDLE;  	       	       	/* Initialize SPI string reception status as idle */
static u8  Global_u8SerialTransferCompleteISR_Source;                                           /* Variable to hold SPI Serial Transfer Complete ISR Source Whether from single character or a string */
static u32 Global_u32TranmissionIterationCounter;				                /* Variable to hold the index of current character of string to be send asynchronously through SPI */
static u32 Global_u32ReceptionIterationCounter;				          	        /* Variable to hold the index of current character of string to be received asynchronously through SPI */
static u8* Global_pu8StringToBeSend = NULL;						     	/* A pointer to char to hold address of string to be sent asynchronously through SPI */
static u8* Global_pu8DataToBeReceived = NULL; 							/* A pointer to char to hold address of data be received asynchronously through SPI */
static u8* Global_pu8StringToBeReceived = NULL; 						/* A pointer to char to hold address of string to be received asynchronously through SPI */
static u8  Global_u8DummyData;									/* A variable to read SPDR register data after transmission is completed to clear WCOL flag */
static void (*SPI_pvSerialTranferCompleteNotificationFunction)(void);		               	/* A pointer to function to hold the address of Serial Transfer Complete callback function */
static SPI_TransmissionError_e* Global_SPI_TransmissionError_pe = NULL;		               	/* A pointer to struct of type SPI_TransmissionError_e to hold address of variable of same type that will tell if there any write collisions during SPI transmission or not */

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  PUBLIC FUNCTIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize Serial Peripheral Interface Communication	  */
/*		     Protocol (SPI) Based on Whether the Node is Master or Slave  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void SPI_vidInit(void)
{
	/******************************************Set SPI Node Mode (Master or Slave)*****************************************/
	/* Check Selected SPI Mode Type from Config File */
	#if   SPI_MODE == SPI_SLAVE_MODE

		/* Clear Master/Slave Select (MSTR) bit in SPCR register to make this node operate as slave */
		CLR_BIT(SPCR,SPCR_MSTR);

	#elif SPI_MODE == SPI_MASTER_MODE

		/* Set Master/Slave Select (MSTR) bit in SPCR register to make this node operate as master */
		SET_BIT(SPCR,SPCR_MSTR);

		/* Check Selected Clock Rate that Master will Generate from Config File */
		#if   SPI_CLOCK_RATE == FOSC_DIV_BY_4

			/* Set clock rate as fosc/4 */
			CLR_BIT(SPCR,SPCR_SPR0);
			CLR_BIT(SPCR,SPCR_SPR1);
			CLR_BIT(SPSR,SPSR_SPI2X);

		#elif SPI_CLOCK_RATE == FOSC_DIV_BY_16

			/* Set clock rate as fosc/16 */
			SET_BIT(SPCR,SPCR_SPR0);
			CLR_BIT(SPCR,SPCR_SPR1);
			CLR_BIT(SPSR,SPSR_SPI2X);

		#elif SPI_CLOCK_RATE == FOSC_DIV_BY_64

			/* Set clock rate as fosc/64 */
			CLR_BIT(SPCR,SPCR_SPR0);
			SET_BIT(SPCR,SPCR_SPR1);
			CLR_BIT(SPSR,SPSR_SPI2X);

		#elif SPI_CLOCK_RATE == FOSC_DIV_BY_128

			/* Set clock rate as fosc/128 */
			SET_BIT(SPCR,SPCR_SPR0);
			SET_BIT(SPCR,SPCR_SPR1);
			CLR_BIT(SPSR,SPSR_SPI2X);

		#elif SPI_CLOCK_RATE == FOSC_DOUBLE_DIV_BY_2

			/* Set clock rate as fosc/2 (Double Speed)*/
			CLR_BIT(SPCR,SPCR_SPR0);
			CLR_BIT(SPCR,SPCR_SPR1);
			SET_BIT(SPSR,SPSR_SPI2X);

		#elif SPI_CLOCK_RATE == FOSC_DOUBLE_DIV_BY_8

			/* Set clock rate as fosc/8 (Double Speed)*/
			SET_BIT(SPCR,SPCR_SPR0);
			CLR_BIT(SPCR,SPCR_SPR1);
			SET_BIT(SPSR,SPSR_SPI2X);

		#elif SPI_CLOCK_RATE == FOSC_DOUBLE_DIV_BY_32

			/* Set clock rate as fosc/32 (Double Speed)*/
			CLR_BIT(SPCR,SPCR_SPR0);
			SET_BIT(SPCR,SPCR_SPR1);
			SET_BIT(SPSR,SPSR_SPI2X);

		#elif SPI_CLOCK_RATE == FOSC_DOUBLE_DIV_BY_64

			/* Set clock rate as fosc/64 (Double Speed)*/
			SET_BIT(SPCR,SPCR_SPR0);
			SET_BIT(SPCR,SPCR_SPR1);
			SET_BIT(SPSR,SPSR_SPI2X);

		#else
			#error " Wrong Clock Rate Configuration ! "
		#endif

	#else
		#error " Wrong SPI Mode Configuration ! "
	#endif


	/******************************************Set SPI Data Order*****************************************/
	/* Check Selected SPI Data Order from Config File */
	#if   SPI_DATA_ORDER == TRANSMIT_LSB_FIRST

		/* Set Data Order (DORD) bit in SPCR register to make LSB of the data word be transmitted first */
		SET_BIT(SPCR,SPCR_DORD);

	#elif SPI_DATA_ORDER == TRANSMIT_MSB_FIRST

		/* Clear Data Order (DORD) bit in SPCR register to make MSB of the data word be transmitted first */
		CLR_BIT(SPCR,SPCR_DORD);

	#else
		#error " Wrong SPI Data Order Configuration ! "
	#endif


	/******************************************Set SPI Clock Polarity*****************************************/
	/* Check Selected SPI Clock Polarity from Config File */
	#if   SPI_CLOCK_POLARITY == RISING_LEADING_FALLING_TRAILING

		/* Clear Clock Polarity (CPOL) bit in SPCR register to set SPI idle state as low */
		CLR_BIT(SPCR,SPCR_CPOL);

	#elif SPI_CLOCK_POLARITY == FALIING_LEADING_RISING_TRAILING

		/* Set Clock Polarity (CPOL) bit in SPCR register to set SPI idle state as high */
		SET_BIT(SPCR,SPCR_CPOL);

	#else
		#error " Wrong SPI Clock Polarity Configuration ! "
	#endif


	/******************************************Set SPI Clock Phase*****************************************/
	/* Check Selected SPI Clock Phase from Config File */
	#if   SPI_CLOCK_PHASE == SAMPLE_LEADING_SETUP_TRAILING

		/* Clear Clock Phase (CPHA) bit in SPCR register to force SPI node to sample at leading edge and setup at trailing edge of clock */
		CLR_BIT(SPCR,SPCR_CPHA);

	#elif SPI_CLOCK_PHASE == SETUP_LEADING_SAMPLE_TRAILING

		/* Set Clock Phase (CPHA) bit in SPCR register to force SPI node to setup at leading edge and sample at trailing edge of clock */
		SET_BIT(SPCR,SPCR_CPHA);

	#else
		#error " Wrong SPI Clock Phase Configuration ! "
	#endif


	/******************************************Enable/Disable Serial Transfer Complete Interrupt*****************************************/
	/* Check if Serial Transfer Complete Interrupt is Enabled or Not */
	#if   SPI_SERIAL_TRANSFER_COMPLETE_INTERRUPT_ENABLE == ENABLE

		/* Enable Serial Transfer Complete Interrupt */
		SET_BIT(SPCR,SPCR_SPIE);

	#elif SPI_SERIAL_TRANSFER_COMPLETE_INTERRUPT_ENABLE == DISABLE

		/* Disable Serial Transfer Complete Interrupt */
		CLR_BIT(SPCR,SPCR_SPIE);

	#else
		#error " Wrong Serial Transfer Complete Interrupt Enable Signal Configuration ! "
	#endif


	/******************************************Enable SPI*****************************************/
	SET_BIT(SPCR,SPCR_SPE);

}
/**********************************************************************************/
/* Description     : Enable Serial Transfer Complete Interrupt			  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void SPI_vidEnableSerialTransferCompleteInterrupt(void)
{
	/* Enable Serial Transfer Complete Interrupt */
	SET_BIT(SPCR,SPCR_SPIE);
}
/**********************************************************************************/
/* Description     : Disable Serial Transfer Complete Interrupt			  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void SPI_vidDisableSerialTransferCompleteInterrupt(void)
{
	/* Disable Serial Transfer Complete Interrupt */
	CLR_BIT(SPCR,SPCR_SPIE);
}
/**********************************************************************************/
/* Description     : Send data over SPI synchronously through writing the data to */
/*		     be sent to start transmitting then busy-waiting over SPI 	  */
/* 		     Interrupt Flag (SPIF) bit to check if serial transfer is     */
/*		     completed or not						  */
/* Input Arguments : u8 Copy_u8DataToBeSend , 					  */
/* 		     SPI_TransmissionError_e* Copy_ErrorType_pe		          */
/* Return          : u8	 						          */
/**********************************************************************************/
u8 SPI_u8SendDataSync(u8 Copy_u8DataToBeSend , SPI_TransmissionError_e* Copy_ErrorType_pe)
{
	/* Local Variables Definitions */
	u8  Local_u8ErrorStatus = RT_OK;  	 /* A variable to hold function error status */
	u8  Local_u8DummyData;			 /* A variable to read SPDR register data after transmission is completed to clear both SPIF and WCOL flags */
	u32 Local_u32TimeOutCounter = 0 ;  	 /* A variable to hold SPI Timeout count */

	/* Check if SPI Character Transmission Status is Idle or Busy */
	if(Global_u8SPI_CharacterTransmission_Status == SPI_CHARACTER_TRANSMISSION_BUSY)
	{
		/* This Function is Busy */
		Local_u8ErrorStatus = BUSY_FUNC;
	}
	else
	{
		/* Check if Passed Pointer is NULL or Not */
		if(Copy_ErrorType_pe == NULL)
		{
			/* Passed Pointer is a NULL Pointer */
			Local_u8ErrorStatus = NULL_POINTER;
		}
		else
		{
			/* Set SPI Character Transmission Status As Busy */
			Global_u8SPI_CharacterTransmission_Status = SPI_CHARACTER_TRANSMISSION_BUSY;

			/* Write Passed Data To Be Sent in SPDR Register To Start Transmitting */
			SPDR = Copy_u8DataToBeSend;

			/* Check if there's write collision occurred or not */
			if(GET_BIT(SPSR,SPSR_WCOL) == 1)
			{
				/* Access SPDR Register Through Reading its Content to Clear WCOL Flag */
				Local_u8DummyData = SPDR;

				/* There is a write collision */
				*Copy_ErrorType_pe = WRITE_COLLISION;
			}
			else
			{
				/* Check if SPI Serial Transfer is Completed or Not Through Busy-Waiting Over SPI Interrupt Flag (SPIF) Bit */
				while((GET_BIT(SPSR,SPSR_SPIF) == 0) && (Local_u32TimeOutCounter < SPI_TIMEOUT))
				{
					/* Increment SPI Timeout Counter */
					Local_u32TimeOutCounter++;
				}

				/* Check if SPI Reached Timeout or Not */
				if(Local_u32TimeOutCounter == SPI_TIMEOUT)
				{
					/* Function is not working as expected */
					Local_u8ErrorStatus = RT_NOK;
				}
				else
				{
					/* Access SPDR Register Through Reading its Content to Clear SPIF Flag */
					Local_u8DummyData = SPDR;

					/* No Transmission Error Occurred */
					*Copy_ErrorType_pe = NO_ERROR;
				}
			}

			/* Set SPI Character Transmission Status As Idle */
			Global_u8SPI_CharacterTransmission_Status = SPI_CHARACTER_TRANSMISSION_IDLE;
		}
	}

	return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Send data over SPI asynchronously through writing the data   */
/* 		     to be sent to start transmitting then hardware generates an  */
/*		     interrupt once serial transfer is completed                  */
/* Input Arguments : u8 Copy_u8DataToBeSend ,                                     */
/* 		     SPI_TransmissionError_e* Copy_ErrorType_pe ,                 */
/*                   void (*Copy_pvNotificationFunc)(void)		          */
/* Return          : u8							          */
/**********************************************************************************/
u8 SPI_u8SendDataAsync(u8 Copy_u8DataToBeSend , SPI_TransmissionError_e* Copy_ErrorType_pe , void (*Copy_pvNotificationFunc)(void))
{
	/* Local Variables Definitions */
	u8  Local_u8ErrorStatus = RT_OK;  	 /* A variable to hold function error status */
	u8  Local_u8DummyData;			 /* A variable to read SPDR register data after transmission is completed to clear WCOL flag */


	/* Check if SPI Character Transmission Status is Idle or Busy */
	if(Global_u8SPI_CharacterTransmission_Status == SPI_CHARACTER_TRANSMISSION_BUSY)
	{
		/* This Function is Busy */
		Local_u8ErrorStatus = BUSY_FUNC;
	}
	else
	{
		/* Check if Passed Pointers are NULL or Not */
		if(Copy_ErrorType_pe == NULL || Copy_pvNotificationFunc == NULL)
		{
			/* Passed Pointer is a NULL Pointer */
			Local_u8ErrorStatus = NULL_POINTER;
		}
		else
		{
			/* Set SPI Character Transmission Status As Busy */
			Global_u8SPI_CharacterTransmission_Status = SPI_CHARACTER_TRANSMISSION_BUSY;

			/* Initialize Global_SPI_TransmissionError_pe */
			Global_SPI_TransmissionError_pe = Copy_ErrorType_pe;

			/* Register Serial Transfer Callback Function */
			SPI_pvSerialTranferCompleteNotificationFunction = Copy_pvNotificationFunc;

			/* Set Serial Transfer Complete ISR Source */
			Global_u8SerialTransferCompleteISR_Source = SPI_TRANSMISSION_SINGLE_CHARACTER_ASYNC;

			/* Write Passed Data To Be Sent in SPDR Register To Start Transmitting */
			SPDR = Copy_u8DataToBeSend;

			/* Check if there's write collision occurred or not */
			if(GET_BIT(SPSR,SPSR_WCOL) == 1)
			{
				/* Access SPDR Register Through Reading its Content to Clear WCOL Flag */
				Local_u8DummyData = SPDR;

				/* There is a write collision */
				*Global_SPI_TransmissionError_pe = WRITE_COLLISION;

				/* Set SPI Character Transmission Status As Idle */
				Global_u8SPI_CharacterTransmission_Status = SPI_CHARACTER_TRANSMISSION_IDLE;
			}
			else
			{
				/* Enable Serial Transfer Complete Interrupt */
				SPI_vidEnableSerialTransferCompleteInterrupt();
			}
		}
	}

	return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Send string through SPI synchronously                        */
/* Input Arguments : u8* Copy_pu8StringToBeSend ,				  */
/* 		     SPI_TransmissionError_e* Copy_ErrorType_pe	                  */
/* Return          : u8 						          */
/**********************************************************************************/
u8 SPI_u8SendStringSync(u8* Copy_pu8StringToBeSend , SPI_TransmissionError_e* Copy_ErrorType_pe)
{
	/* Local Variables Definitions */
	u8  Local_u8ErrorStatus = RT_OK;  	 /* A variable to hold function error status */
	u32 Local_u32IterationCounter = 0;	 /* A variable to hold index of current character of passed string */

	/* Check if SPI String Transmission Status is Idle or Busy */
	if(Global_u8SPI_StringTransmission_Status == SPI_STRING_TRANSMISSION_BUSY)
	{
		/* This Function is Busy */
		Local_u8ErrorStatus = BUSY_FUNC;
	}
	else
	{
		/* Check if Passed Pointers are NULL or Not */
		if(Copy_pu8StringToBeSend == NULL || Copy_ErrorType_pe == NULL)
		{
			/* Passed Pointer is a NULL Pointer */
			Local_u8ErrorStatus = NULL_POINTER;
		}
		else
		{
			/* Set SPI String Transmission Status As Busy */
			Global_u8SPI_StringTransmission_Status = SPI_STRING_TRANSMISSION_BUSY;

			/* Traverse the passed string characters to send it */
			while(Copy_pu8StringToBeSend[Local_u32IterationCounter] != '\0')
			{
				/* Send each string character synchronously */
				Local_u8ErrorStatus = SPI_u8SendDataSync(Copy_pu8StringToBeSend[Local_u32IterationCounter],Copy_ErrorType_pe);

				/* Check Error Status */
				if(Local_u8ErrorStatus != RT_OK || *Copy_ErrorType_pe == WRITE_COLLISION)
				{
					/* Break the loop and return a status error */
					break;
				}

				/* Increment Iteration Counter */
				Local_u32IterationCounter++;
			}

			/* Check Error Status */
			if(Local_u8ErrorStatus == RT_OK && *Copy_ErrorType_pe == NO_ERROR)
			{
				/* Send the string termination character '\0' */
				Local_u8ErrorStatus = SPI_u8SendDataSync(Copy_pu8StringToBeSend[Local_u32IterationCounter] , Copy_ErrorType_pe);
			}

			/* Set SPI String Transmission Status As Idle */
			Global_u8SPI_StringTransmission_Status = SPI_STRING_TRANSMISSION_IDLE;
		}
	}

	return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Send string through SPI asynchronously                       */
/* Input Arguments : u8* Copy_pu8StringToBeSend ,  		                  */
/*		     SPI_TransmissionError_e* Copy_ErrorType_pe ,		  */
/*		     void (*Copy_pvNotificationFunc)(void))			  */
/* Return          : u8							          */
/**********************************************************************************/
u8 SPI_u8SendStringAsync(u8* Copy_pu8StringToBeSend , SPI_TransmissionError_e* Copy_ErrorType_pe , void (*Copy_pvNotificationFunc)(void))
{
	/* Local Variables Definitions */
	u8  Local_u8ErrorStatus = RT_OK;  	 /* A variable to hold function error status */

	/* Check if SPI String Transmission Status is Idle or Busy */
	if(Global_u8SPI_StringTransmission_Status == SPI_STRING_TRANSMISSION_BUSY)
	{
		/* This Function is Busy */
		Local_u8ErrorStatus = BUSY_FUNC;
	}
	else
	{
		/* Check if Passed Pointers are NULL Pointers or Not */
		if(Copy_pu8StringToBeSend == NULL || Copy_ErrorType_pe == NULL || Copy_pvNotificationFunc == NULL)
		{
			/* Passed Pointer is a NULL Pointer */
			Local_u8ErrorStatus = NULL_POINTER;
		}
		else
		{
			/* Set SPI String Transmission Status As Busy */
			Global_u8SPI_StringTransmission_Status = SPI_STRING_TRANSMISSION_BUSY;

			/* Initialize Global_pu8DataToBeReceived */
			Global_pu8StringToBeSend = Copy_pu8StringToBeSend;

			/* Initialize Global_SPI_TransmissionError_pe */
			Global_SPI_TransmissionError_pe = Copy_ErrorType_pe;

			/* Initialize Global_u32TranmissionIterationCounter */
			Global_u32TranmissionIterationCounter = 0;

			/* Register Serial Transfer Callback Function */
			SPI_pvSerialTranferCompleteNotificationFunction = Copy_pvNotificationFunc;

			/* Set Serial Transfer Complete ISR Source */
			Global_u8SerialTransferCompleteISR_Source = SPI_TRANSMISSION_STRING_ASYNC;

			/* Write the first string character in SPDR register to start transmitting */
			SPDR = Global_pu8StringToBeSend[Global_u32TranmissionIterationCounter];

			/* Check if there's write collision occurred or not */
			if(GET_BIT(SPSR,SPSR_WCOL) == 1)
			{
				/* Access SPDR Register Through Reading its Content to Clear WCOL Flag */
				Global_u8DummyData = SPDR;

				/* There is a write collision */
				*Global_SPI_TransmissionError_pe = WRITE_COLLISION;

				/* Set SPI String Transmission Status As Idle */
				Global_u8SPI_StringTransmission_Status = SPI_STRING_TRANSMISSION_IDLE;
			}
			else
			{
				/* Enable Serial Transfer Complete Interrupt */
				SPI_vidEnableSerialTransferCompleteInterrupt();
			}
		}
	}

	return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Receive data over SPI synchronously through busy-waiting     */
/*		     over SPI Interrupt Flag (SPIF) bit to check if serial        */
/*		     transfer is completed or not then read the received data 	  */
/*		     once data transfer is completed				  */
/* Input Arguments : u8* Copy_pu8DataToBeReceived , 				  */
/* 		     SPI_TransmissionError_e* Copy_ErrorType_pe   		  */
/* Return          : u8 						          */
/**********************************************************************************/
u8 SPI_u8ReceiveDataSync(u8* Copy_pu8DataToBeReceived , SPI_TransmissionError_e* Copy_ErrorType_pe)
{
	/* Local Variables Definitions */
	u8  Local_u8ErrorStatus = RT_OK;  	 /* A variable to hold function error status */
	u8  Local_u8DummyData;			 /* A variable to read SPDR register data after transmission is completed to clear WCOL flag */
	u32 Local_u32TimeOutCounter = 0 ;  	 /* A variable to hold SPI Timeout count */

	/* Check if SPI Character Reception Status is Idle or Busy */
	if(Global_u8SPI_CharacterReception_Status == SPI_CHARACTER_RECEPTION_BUSY)
	{
		/* This Function is Busy */
		Local_u8ErrorStatus = BUSY_FUNC;
	}
	else
	{
		/* Check if Passed Pointers are NULL or Not */
		if(Copy_pu8DataToBeReceived == NULL || Copy_ErrorType_pe == NULL)
		{
			/* Passed Pointer is a NULL Pointer */
			Local_u8ErrorStatus = NULL_POINTER;
		}
		else
		{
			/* Set SPI Character Reception Status As Busy */
			Global_u8SPI_CharacterReception_Status = SPI_CHARACTER_RECEPTION_BUSY;

			/* Write a dummy value in SPDR register to start communication */
			SPDR = SPI_DUMMY_VALUE;

			/* Check if there's write collision occurred or not */
			if(GET_BIT(SPSR,SPSR_WCOL) == 1)
			{
				/* Access SPDR Register Through Reading its Content to Clear WCOL Flag */
				Local_u8DummyData = SPDR;

				/* There is a write collision */
				*Copy_ErrorType_pe = WRITE_COLLISION;
			}
			else
			{
				/* Check if SPI Serial Transfer is Completed or Not Through Busy-Waiting Over SPI Interrupt Flag (SPIF) Bit */
				while((GET_BIT(SPSR,SPSR_SPIF) == 0) && (Local_u32TimeOutCounter < SPI_TIMEOUT))
				{
					/* Increment SPI Timeout Counter */
					Local_u32TimeOutCounter++;
				}

				/* Check if SPI Reached Timeout or Not */
				if(Local_u32TimeOutCounter == SPI_TIMEOUT)
				{
					/* Function is not working as expected */
					Local_u8ErrorStatus = RT_NOK;
				}
				else
				{
					/* Read the received data and also clear SPIF flag */
					*Copy_pu8DataToBeReceived = SPDR;

					/* No Transmission Error Occurred */
					*Copy_ErrorType_pe = NO_ERROR;
				}
			}

			/* Set SPI Character Reception Status As Idle */
			Global_u8SPI_CharacterReception_Status = SPI_CHARACTER_RECEPTION_IDLE;
		}
	}

	return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Receive data over SPI asynchronously through reading data    */
/*		     received when hardware generates an interrupt once serial	  */
/*		     transfer is completed				          */
/* Input Arguments : u8* Copy_pu8DataToBeReceived ,   		                  */
/*		     SPI_TransmissionError_e* Copy_ErrorType_pe	,		  */
/*		     void (*Copy_pvNotificationFunc)(void)                        */
/* Return          : u8 						          */
/**********************************************************************************/
u8 SPI_u8ReceiveDataAsync(u8* Copy_pu8DataToBeReceived , SPI_TransmissionError_e* Copy_ErrorType_pe , void (*Copy_pvNotificationFunc)(void))
{
	/* Local Variables Definitions */
	u8  Local_u8ErrorStatus = RT_OK;  	 /* A variable to hold function error status */

	/* Check if SPI Character Reception Status is Idle or Busy */
	if(Global_u8SPI_CharacterReception_Status == SPI_CHARACTER_RECEPTION_BUSY)
	{
		/* This Function is Busy */
		Local_u8ErrorStatus = BUSY_FUNC;
	}
	else
	{
		/* Check if Passed Pointers are NULL or Not */
		if(Copy_pu8DataToBeReceived == NULL || Copy_ErrorType_pe == NULL || Copy_pvNotificationFunc == NULL)
		{
			/* Passed Pointer is a NULL Pointer */
			Local_u8ErrorStatus = NULL_POINTER;
		}
		else
		{
			/* Set SPI Character Reception Status As Busy */
			Global_u8SPI_CharacterReception_Status = SPI_CHARACTER_RECEPTION_BUSY;

			/* Initialize Global_pu8DataToBeReceived */
			Global_pu8DataToBeReceived = Copy_pu8DataToBeReceived;

			/* Initialize Global_SPI_TransmissionError_pe */
			Global_SPI_TransmissionError_pe = Copy_ErrorType_pe;

			/* Register Serial Transfer Callback Function */
			SPI_pvSerialTranferCompleteNotificationFunction = Copy_pvNotificationFunc;

			/* Set Serial Transfer Complete ISR Source */
			Global_u8SerialTransferCompleteISR_Source = SPI_RECEPTION_SINGLE_CHARACTER_ASYNC;

			/* Write a dummy value in SPDR register to start communication */
			SPDR = SPI_DUMMY_VALUE;

			/* Check if there's write collision occurred or not */
			if(GET_BIT(SPSR,SPSR_WCOL) == 1)
			{
				/* Access SPDR Register Through Reading its Content to Clear WCOL Flag */
				Global_u8DummyData = SPDR;

				/* There is a write collision */
				*Global_SPI_TransmissionError_pe = WRITE_COLLISION;

				/* Set SPI Character Reception Status As Idle */
				Global_u8SPI_CharacterReception_Status = SPI_CHARACTER_RECEPTION_IDLE;
			}
			else
			{
				/* Enable Serial Transfer Interrupt */
				SPI_vidEnableSerialTransferCompleteInterrupt();
			}
		}
	}
	return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Receive string through SPI synchronously                     */
/* Input Arguments : u8* Copy_pu8StringToBeReceived ,			          */
/*		     SPI_TransmissionError_e* Copy_ErrorType_pe		          */
/* Return          : u8 						          */
/**********************************************************************************/
u8 SPI_u8ReceiveStringSync(u8* Copy_pu8StringToBeReceived , SPI_TransmissionError_e* Copy_ErrorType_pe)
{
	/* Local Variables Definitions */
	u8  Local_u8ErrorStatus = RT_OK;  	 /* A variable to hold function error status */
	u32 Local_u32IterationCounter = 0;	 /* A variable to hold index of current character of received string */

	/* Check if SPI String Reception Status is Idle or Busy */
	if(Global_u8SPI_StringReception_Status == SPI_STRING_RECEPTION_BUSY)
	{
		/* This Function is Busy */
		Local_u8ErrorStatus = BUSY_FUNC;
	}
	else
	{
		/* Check if Passed Pointers are NULL or Not */
		if(Copy_pu8StringToBeReceived == NULL || Copy_ErrorType_pe == NULL)
		{
			/* Passed Pointer is a NULL Pointer */
			Local_u8ErrorStatus = NULL_POINTER;
		}
		else
		{
			/* Set SPI String Reception Status As Busy */
			Global_u8SPI_StringReception_Status = SPI_STRING_RECEPTION_BUSY;

			/* Receive the First Character */
			Local_u8ErrorStatus =  SPI_u8ReceiveDataSync(&Copy_pu8StringToBeReceived[Local_u32IterationCounter] , Copy_ErrorType_pe);

			/* Check Error Status */
			if(Local_u8ErrorStatus == RT_OK && *Copy_ErrorType_pe == NO_ERROR)
			{
				/* Receive until user presses enter */
				while(Copy_pu8StringToBeReceived[Local_u32IterationCounter] != ENTER_KEY_ASCII)
				{
					/* Increment Iterator Counter */
					Local_u32IterationCounter++;

					/* Receive the Next Character */
					Local_u8ErrorStatus =  SPI_u8ReceiveDataSync(&Copy_pu8StringToBeReceived[Local_u32IterationCounter] , Copy_ErrorType_pe);

					/* Check Error Status */
					if(Local_u8ErrorStatus == RT_NOK || *Copy_ErrorType_pe == WRITE_COLLISION)
					{
						/* Stop receiving characters, break the loop then return error */
						break;
					}
				}

				/* Check if any transmission error showed at last character reception */
				if(Local_u8ErrorStatus == RT_OK && *Copy_ErrorType_pe == NO_ERROR )
				{
					/* Clear Last Character */
					Copy_pu8StringToBeReceived[Local_u32IterationCounter] = '\0';
				}
			}

			/* Set SPI String Reception Status As Idle */
			Global_u8SPI_StringReception_Status = SPI_STRING_RECEPTION_IDLE;
		}
	}

	return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Receive string through SPI asynchronously                    */
/* Input Arguments : u8* Copy_pu8StringToBeReceived ,				  */
/*		     SPI_TransmissionError_e* Copy_ErrorType_pe	,		  */
/* 		     void (*Copy_pvNotificationFunc)(void)		          */
/* Return          : u8 						          */
/**********************************************************************************/
u8 SPI_u8ReceiveStringAsync(u8* Copy_pu8StringToBeReceived , SPI_TransmissionError_e* Copy_ErrorType_pe , void (*Copy_pvNotificationFunc)(void))
{
	/* Local Variables Definitions */
	u8  Local_u8ErrorStatus = RT_OK;  	 /* A variable to hold function error status */

	/* Check if SPI String Reception Status is Idle or Busy */
	if(Global_u8SPI_StringReception_Status == SPI_STRING_RECEPTION_BUSY)
	{
		/* This Function is Busy */
		Local_u8ErrorStatus = BUSY_FUNC;
	}
	else
	{
		/* Check if Passed Pointers are NULL or Not */
		if(Copy_pu8StringToBeReceived == NULL || Copy_ErrorType_pe == NULL || Copy_pvNotificationFunc == NULL)
		{
			/* Passed Pointer is a NULL Pointer */
			Local_u8ErrorStatus = NULL_POINTER;
		}
		else
		{
			/* Set SPI String Reception Status As Busy */
			Global_u8SPI_StringReception_Status = SPI_STRING_RECEPTION_BUSY;

			/* Initialize Global_pu8StringToBeReceived */
			Global_pu8StringToBeReceived = Copy_pu8StringToBeReceived;

			/* Initialize Global_SPI_TransmissionError_pe */
			Global_SPI_TransmissionError_pe = Copy_ErrorType_pe;

			/* Register Serial Transfer Callback Function */
			SPI_pvSerialTranferCompleteNotificationFunction = Copy_pvNotificationFunc;

			/* Initialize Global_u32ReceptionIterationCounter */
			Global_u32ReceptionIterationCounter = 0;

			/* Set Serial Transfer Complete ISR Source */
			Global_u8SerialTransferCompleteISR_Source = SPI_RECEPTION_STRING_ASYNC;

			/* Write a dummy value in SPDR register to start communication */
			SPDR = SPI_DUMMY_VALUE;

			/* Check if there's write collision occurred or not */
			if(GET_BIT(SPSR,SPSR_WCOL) == 1)
			{
				/* Access SPDR Register Through Reading its Content to Clear WCOL Flag */
				Global_u8DummyData = SPDR;

				/* There is a write collision */
				*Global_SPI_TransmissionError_pe = WRITE_COLLISION;

				/* Set SPI String Reception Status As Idle */
				Global_u8SPI_StringReception_Status = SPI_STRING_RECEPTION_IDLE;
			}
			else
			{
				/* Enable Serial Transfer Interrupt */
				SPI_vidEnableSerialTransferCompleteInterrupt();
			}
		}
	}

		return Local_u8ErrorStatus;
}

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            	  INTERRUPT HANDLERS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/************************************************/
/*      Serial Transfer Complete Interrupt	*/
/************************************************/
void __vector_12 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_12 (void)
{
	/* Check Serial Transfer Complete ISR Source */
	if(Global_u8SerialTransferCompleteISR_Source == SPI_TRANSMISSION_SINGLE_CHARACTER_ASYNC)
	{
		/* No Transmission Error Occurred */
		*Global_SPI_TransmissionError_pe = NO_ERROR;

		/* Set SPI Character Transmission Status As Idle */
		Global_u8SPI_CharacterTransmission_Status = SPI_CHARACTER_TRANSMISSION_IDLE;

		/* Disable Serial Transfer Complete Interrupt */
		SPI_vidDisableSerialTransferCompleteInterrupt();

		/* Check if Serial Transfer Complete Notification Function is Registered or Not */
		if(SPI_pvSerialTranferCompleteNotificationFunction != NULL)
		{
			/* Invoke Serial Transfer Complete Notification Function */
			SPI_pvSerialTranferCompleteNotificationFunction();
		}
	}
	else if(Global_u8SerialTransferCompleteISR_Source == SPI_TRANSMISSION_STRING_ASYNC)
	{
		/* No Transmission Error Occurred */
		*Global_SPI_TransmissionError_pe = NO_ERROR;

		/* Check if current character is the string termination character '\0' */
		if(Global_pu8StringToBeSend[Global_u32TranmissionIterationCounter] == '\0')
		{
			/* Set SPI String Transmission Status As Idle */
			Global_u8SPI_StringTransmission_Status = SPI_STRING_TRANSMISSION_IDLE;

			/* Disable Serial Transfer Complete Interrupt */
			SPI_vidDisableSerialTransferCompleteInterrupt();

			/* Check if Serial Transfer Complete Notification Function is Registered or Not */
			if(SPI_pvSerialTranferCompleteNotificationFunction != NULL)
			{
				/* Invoke Serial Transfer Complete Notification Function */
				SPI_pvSerialTranferCompleteNotificationFunction();
			}
		}
		else
		{
			/* Increment Global_u32TranmissionIterationCounter */
			Global_u32TranmissionIterationCounter++;

			/* Send Next String Character */
			SPDR = Global_pu8StringToBeSend[Global_u32TranmissionIterationCounter];

			/* Check if there's write collision occurred or not */
			if(GET_BIT(SPSR,SPSR_WCOL) == 1)
			{
				/* Access SPDR Register Through Reading its Content to Clear WCOL Flag */
				Global_u8DummyData = SPDR;

				/* There is a write collision */
				*Global_SPI_TransmissionError_pe = WRITE_COLLISION;

				/* Set SPI String Transmission Status As Idle */
				Global_u8SPI_StringTransmission_Status = SPI_STRING_TRANSMISSION_IDLE;

				/* Disable Serial Transfer Complete Interrupt */
				SPI_vidDisableSerialTransferCompleteInterrupt();
			}
		}
	}
	else if(Global_u8SerialTransferCompleteISR_Source == SPI_RECEPTION_SINGLE_CHARACTER_ASYNC)
	{
		/* Read the Received Character */
		*Global_pu8DataToBeReceived = SPDR;

		/* No Transmission Error Occurred */
		*Global_SPI_TransmissionError_pe = NO_ERROR;

		/* Set SPI Character Reception Status As Idle */
		Global_u8SPI_CharacterReception_Status = SPI_CHARACTER_RECEPTION_IDLE;

		/* Disable Serial Transfer Complete Interrupt */
		SPI_vidDisableSerialTransferCompleteInterrupt();

		/* Check if Serial Transfer Complete Notification Function is Registered or Not */
		if(SPI_pvSerialTranferCompleteNotificationFunction != NULL)
		{
			/* Invoke Serial Transfer Complete Notification Function */
			SPI_pvSerialTranferCompleteNotificationFunction();
		}
	}
	else if(Global_u8SerialTransferCompleteISR_Source == SPI_RECEPTION_STRING_ASYNC)
	{
		/* No Transmission Error Occurred */
		*Global_SPI_TransmissionError_pe = NO_ERROR;

		/* Read Received String Character */
		Global_pu8StringToBeReceived[Global_u32ReceptionIterationCounter] = SPDR;

		/* Check if Received Character is ENTER */
		if(Global_pu8StringToBeReceived[Global_u32ReceptionIterationCounter] == ENTER_KEY_ASCII)
		{
			/* Clear Last Character */
			Global_pu8StringToBeReceived[Global_u32ReceptionIterationCounter] = '\0';

			/* Set SPI String Reception Status As Idle */
			Global_u8SPI_StringReception_Status = SPI_STRING_RECEPTION_IDLE;

			/* Disable Serial Transfer Complete Interrupt */
			SPI_vidDisableSerialTransferCompleteInterrupt();

			/* Check if Serial Transfer Complete Notification Function is Registered or Not */
			if(SPI_pvSerialTranferCompleteNotificationFunction != NULL)
			{
				/* Invoke Serial Transfer Complete Notification Function */
				SPI_pvSerialTranferCompleteNotificationFunction();
			}
		}
		else
		{
			/* Increment Global_u32ReceptionIterationCounter */
			Global_u32ReceptionIterationCounter++;

			/* Write a dummy value in SPDR register to start communication and receive the next character */
			SPDR = SPI_DUMMY_VALUE;

			/* Check if there's write collision occurred or not */
			if(GET_BIT(SPSR,SPSR_WCOL) == 1)
			{
				/* Access SPDR Register Through Reading its Content to Clear WCOL Flag */
				Global_u8DummyData = SPDR;

				/* There is a write collision */
				*Global_SPI_TransmissionError_pe = WRITE_COLLISION;

				/* Set SPI String Reception Status As Idle */
				Global_u8SPI_StringReception_Status = SPI_STRING_RECEPTION_IDLE;

				/* Disable Serial Transfer Complete Interrupt */
				SPI_vidDisableSerialTransferCompleteInterrupt();
			}
		}
	}

}