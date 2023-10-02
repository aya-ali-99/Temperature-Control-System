/*
 * buttons.c
 *
 * Created: 11/12/2022 1:03:15 PM
 *  Author: Mohamed Taha Gabriel
 */ 
#include "buttons.h"


void button_init(uint8_t btn_port ,uint8_t btn_pin )
{
	DIO_init_pin(btn_port,btn_pin,INPUT);
}

void button_read(uint8_t btn_port ,uint8_t btn_pin, uint8_t *btn_state)
{
	DIO_read_pin(btn_port,btn_pin,btn_state);
}

//set the button as internal pull up
void button_set_pullUp(uint8_t btn_port ,uint8_t btn_pin)
{
	DIO_write_pin(btn_port, btn_pin, HIGH);
}

