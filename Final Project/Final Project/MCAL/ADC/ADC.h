/*
 * ADC.h
 *
 * Created: 17/12/2022 10:10:32
 *  Author: Ayaya
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "../../service_layer/common_macros.h"
#include "../../service_layer/MCU_config.h"
#include "../../service_layer/interrupts.h"

/************************************************************************/
/* ADC config                                                                     */
/************************************************************************/

//put here all the ADC channel that you intend to use in your application
#define ADC_USED_CHANNELS 0xff

#define ADC_AREF_SOURCE       0
#define ADC_AVCC_SOURCE_5V       1
#define ADC_INTERNAL_SOURCE_2_56V  3


#define ADC_VOLTAGE_REF    ADC_AVCC_SOURCE_5V
//#define ADC_VOLTAGE_REF    ADC_INTERNAL_SOURCE_2_56V

#define ADC_PRESCALER_2       1
#define ADC_PRESCALER_4       2
#define ADC_PRESCALER_8       3
#define ADC_PRESCALER_16      4
#define ADC_PRESCALER_32      5
#define ADC_PRESCALER_64      6
#define ADC_PRESCALER_128     7


#define ADC_PRESCALER   ADC_PRESCALER_128

#define ADC_RIGHT_ADJUST_READ   0
#define ADC_LEFT_ADJUST_READ    1

#define ADC_READ_ADJEST  ADC_RIGHT_ADJUST_READ

/************************************************************************/
/* ADC interface                                                                      */
/************************************************************************/

typedef enum {
	ADC_CH0,
	ADC_CH1,
	ADC_CH2,
	ADC_CH3,
	ADC_CH4,
	ADC_CH5,
	ADC_CH6,
	ADC_CH7
}EN_ADC_chanel_t;


//initialization of the ADC
void ADC_init();


//ADC read function
uint16_t ADC_read(EN_ADC_chanel_t channel);



#endif /* ADC_H_ */