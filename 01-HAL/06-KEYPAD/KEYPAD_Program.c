/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Sep 20, 2021               	*/
/*              SWC              : KEYPAD		        */
/*              Description	 : KEYPAD Program               */
/* 	        Version          : V1.0                         */
/****************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_ERRORS.h"
#include "../../LIB/SERVICE_FUNCTIONS.h"

#include "../../MCAL/DIO/DIO_Interface.h"

#include "KEYPAD_Interface.h"
#include "KEYPAD_Private.h"
#include "KEYPAD_Config.h"

#include "util/delay.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            GLOBAL VARIABLES DEFINITIONS	                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/* Set Keypad Type To Operate On From Config File */
#if    KEYPAD_TYPE == NORMAL_KEYPAD

	/* Define Normal Keypad */
	static u8 Global_u8NormalKeypad[KEYPAD_ROWS_NUM][KEYPAD_COLUMNS_NUM] = {{ 1  , 2  , 3  , 4  },
										{ 5  , 6  , 7  , 8  },
										{ 9  , 10 , 11 , 12 },
										{ 13 , 14 , 15 , 16 }};

#elif  KEYPAD_TYPE == CALCULATOR_KEYPAD

	/* Define Calculator Keypad */
	static u8 Global_u8CalculatorKeypad[KEYPAD_ROWS_NUM][KEYPAD_COLUMNS_NUM] = {{ '1' , '2' , '3' , '+' },
										    { '4' , '5' , '6' , '-' },
										    { '7' , '8' , '9' , 'x' },
										    { '=' , '0' , '.' , '/' }};
#else
	#error " Wrong Keypad Type Configuration! "
#endif

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                           	  PUBLIC FUNCTIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Initialize Keypad	   					  */
/* Input Arguments : void						          */
/* Return          : void						          */
/**********************************************************************************/
void KEYPAD_vidInit(void)
{
	/******************************************Set Direction of All Pins Connected To Keypad Rows as Inputs*****************************************/
	DIO_u8setPinDir(KEYPAD_PORT,KEYPAD_ROW_0,INPUT);
	DIO_u8setPinDir(KEYPAD_PORT,KEYPAD_ROW_1,INPUT);
	DIO_u8setPinDir(KEYPAD_PORT,KEYPAD_ROW_2,INPUT);
	DIO_u8setPinDir(KEYPAD_PORT,KEYPAD_ROW_3,INPUT);


	/******************************************Set Direction of All Pins Connected To Keypad Columns as Outputs*****************************************/
	DIO_u8setPinDir(KEYPAD_PORT,KEYPAD_COLUMN_0,OUTPUT);
	DIO_u8setPinDir(KEYPAD_PORT,KEYPAD_COLUMN_1,OUTPUT);
	DIO_u8setPinDir(KEYPAD_PORT,KEYPAD_COLUMN_2,OUTPUT);
	DIO_u8setPinDir(KEYPAD_PORT,KEYPAD_COLUMN_3,OUTPUT);

	/******************************************Set Initial Value of All Pins Connected To Keypad Rows as Input Pulled up*****************************************/
	DIO_u8setPinVal(KEYPAD_PORT,KEYPAD_ROW_0,HIGH);
	DIO_u8setPinVal(KEYPAD_PORT,KEYPAD_ROW_1,HIGH);
	DIO_u8setPinVal(KEYPAD_PORT,KEYPAD_ROW_2,HIGH);
	DIO_u8setPinVal(KEYPAD_PORT,KEYPAD_ROW_3,HIGH);


	/******************************************Set Initial Value of of All Pins Connected To Keypad Columns as High State*****************************************/
	DIO_u8setPinVal(KEYPAD_PORT,KEYPAD_COLUMN_0,HIGH);
	DIO_u8setPinVal(KEYPAD_PORT,KEYPAD_COLUMN_1,HIGH);
	DIO_u8setPinVal(KEYPAD_PORT,KEYPAD_COLUMN_2,HIGH);
	DIO_u8setPinVal(KEYPAD_PORT,KEYPAD_COLUMN_3,HIGH);
}
/**********************************************************************************/
/* Description     : Get Pressed Key on Keypad					  */
/* Input Arguments : void						          */
/* Return          : u8							          */
/**********************************************************************************/
u8 KEYPAD_u8GetPressedKey(void)
{
	/* Local Variables Definitions */
	u8 Local_u8PressedKeyVal = KEYPAD_NO_PRESSED_KEY;   /* Variable to hold value of pressed key; Initialized with KEYPAD_NO_PRESSED_KEY Status */
	u8 Local_u8ColumnCounter;			    /* Variable to hold current column number */
	u8 Local_u8RowCounter; 		            	    /* Variable to hold current row number */
	u8 Local_pu8PinStatus;				    /* Variable to hold pin status */

	/* Traverse over Keypad matrix to check whether any key is pressed or not */
	/* Select Column */
	for(Local_u8ColumnCounter = KEYPAD_COLUMN_0 ; Local_u8ColumnCounter < 8 ; Local_u8ColumnCounter++)
	{
		/* Activate current column through setting the value of pin connected to it as low */
		DIO_u8setPinVal(KEYPAD_PORT,Local_u8ColumnCounter,LOW);

		/* Select Row */
		for(Local_u8RowCounter = KEYPAD_ROW_0 ; Local_u8RowCounter < 4 ; Local_u8RowCounter++)
		{
			/* Get pin status connected to current row */
			DIO_u8getPinVal(KEYPAD_PORT,Local_u8RowCounter,&Local_pu8PinStatus);

			/* Check if any key on current column is pressed */
			if(Local_pu8PinStatus == 0)
			{
				/* Set 5 ms delay to wait for bouncing time */
				_delay_ms(5);

				/* Get pin status connected to current row */
				DIO_u8getPinVal(KEYPAD_PORT,Local_u8RowCounter,&Local_pu8PinStatus);

				/* Check if key is pressed after bouncing time */
				if(Local_pu8PinStatus == 0)
				{
					/* Get the value of pressed key */
					Local_u8PressedKeyVal = Global_u8NormalKeypad[Local_u8RowCounter][Local_u8ColumnCounter - 4];
				}

				/* Check if key is still pressed */
				while(Local_pu8PinStatus == 0)
				{
					/* Get pin status connected to current row */
					DIO_u8getPinVal(KEYPAD_PORT,Local_u8RowCounter,&Local_pu8PinStatus);
				}

				/* Set 5 ms delay to wait for bouncing time */
				_delay_ms(5);

				/* Break the loop */
				break;
			}
		}

		/* Deactivate current column through setting the value of pin connected to it as high */
		DIO_u8setPinVal(KEYPAD_PORT,Local_u8ColumnCounter,HIGH);
	}

	return Local_u8PressedKeyVal;
}