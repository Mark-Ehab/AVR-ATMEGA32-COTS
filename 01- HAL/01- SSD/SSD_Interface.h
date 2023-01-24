/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Dec 19, 2022               	*/
/*              SWC              : SSD				*/
/*              Description	 : SSD Interface                */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef HAL_SSD_INTERFACE_H_
#define HAL_SSD_INTERFACE_H_

						/* Interface Macros */
/* Macros of common pin of seven segments */
#define SSD_COMMON  		1


/* Macros of common pins of multiplexing seven segments */
#define SSD_FIRST_COMMON  	1
#define SSD_SECOND_COMMON 	2


						/* Functions ProtoTypes */
/**********************************************************************************/
/* Description     : Initialize Seven Segment					  */
/* Input Arguments : void			    			          */
/* Return          : void                       			          */
/**********************************************************************************/
void SSD_vidSevenSegmentDisplayInit(void);
/**********************************************************************************/
/* Description     : Turn On Seven Segment					  */
/* Input Arguments : Copy_u8Common		    			          */
/* Return          : void                       			          */
/**********************************************************************************/
void SSD_vidTurnON(u8 Copy_u8Common);
/**********************************************************************************/
/* Description     : Turn Off Seven Segment					  */
/* Input Arguments : Copy_u8Common		    			          */
/* Return          : void                       				  */
/**********************************************************************************/
void SSD_vidTurnOFF(u8 Copy_u8Common);
/**********************************************************************************/
/* Description     : Display a number on seven segment from 0 to 9		  */
/* Input Arguments : Copy_u8Num			    			          */
/* Return          : void                       	                          */
/**********************************************************************************/
void SSD_vidDisplayNum(u8 Copy_u8Num);

#endif /* HAL_SSD_INTERFACE_H_ */
