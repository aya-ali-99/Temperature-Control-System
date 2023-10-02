/*
 * UART.h
 *
 * Created: 24/12/2022 12:50:03
 *  Author: Ayaya
 */ 


#ifndef UART_H_
#define UART_H_

#include "../../service_layer/MCU_config.h"
#include "../../service_layer/std_types_MT.h"
#include "../../service_layer/interrupts.h"

#define BAUD_RATE 9600

// UART init function

void UART_Init( unsigned int baud );

void UART_Transmit( unsigned char data );

// This function will enable the RX complete interrupt
// Also enable global interrupt

void UART_RXC_interruptEnable();

unsigned char UART_Receive( void );

void UART_sendString(char *str);

// Call back function to RX complete
void UART_setCallBcak(void (*p2f) (void));

#endif /* UART_H_ */