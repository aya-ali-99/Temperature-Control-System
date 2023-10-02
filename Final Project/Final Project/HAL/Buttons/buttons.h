/*
 * buttons.h
 *
 * Created: 11/12/2022 1:02:51 PM
 *  Author: Mohamed Taha Gabriel
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_
#include "../../MCAL/DIO/DIO.h"

#define BUTTON 'd',2

#define BUTTON2_PIN 3
#define BUTTON2_PORT 'b'

//init to the button 
void button_init(uint8_t btn_port ,uint8_t btn_pin );

//read the value of the button
void button_read(uint8_t btn_port ,uint8_t btn_pin, uint8_t *btn_state);

//set the button as internal pull up
void button_set_pullUp(uint8_t btn_port ,uint8_t btn_pin);


#endif /* BUTTONS_H_ */