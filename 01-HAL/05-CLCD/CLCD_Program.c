/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Sep 18, 2021               	*/
/*              SWC              : CLCD		        	*/
/*              Description	 : CLCD Program                 */
/* 	        Version          : V1.0                         */
/****************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_ERRORS.h"
#include "../../LIB/SERVICE_FUNCTIONS.h"

#include "../../MCAL/DIO/DIO_Interface.h"

#include "CLCD_Interface.h"
#include "CLCD_Private.h"
#include "CLCD_Config.h"

#include "util/delay.h"


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  PUBLIC FUNCTIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize Character LCD					  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidInit(void)
{
	/* Set control and data ports directions as output ports */
	DIO_u8setPortDir(CLCD_DATA_PORT,FULL_OUTPUT);
	DIO_u8setPortDir(CLCD_CTRL_PINS_PORT,0x07);

	_delay_ms(40);

	/* Set up CLCD on the 8-bit mode */
	CLCD_vidSetEightBitMode();

	_delay_ms(1);

	/* Display on CLCD and turn off cursor */
	CLCD_vidDisplayOnCursorOff();

	_delay_ms(1);

	/* Clear CLCD */
	CLCD_vidClearDisplay();

	_delay_ms(3);

	/* Setting up CLCD on entry mode */
	CLCD_vidSetEntryMode();

	_delay_ms(1);
}
/**********************************************************************************/
/* Description     : Send a command to Character LCD controller			  */
/* Input Arguments : u8 Copy_u8Command					          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidSendCommand(u8 Copy_u8Command)
{
	/* Set RS to LOW to tell CLCD to receive a command */
	DIO_u8setPinVal(CLCD_CTRL_PINS_PORT , CLCD_RS_PIN , LOW);

	/* Set RW to LOW to write on CLCD */
	DIO_u8setPinVal(CLCD_CTRL_PINS_PORT , CLCD_RW_PIN , LOW);

	/* Set E to tell CLCD to start reading the command */
	DIO_u8setPinVal(CLCD_CTRL_PINS_PORT , CLCD_E_PIN , HIGH);

	/* Send the Command */
	DIO_u8setPortVal(CLCD_DATA_PORT , Copy_u8Command);

	/* Clear E to tell CLCD to stop reading the command */
	DIO_u8setPinVal(CLCD_CTRL_PINS_PORT , CLCD_E_PIN , LOW);

	_delay_ms(2);
}
/**********************************************************************************/
/* Description     : Write a character on Character LCD				  */
/* Input Arguments : u8 Copy_u8Character				          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidWriteCharacter(u8 Copy_u8Character)
{
	/* Set RS to HIGH to tell CLCD to receive data */
	DIO_u8setPinVal(CLCD_CTRL_PINS_PORT , CLCD_RS_PIN , HIGH);

	/* Set RW to LOW to write on CLCD */
	DIO_u8setPinVal(CLCD_CTRL_PINS_PORT , CLCD_RW_PIN , LOW);

	/* Set E to tell CLCD to start reading the data */
	DIO_u8setPinVal(CLCD_CTRL_PINS_PORT , CLCD_E_PIN , HIGH);

	/* Send the Character */
	DIO_u8setPortVal(CLCD_DATA_PORT , Copy_u8Character);

	/* Clear E to tell CLCD to stop reading the data */
	DIO_u8setPinVal(CLCD_CTRL_PINS_PORT , CLCD_E_PIN , LOW);

	_delay_ms(2);
}
/**********************************************************************************/
/* Description     : Set up Character LCD on 8-bit mode			          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidSetEightBitMode(void)
{
	CLCD_vidSendCommand(CLCD_FUNCTION_SET_EIGHT_BIT_MODE_CMD);
}
/**********************************************************************************/
/* Description     : Set up Character LCD on 4-bit mode		                  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidSetFourBitMode(void)
{
	 CLCD_vidSendCommand(CLCD_FUNCTION_SET_FOUR_BIT_MODE_CMD);
}
/**********************************************************************************/
/* Description     : Turn on display and turn off cursor			  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidDisplayOnCursorOff(void)
{
	 CLCD_vidSendCommand(CLCD_DISPLAY_ON_CURSOR_OFF_CMD);
}
/**********************************************************************************/
/* Description     : Turn off display and turn off cursor			  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidDisplayOffCursorOff(void)
{
	 CLCD_vidSendCommand(CLCD_DISPLAY_OFF_CURSOR_OFF_CMD);
}
/**********************************************************************************/
/* Description     : Turn on display and turn on cursor			          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidDisplayOnCursorOn(void)
{
	 CLCD_vidSendCommand(CLCD_DISPLAY_ON_CURSOR_ON_CMD);
}
/**********************************************************************************/
/* Description     : Turn off display and turn on cursor			  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidDisplayOffCursorOn(void)
{
	CLCD_vidSendCommand(CLCD_DISPLAY_OFF_CURSOR_ON_CMD);
}
/**********************************************************************************/
/* Description     : Blink the cursor of Character LCD				  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidBlinkCursor(void)
{
	CLCD_vidSendCommand(CLCD_BLINK_CURSOR_CMD);
}
/**********************************************************************************/
/* Description     : Shift left the cursor of Character LCD			  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidShiftLeftCursor(void)
{
	CLCD_vidSendCommand(CLCD_SHIFT_LEFT_CURSOR_CMD);
}
/**********************************************************************************/
/* Description     : Shift right the cursor of Character LCD			  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidShiftRightCursor(void)
{
	CLCD_vidSendCommand(CLCD_SHIFT_RIGHT_CURSOR_CMD);
}
/**********************************************************************************/
/* Description     : Shift left the entire display of Character LCD		  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidShiftDisplayLeft(void)
{
	CLCD_vidSendCommand(CLCD_SHIFT_LEFT_DISPLAY_CMD);
}
/**********************************************************************************/
/* Description     : Shift right the entire display of Character LCD		  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidShiftDisplayRight(void)
{
	CLCD_vidSendCommand(CLCD_SHIFT_RIGHT_DISPLAY_CMD);
}
/**********************************************************************************/
/* Description     : Force cursor to be at the beginning of the first line	  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidBeginAtFirstLine(void)
{
	CLCD_vidSendCommand(CLCD_BEGIN_AT_FIRST_LINE_CMD);
}
/**********************************************************************************/
/* Description     : Force cursor to be at the beginning of the second line	  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidBeginAtSecondLine(void)
{
	CLCD_vidSendCommand(CLCD_BEGIN_AT_SECOND_LINE_CMD);
}
/**********************************************************************************/
/* Description     : Clear the entire display of character LCD			  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidClearDisplay(void)
{
	CLCD_vidSendCommand(CLCD_DISPLAY_CLEAR_CMD);
}
/**********************************************************************************/
/* Description     : Set up character LCD to operate on the entry mode		  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidSetEntryMode(void)
{
	CLCD_vidSendCommand(CLCD_ENTRY_MODE_CMD);
}
/**********************************************************************************/
/* Description     : Write a string on the Character LCD display		  */
/* Input Arguments : u8* Copy_pu8String				                  */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidWriteString(u8* Copy_pu8String)
{
	/* Local Variables Definitions */
	u32 Local_u32Counter = 0 ;

	/* Write the passed string on the CLCD display */
	while(Copy_pu8String[Local_u32Counter] != '\0')
	{
		/* Write a character */
		CLCD_vidWriteCharacter(Copy_pu8String[Local_u32Counter]);

		/* Increment the counter */
		Local_u32Counter++;

		/* Check if the counter reached 16 or not */
		if(Local_u32Counter == 16)
		{
			/* Force CLCD cursor to begin at second line */
			CLCD_vidBeginAtSecondLine();
		}
	}
}
/**********************************************************************************/
/* Description     : Write an integer number on the Character LCD display	  */
/* Input Arguments : s32 Copy_s32Num						  */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidWriteNumber(s32 Copy_s32Num)
{
	/* Local Variables Definitions */
	s32 Local_s32NumCopy = Copy_s32Num;
	u8  Local_u8DigitCounter = 0;
	s8  Local_s8DigitIndex;
	u8* Local_pu8NumDigits;

	if(Copy_s32Num == 0)
	{
		/* Write 0 on CLCD */
		CLCD_vidWriteCharacter('0');
	}

	if(Copy_s32Num < 0)
	{
		/* Write Negative Sign on CLCD */
		CLCD_vidWriteCharacter('-');

		Local_s32NumCopy *= -1;

		Copy_s32Num *= -1;
	}

	/* Count number of digits for the integer */
	while(Local_s32NumCopy != 0)
	{
		Local_s32NumCopy = Local_s32NumCopy / 10;
		Local_u8DigitCounter++;
	}

	/* Allocate memory in heap for number  */
	Local_pu8NumDigits = (u8*) malloc(Local_u8DigitCounter*sizeof(u8));

	/* Separate number's digits then organizing them into a char array */

	for(Local_s8DigitIndex = Local_u8DigitCounter-1 ; Local_s8DigitIndex >= 0 ; Local_s8DigitIndex--)
	{
		Local_pu8NumDigits[Local_s8DigitIndex] = (Copy_s32Num % 10) + '0';
		Copy_s32Num = Copy_s32Num / 10;
	}

	/* Write the passed number on the CLCD display */
	for(Local_s8DigitIndex = 0 ; Local_s8DigitIndex < Local_u8DigitCounter ; Local_s8DigitIndex++)
	{
		CLCD_vidWriteCharacter(Local_pu8NumDigits[Local_s8DigitIndex]);
	}
}
/**********************************************************************************/
/* Description     : Force the Character LCD controller to point CGRAM address	  */
/* Input Arguments : u8 Copy_u8Location						  */
/* Return          : u8							          */
/**********************************************************************************/
u8 CLCD_u8SetCGRamAddress(u8 Copy_u8Location)
{
	/* Local Variables Definitions */
	u8 local_u8ErrorStatus = RT_OK ;

	if(Copy_u8Location < 8)
	{
		CLCD_vidSendCommand(64 + (Copy_u8Location * 8));
	}
	else
	{
		/* Function is not working as expected */
		local_u8ErrorStatus = RT_NOK;
	}
	return local_u8ErrorStatus;
}
/**********************************************************************************/
/* Description     : Add arabic characters to CGRAM of Character LCD		  */
/* Input Arguments : u8* Copy_pu8Character,u8 Copy_u8Location			  */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidWriteArabicCharactersOnCGRam(u8* Copy_pu8Character,u8 Copy_u8Location)
{
	CLCD_u8SetCGRamAddress(Copy_u8Location);

	for(u32 i = 0 ; i < 8 ; i++)
	{
		CLCD_vidWriteCharacter(Copy_pu8Character[i]);
	}
}
/**********************************************************************************/
/* Description     : Put the cursor at a specific location (segment) on the  	  */
/* 		     Character LCD display					  */
/* Input Arguments : u8 Copy_u8RowNumber , u8 Copy_u8ColumnNumber	          */
/* Return          : u8						      	          */
/**********************************************************************************/
u8 CLCD_u8goTo(u8 Copy_u8RowNumber , u8 Copy_u8ColumnNumber)
{
	/* Local Variables Definitions */
	u8 local_u8ErrorStatus = RT_OK ;

	if((Copy_u8ColumnNumber >= 0) && (Copy_u8ColumnNumber <= 15))
	{
		switch(Copy_u8RowNumber)
		{
		case 0:
			CLCD_vidSendCommand(Copy_u8ColumnNumber+128);
			break;
		case 1:
			CLCD_vidSendCommand(Copy_u8ColumnNumber+192);
			break;
		default:
			local_u8ErrorStatus = RT_NOK;
		}
	}
	else
	{
		/* Function is not working as expected */
		local_u8ErrorStatus = RT_NOK;
	}
	return local_u8ErrorStatus ;
}
