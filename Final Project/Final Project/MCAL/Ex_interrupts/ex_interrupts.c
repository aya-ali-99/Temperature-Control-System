/*
 * ex_interrupts.c
 *
 * Created: 26/11/2022 11:24:36
 *  Author: Ayaya
 */ 

#include "ex_interrupt.h"


//External interrupt 0 initialization
void EXT_INT_0_init(EN_sinterrupt_sense_t sense)
{
	//1. Enable global interrupt
	sei();
	
	//2. Choose the interrupt sense on external interrupt 0
	switch (sense)
	{
		case low_level_sense:
			MCUCR &= ~((1<<ISC00) | (1<<ISC01));  //Low level interrupt
			break;
		case anyLogicChange_sense:
			MCUCR |= (1<<ISC00);				//Any logic change 
			break;
		case falling_edge_sense:
			MCUCR |= (1<<ISC01);				//Falling edge trigger
			break;
		case rising_edge_sense:
			MCUCR |= (1<<ISC01) | (1<<ISC00);	//Rising edge trigger
			break;
		default:
			break;
	}
	//3. Enable the external interrupt 0
	GICR |= (1<<INT0);
}
//External interrupt 1 initialization
void EXT_INT_1_init(EN_sinterrupt_sense_t sense)
{
	//1. Enable global interrupt
	sei();
	
	//2. Choose the interrupt sense on external interrupt 1
	switch (sense)
	{
		case low_level_sense:
			MCUCR &= ~((1<<ISC10) | (1<<ISC11));	//Low level interrupt
			break;
		case anyLogicChange_sense:
			MCUCR |= (1<<ISC10);				//Any logic change
			break;
		case falling_edge_sense:
			MCUCR |= (1<<ISC11);				//Falling edge trigger
			break;
		case rising_edge_sense:
			MCUCR |= (1<<ISC11) | (1<<ISC10);	//Rising edge trigger
			break;
		default:
			break;
	}
	//3. Enable the external interrupt 1
	GICR |= (1<<INT1);
}
//External interrupt 2 initialization
void EXT_INT_2_init(EN_sinterrupt_sense_t sense)
{
	//1. Enable global interrupt
	sei();
	
	//2. Choose the interrupt sense on external interrupt 2
	switch (sense)
	{
		
		case falling_edge_sense:
			MCUCSR &= ~(1<<ISC2);		//Falling edge trigger
			break;
		case rising_edge_sense:
			MCUCSR |= (1<<ISC2) ;		//Rising edge trigger
			break;
		default:
			break;
	}
	//3. Enable the external interrupt 2
	GICR |= (1<<INT2);
}