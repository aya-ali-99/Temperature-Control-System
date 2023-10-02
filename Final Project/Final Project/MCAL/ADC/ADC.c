/*
 * ADC.c
 *
 * Created: 17/12/2022 10:10:22
 *  Author: Ayaya
 */ 



#include "ADC.h"

//initialization of the ADC
void ADC_init()
{
	// Set all used ADC channels as inputs
	DDRA &= ~ ADC_USED_CHANNELS;
	
	// Select the reference
	#if (ADC_VOLTAGE_REF == ADC_AVCC_SOURCE_5V)
		SET_BIT(ADMUX, REFS0);
		CLEAR_BIT(ADMUX, REFS1);
	#elif (ADC_VOLTAGE_REF == ADC_INTERNAL_SOURCE_2_56V)
		SET_BIT(ADMUX, REFS0);
		SET_BIT(ADMUX, REFS1);
	#endif
	
	// Select the prescaler
	#if (ADC_PRESCALER == ADC_PRESCALER_128)
		SET_BIT(ADCSRA, ADPS0);
		SET_BIT(ADCSRA, ADPS1);
		SET_BIT(ADCSRA, ADPS2);
	//#elif (ADC_PRESCALER == ADC_PRESCALER_2)
	#endif
	
	// Select right or left adjustment
	#if (ADC_READ_ADJEST == ADC_RIGHT_ADJUST_READ)
		CLEAR_BIT(ADMUX, ADLAR);
	#else
		SET_BIT(ADMUX, ADLAR);
	#endif
	
	// Enable the ADC
	SET_BIT(ADCSRA, ADEN);
}


//ADC read function
uint16_t ADC_read(EN_ADC_chanel_t channel)
{
	uint16_t ADC_value = 0;
	
	// Select the channel
	ADMUX &= 0b11100000;
	ADMUX |= channel;   // Or use switch case 
	
	// Start conversion
	SET_BIT(ADCSRA, ADSC);
	
	// Wait for the conversion to finish
	while (BIT_IS_CLEAR(ADCSRA, ADIF));
	
	// Clear the interrupt flag by setting logical 1 to it
	SET_BIT(ADCSRA, ADIF);
	
	// Read the ADC value
	#if (ADC_READ_ADJEST == ADC_RIGHT_ADJUST_READ)
		ADC_value = ADCL + (ADCH << 8);
	#else
		ADC_value = (ADCL >> 6) + (ADCH << 2);
	#endif
	
	// Return the value
	return ADC_value;
}

