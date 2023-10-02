/*
 * DIO.h
 *
 * Created: 11/12/2022 1:02:06 PM
 *  Author: Mohamed Taha Gabriel
 */ 


#ifndef DIO_H_
#define DIO_H_
#include "../../service_layer/MCU_config.h"
#include "../../service_layer/std_types_MT.h"
//#define AVR



//input or output 
#define INPUT 0
#define OUTPUT 1

//high or low 
#define HIGH 1
#define LOW 0

typedef enum DIO_TAG{
	DIO_OK,
	DIO_NOT_OK=-1
	}EN_DIO_state_t;


// function to initialize a pin as input or output
EN_DIO_state_t DIO_init_pin(uint8_t port_number , uint8_t pin_number ,uint8_t direction );

//EN_DIO_state_t DIO_init_port(uint8_t port_number ,uint8_t direction ); // 0b11110000


//function to write digital high or digital low 
EN_DIO_state_t DIO_write_pin(uint8_t port_number , uint8_t pin_number , uint8_t value);



//function to toggle a pin
EN_DIO_state_t DIO_toggle_pin(uint8_t port_number , uint8_t pin_number);

//function to read the value of the pin
EN_DIO_state_t DIO_read_pin(uint8_t port_number , uint8_t pin_number, uint8_t* retValue );

// function to initialize all pins in a port// direction bits initialize the corresponding pins. 1 as output and 0 as inputEN_DIO_state_t DIO_init_port(uint8_t port_number ,uint8_t direction ); // 0b11110000

//function to initialize multiple pins
EN_DIO_state_t DIO_init_multiple_pins(uint8_t port_number,uint8_t pin_numbers ,uint8_t direction ); 

//function to write a certain value on the whole port//value bits write digital high or low on the corresponding pins. 1 as high and 0 as lowEN_DIO_state_t DIO_write_port(uint8_t port_number , uint8_t value); //0b1111000

// function to initialize upper pins in a port// direction bits initialize the corresponding pins. 1 as output and 0 as inputEN_DIO_state_t DIO_init_upper_pins_port(uint8_t port_number ,uint8_t direction );

// function to initialize lower pins in a port// direction bits initialize the corresponding pins. 1 as output and 0 as inputEN_DIO_state_t DIO_init_lower_pins_port(uint8_t port_number ,uint8_t direction );

//function to write a certain value on the upper pins of the port//value bits write digital high or low on the corresponding pins. 1 as high and 0 as lowEN_DIO_state_t DIO_write_upper_pins_port(uint8_t port_number , uint8_t value);

//function to write a certain value on the lower pins of the port//value bits write digital high or low on the corresponding pins. 1 as high and 0 as lowEN_DIO_state_t DIO_write_lower_pins_port(uint8_t port_number , uint8_t value);

#endif /* DIO_H_ */