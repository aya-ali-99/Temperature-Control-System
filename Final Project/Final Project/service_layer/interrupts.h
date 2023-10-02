/*
 * interrupts.h
 *
 * Created: 26/11/2022 11:24:48
 *  Author: Ayaya
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

/* External Interrupt Request 0 */

/ *Timer2 Compare Handler* /
#define TIM2_COMP __vector_4
/ *Timer2 Overflow Handler * /
#define TIM2_OVF __vector_5

/ * Timer/Counter0 Compare Match* /
#define TIMER0_COMP_vect    __vector_10


/ * Timer/Counter0 Overflow * /
#define TIMER0_OVF_vect     __vector_11



*/
/* RX complete interrupt */
#define UART_RXC_VECT     __vector_13

/* UART data register empty */
#define UART_UDRE_VECT     __vector_14

/* UART TX complete */
#define UART_TXC_VECT     __vector_15






#endif /* INTERRUPTS_H_ */