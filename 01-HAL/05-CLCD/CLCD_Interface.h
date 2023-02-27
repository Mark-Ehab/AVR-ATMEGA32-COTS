/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Sep 18, 2021               	*/
/*              SWC              : CLCD		        	*/
/*              Description	 : CLCD Interface               */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef HAL_CLCD_INTERFACE_H_
#define HAL_CLCD_INTERFACE_H_

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	   INTERFACE MACROS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

#define CLCD_FUNCTION_SET_EIGHT_BIT_MODE_CMD  		                (u8) 0x38
#define CLCD_FUNCTION_SET_FOUR_BIT_MODE_CMD  		                (u8) 0x28
#define CLCD_DISPLAY_ON_CURSOR_OFF_CMD   	    	                (u8) 0x0C
#define CLCD_DISPLAY_OFF_CURSOR_OFF_CMD    	    	                (u8) 0x08
#define CLCD_DISPLAY_ON_CURSOR_ON_CMD   	    		        (u8) 0x0E
#define CLCD_DISPLAY_OFF_CURSOR_ON_CMD    	    	                (u8) 0x0A
#define CLCD_BLINK_CURSOR_CMD						(u8) 0x0F
#define CLCD_SHIFT_LEFT_CURSOR_CMD					(u8) 0x10
#define CLCD_SHIFT_RIGHT_CURSOR_CMD					(u8) 0x14
#define CLCD_SHIFT_LEFT_DISPLAY_CMD					(u8) 0x18
#define CLCD_SHIFT_RIGHT_DISPLAY_CMD					(u8) 0x1C
#define CLCD_BEGIN_AT_FIRST_LINE_CMD					(u8) 0x80
#define CLCD_BEGIN_AT_SECOND_LINE_CMD					(u8) 0xC0
#define CLCD_DISPLAY_CLEAR_CMD 						(u8) 0x01
#define CLCD_ENTRY_MODE_CMD						(u8) 0x06


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	 FUNCTIONS PROTOTYPES		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize Character LCD					  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidInit(void);
/**********************************************************************************/
/* Description     : Send a command to Character LCD controller			  */
/* Input Arguments : u8 Copy_u8Command					          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidSendCommand(u8 Copy_u8Command);
/**********************************************************************************/
/* Description     : Write a character on Character LCD				  */
/* Input Arguments : u8 Copy_u8Character				          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidWriteCharacter(u8 Copy_u8Character);
/**********************************************************************************/
/* Description     : Set up Character LCD on 8-bit mode			          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidSetEightBitMode(void);
/**********************************************************************************/
/* Description     : Set up Character LCD on 4-bit mode		                  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidSetFourBitMode(void);
/**********************************************************************************/
/* Description     : Turn on display and turn off cursor			  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidDisplayOnCursorOff(void);
/**********************************************************************************/
/* Description     : Turn off display and turn off cursor			  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidDisplayOffCursorOff(void);
/**********************************************************************************/
/* Description     : Turn on display and turn on cursor			          */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidDisplayOnCursorOn(void);
/**********************************************************************************/
/* Description     : Turn off display and turn on cursor			  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidDisplayOffCursorOn(void);
/**********************************************************************************/
/* Description     : Blink the cursor of Character LCD				  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidBlinkCursor(void);
/**********************************************************************************/
/* Description     : Shift left the cursor of Character LCD			  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidShiftLeftCursor(void);
/**********************************************************************************/
/* Description     : Shift right the cursor of Character LCD			  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidShiftRightCursor(void);
/**********************************************************************************/
/* Description     : Shift left the entire display of Character LCD		  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidShiftDisplayLeft(void);
/**********************************************************************************/
/* Description     : Shift right the entire display of Character LCD		  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidShiftDisplayRight(void);
/**********************************************************************************/
/* Description     : Force cursor to be at the beginning of the first line	  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidBeginAtFirstLine(void);
/**********************************************************************************/
/* Description     : Force cursor to be at the beginning of the second line	  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidBeginAtSecondLine(void);
/**********************************************************************************/
/* Description     : Clear the entire display of character LCD			  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidClearDisplay(void);
/**********************************************************************************/
/* Description     : Set up character LCD to operate on the entry mode		  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidSetEntryMode(void);
/**********************************************************************************/
/* Description     : Write a string on the Character LCD display		  */
/* Input Arguments : u8* Copy_pu8String				                  */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidWriteString(u8* Copy_pu8String);
/**********************************************************************************/
/* Description     : Write an integer number on the Character LCD display	  */
/* Input Arguments : s32 Copy_s32Num						  */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidWriteNumber(s32 Copy_s32Num);
/**********************************************************************************/
/* Description     : Force the Character LCD controller to point CGRAM address	  */
/* Input Arguments : u8 Copy_u8Location						  */
/* Return          : u8							          */
/**********************************************************************************/
u8 CLCD_u8SetCGRamAddress(u8 Copy_u8Location);
/**********************************************************************************/
/* Description     : Add arabic characters to CGRAM of Character LCD		  */
/* Input Arguments : u8* Copy_pu8Character,u8 Copy_u8Location			  */
/* Return          : void						          */
/**********************************************************************************/
void CLCD_vidWriteArabicCharactersOnCGRam(u8* Copy_pu8Character,u8 Copy_u8Location);
/**********************************************************************************/
/* Description     : Put the cursor at a specific location (segment) on the  	  */
/* 		     Character LCD display					  */
/* Input Arguments : u8 Copy_u8RowNumber , u8 Copy_u8ColumnNumber	          */
/* Return          : u8						      	          */
/**********************************************************************************/
u8 CLCD_u8goTo(u8 Copy_u8RowNumber , u8 Copy_u8ColumnNumber);

#endif /* HAL_CLCD_INTERFACE_H_ */
