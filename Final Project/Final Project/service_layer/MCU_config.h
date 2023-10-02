/*
 * MCU_config.h
 *
 * Created: 11/12/2022 10:10:52 AM
 *  Author: Mohamed Taha Gabriel
 */ 


#ifndef MCU_CONFIG_H_
#define MCU_CONFIG_H_

#define F_CPU 8000000UL
#define AVR_IO
#include <avr/io.h>
#include <util/delay.h>

typedef unsigned char uint8_t;
#define NULL (void*)0

#ifndef AVR_IO
/************************************************************************/
/* ATMEGA32A RIGISTERS                                                                     */
/************************************************************************/

//PORT A 
#define PORTA *((volatile uint8_t * )(0X3B))
#define DDRA *((volatile uint8_t * )(0X3A))
#define PINA *((volatile uint8_t * )(0X39))

#define PINA0 0


//PORT B
#define PORTB *((volatile uint8_t * )(0X38))
#define DDRB *((volatile uint8_t * )(0X37))
#define PINB *((volatile uint8_t * )(0X36))

#define PINB3 3

//PORT C
#define PORTC *((volatile uint8_t * )(0X35))
#define DDRC *((volatile uint8_t * )(0X34))
#define PINC *((volatile uint8_t * )(0X33))

//PORT D
#define PORTD *((volatile uint8_t * )(0X32))
#define DDRD *((volatile uint8_t * )(0X31))
#define PIND *((volatile uint8_t * )(0X30))



/**
 * Timers' Registers 
 * 
 */

// Timer0 Registers
#define TCCR0  *((volatile uint8_t *)0x53)  // timer0 control register 
#define FOC0 7  //TCCR0 bit 7
#define WGM00 6 //TCCR0 bit 6
#define	COM01 5 //TCCR0 bit 5
#define COM00 4 //TCCR0 bit 4
#define WGM01 3 //TCCR0 bit 3
#define CS02  2 //TCCR0 bit 2
#define CS01  1 //TCCR0 bit 1
#define CS00  0 //TCCR0 bit 0
#define TCNT0  *((volatile uint8_t *)0x52)  // timer0 register
#define OCR0  *((volatile uint8_t *)0x5c)	 // timer0 output compare register
#define TIFR  *((volatile uint8_t *)0x58)  // timer0 register
#define TOV0 0 //timer0 overflow flag bit
#define OCF0 1 // timer0 Output Compare Flag 


#define TIMSK *((volatile uint8_t *)0x59)  // timer0 register
#define TOIE0   0
#define OCIE0   1
/************************************************************************/
/* interrupt                                                                      */
/************************************************************************/

#define MCUCR *((volatile uint8_t *)0x55)  // 8-bit register
#define MCUCSR *((volatile uint8_t *)0x54)  // 8-bit register
#define GICR *((volatile uint8_t *)0x5B)  // 8-bit register
#define GIFR *((volatile uint8_t *)0x5A)  // 8-bit register
//External interrupt 0 sense bits
#define ISC00   0
#define ISC01   1
//external interrupt enable bits 
#define INT2    5
#define INT0    6
#define INT1    7

/************************************************************************/
/* ADC                                                                     */
/************************************************************************/
#define ADMUX *((volatile uint8_t *)0x27)  // 8-bit register
#define ADCSRA *((volatile uint8_t *)0x26)
#define ADCH *((volatile uint8_t *)0x25)
#define ADCL *((volatile uint8_t *)0x24)
#define SFIOR *((volatile uint8_t *)0x50)

//ADCMUC bits 
#define  REFS1 7
#define  REFS0 6
#define  ADLAR 5
#define  MUX4  4
#define  MUX3  3
#define  MUX2  2
#define  MUX1  1
#define  MUX0  0

//ADCSRA bits
#define ADEN  7
#define ADSC  6
#define ADATE 5 
#define ADIF  4
#define ADIE  3
#define ADPS2 2
#define ADPS1 1
#define ADPS0 0

//SFIOR register bits for ADC trigger 
#define  ADTS2 7
#define  ADTS1 6
#define  ADTS0 5

#endif

#endif /* MCU_CONFIG_H_ */