/****************************************************************/
/* 		Author   	 : Mark Ehab                    */
/* 		Date     	 : Aug 19, 2023               	*/
/*              Description	 : Interrupt Vectors            */
/* 	        Version          : V1.0                         */
/****************************************************************/

#ifndef LIB_VECTOR_H_
#define LIB_VECTOR_H_

/* Macros for writing interrupt handler functions */

/* Concatenation Function */
#define VECTOR(x) __vector_##x

/* ISR Body */
#define ISR(vector) \
void vector (void) __attribute__ ((signal,used, externally_visible)) ; \
void vector (void)

/* External Interrupt Request 0 */
#define VECTOR_1	VECTOR(1)
/* External Interrupt Request 1 */
#define VECTOR_2	VECTOR(2)
/* External Interrupt Request 2 */
#define VECTOR_3	VECTOR(3)
/* Timer/Counter2 Compare Match */
#define VECTOR_4	VECTOR(4)
/* Timer/Counter2 Overflow */
#define VECTOR_5	VECTOR(5)
/* Timer/Counter1 Capture Event */
#define VECTOR_6	VECTOR(6)
/* Timer/Counter1 Compare Match A */
#define VECTOR_7	VECTOR(7)
/* Timer/Counter1 Compare Match B */
#define VECTOR_8	VECTOR(8)
/* Timer/Counter1 Overflow */
#define VECTOR_9	VECTOR(9)
/* Timer/Counter0 Compare Match */
#define VECTOR_10	VECTOR(10)
/* Timer/Counter0 Overflow */
#define VECTOR_11	VECTOR(11)
/* Serial Transfer Complete */
#define VECTOR_12	VECTOR(12)
/* USART, Rx Complete */
#define VECTOR_13	VECTOR(13)
/* USART Data Register Empty */
#define VECTOR_14	VECTOR(14)
/* USART, Tx Complete */
#define VECTOR_15	VECTOR(15)
/* ADC Conversion Complete */
#define VECTOR_16	VECTOR(16)
/* EEPROM Ready */
#define VECTOR_17	VECTOR(17)
/* Analog Comparator */
#define VECTOR_18	VECTOR(18)
/* Two-wire Serial Interface */
#define VECTOR_19	VECTOR(19)
/* Store Program Memory Ready */
#define VECTOR_20	VECTOR(20)


#endif /* LIB_VECTOR_H_ */
