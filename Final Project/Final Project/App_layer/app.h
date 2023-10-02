/*
 * app.h
 *
 * Created: 01/12/2022 16:57:53
 *  Author: Ayaya
 */ 


#ifndef APP_H_
#define APP_H_

#include "../HAL/LCD/lcd.h"
#include "../HAL/Keypad/keypad.h"
#include "../HAL/BUZZER/buzzer.h"
#include "../HAL/Buttons/buttons.h"
#include "../HAL/LEDs/LEDs.h"
#include "../HAL/EEPROM/EEPROM_MT.h"
#include "../MCAL/ADC/ADC.h"
#include "../MCAL/Timer0/timer0.h"
#include "../MCAL/Ex_interrupts/ex_interrupt.h"
#include "../MCAL/UART/UART.h"


//initialization function // void setup
void app_init();
// void loop
void app_start();

// Mode 1 for Starting the control system
void mode_1(uint8_t temp_H , uint8_t temp_L);

// Mode 2 for Entering the values of High and Low temperature
// then save it on the EEPROM
// passes temp high and low values by reference to change it
void mode_2(uint8_t *temp_H , uint8_t *temp_L);

// Mode 3 for displaying the values of T high and T low saved on the EEPROM
void mode_3(uint8_t t_high , uint8_t t_low);

// Receive the data sent through UART in the uart_data variable
void func_RXC_ISR();

// Fire alarm mode --> current temperature is above 70
void Fire_alarm_mode(uint8_t *t_current , uint32_t *ADC_val);

// Low temperature mode --> current temperature is below low value
void Low_temp_mode(uint8_t *t_current , uint32_t *ADC_val, uint8_t temp_H, uint8_t temp_L);

// High temperature mode --> current temperature is between High and fire alarm values
void High_temp_mode(uint8_t *t_current , uint32_t *ADC_val, uint8_t temp_H, uint8_t temp_L);

// Normal temperature mode --> current temperature is between High and Low values
void Normal_temp_mode(uint8_t *t_current , uint32_t *ADC_val, uint8_t temp_H, uint8_t temp_L);

#endif /* APP_H_ */