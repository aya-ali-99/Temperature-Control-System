/*
 * timer0.h
 *
 * Created: 10/12/2022 11:05:15
 *  Author: Ayaya
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#include "../../service_layer/MCU_config.h"
#include "../../service_layer/common_macros.h"
#include "../../service_layer/interrupts.h"


#define ONE_MS_MARK 131

#define NON_INVERTING

typedef enum{
	 NO_CLOCK,
	 NO_PRESCALAR,
	 PRESCALAR_8,
	 PRESCALAR_64,
	 PRESCALAR_256,
	 PRESCALAR_1024,
	 EXT_CLK_FALLING_EDGE,
	 EXT_CLK_RISING_EDGE
	}EN_setPrescaler_t;


typedef enum t0ENUM{

void timer0_dutyCycle(ET_T0MODES_t mode, uint8_t duty);

void timer0_setCallBack(void(* ptr_to_ISR_t0ovf)(void), ET_T0MODES_t mode);

#endif /* TIMER0_H_ */