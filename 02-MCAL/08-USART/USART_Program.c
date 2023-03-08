/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Mar 1, 2023               	*/
/*              SWC              : USART	        	*/
/*              Description	 : USART Program                */
/* 	        Version          : V1.0                         */
/****************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_ERRORS.h"
#include "../../LIB/SERVICE_FUNCTIONS.h"

#include "USART_Interface.h"
#include "USART_Private.h"
#include "USART_Config.h"

#define ENTER_KEY_ASCII 13

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            GLOBAL VARIABLES DEFINITIONS	                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

static u8   Global_u8USART_CharacterTransmission_Status = USART_CHARACTER_TRANSMISSION_IDLE;  	/* Initialize USART character transmission status as idle */
static u8   Global_u8USART_CharacterReception_Status = USART_CHARACTER_RECEPTION_IDLE;  	/* Initialize USART character reception status as idle */
static u8   Global_u8USART_StringTransmission_Status = USART_STRING_TRANSMISSION_IDLE;          /* Initialize USART string transmission status as idle */
static u8   Global_u8USART_StringReception_Status = USART_STRING_RECEPTION_IDLE;  	        /* Initialize USART string reception status as idle */
static u8   Global_u8DataRegisterEmptyISR_Source;		          	                /* Variable to hold USART Data Register Empty ISR Source Whether from single character or a string */
static u8   Global_u8RxCompleteISR_Source;		        	  	                /* Variable to hold USART Rx Complete ISR Source Whether from single character or a string */
static u16  Global_u16DataToBeSend;             		          	                /* Variable to hold data to be send through USART */
static u8*  Global_pu8StringToBeSend = NULL;				  	                /* A pointer to char to hold address of string to be send asynchronously through USART */
static u16* Global_pu16DataToBeReceived = NULL;             		   	                /* A pointer to u16 to hold address of data be received asynchronously through USART */
static u8*  Global_pu8StringToBeReceived = NULL;				                /* A pointer to char to hold address of string to be received asynchronously through USART */
static u32  Global_u32TranmissionIterationCounter;				                /* Variable to hold the index of current character of string to be send asynchronously through USART */
static u32  Global_u32ReceptionIterationCounter;				                /* Variable to hold the index of current character of string to be received asynchronously through USART */
static void (*USART_pvRxCompleteNotificationFunc)(void) = NULL;		                        /* A pointer to function to hold the address of USART Rx Complete callback function */
static void (*USART_pvDataRegisterEmptyNotificationFunc)(void) = NULL; 	                        /* A pointer to function to hold the address of Data Register Empty callback function */
static void (*USART_pvTxCompleteNotificationFunc)(void) = NULL; 	  	                /* A pointer to function to hold the address of USART Tx Complete callback function */
static USART_FrameError_e* Global_USART_FrameError_pe = NULL;			                /* A pointer to struct of type USART_FrameError_e to hold address of variable of same type that will tell if there any transmission errors at reception or not */

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  PUBLIC FUNCTIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize USART Communication Protocol		          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void USART_vidInit(void)
{
	/******************************************Local Variables Definitions*****************************************/
	u8 Local_u8UCSRC_RegisterClone = 0 ;       /* A variable to hold the value that will be assigned directly to UCSRC Register */
	u8 Local_u8UBRRH_RegisterClone = 0 ;       /* A variable to hold the value that will be assigned directly to UBRRH Register */
	u16 Local_u16UBRValue = 0;                 /* A variable to hold calculated USART Baud Rate Value that will be assigned directly to UBRRH and UBRRL Registera */


	/******************************************Set USART Mode*****************************************/
	/* Check USART Selected Mode From Config File (Asynchronous or Synchronous) */
	#if   USART_MODE == ASYNCHRONOUS_MODE

		/* Set 7th bit of Local_u8UCSRC_RegisterClone (URSEL) */
		SET_BIT(Local_u8UCSRC_RegisterClone,UCSRC_URSEL);

		/* Set USART to Work in Asynchronous Mode through Clearing 6th bit of Local_u8UCSRC_RegisterClone (UMSEL) */
		CLR_BIT(Local_u8UCSRC_RegisterClone,UCSRC_UMSEL);

		/* Check USART Selected Transmission Speed Mode From Config File (Normal Speed or Double Speed) */
		#if   USART_TRANSMISSION_SPEED_MODE == NORMAL_SPEED_MODE

			/* Set USART to Operate on Normal Speed */
			CLR_BIT(UCSRA,UCSRA_U2X);

			/* Check USART Selected Baud Rate Value From Config File */
			#if   USART_BAUDRATE_VAL == BAUDRATE_2400_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (16 * BAUDRATE_2400_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_4800_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (16 * BAUDRATE_4800_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_9600_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (16 * BAUDRATE_9600_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_14400_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (8 * BAUDRATE_14400_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_19200_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (8 * BAUDRATE_19200_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_28800_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (8 * BAUDRATE_28800_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_38400_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (8 * BAUDRATE_38400_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_57600_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (8 * BAUDRATE_57600_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_76800_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (8 * BAUDRATE_76800_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_115200_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (8 * BAUDRATE_115200_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_230400_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (8 * BAUDRATE_230400_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_250000_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (8 * BAUDRATE_250000_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_500000_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (8 * BAUDRATE_500000_bps)) - 1;

			#else
				#error " Wrong USART Baude Rate Value Configuration !"
			#endif

		#elif USART_TRANSMISSION_SPEED_MODE == DOUBLE_SPEED_MODE

			/* Set USART to Operate on Double Speed */
			SET_BIT(UCSRA,UCSRA_U2X)

			/* Check USART Selected Baud Rate Value From Config File */
			#if   USART_BAUDRATE_VAL == BAUDRATE_2400_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (16 * BAUDRATE_2400_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_4800_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (16 * BAUDRATE_4800_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_9600_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (16 * BAUDRATE_9600_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_14400_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (16 * BAUDRATE_14400_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_19200_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (16 * BAUDRATE_19200_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_28800_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (16 * BAUDRATE_28800_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_38400_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (u32)(16 * BAUDRATE_38400_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_57600_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (16 * BAUDRATE_57600_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_76800_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (16 * BAUDRATE_76800_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_115200_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (16 * BAUDRATE_115200_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_230400_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (16 * BAUDRATE_230400_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_250000_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (16 * BAUDRATE_250000_bps)) - 1;

			#elif USART_BAUDRATE_VAL == BAUDRATE_500000_bps

				/* Calculate USART Baude Rate Value */
				Local_u16UBRValue = (USART_FCPU / (16 * BAUDRATE_500000_bps)) - 1;

			#else
				#error " Wrong USART Baude Rate Value Configuration !"
			#endif

		#else
			#error " Wrong USART Transmission Speed Mode Configuration !"
		#endif

	#elif USART_MODE == SYNCHRONOUS_MODE

		/* Set 7th bit of Local_u8UCSRC_RegisterClone (URSEL) */
		SET_BIT(Local_u8UCSRC_RegisterClone,UCSRC_URSEL);

		/* Set USART to Work in Synchronous Mode through Setting 6th bit of Local_u8UCSRC_RegisterClone (UMSEL) */
		SET_BIT(Local_u8UCSRC_RegisterClone,UCSRC_UMSEL);

		/* Check USART Selected Baud Rate Value From Config File */
		#if   USART_BAUDRATE_VAL == BAUDRATE_2400_bps

			/* Calculate USART Baude Rate Value */
			Local_u16UBRValue = (USART_FCPU / (2 * BAUDRATE_2400_bps)) - 1;

		#elif USART_BAUDRATE_VAL == BAUDRATE_4800_bps

			/* Calculate USART Baude Rate Value */
			Local_u16UBRValue = (USART_FCPU / (2 * BAUDRATE_4800_bps)) - 1;

		#elif USART_BAUDRATE_VAL == BAUDRATE_9600_bps

			/* Calculate USART Baude Rate Value */
			Local_u16UBRValue = (USART_FCPU / (2 * BAUDRATE_9600_bps)) - 1;

		#elif USART_BAUDRATE_VAL == BAUDRATE_14400_bps

			/* Calculate USART Baude Rate Value */
			Local_u16UBRValue = (USART_FCPU / (2 * BAUDRATE_14400_bps)) - 1;

		#elif USART_BAUDRATE_VAL == BAUDRATE_19200_bps

			/* Calculate USART Baude Rate Value */
			Local_u16UBRValue = (USART_FCPU / (2 * BAUDRATE_19200_bps)) - 1;

		#elif USART_BAUDRATE_VAL == BAUDRATE_28800_bps

			/* Calculate USART Baude Rate Value */
			Local_u16UBRValue = (USART_FCPU / (2 * BAUDRATE_28800_bps)) - 1;

		#elif USART_BAUDRATE_VAL == BAUDRATE_38400_bps

			/* Calculate USART Baude Rate Value */
			Local_u16UBRValue = (USART_FCPU / (2 * BAUDRATE_38400_bps)) - 1;

		#elif USART_BAUDRATE_VAL == BAUDRATE_57600_bps

			/* Calculate USART Baude Rate Value */
			Local_u16UBRValue = (USART_FCPU / (2 * BAUDRATE_57600_bps)) - 1;

		#elif USART_BAUDRATE_VAL == BAUDRATE_76800_bps

			/* Calculate USART Baude Rate Value */
			Local_u16UBRValue = (USART_FCPU / (2 * BAUDRATE_76800_bps)) - 1;

		#elif USART_BAUDRATE_VAL == BAUDRATE_115200_bps

			/* Calculate USART Baude Rate Value */
			Local_u16UBRValue = (USART_FCPU / (2 * BAUDRATE_115200_bps)) - 1;

		#elif USART_BAUDRATE_VAL == BAUDRATE_230400_bps

			/* Calculate USART Baude Rate Value */
			Local_u16UBRValue = (USART_FCPU / (2 * BAUDRATE_230400_bps)) - 1;

		#elif USART_BAUDRATE_VAL == BAUDRATE_250000_bps

			/* Calculate USART Baude Rate Value */
			Local_u16UBRValue = (USART_FCPU / (2 * BAUDRATE_250000_bps)) - 1;

		#elif USART_BAUDRATE_VAL == BAUDRATE_500000_bps

			/* Calculate USART Baude Rate Value */
			Local_u16UBRValue = (USART_FCPU / (2 * BAUDRATE_500000_bps)) - 1;

		#else
			#error " Wrong USART Baude Rate Value Configuration !"
		#endif

	#else
		#error " Wrong USART Operating Mode Configuration ! "
	#endif


	/******************************************Set USART Communication Mode*****************************************/
	/* Check Selected USART Communication Mode from config file (Single Processor or Multi Processor) */
	#if   USART_COMMUNICATION_MODE == SINGLE_PROCESSOR_MODE

		/* Enable Single Processor Mode Through Clearing Multi-processor Communication Mode (MPCM) bit in UCSRA */
		CLR_BIT(UCSRA,UCSRA_MPCM);

	#elif USART_COMMUNICATION_MODE == MULTI_PROCESSOR_MODE

		/* Enable Multi Processor Mode Through Setting Multi-processor Communication Mode (MPCM) bit in UCSRA */
		SET_BIT(UCSRA,UCSRA_MPCM);

	#else
		#error " Wrong USART Communication Mode Configuration ! "
	#endif


	/******************************************Set USART Data Direction*****************************************/
	/* Check Selected USART Data Direction from Config File */
	#if   USART_DATA_DIRECTION == SIMPLEX_TX

		/* Enable Transmitter */
		SET_BIT(UCSRB,UCSRB_TXEN);

	#elif USART_DATA_DIRECTION == SIMPLIX_RX

		/* Enable Receiver */
		SET_BIT(UCSRB,UCSRB_RXEN);

	#elif USART_DATA_DIRECTION == FULL_DUPLEX_TX_RX

		/* Enable Transmitter */
		SET_BIT(UCSRB,UCSRB_TXEN);

		/* Enable Receiver */
		SET_BIT(UCSRB,UCSRB_RXEN);

	#else
		#error " Wrong USART Data Direction Configuration ! "
	#endif


	/******************************************Set USART Parity Mode*****************************************/
	/* Check Selected USART Parity Mode from Config File  */
	#if   USART_PARITY_MODE == DISABLED

		/* Disable Parity Bit in USART Frame */
		CLR_BIT(Local_u8UCSRC_RegisterClone , UCSRC_UPM0);
		CLR_BIT(Local_u8UCSRC_RegisterClone , UCSRC_UPM1);

	#elif USART_PARITY_MODE == EVEN_PARITY

		/* Enable Even Parity  */
		CLR_BIT(Local_u8UCSRC_RegisterClone , UCSRC_UPM0);
		SET_BIT(Local_u8UCSRC_RegisterClone , UCSRC_UPM1);

	#elif USART_PARITY_MODE == ODD_PARITY

		/* Enable Odd Parity  */
		SET_BIT(Local_u8UCSRC_RegisterClone , UCSRC_UPM0);
		SET_BIT(Local_u8UCSRC_RegisterClone , UCSRC_UPM1);

	#else
		#error " Wrong USART Parity Mode Configuration ! "
	#endif


	/******************************************Set USART Stop Bits*****************************************/
	/* Check Selected Number of Stop Bits in USART Frame from Config File */
	#if   USART_STOP_BITS == ONE_STOP_BIT

		/* Set One Stop Bit in USART Frame */
		CLR_BIT(Local_u8UCSRC_RegisterClone , UCSRC_USBS);

	#elif USART_STOP_BITS == TWO_STOP_BITS

		/* Set Two Stop Bits in USART Frame */
		CLR_BIT(Local_u8UCSRC_RegisterClone , UCSRC_USBS);

	#else
		#error " Wrong Number of Stop Bits Configuration ! "
	#endif


	/******************************************Set USART Character Size*****************************************/
	/* Check Selected USART Character Size from Config File */
	#if   USART_CHARACTER_SIZE == FIVE_BITS

		/* Set Character Size to Five Bits */
		CLR_BIT(Local_u8UCSRC_RegisterClone , UCSRC_UCSZ0);
		CLR_BIT(Local_u8UCSRC_RegisterClone , UCSRC_UCSZ1);
		CLR_BIT(UCSRB , UCSRB_UCSZ2);

	#elif USART_CHARACTER_SIZE == SIX_BITS

		/* Set Character Size to Six Bits */
		SET_BIT(Local_u8UCSRC_RegisterClone , UCSRC_UCSZ0);
		CLR_BIT(Local_u8UCSRC_RegisterClone , UCSRC_UCSZ1);
		CLR_BIT(UCSRB , UCSRB_UCSZ2);

	#elif USART_CHARACTER_SIZE == SEVEN_BITS

		/* Set Character Size to Seven Bits */
		CLR_BIT(Local_u8UCSRC_RegisterClone , UCSRC_UCSZ0);
		SET_BIT(Local_u8UCSRC_RegisterClone , UCSRC_UCSZ1);
		CLR_BIT(UCSRB , UCSRB_UCSZ2);

	#elif USART_CHARACTER_SIZE == EIGHT_BITS

		/* Set Character Size to Eight Bits (1 Byte) */
		SET_BIT(Local_u8UCSRC_RegisterClone , UCSRC_UCSZ0);
		SET_BIT(Local_u8UCSRC_RegisterClone , UCSRC_UCSZ1);
		CLR_BIT(UCSRB , UCSRB_UCSZ2);

	#elif USART_CHARACTER_SIZE == NINE_BITS

		/* Set Character Size to Nine Bits */
		SET_BIT(Local_u8UCSRC_RegisterClone , UCSRC_UCSZ0);
		SET_BIT(Local_u8UCSRC_RegisterClone , UCSRC_UCSZ1);
		SET_BIT(UCSRB , UCSRB_UCSZ2);

	#else
		#error " Wrong USART Character Size Configuration ! "
	#endif


	/******************************************Enable/Disable USART Interrupts*****************************************/
	/* Check if USART Rx Complete Interrupt is Enabled or Not */
	#if   USART_RX_COMPLETE_INTERRUPT_ENABLE == ENABLE

		/* Enable USART Rx Complete Interrupt */
		SET_BIT(UCSRB , UCSRB_RXCIE);

	#elif USART_RX_COMPLETE_INTERRUPT_ENABLE == DISABLE

		/* Disable USART Rx Complete Interrupt */
		CLR_BIT(UCSRB , UCSRB_RXCIE);

	#else
		#error " Wrong USART Rx Complete Interrupt Enable Signal Configuration !"
	#endif

	/* Check if USART Data Register Empty Interrupt is Enabled or Not */
	#if   USART_DATA_REGISTER_EMPTY_INTERRUPT_ENABLE == ENABLE

		/* Enable USART Data Register Empty Interrupt */
		SET_BIT(UCSRB , UCSRB_UDRIE);

	#elif USART_DATA_REGISTER_EMPTY_INTERRUPT_ENABLE == DISABLE

		/* Disable USART Data Register Empty Interrupt */
		CLR_BIT(UCSRB , UCSRB_UDRIE);

	#else
		#error " Wrong USART Data Register Empty Interrupt Enable Signal Configuration !"
	#endif

	/* Check if USART Tx Complete Interrupt is Enabled or Not */
	#if   USART_TX_COMPLETE_INTERRUPT_ENABLE == ENABLE

		/* Enable USART Tx Complete Interrupt */
		SET_BIT(UCSRB , UCSRB_TXCIE);

	#elif USART_TX_COMPLETE_INTERRUPT_ENABLE == DISABLE

		/* Disable USART Tx Complete Interrupt */
		CLR_BIT(UCSRB , UCSRB_TXCIE);

	#else
		#error " Wrong USART Tx Complete Interrupt Enable Signal Configuration !"
	#endif


	/* Assign Local_u8UCSRC_RegisterClone Final Value to UCSRC Register */
	UCSRC = Local_u8UCSRC_RegisterClone;

	/* Set UBRRL Register */
	UBRRL = (u8)(Local_u16UBRValue);

	/* Set Local_u8UBRRH_RegisterClone Value */
	Local_u8UBRRH_RegisterClone = (u8)(Local_u16UBRValue >> 8);

	/* Clear 7th bit of Local_u8UBRRH_RegisterClone (URSEL) */
	CLR_BIT(Local_u8UBRRH_RegisterClone,UBRRH_URSEL);

	/* Assign Local_u8UBRRH_RegisterClone Final Value to UBRRH Register */
	UBRRH = Local_u8UBRRH_RegisterClone;
}
/**********************************************************************************/
/* Description     : Enable USART Rx Complete Interrupt 		          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void USART_vidEnableRxCompleteInterrupt(void)
{
	/* Enable USART Rx Complete Interrupt */
	SET_BIT(UCSRB , UCSRB_RXCIE);
}
/**********************************************************************************/
/* Description     : Disable USART Rx Complete Interrupt 		          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void USART_vidDisableRxCompleteInterrupt(void)
{
	/* Disable USART Rx Complete Interrupt */
	CLR_BIT(UCSRB , UCSRB_RXCIE);
}
/**********************************************************************************/
/* Description     : Enable USART Data Register Empty Interrupt 	          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void USART_vidEnableDataRegisterEmptyInterrupt(void)
{
	/* Enable USART Data Register Empty Interrupt */
	SET_BIT(UCSRB , UCSRB_UDRIE);
}
/**********************************************************************************/
/* Description     : Disable USART Data Register Empty Interrupt 	          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void USART_vidDisableDataRegisterEmptyInterrupt(void)
{
	/* Disable USART Data Register Empty Interrupt */
	CLR_BIT(UCSRB , UCSRB_UDRIE);
}
/**********************************************************************************/
/* Description     : Enable USART Tx Complete Interrupt 		          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void USART_vidEnableTxCompleteInterrupt(void)
{
	/* Enable USART Tx Complete Interrupt */
	SET_BIT(UCSRB , UCSRB_TXCIE);
}
/**********************************************************************************/
/* Description     : Disable USART Tx Complete Interrupt 		          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void USART_vidDisableTxCompleteInterrupt(void)
{
	/* Disable USART Tx Complete Interrupt */
	CLR_BIT(UCSRB , UCSRB_TXCIE);
}
/**********************************************************************************/
/* Description     : Send one byte or 9-bit data through USART synchronously      */
/* 		     through busy-waiting over USART Data Register Empty (UDRE)   */
/*		     bit to check if data transmission buffer (TXB) is empty or   */
/*		     not and once is empty begin sending data			  */
/* Input Arguments : u16 Copy_u16Data				                  */
/* Return          : u8 						          */
/**********************************************************************************/
u8 USART_u8SendDataSync(u16 Copy_u16Data)
{
	/* Local Variables Definitions */
	u8  Local_u8ErrorStatus = RT_OK;   /* A variable to hold function error status */
	u32 Local_u32TimeOutCounter = 0 ;  /* A variable to hold USART Timeout count */

	/* Check if USART Transmission Status is idle or busy */
	if(Global_u8USART_CharacterTransmission_Status == USART_CHARACTER_TRANSMISSION_BUSY)
	{
		/* This Function is Busy */
		Local_u8ErrorStatus = BUSY_FUNC;
	}
	else
	{
		/* Check if passed value is in range or not */
		if(Copy_u16Data > 512)
		{
			/* Function is not working as expected */
			Local_u8ErrorStatus = RT_NOK;
		}
		else
		{
			/* Set USART Transmission Status As Busy */
			Global_u8USART_CharacterTransmission_Status = USART_CHARACTER_TRANSMISSION_BUSY;

			/* Check if USART Data Register is Empty or Not Through Busy-Waiting Over USART Data Register Empty (UDRE) Bit */
			while((GET_BIT(UCSRA , UCSRA_UDRE) == 0) && (Local_u32TimeOutCounter < USART_TIMEOUT))
			{
				/* Increment USART Timeout Counter */
				Local_u32TimeOutCounter++;
			}

			/* Check if USART Reached Timeout or Not */
			if(Local_u32TimeOutCounter == USART_TIMEOUT)
			{
				/* Function is not working as expected */
				Local_u8ErrorStatus = RT_NOK;
			}
			else
			{
				#if   USART_CHARACTER_SIZE == FIVE_BITS || USART_CHARACTER_SIZE == SIX_BITS || USART_CHARACTER_SIZE == SEVEN_BITS || USART_CHARACTER_SIZE == EIGHT_BITS

					/* Set Passed Value To UDR Register To Start USART Transmission */
					UDR = (u8)(Copy_u16Data);

				#elif USART_CHARACTER_SIZE == NINE_BITS

					/* Assign 9th Bit Value to TXB8 Bit in UCSRB Register */
					UCSRB |= (((u8)(Copy_u16Data >> 8) & (0x01)) << UCSRB_TXB8);

					/* Set the Rest of 8 Bits To UDR Register To Start USART Transmission */
					UDR = (u8)(Copy_u16Data);

				#endif
			}

			/* Set USART Transmission Status As Idle */
			Global_u8USART_CharacterTransmission_Status = USART_CHARACTER_TRANSMISSION_IDLE;
		}

	}

	return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Send one byte or 9-bit data through USART asynchronously     */
/* 		     when hardware generates an interrupt once data transmission  */
/*		     buffer (TXB) is empty				          */
/* Input Arguments : u16 Copy_u16Data , 					  */
/* 		     void(*Copy_pvDataRegisterEmptyNotificationFunc)(void) ,	  */
/*		     void(*Copy_pvTxCompleteNotificationFunc)(void)		  */
/* Return          : u8 						          */
/**********************************************************************************/
u8 USART_u8SendDataAsync(u16 Copy_u16Data , void(*Copy_pvDataRegisterEmptyNotificationFunc)(void) , void(*Copy_pvTxCompleteNotificationFunc)(void))
{
	/* Local Variables Definitions */
	u8  Local_u8ErrorStatus = RT_OK;   /* A variable to hold function error status */

	/* Check if USART Transmission Status is idle or busy */
	if(Global_u8USART_CharacterTransmission_Status == USART_CHARACTER_TRANSMISSION_BUSY)
	{
		/* This Function is Busy */
		Local_u8ErrorStatus = BUSY_FUNC;
	}
	else
	{
		/* Check if Passed Pointers are NULL Pointers or Not */
		if(Copy_pvDataRegisterEmptyNotificationFunc == NULL || Copy_pvTxCompleteNotificationFunc == NULL)
		{
			/* Passed Pointer is a NULL Pointer */
			Local_u8ErrorStatus = NULL_POINTER;
		}
		else
		{
			/* Check if passed value is in range or not */
			if(Copy_u16Data > 512)
			{
				/* Function is not working as expected */
				Local_u8ErrorStatus = RT_NOK;
			}
			else
			{
				/* Set USART Transmission Status As Busy */
				Global_u8USART_CharacterTransmission_Status = USART_CHARACTER_TRANSMISSION_BUSY;

				/* Initialize Global_u16DataToBeSend */
				Global_u16DataToBeSend = Copy_u16Data;

				/* Register Data Register Empty Callback Function */
				USART_pvDataRegisterEmptyNotificationFunc = Copy_pvDataRegisterEmptyNotificationFunc;

				/* Register Tx Complete Callback Function */
				USART_pvTxCompleteNotificationFunc = Copy_pvTxCompleteNotificationFunc;

				/* Set Data Register Empty ISR Source */
				Global_u8DataRegisterEmptyISR_Source = USART_TRANSMISSION_SINGLE_CHARACTER_ASYNC;

				/* Enable USART Data Register Empty Interrupt */
				USART_vidEnableDataRegisterEmptyInterrupt();

				/* Enable USART Tx Complete Interrupt */
				USART_vidEnableTxCompleteInterrupt();
			}
		}
	}

	return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Send string through USART synchronously			  */
/* Input Arguments : u8* Copy_pu8StringToBeSend					  */
/* Return          : u8 						          */
/**********************************************************************************/
u8 USART_u8SendStringSync(u8* Copy_pu8StringToBeSend)
{
	/* Local Variables Definitions */
	u8  Local_u8ErrorStatus = RT_OK;  	 /* A variable to hold function error status */
	u32 Local_u32IterationCounter = 0;	 /* A variable to hold index of current character of passed string */

	/* Check if USART Transmission Status is idle or busy */
	if(Global_u8USART_StringTransmission_Status == USART_STRING_TRANSMISSION_BUSY)
	{
		/* This Function is Busy */
		Local_u8ErrorStatus = BUSY_FUNC;
	}
	else
	{
		/* Check if passed pointer is NULL pointer or not */
		if(Copy_pu8StringToBeSend == NULL)
		{
			/* Function is not working as expected */
			Local_u8ErrorStatus = NULL_POINTER;
		}
		else
		{
			/* Set USART Transmission Status As Busy */
			Global_u8USART_StringTransmission_Status = USART_STRING_TRANSMISSION_BUSY;

			/* Traverse the passed string characters to send it */
			while(Copy_pu8StringToBeSend[Local_u32IterationCounter] != '\0')
			{
				/* Send each string character synchronously */
				Local_u8ErrorStatus = USART_u8SendDataSync(Copy_pu8StringToBeSend[Local_u32IterationCounter]);

				/* Check Error Status */
				if(Local_u8ErrorStatus != RT_OK)
				{
					/* Break the loop and return a status error */
					break;
				}

				/* Increment Iteration Counter */
				Local_u32IterationCounter++;
			}

			/* Check Error Status */
			if(Local_u8ErrorStatus == RT_OK)
			{
				/* Send the string termination character '\0' */
				Local_u8ErrorStatus = USART_u8SendDataSync(Copy_pu8StringToBeSend[Local_u32IterationCounter]);
			}

			/* Set USART Transmission Status As Idle */
			Global_u8USART_StringTransmission_Status = USART_STRING_TRANSMISSION_IDLE;
		}
	}

	return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Send string through USART asynchronously			  */
/* Input Arguments : u8* Copy_pu8StringToBeSend , 				  */
/* 		     void(*Copy_pvDataRegisterEmptyNotificationFunc)(void) , 	  */
/*      	     void(*Copy_pvTxCompleteNotificationFunc)(void)		  */
/* Return          : u8 						          */
/**********************************************************************************/
u8 USART_u8SendStringAsync(u8* Copy_pu8StringToBeSend , void(*Copy_pvDataRegisterEmptyNotificationFunc)(void) , void(*Copy_pvTxCompleteNotificationFunc)(void))
{
	/* Local Variables Definitions */
	u8  Local_u8ErrorStatus = RT_OK;  	 /* A variable to hold function error status */

	/* Check if USART Transmission Status is idle or busy */
	if(Global_u8USART_StringTransmission_Status == USART_STRING_TRANSMISSION_BUSY)
	{
		/* This Function is Busy */
		Local_u8ErrorStatus = BUSY_FUNC;
	}
	else
	{
		/* Check if Passed Pointers are NULL Pointers or Not */
		if(Copy_pvDataRegisterEmptyNotificationFunc == NULL || Copy_pvTxCompleteNotificationFunc == NULL)
		{
			/* Passed Pointer is a NULL Pointer */
			Local_u8ErrorStatus = NULL_POINTER;
		}
		else
		{
			/* Set USART Transmission Status As Busy */
			Global_u8USART_StringTransmission_Status = USART_STRING_TRANSMISSION_BUSY;

			/* Initialize Global_pu8StringToBeSend */
			Global_pu8StringToBeSend = Copy_pu8StringToBeSend;

			/* Initialize Global_u32TranmissionIterationCounter */
			Global_u32TranmissionIterationCounter = 0;

			/* Register Data Register Empty Callback Function */
			USART_pvDataRegisterEmptyNotificationFunc = Copy_pvDataRegisterEmptyNotificationFunc;

			/* Register Tx Complete Callback Function */
			USART_pvTxCompleteNotificationFunc = Copy_pvTxCompleteNotificationFunc;

			/* Set Data Register Empty ISR Source */
			Global_u8DataRegisterEmptyISR_Source = USART_TRANSMISSION_STRING_ASYNC;

			/* Enable USART Data Register Empty Interrupt */
			USART_vidEnableDataRegisterEmptyInterrupt();
		}
	}

	return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Receive one byte or 9-bit data through USART synchronously	  */
/*		     through busy-waiting over USART Receive Complete (RXC) bit   */
/*		     to check if USART reception process is completed and once	  */
/*		     is done begin reading data			        	  */
/* Input Arguments : u16* Copy_pu16DataToBeReceived,				  */
/*		     USART_FrameError_e* Copy_ErrorType_pe		          */
/* Return          : u8							          */
/**********************************************************************************/
u8 USART_u8ReceiveDataSync(u16* Copy_pu16DataToBeReceived , USART_FrameError_e* Copy_ErrorType_pe)
{
	/* Local Variables Definitions */
	u8  Local_u8ErrorStatus = RT_OK;   /* A variable to hold function error status */
	u32 Local_u32TimeOutCounter = 0 ;  /* A variable to hold USART Timeout count */

	/* Check if USART Reception Status is idle or busy */
	if(Global_u8USART_CharacterReception_Status == USART_CHARACTER_RECEPTION_BUSY)
	{
		/* This Function is Busy */
		Local_u8ErrorStatus = BUSY_FUNC;
	}
	else
	{
		/* Check if Passed Pointers are NULL Pointers or Not */
		if(Copy_pu16DataToBeReceived == NULL || Copy_ErrorType_pe == NULL)
		{
			/* Passed Pointer is a NULL Pointer */
			Local_u8ErrorStatus = NULL_POINTER;
		}
		else
		{
			/* Set USART Reception Status As Busy */
			Global_u8USART_CharacterReception_Status = USART_CHARACTER_RECEPTION_BUSY;

			/* Check if USART Reception Process is Completed Through Busy-Waiting Over USART Receive Complete (RXC) Bit in UCSRA Register */
			while((GET_BIT(UCSRA , UCSRA_RXC) == 0) && (Local_u32TimeOutCounter < USART_TIMEOUT))
			{
				/* Increment USART Timeout Counter */
				Local_u32TimeOutCounter++;
			}

			/* Check if USART Reached Timeout or Not */
			if(Local_u32TimeOutCounter == USART_TIMEOUT)
			{
				/* Function is not working as expected */
				Local_u8ErrorStatus = RT_NOK;
			}
			else
			{
				/* Check if there's any errors in the received frame through USART */
				if(GET_BIT(UCSRA , UCSRA_FE) == 1)
				{
					/* There is a frame error */
					*Copy_ErrorType_pe = FRAME_ERROR;
				}
				else if(GET_BIT(UCSRA , UCSRA_DOR) == 1)
				{
					/* There is data overrun */
					*Copy_ErrorType_pe = DATA_OVERRUN;
				}
				else if(GET_BIT(UCSRA , UCSRA_DOR) == 1)
				{
					/* There is a parity error */
					*Copy_ErrorType_pe = PARITY_ERROR;
				}
				else
				{
					/* No error showed in received frame */
					*Copy_ErrorType_pe = NO_ERROR;

					#if   USART_CHARACTER_SIZE == FIVE_BITS || USART_CHARACTER_SIZE == SIX_BITS || USART_CHARACTER_SIZE == SEVEN_BITS || USART_CHARACTER_SIZE == EIGHT_BITS

						/* Read Received Character From UDR Register */
						*(u8*)Copy_pu16DataToBeReceived = UDR;

					#elif USART_CHARACTER_SIZE == NINE_BITS

						/* Read 9th Bit Value From RXB8 Bit in UCSRB Register */
						*Copy_pu16DataToBeReceived |= (GET_BIT(UCSRB , UCSRB_RXB8) << 8);

						/* Read the Rest of 8 Bits From UDR Register */
						*Copy_pu16DataToBeReceived |= UDR;

					#endif
				}
			}

			/* Set USART Reception Status As Idle */
			Global_u8USART_CharacterReception_Status = USART_CHARACTER_RECEPTION_IDLE;
		}
	}

	return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Receive one byte or 9-bit data through USART asynchronously  */
/*		     when hardware generates an interrupt once USART reception    */
/*		     process is completed					  */
/* Input Arguments : u16* Copy_pu16DataToBeReceived,				  */
/*		     USART_FrameError_e* Copy_ErrorType_pe,			  */
/*		     void(*Copy_pvNotificationFunc)(void)			  */
/* Return          : u8							          */
/**********************************************************************************/
u8 USART_u8ReceiveDataAsync(u16* Copy_pu16DataToBeReceived , USART_FrameError_e* Copy_ErrorType_pe , void(*Copy_pvNotificationFunc)(void))
{
	/* Local Variables Definitions */
	u8  Local_u8ErrorStatus = RT_OK;   /* A variable to hold function error status */

	/* Check if USART Reception Status is idle or busy */
	if(Global_u8USART_CharacterReception_Status == USART_CHARACTER_RECEPTION_BUSY)
	{
		/* This Function is Busy */
		Local_u8ErrorStatus = BUSY_FUNC;
	}
	else
	{
		/* Check if Passed Pointers are NULL Pointers or Not */
		if(Copy_pu16DataToBeReceived == NULL || Copy_ErrorType_pe == NULL || Copy_pvNotificationFunc == NULL)
		{
			/* Passed Pointer is a NULL Pointer */
			Local_u8ErrorStatus = NULL_POINTER;
		}
		else
		{
			/* Set USART Reception Status As Busy */
			Global_u8USART_CharacterReception_Status = USART_CHARACTER_RECEPTION_BUSY;

			/* Initialize Global_pu16DataToBeReceived */
			Global_pu16DataToBeReceived = Copy_pu16DataToBeReceived;

			/* Initialize Global_USART_FrameError_pe */
			Global_USART_FrameError_pe = Copy_ErrorType_pe;

			/* Register Rx Complete Callback Function */
			USART_pvRxCompleteNotificationFunc = Copy_pvNotificationFunc;

			/* Set Rx Complete ISR Source */
			Global_u8RxCompleteISR_Source = USART_RECEPTION_SINGLE_CHARACTER_ASYNC;

			/* Enable Rx Complete Interrupt */
			USART_vidEnableRxCompleteInterrupt();
		}
	}

	return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Receive string through USART synchronously		 	  */
/* Input Arguments : u8* Copy_pu8StringToBeReceived,			          */
/* 		     USART_FrameError_e* Copy_ErrorType_pe,			  */
/* Return          : u8 						          */
/**********************************************************************************/
u8 USART_u8ReceiveStringSync(u8* Copy_pu8StringToBeReceived , USART_FrameError_e* Copy_ErrorType_pe)
{
	/* Local Variables Definitions */
	u8  Local_u8ErrorStatus = RT_OK;  	 /* A variable to hold function error status */
	u32 Local_u32IterationCounter = 0;	 /* A variable to hold index of current character of received string */

	/* Check if USART Reception Status is idle or busy */
	if(Global_u8USART_StringReception_Status == USART_STRING_RECEPTION_BUSY)
	{
		/* This Function is Busy */
		Local_u8ErrorStatus = BUSY_FUNC;
	}
	else
	{
		/* Check if Passed Pointers are NULL Pointers or Not */
		if(Copy_pu8StringToBeReceived == NULL || Copy_ErrorType_pe == NULL)
		{
			/* Passed Pointer is a NULL Pointer */
			Local_u8ErrorStatus = NULL_POINTER;
		}
		else
		{
			/* Set USART Reception Status As Busy */
			Global_u8USART_StringReception_Status = USART_STRING_RECEPTION_BUSY;

			/* Receive the First Character */
			Local_u8ErrorStatus = USART_u8ReceiveDataSync((u16*)&Copy_pu8StringToBeReceived[Local_u32IterationCounter],Copy_ErrorType_pe);

			/* Check if any transmission error showed at first character reception */
			if(Local_u8ErrorStatus == RT_OK && *Copy_ErrorType_pe == NO_ERROR )
			{
				/* Receive until user presses enter */
				while(Copy_pu8StringToBeReceived[Local_u32IterationCounter] != ENTER_KEY_ASCII)
				{
					/* Increment Iterator Counter */
					Local_u32IterationCounter++;

					/* Receive the next character and store it in Copy_pu8StringToBeReceived array */
					Local_u8ErrorStatus = USART_u8ReceiveDataSync((u16*)&Copy_pu8StringToBeReceived[Local_u32IterationCounter],Copy_ErrorType_pe);

					/* Check if any transmission error showed */
					if(Local_u8ErrorStatus != RT_OK || *Copy_ErrorType_pe != NO_ERROR )
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

			/* Set USART Reception Status As Idle */
			Global_u8USART_StringReception_Status = USART_STRING_RECEPTION_IDLE;
		}
	}

	return Local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Receive string through USART asynchronously		  */
/* Input Arguments : u8* Copy_pu8StringToBeReceived,			          */
/* 		     USART_FrameError_e* Copy_ErrorType_pe,			  */
/* 		     void(*Copy_pvNotificationFunc)(void)			  */
/* Return          : u8 						          */
/**********************************************************************************/
u8 USART_u8ReceiveStringAsync(u8* Copy_pu8StringToBeReceived , USART_FrameError_e* Copy_ErrorType_pe , void(*Copy_pvNotificationFunc)(void))
{
	/* Local Variables Definitions */
	u8  Local_u8ErrorStatus = RT_OK;  	 /* A variable to hold function error status */

	/* Check if USART Reception Status is idle or busy */
	if(Global_u8USART_StringReception_Status == USART_STRING_RECEPTION_BUSY)
	{
		/* This Function is Busy */
		Local_u8ErrorStatus = BUSY_FUNC;
	}
	else
	{
		/* Check if Passed Pointers are NULL Pointers or Not */
		if(Copy_pu8StringToBeReceived == NULL || Copy_ErrorType_pe == NULL || Copy_pvNotificationFunc == NULL)
		{
			/* Passed Pointer is a NULL Pointer */
			Local_u8ErrorStatus = NULL_POINTER;
		}
		else
		{
			/* Set USART Reception Status As Busy */
			Global_u8USART_StringReception_Status = USART_STRING_RECEPTION_BUSY;

			/* Initialize Global_pu8StringToBeReceived */
			Global_pu8StringToBeReceived = Copy_pu8StringToBeReceived;

			/* Initialize Global_USART_FrameError_pe */
			Global_USART_FrameError_pe = Copy_ErrorType_pe;

			/* Register Rx Complete Callback Function */
			USART_pvRxCompleteNotificationFunc = Copy_pvNotificationFunc;

			/* Initialize Global_u32ReceptionIterationCounter */
			Global_u32ReceptionIterationCounter = 0;

			/* Set Rx Complete ISR Source */
			Global_u8RxCompleteISR_Source = USART_RECEPTION_STRING_ASYNC;

			/* Enable USART Rx Complete Interrupt */
			USART_vidEnableRxCompleteInterrupt();
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
/* 	   USART Rx Complete Interrupt		*/
/************************************************/
void __vector_13 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_13 (void)
{
	/* Check USART Rx Complete ISR Source */
	if(Global_u8RxCompleteISR_Source == USART_RECEPTION_SINGLE_CHARACTER_ASYNC)
	{
		/* Check if there's any errors in the received frame through USART */
		if(GET_BIT(UCSRA , UCSRA_FE) == 1)
		{
			/* There is a frame error */
			*Global_USART_FrameError_pe = FRAME_ERROR;
		}
		else if(GET_BIT(UCSRA , UCSRA_DOR) == 1)
		{
			/* There is data overrun */
			*Global_USART_FrameError_pe = DATA_OVERRUN;
		}
		else if(GET_BIT(UCSRA , UCSRA_DOR) == 1)
		{
			/* There is a parity error */
			*Global_USART_FrameError_pe = PARITY_ERROR;
		}
		else
		{
			/* No error showed in received frame */
			*Global_USART_FrameError_pe = NO_ERROR;

			#if   USART_CHARACTER_SIZE == FIVE_BITS || USART_CHARACTER_SIZE == SIX_BITS || USART_CHARACTER_SIZE == SEVEN_BITS || USART_CHARACTER_SIZE == EIGHT_BITS

				/* Read Received Character From UDR Register */
				*(u8*)Global_pu16DataToBeReceived = UDR;

			#elif USART_CHARACTER_SIZE == NINE_BITS

				/* Read 9th Bit Value From RXB8 Bit in UCSRB Register */
				*Global_pu16DataToBeReceived |= (GET_BIT(UCSRB , UCSRB_RXB8) << 8);

				/* Read the Rest of 8 Bits From UDR Register */
				*Global_pu16DataToBeReceived |= UDR;

			#endif
		}

		/* Set USART Reception Status As Idle */
		Global_u8USART_CharacterReception_Status = USART_CHARACTER_RECEPTION_IDLE;

		/* Disable USART Rx Complete Interrupt */
		USART_vidDisableRxCompleteInterrupt();

		/* Check if USART Rx Complete Notification Function is Registered or Not */
		if(USART_pvRxCompleteNotificationFunc != NULL)
		{
			/* Invoke USART Rx Complete Notification Function */
			USART_pvRxCompleteNotificationFunc();
		}
	}
	else if(Global_u8RxCompleteISR_Source == USART_RECEPTION_STRING_ASYNC)
	{
		/* Check if there's any errors in the received frame through USART */
		if(GET_BIT(UCSRA , UCSRA_FE) == 1)
		{
			/* There is a frame error */
			*Global_USART_FrameError_pe = FRAME_ERROR;

			/* Set USART Reception Status As Idle */
			Global_u8USART_StringReception_Status = USART_STRING_RECEPTION_IDLE;

			/* Disable USART Rx Complete Interrupt */
			USART_vidDisableRxCompleteInterrupt();

			/* Check if USART Rx Complete Notification Function is Registered or Not */
			if(USART_pvRxCompleteNotificationFunc != NULL)
			{
				/* Invoke USART Rx Complete Notification Function */
				USART_pvRxCompleteNotificationFunc();
			}
		}
		else if(GET_BIT(UCSRA , UCSRA_DOR) == 1)
		{
			/* There is data overrun */
			*Global_USART_FrameError_pe = DATA_OVERRUN;

			/* Set USART Reception Status As Idle */
			Global_u8USART_StringReception_Status = USART_STRING_RECEPTION_IDLE;

			/* Disable USART Rx Complete Interrupt */
			USART_vidDisableRxCompleteInterrupt();

			/* Check if USART Rx Complete Notification Function is Registered or Not */
			if(USART_pvRxCompleteNotificationFunc != NULL)
			{
				/* Invoke USART Rx Complete Notification Function */
				USART_pvRxCompleteNotificationFunc();
			}
		}
		else if(GET_BIT(UCSRA , UCSRA_DOR) == 1)
		{
			/* There is a parity error */
			*Global_USART_FrameError_pe = PARITY_ERROR;

			/* Set USART Reception Status As Idle */
			Global_u8USART_StringReception_Status = USART_STRING_RECEPTION_IDLE;

			/* Disable USART Rx Complete Interrupt */
			USART_vidDisableRxCompleteInterrupt();

			/* Check if USART Rx Complete Notification Function is Registered or Not */
			if(USART_pvRxCompleteNotificationFunc != NULL)
			{
				/* Invoke USART Rx Complete Notification Function */
				USART_pvRxCompleteNotificationFunc();
			}
		}
		else
		{
			/* No error showed in received frame */
			*Global_USART_FrameError_pe = NO_ERROR;

			/* Read Current Received String Character From UDR Register */
			Global_pu8StringToBeReceived[Global_u32ReceptionIterationCounter] = UDR;

			if(Global_pu8StringToBeReceived[Global_u32ReceptionIterationCounter] == ENTER_KEY_ASCII)
			{
				/* Clear Last Character */
				Global_pu8StringToBeReceived[Global_u32ReceptionIterationCounter] = '\0';

				/* Set USART Reception Status As Idle */
				Global_u8USART_StringReception_Status = USART_STRING_RECEPTION_IDLE;

				/* Disable USART Rx Complete Interrupt */
				USART_vidDisableRxCompleteInterrupt();

				/* Check if USART Rx Complete Notification Function is Registered or Not */
				if(USART_pvRxCompleteNotificationFunc != NULL)
				{
					/* Invoke USART Rx Complete Notification Function */
					USART_pvRxCompleteNotificationFunc();
				}
			}
			else
			{
				/* Increment Reception Iteration Counter */
				Global_u32ReceptionIterationCounter++;
			}
		}
	}
}
/************************************************/
/*      USART Data Register Empty Interrupt	*/
/************************************************/
void __vector_14 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_14 (void)
{
	/* Check USART Data Register Empty ISR Source */
	if(Global_u8DataRegisterEmptyISR_Source == USART_TRANSMISSION_SINGLE_CHARACTER_ASYNC)
	{
		#if   USART_CHARACTER_SIZE == FIVE_BITS || USART_CHARACTER_SIZE == SIX_BITS || USART_CHARACTER_SIZE == SEVEN_BITS || USART_CHARACTER_SIZE == EIGHT_BITS

			/* Set Data To Be Send To UDR Register To Start USART Transmission */
			UDR = (u8)(Global_u16DataToBeSend);

		#elif USART_CHARACTER_SIZE == NINE_BITS

			/* Assign 9th Bit Value to TXB8 Bit in UCSRB Register */
			UCSRB |= (((u8)(Global_u16DataToBeSend >> 8) & (0x01)) << UCSRB_TXB8);

			/* Set the Rest of 8 Bits To UDR Register To Start USART Transmission */
			UDR = (u8)(Global_u16DataToBeSend);

		#endif

		/* Disable USART Data Register Empty Interrupt */
		USART_vidDisableDataRegisterEmptyInterrupt();

		/* Check if USART Data Register Empty Notification Function is Registered or Not */
		if(USART_pvDataRegisterEmptyNotificationFunc != NULL)
		{
			/* Invoke USART Data Register Empty Notification Function */
			USART_pvDataRegisterEmptyNotificationFunc();
		}
	}
	else if(Global_u8DataRegisterEmptyISR_Source == USART_TRANSMISSION_STRING_ASYNC)
	{
		/* Set Current String Character To Be Send To UDR Register To Start USART Transmission */
		UDR = Global_pu8StringToBeSend[Global_u32TranmissionIterationCounter];

		/* Check if current character is the string termination character '\0' */
		if(Global_pu8StringToBeSend[Global_u32TranmissionIterationCounter] == '\0')
		{
			/* Enable USART Tx Complete Interrupt */
			USART_vidEnableTxCompleteInterrupt();

			/* Disable USART Data Register Empty Interrupt */
			USART_vidDisableDataRegisterEmptyInterrupt();

			/* Check if USART Data Register Empty Notification Function is Registered or Not */
			if(USART_pvDataRegisterEmptyNotificationFunc != NULL)
			{
				/* Invoke USART Data Register Empty Notification Function */
				USART_pvDataRegisterEmptyNotificationFunc();
			}
		}
		else
		{
			/* Increment Transmission Iterator Counter */
			Global_u32TranmissionIterationCounter++;
		}
	}
}
/************************************************/
/* 	   USART Tx Complete Interrupt		*/
/************************************************/
void __vector_15 (void) __attribute__ ((signal,used, externally_visible)) ; \
void __vector_15 (void)
{
	/* Check USART Data Register Empty ISR Source */
	if(Global_u8DataRegisterEmptyISR_Source == USART_TRANSMISSION_SINGLE_CHARACTER_ASYNC)
	{
		/* Set USART Transmission Status As Idle */
		Global_u8USART_CharacterTransmission_Status = USART_CHARACTER_TRANSMISSION_IDLE;
	}
	else if(Global_u8DataRegisterEmptyISR_Source == USART_TRANSMISSION_STRING_ASYNC)
	{
		/* Set USART Transmission Status As Idle */
		Global_u8USART_StringTransmission_Status = USART_STRING_TRANSMISSION_IDLE;
	}

	/* Disable USART Tx Complete Interrupt */
	USART_vidDisableTxCompleteInterrupt();

	/* Check if USART Tx Complete Notification Function is Registered or Not */
	if(USART_pvTxCompleteNotificationFunc != NULL)
	{
		/* Invoke USART Tx Complete Notification Function */
		USART_pvTxCompleteNotificationFunc();
	}
}