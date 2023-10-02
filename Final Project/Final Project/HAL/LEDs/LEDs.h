/*
 * LEDs.h
 *
 * Created: 11/12/2022 1:03:52 PM
 *  Author: Mohamed Taha Gabriel
 */ 


#ifndef LEDS_H_
#define LEDS_H_

#include "../../MCAL/DIO/DIO.h"

//led 1 configuration 
#define LED_LOW 'b',4

//led 2 configuration
#define LED_NORMAL 'b',5

//led 3 configuration
#define LED_HIGH 'b',6

//led 3 configuration
#define LED4_PIN 0
#define LED4_PORT 'b'

//initialize the LEDs 
void LED_init(uint8_t ledPort , uint8_t ledPin);

//TURN ON THE LED 
void LED_ON(uint8_t ledPort , uint8_t ledPin);

//TURN OFF THE LED 
void LED_OFF(uint8_t ledPort , uint8_t ledPin);

//TURN OFF THE LED
void LED_toggle(uint8_t ledPort , uint8_t ledPin);





#endif /* LEDS_H_ */