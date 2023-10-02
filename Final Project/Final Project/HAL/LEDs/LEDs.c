/*
 * LEDs.c
 *
 * Created: 11/12/2022 1:03:34 PM
 *  Author: Mohamed Taha Gabriel
 */ 

#include "LEDs.h"

//initialize the LEDs
void LED_init(uint8_t ledPort , uint8_t ledPin)
{
	DIO_init_pin(ledPort,ledPin,OUTPUT);
}

//TURN ON THE LED
void LED_ON(uint8_t ledPort , uint8_t ledPin)
{
	DIO_write_pin(ledPort,ledPin,HIGH);
}

//TURN OFF THE LED
void LED_OFF(uint8_t ledPort , uint8_t ledPin)
{
	DIO_write_pin(ledPort,ledPin,LOW);
}

//TOGGLE THE LED
void LED_toggle(uint8_t ledPort , uint8_t ledPin)
{
	
	DIO_toggle_pin(ledPort,ledPin);
}