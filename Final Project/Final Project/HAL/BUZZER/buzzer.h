/*
 * buzzer.h
 *
 * Created: 01/01/2023 16:01:59
 *  Author: Ayaya
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#include "../../MCAL/DIO/DIO.h"


// BUZZER configuration
#define BUZZER_1 'b',7

//initialize the BUZZER
void BUZZER_init(uint8_t buzzerPort , uint8_t buzzerPin);

//TURN ON THE LED
void BUZZER_ON(uint8_t buzzerPort , uint8_t buzzerPin);

//TURN OFF THE LED
void BUZZER_OFF(uint8_t buzzerPort , uint8_t buzzerPin);




#endif /* BUZZER_H_ */