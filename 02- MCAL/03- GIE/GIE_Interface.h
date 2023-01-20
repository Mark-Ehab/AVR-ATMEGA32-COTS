/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Nov 7, 2021              	*/
/*              SWC              : GIE				*/
/*              Description	 : GIE Interface                */
/* 	        Version          : V1.0                         */
/****************************************************************/
#ifndef MCAL_GIE_INTERFACE_H_
#define MCAL_GIE_INTERFACE_H_


 	 	 	 	 	 /* Interface Macros */

/* Global Interrupt Enable and Disable Flags Macros */

#define GIE_ENABLE					0b10000000
#define GIE_DISABLE					0b01111111

/***************************************************************/


  	  	  	  	  	 /* Functions Prototypes */

/**********************************************************************************/
/* Description     : Enable/Disable Global Interrupt 	   			  */
/* Input Arguments : u8 Copy_u8Flag		  			          */
/* Return          : u8                       				          */
/**********************************************************************************/
u8 GIE_u8EnableGlobalInterrupt(u8 Copy_u8Flag);

#endif /* MCAL_GIE_INTERFACE_H_  */
