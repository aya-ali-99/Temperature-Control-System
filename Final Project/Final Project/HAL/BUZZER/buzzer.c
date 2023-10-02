/*
 * buzzer.c
 *
 * Created: 01/01/2023 16:01:48
 *  Author: Ayaya
 */ 



#include "buzzer.h"


//initialize the BUZZER
void BUZZER_init(uint8_t buzzerPort , uint8_t buzzerPin)
{
	DIO_init_pin(buzzerPort,buzzerPin,OUTPUT);
}

//TURN ON THE BUZZER
void BUZZER_ON(uint8_t buzzerPort , uint8_t buzzerPin)
{
	DIO_write_pin(buzzerPort,buzzerPin,HIGH);
}

//TURN OFF THE BUZZER
void BUZZER_OFF(uint8_t buzzerPort , uint8_t buzzerPin)
{
	DIO_write_pin(buzzerPort,buzzerPin,LOW);
}
