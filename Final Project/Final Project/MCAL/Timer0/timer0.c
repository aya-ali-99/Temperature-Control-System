/*
 * timer0.c
 *
 * Created: 10/12/2022 11:05:02
 *  Author: Ayaya
 */ 


#include "timer0.h"

static void (*ptr2fun_t0ovf)(void) = NULL;
static void (*ptr2fun_t0comp)(void) = NULL;


// Timer0 initialization
void timer0_init(ET_T0MODES_t mode, EN_setPrescaler_t prescaler){	// Clear timer0 register 	TCNT0 = 0;		// Select the mode	// Enable 	switch (mode)
	{
		case NORMAL_MODE:
			// Select normal mode
			CLEAR_BIT(TCCR0, WGM00);
			CLEAR_BIT(TCCR0, WGM01);
			// Enable global interrupt
			sei();
			// Enable timer0 overflow 
			SET_BIT(TIMSK, TOIE0);
			break;
		case CTC_MODE:
			// Select CTC mode
			CLEAR_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);
			// Enable global interrupt
			sei();
			// Enable timer0 output compare interrupt
			SET_BIT(TIMSK, OCIE0);
			break;
		case FAST_PWM_MODE:
			// Select the fast PWM mode
			SET_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);
			
			// Select the mode of fast PWM
			#ifdef NON_INVERTING  // Non inverting mode
				CLEAR_BIT(TCCR0, COM00);
				SET_BIT(TCCR0, COM01);
			#else // Inverting mode
				SET_BIT(TCCR0, COM00);
				SET_BIT(TCCR0, COM01);
			#endif
			
			// Set pin b3 as output (OC0)
			SET_BIT(DDRB, PINB3);
			
			break;
		case PWM_PHASE_CORRECT_MODE:
			// Select PWM with phase correct mode
			SET_BIT(TCCR0, WGM00);
			CLEAR_BIT(TCCR0, WGM01);
			
			// Select the mode
			#ifdef NON_INVERTING  // Non inverting mode
				CLEAR_BIT(TCCR0, COM00);
				SET_BIT(TCCR0, COM01);
			#else // Inverting mode
				SET_BIT(TCCR0, COM00);
				SET_BIT(TCCR0, COM01);
			#endif
			
			// Set pin b3 as output (OC0)
			SET_BIT(DDRB, PINB3);
			break;
		default:
			// Error handling
			break;
	}		// Set prescaler	switch (prescaler)
	{
		case NO_CLOCK:
			CLEAR_BIT(TCCR0, CS00);
			CLEAR_BIT(TCCR0, CS01);
			CLEAR_BIT(TCCR0, CS02);
			break;
		case NO_PRESCALAR:
			SET_BIT(TCCR0, CS00);
			CLEAR_BIT(TCCR0, CS01);
			CLEAR_BIT(TCCR0, CS02);
			break;
		case PRESCALAR_8:
			CLEAR_BIT(TCCR0, CS00);
			SET_BIT(TCCR0, CS01);
			CLEAR_BIT(TCCR0, CS02);
			break;
		case PRESCALAR_64:
			SET_BIT(TCCR0, CS00);
			SET_BIT(TCCR0, CS01);
			CLEAR_BIT(TCCR0, CS02);
			break;
		case PRESCALAR_256:
			CLEAR_BIT(TCCR0, CS00);
			CLEAR_BIT(TCCR0, CS01);
			SET_BIT(TCCR0, CS02);
			break;
		case PRESCALAR_1024:
			SET_BIT(TCCR0, CS00);
			CLEAR_BIT(TCCR0, CS01);
			SET_BIT(TCCR0, CS02);
			break;
		default:
			// Error handling
			break;
	}}void timer0_start(uint8_t timer_iv, EN_setPrescaler_t prescaler){	// Set timer0 initial value
	TCNT0 = timer_iv;
	
	// Set prescaler
	switch (prescaler)
	{
		case NO_CLOCK:
			CLEAR_BIT(TCCR0, CS00);
			CLEAR_BIT(TCCR0, CS01);
			CLEAR_BIT(TCCR0, CS02);
			break;
		case NO_PRESCALAR:
			SET_BIT(TCCR0, CS00);
			CLEAR_BIT(TCCR0, CS01);
			CLEAR_BIT(TCCR0, CS02);
			break;
		case PRESCALAR_8:
			CLEAR_BIT(TCCR0, CS00);
			SET_BIT(TCCR0, CS01);
			CLEAR_BIT(TCCR0, CS02);
			break;
		case PRESCALAR_64:
			SET_BIT(TCCR0, CS00);
			SET_BIT(TCCR0, CS01);
			CLEAR_BIT(TCCR0, CS02);
			break;
		case PRESCALAR_256:
			CLEAR_BIT(TCCR0, CS00);
			CLEAR_BIT(TCCR0, CS01);
			SET_BIT(TCCR0, CS02);
			break;
		case PRESCALAR_1024:
			SET_BIT(TCCR0, CS00);
			CLEAR_BIT(TCCR0, CS01);
			SET_BIT(TCCR0, CS02);
			break;
		default:
		// Error handling
		break;
	}
	}void Timer0_Set_OCR0(uint8_t value){	OCR0 = value;}void timer0_stop(){	TCCR0 = 0;}void timer0_dutyCycle(ET_T0MODES_t mode, uint8_t duty){	switch(mode)	{		case FAST_PWM_MODE:			// Select the mode
			#ifdef NON_INVERTING  // Non inverting mode
				Timer0_Set_OCR0((duty*256)/100-1);
			#else // Inverting mode
				Timer0_Set_OCR0((duty*255)/100);
			#endif			break;		case PWM_PHASE_CORRECT_MODE:			// Select the mode
			#ifdef NON_INVERTING  // Non inverting mode
				Timer0_Set_OCR0((duty*255)/100);
			#else // Inverting mode
				Timer0_Set_OCR0(255-((duty*255)/100));
			#endif			break;		default:			// Error handling			break;	}}void timer0_setCallBack(void(* ptr_to_ISR_t0ovf)(void), ET_T0MODES_t mode)
{
	switch (mode)
	{
		case NORMAL_MODE:
			if (ptr_to_ISR_t0ovf != NULL)
			{
				ptr2fun_t0ovf = ptr_to_ISR_t0ovf;
			}
			break;
		case CTC_MODE:
			if (ptr_to_ISR_t0ovf != NULL)
			{
				ptr2fun_t0comp = ptr_to_ISR_t0ovf;
			}
			break;
	}
	
	
}
ISR(TIMER0_OVF_vect){	if (ptr2fun_t0ovf != NULL)
	{
		ptr2fun_t0ovf();		// func();
	}}ISR(TIMER0_COMP_vect){	if (ptr2fun_t0comp != NULL)
	{
		ptr2fun_t0comp();		// func_comp();
	}}