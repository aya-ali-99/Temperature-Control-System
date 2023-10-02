/*
 * ex_interrupt.h
 *
 * Created: 26/11/2022 11:34:42
 *  Author: Ayaya
 */ 


#ifndef EX_INTERRUPT_H_
#define EX_INTERRUPT_H_

#include "../../service_layer/MCU_config.h"
#include "../../service_layer/interrupts.h"

typedef enum{
	low_level_sense,
	anyLogicChange_sense,
	falling_edge_sense,
	rising_edge_sense
	}EN_sinterrupt_sense_t;

//External interrupt 0 initialization
void EXT_INT_0_init(EN_sinterrupt_sense_t sense);
//External interrupt 1 initialization
void EXT_INT_1_init(EN_sinterrupt_sense_t sense);
//External interrupt 2 initialization
void EXT_INT_2_init(EN_sinterrupt_sense_t sense);



#endif /* EX_INTERRUPT_H_ */